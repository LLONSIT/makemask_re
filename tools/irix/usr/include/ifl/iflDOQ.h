#if 0
    Copyright 1997, Silicon Graphics, Inc.
    ALL RIGHTS RESERVED
 
    UNPUBLISHED -- Rights reserved under the copyright laws of the United
    States.   Use of a copyright notice is precautionary only and does not
    imply publication or disclosure.

    U.S. GOVERNMENT RESTRICTED RIGHTS LEGEND:
    Use, duplication or disclosure by the Government is subject to restrictions
    as set forth in FAR 52.227.19(c)(2) or subparagraph (c)(1)(ii) of the Rights    in Technical Data and Computer Software clause at DFARS 252.227-7013 and/or
    in similar or successor clauses in the FAR, or the DOD or NASA FAR
    Supplement.  Contractor/manufacturer is Silicon Graphics, Inc.,
    2011 N. Shoreline Blvd. Mountain View, CA 94039-7311.
 
    THE CONTENT OF THIS WORK CONTAINS CONFIDENTIAL AND PROPRIETARY
    INFORMATION OF SILICON GRAPHICS, INC. ANY DUPLICATION, MODIFICATION,
    DISTRIBUTION, OR DISCLOSURE IN ANY FORM, IN WHOLE, OR IN PART, IS STRICTLY
    PROHIBITED WITHOUT THE PRIOR EXPRESS WRITTEN PERMISSION OF SILICON
    GRAPHICS, INC.
#endif
#ifndef _iflDOQ_h_
#define _iflDOQ_h_
/*
    This file defines the getTag/setTag tag values supported by the
    DOQ image file format.

    The following quasi-prototypes illustrate the use of these tag values:

	getTag(iflFITextensionSize, int* extSize)
	
	    returns size of extension in bytes in 'extSize'
	    
	getTag(iflFITextensionData, void* extData, int length)

	    reads 'length' bytes of extension data into 'extData'

	setTag(iflFITextensionSize, int extSize)

	    sets size of extension in bytes to 'extSize', must be called
	    before any data is written to the file
*/

enum { 
    /* record 1 */
    iflDOQ_QuadrangleName		= 1,	/* char* */
    iflDOQ_Quadrant,				/* as follows */
	iflDOQ_QuadrantSW,
	iflDOQ_QuadrantNW,
	iflDOQ_QuadrantNE,
	iflDOQ_QuadrantSE,
    iflDOQ_Nation,				/* char*[2] */
    iflDOQ_State,				/* char*[4] */
    iflDOQ_State1County,			/* char*[5] */
    iflDOQ_State2County,			/* char*[5] */
    iflDOQ_State3County,			/* char*[5] */
    iflDOQ_State4County,			/* char*[5] */
    iflDOQ_Filler,				/* char* */
    iflDOQ_ProducerCode,			/* as follows */
	iflDOQ_ProducerCodeEMC,
	iflDOQ_ProducerCodeMCMC,
	iflDOQ_ProducerCodeWMC,
	iflDOQ_ProducerCodeRMMC,
	iflDOQ_ProducerCodeFS,
	iflDOQ_ProducerCodeBLM,
	iflDOQ_ProducerCodeSCS,
    iflDOQ_DataOrdering,			/* as follows */
	iflDOQ_DataOrderingNSWE,
	iflDOQ_DataOrderingWENS,
    iflDOQ_BandType,				/* as follows */
	iflDOQ_BandTypeL,				/* lum */
	iflDOQ_BandTypeR,				/* red */
	iflDOQ_BandTypeG,				/* green */
	iflDOQ_BandTypeB,				/* blue */
	iflDOQ_BandTypeRGB,				/* rgb */
	iflDOQ_BandTypeRGBL,				/* rgb + lum */
	iflDOQ_BandTypeLE,				/* lum + elev */
	iflDOQ_BandTypeRGBE,				/* rgb + elev */
	iflDOQ_BandTypeRGBLE,				/* rgb + lum + elev */
    iflDOQ_ElevStorage,				/* as follows */
	iflDOQ_ElevStorageNone,
	iflDOQ_ElevStorageByProfile,
	iflDOQ_ElevStorageByPixel,
    iflDOQ_BandStorage,				/* as follows */
	iflDOQ_BandStorageSeparate,
	iflDOQ_BandStorageSequential,
	iflDOQ_BandStorageBandInterleaved,
	iflDOQ_BandStorageLineInterleaved,
	iflDOQ_BandStoragePixelInterleaved,
    iflDOQ_VertDatum,				/* as follows */
	iflDOQ_VertDatumNone,
	iflDOQ_VertDatumLMSL,
	iflDOQ_VertDatumNGVD29,
	iflDOQ_VertDatumNAVD88,
    iflDOQ_PriHorizDatum,			/* as follows */
	iflDOQ_HorizDatumNAD27,
	iflDOQ_HorizDatumWGS72,
	iflDOQ_HorizDatumWGS84,
	iflDOQ_HorizDatumNAD83,
	iflDOQ_HorizDatumHawaii,
	iflDOQ_HorizDatumPR,
    iflDOQ_SecHorizDatum,			/* as above */
    iflDOQ_RotationAngle,			/* double */
    iflDOQ_GroundXYRefSys,			/* as follows */
	iflDOQ_GroundXYRefSysGeo,
	iflDOQ_GroundXYRefSysUTM,
	iflDOQ_GroundXYRefSysSPCS,
    iflDOQ_GroundZoneCode,			/* int */
    iflDOQ_GroundXYUnits,			/* as follows */
	iflDOQ_UnitsRadians,
	iflDOQ_UnitsFeet,
	iflDOQ_UnitsMeters,
	iflDOQ_UnitsArcSeconds,
    iflDOQ_SWPriGroundCoord,			/* double[2] */
    iflDOQ_NWPriGroundCoord,			/* double[2] */
    iflDOQ_NEPriGroundCoord,			/* double[2] */
    iflDOQ_SEPriGroundCoord,			/* double[2] */

