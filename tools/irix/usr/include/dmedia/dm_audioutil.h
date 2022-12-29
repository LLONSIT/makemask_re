#ifndef __INC_DM_AUDIOUTIL_H__
#define __INC_DM_AUDIOUTIL_H__  

/***************************************************************************
 * SGI Digital Media Library: Audio Utility Routines
 *
 * <dmedia/dm_audioutil.h>
 *    header file for use with /usr/lib/libdmedia.so
 *
 ***************************************************************************
 * 
 * Copyright 1995, Silicon Graphics, Inc.
 * ALL RIGHTS RESERVED
 *
 * UNPUBLISHED -- Rights reserved under the copyright laws of the United
 * States.   Use of a copyright notice is precautionary only and does not
 * imply publication or disclosure.
 *
 * U.S. GOVERNMENT RESTRICTED RIGHTS LEGEND:
 * Use, duplication or disclosure by the Government is subject to restrictions
 * as set forth in FAR 52.227.19(c)(2) or subparagraph (c)(1)(ii) of the Rights
 * in Technical Data and Computer Software clause at DFARS 252.227-7013 and/or
 * in similar or successor clauses in the FAR, or the DOD or NASA FAR
 * Supplement.  Contractor/manufacturer is Silicon Graphics, Inc.,
 * 2011 N. Shoreline Blvd. Mountain View, CA 94039-7311.
 *
 * THE CONTENT OF THIS WORK CONTAINS CONFIDENTIAL AND PROPRIETARY
 * INFORMATION OF SILICON GRAPHICS, INC. ANY DUPLICATION, MODIFICATION,
 * DISTRIBUTION, OR DISCLOSURE IN ANY FORM, IN WHOLE, OR IN PART, IS STRICTLY
 * PROHIBITED WITHOUT THE PRIOR EXPRESS WRITTEN PERMISSION OF SILICON
 * GRAPHICS, INC.
 *
 ****************************************************************************/

#ident "$Revision: 1.87 $"

