#ifndef __ufm_h_
#define __ufm_h_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* The API (Applications Programming Interface) for the SGI Universal Font  */
/* Manager (libufm). You can use this API to get data from those types of   */
/* font and font metric files which are supported by the SGI Universal Font */
/* Manager (UFM).                                                           */

/* UFM API Version Number: 1.0                                              */
#define UFM_MAJOR 1
#define UFM_MINOR 0

/*
 * Copyright 1991-1996 Silicon Graphics, Inc.
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Silicon Graphics, Inc.;
 * the contents of this file may not be disclosed to third parties, copied or 
 * duplicated in any form, in whole or in part, without the prior written
 * permission of Silicon Graphics, Inc.
 *
 * RESTRICTED RIGHTS LEGEND:
 * Use, duplication or disclosure by the Government is subject to restrictions 
 * as set forth in subdivision (c)(1)(ii) of the Rights in Technical Data
 * and Computer Software clause at DFARS 252.227-7013, and/or in similar or
 * successor clauses in the FAR, DOD or NASA FAR Supplement. Unpublished -
 * rights reserved under the Copyright Laws of the United States.
 */

#ifndef NULL
#define NULL 0L
#endif

/* UFM function return codes */
#define UFM_NO_ERROR                           0
#define UFM_ERROR                             -1
#define UFM_INVALID_ENUM                      -2
#define UFM_INVALID_VALUE                     -3
#define UFM_INVALID_NAME                      -4
#define UFM_OUT_OF_MEMORY                     -5
#define UFM_INVALID_DIRECTORY                 -6
#define UFM_PARSE_ERROR                       -7
#define UFM_EARLY_EOF                         -8

/* values for the argument charCodeType */
#define UFM_BYTE1                              0 
#define UFM_UCS2                               1 
#define UFM_UCS4                               2 
#define UFM_BYTE2                              3
#define UFM_BYTE4                              4
#define UFM_INT                                5

/* values of operators in exact character outlines */
#define UFM_MOVE                               1
#define UFM_LINE                               2
#define UFM_CURVE                              3
#define UFM_CLOSE                              4

/* types of values */
#define UFM_VALUE_CHAR                         1
#define UFM_VALUE_INT                          2
#define UFM_VALUE_FLOAT                        3

typedef union c_Code { /* character codes */
    unsigned char onebyte;   /* used for char codes of the type UFM_BYTE1   */
    unsigned short twobytes; /* used for UFM_UCS2 and UFM_BYTE2 char codes  */
    unsigned int fourbytes;  /* used for UFM_UCS4 and UFM_BYTE4 char codes  */
    int signedint;           /* used for char codes of the type UFM_INT     */
} cCode;

typedef struct ufm_Bitmap {
    char *charName;          /* character name or CID code                  */
    int charCodeType;        /* type of character code                      */
    union c_Code charCode;   /* character code                              */
    int typefaceIndex;       /* in which typeface was the character found   */
    int width;               /* character bitmap width in pixels            */
    int height;              /* character bitmap height in pixels           */
    float xOrig;             /* x coord. of the origin in bitmap image      */
    float yOrig;             /* y coord. of the origin in bitmap image      */
    float xMove;             /* move in the x direction after char drawn    */
    float yMove;             /* move in the y direction after char drawn    */
    float xMoveScalable;     /* scalable move in the x direction in em      */
    float yMoveScalable;     /* scalable move in the y direction in em      */
    unsigned char *bitmap;   /* character bitmap                            */
} ufmBitmap;

typedef struct ufm_CharMetrics { /* scalable character metrics in em        */
    int charCodeType;        /* type of character code                      */
    union c_Code charCode;   /* character code                              */
    int typefaceIndex;       /* in which typeface was the character found   */
    char *charName;          /* character name or CID code                  */
    float xMoveScalable;     /* scalable move in the x direction in em      */
    float yMoveScalable;     /* scalable move in the y direction in em      */
    float llxScalable;       /* bounding box: lower-left x coordinate       */
    float llyScalable;       /* bounding box: lower-left y coordinate       */
    float urxScalable;       /* bounding box: upper-right x coordinate      */
    float uryScalable;       /* bounding box: upper-right y coordinate      */
} ufmCharMetrics;

