#include <stdint.h>

#define SAMPLE_MAX      32767
#define HEADER_SIZE     36
#define HEADER_FMT_SIZE 16
#define FORMAT_TAG      1 // (1): PCM;(3): IEEE float audio.
#define BITS_PER_SAMPLE 8
#define DURATION        5
#define SR              44100
#define NCHANNELS       2
#define FMT_STRING_SIZE 4
#define NSAMPLES        (NCHANNELS * DURATION * SR)
#define A4              440

// TODO: should I use stdint values in other parts of the program instead of just int?
typedef int8_t  fourcc[4];
typedef int16_t sample_t;

typedef struct RiffHeader {
    fourcc   id;
    uint32_t size;
    fourcc   type;
} RiffHeader;

typedef struct FormatChunk {
    fourcc   id;
    uint32_t size;
    uint16_t format_tag;
    uint16_t channels;
    uint32_t samples_per_sec;
    uint32_t bytes_per_sec;
    uint16_t block_align;
    uint16_t bits_per_sample;
} FormatChunk;

typedef struct DataHeader {
    fourcc   id;
    uint32_t size;
} DataHeader;

typedef struct WavHeader {
    struct RiffHeader  riff;
    struct FormatChunk format;
    struct DataHeader  data;
} WavHeader;

int  wav_hello_world(void);
int  wav_init(void);
void wav_finish(void);
