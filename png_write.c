#include <stdio.h>
#include <stdlib.h>

unsigned long crc_table[256] = {
    0,          1996959894, 3993919788, 2567524794, 124634137,  1886057615, 3915621685, 2657392035,
    249268274,  2044508324, 3772115230, 2547177864, 162941995,  2125561021, 3887607047, 2428444049,
    498536548,  1789927666, 4089016648, 2227061214, 450548861,  1843258603, 4107580753, 2211677639,
    325883990,  1684777152, 4251122042, 2321926636, 335633487,  1661365465, 4195302755, 2366115317,
    997073096,  1281953886, 3579855332, 2724688242, 1006888145, 1258607687, 3524101629, 2768942443,
    901097722,  1119000684, 3686517206, 2898065728, 853044451,  1172266101, 3705015759, 2882616665,
    651767980,  1373503546, 3369554304, 3218104598, 565507253,  1454621731, 3485111705, 3099436303,
    671266974,  1594198024, 3322730930, 2970347812, 795835527,  1483230225, 3244367275, 3060149565,
    1994146192, 31158534,   2563907772, 4023717930, 1907459465, 112637215,  2680153253, 3904427059,
    2013776290, 251722036,  2517215374, 3775830040, 2137656763, 141376813,  2439277719, 3865271297,
    1802195444, 476864866,  2238001368, 4066508878, 1812370925, 453092731,  2181625025, 4111451223,
    1706088902, 314042704,  2344532202, 4240017532, 1658658271, 366619977,  2362670323, 4224994405,
    1303535960, 984961486,  2747007092, 3569037538, 1256170817, 1037604311, 2765210733, 3554079995,
    1131014506, 879679996,  2909243462, 3663771856, 1141124467, 855842277,  2852801631, 3708648649,
    1342533948, 654459306,  3188396048, 3373015174, 1466479909, 544179635,  3110523913, 3462522015,
    1591671054, 702138776,  2966460450, 3352799412, 1504918807, 783551873,  3082640443, 3233442989,
    3988292384, 2596254646, 62317068,   1957810842, 3939845945, 2647816111, 81470997,   1943803523,
    3814918930, 2489596804, 225274430,  2053790376, 3826175755, 2466906013, 167816743,  2097651377,
    4027552580, 2265490386, 503444072,  1762050814, 4150417245, 2154129355, 426522225,  1852507879,
    4275313526, 2312317920, 282753626,  1742555852, 4189708143, 2394877945, 397917763,  1622183637,
    3604390888, 2714866558, 953729732,  1340076626, 3518719985, 2797360999, 1068828381, 1219638859,
    3624741850, 2936675148, 906185462,  1090812512, 3747672003, 2825379669, 829329135,  1181335161,
    3412177804, 3160834842, 628085408,  1382605366, 3423369109, 3138078467, 570562233,  1426400815,
    3317316542, 2998733608, 733239954,  1555261956, 3268935591, 3050360625, 752459403,  1541320221,
    2607071920, 3965973030, 1969922972, 40735498,   2617837225, 3943577151, 1913087877, 83908371,
    2512341634, 3803740692, 2075208622, 213261112,  2463272603, 3855990285, 2094854071, 198958881,
    2262029012, 4057260610, 1759359992, 534414190,  2176718541, 4139329115, 1873836001, 414664567,
    2282248934, 4279200368, 1711684554, 285281116,  2405801727, 4167216745, 1634467795, 376229701,
    2685067896, 3608007406, 1308918612, 956543938,  2808555105, 3495958263, 1231636301, 1047427035,
    2932959818, 3654703836, 1088359270, 936918000,  2847714899, 3736837829, 1202900863, 817233897,
    3183342108, 3401237130, 1404277552, 615818150,  3134207493, 3453421203, 1423857449, 601450431,
    3009837614, 3294710456, 1567103746, 711928724,  3020668471, 3272380065, 1510334235, 755167117,
};

// https://valeriavg.dev/crc-32-checksum-in-wasm-and-raw-js-tutorial-and-benchmark
unsigned int crc32(const unsigned char *buf, size_t length) {
    unsigned int c = 0xffffffff;
    for (size_t i = 0; i < length; i++) {
        c = crc_table[(c ^ buf[i]) & 0xFF] ^ (c >> 8);
    }
    return c ^ 0xffffffff;
}

unsigned int adler32(const unsigned char *data, size_t len) {
    unsigned int s1 = 1;
    unsigned int s2 = 0;
    for (size_t i = 0; i < len; i++) {
        s1 = (s1 + data[i]) % 65521;
        s2 = (s2 + s1) % 65521;
    }
    return (s2 << 16) | s1;
}

#define PNG_SIGNATURE 0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A

#define IHDR               0x49, 0x48, 0x44, 0x52
#define IHDR_LENGTH        0x00, 0x00, 0x00, 0x0D
#define WIDTH              0x00, 0x00, 0x00, 0x04
#define HEIGHT             0x00, 0x00, 0x00, 0x04
#define BIT_DEPTH          0x08
#define COLOR_TYPE         0x02
#define COMPRESSION_METHOD 0x00
#define FILTER_METHOD      0x00
#define INTERLACE_METHOD   0x00