typedef union p_Value {
    char *charValue;         /* use when valueType is UFM_VALUE_CHAR        */
    int intValue;            /* use when valueType is UFM_VALUE_INT         */
    float floatValue;        /* use when valueType is UFM_VALUE_FLOAT       */
} pValue;

typedef struct ufm_KeyValue { /* key-value pair */
    char *key;               /* key                                         */
    int valueType;           /* type of value                               */
    union p_Value value;     /* value                                       */
} ufmKeyValue;

typedef struct ufm_Font {
    char *fontName;             /* font name                                */
    char *fileName;             /* file name                                */
    double matrix00;            /* element 00 of a 2x2 font matrix          */
    double matrix01;            /* element 01 of a 2x2 font matrix          */
    double matrix10;            /* element 10 of a 2x2 font matrix          */
    double matrix11;            /* element 11 of a 2x2 font matrix          */
    unsigned int nProperties;   /* number of properties                     */
    ufmKeyValue *properties;    /* properties                               */
    unsigned int nChars;        /* number of characters                     */
    int charCodeType;           /* type of character code                   */
    union c_Code firstCharCode; /* smallest (minimum) character code        */
    union c_Code lastCharCode;  /* largest (maximum) character code         */
} ufmFont;

typedef struct ufm_Point { 
    float x;
    float y;
} ufmPoint;

typedef struct ufm_ExactOutline {
    char *charName;          /* character name or CID code                  */
    int charCodeType;        /* type of character code                      */
    union c_Code charCode;   /* character code                              */
    int typefaceIndex;       /* in which typeface was the character found   */
    float llxScalable;       /* bounding box: lower-left x coordinate       */
    float llyScalable;       /* bounding box: lower-left y coordinate       */
    float urxScalable;       /* bounding box: upper-right x coordinate      */
    float uryScalable;       /* bounding box: upper-right y coordinate      */
    float xMoveScalable;     /* move in the x direction after char drawn    */
    float yMoveScalable;     /* move in the y direction after char drawn    */
    unsigned int nPaths;     /* number of paths in an outline               */
    unsigned int *nPoints;
    ufmPoint *points;
    unsigned int *nOperators;
    unsigned char *operators;
} ufmExactOutline;

typedef struct ufm_VectorOutline {
    char *charName;          /* character name or CID code                  */
    int charCodeType;        /* type of character code                      */
    union c_Code charCode;   /* character code                              */
    int typefaceIndex;       /* in which typeface was the character found   */
    float llxScalable;       /* bounding box: lower-left x coordinate       */
    float llyScalable;       /* bounding box: lower-left y coordinate       */
    float urxScalable;       /* bounding box: upper-right x coordinate      */
    float uryScalable;       /* bounding box: upper-right y coordinate      */
    float xMoveScalable;     /* move in the x direction after char drawn    */
    float yMoveScalable;     /* move in the y direction after char drawn    */
    unsigned int nPaths;     /* number of paths in an outline               */
    unsigned int *nPoints;
    ufmPoint *points;
} ufmVectorOutline;

typedef unsigned int ufmPropertiesMask;

/* bits for the typeface properties mask */
#define ufmFoundry                    (1<<0)
#define ufmFamilyName                 (1<<1)
#define ufmRelativeWeight             (1<<2)
#define ufmRelativeSlant              (1<<3)
#define ufmRelativeWidth              (1<<4)
#define ufmAddStyleName               (1<<5)
#define ufmSpacing                    (1<<6)
#define ufmCharsetRegistry            (1<<7)
#define ufmCharsetEncoding            (1<<8)
#define ufmAllProperties (ufmFoundry | ufmFamilyName | ufmRelativeWeight | ufmRelativeSlant | ufmRelativeWidth | ufmAddStyleName | ufmSpacing | ufmCharsetRegistry | ufmCharsetEncoding)

typedef struct ufm_TypefaceProps { /* typeface properties */
    char *foundry;         /* which company designed or prepared typeface   */
    char *familyName;      /* e.g., Helvetica                               */
    int relativeWeight;    /* 0=undefined, 10=ultralight, ..., 90=ultrabold */
    int relativeSlant;     /* 0=no slant, 1=slant, -1=polymorphic           */
    int relativeWidth;     /* 0=undefined, 10=ultracondensed, ...,          */
    char *addStyleName;    /* serif, sans, decorated, informal, etc.        */
    char *spacing;         /* p=proportional, m=monospaced, etc.            */
    char *charsetRegistry; /* for example: iso8859                          */
    char *charsetEncoding; /* for example: 1                                */
} ufmTypefaceProps;

