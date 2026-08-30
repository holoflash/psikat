#include "audio_engine.h"
#include "notes.h"
#include <AudioToolbox/AudioToolbox.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/* MACROS */
#define UNUSED __attribute__((unused))
#define SINE 0
#define SQUARE 1
#define SAMPLE_RATE 44100.0
#define BPM 120.0
#define MAX_LENGTH (256 * 256)

/* STRUCTS */
typedef struct
{
    double phase_increment;
    double duration_in_samples;
    int    instrument;
} Note;

struct Player
{
    AudioUnit output_unit;
    double    sample_rate;
    double    phase;
    double    sample_count;
    double    bpm;
    Note      melody[MAX_LENGTH];
    size_t    curr_note_index;
    size_t    total_notes;
};

/* HELPERS */
static double division_to_samples(double division)
{
    return (60.0 / BPM) * SAMPLE_RATE * (4.0 / division);
}

static double freq_to_phase_increment(double frequency)
{
    return (2.0 * M_PI) / SAMPLE_RATE * frequency;
}

/* SYNTH ENGINE */
static OSStatus render_audio_callback(void *inRefCon, AudioUnitRenderActionFlags UNUSED *ioActionFlags,
                                      const AudioTimeStamp UNUSED *inTimeStamp, UInt32 UNUSED inBusNumber,
                                      UInt32 inNumberFrames, AudioBufferList *ioData)
{
    Player *player = (Player *)inRefCon;
    double  phase  = player->phase;
    float  *dataL  = (float *)ioData->mBuffers[0].mData;
    float  *dataR  = (float *)ioData->mBuffers[1].mData;

    // "sequencer"
    for (UInt32 frame = 0; frame < inNumberFrames; ++frame)
    {
        Note curr_note = player->melody[player->curr_note_index];

        if (player->sample_count >= curr_note.duration_in_samples)
        {
            player->sample_count    = 0;
            player->curr_note_index = (player->curr_note_index + 1) % player->total_notes;
        }

        // "Wave generator"
        phase += curr_note.phase_increment;
        if (phase >= 2.0 * M_PI)
        {
            phase -= 2.0 * M_PI;
        }

        if (SINE == curr_note.instrument)
        {
            dataL[frame] = sin(phase);
            dataR[frame] = sin(phase);
        }
        if (SQUARE == curr_note.instrument)
        {
            // Square wave: flip halway through the wave cycle
            if (phase >= M_PI)
            {
                dataL[frame] = -1.0;
                dataR[frame] = -1.0;
            }
            else
            {
                dataL[frame] = 1.0;
                dataR[frame] = 1.0;
            }
        }
        player->sample_count++;
    }

    player->phase = phase;
    return noErr;
}

/* AUDIO UNIT */
void audio_unit_start(Player *player)
{
    if (noErr != AudioOutputUnitStart(player->output_unit))
    {
        fprintf(stderr, "Couldn't start AudioUnit\n");
    }
}

void audio_unit_stop(Player *player)
{
    if (noErr != AudioOutputUnitStop(player->output_unit))
    {
        fprintf(stderr, "Couldn't stop AudioUnit\n");
    }
}

void audio_unit_destroy(Player *player)
{
    if (noErr != AudioUnitUninitialize(player->output_unit))
    {
        fprintf(stderr, "Couldn't uninitialize AudioUnit\n");
    }
    if (noErr != AudioComponentInstanceDispose(player->output_unit))
    {
        fprintf(stderr, "Couldn't dispose AudioUnit\n");
    }
}

// based on Matthijs Hollemans Learning Core Audio example
// https://gist.github.com/hollance/91d9da0d07a869ef9f56466aa46a6466
static void init_audio_unit(Player *player)
{
    AudioStreamBasicDescription streamFormat = {0};
    streamFormat.mSampleRate                 = player->sample_rate;
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
    if (!component)
    {
        fprintf(stderr, "Couldn't get output AudioUnit\n");
        exit(1);
    }

    if (noErr != AudioComponentInstanceNew(component, &player->output_unit))
    {
        fprintf(stderr, "Couldn't instantiate AudioUnit instance\n");
        exit(1);
    }

    AURenderCallbackStruct input = {.inputProc = render_audio_callback, .inputProcRefCon = player};

    if (noErr != AudioUnitSetProperty(player->output_unit, kAudioUnitProperty_SetRenderCallback, kAudioUnitScope_Input,
                                      0, &input, sizeof(input)))
    {
        fprintf(stderr, "Couldn't set render callback\n");
        exit(1);
    }

    if (noErr != AudioUnitSetProperty(player->output_unit, kAudioUnitProperty_StreamFormat, kAudioUnitScope_Input, 0,
                                      &streamFormat, sizeof(streamFormat)))
    {
        fprintf(stderr, "Couldn't set stream format\n");
        exit(1);
    }

    if (noErr != AudioUnitInitialize(player->output_unit))
    {
        fprintf(stderr, "Couldn't initialize AudioUnit\n");
        exit(1);
    }
}

static Player player;

Player *launch(void)
{
    player = (Player){.sample_rate = SAMPLE_RATE,
                      .bpm         = BPM,
                      .total_notes = player.total_notes = sizeof(player.melody) / sizeof(player.melody[0]),
                      .melody                           = {
                          {freq_to_phase_increment(N_FREQUENCY[60]), division_to_samples(16.0), SQUARE},
                          {freq_to_phase_increment(N_FREQUENCY[62]), division_to_samples(16.0), SQUARE},
                          {freq_to_phase_increment(N_FREQUENCY[63]), division_to_samples(16.0), SQUARE},
                          {freq_to_phase_increment(N_FREQUENCY[65]), division_to_samples(16.0), SINE},
                          {freq_to_phase_increment(N_FREQUENCY[67]), division_to_samples(16.0), SINE},
                          {freq_to_phase_increment(N_FREQUENCY[68]), division_to_samples(16.0), SQUARE},
                      }};

    init_audio_unit(&player);
    return &player;
}
