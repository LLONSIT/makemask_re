#include <stdio.h>
#include <stdlib.h>


unsigned int A[0x40002];

#define SEEK_SET 0

unsigned int code1;
unsigned int code2;

#define HEADER_SIZE (0x40)
#define IPL3_OFFSET HEADER_SIZE
#define IPL3_SIZE (0x1000 - 0x40)
#define MAKEROM_SIZE (HEADER_SIZE + IPL3_SIZE)
#define CHECKSUMMED_SIZE 0x100000

#define BUFF_SIZE (HEADER_SIZE + IPL3_SIZE + CHECKSUMMED_SIZE + 8)
// 0x40402
#define BUFF_COUNT (BUFF_SIZE / sizeof(unsigned int))


void calc3(const unsigned int arg0) {
    unsigned int sp2C;
    unsigned int sp28;
    unsigned int sp24;
    unsigned int sp20;
    unsigned int sp1C;
    unsigned int sp18;
    unsigned int sp14;
    unsigned int sp10;
    unsigned int spC;
    unsigned int sp8;
    unsigned int sp4;

    sp4 = sp8 = spC = sp10 = sp14 = sp18 = (arg0 * 0x5D588B65) + 1;
    for (sp24 = 0; sp24 < 0x40000; sp24++) {
        sp1C = sp2C;
        sp2C = A[sp24];
        sp28 = sp18 + sp2C;
        if (sp28 < sp18) {
            sp14++;
        }
        sp18 = sp28;
        sp10 = sp10 ^ sp2C;
        sp20 = sp2C & 0x1F;
        sp28 = (sp2C << sp20) | (sp2C >> -sp20);
        spC += sp28;
        sp8 = (sp8 < sp2C) ? sp18 ^ sp2C ^ sp8 : sp8 ^ sp28;
        sp4 = sp4 + (sp2C ^ spC);
    }
    
    sp18 = sp18 ^ sp14 ^ sp10;
    spC = spC ^ sp8 ^ sp4;
    
    code1 = sp18;
    code2 = spC;
}



int main(int argc, char** argv) {
    // FILE* sp101044;
    // FILE* sp101040;
    // int sp10103C;
    // int pad;

    // int sp30[BUFF_COUNT];
    // char sp2F;
    // int sp28;
    // int sp24;
    FILE* out; // output file
    FILE* ipl3_file; // file from which to copy IPL3
    int chksum_seed;   // Checksum seed
    int pad;        // Either this or the buffer is 1 word bigger, although seems unlikely given the fread
    int buf[BUFF_COUNT]; // buffer
    char ch; // multipurpose single-byte temp
    int i;
    int j;

    printf("makemask ver.2.02\n");
    
    if (argc < 2) {
        fprintf(stderr,"Usage: makemask [ROM_file]\n");
        return -1;
    }
    
    if ((out = fopen(argv[1],"r")) == 0) {
        fprintf(stderr,"Ouch!! The rom file doesn't exist.\n");
        return -1;
    }
    if (fread(buf, sizeof(unsigned int), BUFF_COUNT, out) != BUFF_COUNT) {
        fprintf(stderr, "Ouch!! The rom file is too small.\n");
        fprintf(stderr, "Rom size must be bigger than 9Mbits.\n");
        fprintf(stderr, "You can make a big ROM by makerom.\n");
        fprintf(stderr, "Please use \"man makerom.\"\n");
        return -1;
    }
    
    if ((ipl3_file = fopen("/usr/sbin/makemask", "r")) == 0) {
        fprintf(stderr, "Ouch!! \"/usr/sbin/makemask\" doesn't exist.\n");
        return -1;
    }
    
    fclose(out);

    // 0x40002
    for(i = 0; i < (BUFF_SIZE - MAKEROM_SIZE) / (int)sizeof(unsigned int); i++ )  {
        A[i] = buf[MAKEROM_SIZE / sizeof(unsigned int) + i];
    }

    // Calculate checksum
    chksum_seed = 0x3F;
    calc3(chksum_seed); //BOOTCODE

    // copy checksum byte by byte
    out = fopen(argv[1], "rb+");
    fseek(out, 0x10, SEEK_SET);
    for(i = 3 ; i >= 0 ; i--) {
        ch = (code1 >> (i * 8)) & 0xFF;
        fputc(ch, out);
    }
    for(i = 3 ; i >= 0 ; i--) {
        ch = (code2 >> (i * 8)) & 0xFF;
        fputc(ch, out);
    }

    // copy IPL3
    fseek(out, IPL3_OFFSET, SEEK_SET);
    // Copies from a known offset into this file? Scary
    fseek(ipl3_file, 0x4624, SEEK_SET);
    for(j = IPL3_OFFSET; j < MAKEROM_SIZE; j++ ) {
        ch = fgetc(ipl3_file);
        fputc(ch, out);
    }

    fclose(out);
    fclose(ipl3_file);
    return 0;
}