#define IEND_LENGTH 0x00, 0x00, 0x00, 0x00
#define IEND        0x49, 0x45, 0x4E, 0x44

// Image data
#define RED_BLACK 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00
#define BLACK_RED 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00

int main(void) {
    FILE         *write_ptr = fopen("test.png", "wb");
    unsigned char sig[]     = {PNG_SIGNATURE};
    fwrite(sig, 1, 8, write_ptr);

    // IHDR
    unsigned char ihdr_chunk[] = {
        IHDR,
        WIDTH,
        HEIGHT,
        BIT_DEPTH,
        COLOR_TYPE,
        COMPRESSION_METHOD,
        FILTER_METHOD,
        INTERLACE_METHOD,
    };

    unsigned int  ihdr_crc   = crc32(ihdr_chunk, sizeof(ihdr_chunk));
    unsigned char ihdr_len[] = {IHDR_LENGTH};
    fwrite(ihdr_len, 1, 4, write_ptr);
    fwrite(ihdr_chunk, 1, sizeof(ihdr_chunk), write_ptr);

    unsigned char chunk_crc[4];
    chunk_crc[0] = (ihdr_crc >> 24) & 0xFF;
    chunk_crc[1] = (ihdr_crc >> 16) & 0xFF;
    chunk_crc[2] = (ihdr_crc >> 8) & 0xFF;
    chunk_crc[3] = ihdr_crc & 0xFF;
    fwrite(chunk_crc, 1, 4, write_ptr);

    // IDAT
    unsigned char pixels[] = {RED_BLACK, BLACK_RED, RED_BLACK, BLACK_RED};
    size_t        raw_len  = sizeof(pixels);

    // -- ZLIB
    size_t         idat_data_len = 2 + 1 + 2 + 2 + raw_len + 4;
    unsigned char *idat_data     = malloc(idat_data_len);

    unsigned char idat_header[8];
    idat_header[0] = (idat_data_len >> 24) & 0xFF;
    idat_header[1] = (idat_data_len >> 16) & 0xFF;
    idat_header[2] = (idat_data_len >> 8) & 0xFF;
    idat_header[3] = idat_data_len & 0xFF;
    idat_header[4] = 0x49;
    idat_header[5] = 0x44;
    idat_header[6] = 0x41;
    idat_header[7] = 0x54;

    // -- ZLIB HEADER
    idat_data[0] = 0x08;
    idat_data[1] = 0x1D;

    // -- DEFLATE FLAG
    idat_data[2] = 0x01;

    // -- LEN & NLEN
    idat_data[3] = raw_len & 0xFF;
    idat_data[4] = (raw_len >> 8) & 0xFF;
    idat_data[5] = (~raw_len) & 0xFF;
    idat_data[6] = ((~raw_len) >> 8) & 0xFF;

    for (size_t i = 0; i < raw_len; i++) {
        idat_data[7 + i] = pixels[i];
    }

    unsigned int adler      = adler32(pixels, raw_len);
    idat_data[7 + raw_len]  = (adler >> 24) & 0xFF;
    idat_data[8 + raw_len]  = (adler >> 16) & 0xFF;
    idat_data[9 + raw_len]  = (adler >> 8) & 0xFF;
    idat_data[10 + raw_len] = adler & 0xFF;

    unsigned char *idat_crc_buf = malloc(4 + idat_data_len);
    idat_crc_buf[0]             = 0x49;
    idat_crc_buf[1]             = 0x44;
    idat_crc_buf[2]             = 0x41;
    idat_crc_buf[3]             = 0x54;

    for (size_t i = 0; i < idat_data_len; i++) {
        idat_crc_buf[4 + i] = idat_data[i];
    }

    unsigned int idat_crc = crc32(idat_crc_buf, 4 + idat_data_len);
    fwrite(idat_header, 1, 8, write_ptr);
    fwrite(idat_data, 1, idat_data_len, write_ptr);
    chunk_crc[0] = (idat_crc >> 24) & 0xFF;
    chunk_crc[1] = (idat_crc >> 16) & 0xFF;
    chunk_crc[2] = (idat_crc >> 8) & 0xFF;
    chunk_crc[3] = idat_crc & 0xFF;
    fwrite(chunk_crc, 1, 4, write_ptr);

    // IEND
    unsigned char iend_chunk[] = {IEND};
    unsigned int  iend_crc     = crc32(iend_chunk, sizeof(iend_chunk));
    unsigned char iend_len[]   = {IEND_LENGTH};

    fwrite(iend_len, 1, 4, write_ptr);
    fwrite(iend_chunk, 1, sizeof(iend_chunk), write_ptr);
    chunk_crc[0] = (iend_crc >> 24) & 0xFF;
    chunk_crc[1] = (iend_crc >> 16) & 0xFF;
    chunk_crc[2] = (iend_crc >> 8) & 0xFF;
    chunk_crc[3] = iend_crc & 0xFF;
    fwrite(chunk_crc, 1, 4, write_ptr);

    fclose(write_ptr);
    free(idat_data);
    free(idat_crc_buf);
    return 0;
}
