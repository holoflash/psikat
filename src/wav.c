#include "wav.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

static FILE    *file_pointer;
static sample_t buffer[NSAMPLES];

// Thanks to the writer of https://mu.krj.st/wave/ !!!
int wav_init(void) {
    struct WavHeader wav_header = {0};
    file_pointer                = fopen("output.wav", "wb");
    if (!file_pointer)
        return 0;

    /* RIFF header */
    memcpy(&wav_header.riff.id, "RIFF", FMT_STRING_SIZE);
    wav_header.riff.size = HEADER_SIZE + NSAMPLES * sizeof(sample_t);
    memcpy(&wav_header.riff.type, "WAVE", FMT_STRING_SIZE);

    /* format chunk */
    memcpy(&wav_header.format.id, "fmt ", FMT_STRING_SIZE);
    wav_header.format.size            = HEADER_FMT_SIZE;
    wav_header.format.format_tag      = FORMAT_TAG;
    wav_header.format.channels        = NCHANNELS;
    wav_header.format.samples_per_sec = SR;
    wav_header.format.bytes_per_sec   = NCHANNELS * SR * sizeof(sample_t);
    wav_header.format.block_align     = NCHANNELS * sizeof(sample_t);
    wav_header.format.bits_per_sample = BITS_PER_SAMPLE * sizeof(sample_t);

    /* DATA header */
    memcpy(&wav_header.data.id, "data", FMT_STRING_SIZE);
    wav_header.data.size = NSAMPLES * sizeof(sample_t);

    if (fwrite(&wav_header, sizeof(struct WavHeader), 1, file_pointer) != 1) {
        fclose(file_pointer);
        return 0;
    }
    return 1;
}

void wav_finish(void) {
    fwrite(buffer, sizeof(buffer), 1, file_pointer);
    /* 1 byte padding if buffer size is odd */
    if (sizeof(buffer) % 2 == 1) {
        char nil = 0;
        fwrite(&nil, 1, 1, file_pointer);
    }
    fclose(file_pointer);
}

int wav_hello_world(void) {
    size_t i;
    if (!wav_init())
        return 1;

    for (i = 0; i < NSAMPLES; ++i)
        buffer[i] = lrint(SAMPLE_MAX * sin(2 * M_PI * A4 * i / SR));

    wav_finish();
    return 0;
}