    /* record 2 */
    iflDOQ_PriXformParm,			/* double[4] */
    iflDOQ_PriXformCentroid,			/* double[4] */
    iflDOQ_SWSecGroundCoord,			/* double[2] */
    iflDOQ_NWSecGroundCoord,			/* double[2] */
    iflDOQ_NESecGroundCoord,			/* double[2] */
    iflDOQ_SESecGroundCoord,			/* double[2] */

    /* record 3 */
    iflDOQ_SecXformParm,			/* double[4] */
    iflDOQ_SecXformCentroid,			/* double[4] */
    iflDOQ_SWIntNAD83Coord,			/* int[2] */
    iflDOQ_NWIntNAD83Coord,			/* int[2] */
    iflDOQ_NEIntNAD83Coord,			/* int[2] */
    iflDOQ_SEIntNAD83Coord,			/* int[2] */
    iflDOQ_SWIntSecCoord,			/* int[2] */
    iflDOQ_NWIntSecCoord,			/* int[2] */
    iflDOQ_NEIntSecCoord,			/* int[2] */
    iflDOQ_SEIntSecCoord,			/* int[2] */
    iflDOQ_Pixel1PriCoord,			/* double[2] */
    iflDOQ_Pixel1SecCoord,			/* double[2] */

    /* record 4 */
    iflDOQ_ElevationUnits,			/* see iflDOQ_Units above */
    iflDOQ_MinOrthoElevation,			/* double */
    iflDOQ_MaxOrthoElevation,			/* double */
    iflDOQ_GroundResolution,			/* double[3] */
    iflDOQ_PixelResolution,			/* double[3] */
    iflDOQ_MaxContourInterval,			/* int */
    iflDOQ_MaxContourIntervalUnits,		/* see iflDOQ_Units above */
    iflDOQ_MinContourInterval,			/* int */
    iflDOQ_MinContourIntervalUnits,		/* see iflDOQ_Units above */
    iflDOQ_SuspectAreasCode,			/* as follows */
	iflDOQ_SuspectAreasCodeNone,
	iflDOQ_SuspectAreasCodeSuspect,
	iflDOQ_SuspectAreasCodeVoid,
	iflDOQ_SuspectAreasCodeSuspectAndVoid,
    iflDOQ_HorizAccuracy,			/* double */
    iflDOQ_VertAccuracy,			/* double */
    iflDOQ_NumHorizPoints,			/* int */
    iflDOQ_ProcessingAlgorithm,			/* as follows */
	iflDOQ_ProcessingAlgorithmNearest,
	iflDOQ_ProcessingAlgorithmBilinear,
	iflDOQ_ProcessingAlgorithmCubicConv,
    iflDOQ_ProductionSystem,			/* char* */
    iflDOQ_ProductionDate,			/* char* */
    iflDOQ_FilmType,				/* char* */
    iflDOQ_SourcePhotoID,			/* char* */
    iflDOQ_MosaickedImage,			/* int */
    iflDOQ_LeafOffFlag,				/* char* */
    iflDOQ_SourcePhotoDate,			/* char* */
    iflDOQ_CameraFocalLength,			/* double */
    iflDOQ_SourcePhotoAlt,			/* int */
    iflDOQ_ScannerType,				/* char* */
    iflDOQ_ScanResolution,			/* double[2] */
    iflDOQ_ScannerSampleResolution,		/* double[2] */
    iflDOQ_RadiometricResolution,		/* as follows */
	iflDOQ_RadiometricResolution8,
	iflDOQ_RadiometricResolution16,
    iflDOQ_ResampledGroundResolution,		/* double */
    iflDOQ_CompressionFlag,			/* char* */
    iflDOQ_CompressedImageSize,			/* int */
    iflDOQ_CompressionAlgorithm,		/* char* */
    iflDOQ_CompressionType,			/* char* */
    iflDOQ_CompressionFactor			/* int */
};

#endif
