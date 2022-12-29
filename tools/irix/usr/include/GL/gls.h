#if !defined(__gls_h_)
#define __gls_h_

/*
** Copyright 1995-2095, Silicon Graphics, Inc.
** All Rights Reserved.
** 
** This is UNPUBLISHED PROPRIETARY SOURCE CODE of Silicon Graphics, Inc.;
** the contents of this file may not be disclosed to third parties, copied or
** duplicated in any form, in whole or in part, without the prior written
** permission of Silicon Graphics, Inc.
** 
** RESTRICTED RIGHTS LEGEND:
** Use, duplication or disclosure by the Government is subject to restrictions
** as set forth in subdivision (c)(1)(ii) of the Rights in Technical Data
** and Computer Software clause at DFARS 252.227-7013, and/or in similar or
** successor clauses in the FAR, DOD or NASA FAR Supplement. Unpublished -
** rights reserved under the Copyright Laws of the United States.
*/

#include <GL/gl.h>
#include <stddef.h>
#include <stdio.h>

#if defined(__cplusplus)
    extern "C" {
#endif /* defined(__cplusplus) */

typedef void GLSchar;
typedef GLint GLSenum;
typedef long long GLSlong;
typedef GLint GLSopcode;
typedef void (*GLScaptureWrapFunc)(GLSopcode inOpcode);
typedef size_t (*GLSreadFunc)(size_t inCount, GLvoid *outBuf);
typedef size_t (*GLSwriteFunc)(size_t inCount, const GLvoid *inBuf);

#if defined(__cplusplus)
    typedef void (*GLSfunc)(...);
#else /* !defined(__cplusplus) */
    typedef void (*GLSfunc)();
#endif /* defined(__cplusplus) */

/* CaptureFlags */
/*      GLS_NONE */
#define GLS_CAPTURE_EXECUTE_BIT                   0x00000001
#define GLS_CAPTURE_WRITE_BIT                     0x00000002
#define GLS_CAPTURE_WRAP_BIT                      0x00000004

/* ImageFlags */
/*      GLS_NONE */
#define GLS_IMAGE_NULL_BIT                        0x00000001

/* WriteFlags */
/*      GLS_NONE */
#define GLS_WRITE_APPEND_BIT                      0x00000001
#define GLS_WRITE_BARE_BIT                        0x00000002

/* Fundamental */
#define GLS_NONE                                  0x0000

/* API */
#define GLS_API_GLS                               0x0010
#define GLS_API_GL                                0x0011

/* BlockType */
#define GLS_FRAME                                 0x0020
#define GLS_HEADER                                0x0021
#define GLS_INIT                                  0x0022
#define GLS_STATIC                                0x0023

/* Boolean */
#define GLS_ABORT_CALL                            0x0030
#define GLS_CAPTURE_VERTEX_ARRAYS                 0x0031

/* CaptureStreamType */
#define GLS_CONTEXT                               0x0040
#define GLS_BINARY_LSB_FIRST                      0x0041
#define GLS_BINARY_MSB_FIRST                      0x0042
#define GLS_TEXT                                  0x0043

/* CaptureWrapFunc */
#define GLS_CAPTURE_ENTRY_FUNC                    0x0050
#define GLS_CAPTURE_EXIT_FUNC                     0x0051

/* Channel */
#define GLS_DEFAULT_READ_CHANNEL                  0x0060
#define GLS_DEFAULT_WRITE_CHANNEL                 0x0061

/* CommandFunc */
#define GLS_CALL_FUNC                             0x0070
#define GLS_CAPTURE_FUNC                          0x0071

/* CopyStreamType */
/*      GLS_NONE */
/*      GLS_CONTEXT */
/*      GLS_BINARY_LSB_FIRST */
/*      GLS_BINARY_MSB_FIRST */
/*      GLS_TEXT */

/* ErrorCode */
/*      GLS_NONE */
#define GLS_DECODE_ERROR                          0x0080
#define GLS_IO_ERROR                              0x0081
#define GLS_PARAMETER_ERROR                       0x0082
#define GLS_RESOURCE_ERROR                        0x0083
#define GLS_STATE_ERROR                           0x0084
#define GLS_UNSUPPORTED_COMMAND                   0x0085
#define GLS_UNSUPPORTED_EXTENSION                 0x0086
#define GLS_UNSUPPORTED_VERSION                   0x0087

/* ExternStreamType */
/*      GLS_BINARY_LSB_FIRST */
/*      GLS_BINARY_MSB_FIRST */
/*      GLS_TEXT */

/* GetCommandFunc */
/*      GLS_CALL_FUNC */
/*      GLS_CAPTURE_FUNC */
#define GLS_NULL_FUNC                             0x0090

/* GetCommandi */
#define GLS_API                                   0x00A0
#define GLS_IS_CLIENT_COMMAND                     0x00A1
#define GLS_IS_GET_COMMAND                        0x00A2

/* GetEnumi */
#define GLS_IS_CLIENT_ENUM                        0x00B0

/* GetFunc */
/*      GLS_CAPTURE_ENTRY_FUNC */
/*      GLS_CAPTURE_EXIT_FUNC */
#define GLS_READ_FUNC                             0x00C0
#define GLS_WRITE_FUNC                            0x00C1

/* GetListc */
#define GLS_CONTEXT_STREAM_LIST                   0x00D0
#define GLS_READ_PREFIX_LIST                      0x00D1

/* GetListi */
#define GLS_OUT_ARG_SIZE_LIST                     0x00E0

/* GetListl */
#define GLS_OUT_ARG_POINTER_LIST                  0x00F0

/* GetPointer */
/*      GLS_DEFAULT_READ_CHANNEL */
/*      GLS_DEFAULT_WRITE_CHANNEL */
#define GLS_DATA_POINTER                          0x0100

/* GetStreamType */
/*      GLS_NONE */
/*      GLS_CONTEXT */
/*      GLS_BINARY_LSB_FIRST */
/*      GLS_BINARY_MSB_FIRST */
/*      GLS_TEXT */
#define GLS_UNKNOWN                               0x0110

/* GetStreamc */
#define GLS_READ_NAME                             0x0120
#define GLS_WRITE_NAME                            0x0121

/* GetStreami */
#define GLS_CRC32                                 0x0130
#define GLS_STREAM_TYPE                           0x0131

/* Getc */
#define GLS_EXTENSIONS                            0x0140
#define GLS_RELEASE                               0x0141
#define GLS_VENDOR                                0x0142
#define GLS_WRITE_PREFIX                          0x0143

/* Geti */
#define GLS_BLOCK_TYPE                            0x0150
#define GLS_CALL_NESTING                          0x0151
#define GLS_CAPTURE_NESTING                       0x0152
#define GLS_CONTEXT_STREAM_COUNT                  0x0153
#define GLS_MAX_CALL_NESTING                      0x0154
#define GLS_MAX_CAPTURE_NESTING                   0x0155
#define GLS_OUT_ARG_COUNT                         0x0156
#define GLS_READ_PREFIX_COUNT                     0x0157
#define GLS_STRING_TYPE                           0x0158
#define GLS_VERSION_MAJOR                         0x0159
#define GLS_VERSION_MINOR                         0x015A

/* Getiv */
#define GLS_CURRENT_TIME                          0x0170

/* Headerc */
#define GLS_AUTHOR                                0x0180
#define GLS_TITLE                                 0x0181
#define GLS_VERSION                               0x0182

/* Headerf */
#define GLS_ASPECT                                0x0190
#define GLS_CONTRAST                              0x0191

/* Headerfv */
#define GLS_GAMMA                                 0x01A0
#define GLS_RED_POINT                             0x01A1
#define GLS_GREEN_POINT                           0x01A2
#define GLS_BLUE_POINT                            0x01A3
#define GLS_WHITE_POINT                           0x01A4

/* Headeri */
#define GLS_ACCUM_RED_BITS                        0x01B0
#define GLS_ACCUM_GREEN_BITS                      0x01B1
#define GLS_ACCUM_BLUE_BITS                       0x01B2
#define GLS_ACCUM_ALPHA_BITS                      0x01B3
#define GLS_AUX_BUFFERS                           0x01B4
#define GLS_COLOR_RED_BITS                        0x01B5
#define GLS_COLOR_GREEN_BITS                      0x01B6
#define GLS_COLOR_BLUE_BITS                       0x01B7
#define GLS_COLOR_ALPHA_BITS                      0x01B8
#define GLS_DEPTH_BITS                            0x01B9
#define GLS_DOUBLEBUFFER                          0x01BA
#define GLS_HEIGHT                                0x01BB
#define GLS_INDEX_BITS                            0x01BC
#define GLS_RGBA_MODE                             0x01BD
#define GLS_STENCIL_BITS                          0x01BE
#define GLS_STEREO                                0x01BF
#define GLS_TILEABLE                              0x01C0
/*      GLS_SAMPLES_SGIS */

/* Headeriv */
#define GLS_CREATE_TIME                           0x01D0

/* StringType */
#define GLS_UCS1                                  0x01E0
#define GLS_UCS2                                  0x01E1
#define GLS_UCS4                                  0x01E2

/* GL_SGIS_multisample */
#define GLS_SAMPLES_SGIS                          0x0200

/* GLS opcodes */
#define GLS_OP_glsBeginGLS                        0x0010
#define GLS_OP_glsBlock                           0x0011
#define GLS_OP_glsCallStream                      0x0012
#define GLS_OP_glsDrawVertexArray                 0x0013
#define GLS_OP_glsEndGLS                          0x0014
#define GLS_OP_glsError                           0x0015
#define GLS_OP_glsHeaderc                         0x0016
#define GLS_OP_glsHeaderf                         0x0017
#define GLS_OP_glsHeaderfv                        0x0018
#define GLS_OP_glsHeaderi                         0x0019
#define GLS_OP_glsHeaderiv                        0x001A
#define GLS_OP_glsRequireExtension                0x001B
#define GLS_OP_glsRequireVersion                  0x001C
#define GLS_OP_glsUnsupportedCommand              0x001D
#define GLS_OP_glsBeginObj                        0x001E
#define GLS_OP_glsComment                         0x001F
#define GLS_OP_glsEndObj                          0x0020
#define GLS_OP_glsNumbv                           0x0021
#define GLS_OP_glsNumd                            0x0022
#define GLS_OP_glsNumdv                           0x0023
#define GLS_OP_glsNumf                            0x0024
#define GLS_OP_glsNumfv                           0x0025
#define GLS_OP_glsNumi                            0x0026
#define GLS_OP_glsNumiv                           0x0027
#define GLS_OP_glsNuml                            0x0028
#define GLS_OP_glsNumlv                           0x0029
#define GLS_OP_glsNumsv                           0x002A
#define GLS_OP_glsPad                             0x002B
#define GLS_OP_glsString                          0x002C
#define GLS_OP_glsSwapBuffers                     0x002D

/* GL opcodes */
#define GLS_OP_glAccum                            0x00BF
#define GLS_OP_glAlphaFunc                        0x00D6
#define GLS_OP_glAreTexturesResident              0x0259
#define GLS_OP_glAreTexturesResidentEXT           0x0147
#define GLS_OP_glArrayElement                     0x013E
#define GLS_OP_glArrayElementEXT                  0x013E
#define GLS_OP_glAsyncMarkerSGIX                  0x0198
#define GLS_OP_glBegin                            0x0037
#define GLS_OP_glBindTexture                      0x0148
#define GLS_OP_glBindTextureEXT                   0x0148
#define GLS_OP_glBitmap                           0x0038
#define GLS_OP_glBlendColor                       0x0120
#define GLS_OP_glBlendColorEXT                    0x0120
#define GLS_OP_glBlendEquation                    0x0121
#define GLS_OP_glBlendEquationEXT                 0x0121
#define GLS_OP_glBlendFunc                        0x00D7
#define GLS_OP_glCallList                         0x0032
#define GLS_OP_glCallLists                        0x0033
#define GLS_OP_glClear                            0x00B5
#define GLS_OP_glClearAccum                       0x00B6
#define GLS_OP_glClearColor                       0x00B8
#define GLS_OP_glClearDepth                       0x00BA
#define GLS_OP_glClearIndex                       0x00B7
#define GLS_OP_glClearStencil                     0x00B9
#define GLS_OP_glClipPlane                        0x0080
#define GLS_OP_glColor3bv                         0x0039
#define GLS_OP_glColor3dv                         0x003A
#define GLS_OP_glColor3fv                         0x003B
#define GLS_OP_glColor3iv                         0x003C
#define GLS_OP_glColor3sv                         0x003D
#define GLS_OP_glColor3ubv                        0x003E
#define GLS_OP_glColor3uiv                        0x003F
#define GLS_OP_glColor3usv                        0x0040
#define GLS_OP_glColor4bv                         0x0041
#define GLS_OP_glColor4dv                         0x0042
#define GLS_OP_glColor4fv                         0x0043
#define GLS_OP_glColor4iv                         0x0044
#define GLS_OP_glColor4sv                         0x0045
#define GLS_OP_glColor4ubv                        0x0046
#define GLS_OP_glColor4uiv                        0x0047
#define GLS_OP_glColor4usv                        0x0048
#define GLS_OP_glColorMask                        0x00BC
#define GLS_OP_glColorMaterial                    0x0081
#define GLS_OP_glColorPointer                     0x0152
#define GLS_OP_glColorPointerEXT                  0x013F
#define GLS_OP_glColorSubTable                    0x018E
#define GLS_OP_glColorTable                       0x0167
#define GLS_OP_glColorTableParameterfv            0x0168
#define GLS_OP_glColorTableParameterfvSGI         0x0168
#define GLS_OP_glColorTableParameteriv            0x0169
#define GLS_OP_glColorTableParameterivSGI         0x0169
#define GLS_OP_glColorTableSGI                    0x0167
#define GLS_OP_glConvolutionFilter1D              0x0125
#define GLS_OP_glConvolutionFilter1DEXT           0x0125
#define GLS_OP_glConvolutionFilter2D              0x0126
#define GLS_OP_glConvolutionFilter2DEXT           0x0126
#define GLS_OP_glConvolutionParameterf            0x0127
#define GLS_OP_glConvolutionParameterfEXT         0x0127
#define GLS_OP_glConvolutionParameterfv           0x0128
#define GLS_OP_glConvolutionParameterfvEXT        0x0128
#define GLS_OP_glConvolutionParameteri            0x0129
#define GLS_OP_glConvolutionParameteriEXT         0x0129
#define GLS_OP_glConvolutionParameteriv           0x012A
#define GLS_OP_glConvolutionParameterivEXT        0x012A
#define GLS_OP_glCopyColorSubTable                0x018F
#define GLS_OP_glCopyColorTable                   0x016A
#define GLS_OP_glCopyColorTableSGI                0x016A
#define GLS_OP_glCopyConvolutionFilter1D          0x012B
#define GLS_OP_glCopyConvolutionFilter1DEXT       0x012B
#define GLS_OP_glCopyConvolutionFilter2D          0x012C
#define GLS_OP_glCopyConvolutionFilter2DEXT       0x012C
#define GLS_OP_glCopyPixels                       0x00E5
#define GLS_OP_glCopyTexImage1D                   0x014D
#define GLS_OP_glCopyTexImage1DEXT                0x014D
#define GLS_OP_glCopyTexImage2D                   0x014E
#define GLS_OP_glCopyTexImage2DEXT                0x014E
#define GLS_OP_glCopyTexSubImage1D                0x014F
#define GLS_OP_glCopyTexSubImage1DEXT             0x014F
#define GLS_OP_glCopyTexSubImage2D                0x0150
#define GLS_OP_glCopyTexSubImage2DEXT             0x0150
#define GLS_OP_glCopyTexSubImage3D                0x0151
#define GLS_OP_glCopyTexSubImage3DEXT             0x0151
#define GLS_OP_glCullFace                         0x0082
#define GLS_OP_glDeformSGIX                       0x0186
#define GLS_OP_glDeformationMap3dSGIX             0x0184
#define GLS_OP_glDeformationMap3fSGIX             0x0185
#define GLS_OP_glDeleteAsyncMarkersSGIX           0x019C
#define GLS_OP_glDeleteLists                      0x0034
#define GLS_OP_glDeleteTextures                   0x025A
#define GLS_OP_glDeleteTexturesEXT                0x0149
#define GLS_OP_glDepthFunc                        0x00DB
#define GLS_OP_glDepthMask                        0x00BD
#define GLS_OP_glDepthRange                       0x0106
#define GLS_OP_glDetailTexFuncSGIS                0x0163
#define GLS_OP_glDisable                          0x00C0
#define GLS_OP_glDisableClientState               0x0153
#define GLS_OP_glDrawArrays                       0x0258
#define GLS_OP_glDrawArraysEXT                    0x0140
#define GLS_OP_glDrawBuffer                       0x00B4
#define GLS_OP_glDrawElements                     0x0154
#define GLS_OP_glDrawPixels                       0x00E7
#define GLS_OP_glDrawRangeElements                0x0190
#define GLS_OP_glEdgeFlagPointer                  0x0155
#define GLS_OP_glEdgeFlagPointerEXT               0x0141
#define GLS_OP_glEdgeFlagv                        0x0049
#define GLS_OP_glEnable                           0x00C1
#define GLS_OP_glEnableClientState                0x0156
#define GLS_OP_glEnd                              0x004A
#define GLS_OP_glEndList                          0x0031
#define GLS_OP_glEvalCoord1dv                     0x00CE
#define GLS_OP_glEvalCoord1fv                     0x00CF
#define GLS_OP_glEvalCoord2dv                     0x00D0
#define GLS_OP_glEvalCoord2fv                     0x00D1
#define GLS_OP_glEvalMesh1                        0x00D2
#define GLS_OP_glEvalMesh2                        0x00D4
#define GLS_OP_glEvalPoint1                       0x00D3
#define GLS_OP_glEvalPoint2                       0x00D5
#define GLS_OP_glFeedbackBuffer                   0x00AC
#define GLS_OP_glFinish                           0x00C2
#define GLS_OP_glFinishAsyncSGIX                  0x0199
#define GLS_OP_glFlush                            0x00C3
#define GLS_OP_glFlushRasterSGIX                  0x0180
#define GLS_OP_glFogFuncSGIS                      0x0179
#define GLS_OP_glFogf                             0x0083
#define GLS_OP_glFogfv                            0x0084
#define GLS_OP_glFogi                             0x0085
#define GLS_OP_glFogiv                            0x0086
#define GLS_OP_glFragmentColorMaterialSGIX        0x019E
#define GLS_OP_glFragmentLightModelfSGIX          0x01A3
#define GLS_OP_glFragmentLightModelfvSGIX         0x01A4
#define GLS_OP_glFragmentLightModeliSGIX          0x01A5
#define GLS_OP_glFragmentLightModelivSGIX         0x01A6
#define GLS_OP_glFragmentLightfSGIX               0x019F
#define GLS_OP_glFragmentLightfvSGIX              0x01A0
#define GLS_OP_glFragmentLightiSGIX               0x01A1
#define GLS_OP_glFragmentLightivSGIX              0x01A2
#define GLS_OP_glFragmentMaterialfSGIX            0x01A7
#define GLS_OP_glFragmentMaterialfvSGIX           0x01A8
#define GLS_OP_glFragmentMaterialiSGIX            0x01A9
#define GLS_OP_glFragmentMaterialivSGIX           0x01AA
#define GLS_OP_glFrameZoomSGIX                    0x0182
#define GLS_OP_glFrontFace                        0x0087
#define GLS_OP_glFrustum                          0x0107
#define GLS_OP_glGenAsyncMarkersSGIX              0x019B
#define GLS_OP_glGenLists                         0x0035
#define GLS_OP_glGenTextures                      0x025B
#define GLS_OP_glGenTexturesEXT                   0x014A
#define GLS_OP_glGetBooleanv                      0x00E8
#define GLS_OP_glGetClipPlane                     0x00E9
#define GLS_OP_glGetColorTable                    0x025D
#define GLS_OP_glGetColorTableParameterfv         0x025E
#define GLS_OP_glGetColorTableParameterfvSGI      0x016C
#define GLS_OP_glGetColorTableParameteriv         0x025F
#define GLS_OP_glGetColorTableParameterivSGI      0x016D
#define GLS_OP_glGetColorTableSGI                 0x016B
#define GLS_OP_glGetConvolutionFilter             0x0260
#define GLS_OP_glGetConvolutionFilterEXT          0x012D
#define GLS_OP_glGetConvolutionParameterfv        0x0261
#define GLS_OP_glGetConvolutionParameterfvEXT     0x012E
#define GLS_OP_glGetConvolutionParameteriv        0x0262
#define GLS_OP_glGetConvolutionParameterivEXT     0x012F
#define GLS_OP_glGetDetailTexFuncSGIS             0x0164
#define GLS_OP_glGetDoublev                       0x00EA
#define GLS_OP_glGetError                         0x00EB
#define GLS_OP_glGetFloatv                        0x00EC
#define GLS_OP_glGetFogFuncSGIS                   0x0191
#define GLS_OP_glGetFragmentLightfvSGIX           0x01AB
#define GLS_OP_glGetFragmentLightivSGIX           0x01AC
#define GLS_OP_glGetFragmentMaterialfvSGIX        0x01AD
#define GLS_OP_glGetFragmentMaterialivSGIX        0x01AE
#define GLS_OP_glGetHistogram                     0x0264
#define GLS_OP_glGetHistogramEXT                  0x0132
#define GLS_OP_glGetHistogramParameterfv          0x0265
#define GLS_OP_glGetHistogramParameterfvEXT       0x0133
#define GLS_OP_glGetHistogramParameteriv          0x0266
#define GLS_OP_glGetHistogramParameterivEXT       0x0134
#define GLS_OP_glGetInstrumentsSGIX               0x017A
#define GLS_OP_glGetIntegerv                      0x00ED
#define GLS_OP_glGetLightfv                       0x00EE
#define GLS_OP_glGetLightiv                       0x00EF
#define GLS_OP_glGetListParameterfvSGIX           0x0188
#define GLS_OP_glGetListParameterivSGIX           0x0189
#define GLS_OP_glGetMapdv                         0x00F0
#define GLS_OP_glGetMapfv                         0x00F1
#define GLS_OP_glGetMapiv                         0x00F2
#define GLS_OP_glGetMaterialfv                    0x00F3
#define GLS_OP_glGetMaterialiv                    0x00F4
#define GLS_OP_glGetMinmax                        0x0267
#define GLS_OP_glGetMinmaxEXT                     0x0135
#define GLS_OP_glGetMinmaxParameterfv             0x0268
#define GLS_OP_glGetMinmaxParameterfvEXT          0x0136
#define GLS_OP_glGetMinmaxParameteriv             0x0269
#define GLS_OP_glGetMinmaxParameterivEXT          0x0137
#define GLS_OP_glGetPixelMapfv                    0x00F5
#define GLS_OP_glGetPixelMapuiv                   0x00F6
#define GLS_OP_glGetPixelMapusv                   0x00F7
#define GLS_OP_glGetPixelTexGenParameterfvSGIS    0x0197
#define GLS_OP_glGetPixelTexGenParameterivSGIS    0x0196
#define GLS_OP_glGetPointerv                      0x0142
#define GLS_OP_glGetPointervEXT                   0x0142
#define GLS_OP_glGetPolygonStipple                0x00F8
#define GLS_OP_glGetSeparableFilter               0x0263
#define GLS_OP_glGetSeparableFilterEXT            0x0130
#define GLS_OP_glGetSharpenTexFuncSGIS            0x0166
#define GLS_OP_glGetString                        0x00F9
#define GLS_OP_glGetTexEnvfv                      0x00FA
#define GLS_OP_glGetTexEnviv                      0x00FB
#define GLS_OP_glGetTexFilterFuncSGIS             0x0175
#define GLS_OP_glGetTexGendv                      0x00FC
#define GLS_OP_glGetTexGenfv                      0x00FD
#define GLS_OP_glGetTexGeniv                      0x00FE
#define GLS_OP_glGetTexImage                      0x00FF
#define GLS_OP_glGetTexLevelParameterfv           0x0102
#define GLS_OP_glGetTexLevelParameteriv           0x0103
#define GLS_OP_glGetTexParameterfv                0x0100
#define GLS_OP_glGetTexParameteriv                0x0101
#define GLS_OP_glHint                             0x0088
#define GLS_OP_glHistogram                        0x0138
#define GLS_OP_glHistogramEXT                     0x0138
#define GLS_OP_glIglooInterfaceSGIX               0x0183
#define GLS_OP_glIndexMask                        0x00BE
#define GLS_OP_glIndexPointer                     0x0157
#define GLS_OP_glIndexPointerEXT                  0x0143
#define GLS_OP_glIndexdv                          0x004B
#define GLS_OP_glIndexfv                          0x004C
#define GLS_OP_glIndexiv                          0x004D
#define GLS_OP_glIndexsv                          0x004E
#define GLS_OP_glIndexubv                         0x015D
#define GLS_OP_glInitNames                        0x00AF
#define GLS_OP_glInstrumentsBufferSGIX            0x017B
#define GLS_OP_glInterleavedArrays                0x0158
#define GLS_OP_glIsAsyncMarkerSGIX                0x019D
#define GLS_OP_glIsEnabled                        0x0104
#define GLS_OP_glIsList                           0x0105
#define GLS_OP_glIsTexture                        0x025C
#define GLS_OP_glIsTextureEXT                     0x014B
#define GLS_OP_glLightEnviSGIX                    0x01AF
#define GLS_OP_glLightModelf                      0x008D
#define GLS_OP_glLightModelfv                     0x008E
#define GLS_OP_glLightModeli                      0x008F
#define GLS_OP_glLightModeliv                     0x0090
#define GLS_OP_glLightf                           0x0089
#define GLS_OP_glLightfv                          0x008A
#define GLS_OP_glLighti                           0x008B
#define GLS_OP_glLightiv                          0x008C
#define GLS_OP_glLineStipple                      0x0091
#define GLS_OP_glLineWidth                        0x0092
#define GLS_OP_glListBase                         0x0036
#define GLS_OP_glListParameterfSGIX               0x018A
#define GLS_OP_glListParameterfvSGIX              0x018B
#define GLS_OP_glListParameteriSGIX               0x018C
#define GLS_OP_glListParameterivSGIX              0x018D
#define GLS_OP_glLoadIdentity                     0x0108
#define GLS_OP_glLoadIdentityDeformationMapSGIX   0x0187
#define GLS_OP_glLoadMatrixd                      0x010A
#define GLS_OP_glLoadMatrixf                      0x0109
#define GLS_OP_glLoadName                         0x00B0
#define GLS_OP_glLogicOp                          0x00D8
#define GLS_OP_glMap1d                            0x00C6
#define GLS_OP_glMap1f                            0x00C7
#define GLS_OP_glMap2d                            0x00C8
#define GLS_OP_glMap2f                            0x00C9
#define GLS_OP_glMapGrid1d                        0x00CA
#define GLS_OP_glMapGrid1f                        0x00CB
#define GLS_OP_glMapGrid2d                        0x00CC
#define GLS_OP_glMapGrid2f                        0x00CD
#define GLS_OP_glMaterialf                        0x0093
#define GLS_OP_glMaterialfv                       0x0094
#define GLS_OP_glMateriali                        0x0095
#define GLS_OP_glMaterialiv                       0x0096
#define GLS_OP_glMatrixMode                       0x010B
#define GLS_OP_glMinmax                           0x0139
#define GLS_OP_glMinmaxEXT                        0x0139
#define GLS_OP_glMultMatrixd                      0x010D
#define GLS_OP_glMultMatrixf                      0x010C
#define GLS_OP_glNewList                          0x0030
#define GLS_OP_glNormal3bv                        0x004F
#define GLS_OP_glNormal3dv                        0x0050
#define GLS_OP_glNormal3fv                        0x0051
#define GLS_OP_glNormal3iv                        0x0052
#define GLS_OP_glNormal3sv                        0x0053
#define GLS_OP_glNormalPointer                    0x0159
#define GLS_OP_glNormalPointerEXT                 0x0144
#define GLS_OP_glOrtho                            0x010E
#define GLS_OP_glPassThrough                      0x00B1
#define GLS_OP_glPixelMapfv                       0x00E1
#define GLS_OP_glPixelMapuiv                      0x00E2
#define GLS_OP_glPixelMapusv                      0x00E3
#define GLS_OP_glPixelStoref                      0x00DF
#define GLS_OP_glPixelStorei                      0x00E0
#define GLS_OP_glPixelTexGenParameterfSGIS        0x0194
#define GLS_OP_glPixelTexGenParameterfvSGIS       0x0195
#define GLS_OP_glPixelTexGenParameteriSGIS        0x0192
#define GLS_OP_glPixelTexGenParameterivSGIS       0x0193
#define GLS_OP_glPixelTexGenSGIX                  0x0170
#define GLS_OP_glPixelTransferf                   0x00DD
#define GLS_OP_glPixelTransferi                   0x00DE
#define GLS_OP_glPixelZoom                        0x00DC
#define GLS_OP_glPointParameterfEXT               0x0177
#define GLS_OP_glPointParameterfSGIS              0x0177
#define GLS_OP_glPointParameterfvEXT              0x0178
#define GLS_OP_glPointParameterfvSGIS             0x0178
#define GLS_OP_glPointSize                        0x0097
#define GLS_OP_glPollAsyncSGIX                    0x019A
#define GLS_OP_glPollInstrumentsSGIX              0x017C
#define GLS_OP_glPolygonMode                      0x0098
#define GLS_OP_glPolygonOffset                    0x015C
#define GLS_OP_glPolygonOffsetEXT                 0x0122
#define GLS_OP_glPolygonStipple                   0x0099
#define GLS_OP_glPopAttrib                        0x00C4
#define GLS_OP_glPopClientAttrib                  0x015E
#define GLS_OP_glPopMatrix                        0x010F
#define GLS_OP_glPopName                          0x00B2
#define GLS_OP_glPrioritizeTextures               0x014C
#define GLS_OP_glPrioritizeTexturesEXT            0x014C
#define GLS_OP_glPushAttrib                       0x00C5
#define GLS_OP_glPushClientAttrib                 0x015F
#define GLS_OP_glPushMatrix                       0x0110
#define GLS_OP_glPushName                         0x00B3
#define GLS_OP_glRasterPos2dv                     0x0054
#define GLS_OP_glRasterPos2fv                     0x0055
#define GLS_OP_glRasterPos2iv                     0x0056
#define GLS_OP_glRasterPos2sv                     0x0057
#define GLS_OP_glRasterPos3dv                     0x0058
#define GLS_OP_glRasterPos3fv                     0x0059
#define GLS_OP_glRasterPos3iv                     0x005A
#define GLS_OP_glRasterPos3sv                     0x005B
#define GLS_OP_glRasterPos4dv                     0x005C
#define GLS_OP_glRasterPos4fv                     0x005D
#define GLS_OP_glRasterPos4iv                     0x005E
#define GLS_OP_glRasterPos4sv                     0x005F
#define GLS_OP_glReadBuffer                       0x00E4
#define GLS_OP_glReadInstrumentsSGIX              0x017D
#define GLS_OP_glReadPixels                       0x00E6
#define GLS_OP_glRectdv                           0x0060
#define GLS_OP_glRectfv                           0x0061
#define GLS_OP_glRectiv                           0x0062
#define GLS_OP_glRectsv                           0x0063
#define GLS_OP_glReferencePlaneSGIX               0x0181
#define GLS_OP_glRenderMode                       0x00AE
#define GLS_OP_glResetHistogram                   0x013A
#define GLS_OP_glResetHistogramEXT                0x013A
#define GLS_OP_glResetMinmax                      0x013B
#define GLS_OP_glResetMinmaxEXT                   0x013B
#define GLS_OP_glRotated                          0x0111
#define GLS_OP_glRotatef                          0x0112
#define GLS_OP_glSampleMaskSGIS                   0x0160
#define GLS_OP_glSamplePatternSGIS                0x0161
#define GLS_OP_glScaled                           0x0113
#define GLS_OP_glScalef                           0x0114
#define GLS_OP_glScissor                          0x009A
#define GLS_OP_glSelectBuffer                     0x00AD
#define GLS_OP_glSeparableFilter2D                0x0131
#define GLS_OP_glSeparableFilter2DEXT             0x0131
#define GLS_OP_glShadeModel                       0x009B
#define GLS_OP_glSharpenTexFuncSGIS               0x0165
#define GLS_OP_glSpriteParameterfSGIX             0x0171
#define GLS_OP_glSpriteParameterfvSGIX            0x0172
#define GLS_OP_glSpriteParameteriSGIX             0x0173
#define GLS_OP_glSpriteParameterivSGIX            0x0174
#define GLS_OP_glStartInstrumentsSGIX             0x017E
#define GLS_OP_glStencilFunc                      0x00D9
#define GLS_OP_glStencilMask                      0x00BB
#define GLS_OP_glStencilOp                        0x00DA
#define GLS_OP_glStopInstrumentsSGIX              0x017F
#define GLS_OP_glTagSampleBufferSGIX              0x0162
#define GLS_OP_glTexCoord1dv                      0x0064
#define GLS_OP_glTexCoord1fv                      0x0065
#define GLS_OP_glTexCoord1iv                      0x0066
#define GLS_OP_glTexCoord1sv                      0x0067
#define GLS_OP_glTexCoord2dv                      0x0068
#define GLS_OP_glTexCoord2fv                      0x0069
#define GLS_OP_glTexCoord2iv                      0x006A
#define GLS_OP_glTexCoord2sv                      0x006B
#define GLS_OP_glTexCoord3dv                      0x006C
#define GLS_OP_glTexCoord3fv                      0x006D
#define GLS_OP_glTexCoord3iv                      0x006E
#define GLS_OP_glTexCoord3sv                      0x006F
#define GLS_OP_glTexCoord4dv                      0x0070
#define GLS_OP_glTexCoord4fv                      0x0071
#define GLS_OP_glTexCoord4iv                      0x0072
#define GLS_OP_glTexCoord4sv                      0x0073
#define GLS_OP_glTexCoordPointer                  0x015A
#define GLS_OP_glTexCoordPointerEXT               0x0145
#define GLS_OP_glTexEnvf                          0x00A2
#define GLS_OP_glTexEnvfv                         0x00A3
#define GLS_OP_glTexEnvi                          0x00A4
#define GLS_OP_glTexEnviv                         0x00A5
#define GLS_OP_glTexFilterFuncSGIS                0x0176
#define GLS_OP_glTexGend                          0x00A6
#define GLS_OP_glTexGendv                         0x00A7
#define GLS_OP_glTexGenf                          0x00A8
#define GLS_OP_glTexGenfv                         0x00A9
#define GLS_OP_glTexGeni                          0x00AA
#define GLS_OP_glTexGeniv                         0x00AB
#define GLS_OP_glTexImage1D                       0x00A0
#define GLS_OP_glTexImage2D                       0x00A1
#define GLS_OP_glTexImage3D                       0x013C
#define GLS_OP_glTexImage3DEXT                    0x013C
#define GLS_OP_glTexImage4DSGIS                   0x016E
#define GLS_OP_glTexParameterf                    0x009C
#define GLS_OP_glTexParameterfv                   0x009D
#define GLS_OP_glTexParameteri                    0x009E
#define GLS_OP_glTexParameteriv                   0x009F
#define GLS_OP_glTexSubImage1D                    0x0123
#define GLS_OP_glTexSubImage1DEXT                 0x0123
#define GLS_OP_glTexSubImage2D                    0x0124
#define GLS_OP_glTexSubImage2DEXT                 0x0124
#define GLS_OP_glTexSubImage3D                    0x013D
#define GLS_OP_glTexSubImage3DEXT                 0x013D
#define GLS_OP_glTexSubImage4DSGIS                0x016F
#define GLS_OP_glTextureColorMaskSGIS             0x01B0
#define GLS_OP_glTranslated                       0x0115
#define GLS_OP_glTranslatef                       0x0116
#define GLS_OP_glVertex2dv                        0x0074
#define GLS_OP_glVertex2fv                        0x0075
#define GLS_OP_glVertex2iv                        0x0076
#define GLS_OP_glVertex2sv                        0x0077
#define GLS_OP_glVertex3dv                        0x0078
#define GLS_OP_glVertex3fv                        0x0079
#define GLS_OP_glVertex3iv                        0x007A
#define GLS_OP_glVertex3sv                        0x007B
#define GLS_OP_glVertex4dv                        0x007C
#define GLS_OP_glVertex4fv                        0x007D
#define GLS_OP_glVertex4iv                        0x007E
#define GLS_OP_glVertex4sv                        0x007F
#define GLS_OP_glVertexPointer                    0x015B
#define GLS_OP_glVertexPointerEXT                 0x0146
#define GLS_OP_glViewport                         0x0117

/* GLS capture commands */
extern void glsCapture_glsBeginGLS (GLint inVersionMajor, GLint inVersionMinor);
extern void glsCapture_glsBlock (GLSenum inBlockType);
extern GLSenum glsCapture_glsCallStream (const GLSchar *inName);
extern void glsCapture_glsDrawVertexArray (GLenum inMode, GLenum inFormat, GLint inCount, const GLvoid *inArray);
extern void glsCapture_glsEndGLS (void);
extern void glsCapture_glsError (GLSopcode inOpcode, GLSenum inError);
extern void glsCapture_glsHeaderc (GLSenum inAttrib, const GLSchar *inString);
extern void glsCapture_glsHeaderf (GLSenum inAttrib, GLfloat inVal);
extern void glsCapture_glsHeaderfv (GLSenum inAttrib, const GLfloat *inVec);
extern void glsCapture_glsHeaderi (GLSenum inAttrib, GLint inVal);
extern void glsCapture_glsHeaderiv (GLSenum inAttrib, const GLint *inVec);
extern void glsCapture_glsRequireExtension (const GLSchar *inExtension);
extern void glsCapture_glsRequireVersion (GLSenum inAPI, GLint inVersionMajor, GLint inVersionMinor);
extern void glsCapture_glsUnsupportedCommand (const GLSchar *inCommand);
extern void glsCapture_glsBeginObj (const GLSchar *inTag);
extern void glsCapture_glsComment (const GLSchar *inComment);
extern void glsCapture_glsEndObj (void);
extern void glsCapture_glsNumbv (const GLSchar *inTag, GLint inCount, const GLbyte *inVec);
extern void glsCapture_glsNumd (const GLSchar *inTag, GLdouble inVal);
extern void glsCapture_glsNumdv (const GLSchar *inTag, GLint inCount, const GLdouble *inVec);
extern void glsCapture_glsNumf (const GLSchar *inTag, GLfloat inVal);
extern void glsCapture_glsNumfv (const GLSchar *inTag, GLint inCount, const GLfloat *inVec);
extern void glsCapture_glsNumi (const GLSchar *inTag, GLint inVal);
extern void glsCapture_glsNumiv (const GLSchar *inTag, GLint inCount, const GLint *inVec);
extern void glsCapture_glsNuml (const GLSchar *inTag, GLSlong inVal);
extern void glsCapture_glsNumlv (const GLSchar *inTag, GLint inCount, const GLSlong *inVec);
extern void glsCapture_glsNumsv (const GLSchar *inTag, GLint inCount, const GLshort *inVec);
extern void glsCapture_glsPad (void);
extern void glsCapture_glsString (const GLSchar *inTag, const GLSchar *inString);
extern void glsCapture_glsSwapBuffers (void);
extern const GLubyte* glsCapture_glGetString (GLenum name);
extern void glsCapture_glAccum (GLenum op, GLfloat value);
extern void glsCapture_glAlphaFunc (GLenum func, GLclampf ref);
extern GLboolean glsCapture_glAreTexturesResident (GLsizei n, const GLuint *textures, GLboolean *residences);
extern GLboolean glsCapture_glAreTexturesResidentEXT (GLsizei n, const GLuint *textures, GLboolean *residences);
extern void glsCapture_glArrayElement (GLint i);
extern void glsCapture_glArrayElementEXT (GLint i);
extern void glsCapture_glAsyncMarkerSGIX (GLuint marker);
extern void glsCapture_glBegin (GLenum mode);
extern void glsCapture_glBindTexture (GLenum target, GLuint texture);
extern void glsCapture_glBindTextureEXT (GLenum target, GLuint texture);
extern void glsCapture_glBitmap (GLsizei width, GLsizei height, GLfloat xorig, GLfloat yorig, GLfloat xmove, GLfloat ymove, const GLubyte *bitmap);
extern void glsCapture_glBlendColor (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
extern void glsCapture_glBlendColorEXT (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
extern void glsCapture_glBlendEquation (GLenum mode);
extern void glsCapture_glBlendEquationEXT (GLenum mode);
extern void glsCapture_glBlendFunc (GLenum sfactor, GLenum dfactor);
extern void glsCapture_glCallList (GLuint list);
extern void glsCapture_glCallLists (GLsizei n, GLenum type, const GLvoid *lists);
extern void glsCapture_glClear (GLbitfield mask);
extern void glsCapture_glClearAccum (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
extern void glsCapture_glClearColor (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
extern void glsCapture_glClearDepth (GLclampd depth);
extern void glsCapture_glClearIndex (GLfloat c);
extern void glsCapture_glClearStencil (GLint s);
extern void glsCapture_glClipPlane (GLenum plane, const GLdouble *equation);
extern void glsCapture_glColor3bv (const GLbyte *v);
extern void glsCapture_glColor3dv (const GLdouble *v);
extern void glsCapture_glColor3fv (const GLfloat *v);
extern void glsCapture_glColor3iv (const GLint *v);
extern void glsCapture_glColor3sv (const GLshort *v);
extern void glsCapture_glColor3ubv (const GLubyte *v);
extern void glsCapture_glColor3uiv (const GLuint *v);
extern void glsCapture_glColor3usv (const GLushort *v);
extern void glsCapture_glColor4bv (const GLbyte *v);
extern void glsCapture_glColor4dv (const GLdouble *v);
extern void glsCapture_glColor4fv (const GLfloat *v);
extern void glsCapture_glColor4iv (const GLint *v);
extern void glsCapture_glColor4sv (const GLshort *v);
extern void glsCapture_glColor4ubv (const GLubyte *v);
extern void glsCapture_glColor4uiv (const GLuint *v);
extern void glsCapture_glColor4usv (const GLushort *v);
extern void glsCapture_glColorMask (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
extern void glsCapture_glColorMaterial (GLenum face, GLenum mode);
extern void glsCapture_glColorPointer (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
extern void glsCapture_glColorPointerEXT (GLint size, GLenum type, GLsizei stride, GLsizei count, const GLvoid *pointer);
extern void glsCapture_glColorSubTable (GLenum target, GLsizei start, GLsizei count, GLenum format, GLenum type, const GLvoid *data);
extern void glsCapture_glColorTable (GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const GLvoid *table);
extern void glsCapture_glColorTableParameterfv (GLenum target, GLenum pname, const GLfloat *params);
extern void glsCapture_glColorTableParameterfvSGI (GLenum target, GLenum pname, const GLfloat *params);
extern void glsCapture_glColorTableParameteriv (GLenum target, GLenum pname, const GLint *params);
extern void glsCapture_glColorTableParameterivSGI (GLenum target, GLenum pname, const GLint *params);
extern void glsCapture_glColorTableSGI (GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const GLvoid *table);
extern void glsCapture_glConvolutionFilter1D (GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const GLvoid *image);
extern void glsCapture_glConvolutionFilter1DEXT (GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const GLvoid *image);
extern void glsCapture_glConvolutionFilter2D (GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *image);
extern void glsCapture_glConvolutionFilter2DEXT (GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *image);
extern void glsCapture_glConvolutionParameterf (GLenum target, GLenum pname, GLfloat params);
extern void glsCapture_glConvolutionParameterfEXT (GLenum target, GLenum pname, GLfloat params);
extern void glsCapture_glConvolutionParameterfv (GLenum target, GLenum pname, const GLfloat *params);
extern void glsCapture_glConvolutionParameterfvEXT (GLenum target, GLenum pname, const GLfloat *params);
extern void glsCapture_glConvolutionParameteri (GLenum target, GLenum pname, GLint params);
extern void glsCapture_glConvolutionParameteriEXT (GLenum target, GLenum pname, GLint params);
extern void glsCapture_glConvolutionParameteriv (GLenum target, GLenum pname, const GLint *params);
extern void glsCapture_glConvolutionParameterivEXT (GLenum target, GLenum pname, const GLint *params);
extern void glsCapture_glCopyColorSubTable (GLenum target, GLsizei start, GLint x, GLint y, GLsizei width);
extern void glsCapture_glCopyColorTable (GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width);
extern void glsCapture_glCopyColorTableSGI (GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width);
extern void glsCapture_glCopyConvolutionFilter1D (GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width);
extern void glsCapture_glCopyConvolutionFilter1DEXT (GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width);
extern void glsCapture_glCopyConvolutionFilter2D (GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height);
extern void glsCapture_glCopyConvolutionFilter2DEXT (GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height);
extern void glsCapture_glCopyPixels (GLint x, GLint y, GLsizei width, GLsizei height, GLenum type);
extern void glsCapture_glCopyTexImage1D (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border);
extern void glsCapture_glCopyTexImage1DEXT (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border);
extern void glsCapture_glCopyTexImage2D (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
extern void glsCapture_glCopyTexImage2DEXT (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
extern void glsCapture_glCopyTexSubImage1D (GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
extern void glsCapture_glCopyTexSubImage1DEXT (GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
extern void glsCapture_glCopyTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
extern void glsCapture_glCopyTexSubImage2DEXT (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
extern void glsCapture_glCopyTexSubImage3D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
extern void glsCapture_glCopyTexSubImage3DEXT (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
extern void glsCapture_glCullFace (GLenum mode);
extern void glsCapture_glDeformSGIX (GLbitfield mask);
extern void glsCapture_glDeformationMap3dSGIX (GLenum target, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, GLdouble w1, GLdouble w2, GLint wstride, GLint worder, const GLdouble *points);
extern void glsCapture_glDeformationMap3fSGIX (GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, GLfloat w1, GLfloat w2, GLint wstride, GLint worder, const GLfloat *points);
extern void glsCapture_glDeleteAsyncMarkersSGIX (GLuint marker, GLsizei range);
extern void glsCapture_glDeleteLists (GLuint list, GLsizei range);
extern void glsCapture_glDeleteTextures (GLsizei n, const GLuint *textures);
extern void glsCapture_glDeleteTexturesEXT (GLsizei n, const GLuint *textures);
extern void glsCapture_glDepthFunc (GLenum func);
extern void glsCapture_glDepthMask (GLboolean flag);
extern void glsCapture_glDepthRange (GLclampd zNear, GLclampd zFar);
extern void glsCapture_glDetailTexFuncSGIS (GLenum target, GLsizei n, const GLfloat *points);
extern void glsCapture_glDisable (GLenum cap);
extern void glsCapture_glDisableClientState (GLenum array);
extern void glsCapture_glDrawArrays (GLenum mode, GLint first, GLsizei count);
extern void glsCapture_glDrawArraysEXT (GLenum mode, GLint first, GLsizei count);
extern void glsCapture_glDrawBuffer (GLenum mode);
extern void glsCapture_glDrawElements (GLenum mode, GLsizei count, GLenum type, const GLvoid *indices);
extern void glsCapture_glDrawPixels (GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels);
extern void glsCapture_glDrawRangeElements (GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid *indices);
extern void glsCapture_glEdgeFlagPointer (GLsizei stride, const GLboolean *pointer);
extern void glsCapture_glEdgeFlagPointerEXT (GLsizei stride, GLsizei count, const GLboolean *pointer);
extern void glsCapture_glEdgeFlagv (const GLboolean *flag);
extern void glsCapture_glEnable (GLenum cap);
extern void glsCapture_glEnableClientState (GLenum array);
extern void glsCapture_glEnd (void);
extern void glsCapture_glEndList (void);
extern void glsCapture_glEvalCoord1dv (const GLdouble *u);
extern void glsCapture_glEvalCoord1fv (const GLfloat *u);
extern void glsCapture_glEvalCoord2dv (const GLdouble *u);
extern void glsCapture_glEvalCoord2fv (const GLfloat *u);
extern void glsCapture_glEvalMesh1 (GLenum mode, GLint i1, GLint i2);
extern void glsCapture_glEvalMesh2 (GLenum mode, GLint i1, GLint i2, GLint j1, GLint j2);
extern void glsCapture_glEvalPoint1 (GLint i);
extern void glsCapture_glEvalPoint2 (GLint i, GLint j);
extern void glsCapture_glFeedbackBuffer (GLsizei size, GLenum type, GLfloat *buffer);
extern void glsCapture_glFinish (void);
extern GLint glsCapture_glFinishAsyncSGIX (GLuint *markerp);
extern void glsCapture_glFlush (void);
extern void glsCapture_glFlushRasterSGIX (void);
extern void glsCapture_glFogFuncSGIS (GLsizei n, const GLfloat *points);
extern void glsCapture_glFogf (GLenum pname, GLfloat param);
extern void glsCapture_glFogfv (GLenum pname, const GLfloat *params);
extern void glsCapture_glFogi (GLenum pname, GLint param);
extern void glsCapture_glFogiv (GLenum pname, const GLint *params);
extern void glsCapture_glFragmentColorMaterialSGIX (GLenum face, GLenum mode);
extern void glsCapture_glFragmentLightModelfSGIX (GLenum pname, GLfloat param);
extern void glsCapture_glFragmentLightModelfvSGIX (GLenum pname, const GLfloat *params);
extern void glsCapture_glFragmentLightModeliSGIX (GLenum pname, GLint param);
extern void glsCapture_glFragmentLightModelivSGIX (GLenum pname, const GLint *params);
extern void glsCapture_glFragmentLightfSGIX (GLenum light, GLenum pname, GLfloat param);
extern void glsCapture_glFragmentLightfvSGIX (GLenum light, GLenum pname, const GLfloat *params);
extern void glsCapture_glFragmentLightiSGIX (GLenum light, GLenum pname, GLint param);
extern void glsCapture_glFragmentLightivSGIX (GLenum light, GLenum pname, const GLint *params);
extern void glsCapture_glFragmentMaterialfSGIX (GLenum face, GLenum pname, GLfloat param);
extern void glsCapture_glFragmentMaterialfvSGIX (GLenum face, GLenum pname, const GLfloat *params);
extern void glsCapture_glFragmentMaterialiSGIX (GLenum face, GLenum pname, GLint param);
extern void glsCapture_glFragmentMaterialivSGIX (GLenum face, GLenum pname, const GLint *params);
extern void glsCapture_glFrameZoomSGIX (GLint factor);
extern void glsCapture_glFrontFace (GLenum mode);
extern void glsCapture_glFrustum (GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
extern GLuint glsCapture_glGenAsyncMarkersSGIX (GLsizei range);
extern GLuint glsCapture_glGenLists (GLsizei range);
extern void glsCapture_glGenTextures (GLsizei n, GLuint *textures);
extern void glsCapture_glGenTexturesEXT (GLsizei n, GLuint *textures);
extern void glsCapture_glGetBooleanv (GLenum pname, GLboolean *params);
extern void glsCapture_glGetClipPlane (GLenum plane, GLdouble *equation);
extern void glsCapture_glGetColorTable (GLenum target, GLenum format, GLenum type, GLvoid *table);
extern void glsCapture_glGetColorTableParameterfv (GLenum target, GLenum pname, GLfloat *params);
extern void glsCapture_glGetColorTableParameterfvSGI (GLenum target, GLenum pname, GLfloat *params);
extern void glsCapture_glGetColorTableParameteriv (GLenum target, GLenum pname, GLint *params);
extern void glsCapture_glGetColorTableParameterivSGI (GLenum target, GLenum pname, GLint *params);
extern void glsCapture_glGetColorTableSGI (GLenum target, GLenum format, GLenum type, GLvoid *table);
extern void glsCapture_glGetConvolutionFilter (GLenum target, GLenum format, GLenum type, GLvoid *image);
extern void glsCapture_glGetConvolutionFilterEXT (GLenum target, GLenum format, GLenum type, GLvoid *image);
extern void glsCapture_glGetConvolutionParameterfv (GLenum target, GLenum pname, GLfloat *params);
extern void glsCapture_glGetConvolutionParameterfvEXT (GLenum target, GLenum pname, GLfloat *params);
extern void glsCapture_glGetConvolutionParameteriv (GLenum target, GLenum pname, GLint *params);
extern void glsCapture_glGetConvolutionParameterivEXT (GLenum target, GLenum pname, GLint *params);
extern void glsCapture_glGetDetailTexFuncSGIS (GLenum target, GLfloat *points);
extern void glsCapture_glGetDoublev (GLenum pname, GLdouble *params);
extern GLenum glsCapture_glGetError (void);
extern void glsCapture_glGetFloatv (GLenum pname, GLfloat *params);
extern void glsCapture_glGetFogFuncSGIS (const GLfloat *points);
extern void glsCapture_glGetFragmentLightfvSGIX (GLenum light, GLenum pname, GLfloat *params);
extern void glsCapture_glGetFragmentLightivSGIX (GLenum light, GLenum pname, GLint *params);
extern void glsCapture_glGetFragmentMaterialfvSGIX (GLenum face, GLenum pname, GLfloat *params);
extern void glsCapture_glGetFragmentMaterialivSGIX (GLenum face, GLenum pname, GLint *params);
extern void glsCapture_glGetHistogram (GLenum target, GLboolean reset, GLenum format, GLenum type, GLvoid *values);
extern void glsCapture_glGetHistogramEXT (GLenum target, GLboolean reset, GLenum format, GLenum type, GLvoid *values);
extern void glsCapture_glGetHistogramParameterfv (GLenum target, GLenum pname, GLfloat *params);
extern void glsCapture_glGetHistogramParameterfvEXT (GLenum target, GLenum pname, GLfloat *params);
extern void glsCapture_glGetHistogramParameteriv (GLenum target, GLenum pname, GLint *params);
extern void glsCapture_glGetHistogramParameterivEXT (GLenum target, GLenum pname, GLint *params);
extern GLint glsCapture_glGetInstrumentsSGIX (void);
extern void glsCapture_glGetIntegerv (GLenum pname, GLint *params);
extern void glsCapture_glGetLightfv (GLenum light, GLenum pname, GLfloat *params);
extern void glsCapture_glGetLightiv (GLenum light, GLenum pname, GLint *params);
extern void glsCapture_glGetListParameterfvSGIX (GLuint list, GLenum pname, GLfloat *params);
extern void glsCapture_glGetListParameterivSGIX (GLuint list, GLenum pname, GLint *params);
extern void glsCapture_glGetMapdv (GLenum target, GLenum query, GLdouble *v);
extern void glsCapture_glGetMapfv (GLenum target, GLenum query, GLfloat *v);
extern void glsCapture_glGetMapiv (GLenum target, GLenum query, GLint *v);
extern void glsCapture_glGetMaterialfv (GLenum face, GLenum pname, GLfloat *params);
extern void glsCapture_glGetMaterialiv (GLenum face, GLenum pname, GLint *params);
extern void glsCapture_glGetMinmax (GLenum target, GLboolean reset, GLenum format, GLenum type, GLvoid *values);
extern void glsCapture_glGetMinmaxEXT (GLenum target, GLboolean reset, GLenum format, GLenum type, GLvoid *values);
extern void glsCapture_glGetMinmaxParameterfv (GLenum target, GLenum pname, GLfloat *params);
extern void glsCapture_glGetMinmaxParameterfvEXT (GLenum target, GLenum pname, GLfloat *params);
extern void glsCapture_glGetMinmaxParameteriv (GLenum target, GLenum pname, GLint *params);
extern void glsCapture_glGetMinmaxParameterivEXT (GLenum target, GLenum pname, GLint *params);
extern void glsCapture_glGetPixelMapfv (GLenum map, GLfloat *values);
extern void glsCapture_glGetPixelMapuiv (GLenum map, GLuint *values);
extern void glsCapture_glGetPixelMapusv (GLenum map, GLushort *values);
extern void glsCapture_glGetPixelTexGenParameterfvSGIS (GLenum pname, GLfloat *params);
extern void glsCapture_glGetPixelTexGenParameterivSGIS (GLenum pname, GLint *params);
extern void glsCapture_glGetPointerv (GLenum pname, GLvoid* *params);
extern void glsCapture_glGetPointervEXT (GLenum pname, GLvoid* *params);
extern void glsCapture_glGetPolygonStipple (GLubyte *mask);
extern void glsCapture_glGetSeparableFilter (GLenum target, GLenum format, GLenum type, GLvoid *row, GLvoid *column, GLvoid *span);
extern void glsCapture_glGetSeparableFilterEXT (GLenum target, GLenum format, GLenum type, GLvoid *row, GLvoid *column, GLvoid *span);
extern void glsCapture_glGetSharpenTexFuncSGIS (GLenum target, GLfloat *points);
extern void glsCapture_glGetTexEnvfv (GLenum target, GLenum pname, GLfloat *params);
extern void glsCapture_glGetTexEnviv (GLenum target, GLenum pname, GLint *params);
extern void glsCapture_glGetTexFilterFuncSGIS (GLenum target, GLenum filter, GLfloat *weights);
extern void glsCapture_glGetTexGendv (GLenum coord, GLenum pname, GLdouble *params);
extern void glsCapture_glGetTexGenfv (GLenum coord, GLenum pname, GLfloat *params);
extern void glsCapture_glGetTexGeniv (GLenum coord, GLenum pname, GLint *params);
extern void glsCapture_glGetTexImage (GLenum target, GLint level, GLenum format, GLenum type, GLvoid *pixels);
extern void glsCapture_glGetTexLevelParameterfv (GLenum target, GLint level, GLenum pname, GLfloat *params);
extern void glsCapture_glGetTexLevelParameteriv (GLenum target, GLint level, GLenum pname, GLint *params);
extern void glsCapture_glGetTexParameterfv (GLenum target, GLenum pname, GLfloat *params);
extern void glsCapture_glGetTexParameteriv (GLenum target, GLenum pname, GLint *params);
extern void glsCapture_glHint (GLenum target, GLenum mode);
extern void glsCapture_glHistogram (GLenum target, GLsizei width, GLenum internalformat, GLboolean sink);
extern void glsCapture_glHistogramEXT (GLenum target, GLsizei width, GLenum internalformat, GLboolean sink);
extern void glsCapture_glIglooInterfaceSGIX (GLenum pname, const GLvoid *params);
extern void glsCapture_glIndexMask (GLuint mask);
extern void glsCapture_glIndexPointer (GLenum type, GLsizei stride, const GLvoid *pointer);
extern void glsCapture_glIndexPointerEXT (GLenum type, GLsizei stride, GLsizei count, const GLvoid *pointer);
extern void glsCapture_glIndexdv (const GLdouble *c);
extern void glsCapture_glIndexfv (const GLfloat *c);
extern void glsCapture_glIndexiv (const GLint *c);
extern void glsCapture_glIndexsv (const GLshort *c);
extern void glsCapture_glIndexubv (const GLubyte *c);
extern void glsCapture_glInitNames (void);
extern void glsCapture_glInstrumentsBufferSGIX (GLsizei size, GLint *buffer);
extern void glsCapture_glInterleavedArrays (GLenum format, GLsizei stride, const GLvoid *pointer);
extern GLboolean glsCapture_glIsAsyncMarkerSGIX (GLuint marker);
extern GLboolean glsCapture_glIsEnabled (GLenum cap);
extern GLboolean glsCapture_glIsList (GLuint list);
extern GLboolean glsCapture_glIsTexture (GLuint texture);
extern GLboolean glsCapture_glIsTextureEXT (GLuint texture);
extern void glsCapture_glLightEnviSGIX (GLenum pname, GLint param);
extern void glsCapture_glLightModelf (GLenum pname, GLfloat param);
extern void glsCapture_glLightModelfv (GLenum pname, const GLfloat *params);
extern void glsCapture_glLightModeli (GLenum pname, GLint param);
extern void glsCapture_glLightModeliv (GLenum pname, const GLint *params);
extern void glsCapture_glLightf (GLenum light, GLenum pname, GLfloat param);
extern void glsCapture_glLightfv (GLenum light, GLenum pname, const GLfloat *params);
extern void glsCapture_glLighti (GLenum light, GLenum pname, GLint param);
extern void glsCapture_glLightiv (GLenum light, GLenum pname, const GLint *params);
extern void glsCapture_glLineStipple (GLint factor, GLushort pattern);
extern void glsCapture_glLineWidth (GLfloat width);
extern void glsCapture_glListBase (GLuint base);
extern void glsCapture_glListParameterfSGIX (GLuint list, GLenum pname, GLfloat param);
extern void glsCapture_glListParameterfvSGIX (GLuint list, GLenum pname, const GLfloat *params);
extern void glsCapture_glListParameteriSGIX (GLuint list, GLenum pname, GLint param);
extern void glsCapture_glListParameterivSGIX (GLuint list, GLenum pname, const GLint *params);
extern void glsCapture_glLoadIdentity (void);
extern void glsCapture_glLoadIdentityDeformationMapSGIX (GLbitfield mask);
extern void glsCapture_glLoadMatrixd (const GLdouble *m);
extern void glsCapture_glLoadMatrixf (const GLfloat *m);
extern void glsCapture_glLoadName (GLuint name);
extern void glsCapture_glLogicOp (GLenum opcode);
extern void glsCapture_glMap1d (GLenum target, GLdouble u1, GLdouble u2, GLint stride, GLint order, const GLdouble *points);
extern void glsCapture_glMap1f (GLenum target, GLfloat u1, GLfloat u2, GLint stride, GLint order, const GLfloat *points);
extern void glsCapture_glMap2d (GLenum target, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, const GLdouble *points);
extern void glsCapture_glMap2f (GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, const GLfloat *points);
extern void glsCapture_glMapGrid1d (GLint un, GLdouble u1, GLdouble u2);
extern void glsCapture_glMapGrid1f (GLint un, GLfloat u1, GLfloat u2);
extern void glsCapture_glMapGrid2d (GLint un, GLdouble u1, GLdouble u2, GLint vn, GLdouble v1, GLdouble v2);
extern void glsCapture_glMapGrid2f (GLint un, GLfloat u1, GLfloat u2, GLint vn, GLfloat v1, GLfloat v2);
extern void glsCapture_glMaterialf (GLenum face, GLenum pname, GLfloat param);
extern void glsCapture_glMaterialfv (GLenum face, GLenum pname, const GLfloat *params);
extern void glsCapture_glMateriali (GLenum face, GLenum pname, GLint param);
extern void glsCapture_glMaterialiv (GLenum face, GLenum pname, const GLint *params);
extern void glsCapture_glMatrixMode (GLenum mode);
extern void glsCapture_glMinmax (GLenum target, GLenum internalformat, GLboolean sink);
extern void glsCapture_glMinmaxEXT (GLenum target, GLenum internalformat, GLboolean sink);
extern void glsCapture_glMultMatrixd (const GLdouble *m);
extern void glsCapture_glMultMatrixf (const GLfloat *m);
extern void glsCapture_glNewList (GLuint list, GLenum mode);
extern void glsCapture_glNormal3bv (const GLbyte *v);
extern void glsCapture_glNormal3dv (const GLdouble *v);
extern void glsCapture_glNormal3fv (const GLfloat *v);
extern void glsCapture_glNormal3iv (const GLint *v);
extern void glsCapture_glNormal3sv (const GLshort *v);
extern void glsCapture_glNormalPointer (GLenum type, GLsizei stride, const GLvoid *pointer);
extern void glsCapture_glNormalPointerEXT (GLenum type, GLsizei stride, GLsizei count, const GLvoid *pointer);
extern void glsCapture_glOrtho (GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
extern void glsCapture_glPassThrough (GLfloat token);
extern void glsCapture_glPixelMapfv (GLenum map, GLint mapsize, const GLfloat *values);
extern void glsCapture_glPixelMapuiv (GLenum map, GLint mapsize, const GLuint *values);
extern void glsCapture_glPixelMapusv (GLenum map, GLint mapsize, const GLushort *values);
extern void glsCapture_glPixelStoref (GLenum pname, GLfloat param);
extern void glsCapture_glPixelStorei (GLenum pname, GLint param);
extern void glsCapture_glPixelTexGenParameterfSGIS (GLenum pname, GLfloat param);
extern void glsCapture_glPixelTexGenParameterfvSGIS (GLenum pname, const GLfloat *params);
extern void glsCapture_glPixelTexGenParameteriSGIS (GLenum pname, GLint param);
extern void glsCapture_glPixelTexGenParameterivSGIS (GLenum pname, const GLint *params);
extern void glsCapture_glPixelTexGenSGIX (GLenum mode);
extern void glsCapture_glPixelTransferf (GLenum pname, GLfloat param);
extern void glsCapture_glPixelTransferi (GLenum pname, GLint param);
extern void glsCapture_glPixelZoom (GLfloat xfactor, GLfloat yfactor);
extern void glsCapture_glPointParameterfEXT (GLenum pname, GLfloat param);
extern void glsCapture_glPointParameterfSGIS (GLenum pname, GLfloat param);
extern void glsCapture_glPointParameterfvEXT (GLenum pname, const GLfloat *params);
extern void glsCapture_glPointParameterfvSGIS (GLenum pname, const GLfloat *params);
extern void glsCapture_glPointSize (GLfloat size);
extern GLint glsCapture_glPollAsyncSGIX (GLuint *markerp);
extern GLint glsCapture_glPollInstrumentsSGIX (GLint *marker_p);
extern void glsCapture_glPolygonMode (GLenum face, GLenum mode);
extern void glsCapture_glPolygonOffset (GLfloat factor, GLfloat units);
extern void glsCapture_glPolygonOffsetEXT (GLfloat factor, GLfloat bias);
extern void glsCapture_glPolygonStipple (const GLubyte *mask);
extern void glsCapture_glPopAttrib (void);
extern void glsCapture_glPopClientAttrib (void);
extern void glsCapture_glPopMatrix (void);
extern void glsCapture_glPopName (void);
extern void glsCapture_glPrioritizeTextures (GLsizei n, const GLuint *textures, const GLclampf *priorities);
extern void glsCapture_glPrioritizeTexturesEXT (GLsizei n, const GLuint *textures, const GLclampf *priorities);
extern void glsCapture_glPushAttrib (GLbitfield mask);
extern void glsCapture_glPushClientAttrib (GLbitfield mask);
extern void glsCapture_glPushMatrix (void);
extern void glsCapture_glPushName (GLuint name);
extern void glsCapture_glRasterPos2dv (const GLdouble *v);
extern void glsCapture_glRasterPos2fv (const GLfloat *v);
extern void glsCapture_glRasterPos2iv (const GLint *v);
extern void glsCapture_glRasterPos2sv (const GLshort *v);
extern void glsCapture_glRasterPos3dv (const GLdouble *v);
extern void glsCapture_glRasterPos3fv (const GLfloat *v);
extern void glsCapture_glRasterPos3iv (const GLint *v);
extern void glsCapture_glRasterPos3sv (const GLshort *v);
extern void glsCapture_glRasterPos4dv (const GLdouble *v);
extern void glsCapture_glRasterPos4fv (const GLfloat *v);
extern void glsCapture_glRasterPos4iv (const GLint *v);
extern void glsCapture_glRasterPos4sv (const GLshort *v);
extern void glsCapture_glReadBuffer (GLenum mode);
extern void glsCapture_glReadInstrumentsSGIX (GLint marker);
extern void glsCapture_glReadPixels (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid *pixels);
extern void glsCapture_glRectdv (const GLdouble *v1, const GLdouble *v2);
extern void glsCapture_glRectfv (const GLfloat *v1, const GLfloat *v2);
extern void glsCapture_glRectiv (const GLint *v1, const GLint *v2);
extern void glsCapture_glRectsv (const GLshort *v1, const GLshort *v2);
extern void glsCapture_glReferencePlaneSGIX (const GLdouble *equation);
extern GLint glsCapture_glRenderMode (GLenum mode);
extern void glsCapture_glResetHistogram (GLenum target);
extern void glsCapture_glResetHistogramEXT (GLenum target);
extern void glsCapture_glResetMinmax (GLenum target);
extern void glsCapture_glResetMinmaxEXT (GLenum target);
extern void glsCapture_glRotated (GLdouble angle, GLdouble x, GLdouble y, GLdouble z);
extern void glsCapture_glRotatef (GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
extern void glsCapture_glSampleMaskSGIS (GLclampf value, GLboolean invert);
extern void glsCapture_glSamplePatternSGIS (GLenum pattern);
extern void glsCapture_glScaled (GLdouble x, GLdouble y, GLdouble z);
extern void glsCapture_glScalef (GLfloat x, GLfloat y, GLfloat z);
extern void glsCapture_glScissor (GLint x, GLint y, GLsizei width, GLsizei height);
extern void glsCapture_glSelectBuffer (GLsizei size, GLuint *buffer);
extern void glsCapture_glSeparableFilter2D (GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *row, const GLvoid *column);
extern void glsCapture_glSeparableFilter2DEXT (GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *row, const GLvoid *column);
extern void glsCapture_glShadeModel (GLenum mode);
extern void glsCapture_glSharpenTexFuncSGIS (GLenum target, GLsizei n, const GLfloat *points);
extern void glsCapture_glSpriteParameterfSGIX (GLenum pname, GLfloat param);
extern void glsCapture_glSpriteParameterfvSGIX (GLenum pname, const GLfloat *params);
extern void glsCapture_glSpriteParameteriSGIX (GLenum pname, GLint param);
extern void glsCapture_glSpriteParameterivSGIX (GLenum pname, const GLint *params);
extern void glsCapture_glStartInstrumentsSGIX (void);
extern void glsCapture_glStencilFunc (GLenum func, GLint ref, GLuint mask);
extern void glsCapture_glStencilMask (GLuint mask);
extern void glsCapture_glStencilOp (GLenum fail, GLenum zfail, GLenum zpass);
extern void glsCapture_glStopInstrumentsSGIX (GLint marker);
extern void glsCapture_glTagSampleBufferSGIX (void);
extern void glsCapture_glTexCoord1dv (const GLdouble *v);
extern void glsCapture_glTexCoord1fv (const GLfloat *v);
extern void glsCapture_glTexCoord1iv (const GLint *v);
extern void glsCapture_glTexCoord1sv (const GLshort *v);
extern void glsCapture_glTexCoord2dv (const GLdouble *v);
extern void glsCapture_glTexCoord2fv (const GLfloat *v);
extern void glsCapture_glTexCoord2iv (const GLint *v);
extern void glsCapture_glTexCoord2sv (const GLshort *v);
extern void glsCapture_glTexCoord3dv (const GLdouble *v);
extern void glsCapture_glTexCoord3fv (const GLfloat *v);
extern void glsCapture_glTexCoord3iv (const GLint *v);
extern void glsCapture_glTexCoord3sv (const GLshort *v);
extern void glsCapture_glTexCoord4dv (const GLdouble *v);
extern void glsCapture_glTexCoord4fv (const GLfloat *v);
extern void glsCapture_glTexCoord4iv (const GLint *v);
extern void glsCapture_glTexCoord4sv (const GLshort *v);
extern void glsCapture_glTexCoordPointer (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
extern void glsCapture_glTexCoordPointerEXT (GLint size, GLenum type, GLsizei stride, GLsizei count, const GLvoid *pointer);
extern void glsCapture_glTexEnvf (GLenum target, GLenum pname, GLfloat param);
extern void glsCapture_glTexEnvfv (GLenum target, GLenum pname, const GLfloat *params);
extern void glsCapture_glTexEnvi (GLenum target, GLenum pname, GLint param);
extern void glsCapture_glTexEnviv (GLenum target, GLenum pname, const GLint *params);
extern void glsCapture_glTexFilterFuncSGIS (GLenum target, GLenum filter, GLsizei n, const GLfloat *weights);
extern void glsCapture_glTexGend (GLenum coord, GLenum pname, GLdouble param);
extern void glsCapture_glTexGendv (GLenum coord, GLenum pname, const GLdouble *params);
extern void glsCapture_glTexGenf (GLenum coord, GLenum pname, GLfloat param);
extern void glsCapture_glTexGenfv (GLenum coord, GLenum pname, const GLfloat *params);
extern void glsCapture_glTexGeni (GLenum coord, GLenum pname, GLint param);
extern void glsCapture_glTexGeniv (GLenum coord, GLenum pname, const GLint *params);
extern void glsCapture_glTexImage1D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const GLvoid *pixels);
extern void glsCapture_glTexImage2D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels);
extern void glsCapture_glTexImage3D (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid *pixels);
extern void glsCapture_glTexImage3DEXT (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid *pixels);
extern void glsCapture_glTexImage4DSGIS (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLsizei size4d, GLint border, GLenum format, GLenum type, const GLvoid *pixels);
extern void glsCapture_glTexParameterf (GLenum target, GLenum pname, GLfloat param);
extern void glsCapture_glTexParameterfv (GLenum target, GLenum pname, const GLfloat *params);
extern void glsCapture_glTexParameteri (GLenum target, GLenum pname, GLint param);
extern void glsCapture_glTexParameteriv (GLenum target, GLenum pname, const GLint *params);
extern void glsCapture_glTexSubImage1D (GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const GLvoid *pixels);
extern void glsCapture_glTexSubImage1DEXT (GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const GLvoid *pixels);
extern void glsCapture_glTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels);
extern void glsCapture_glTexSubImage2DEXT (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels);
extern void glsCapture_glTexSubImage3D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid *pixels);
extern void glsCapture_glTexSubImage3DEXT (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid *pixels);
extern void glsCapture_glTexSubImage4DSGIS (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint woffset, GLsizei width, GLsizei height, GLsizei depth, GLsizei size4d, GLenum format, GLenum type, const GLvoid *pixels);
extern void glsCapture_glTextureColorMaskSGIS (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
extern void glsCapture_glTranslated (GLdouble x, GLdouble y, GLdouble z);
extern void glsCapture_glTranslatef (GLfloat x, GLfloat y, GLfloat z);
extern void glsCapture_glVertex2dv (const GLdouble *v);
extern void glsCapture_glVertex2fv (const GLfloat *v);
extern void glsCapture_glVertex2iv (const GLint *v);
extern void glsCapture_glVertex2sv (const GLshort *v);
extern void glsCapture_glVertex3dv (const GLdouble *v);
extern void glsCapture_glVertex3fv (const GLfloat *v);
extern void glsCapture_glVertex3iv (const GLint *v);
extern void glsCapture_glVertex3sv (const GLshort *v);
extern void glsCapture_glVertex4dv (const GLdouble *v);
extern void glsCapture_glVertex4fv (const GLfloat *v);
extern void glsCapture_glVertex4iv (const GLint *v);
extern void glsCapture_glVertex4sv (const GLshort *v);
extern void glsCapture_glVertexPointer (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
extern void glsCapture_glVertexPointerEXT (GLint size, GLenum type, GLsizei stride, GLsizei count, const GLvoid *pointer);
extern void glsCapture_glViewport (GLint x, GLint y, GLsizei width, GLsizei height);

/* GLS global commands */
extern void glsContext (GLint inContext);
extern void glsDeleteContext (GLint inContext);
extern GLint glsGenContext (void);
extern GLint* glsGetAllContexts (void);
extern GLSenum glsGetBinaryType (GLint inSwapCount);
extern GLint glsGetCommandi (GLSopcode inOpcode, GLSenum inAttrib);
extern GLint glsGetCurrentContext (void);
extern GLint glsGetEnumi (GLSenum inAPI, GLSenum inValue, GLSenum inAttrib);
extern GLSenum glsGetError (void);
extern GLint glsGetOpcodeCount (GLSenum inAPI);
extern const GLSopcode* glsGetOpcodes (GLSenum inAPI);
extern GLboolean glsIsContext (GLint inContext);

/* GLS immediate commands */
extern void glsAppendReadPrefix (const GLSchar *inPrefix);
extern GLboolean glsBeginCapture (const GLSchar *inStreamName, GLSenum inCaptureStreamType, GLint inWriteFlags);
extern void glsCallArray (GLSenum inExternStreamType, size_t inCount, const GLvoid *inArray);
extern void glsCaptureFlags (GLSopcode inOpcode, GLint inFlags);
extern void glsCaptureWrapFunc (GLSenum inAttrib, GLScaptureWrapFunc inFunc);
extern void glsChannel (GLSenum inAttrib, FILE *inChannel);
extern void glsCommandFunc (GLSenum inAttrib, GLSopcode inOpcode, GLSfunc inFunc);
extern GLSenum glsCopyStream (const GLSchar *inSource, const GLSchar *inDest, GLSenum inDestType, GLint inWriteFlags);
extern void glsDataPointer (GLvoid *inPointer);
extern void glsDeleteStream (const GLSchar *inName);
extern void glsDisable (GLSenum inAttrib);
extern void glsEnable (GLSenum inAttrib);
extern void glsEndCapture (void);
extern void glsFlush (void);
extern GLint glsGetCaptureFlags (GLSopcode inOpcode);
extern GLSfunc glsGetCommandFunc (GLSenum inAttrib, GLSopcode inOpcode);
extern const GLSchar* glsGetCommandName (GLSopcode inOpcode);
extern size_t glsGetCommandOffset (void);
extern GLSopcode glsGetCommandOpcode (const GLSchar *inName);
extern const GLSchar* glsGetEnumName (GLSenum inAPI, GLSenum inValue);
extern GLint glsGetEnumValue (GLSenum inAPI, const GLSchar *inName);
extern GLSfunc glsGetFunc (GLSenum inAttrib);
extern const GLSchar* glsGetHeaderc (GLSenum inAttrib);
extern GLfloat glsGetHeaderf (GLSenum inAttrib);
extern GLfloat* glsGetHeaderfv (GLSenum inAttrib, GLfloat *outVec);
extern GLint glsGetHeaderi (GLSenum inAttrib);
extern GLint* glsGetHeaderiv (GLSenum inAttrib, GLint *outVec);
extern const GLSchar* glsGetListc (GLSenum inAttrib, GLint inIndex);
extern GLint glsGetListi (GLSenum inAttrib, GLint inIndex);
extern GLSlong glsGetListl (GLSenum inAttrib, GLint inIndex);
extern GLvoid* glsGetPointer (GLSenum inAttrib);
extern size_t glsGetStreamSize (const GLSchar *inName);
extern const GLSchar* glsGetStreamc (GLSenum inAttrib, const GLSchar *inName);
extern GLint glsGetStreami (GLSenum inAttrib, const GLSchar *inName);
extern const GLSchar* glsGetc (GLSenum inAttrib);
extern GLint glsGeti (GLSenum inAttrib);
extern GLint* glsGetiv (GLSenum inAttrib, GLint *outVec);
extern GLboolean glsIsContextStream (const GLSchar *inName);
extern GLboolean glsIsEnabled (GLSenum inAttrib);
extern GLboolean glsIsExtensionSupported (const GLSchar *inExtension);
extern GLboolean glsIsVersionSupported (GLSenum inAPI, GLint inVersionMajor, GLint inVersionMinor);
extern void glsPrependReadPrefix (const GLSchar *inPrefix);
extern void glsReadFunc (GLSreadFunc inFunc);
extern void glsRemoveReadPrefix (GLint inIndex);
extern void glsResetAlignment (void);
extern void glsStringType (GLSenum inStringType);
extern void glsWriteFunc (GLSwriteFunc inFunc);
extern void glsWritePrefix (const GLSchar *inPrefix);

/* GLS encodable commands */
extern void glsBeginGLS (GLint inVersionMajor, GLint inVersionMinor);
extern void glsBlock (GLSenum inBlockType);
extern GLSenum glsCallStream (const GLSchar *inName);
extern void glsDrawVertexArray (GLenum inMode, GLenum inFormat, GLint inCount, const GLvoid *inArray);
extern void glsEndGLS (void);
extern void glsError (GLSopcode inOpcode, GLSenum inError);
extern void glsHeaderc (GLSenum inAttrib, const GLSchar *inString);
extern void glsHeaderf (GLSenum inAttrib, GLfloat inVal);
extern void glsHeaderfv (GLSenum inAttrib, const GLfloat *inVec);
extern void glsHeaderi (GLSenum inAttrib, GLint inVal);
extern void glsHeaderiv (GLSenum inAttrib, const GLint *inVec);
extern void glsRequireExtension (const GLSchar *inExtension);
extern void glsRequireVersion (GLSenum inAPI, GLint inVersionMajor, GLint inVersionMinor);
extern void glsUnsupportedCommand (const GLSchar *inCommand);

/* GLS encodable-nop commands */
extern void glsBeginObj (const GLSchar *inTag);
extern void glsComment (const GLSchar *inComment);
extern void glsEndObj (void);
extern void glsNumbv (const GLSchar *inTag, GLint inCount, const GLbyte *inVec);
extern void glsNumd (const GLSchar *inTag, GLdouble inVal);
extern void glsNumdv (const GLSchar *inTag, GLint inCount, const GLdouble *inVec);
extern void glsNumf (const GLSchar *inTag, GLfloat inVal);
extern void glsNumfv (const GLSchar *inTag, GLint inCount, const GLfloat *inVec);
extern void glsNumi (const GLSchar *inTag, GLint inVal);
extern void glsNumiv (const GLSchar *inTag, GLint inCount, const GLint *inVec);
extern void glsNuml (const GLSchar *inTag, GLSlong inVal);
extern void glsNumlv (const GLSchar *inTag, GLint inCount, const GLSlong *inVec);
extern void glsNumsv (const GLSchar *inTag, GLint inCount, const GLshort *inVec);
extern void glsPad (void);
extern void glsString (const GLSchar *inTag, const GLSchar *inString);
extern void glsSwapBuffers (void);

#if defined(__cplusplus)
    }
#endif /* defined(__cplusplus) */

#endif /* defined(__gls_h_) */
