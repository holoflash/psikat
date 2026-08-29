// based on Matthijs Hollemans Learning Core Audio example
// https://gist.github.com/hollance/91d9da0d07a869ef9f56466aa46a6466

#include <AudioToolbox/AudioToolbox.h>

#define UNUSED __attribute__((unused))

static double UNUSED NOTE_FREQUENCY[128] = {
    8.18,    8.66,    9.18,    9.72,    10.3,     10.91,   11.56,    12.25,    12.98,   13.75,  14.57,   15.44,
    16.35,   17.32,   18.35,   19.45,   20.6,     21.83,   23.12,    24.5,     25.96,   27.5,   29.14,   30.87,
    32.7,    34.65,   36.71,   38.89,   41.2,     43.65,   46.25,    49.0,     51.91,   55.0,   58.27,   61.74,
    65.41,   69.3,    73.42,   77.78,   82.41,    87.31,   92.5,     98.0,     103.83,  110.0,  116.54,  123.47,
    130.81,  138.59,  146.83,  155.56,  164.81,   174.61,  185.0,    196.0,    207.65,  220.0,  233.08,  246.94,
    261.63,  277.18,  293.66,  311.13,  329.63,   349.23,  369.99,   392.0,    415.3,   440.0,  466.16,  493.88,
    523.25,  554.37,  587.33,  622.25,  659.25,   698.46,  739.99,   783.99,   830.61,  880.0,  932.33,  987.77,
    1046.5,  1108.73, 1174.66, 1244.51, 1318.51,  1396.91, 1479.98,  1567.98,  1661.22, 1760.0, 1864.66, 1975.53,
    2093.0,  2217.46, 2349.32, 2489.02, 2637.02,  2793.83, 2959.96,  3135.96,  3322.44, 3520.0, 3729.31, 3951.07,
    4186.01, 4434.92, 4698.64, 4978.03, 5274.04,  5587.65, 5919.91,  6271.93,  6644.88, 7040.0, 7458.62, 7902.13,
    8372.02, 8869.84, 9397.27, 9956.06, 10548.08, 11175.3, 11839.82, 12543.85,
};
static char UNUSED NOTE_NAME[128][128] = {
    "C--", "C#-", "D--", "D#-", "E--", "F--", "F#-", "G--", "G#-", "A--", "A#-", "B--", "C-0", "C#0", "D-0", "D#0",
    "E-0", "F-0", "F#0", "G-0", "G#0", "A-0", "A#0", "B-0", "C-1", "C#1", "D-1", "D#1", "E-1", "F-1", "F#1", "G-1",
    "G#1", "A-1", "A#1", "B-1", "C-2", "C#2", "D-2", "D#2", "E-2", "F-2", "F#2", "G-2", "G#2", "A-2", "A#2", "B-2",
    "C-3", "C#3", "D-3", "D#3", "E-3", "F-3", "F#3", "G-3", "G#3", "A-3", "A#3", "B-3", "C-4", "C#4", "D-4", "D#4",
    "E-4", "F-4", "F#4", "G-4", "G#4", "A-4", "A#4", "B-4", "C-5", "C#5", "D-5", "D#5", "E-5", "F-5", "F#5", "G-5",
    "G#5", "A-5", "A#5", "B-5", "C-6", "C#6", "D-6", "D#6", "E-6", "F-6", "F#6", "G-6", "G#6", "A-6", "A#6", "B-6",
    "C-7", "C#7", "D-7", "D#7", "E-7", "F-7", "F#7", "G-7", "G#7", "A-7", "A#7", "B-7", "C-8", "C#8", "D-8", "D#8",
    "E-8", "F-8", "F#8", "G-8", "G#8", "A-8", "A#8", "B-8", "C-9", "C#9", "D-9", "D#9", "E-9", "F-9", "F#9", "G-9",
};

#define SINE 0
#define SQUARE 1

typedef struct
{
    double phase_increment;
    double duration_in_samples;
    int    instrument;
} Note;

typedef struct
{
    AudioUnit output_unit;
    double    sample_rate;
    double    phase;
    double    sample_count;
    double    bpm;
    Note     *melody;
    size_t    curr_note_index;
    size_t    total_notes;
} Player;

OSStatus render_audio(void *inRefCon, AudioUnitRenderActionFlags UNUSED *ioActionFlags,
                      const AudioTimeStamp UNUSED *inTimeStamp, UInt32 UNUSED inBusNumber, UInt32 inNumberFrames,
                      AudioBufferList *ioData)
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
    streamFormat.mSampleRate                 = 44100.0;
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

    AURenderCallbackStruct input = {.inputProc = render_audio, .inputProcRefCon = player};

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

static double BPM         = 120.0;
static double SAMPLE_RATE = 44100.0;

double division_to_samples(double division)
{
    return (60 / BPM) * SAMPLE_RATE * (4.0 / division);
}

double freq_to_phase_increment(double frequency)
{
    return (2.0 * M_PI) / SAMPLE_RATE * frequency;
}

int main(void)
{
    Note melody[] = {
        {freq_to_phase_increment(110.0), division_to_samples(16.0), SQUARE},
        {freq_to_phase_increment(220.0), division_to_samples(16.0), SQUARE},
        {freq_to_phase_increment(440.0), division_to_samples(16.0), SQUARE},
        {freq_to_phase_increment(880.0), division_to_samples(16.0), SINE},
        {freq_to_phase_increment(440.0), division_to_samples(16.0), SINE},
        {freq_to_phase_increment(220.0), division_to_samples(16.0), SINE},
    };

    Player player      = {0};
    player.sample_rate = SAMPLE_RATE;
    player.bpm         = BPM;
    player.melody      = melody;
    player.total_notes = sizeof(melody) / sizeof(melody[0]);

    init_audio_unit(&player);
    start_audio_unit(&player);

    getchar();
    stop_audio_unit(&player);
    destroy_audio_unit(&player);
}
