#include <stdio.h>
#include <stdlib.h>
#include "include/structs.h"

typedef unsigned int u32;
typedef signed int s32;
typedef unsigned char u8;

//TODO: Document this Function
//thanks fluffy! (decomp.me anon)
void calc3(u32 arg0) {
    
     u32 A[4];
    u32 code1;
    u32 code2;
    
    u32 sp2C;
    u32 sp28;
    u32 sp24;
    s32 sp20;
    u32 sp1C;
    u32 sp18;
    u32 sp14;
    u32 sp10;
    u32 spC;
    u32 sp8;
    u32 sp4;

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
    
    u32 A[4];
    u32 code1;
    u32 code2;

    FILE* sp101044;
    FILE* sp101040;
    int sp10103C;
    int sp30[0x40403];
    u8 sp2F;
    s32 sp28;
    s32 sp24;
    // s32 temp_t6_2;
    // s32 temp_t8;
    // s32 temp_t8_2;
    // s32 temp_t9;
    // u8 temp_t5;
    // u8 temp_t6;
    // u8 sp30[4]; //
    
    // sp100000.unk1048 = arg0;
    // sp100000.unk104C = arg1;
    
    printf("makemask ver.2.02\n");
    
    if (argc < 2) {
        fprintf(stderr,"Usage: makemask [ROM_file]\n");
        return -1;
    }
    
    if ((sp101044 = fopen(argv[1],"r")) == 0) {
        fprintf(stderr,"Ouch!! The rom file doesn't exist.\n");
        return -1;
    }
    if (fread(&sp30[0], 4, 0x40402, sp101044) != 0x40402) {
        fprintf(stderr, "Ouch!! The rom file is too small.\n");
        fprintf(stderr, "Rom size must be bigger than 9Mbits.\n");
        fprintf(stderr, "You can make a big ROM by makerom.\n");
        fprintf(stderr, "Please use \"man makerom.\"\n");
        return -1;
    }
    
    if ((sp101040 = fopen("/usr/sbin/makemask", "r")) == 0) {
        fprintf(stderr, "Ouch!! \"/usr/sbin/makemask\" doesn't exist.\n");
        return -1;
    }
    
    fclose(sp101044);
    
    for(sp28 = 0; sp28 < 0x40002 ; sp28++ )  {
        A[sp28] = sp30[0x400 + sp28];
        
    }
    
    sp10103C = 0x3F;
    calc3(sp10103C); //BOOTCODE
    
    sp101044 = fopen(argv[1], "rb+");
    fseek(sp101044, 0x10, 0);
    
    
    for(sp28 = 3 ; sp28 >= 0 ; sp28--) {
        sp2F = ((u32) code1 >> (sp28 * 8)) & 0xFF;
        fputc(sp2F, sp101044);
        }
   

    for(sp28 = 3 ; sp28 >= 0 ; sp28--) {
        sp2F = ((u32) code2 >> (sp28 * 8)) & 0xFF;
        fputc(sp2F, sp101044);
    
    } 
    
    fseek(sp101044, 0x40, 0);
    fseek(sp101040, 0x4624, 0);
    
    
             /* irregular */
    for(sp24 = 0x40 ; sp24 < 0x1000 ; sp24++ ) {
        sp2F = fgetc(sp101040);
        fputc(sp2F, sp101044);
        }
        

    fclose(sp101044);
    fclose(sp101040);
    return 0;
}
