C
C  Copyright 1991-1993, Silicon Graphics, Inc.
C  All Rights Reserved.
C  
C  This is UNPUBLISHED PROPRIETARY SOURCE CODE of Silicon Graphics, Inc.;
C  the contents of this file may not be disclosed to third parties, copied or
C  duplicated in any form, in whole or in part, without the prior written
C  permission of Silicon Graphics, Inc.
C  
C  RESTRICTED RIGHTS LEGEND:
C  Use, duplication or disclosure by the Government is subject to restrictions
C  as set forth in subdivision (c)(1)(ii) of the Rights in Technical Data
C  and Computer Software clause at DFARS 252.227-7013, and/or in similar or
C  successor clauses in the FAR, DOD or NASA FAR Supplement. Unpublished -
C  rights reserved under the Copyright Laws of the United States.
C


C ***********************************************************

C  Extensions 
       integer*4   GLU_EXT_object_space_tess
       parameter ( GLU_EXT_object_space_tess = 1 )
       integer*4   GLU_EXT_nurbs_tessellator
       parameter ( GLU_EXT_nurbs_tessellator = 1 )

C  Boolean 
       integer*4   GLU_FALSE
       parameter ( GLU_FALSE = 0 )
       integer*4   GLU_TRUE
       parameter ( GLU_TRUE = 1 )

C  Version 
       integer*4   GLU_VERSION_1_1
       parameter ( GLU_VERSION_1_1 = 1 )
       integer*4   GLU_VERSION_1_2
       parameter ( GLU_VERSION_1_2 = 1 )
       integer*4   GLU_VERSION_1_3
       parameter ( GLU_VERSION_1_3 = 1 )

C  StringName 
       integer*4   GLU_VERSION
       parameter ( GLU_VERSION = 100800 )
       integer*4   GLU_EXTENSIONS
       parameter ( GLU_EXTENSIONS = 100801 )

C  ErrorCode 
       integer*4   GLU_INVALID_ENUM
       parameter ( GLU_INVALID_ENUM = 100900 )
       integer*4   GLU_INVALID_VALUE
       parameter ( GLU_INVALID_VALUE = 100901 )
       integer*4   GLU_OUT_OF_MEMORY
       parameter ( GLU_OUT_OF_MEMORY = 100902 )
       integer*4   GLU_INVALID_OPERATION
       parameter ( GLU_INVALID_OPERATION = 100904 )

C  Filter4TypeSGIS 
       integer*4   GLU_LAGRANGIAN_SGI
       parameter ( GLU_LAGRANGIAN_SGI = 100300 )
       integer*4   GLU_MITCHELL_NETRAVALI_SGI
       parameter ( GLU_MITCHELL_NETRAVALI_SGI = 100301 )

C  NurbsDisplay 
C       GLU_FILL 
       integer*4   GLU_OUTLINE_POLYGON
       parameter ( GLU_OUTLINE_POLYGON = 100240 )
       integer*4   GLU_OUTLINE_PATCH
       parameter ( GLU_OUTLINE_PATCH = 100241 )