typedef unsigned int ufmTypefaceMask;

/* bits for the typeface type mask */
#define ufmTypefaceBitmaps                     (1<<0)
#define ufmTypefaceOutlines                    (1<<1) 
#define ufmTypefaceScalableMetrics             (1<<2)
#define ufmTypefaceAll                         0

typedef struct ufm_Typeface {
    char *typefaceName;    /* typeface name                                 */
    ufmTypefaceProps *typefaceProps; /* typeface properties                 */
    unsigned int nPixelSizes;       
                           /* number of pixel sizes                         */
    int *pixelSizes;       /* pixel sizes                                   */
    ufmTypefaceMask typefaceMask; /* typeface mask                          */
} ufmTypeface;

typedef struct ufm_TypefaceMetrics { /* scalable typeface metrics in em     */
    char *typefaceName;       /* typeface name                              */
    float llxScalable;        /* bounding box: lower-left x coordinate      */
    float llyScalable;        /* bounding box: lower-left y coordinate      */
    float urxScalable;        /* bounding box: upper-right x coordinate     */
    float uryScalable;        /* bounding box: upper-right y coordinate     */
    float underlinePosition;  /* underline position                         */
    float underlineThickness; /* underline thickness                        */
    float italicAngle;        /* italic angle                               */
    int isFixedPitch;         /* fixed pitch or monospaced: 1=yes, 0=no     */
    unsigned int nChars;      /* number of characters                       */
    unsigned int nKeyValues;  /* number of key-value pairs                  */
    ufmKeyValue *keyValues;   /* key-value pairs                            */
} ufmTypefaceMetrics;

/* prototypes of the UFM functions */
extern int ufmCloseTypeface( /* close a typeface */
    unsigned int /* typefaceHandle */ 
);

extern void ufmFree( /* free an area of memory that was allocated by UFM */
    void * /* ufmPointer */
);

extern int ufmFreeBitmap( /* free character bitmaps */
    unsigned int /* nCharBitmaps */,
    ufmBitmap * /* charBitmaps */
);

extern int ufmFreeCharMetrics( /* free character metrics */
    unsigned int /* nCharMetrics */,
    ufmCharMetrics * /* charMetrics */
);

extern int ufmFreeExactOutline( /* free exact character outlines */
    unsigned int /* nOutlines */,
    ufmExactOutline * /* outlines */
);

extern int ufmFreeFontInfo( /* free font information */
    ufmFont * /* font */
);

extern int ufmFreeTypefaceInfo( /* free typeface information */
    ufmTypeface * /* typeface */
);

extern int ufmFreeTypefaceList( /* free a typeface list */
    unsigned int /* nTypefaces */,
    ufmTypeface * /* typefaces */
);

extern int ufmFreeTypefaceMetrics( /* free typeface metrics */
    ufmTypefaceMetrics * /* typefaceMetrics */
);

extern int ufmFreeVectorOutline( /* free vector character outlines */
    unsigned int /* nOutlines */,
    ufmVectorOutline * /* outlines */
);

/* get character bitmaps from a bitmap or outline font */
extern int ufmGetBitmap( /* get a character bitmap */
    unsigned int /* nTypefaceHandles */,  /* number of typeface handles     */
    unsigned int * /* typefaceHandles */, /* typeface handles               */
    int /* charCodeType */,               /* type of character code         */
    unsigned int /* nCharCodes */,        /* number of character codes      */
    void * /* charCodes */,               /* character code                 */
    int /* pixelSize */,                  /* size in pixels                 */
    float /* angle */,                    /* rotation angle in degrees @    */
    unsigned int * /* nCharBitmaps */,    /* RETURN                         */
    ufmBitmap ** /* charBitmaps */        /* RETURN                         */
);

/* get scalable character metrics from an AFM file by character code */
extern int ufmGetCharMetrics(
    unsigned int /* nTypefaceHandles */,  /* number of typeface handles     */
    unsigned int * /* typefaceHandles */, /* typeface handles               */
    int /* charCodeType */,               /* type of character code         */
    unsigned int /* nCharCodes */,        /* number of character codes      */
    void * /* charCodes */,               /* character codes                */
    unsigned int * /* nCharMetrics */,    /* RETURN                         */
    ufmCharMetrics ** /* charMetrics */   /* RETURN                         */
);