#ifdef __cplusplus
extern "C" {
#endif

#include <dmedia/dmedia.h>
#include <dmedia/dm_audio.h>
#include <dmedia/dm_audioconvert.h>
#include <dmedia/dm_params.h>

/********
*
* Audio sampling rate conversion parameters
*
********/

/********
*
* Parameters returned by dmAudioRateConverterGetParams (for all algorithms)
*
********/

#define DM_AUDIO_RC_INPUT_RATE		"DM_AUDIO_RC_INPUT_RATE"
#define DM_AUDIO_RC_OUTPUT_RATE		"DM_AUDIO_RC_OUTPUT_RATE"
#define DM_AUDIO_RC_ATOMIC_IN_LENGTH        "DM_AUDIO_RC_ATOMIC_IN_LENGTH"
#define DM_AUDIO_RC_ATOMIC_OUT_LENGTH       "DM_AUDIO_RC_ATOMIC_OUT_LENGTH"
#define DM_AUDIO_RC_GROUP_DELAY             "DM_AUDIO_RC_GROUP_DELAY"

/********
*
* Audio sampling rate conversion routines 
*
*********/

typedef struct _DMaudiorateconverter *DMaudiorateconverter;

extern DMstatus dmAudioRateConverterCreate ( DMaudiorateconverter *converter);

extern DMstatus dmAudioRateConverterDestroy ( DMaudiorateconverter converter);

extern DMstatus	dmAudioRateConverterSetParams ( DMaudiorateconverter converter, 
                                              	DMparams *params);

extern DMstatus	dmAudioRateConverterGetParams ( DMaudiorateconverter converter, 
                                              	DMparams *params);

extern DMstatus	dmAudioRateConvert ( DMaudiorateconverter converter,
                                     float *inBuffer,
                                     float *outBuffer,
                                     int numInputSamples,
                                     int *numOutputSamples);

extern DMstatus	dmAudioRateConverterReset ( DMaudiorateconverter converter, 
                                            float resetValue);

/********
*
* CCITT G.711 mu-law, A-law conversion routines
*
*********/

extern void dmG711MulawEncode ( short *inBuffer, 
                                unsigned char *outBuffer, 
                                int numSamples );
extern void dmG711MulawDecode ( unsigned char *inBuffer, 
                                    short *outBuffer, 
                                    int numSamples );
extern void dmG711MulawZeroTrapEncode ( short *inBuffer, 
                                        unsigned char *outBuffer,
                                        int numSamples );
extern void dmSunMulawEncode ( short *inBuffer, 
                               unsigned char *outBuffer,
                               int numSamples );

extern void dmSunMulawDecode ( unsigned char *inBuffer, 
                               short *outBuffer, 
                               int numSamples );

extern void dmNeXTMulawEncode ( short *inBuffer, 
                                unsigned char *outBuffer,
                                int numSamples);

extern void dmG711AlawEncode (short *inBuffer, 
                              unsigned char *outBuffer,
                              int numSamples);

extern void dmG711AlawDecode (unsigned char *inBuffer, 
                              short *outBuffer, 
                              int numSamples);

extern void dmG711AlawToMulaw (unsigned char *inBuffer, 
                               unsigned char *outBuffer,
                               int numSamples);

extern void dmG711MulawToAlaw (unsigned char *inBuffer, 
                               unsigned char *outBuffer,
                               int numSamples);

#define dmNeXTMulawDecode             dmG711MulawDecode
#define dmG711MulawZeroTrapDecode     dmG711MulawDecode 

/********
*
* CCITT G.722 conversion routines
*
* Note: The numSamples argument to dmG722Encode and dmG722Decode
*    	must always be a multiple of 2, since G.722 stores two 
*	encoded samples in a single byte
*
*********/

typedef struct _DMG722encoder *DMG722encoder;
typedef struct _DMG722decoder *DMG722decoder;

extern DMstatus dmG722EncoderCreate ( DMG722encoder *encoder,
                                      int maxSamples);

extern DMstatus dmG722EncoderGetParams ( DMG722encoder encoder,
					 DMparams *params);

extern DMstatus dmG722EncoderReset( DMG722encoder encoder);

extern DMstatus dmG722EncoderDestroy( DMG722encoder encoder);

extern DMstatus dmG722Encode ( DMG722encoder encoder,
                   	       short *inBuffer, 
                               unsigned char *outBuffer, 
                               int numSamples);

/* G722 decoder operates in 3 different modes:  64, 56, or 48 kbits/sec. */

#define DM_G722_64_KBITS  64000
#define DM_G722_56_KBITS  56000
#define DM_G722_48_KBITS  48000

extern DMstatus dmG722DecoderCreate( DMG722decoder *decoder,
                                     int maxSamples, 
                                     int decodeMode);

extern DMstatus dmG722DecoderGetParams ( DMG722decoder decoder,
					 DMparams *params);

extern DMstatus dmG722DecoderReset( DMG722decoder decoder);

extern DMstatus dmG722DecoderDestroy( DMG722decoder decoder);

extern DMstatus dmG722Decode( DMG722decoder decoder,
                              unsigned char *inBuffer, 
                              short *outBuffer, 
                              int numSamples);

/********
* Sony DV (digital video) audio compression/decompression routines
*
*********/

#define DM_DVAUDIO_VERBOSE     "DM_DVAUDIO_VERBOSE"

#define DM_DVAUDIO_FORMAT      "DM_DVAUDIO_FORMAT"
#define DM_DVAUDIO_PAL		12
#define DM_DVAUDIO_NTSC		10 

#define DM_DVAUDIO_PAL_DIF_FRAMESIZE  144000 /* bytes */
#define DM_DVAUDIO_NTSC_DIF_FRAMESIZE 120000 /* bytes */

/* The audio encoder needs to know whether to encode DV audio or DVCPRO audio.
 * The difference is that DVCPRO audio data is a subset of DV audio data
 * (only 48Khz and 16 bit samples are supported in DVCPRO audio), and also
 * we need to set a bit in the header indicating DV vs. DVCPRO audio.
 */
#define DM_DVAUDIO_TYPE    	"DM_DVAUDIO_TYPE" 
#define DM_DVAUDIO_DV      	1
#define DM_DVAUDIO_DVCPRO  	2

/*
 * The following is a boolean representing whether the "lock"
 * bit in the AAUX is set.
 */
#define DM_DVAUDIO_LOCK_MODE	"DM_DVAUDIO_LOCK_MODE"

/* Because DV audio blocks contain a variable number of frames, there is
 * need for a parameter to specify the minimum count
 * (DM_AUDIO_CODEC_FRAMES_PER_BLOCK is always the maximum count).
 */
#define DM_DVAUDIO_MIN_FRAMES_PER_BLOCK "DM_DVAUDIO_MIN_FRAMES_PER_BLOCK" 

/*
 * The following specifies whether the audio in the DV block is encoded as
 * SD-2ch or SD-4ch.  SD-2ch is either 32KHz, 44.1KHz, or 48KHz, with 16 bit
 * uncompressed samples, and can have either 1ch mono, 2ch mono, or stereo.  
 * SD-4ch audio is always 32KHz with 12 bit m-law compressed samples. Currently
 * SGI's support for SD-4ch is very minimal (dmAC can not encode SD-4ch).
 */
#define DM_DVAUDIO_CHANNEL_MODE	"DM_DVAUDIO_CHANNEL_MODE"
#define DM_DVAUDIO_SD_2CH    1	
#define DM_DVAUDIO_SD_4CH    2	

/*
 * The following specifies exactly what is inside a DV audio block.  The
 * first 3 choices start with the letters "DM_DVAUDIO_SD_2CH_" and are valid
 * choices when the DM_DVAUDIO_CHANNEL_MODE is set to DM_DVAUDIO_SD_2CH.  These
 * three values are from Table 15 of the DV "Blue Book 1994", part 2.  Note 
 * that dmAC currently does not support the DM_DVAUDIO_SD_2CH_2CH_MONO setting 
 * for encoding.
 *
 * After the first 3 choices, the rest of the choices start with the letters
 * "DM_DVAUDIO_SD_4CH_" are valid only when the DM_DVAUDIO_CHANNEL_MODE is set 
 * to DM_DVAUDIO_SD_4CH.  These values are from Table 16 of the DV "Blue Book 
 * 1994", part 2.  Right now, SGI's support for SD-4ch audio is very minimal 
 * (dmAC can not encode SD-4ch).
 */
#define DM_DVAUDIO_CHANNEL_POLICY "DM_DVAUDIO_CHANNEL_POLICY"

                        /* DM_DVAUDIO_SD_2CH mode    CH1    CH2  */
						 /* -----  ----- */
#define DM_DVAUDIO_SD_2CH_STEREO              1	 /*  L      R    */ /* COMMON */
#define DM_DVAUDIO_SD_2CH_2CH_MONO            2	 /*  M1     M2   */
#define DM_DVAUDIO_SD_2CH_MONO                3	 /*  M1     -    */ /* COMMON */

                        /* DM_DVAUDIO_SD_4CH mode                */
#define DM_DVAUDIO_SD_4CH_STEREO_STEREO       4	 /* L1 R1  L2 R2 */ /* COMMON */
#define DM_DVAUDIO_SD_4CH_STEREO_2CH_MONO     5	 /* L  R   M1 M2 */
#define DM_DVAUDIO_SD_4CH_STEREO_1CH_MONO     6	 /* L  R   M1 -  */
#define DM_DVAUDIO_SD_4CH_STEREO	      7	 /* L  R   -  -  */
#define DM_DVAUDIO_SD_4CH_2CH_MONO_STEREO     8	 /* M1 M2  L  R  */
#define DM_DVAUDIO_SD_4CH_4CH_MONO	      9	 /* M1 M2  M3 M4 */
#define DM_DVAUDIO_SD_4CH_3CH_MONO_1	      10 /* M1 M2  M3 -  */
#define DM_DVAUDIO_SD_4CH_2CH_MONO_1	      11 /* M1 M2  -  -  */
#define DM_DVAUDIO_SD_4CH_1CH_MONO_STEREO     12 /* M1 -   L  R  */
#define DM_DVAUDIO_SD_4CH_3CH_MONO_2	      13 /* M1 -   M2 M3 */
#define DM_DVAUDIO_SD_4CH_2CH_MONO_2	      14 /* M1 -   M2 -  */
#define DM_DVAUDIO_SD_4CH_1CH_MONO	      15 /* M1 -   -  -  */
#define DM_DVAUDIO_SD_4CH_3_1_STEREO          16 /* L  R   C  S  */
#define DM_DVAUDIO_SD_4CH_3_0_STEREO_1CH_MONO 17 /* L  R   C  M1 */
#define DM_DVAUDIO_SD_4CH_3_0_STEREO          18 /* A  R   C  -  */
#define DM_DVAUDIO_SD_4CH_2_2_STEREO          19 /* L  R   LS RS */

#define DV_PAL_SEQS_PER_FRAME           12
#define DV_NTSC_SEQS_PER_FRAME          10

/* DIF Components */
typedef struct {
  unsigned char bytes[80];
} headerblock;

typedef struct {
  unsigned char bytes[80];
} subcodeblock;

typedef struct {
  unsigned char bytes[80];
} vauxblock;

typedef struct {
  unsigned char bytes[80];
} audioblock;

typedef struct {
  unsigned char bytes[80];
} macroblock;

typedef struct {
  macroblock mb[5];
} videosegment;

typedef struct {
  audioblock audio;
  videosegment vidseg[3];
} audiovideorow;

typedef struct {
  headerblock   header;
  subcodeblock subcode[2];
  vauxblock vaux[3];
  audiovideorow row[9];
} DIFsequence;

typedef DIFsequence DIFframe[12];

/*
 * Packed data structure decoding stuff
 */

typedef struct {
  unsigned int lf           : 1;
  unsigned int pad0         : 1;
  unsigned int afsize       : 6;
  unsigned int sm           : 1;
  unsigned int chn          : 2;
  unsigned int pa           : 1;
  unsigned int audiomode  : 4;
  unsigned int pad1         : 1;
  unsigned int ml           : 1;
  unsigned int vfreq        : 1;
  unsigned int stype        : 5;
  unsigned int ef           : 1;
  unsigned int tc           : 1;
  unsigned int smp          : 3;
  unsigned int qu           : 3;
} aaux_source_t;

typedef struct {
  unsigned int ds: 1;
  unsigned int tm: 1;
  unsigned int totz: 2;
  unsigned int uotz: 4;
  unsigned int ones: 2;
  unsigned int tod: 2;
  unsigned int uod: 4;
  unsigned int week: 3;
  unsigned int tnmn: 1;
  unsigned int uom: 4;
  unsigned int toy: 4;
  unsigned int uoy: 4;
} aaux_rec_date_t;

typedef struct {
  unsigned int d1: 2;
  unsigned int tof:2;
  unsigned int uof:4;
  unsigned int d2: 1;
  unsigned int tos:3;
  unsigned int uos:4;
  unsigned int d3: 1;
  unsigned int tom: 3;
  unsigned int uom: 4;
  unsigned int d4: 2;
  unsigned int toh: 2;
  unsigned int uoh: 4;
} aaux_rec_time_t;

typedef struct {
  unsigned int bf: 1;
  unsigned int d1: 1;
  unsigned int tof:2;
  unsigned int uof:4;
  unsigned int d2:1;
  unsigned int tos:3;
  unsigned int uos:4;
  unsigned int d3:1;
  unsigned int tom:3;
  unsigned int uom:4;
  unsigned int d4:2;
  unsigned int toh:2;
  unsigned int uoh:4;
} time_code_t;

typedef struct {
  unsigned int cgms : 2;
  unsigned int isr : 2;
  unsigned int cmp : 2;
  unsigned int ss : 2;
  unsigned int rec_st : 1;
  unsigned int rec_end: 1;
  unsigned int rec_mode : 3;
  unsigned int insert_ch : 3;
  unsigned int drf: 1;
  unsigned int speed:7;
  unsigned int d1: 1;
  unsigned int genre_category:7;
} aaux_source_control_t;

typedef struct {
  unsigned int dsf:1;
  unsigned int zero:1;
  unsigned int rsv3:6;
  unsigned int dftia:4;
  unsigned int rsv4:1;
  unsigned int apt:3;
  unsigned int tf1:1;
  unsigned int rsv5:4;
  unsigned int ap1:3;
  unsigned int tf2:1;
  unsigned int rsv6:4;
  unsigned int ap2:3;
  unsigned int tf3:1;
  unsigned int rsv7:4;
  unsigned int ap3:3;
} hdr_t;


typedef struct
{
  unsigned char totvc:4;
  unsigned char uotvc:4;
  unsigned char bw:1;
  unsigned char en:1;
  unsigned char clf:2;
  unsigned char hotvc:4;
  unsigned char source_code:2;
  unsigned char f60_50:1;
  unsigned char stype:5;
  unsigned char tuner_category;
} vaux_source_t;


typedef struct
{
  unsigned char cgms:2;
  unsigned char isr:2;
  unsigned char cmp:2;
  unsigned char ss:2;

  unsigned char rec_st:1;
  unsigned char b_1:1;
  unsigned char rec_mode:2;
  unsigned char b_2:1;
  unsigned char disp:3;

  unsigned char ff:1;
  unsigned char fs:1;
  unsigned char fc:1;
  unsigned char il:1;
  unsigned char st:1;
  unsigned char sc:1;
  unsigned char bcsys:2;

  unsigned char b_3:1;
  unsigned char genre_category:7;
} vaux_source_control_t;


#define AAUX_SOURCE_50HZ 1
#define AAUX_SOURCE_60HZ 0
#define AAUX_SOURCE_SD   0
#define AAUX_SOURCE_HD   2
#define AAUX_SOURCE_48KHZ 0
#define AAUX_SOURCE_441KHZ 1
#define AAUX_SOURCE_32KHZ 2

typedef struct _DMDVencodestate *DMDVaudioencoder;
typedef struct _DMDVdecodestate *DMDVaudiodecoder;

extern DMstatus dmDVAudioEncoderCreate(DMDVaudioencoder *encoder);
extern DMstatus dmDVAudioEncoderGetParams(DMDVaudioencoder encoder,
					  DMparams *params);
extern DMstatus dmDVAudioEncoderSetParams(DMDVaudioencoder encoder,
					  DMparams *params);
extern DMstatus dmDVAudioEncoderReset(DMDVaudioencoder encoder);
extern DMstatus dmDVAudioEncoderDestroy(DMDVaudioencoder encoder);
extern DMstatus dmDVAudioEncode(DMDVaudioencoder encoder,
                                 void *inBuffer, 
                                 void *outBuffer, 
                                 int *numFrames);

extern DMstatus dmDVAudioDecoderCreate(DMDVaudiodecoder *decoder);
extern DMstatus dmDVAudioDecoderGetParams(DMDVaudiodecoder decoder,
				          DMparams *params);
extern DMstatus dmDVAudioDecoderSetParams(DMDVaudiodecoder decoder,
				 	  DMparams *params);
extern DMstatus dmDVAudioDecoderReset(DMDVaudiodecoder decoder);
extern DMstatus dmDVAudioDecoderDestroy(DMDVaudiodecoder decoder);
extern DMstatus dmDVAudioDecode(DMDVaudiodecoder decoder,
                                void *inBuffer, 
                                void *outBuffer, 
                                int *numFrames);
extern float dmDVAudioDecodeGetSampleRate(void *buffer);
extern DMstatus dmDVAudioHeaderGetParams(void *buffer, DMparams *params, 
                                         int *numSampFrames);

extern DMstatus dmDVAudioEncoderGetFrameSize(DMDVaudioencoder encoder,
                                         int *numSampFrames);

/********
*
* DVI/IMA ADPCM audio compression/decompression routines
*
* Note: For 4 bits per sample algorithm, the numSamples argument to
*	dmDVIaudioEncode and dmDVIaudioDecode must always be a multiple of 2,
*	since DVIaudio stores two encoded samples in a single byte. This is
*	the default.
*
*	For 3 bits per sample algorithm, the numSamples argument to
*	dmDVIaudioEncode and dmDVIaudioDecode must always be a multiple of 8,
*	since DVIaudio stores 8 encoded samples in 3 bytes.  Accordingly, the
*	length of the sample data buffer has to be a multiple of 8
* 	in short and the length of the compressed bit stream buffer
* 	has to be the same multiple of 3 in bytes.  
*
*********/

/* Apple and Intel/Microsoft have different ways of storing blocks of 
 * encoded data.  This parameter allows the audio conversion library 
 * to handle either type, or the possibility of no blocking whatsoever.
 * Note that this parameter is not used by the libdmedia DVI routines.
 */

#define DM_DVI_AUDIO_BLOCK_TYPE		"DM_DVI_AUDIO_BLOCK_TYPE"
#define DM_DVI_AUDIO_BLOCK_TYPE_NONE	0	/* no blocking at all */
#define DM_DVI_AUDIO_BLOCK_TYPE_APPLE	1	/* Apple, Inc. blocks */
#define DM_DVI_AUDIO_BLOCK_TYPE_INTEL	2	/* Intel/MS Inc. blocks */

#define DM_DVI_AUDIO_BITS_PER_SAMPLE	"DM_DVI_AUDIO_BITS_PER_SAMPLE"
#define DM_DVI_AUDIO_4BITS_PER_SAMPLE	4 	/* default */
#define DM_DVI_AUDIO_3BITS_PER_SAMPLE	3

typedef struct _DMDVIaudioState *DMDVIaudioencoder;
typedef struct _DMDVIaudioState *DMDVIaudiodecoder;

extern DMstatus dmDVIAudioEncoderCreate ( DMDVIaudioencoder *encoder);

extern DMstatus dmDVIAudioEncoderGetParams ( DMDVIaudioencoder encoder,
					  DMparams *params);
extern DMstatus dmDVIAudioEncoderSetParams ( DMDVIaudioencoder encoder,
					  DMparams *params);
extern DMstatus dmDVIAudioEncoderReset( DMDVIaudioencoder encoder);

extern DMstatus dmDVIAudioEncoderDestroy( DMDVIaudioencoder encoder);

extern DMstatus dmDVIAudioEncode ( DMDVIaudioencoder encoder,
                                   short *inBuffer, 
                                   unsigned char *outBuffer, 
                                   int numSamples);



extern DMstatus dmDVIAudioDecoderCreate( DMDVIaudiodecoder *decoder);

extern DMstatus dmDVIAudioDecoderGetParams ( DMDVIaudiodecoder decoder,
				 		 DMparams *params);
extern DMstatus dmDVIAudioDecoderSetParams ( DMDVIaudiodecoder decoder,
				 		 DMparams *params);
extern DMstatus dmDVIAudioDecoderReset( DMDVIaudiodecoder decoder);

extern DMstatus dmDVIAudioDecoderDestroy( DMDVIaudiodecoder decoder);

extern DMstatus dmDVIAudioDecode( DMDVIaudiodecoder decoder,
                                  unsigned char *inBuffer, 
                                  short *outBuffer, 
                                  int numSamples);

/********
*
* GSM speech compression/decompression routines
*   Note: The sample data size of input buffer to dmGSMEncode
*   must always be a multiple of 160, and the output bitstrem
* 	buffer consists of a multiple of 33 bytes.
*	For dmGSMDecode, vice versa.  The speech/audio
*	data is short type (16 bits) and two's complement format. 
* 	The sampling rate is 8000 Hz. And the compressed bitrate
*	is 13200 bits/s.  This is not the same as standard specification
*	of 13000 bits/s because the first 4 bits of each 33 byte are
*	not useful information bits.  This bits arrangement was adopted
*	using the original scheme by Jutta Degener (jutta@cs.tu-berlin.de)
*	and Carsten Bormann (cabo@cs.tu-berlin.de), Communications and
*	Operating Systems Research Group, TU Berlin for compatibility
*	with typical UNIX applications.  And may be modify later (Ke).
*
*********/

typedef struct _DMGSMState *DMGSMencoder;
typedef struct _DMGSMState *DMGSMdecoder;

extern DMstatus dmGSMEncoderCreate ( DMGSMencoder *encoder);

extern DMstatus dmGSMEncoderGetParams ( DMGSMencoder encoder,
                                        DMparams *params);

extern DMstatus dmGSMEncoderSetParams ( DMGSMencoder encoder,
                                        DMparams *params);

extern DMstatus dmGSMEncoderReset( DMGSMencoder encoder);

extern DMstatus dmGSMEncoderDestroy( DMGSMencoder encoder);

extern DMstatus dmGSMEncode ( DMGSMencoder encoder,
                              short *inBuffer,
                              unsigned char *outBuffer, 
                              int numSamples);


extern DMstatus dmGSMDecoderCreate( DMGSMdecoder *decoder);

extern DMstatus dmGSMDecoderGetParams ( DMGSMdecoder decoder,
					DMparams *params);

extern DMstatus dmGSMDecoderSetParams ( DMGSMdecoder decoder,
					DMparams *params);

extern DMstatus dmGSMDecoderReset( DMGSMdecoder decoder);

extern DMstatus dmGSMDecoderDestroy( DMGSMdecoder decoder);

extern DMstatus dmGSMDecode( DMGSMdecoder decoder,
                             unsigned char *inBuffer, 
                             short *outBuffer,
                             int numSamples);

/********
*
* CCITT G.726 conversion routines that compress PCM sample data to ADPCM or
*	decompress ADPCM bitstrem to PCM sample data.
*
*   Note: The numSamples argument to dmG726Encode and dmG726Decode
*   	must always be a multiple of of 4, 8, 2, or 8 for operations at
*   	16, 24, 32, or 40 kbit/s respectively.  The output bitstrem buffer consists
* 	of the same multiple of 1, 3, 1, or 5 bytes, since G.726 stores 2, 3, 4, or 5 
*	bits for each input sample for operations at 16, 24, 32, or 40 kbit/s
*	respectively.  16, 24, 32, or 40 kbit/s operation is set via
*	DM_AUDIO_BITRATE.  The native output format can be set via
*   	DM_G726_NATIVE_FORMAT for mu law, A law, and linear for the PCM data. 
*	If the native format is linear PCM, the PCM data type will be short.
*	Otherwise, the PCM data type will be unsigned char.  Therefore, it
*	is void in the function prototyping.
*
*********/

/* bit stream rate values for G726 decompression */

#define DM_G726_16_KBITS 16000	/* G723-16 */
#define DM_G726_24_KBITS 24000	/* G723-24 */
#define DM_G726_32_KBITS 32000	/* G721    */
#define DM_G726_40_KBITS 40000	/* G723-40 */

/* native format of G726 {de}compressor */

#define DM_G726_NATIVE_FORMAT	"DM_G726_NATIVE_FORMAT"

#define DM_G726_ULAW        0
#define DM_G726_ALAW        1
#define DM_G726_LINEAR_PCM  2	/* default */

typedef struct _DMG726coder *DMG726encoder;
typedef struct _DMG726coder *DMG726decoder;

extern DMstatus dmG726EncoderCreate ( DMG726encoder *encoder);

extern DMstatus dmG726EncoderSetParams( DMG726encoder encoder,
                                        DMparams *params);

extern DMstatus dmG726EncoderGetParams( DMG726encoder encoder,
                                        DMparams *params);

extern DMstatus dmG726EncoderReset( DMG726encoder encoder);

extern DMstatus dmG726EncoderDestroy( DMG726encoder encoder);

extern DMstatus dmG726Encode ( DMG726encoder encoder,
                               void *inBuffer, 
                               unsigned char *outBuffer, 
                               int numSamples);



extern DMstatus dmG726DecoderCreate( DMG726decoder *decoder);

extern DMstatus dmG726DecoderSetParams( DMG726decoder encoder,
                                        DMparams *params);

extern DMstatus dmG726DecoderGetParams( DMG726decoder encoder,
                                        DMparams *params);

extern DMstatus dmG726DecoderReset( DMG726decoder decoder);

extern DMstatus dmG726DecoderDestroy( DMG726decoder decoder);

extern DMstatus dmG726Decode( DMG726decoder decoder,
                              unsigned char *inBuffer, 
                              void *outBuffer, 
                              int numSamples);
/********
* CCITT G.728 conversion routines that compress PCM sample data to
*  	LD-CELP or decompress LD-CELP bitstrem to PCM sample data.
* 
*   Note: The sample data size of input buffer, numSamples, to 
* 	dmG728Encode must always be a multiple of 40, and the
* 	output bitstrem buffer consists a multiple of
*   of 10 bytes.  For dmG728Decode, vice versa.  The speech/audio
*	data is short type (16 bits) and two's complement format. 
* 	The sampling rate is 8000 Hz. And the compressed bitrate
*	is 16000 bits/s. 
*
*********/

/* flag to select a decoder with or without postfiltering. */
/* for speech/voice signal, postfiltering should be used   */
/* and for DTMF tone or music audio, no postfiltering should be used */

#define DM_G728_POSTFILTERING_FLAG "DM_G728_POSTFILTERING_FLAG"
#define DM_G728_POSTFILTERING_YES	1  /* default */
#define DM_G728_POSTFILTERING_NO	0

typedef struct _DMG728coder *DMG728encoder;
typedef struct _DMG728coder *DMG728decoder;

extern DMstatus dmG728EncoderCreate(DMG728encoder *c);

extern DMstatus dmG728EncoderSetParams(DMG728encoder c,
                                       DMparams *params);

extern DMstatus dmG728EncoderGetParams(DMG728encoder c,
                                       DMparams *params);

extern DMstatus dmG728Encode(DMG728encoder c, 
                             short *sampledata, 
                             unsigned char *obuf,
                             int numSamples);

extern DMstatus dmG728EncoderReset(DMG728encoder c);

extern DMstatus dmG728EncoderDestroy(DMG728encoder c);


extern DMstatus dmG728DecoderCreate(DMG728decoder *d);

extern DMstatus dmG728Decode(DMG728decoder d,
                             unsigned char *ibuf,
                             short *sampledata,
                             int numSamples);

extern DMstatus dmG728DecoderReset(DMG728decoder d);

extern DMstatus dmG728DecoderGetParams(DMG728decoder d,
                                       DMparams *params);

extern DMstatus dmG728DecoderSetParams(DMG728decoder d,
                                       DMparams *params);

extern DMstatus dmG728DecoderDestroy(DMG728decoder d);

/***************
*                                                                         
*	Federal Standard 1016 CELP Voice encoder/decoder APIs.
*		                                  *
*	Note: the sample data format is short (16-bit) and 
*	assumed to be two's complement.  The sampling rate must be
*       8 kHz.  The compressed data format is unsigned char (8-bit).
*	Bitstrem buffer must consist of a multiple of 18 bytes.
*	The value of nsamples passed to FS1016
*       decode/decode routines must always be a multiple
*       of 240, 160, or 120 for operations of 4800, 7200,
*       or 9600 bits/s respectively.  The multipler has to
*       be the same as the multipler for bit stream.								  
*                                                                         
***************/

#define DM_FS1016_4800_BITS 4800 		/* default */
#define DM_FS1016_7200_BITS 7200 
#define DM_FS1016_9600_BITS 9600 

#define DM_FS1016_POSTFILTERING_FLAG "DM_FS1016_POSTFILTERING_FLAG"
#define DM_FS1016_POSTFILTERING_YES       1  	/* default */
#define DM_FS1016_POSTFILTERING_NO        0

#define DM_FS1016_HIGHPASS_FLAG "DM_FS1016_HIGHPASS_FLAG"
#define DM_FS1016_HIGHPASS_YES       1
#define DM_FS1016_HIGHPASS_NO        0  	/* default */

typedef struct _DMFS1016encoder *DMFS1016encoder;
typedef struct _DMFS1016decoder *DMFS1016decoder;

extern DMstatus dmFS1016EncoderCreate(DMFS1016encoder *c);
extern DMstatus dmFS1016EncoderDestroy(DMFS1016encoder c);
extern DMstatus dmFS1016EncoderReset(DMFS1016encoder c);
extern DMstatus dmFS1016Encode (DMFS1016encoder c, 
            		    short *sampledata, 
            		    unsigned char *obuf,
            		    int numSamples);

extern DMstatus dmFS1016EncoderSetParams(DMFS1016encoder c,
					 DMparams *params);
extern DMstatus dmFS1016EncoderGetParams(DMFS1016encoder c,
					 DMparams *params);


extern DMstatus dmFS1016DecoderCreate(DMFS1016decoder *d);
extern DMstatus dmFS1016DecoderDestroy(DMFS1016decoder d);
extern DMstatus dmFS1016DecoderReset(DMFS1016decoder d);
extern DMstatus dmFS1016Decode (DMFS1016decoder d,  
            			unsigned char *ibuf,
            			short *sampledata,
            			int numSamples);
extern DMstatus dmFS1016DecoderSetParams(DMFS1016decoder d,
			 DMparams *params);
extern DMstatus dmFS1016DecoderGetParams(DMFS1016decoder d,
			 DMparams *params);

/**********************************************************************
 * MPEG1 audio compression/decompression API routines 
 **********************************************************************/

/********
*
* MPEG1 audio compression/decompression control parameters
* for "DMMPEG1audioencoder" or "DMMPEG1audiodecoder" and
* possible values.
*
* A call to dmMPEG1AudioEncoderCreate or dmMPEG1AudioDecoderCreate
* will set encoder/decoder control, input, and output parameter values
* to predefined defaults.  It also does license check.
*
* dmMPEG1AudioEncoderSetParams and dmMPEG1AudioDecoderSetParams will
* set encoder/decoder control, input, and output parameter values
* to user defined values.  They also initialize necessary filter
* coefficients for encoder or decoder.	  
*
* Decoder parameter values can also be obtained by a call to
* dmMPEG1AudioHeaderGetParams (from the compressed MPEG1 bit stream
* header). This should be the normal way to get decoder parameter values.
* Then the obtained values can be plugged into decoder by calling
* dmMPEG1AudioDecoderCreate.
*
* Parameter values passed to/from the calls to dmMPEG1AudioEncoderCreate,
* dmMPEG1AudioEncoderGetParams, dmMPEG1AudioDecoderCreate, and
* dmMPEG1AudioDecoderGetParams are handled by DMparams.
*
* Uncompressed sample data type should be 16 bit short (twos-complement).
* Compressed bit stream data type should be unsigned char.
*
* For input and output sample data, the defaults is two channel, 44.1 KHz
*
********/

#define DM_MPEG1_AUDIO_LAYER   "DM_MPEG1_AUDIO_LAYER"

/* following are the possible enum values for DM_MPEG1_AUDIO_LAYER */

#define DM_MPEG1_AUDIO_LAYER1   1
#define DM_MPEG1_AUDIO_LAYER2   2
#define DM_MPEG1_AUDIO_LAYER3   3

/********/

#define DM_AUDIO_CHANNEL_POLICY  "DM_AUDIO_CHANNEL_POLICY"

/* following are the possible enum values for DM_MPEG1_AUDIO_CHANNEL_POLICY */

#define DM_AUDIO_STEREO             0
#define DM_AUDIO_JOINT_STEREO       1
#define DM_AUDIO_INDEPENDENT        2

/********/

/*
   The following is a list of valid MPEG bitrate values
   (integer - 32 bits) for DM_AUDIO_BITRATE:

 Layer 1:      32000,  64000,  96000, 128000,
              160000, 192000, 224000, 256000 (default),
              288000, 320000, 352000, 384000,
              416000, 448000
 Layer 2:      32000,  48000,  56000,  64000,
               80000,  96000, 112000, 128000,
              160000, 192000, 224000, 256000 (default),
              320000, 384000
 Layer 3:      32000,  40000,  48000,  56000,
               64000,  80000,  96000, 112000,
              128000, 160000, 192000, 224000,
              256000, 320000
*/

/********
*
* MPEG1 audio compression only:  parameters and possible values.
*
********/

#define DM_MPEG1_AUDIO_PSYCHOMODEL 	"DM_MPEG1_AUDIO_PSYCHOMODEL"

/* following are the possible enum values for DM_MPEG1_AUDIO_PSYCHOMODEL */

#define DM_MPEG1_AUDIO_PSYCHOMODEL1     1
#define DM_MPEG1_AUDIO_PSYCHOMODEL2     2


#define DM_MPEG1_AUDIO_PSYCHOMODEL1_ALPHA "DM_MPEG1_AUDIO_PSYCHOMODEL1_ALPHA"

/* possible float value for DM_MPEG1_AUDIO_PSYCHOMODEL1_ALPHA  */
/* is within (0.0, 2.0]. Default is 2.0.			  */ 


#define DM_MPEG1_AUDIO_BITRATE_POLICY   "DM_MPEG1_AUDIO_BITRATE_POLICY"

/* following are the possible values for both layer 1 and 2 */

#define DM_MPEG1_AUDIO_FIXRATE          0   	/* default */
#define DM_MPEG1_AUDIO_CONSTANT_QUALITY 1


#define DM_MPEG1_AUDIO_CONST_QUAL_NMR "DM_MPEG1_AUDIO_CONST_QUAL_NMR"

/*
   possible float value for DM_MPEG1_AUDIO_CONST_QUAL_NMR
   is within (-13.0, 13.0]. Default is 0.0.
   The argument is the desired mask to noise ratio in dB.
   A value of 0.0 is appropriate.  Positive (negative) values
   will make quantization noise more (less) audible and result
   in smaller (larger) compressed files.
*/

/********
*
* The following parameter and values are only for decompressor.
*
********/

#define DM_MPEG1_AUDIO_DECIMATION_SCALE "DM_MPEG1_AUDIO_DECIMATION_SCALE"

   /* The following are the possible integer values for parameter	*/
   /* DM_MPEG1_AUDIO_DECIMATION_SCALE.  2 or 4 indicates that  	*/
   /* the resynthesized stream should be at one-half or one-	*/
   /* quarter or the norminal sampling rate. A value of 1 	*/
   /* results in normal behavior.				*/

#define DM_MPEG1_AUDIO_BANDWIDTH_FULL		1 	/* default */
#define DM_MPEG1_AUDIO_BANDWIDTH_HALF		2
#define DM_MPEG1_AUDIO_BANDWIDTH_QUARTER	4

/********/
#define DM_MPEG1_AUDIO_SCALE_FILTERSHAPE "DM_MPEG1_AUDIO_SCALE_FILTERSHAPE"

   /* following are the possible num values for parameter	*/
   /* DM_MPEG1_AUDIO_SCALE_FILTERSHAPE.  		  	*/


#define DM_MPEG1_AUDIO_DEFAULT_FILTER	0 /* default */
#define DM_MPEG1_AUDIO_FILTER_SHAPE1	1 
#define DM_MPEG1_AUDIO_FILTER_SHAPE2	2 

/********/
#define DM_MPEG1_AUDIO_COMBINE_CHANS_FLAG  "DM_MPEG1_AUDIO_COMBINE_CHANS_FLAG"

/* integer, default value is 0; if set to 1, overrides the JOINT_STEREO mode */

/********
*
* MPEG1 audio parameters returned by
* dmMPEG1AudioEncoderGetParams or dmMPEG1AudioDecoderGetParams.
*
********/

#define DM_AUDIO_CODEC_FRAMES_PER_BLOCK  "DM_AUDIO_CODEC_FRAMES_PER_BLOCK"

   /* for each call to cmpression (encode), this many new     */
   /* sample frames (integer) must be provided; each call to  */
   /* decompression (decode), will return this many new       */
   /* sample frames (integer) for DM_AUDIO_CODEC_FRAMES_PER_BLOCK. */

#define DM_AUDIO_CODEC_MAX_BYTES_PER_BLOCK  "DM_AUDIO_CODEC_MAX_BYTES_PER_BLOCK"

   /* DM_AUDIO_CODEC_MAX_BYTES_PER_BLOCK                      */
   /* indicates the maximum number of bytes (integer) that    */
   /* will comprise a compressed data block.                  */

#define DM_AUDIO_CODEC_FILTER_DELAY  	"DM_AUDIO_CODEC_FILTER_DELAY"

   /* DM_AUDIO_CODEC_FILTER_DELAY indicates                      */ 
   /* number of sample frames (integer) of delay introduced in   */
   /* compression and decompression processing, usually          */
   /* different for compression versus decompression             */


/********
*
* MPEG1 audio Routines.
*
*********/

typedef struct _DMMPEG1audiocoder *DMMPEG1audioencoder;
typedef struct _DMMPEG1audiocoder *DMMPEG1audiodecoder;
typedef struct _DMawfilterstate *DMMPEG1audiofilterstate;

/* dmMPEG1AudioEncoderCreate will set encoder parameters to defaults. */
/* It will do licence check too.  dmMPEG1AudioEncoderSetParams will   */
/* set user defined parameter values and initialize necessary filter */
/* coefficients for encoder.  *params can be NULL, then defaults     */
/* will be used.                                                     */

extern DMstatus dmMPEG1AudioEncoderCreate (DMMPEG1audioencoder *encoder);
extern DMstatus dmMPEG1AudioEncoderSetParams (DMMPEG1audioencoder encoder,
                                              DMparams *params);	
extern DMstatus dmMPEG1AudioEncoderDestroy (DMMPEG1audioencoder encoder);
extern DMstatus dmMPEG1AudioEncoderReset (DMMPEG1audioencoder encoder);

extern DMstatus dmMPEG1AudioEncoderGetParams (DMMPEG1audioencoder encoder,
                                              DMparams *params);
extern DMstatus dmMPEG1AudioEncode (DMMPEG1audioencoder encoder,
				    short *sampBuf,
				    unsigned char *output,
				    int *frameBytes /* return value;     */
				                    /* number of output  */
					                /* bytes in bitstream produced */
				    );


/* dmMPEG1AudioDecoderCreate will set encoder parameters to defaults. */
/* It will do licence check too.  _MPEG1AudioDecoderSetParams will   */
/* set user defined parameter values and initialize necessary filter */
/* coefficients for encoder.  *params can be NULL, then defaults     */
/* will be used.  User defined parameters should be obtained first   */
/* by using _MPEG1AudioHeaderGetParams from compressed data header.  */

extern DMstatus dmMPEG1AudioDecoderCreate (DMMPEG1audiodecoder *decoder);
extern DMstatus dmMPEG1AudioDecoderSetParams (DMMPEG1audiodecoder decoder,
                                             DMparams *params);

extern DMstatus dmMPEG1AudioDecoderDestroy (DMMPEG1audiodecoder decoder);
extern DMstatus dmMPEG1AudioDecoderReset (DMMPEG1audiodecoder decoder);
extern DMstatus dmMPEG1AudioDecoderGetParams (DMMPEG1audiodecoder decoder,
                                              DMparams *params);
extern DMstatus dmMPEG1AudioDecode (DMMPEG1audiodecoder decoder,
				    unsigned char *cmpData,
				    short *output,
				    int *fmtBytes /* return value;     */
					              /* number of input  */
				 	              /* bytes in bitstream consumed */
				    );
/* routine checking if compressed bitstream header is valid */

extern DMstatus dmMPEG1AudioHeaderCheck (unsigned char *cmpData);

/* routine getting information from compressed bitstream header */

extern DMstatus dmMPEG1AudioHeaderGetParams (unsigned char *cmpData,
                                             DMparams *params);

/* routine getting expected length in bytes of any compressed data block */
/* starting from the header that was found. If no valid header was found */
/* zero is returned.  This may be useful number of bytes to queue up for */
/* calls to dmMPEG1AudioDecode.  It substitutes the function of	         */
/* AwGetBlockBytes, but the returned value is in blockSize. 		 */

extern DMstatus dmMPEG1AudioHeaderGetBlockBytes (DMMPEG1audiodecoder decoder,
						 unsigned char *cmpData,
						 int *blockSize /* return value;    */
							   /* length of bytes  */
							   /* in bitstream to  */
							   /* be decompressed  */	
 						 );				

/* routines that save encoder or decoder filter states.	  		*/
/* coder can be either DMMPEG1audioencoder or DMMPEG1audiodecoder.      */
                        
extern DMstatus dmMPEG1AudioFilterStateCreate (DMMPEG1audiofilterstate *filterState);
extern DMstatus dmMPEG1AudioFilterStateDestroy (DMMPEG1audiofilterstate filterState);
extern DMstatus dmMPEG1AudioFilterStateSave (void *coder,
                                         	DMMPEG1audiofilterstate filterState);
extern DMstatus dmMPEG1AudioFilterStateRestore (void *coder,
                                           	DMMPEG1audiofilterstate filterState);

/********
* end of MPEG1 audio routines.
*********/

/********
*
* multirate parameters.
*
*********/
/********
*
* multirate parameters for both compression and decompression.
*
********/
/*
* Parameter values passed to/from the calls of dmMultiRateEncoderSetParams
* dmMultiRateEncoderGetParams, dmMultiRateDecoderSetParams, and
* dmMultiRateDecoderGetParams are handled by DMparams.
*
* Uncompressed sample data type should be 16 bit short (twos-complement).
* Compressed bit stream data type should be unsigned char.
*
* For input and output sample data, the defaults are two channel, 44.1 KHz
* sampling rate.
*/

   /* DM_AUDIO_STEREO (== 0 == MPGMODE_STEREO -- default)     	*/
   /* and DM_AUDIO_INDEPENDENT  (== 2 == MPGMODE_DUAL)		*/ 
   /* are the only possible values for 				*/
   /* DM_AUDIO_CHANNEL_POLICY for multirate. 			*/

/********/
#define DM_MULTIRATE_BITRATE_POLICY   "DM_MULTIRATE_BITRATE_POLICY"

   /* following is the possible value for DM_MULTIRATE_BITRATE_POLICY */

#define DM_MULTIRATE_CONSTANT_QUALITY   0       /* default */
#define DM_MULTIRATE_LOSSLESS  		1

/********
*
* Following parameter and values are only for decompressor.
*
********/

#define DM_MULTIRATE_DECIMATION_SCALE "DM_MULTIRATE_DECIMATION_SCALE"

   /* following are the possible integer values for parameter   */
   /* DM_MULTIRATE_DECIMATION_SCALE.  2 or 4 indicates that   */
   /* the resynthesized stream should be at one-half or one-    */
   /* quarter or the norminal sampling rate. A value of 1       */
   /* results in normal behavior.                               */

#define DM_MULTIRATE_BANDWIDTH_FULL           1       /* default */
#define DM_MULTIRATE_BANDWIDTH_HALF           2
#define DM_MULTIRATE_BANDWIDTH_QUARTER        4

/********/
#define DM_MULTIRATE_COMBINE_CHANS_FLAG  "DM_MULTIRATE_COMBINE_CHANS_FLAG"

    /* integer, default value is 0; if set to 1, overwrite the STEREO mode */
    /* need more study on this parameter; use default now.                 */

/********/
#define DM_MULTIRATE_LOSSEY_DECODE_FLAG  "DM_MULTIRATE_LOSSY_DECODE_FLAG"

    /* integer, default value is 0; only used for lossey decode of lossless */

/********
*
* multirate parameters returned by
* dmMultiRateEncoderGetParams or dmMultiRateDecoderGetParams.
*
********/
/*
DM_AUDIO_CODEC_FRAMES_PER_BLOCK  
DM_AUDIO_CODEC_MAX_BYTES_PER_BLOCK  
DM_AUDIO_CODEC_FILTER_DELAY    
*/
/********
* end of multirate parameters.
*********/

/*
	MS ADPCM
*/
typedef struct _DMMSADPCMstate *DMMSADPCMencoder;
typedef struct _DMMSADPCMstate *DMMSADPCMdecoder;

extern DMstatus dmMSADPCMDecoderCreate (DMMSADPCMdecoder *decoder);

#pragma optional dmMSADPCMDecoderCreate

extern DMstatus dmMSADPCMDecoderGetParams (DMMSADPCMdecoder decoder,
	DMparams *params);

#pragma optional dmMSADPCMDecoderGetParams

extern DMstatus dmMSADPCMDecoderSetParams (DMMSADPCMdecoder decoder,
	DMparams *params);

#pragma optional dmMSADPCMDecoderSetParams

extern DMstatus dmMSADPCMDecoderReset (DMMSADPCMdecoder decoder);

#pragma optional dmMSADPCMDecoderReset

extern DMstatus dmMSADPCMDecoderDestroy (DMMSADPCMdecoder decoder);

#pragma optional dmMSADPCMDecoderDestroy

extern DMstatus dmMSADPCMDecode (DMMSADPCMdecoder decoder,
	unsigned char *inBuffer, short *outBuffer, int numSamples);

#pragma optional dmMSADPCMDecode

extern DMstatus dmMSADPCMEncoderCreate (DMMSADPCMencoder *encoder);

#pragma optional dmMSADPCMEncoderCreate

extern DMstatus dmMSADPCMEncoderGetParams (DMMSADPCMencoder encoder,
	DMparams *params);

#pragma optional dmMSADPCMEncoderGetParams

extern DMstatus dmMSADPCMEncoderSetParams (DMMSADPCMencoder encoder,
	DMparams *params);

#pragma optional dmMSADPCMEncoderSetParams

extern DMstatus dmMSADPCMEncoderReset (DMMSADPCMencoder encoder);

#pragma optional dmMSADPCMEncoderReset

extern DMstatus dmMSADPCMEncoderDestroy (DMMSADPCMencoder encoder);

#pragma optional dmMSADPCMEncoderDestroy

extern DMstatus dmMSADPCMEncode (DMMSADPCMencoder encoder,
	short *inBuffer, unsigned char *outBuffer, int numSamples);

#pragma optional dmMSADPCMEncode

/*
 * old license utility routines
 * MPEG audio encode / decode no longer requires license
 * MultiRate audio encode / decode still requires 3rd party license
 */
#define AU_LICENSE_SGI_MPEG_ENCODER          1
#define AU_LICENSE_AWARE_MULTIRATE_ENCODER   3
#define AU_LICENSE_AWARE_MULTIRATE_DECODER   4

#define AU_LICENSE_AWARE_MPEG_ENCODER        AU_LICENSE_SGI_MPEG_ENCODER

#define AU_LICENSE_AWARE_MPEG_DECODER        2 /* obsolete */
#define AU_LICENSE_SGI_MPEG_DECODER          AU_LICENSE_AWARE_MPEG_DECODER

extern int AUchecklicense(int /*product*/, int */*errorval*/, char ** /*msg*/);

#define AU_LICENSE_OK     0
#define AU_LICENSE_ERR   -1
#define AU_BAD_PRODUCT   -2

/*
 * audio utility parameter-value list utilities
 * used only by Audio File Library
 */
typedef struct _AUpvlist *AUpvlist;
/*
 * valid types
 */
#define AU_PVTYPE_LONG   1      /* setparam arg is pointer to long */
#define AU_PVTYPE_DOUBLE 2      /* setparam arg is pointer to double */
#define AU_PVTYPE_PTR    3      /* setparam arg is pointer to (void *) */

#define AU_NULL_PVLIST ((struct _AUpvlist *)0)

/*
 * each returns nonnegative value on success
 * each returns negative value on failure
 */
extern AUpvlist AUpvnew(int /* max items */);
extern int AUpvgetmaxitems(AUpvlist);
extern int AUpvfree       (AUpvlist);
extern int AUpvsetparam   (AUpvlist, int /*item*/, int /*param*/);
extern int AUpvsetvaltype (AUpvlist, int /*item*/, int /*type*/);
extern int AUpvsetval     (AUpvlist, int /*item*/, void * /*val*/);
extern int AUpvgetparam   (AUpvlist, int /*item*/, int  * /*param*/);
extern int AUpvgetvaltype (AUpvlist, int /*item*/, int  * /*type*/);
extern int AUpvgetval     (AUpvlist, int /*item*/, void * /*val*/);

#ifdef __cplusplus 
}
#endif

#endif /* ! __INC_DM_AUDIOUTIL_H__ */