C  NurbsCallback 
       integer*4   GLU_NURBS_ERROR
       parameter ( GLU_NURBS_ERROR = 100103 )
       integer*4   GLU_ERROR
       parameter ( GLU_ERROR = 100103 )
       integer*4   GLU_NURBS_BEGIN
       parameter ( GLU_NURBS_BEGIN = 100164 )
       integer*4   GLU_NURBS_BEGIN_EXT
       parameter ( GLU_NURBS_BEGIN_EXT = 100164 )
       integer*4   GLU_NURBS_VERTEX
       parameter ( GLU_NURBS_VERTEX = 100165 )
       integer*4   GLU_NURBS_VERTEX_EXT
       parameter ( GLU_NURBS_VERTEX_EXT = 100165 )
       integer*4   GLU_NURBS_NORMAL
       parameter ( GLU_NURBS_NORMAL = 100166 )
       integer*4   GLU_NURBS_NORMAL_EXT
       parameter ( GLU_NURBS_NORMAL_EXT = 100166 )
       integer*4   GLU_NURBS_COLOR
       parameter ( GLU_NURBS_COLOR = 100167 )
       integer*4   GLU_NURBS_COLOR_EXT
       parameter ( GLU_NURBS_COLOR_EXT = 100167 )
       integer*4   GLU_NURBS_TEXTURE_COORD
       parameter ( GLU_NURBS_TEXTURE_COORD = 100168 )
       integer*4   GLU_NURBS_TEXTURE_COORD_EXT
       parameter ( GLU_NURBS_TEXTURE_COORD_EXT = 100168 )
       integer*4   GLU_NURBS_END
       parameter ( GLU_NURBS_END = 100169 )
       integer*4   GLU_NURBS_END_EXT
       parameter ( GLU_NURBS_END_EXT = 100169 )
       integer*4   GLU_NURBS_BEGIN_DATA
       parameter ( GLU_NURBS_BEGIN_DATA = 100170 )
       integer*4   GLU_NURBS_BEGIN_DATA_EXT
       parameter ( GLU_NURBS_BEGIN_DATA_EXT = 100170 )
       integer*4   GLU_NURBS_VERTEX_DATA
       parameter ( GLU_NURBS_VERTEX_DATA = 100171 )
       integer*4   GLU_NURBS_VERTEX_DATA_EXT
       parameter ( GLU_NURBS_VERTEX_DATA_EXT = 100171 )
       integer*4   GLU_NURBS_NORMAL_DATA
       parameter ( GLU_NURBS_NORMAL_DATA = 100172 )
       integer*4   GLU_NURBS_NORMAL_DATA_EXT
       parameter ( GLU_NURBS_NORMAL_DATA_EXT = 100172 )
       integer*4   GLU_NURBS_COLOR_DATA
       parameter ( GLU_NURBS_COLOR_DATA = 100173 )
       integer*4   GLU_NURBS_COLOR_DATA_EXT
       parameter ( GLU_NURBS_COLOR_DATA_EXT = 100173 )
       integer*4   GLU_NURBS_TEXTURE_COORD_DATA
       parameter ( GLU_NURBS_TEXTURE_COORD_DATA = 100174 )
       integer*4   GLU_NURBS_TEXTURE_COORD_DATA_EXT
       parameter ( GLU_NURBS_TEXTURE_COORD_DATA_EXT = 100174 )
       integer*4   GLU_NURBS_END_DATA
       parameter ( GLU_NURBS_END_DATA = 100175 )
       integer*4   GLU_NURBS_END_DATA_EXT
       parameter ( GLU_NURBS_END_DATA_EXT = 100175 )