/* get scalable character metrics from an AFM file by character name or CID */
extern int ufmGetCharMetricsByName(
    unsigned int /* nTypefaceHandles */,  /* number of typeface handles     */
    unsigned int * /* typefaceHandles */, /* typeface handles               */
    unsigned int /* nCharNames */,        /* number of character names      */
    char ** /* charNames */,              /* character names or CID codes   */
    unsigned int * /* nCharMetrics */,    /* RETURN                         */
    ufmCharMetrics ** /* charMetrics */   /* RETURN                         */
);

/* get exact character outlines from an outline font */
extern int ufmGetExactOutline(
    unsigned int /* nTypefaceHandles */,  /* number of typeface handles     */
    unsigned int * /* typefaceHandles */, /* typeface handles               */
    int /* charCodeType */,               /* type of character code         */
    unsigned int /* nCharCodes */,        /* number of character codes      */
    void * /* charCodes */,               /* character codes                */
    unsigned int * /* nOutlines */,       /* RETURN                         */
    ufmExactOutline ** /* outlines */     /* RETURN                         */
);

extern int ufmGetFontInfo( /* get font information */
    unsigned int /* typefaceHandle */,    /* typeface handle                */
    int /* pixelSize */,                  /* pixel Size                     */
    ufmFont ** /* font */                 /* RETURN                         */
);

extern int ufmGetFontPath( /* get the current UFM font path */
    char ** /* fontPath */                /* RETURN                         */
);

/* get transformed character bitmaps from a bitmap or outline font */
extern int ufmGetTransformedBitmap( /* get a transformed character bitmap */
    unsigned int /* nTypefaceHandles */,  /* number of typeface handles     */
    unsigned int * /* typefaceHandles */, /* typeface handles               */
    int /* charCodeType */,               /* type of character code         */
    unsigned int /* nCharCodes */,        /* number of character codes      */
    void * /* charCodes */,               /* character code                 */
    float[4] /* transfMatrix */,          /* elements 00, 10, 01 and 11     */
    unsigned int * /* nCharBitmaps */,    /* RETURN                         */
    ufmBitmap ** /* charBitmaps */        /* RETURN                         */
);

extern int ufmGetTypefaceInfo( /* get typeface information */
    unsigned int /* typefaceHandle */,    /* typeface handle                */
    ufmTypeface ** /* typefaceInfo */     /* RETURN                         */
);

extern int ufmGetTypefaceList( /* get a list of typefaces */
    ufmPropertiesMask /* propertiesMask */, /* typeface properties mask     */
    ufmTypefaceProps * /* typefaceProps */, /* typeface properties          */
    ufmTypefaceMask /* typefaceMask */,     /* typeface type mask           */ 
    unsigned int * /* nTypefaces */,        /* RETURN                       */
    ufmTypeface ** /* typefaces */          /* RETURN                       */
);

extern int ufmGetTypefaceMetrics( /* get scalable typeface metrics */
    unsigned int /* typefaceHandle */,          /* typeface handle          */
    ufmTypefaceMetrics ** /* typefaceMetrics */ /* RETURN                   */
);

/* get vector character outlines from an outline font */
extern int ufmGetVectorOutline(
    unsigned int /* nTypefaceHandles */,  /* number of typeface handles     */
    unsigned int * /* typefaceHandles */, /* typeface handles               */
    int /* charCodeType */,               /* type of character code         */
    unsigned int /* nCharCodes */,        /* number of character codes      */
    void * /* charCodes */,               /* character codes                */
    float /* tolerance */,                /* approximation tolerance        */
    unsigned int * /* nOutlines */,       /* RETURN                         */
    ufmVectorOutline ** /* outlines */    /* RETURN                         */
);

extern int ufmGetVersion( /* get the version of UFM */
    int * /* major */,                    /* RETURN                         */
    int * /* minor */                     /* RETURN                         */
);

extern int ufmOpenTypeface( /* open a typeface */
    char * /* typefaceName */,     /* typeface name                         */
    unsigned int * /* typefaceHandle */   /* RETURN                         */
);

/* use the env. variable UFM_FONTPATH to change the default font path */
extern int ufmSetFontPath( /* set the UFM font path */
    char * /* fontPath */
);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __ufm_h_ */
