#include "audio_engine.h"

static OSStatus render_audio_unit_callback(void                              *inRefCon,
                                           AudioUnitRenderActionFlags UNUSED *ioActionFlags,
                                           const AudioTimeStamp UNUSED       *inTimeStamp,
                                           UInt32 UNUSED                      inBusNumber,
                                           UInt32                             inNumberFrames,
                                           AudioBufferList                   *ioData) {
    Player *p     = (Player *)inRefCon;
    double  phase = p->phase;
    float  *dataL = (float *)ioData->mBuffers[0].mData;
    float  *dataR = (float *)ioData->mBuffers[1].mData;

    // "sequencer"
    for (UInt32 frame = 0; frame < inNumberFrames; ++frame) {
        Note curr_note = p->arrangement->pattern[p->curr_note_index];

        if (p->sample_count >= curr_note.duration_in_samples) {
            p->sample_count    = 0;
            p->curr_note_index = (p->curr_note_index + 1) % p->arrangement->pattern_len;
        }

        // "Wave generator"
        phase += curr_note.phase_increment;
        if (phase >= 2.0 * M_PI) {
            phase -= 2.0 * M_PI;
        }

        if (SINE == curr_note.instrument) {
            dataL[frame] = sin(phase);
            dataR[frame] = sin(phase);
        }
        if (SQUARE == curr_note.instrument) {
            // Square wave: flip halway through the wave cycle
            if (phase >= M_PI) {
                dataL[frame] = -1.0;
                dataR[frame] = -1.0;
            } else {
                dataL[frame] = 1.0;
                dataR[frame] = 1.0;
            }
        }
        p->sample_count++;
    }

    p->phase = phase;
    return noErr;
}

/* AUDIO UNIT */
// based on Matthijs Hollemans Learning Core Audio example
// https://gist.github.com/hollance/91d9da0d07a869ef9f56466aa46a6466
static void init_audio_unit_unit(Player *p) {
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
        exit(1);
    }

    if (noErr != AudioComponentInstanceNew(component, &p->output_unit)) {
        fprintf(stderr, "Couldn't instantiate AudioUnit instance\n");
        exit(1);
    }

    AURenderCallbackStruct input = {.inputProc = render_audio_unit_callback, .inputProcRefCon = p};

    if (noErr !=
        AudioUnitSetProperty(
            p->output_unit, kAudioUnitProperty_SetRenderCallback, kAudioUnitScope_Input, 0, &input, sizeof(input))) {
        fprintf(stderr, "Couldn't set render callback\n");
        exit(1);
    }

    if (noErr != AudioUnitSetProperty(p->output_unit,
                                      kAudioUnitProperty_StreamFormat,
                                      kAudioUnitScope_Input,
                                      0,
                                      &streamFormat,
                                      sizeof(streamFormat))) {
        fprintf(stderr, "Couldn't set stream format\n");
        exit(1);
    }

    if (noErr != AudioUnitInitialize(p->output_unit)) {
        fprintf(stderr, "Couldn't initialize AudioUnit\n");
        exit(1);
    }
}

void audio_unit_start(Player *p) {
    if (noErr != AudioOutputUnitStart(p->output_unit)) {
        fprintf(stderr, "Couldn't start AudioUnit\n");
    }
}

void audio_unit_pause(Player *p) {
    p->sample_count = 0;
    if (noErr != AudioOutputUnitStop(p->output_unit)) {
        fprintf(stderr, "Couldn't stop AudioUnit\n");
    }
}

void audio_unit_stop(Player *p) {
    p->curr_note_index = 0;
    p->sample_count    = 0;
    if (noErr != AudioOutputUnitStop(p->output_unit)) {
        fprintf(stderr, "Couldn't stop AudioUnit\n");
    }
}

void audio_unit_destroy(Player *p) {
    if (noErr != AudioUnitUninitialize(p->output_unit)) {
        fprintf(stderr, "Couldn't uninitialize AudioUnit\n");
    }
    if (noErr != AudioComponentInstanceDispose(p->output_unit)) {
        fprintf(stderr, "Couldn't dispose AudioUnit\n");
    }
}

static Player p;

Player *audio_init(Arrangement *arrangement) {
    p.arrangement      = arrangement;
    p.playback_paused  = false;
    p.playback_stopped = true;

    init_audio_unit_unit(&p);
    return &p;
}