C  NurbsError 
       integer*4   GLU_NURBS_ERROR1
       parameter ( GLU_NURBS_ERROR1 = 100251 )
       integer*4   GLU_NURBS_ERROR2
       parameter ( GLU_NURBS_ERROR2 = 100252 )
       integer*4   GLU_NURBS_ERROR3
       parameter ( GLU_NURBS_ERROR3 = 100253 )
       integer*4   GLU_NURBS_ERROR4
       parameter ( GLU_NURBS_ERROR4 = 100254 )
       integer*4   GLU_NURBS_ERROR5
       parameter ( GLU_NURBS_ERROR5 = 100255 )
       integer*4   GLU_NURBS_ERROR6
       parameter ( GLU_NURBS_ERROR6 = 100256 )
       integer*4   GLU_NURBS_ERROR7
       parameter ( GLU_NURBS_ERROR7 = 100257 )
       integer*4   GLU_NURBS_ERROR8
       parameter ( GLU_NURBS_ERROR8 = 100258 )
       integer*4   GLU_NURBS_ERROR9
       parameter ( GLU_NURBS_ERROR9 = 100259 )
       integer*4   GLU_NURBS_ERROR10
       parameter ( GLU_NURBS_ERROR10 = 100260 )
       integer*4   GLU_NURBS_ERROR11
       parameter ( GLU_NURBS_ERROR11 = 100261 )
       integer*4   GLU_NURBS_ERROR12
       parameter ( GLU_NURBS_ERROR12 = 100262 )
       integer*4   GLU_NURBS_ERROR13
       parameter ( GLU_NURBS_ERROR13 = 100263 )
       integer*4   GLU_NURBS_ERROR14
       parameter ( GLU_NURBS_ERROR14 = 100264 )
       integer*4   GLU_NURBS_ERROR15
       parameter ( GLU_NURBS_ERROR15 = 100265 )
       integer*4   GLU_NURBS_ERROR16
       parameter ( GLU_NURBS_ERROR16 = 100266 )
       integer*4   GLU_NURBS_ERROR17
       parameter ( GLU_NURBS_ERROR17 = 100267 )
       integer*4   GLU_NURBS_ERROR18
       parameter ( GLU_NURBS_ERROR18 = 100268 )
       integer*4   GLU_NURBS_ERROR19
       parameter ( GLU_NURBS_ERROR19 = 100269 )
       integer*4   GLU_NURBS_ERROR20
       parameter ( GLU_NURBS_ERROR20 = 100270 )
       integer*4   GLU_NURBS_ERROR21
       parameter ( GLU_NURBS_ERROR21 = 100271 )
       integer*4   GLU_NURBS_ERROR22
       parameter ( GLU_NURBS_ERROR22 = 100272 )
       integer*4   GLU_NURBS_ERROR23
       parameter ( GLU_NURBS_ERROR23 = 100273 )
       integer*4   GLU_NURBS_ERROR24
       parameter ( GLU_NURBS_ERROR24 = 100274 )
       integer*4   GLU_NURBS_ERROR25
       parameter ( GLU_NURBS_ERROR25 = 100275 )
       integer*4   GLU_NURBS_ERROR26
       parameter ( GLU_NURBS_ERROR26 = 100276 )
       integer*4   GLU_NURBS_ERROR27
       parameter ( GLU_NURBS_ERROR27 = 100277 )
       integer*4   GLU_NURBS_ERROR28
       parameter ( GLU_NURBS_ERROR28 = 100278 )
       integer*4   GLU_NURBS_ERROR29
       parameter ( GLU_NURBS_ERROR29 = 100279 )
       integer*4   GLU_NURBS_ERROR30
       parameter ( GLU_NURBS_ERROR30 = 100280 )
       integer*4   GLU_NURBS_ERROR31
       parameter ( GLU_NURBS_ERROR31 = 100281 )
       integer*4   GLU_NURBS_ERROR32
       parameter ( GLU_NURBS_ERROR32 = 100282 )
       integer*4   GLU_NURBS_ERROR33
       parameter ( GLU_NURBS_ERROR33 = 100283 )
       integer*4   GLU_NURBS_ERROR34
       parameter ( GLU_NURBS_ERROR34 = 100284 )
       integer*4   GLU_NURBS_ERROR35
       parameter ( GLU_NURBS_ERROR35 = 100285 )
       integer*4   GLU_NURBS_ERROR36
       parameter ( GLU_NURBS_ERROR36 = 100286 )
       integer*4   GLU_NURBS_ERROR37
       parameter ( GLU_NURBS_ERROR37 = 100287 )

C  NurbsProperty 
       integer*4   GLU_AUTO_LOAD_MATRIX
       parameter ( GLU_AUTO_LOAD_MATRIX = 100200 )
       integer*4   GLU_CULLING
       parameter ( GLU_CULLING = 100201 )
       integer*4   GLU_SAMPLING_TOLERANCE
       parameter ( GLU_SAMPLING_TOLERANCE = 100203 )
       integer*4   GLU_DISPLAY_MODE
       parameter ( GLU_DISPLAY_MODE = 100204 )
       integer*4   GLU_PARAMETRIC_TOLERANCE
       parameter ( GLU_PARAMETRIC_TOLERANCE = 100202 )
       integer*4   GLU_SAMPLING_METHOD
       parameter ( GLU_SAMPLING_METHOD = 100205 )
       integer*4   GLU_U_STEP
       parameter ( GLU_U_STEP = 100206 )
       integer*4   GLU_V_STEP
       parameter ( GLU_V_STEP = 100207 )
       integer*4   GLU_NURBS_MODE
       parameter ( GLU_NURBS_MODE = 100160 )
       integer*4   GLU_NURBS_MODE_EXT
       parameter ( GLU_NURBS_MODE_EXT = 100160 )
       integer*4   GLU_NURBS_TESSELLATOR
       parameter ( GLU_NURBS_TESSELLATOR = 100161 )
       integer*4   GLU_NURBS_TESSELLATOR_EXT
       parameter ( GLU_NURBS_TESSELLATOR_EXT = 100161 )
       integer*4   GLU_NURBS_RENDERER
       parameter ( GLU_NURBS_RENDERER = 100162 )
       integer*4   GLU_NURBS_RENDERER_EXT
       parameter ( GLU_NURBS_RENDERER_EXT = 100162 )

