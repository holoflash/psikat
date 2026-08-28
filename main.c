// based on Matthijs Hollemans Learning Core Audio example
// https://gist.github.com/hollance/91d9da0d07a869ef9f56466aa46a6466

#include <AudioToolbox/AudioToolbox.h>

typedef struct
{
    double frequency;
    double duration;
} Note;

typedef struct
{
    AudioUnit output_unit;
    double sample_rate;
    double inverse_sample_rate;
    double phase;
    double frequency;
    double sample_count;
    double bpm;
    Note *melody;
    size_t current_note_index;
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

    for (UInt32 frame = 0; frame < inNumberFrames; ++frame)
    {
        // "sequencer"
        Note current_note = player->melody[player->current_note_index];
        double note_duration_in_samples = (60 / player->bpm) * (4.0 / current_note.duration) * player->sample_rate;

        if (player->sample_count >= note_duration_in_samples)
        {
            player->sample_count = 0;
            player->current_note_index = (player->current_note_index + 1) % player->total_notes;
            player->frequency = player->melody[player->current_note_index].frequency;
        }

        // "Wave generator"
        double phase_increment = player->inverse_sample_rate * player->frequency;
        phase += phase_increment;

        if (phase >= 2.0 * M_PI)
        {
            phase -= 2.0 * M_PI;
        }

        /* Sine wave:   dataL[frame] = sin(phase)
                dataR[frame] = sin(phase)
                                       */

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

int main(void)
{
    Note melody[] = {
        {110.0, 16},
        {220.0, 16},
        {440.0, 16},
        {880.0, 16},
        {1040.0, 24},
        {880.0, 24},
        {440.0, 24},
        {220.0, 32},
        {128.33, 32},
    };

    Player player = {0};
    player.sample_rate = 44100.0;
    player.bpm = 120.0;
    player.inverse_sample_rate = (2.0 * M_PI) / player.sample_rate;
    player.melody = melody;
    player.frequency = melody[0].frequency;
    player.total_notes = sizeof(melody) / sizeof(melody[0]);

    init_audio_unit(&player);
    start_audio_unit(&player);

    getchar();
    stop_audio_unit(&player);
    destroy_audio_unit(&player);
}
