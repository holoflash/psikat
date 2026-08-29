// based on Matthijs Hollemans Learning Core Audio example
// https://gist.github.com/hollance/91d9da0d07a869ef9f56466aa46a6466

#include <AudioToolbox/AudioToolbox.h>

#define SINE 0
#define SQUARE 1

typedef struct
{
    double phase_increment;
    double duration_in_samples;
    int instrument;
} Note;

typedef struct
{
    AudioUnit output_unit;
    double sample_rate;
    double phase;
    double sample_count;
    double bpm;
    Note *melody;
    size_t curr_note_index;
    size_t total_notes;
} Player;

OSStatus render_audio(
    void *inRefCon,
    AudioUnitRenderActionFlags __attribute__((unused)) * ioActionFlags,
    const AudioTimeStamp __attribute__((unused)) * inTimeStamp,
    UInt32 __attribute__((unused)) inBusNumber,
    UInt32 inNumberFrames,
    AudioBufferList *ioData)
{
    Player *player = (Player *)inRefCon;
    double phase = player->phase;

    float *dataL = (float *)ioData->mBuffers[0].mData;
    float *dataR = (float *)ioData->mBuffers[1].mData;

    // "sequencer"
    for (UInt32 frame = 0; frame < inNumberFrames; ++frame)
    {
        if (player->sample_count >= player->melody[player->curr_note_index].duration_in_samples)
        {
            player->sample_count = 0;
            player->curr_note_index = (player->curr_note_index + 1) % player->total_notes;
        }

        // "Wave generator"
        phase += player->melody[player->curr_note_index].phase_increment;
        if (phase >= 2.0 * M_PI)
        {
            phase -= 2.0 * M_PI;
        }

        if (SINE == player->melody[player->curr_note_index].instrument)
        {

            dataL[frame] = sin(phase);
            dataR[frame] = sin(phase);
        }
        if (SQUARE == player->melody[player->curr_note_index].instrument)
        {

            // Square wave: flip halway through the wave cycle
            if (phase >= M_PI)
            {
                dataL[frame] = -1;
                dataR[frame] = -1;
            }
            else
            {
                dataL[frame] = 1;
                dataR[frame] = 1;
            }
        }
        player->sample_count++;
    }

    player->phase = phase;
    return noErr;
}

/* AUDIO UNIT */
void start_audio_unit(Player *player)
{
    if (noErr != AudioOutputUnitStart(player->output_unit))
    {
        fprintf(stderr, "Couldn't start AudioUnit\n");
        exit(1);
    }
}

void stop_audio_unit(Player *player)
{
    if (noErr != AudioOutputUnitStop(player->output_unit))
    {
        fprintf(stderr, "Couldn't stop AudioUnit\n");
        exit(1);
    }
}
void destroy_audio_unit(Player *player)
{
    if (noErr != AudioUnitUninitialize(player->output_unit))
    {
        fprintf(stderr, "Couldn't uninitialize AudioUnit\n");
        exit(1);
    }
    if (noErr != AudioComponentInstanceDispose(player->output_unit))
    {
        fprintf(stderr, "Couldn't dispose AudioUnit\n");
        exit(1);
    }
}

void init_audio_unit(Player *player)
{
    AudioStreamBasicDescription streamFormat = {0};
    streamFormat.mSampleRate = 44100.0;
    streamFormat.mFormatID = kAudioFormatLinearPCM;
    streamFormat.mFormatFlags = kAudioFormatFlagsNativeFloatPacked | kAudioFormatFlagIsNonInterleaved;
    streamFormat.mChannelsPerFrame = 2;
    streamFormat.mBitsPerChannel = 8 * sizeof(float);
    streamFormat.mBytesPerFrame = sizeof(float);
    streamFormat.mFramesPerPacket = 1;
    streamFormat.mBytesPerPacket = streamFormat.mBytesPerFrame * streamFormat.mFramesPerPacket;

    AudioComponentDescription description = {
        .componentType = kAudioUnitType_Output,
        .componentSubType = kAudioUnitSubType_DefaultOutput,
        .componentManufacturer = kAudioUnitManufacturer_Apple,
        .componentFlags = 0,
        .componentFlagsMask = 0};

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

    AURenderCallbackStruct input = {
        .inputProc = render_audio,
        .inputProcRefCon = player};

    if (noErr != AudioUnitSetProperty(player->output_unit,
                                      kAudioUnitProperty_SetRenderCallback,
                                      kAudioUnitScope_Input,
                                      0,
                                      &input,
                                      sizeof(input)))
    {
        fprintf(stderr, "Couldn't set render callback\n");
        exit(1);
    }

    if (noErr != AudioUnitSetProperty(player->output_unit,
                                      kAudioUnitProperty_StreamFormat,
                                      kAudioUnitScope_Input,
                                      0,
                                      &streamFormat,
                                      sizeof(streamFormat)))
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

static double BPM = 120.0;
static double SAMPLE_RATE = 44100.0;

double division_to_samples(int division)
{
    return (60 / BPM) * SAMPLE_RATE * (4.0 / division);
}

double freq_to_phase_increment(double frequency)
{
    return (2.0 * M_PI) / 44100.0 * frequency;
}

int main(void)
{
    Note melody[] = {
        {freq_to_phase_increment(110.0), division_to_samples(16), SQUARE},
        {freq_to_phase_increment(220.0), division_to_samples(16), SQUARE},
        {freq_to_phase_increment(440.0), division_to_samples(16), SQUARE},
        {freq_to_phase_increment(880.0), division_to_samples(16), SINE},
        {freq_to_phase_increment(440.0), division_to_samples(16), SINE},
        {freq_to_phase_increment(220.0), division_to_samples(16), SINE},
    };

    Player player = {0};
    player.sample_rate = SAMPLE_RATE;
    player.bpm = BPM;
    player.melody = melody;
    player.total_notes = sizeof(melody) / sizeof(melody[0]);

    init_audio_unit(&player);
    start_audio_unit(&player);

    getchar();
    stop_audio_unit(&player);
    destroy_audio_unit(&player);
}