C  NurbsSampling 
       integer*4   GLU_OBJECT_PARAMETRIC_ERROR
       parameter ( GLU_OBJECT_PARAMETRIC_ERROR = 100208 )
       integer*4   GLU_OBJECT_PARAMETRIC_ERROR_EXT
       parameter ( GLU_OBJECT_PARAMETRIC_ERROR_EXT = 100208 )
       integer*4   GLU_OBJECT_PATH_LENGTH
       parameter ( GLU_OBJECT_PATH_LENGTH = 100209 )
       integer*4   GLU_OBJECT_PATH_LENGTH_EXT
       parameter ( GLU_OBJECT_PATH_LENGTH_EXT = 100209 )
       integer*4   GLU_PATH_LENGTH
       parameter ( GLU_PATH_LENGTH = 100215 )
       integer*4   GLU_PARAMETRIC_ERROR
       parameter ( GLU_PARAMETRIC_ERROR = 100216 )
       integer*4   GLU_DOMAIN_DISTANCE
       parameter ( GLU_DOMAIN_DISTANCE = 100217 )

C  NurbsTrim 
       integer*4   GLU_MAP1_TRIM_2
       parameter ( GLU_MAP1_TRIM_2 = 100210 )
       integer*4   GLU_MAP1_TRIM_3
       parameter ( GLU_MAP1_TRIM_3 = 100211 )

C  QuadricDrawStyle 
       integer*4   GLU_POINT
       parameter ( GLU_POINT = 100010 )
       integer*4   GLU_LINE
       parameter ( GLU_LINE = 100011 )
       integer*4   GLU_FILL
       parameter ( GLU_FILL = 100012 )
       integer*4   GLU_SILHOUETTE
       parameter ( GLU_SILHOUETTE = 100013 )

C  QuadricCallback 
C       GLU_ERROR 

C  QuadricNormal 
       integer*4   GLU_SMOOTH
       parameter ( GLU_SMOOTH = 100000 )
       integer*4   GLU_FLAT
       parameter ( GLU_FLAT = 100001 )
       integer*4   GLU_NONE
       parameter ( GLU_NONE = 100002 )

C  QuadricOrientation 
       integer*4   GLU_OUTSIDE
       parameter ( GLU_OUTSIDE = 100020 )
       integer*4   GLU_INSIDE
       parameter ( GLU_INSIDE = 100021 )

C  TessCallback 
       integer*4   GLU_TESS_BEGIN
       parameter ( GLU_TESS_BEGIN = 100100 )
       integer*4   GLU_BEGIN
       parameter ( GLU_BEGIN = 100100 )
       integer*4   GLU_TESS_VERTEX
       parameter ( GLU_TESS_VERTEX = 100101 )
       integer*4   GLU_VERTEX
       parameter ( GLU_VERTEX = 100101 )
       integer*4   GLU_TESS_END
       parameter ( GLU_TESS_END = 100102 )
       integer*4   GLU_END
       parameter ( GLU_END = 100102 )
       integer*4   GLU_TESS_ERROR
       parameter ( GLU_TESS_ERROR = 100103 )
       integer*4   GLU_TESS_EDGE_FLAG
       parameter ( GLU_TESS_EDGE_FLAG = 100104 )
       integer*4   GLU_EDGE_FLAG
       parameter ( GLU_EDGE_FLAG = 100104 )
       integer*4   GLU_TESS_COMBINE
       parameter ( GLU_TESS_COMBINE = 100105 )
       integer*4   GLU_TESS_BEGIN_DATA
       parameter ( GLU_TESS_BEGIN_DATA = 100106 )
       integer*4   GLU_TESS_VERTEX_DATA
       parameter ( GLU_TESS_VERTEX_DATA = 100107 )
       integer*4   GLU_TESS_END_DATA
       parameter ( GLU_TESS_END_DATA = 100108 )
       integer*4   GLU_TESS_ERROR_DATA
       parameter ( GLU_TESS_ERROR_DATA = 100109 )
       integer*4   GLU_TESS_EDGE_FLAG_DATA
       parameter ( GLU_TESS_EDGE_FLAG_DATA = 100110 )
       integer*4   GLU_TESS_COMBINE_DATA
       parameter ( GLU_TESS_COMBINE_DATA = 100111 )

