#include "audio.h"
#include "app.h"
#include "constants.h"
#include "helpers.h"
#include <AudioToolbox/AudioToolbox.h>

static OSStatus render_callback(void                              *inRefCon,
                                AudioUnitRenderActionFlags UNUSED *ioActionFlags,
                                const AudioTimeStamp UNUSED       *inTimeStamp,
                                UInt32 UNUSED                      inBusNumber,
                                UInt32                             inNumberFrames,
                                AudioBufferList                   *ioData) {
    App       *app       = (App *)inRefCon;
    Transport *transport = &app->transport;
    Project   *project   = &app->project;
    Audio     *audio     = &app->audio;

    double phase = transport->phase;
    float *dataL = (float *)ioData->mBuffers[0].mData;
    float *dataR = (float *)ioData->mBuffers[1].mData;

    // "sequencer"
    Note   current_note = app->project.pattern[app->transport.curr_note_index];
    double duration_in_samples =
        subdivision_to_samples(app->project.bpm, current_note.subdivision, audio->sample_rate);

    for (UInt32 frame = 0; frame < inNumberFrames; ++frame) {

        if (transport->sample_count >= duration_in_samples) {
            transport->sample_count    = 0.0;
            transport->curr_note_index = (transport->curr_note_index + 1) % project->pattern_len;
        }

        double frequency       = project->tuning * pow(2.0, (current_note.midi_value - 69.0) / 12.0);
        double phase_increment = (TWO_PI / audio->sample_rate) * frequency;

        // "Wave generator"
        phase += phase_increment;
        if (phase >= 2.0 * M_PI) {
            phase -= 2.0 * M_PI;
        }

        if (SINE == current_note.waveform) {
            dataL[frame] = sin(phase) * transport->master_volume;
            dataR[frame] = sin(phase) * transport->master_volume;
        }
        if (SQUARE == current_note.waveform) {
            // Square wave: flip halway through the wave cycle
            if (phase >= M_PI) {
                dataL[frame] = -1.0 * transport->master_volume;
                dataR[frame] = -1.0 * transport->master_volume;
            } else {
                dataL[frame] = 1.0 * transport->master_volume;
                dataR[frame] = 1.0 * transport->master_volume;
            }
        }
        transport->sample_count++;
    }

    transport->phase = phase;
    return noErr;
}

/* AUDIO ENGINE */
// based on Matthijs Hollemans Learning Core Audio example
// https://gist.github.com/hollance/91d9da0d07a869ef9f56466aa46a6466
bool audio_init(AudioUnit *unit, struct App *app) {
    AudioStreamBasicDescription streamFormat = {0};
    streamFormat.mSampleRate                 = app->audio.sample_rate;
    streamFormat.mFormatID                   = kAudioFormatLinearPCM;
    streamFormat.mFormatFlags                = kAudioFormatFlagsNativeFloatPacked | kAudioFormatFlagIsNonInterleaved;
    streamFormat.mChannelsPerFrame           = 2;
    streamFormat.mBitsPerChannel             = 8 * sizeof(float);
    streamFormat.mBytesPerFrame              = sizeof(float);
    streamFormat.mFramesPerPacket            = 1;
    streamFormat.mBytesPerPacket             = streamFormat.mBytesPerFrame * streamFormat.mFramesPerPacket;

    AudioComponentDescription description = {.componentType         = kAudioUnitType_Output,
                                             .componentSubType      = kAudioUnitSubType_DefaultOutput,
                                             .componentManufacturer = kAudioUnitManufacturer_Apple,
                                             .componentFlags        = 0,
                                             .componentFlagsMask    = 0};

    AudioComponent component = AudioComponentFindNext(NULL, &description);
    if (!component) {
        fprintf(stderr, "Couldn't get output AudioUnit\n");
        return false;
    }

    if (noErr != AudioComponentInstanceNew(component, unit)) {
        fprintf(stderr, "Couldn't instantiate AudioUnit instance\n");
        return false;
    }

    AURenderCallbackStruct input = {.inputProc = render_callback, .inputProcRefCon = app};

    if (noErr != AudioUnitSetProperty(
                     *unit, kAudioUnitProperty_SetRenderCallback, kAudioUnitScope_Input, 0, &input, sizeof(input))) {
        fprintf(stderr, "Couldn't set render callback\n");
        return false;
    }

    if (noErr !=
        AudioUnitSetProperty(
            *unit, kAudioUnitProperty_StreamFormat, kAudioUnitScope_Input, 0, &streamFormat, sizeof(streamFormat))) {
        fprintf(stderr, "Couldn't set stream format\n");
        return false;
    }

    if (noErr != AudioUnitInitialize(*unit)) {
        fprintf(stderr, "Couldn't initialize AudioUnit\n");
        return false;
    }

    return true;
}

void audio_start(AudioUnit *unit) {
    if (noErr != AudioOutputUnitStart(*unit)) {
        fprintf(stderr, "Couldn't start AudioUnit\n");
    }
}

void audio_stop(AudioUnit *unit) {
    if (noErr != AudioOutputUnitStop(*unit)) {
        fprintf(stderr, "Couldn't stop AudioUnit\n");
    }
}

void audio_destroy(AudioUnit *unit) {
    if (noErr != AudioUnitUninitialize(*unit)) {
        fprintf(stderr, "Couldn't uninitialize AudioUnit\n");
    }
    if (noErr != AudioComponentInstanceDispose(*unit)) {
        fprintf(stderr, "Couldn't dispose AudioUnit\n");
    }
}
