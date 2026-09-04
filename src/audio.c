#include "audio.h"
#include "player.h"

#include <math.h>
#include <stdio.h>

static OSStatus render_callback(void *inRefCon,
                                AudioUnitRenderActionFlags __attribute__((unused)) * ioActionFlags,
                                const AudioTimeStamp __attribute__((unused)) * inTimeStamp,
                                UInt32 __attribute__((unused)) inBusNumber,
                                UInt32                         inNumberFrames,
                                AudioBufferList               *ioData) {
    Player *player = (Player *)inRefCon;
    double  phase  = player->phase;
    float  *dataL  = (float *)ioData->mBuffers[0].mData;
    float  *dataR  = (float *)ioData->mBuffers[1].mData;

    // "sequencer"
    for (UInt32 frame = 0; frame < inNumberFrames; ++frame) {
        Note curr_note = player->composition.pattern[player->curr_note_index];

        if (player->sample_count >= curr_note.duration_in_samples) {
            player->sample_count    = 0;
            player->curr_note_index = (player->curr_note_index + 1) % player->composition.pattern_len;
        }

        // "Wave generator"
        phase += curr_note.phase_increment;
        if (phase >= TWO_PI) {
            phase -= TWO_PI;
        }

        if (SINE == curr_note.waveform) {
            dataL[frame] = sin(phase);
            dataR[frame] = sin(phase);
        }
        if (SQUARE == curr_note.waveform) {
            // Square wave: flip halway through the wave cycle
            if (phase >= M_PI) {
                dataL[frame] = -1.0;
                dataR[frame] = -1.0;
            } else {
                dataL[frame] = 1.0;
                dataR[frame] = 1.0;
            }
        }
        player->sample_count++;
    }

    player->phase = phase;
    return noErr;
}

/* AUDIO ENGINE */
// based on Matthijs Hollemans Learning Core Audio example
// https://gist.github.com/hollance/91d9da0d07a869ef9f56466aa46a6466
bool audio_init(AudioUnit *unit, struct Player *player) {
    AudioStreamBasicDescription streamFormat = {0};
    streamFormat.mSampleRate                 = SAMPLE_RATE;
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

    AURenderCallbackStruct input = {.inputProc = render_callback, .inputProcRefCon = player};

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