C  TessContour 
       integer*4   GLU_CW
       parameter ( GLU_CW = 100120 )
       integer*4   GLU_CCW
       parameter ( GLU_CCW = 100121 )
       integer*4   GLU_INTERIOR
       parameter ( GLU_INTERIOR = 100122 )
       integer*4   GLU_EXTERIOR
       parameter ( GLU_EXTERIOR = 100123 )
       integer*4   GLU_UNKNOWN
       parameter ( GLU_UNKNOWN = 100124 )

C  TessProperty 
       integer*4   GLU_TESS_WINDING_RULE
       parameter ( GLU_TESS_WINDING_RULE = 100140 )
       integer*4   GLU_TESS_BOUNDARY_ONLY
       parameter ( GLU_TESS_BOUNDARY_ONLY = 100141 )
       integer*4   GLU_TESS_TOLERANCE
       parameter ( GLU_TESS_TOLERANCE = 100142 )

C  TessError 
       integer*4   GLU_TESS_ERROR1
       parameter ( GLU_TESS_ERROR1 = 100151 )
       integer*4   GLU_TESS_ERROR2
       parameter ( GLU_TESS_ERROR2 = 100152 )
       integer*4   GLU_TESS_ERROR3
       parameter ( GLU_TESS_ERROR3 = 100153 )
       integer*4   GLU_TESS_ERROR4
       parameter ( GLU_TESS_ERROR4 = 100154 )
       integer*4   GLU_TESS_ERROR5
       parameter ( GLU_TESS_ERROR5 = 100155 )
       integer*4   GLU_TESS_ERROR6
       parameter ( GLU_TESS_ERROR6 = 100156 )
       integer*4   GLU_TESS_ERROR7
       parameter ( GLU_TESS_ERROR7 = 100157 )
       integer*4   GLU_TESS_ERROR8
       parameter ( GLU_TESS_ERROR8 = 100158 )
       integer*4   GLU_TESS_MISSING_BEGIN_POLYGON
       parameter ( GLU_TESS_MISSING_BEGIN_POLYGON = 100151 )
       integer*4   GLU_TESS_MISSING_BEGIN_CONTOUR
       parameter ( GLU_TESS_MISSING_BEGIN_CONTOUR = 100152 )
       integer*4   GLU_TESS_MISSING_END_POLYGON
       parameter ( GLU_TESS_MISSING_END_POLYGON = 100153 )
       integer*4   GLU_TESS_MISSING_END_CONTOUR
       parameter ( GLU_TESS_MISSING_END_CONTOUR = 100154 )
       integer*4   GLU_TESS_COORD_TOO_LARGE
       parameter ( GLU_TESS_COORD_TOO_LARGE = 100155 )
       integer*4   GLU_TESS_NEED_COMBINE_CALLBACK
       parameter ( GLU_TESS_NEED_COMBINE_CALLBACK = 100156 )

C  TessWinding 
       integer*4   GLU_TESS_WINDING_ODD
       parameter ( GLU_TESS_WINDING_ODD = 100130 )
       integer*4   GLU_TESS_WINDING_NONZERO
       parameter ( GLU_TESS_WINDING_NONZERO = 100131 )
       integer*4   GLU_TESS_WINDING_POSITIVE
       parameter ( GLU_TESS_WINDING_POSITIVE = 100132 )
       integer*4   GLU_TESS_WINDING_NEGATIVE
       parameter ( GLU_TESS_WINDING_NEGATIVE = 100133 )
       integer*4   GLU_TESS_WINDING_ABS_GEQ_TWO
       parameter ( GLU_TESS_WINDING_ABS_GEQ_TWO = 100134 )

C ***********************************************************


       character*128       fgluErrorString
       character*128       fgluGetString
       integer*4           fgluBuild1DMipmapLevels
       integer*4           fgluBuild1DMipmaps
       integer*4           fgluBuild2DMipmapLevels
       integer*4           fgluBuild2DMipmaps
       integer*4           fgluBuild3DMipmapLevels
       integer*4           fgluBuild3DMipmaps
       integer*4           fgluProject
       integer*4           fgluScaleImage
       integer*4           fgluTexFilterFuncSGI
       integer*4           fgluUnProject
       integer*4           fgluUnProject4
       logical*1           fgluCheckExtension
       logical*4           fgluNewNurbsRenderer
       logical*4           fgluNewQuadric
       logical*4           fgluNewTess
