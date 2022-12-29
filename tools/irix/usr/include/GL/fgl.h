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
       integer*4   GL_VERSION_1_1
       parameter ( GL_VERSION_1_1 = 1 )
       integer*4   GL_VERSION_1_2
       parameter ( GL_VERSION_1_2 = 1 )
       integer*4   GL_VERSION_1_3
       parameter ( GL_VERSION_1_3 = 1 )
       integer*4   GL_VERSION_1_4
       parameter ( GL_VERSION_1_4 = 1 )
       integer*4   GL_ARB_imaging
       parameter ( GL_ARB_imaging = 1 )
       integer*4   GL_EXT_abgr
       parameter ( GL_EXT_abgr = 1 )
       integer*4   GL_EXT_blend_color
       parameter ( GL_EXT_blend_color = 1 )
       integer*4   GL_EXT_blend_logic_op
       parameter ( GL_EXT_blend_logic_op = 1 )
       integer*4   GL_EXT_blend_minmax
       parameter ( GL_EXT_blend_minmax = 1 )
       integer*4   GL_EXT_blend_subtract
       parameter ( GL_EXT_blend_subtract = 1 )
       integer*4   GL_EXT_cmyka
       parameter ( GL_EXT_cmyka = 1 )
       integer*4   GL_EXT_convolution
       parameter ( GL_EXT_convolution = 1 )
       integer*4   GL_EXT_copy_texture
       parameter ( GL_EXT_copy_texture = 1 )
       integer*4   GL_EXT_histogram
       parameter ( GL_EXT_histogram = 1 )
       integer*4   GL_EXT_packed_pixels
       parameter ( GL_EXT_packed_pixels = 1 )
       integer*4   GL_EXT_point_parameters
       parameter ( GL_EXT_point_parameters = 1 )
       integer*4   GL_EXT_polygon_offset
       parameter ( GL_EXT_polygon_offset = 1 )
       integer*4   GL_EXT_rescale_normal
       parameter ( GL_EXT_rescale_normal = 1 )
       integer*4   GL_EXT_shared_texture_palette
       parameter ( GL_EXT_shared_texture_palette = 1 )
       integer*4   GL_EXT_subtexture
       parameter ( GL_EXT_subtexture = 1 )
       integer*4   GL_EXT_texture
       parameter ( GL_EXT_texture = 1 )
       integer*4   GL_EXT_texture3D
       parameter ( GL_EXT_texture3D = 1 )
       integer*4   GL_EXT_texture_object
       parameter ( GL_EXT_texture_object = 1 )
       integer*4   GL_EXT_vertex_array
       parameter ( GL_EXT_vertex_array = 1 )
       integer*4   GL_SGIS_detail_texture
       parameter ( GL_SGIS_detail_texture = 1 )
       integer*4   GL_SGIS_fog_function
       parameter ( GL_SGIS_fog_function = 1 )
       integer*4   GL_SGIS_generate_mipmap
       parameter ( GL_SGIS_generate_mipmap = 1 )
       integer*4   GL_SGIS_multisample
       parameter ( GL_SGIS_multisample = 1 )
       integer*4   GL_SGIS_pixel_texture
       parameter ( GL_SGIS_pixel_texture = 1 )
       integer*4   GL_SGIS_point_line_texgen
       parameter ( GL_SGIS_point_line_texgen = 1 )
       integer*4   GL_SGIS_point_parameters
       parameter ( GL_SGIS_point_parameters = 1 )
       integer*4   GL_SGIS_sharpen_texture
       parameter ( GL_SGIS_sharpen_texture = 1 )
       integer*4   GL_SGIS_texture4D
       parameter ( GL_SGIS_texture4D = 1 )
       integer*4   GL_SGIS_texture_border_clamp
       parameter ( GL_SGIS_texture_border_clamp = 1 )
       integer*4   GL_SGIS_texture_color_mask
       parameter ( GL_SGIS_texture_color_mask = 1 )
       integer*4   GL_SGIS_texture_edge_clamp
       parameter ( GL_SGIS_texture_edge_clamp = 1 )
       integer*4   GL_SGIS_texture_filter4
       parameter ( GL_SGIS_texture_filter4 = 1 )
       integer*4   GL_SGIS_texture_lod
       parameter ( GL_SGIS_texture_lod = 1 )
       integer*4   GL_SGIS_texture_select
       parameter ( GL_SGIS_texture_select = 1 )
       integer*4   GL_SGIX_async
       parameter ( GL_SGIX_async = 1 )
       integer*4   GL_SGIX_async_histogram
       parameter ( GL_SGIX_async_histogram = 1 )
       integer*4   GL_SGIX_async_pixel
       parameter ( GL_SGIX_async_pixel = 1 )
       integer*4   GL_SGIX_blend_alpha_minmax
       parameter ( GL_SGIX_blend_alpha_minmax = 1 )
       integer*4   GL_SGIX_calligraphic_fragment
       parameter ( GL_SGIX_calligraphic_fragment = 1 )
       integer*4   GL_SGIX_clipmap
       parameter ( GL_SGIX_clipmap = 1 )
       integer*4   GL_SGIX_convolution_accuracy
       parameter ( GL_SGIX_convolution_accuracy = 1 )
       integer*4   GL_SGIX_depth_texture
       parameter ( GL_SGIX_depth_texture = 1 )
       integer*4   GL_SGIX_flush_raster
       parameter ( GL_SGIX_flush_raster = 1 )
       integer*4   GL_SGIX_fog_offset
       parameter ( GL_SGIX_fog_offset = 1 )
       integer*4   GL_SGIX_fragment_lighting
       parameter ( GL_SGIX_fragment_lighting = 1 )
       integer*4   GL_SGIX_framezoom
       parameter ( GL_SGIX_framezoom = 1 )
       integer*4   GL_SGIX_icc_texture
       parameter ( GL_SGIX_icc_texture = 1 )
       integer*4   GL_SGIX_impact_pixel_texture
       parameter ( GL_SGIX_impact_pixel_texture = 1 )
       integer*4   GL_SGIX_instruments
       parameter ( GL_SGIX_instruments = 1 )
       integer*4   GL_SGIX_interlace
       parameter ( GL_SGIX_interlace = 1 )
       integer*4   GL_SGIX_ir_instrument1
       parameter ( GL_SGIX_ir_instrument1 = 1 )
       integer*4   GL_SGIX_list_priority
       parameter ( GL_SGIX_list_priority = 1 )
       integer*4   GL_SGIX_pixel_texture
       parameter ( GL_SGIX_pixel_texture = 1 )
       integer*4   GL_SGIX_pixel_tiles
       parameter ( GL_SGIX_pixel_tiles = 1 )
       integer*4   GL_SGIX_polynomial_ffd
       parameter ( GL_SGIX_polynomial_ffd = 1 )
       integer*4   GL_SGIX_reference_plane
       parameter ( GL_SGIX_reference_plane = 1 )
       integer*4   GL_SGIX_resample
       parameter ( GL_SGIX_resample = 1 )
       integer*4   GL_SGIX_scalebias_hint
       parameter ( GL_SGIX_scalebias_hint = 1 )
       integer*4   GL_SGIX_shadow
       parameter ( GL_SGIX_shadow = 1 )
       integer*4   GL_SGIX_shadow_ambient
       parameter ( GL_SGIX_shadow_ambient = 1 )
       integer*4   GL_SGIX_sprite
       parameter ( GL_SGIX_sprite = 1 )
       integer*4   GL_SGIX_subsample
       parameter ( GL_SGIX_subsample = 1 )
       integer*4   GL_SGIX_tag_sample_buffer
       parameter ( GL_SGIX_tag_sample_buffer = 1 )
       integer*4   GL_SGIX_texture_add_env
       parameter ( GL_SGIX_texture_add_env = 1 )
       integer*4   GL_SGIX_texture_coordinate_clamp
       parameter ( GL_SGIX_texture_coordinate_clamp = 1 )
       integer*4   GL_SGIX_texture_lod_bias
       parameter ( GL_SGIX_texture_lod_bias = 1 )
       integer*4   GL_SGIX_texture_multi_buffer
       parameter ( GL_SGIX_texture_multi_buffer = 1 )
       integer*4   GL_SGIX_texture_scale_bias
       parameter ( GL_SGIX_texture_scale_bias = 1 )
       integer*4   GL_SGIX_vertex_preclip
       parameter ( GL_SGIX_vertex_preclip = 1 )
       integer*4   GL_SGIX_ycrcb
       parameter ( GL_SGIX_ycrcb = 1 )
       integer*4   GL_SGI_color_matrix
       parameter ( GL_SGI_color_matrix = 1 )
       integer*4   GL_SGI_color_table
       parameter ( GL_SGI_color_table = 1 )
       integer*4   GL_SGI_texture_color_table
       parameter ( GL_SGI_texture_color_table = 1 )
       integer*4   GL_ARB_multitexture
       parameter ( GL_ARB_multitexture = 1 )
       integer*4   GL_ARB_transpose_matrix
       parameter ( GL_ARB_transpose_matrix = 1 )
       integer*4   GL_ARB_multisample
       parameter ( GL_ARB_multisample = 1 )
       integer*4   GL_ARB_texture_env_add
       parameter ( GL_ARB_texture_env_add = 1 )
       integer*4   GL_ARB_texture_cube_map
       parameter ( GL_ARB_texture_cube_map = 1 )
       integer*4   GL_ARB_texture_compression
       parameter ( GL_ARB_texture_compression = 1 )
       integer*4   GL_ARB_texture_border_clamp
       parameter ( GL_ARB_texture_border_clamp = 1 )
       integer*4   GL_ARB_point_parameters
       parameter ( GL_ARB_point_parameters = 1 )
       integer*4   GL_ARB_vertex_blend
       parameter ( GL_ARB_vertex_blend = 1 )
       integer*4   GL_ARB_texture_env_combine
       parameter ( GL_ARB_texture_env_combine = 1 )
       integer*4   GL_ARB_texture_env_crossbar
       parameter ( GL_ARB_texture_env_crossbar = 1 )
       integer*4   GL_ARB_texture_env_dot3
       parameter ( GL_ARB_texture_env_dot3 = 1 )
       integer*4   GL_ARB_depth_texture
       parameter ( GL_ARB_depth_texture = 1 )
       integer*4   GL_ARB_shadow
       parameter ( GL_ARB_shadow = 1 )
       integer*4   GL_ARB_shadow_ambient
       parameter ( GL_ARB_shadow_ambient = 1 )
       integer*4   GL_ARB_window_pos
       parameter ( GL_ARB_window_pos = 1 )
       integer*4   GL_ARB_vertex_program
       parameter ( GL_ARB_vertex_program = 1 )
       integer*4   GL_ARB_fragment_program
       parameter ( GL_ARB_fragment_program = 1 )
       integer*4   GL_EXT_texture_cube_map
       parameter ( GL_EXT_texture_cube_map = 1 )
       integer*4   GL_EXT_texture_edge_clamp
       parameter ( GL_EXT_texture_edge_clamp = 1 )
       integer*4   GL_EXT_clip_volume_hint
       parameter ( GL_EXT_clip_volume_hint = 1 )
       integer*4   GL_EXT_compiled_vertex_array
       parameter ( GL_EXT_compiled_vertex_array = 1 )
       integer*4   GL_EXT_draw_range_elements
       parameter ( GL_EXT_draw_range_elements = 1 )
       integer*4   GL_EXT_bgra
       parameter ( GL_EXT_bgra = 1 )
       integer*4   GL_HP_occlusion_test
       parameter ( GL_HP_occlusion_test = 1 )
       integer*4   GL_EXT_separate_specular_color
       parameter ( GL_EXT_separate_specular_color = 1 )
       integer*4   GL_EXT_secondary_color
       parameter ( GL_EXT_secondary_color = 1 )
       integer*4   GL_EXT_multi_draw_arrays
       parameter ( GL_EXT_multi_draw_arrays = 1 )
       integer*4   GL_EXT_fog_coord
       parameter ( GL_EXT_fog_coord = 1 )
       integer*4   GL_EXT_texture_env_combine
       parameter ( GL_EXT_texture_env_combine = 1 )
       integer*4   GL_EXT_blend_func_separate
       parameter ( GL_EXT_blend_func_separate = 1 )
       integer*4   GL_INGR_interlace_read
       parameter ( GL_INGR_interlace_read = 1 )
       integer*4   GL_EXT_stencil_wrap
       parameter ( GL_EXT_stencil_wrap = 1 )
       integer*4   GL_NV_texgen_reflection
       parameter ( GL_NV_texgen_reflection = 1 )
       integer*4   GL_EXT_texgen_reflection
       parameter ( GL_EXT_texgen_reflection = 1 )
       integer*4   GL_EXT_texture_env_add
       parameter ( GL_EXT_texture_env_add = 1 )
       integer*4   GL_EXT_texture_lod_bias
       parameter ( GL_EXT_texture_lod_bias = 1 )
       integer*4   GL_EXT_texture_filter_anisotropic
       parameter ( GL_EXT_texture_filter_anisotropic = 1 )
       integer*4   GL_NV_blend_square
       parameter ( GL_NV_blend_square = 1 )
       integer*4   GL_EXT_texture_compression_s3tc
       parameter ( GL_EXT_texture_compression_s3tc = 1 )
       integer*4   GL_EXT_texture_env_dot3
       parameter ( GL_EXT_texture_env_dot3 = 1 )
       integer*4   GL_ATI_texture_mirror_once
       parameter ( GL_ATI_texture_mirror_once = 1 )
       integer*4   GL_ATI_envmap_bumpmap
       parameter ( GL_ATI_envmap_bumpmap = 1 )
       integer*4   GL_ATI_fragment_shader
       parameter ( GL_ATI_fragment_shader = 1 )
       integer*4   GL_ATI_pn_triangles
       parameter ( GL_ATI_pn_triangles = 1 )
       integer*4   GL_ATI_vertex_array_object
       parameter ( GL_ATI_vertex_array_object = 1 )
       integer*4   GL_EXT_vertex_shader
       parameter ( GL_EXT_vertex_shader = 1 )
       integer*4   GL_ATI_vertex_streams
       parameter ( GL_ATI_vertex_streams = 1 )
       integer*4   GL_ATI_element_array
       parameter ( GL_ATI_element_array = 1 )
       integer*4   GL_NV_occlusion_query
       parameter ( GL_NV_occlusion_query = 1 )
       integer*4   GL_S3_s3tc
       parameter ( GL_S3_s3tc = 1 )
       integer*4   GL_ATI_draw_buffers
       parameter ( GL_ATI_draw_buffers = 1 )
       integer*4   GL_ATI_map_object_buffer
       parameter ( GL_ATI_map_object_buffer = 1 )
       integer*4   GL_ATI_separate_stencil
       parameter ( GL_ATI_separate_stencil = 1 )
       integer*4   GL_ATI_vertex_attrib_array_object
       parameter ( GL_ATI_vertex_attrib_array_object = 1 )

C  AttribMask 
       integer*4   GL_CURRENT_BIT
       parameter ( GL_CURRENT_BIT = 1 )
       integer*4   GL_POINT_BIT
       parameter ( GL_POINT_BIT = 2 )
       integer*4   GL_LINE_BIT
       parameter ( GL_LINE_BIT = 4 )
       integer*4   GL_POLYGON_BIT
       parameter ( GL_POLYGON_BIT = 8 )
       integer*4   GL_POLYGON_STIPPLE_BIT
       parameter ( GL_POLYGON_STIPPLE_BIT = 16 )
       integer*4   GL_PIXEL_MODE_BIT
       parameter ( GL_PIXEL_MODE_BIT = 32 )
       integer*4   GL_LIGHTING_BIT
       parameter ( GL_LIGHTING_BIT = 64 )
       integer*4   GL_FOG_BIT
       parameter ( GL_FOG_BIT = 128 )
       integer*4   GL_DEPTH_BUFFER_BIT
       parameter ( GL_DEPTH_BUFFER_BIT = 256 )
       integer*4   GL_ACCUM_BUFFER_BIT
       parameter ( GL_ACCUM_BUFFER_BIT = 512 )
       integer*4   GL_STENCIL_BUFFER_BIT
       parameter ( GL_STENCIL_BUFFER_BIT = 1024 )
       integer*4   GL_VIEWPORT_BIT
       parameter ( GL_VIEWPORT_BIT = 2048 )
       integer*4   GL_TRANSFORM_BIT
       parameter ( GL_TRANSFORM_BIT = 4096 )
       integer*4   GL_ENABLE_BIT
       parameter ( GL_ENABLE_BIT = 8192 )
       integer*4   GL_COLOR_BUFFER_BIT
       parameter ( GL_COLOR_BUFFER_BIT = 16384 )
       integer*4   GL_HINT_BIT
       parameter ( GL_HINT_BIT = 32768 )
       integer*4   GL_EVAL_BIT
       parameter ( GL_EVAL_BIT = 65536 )
       integer*4   GL_LIST_BIT
       parameter ( GL_LIST_BIT = 131072 )
       integer*4   GL_TEXTURE_BIT
       parameter ( GL_TEXTURE_BIT = 262144 )
       integer*4   GL_SCISSOR_BIT
       parameter ( GL_SCISSOR_BIT = 524288 )
       integer*4   GL_ALL_ATTRIB_BITS
       parameter ( GL_ALL_ATTRIB_BITS = 1048575 )
       integer*4   GL_MULTISAMPLE_BIT_EXT
       parameter ( GL_MULTISAMPLE_BIT_EXT = 536870912 )

C  ClearBufferMask 
C       GL_COLOR_BUFFER_BIT 
C       GL_ACCUM_BUFFER_BIT 
C       GL_STENCIL_BUFFER_BIT 
C       GL_DEPTH_BUFFER_BIT 

C  ClientAttribMask 
       integer*4   GL_CLIENT_PIXEL_STORE_BIT
       parameter ( GL_CLIENT_PIXEL_STORE_BIT = 1 )
       integer*4   GL_CLIENT_VERTEX_ARRAY_BIT
       parameter ( GL_CLIENT_VERTEX_ARRAY_BIT = 2 )
       integer*4   GL_CLIENT_ALL_ATTRIB_BITS
       parameter ( GL_CLIENT_ALL_ATTRIB_BITS = $FFFFFFFF )

C  Boolean 
       integer*4   GL_FALSE
       parameter ( GL_FALSE = 0 )
       integer*4   GL_TRUE
       parameter ( GL_TRUE = 1 )

C  BeginMode 
       integer*4   GL_POINTS
       parameter ( GL_POINTS = 0 )
       integer*4   GL_LINES
       parameter ( GL_LINES = 1 )
       integer*4   GL_LINE_LOOP
       parameter ( GL_LINE_LOOP = 2 )
       integer*4   GL_LINE_STRIP
       parameter ( GL_LINE_STRIP = 3 )
       integer*4   GL_TRIANGLES
       parameter ( GL_TRIANGLES = 4 )
       integer*4   GL_TRIANGLE_STRIP
       parameter ( GL_TRIANGLE_STRIP = 5 )
       integer*4   GL_TRIANGLE_FAN
       parameter ( GL_TRIANGLE_FAN = 6 )
       integer*4   GL_QUADS
       parameter ( GL_QUADS = 7 )
       integer*4   GL_QUAD_STRIP
       parameter ( GL_QUAD_STRIP = 8 )
       integer*4   GL_POLYGON
       parameter ( GL_POLYGON = 9 )

C  AccumOp 
       integer*4   GL_ACCUM
       parameter ( GL_ACCUM = 256 )
       integer*4   GL_LOAD
       parameter ( GL_LOAD = 257 )
       integer*4   GL_RETURN
       parameter ( GL_RETURN = 258 )
       integer*4   GL_MULT
       parameter ( GL_MULT = 259 )
       integer*4   GL_ADD
       parameter ( GL_ADD = 260 )

C  AlphaFunction 
       integer*4   GL_NEVER
       parameter ( GL_NEVER = 512 )
       integer*4   GL_LESS
       parameter ( GL_LESS = 513 )
       integer*4   GL_EQUAL
       parameter ( GL_EQUAL = 514 )
       integer*4   GL_LEQUAL
       parameter ( GL_LEQUAL = 515 )
       integer*4   GL_GREATER
       parameter ( GL_GREATER = 516 )
       integer*4   GL_NOTEQUAL
       parameter ( GL_NOTEQUAL = 517 )
       integer*4   GL_GEQUAL
       parameter ( GL_GEQUAL = 518 )
       integer*4   GL_ALWAYS
       parameter ( GL_ALWAYS = 519 )

C  BlendingFactorDest 
       integer*4   GL_ZERO
       parameter ( GL_ZERO = 0 )
       integer*4   GL_ONE
       parameter ( GL_ONE = 1 )
       integer*4   GL_SRC_COLOR
       parameter ( GL_SRC_COLOR = 768 )
       integer*4   GL_ONE_MINUS_SRC_COLOR
       parameter ( GL_ONE_MINUS_SRC_COLOR = 769 )
       integer*4   GL_SRC_ALPHA
       parameter ( GL_SRC_ALPHA = 770 )
       integer*4   GL_ONE_MINUS_SRC_ALPHA
       parameter ( GL_ONE_MINUS_SRC_ALPHA = 771 )
       integer*4   GL_DST_ALPHA
       parameter ( GL_DST_ALPHA = 772 )
       integer*4   GL_ONE_MINUS_DST_ALPHA
       parameter ( GL_ONE_MINUS_DST_ALPHA = 773 )
C       GL_CONSTANT_COLOR_EXT 
C       GL_ONE_MINUS_CONSTANT_COLOR_EXT 
C       GL_CONSTANT_ALPHA_EXT 
C       GL_ONE_MINUS_CONSTANT_ALPHA_EXT 

C  BlendingFactorSrc 
C       GL_ZERO 
C       GL_ONE 
       integer*4   GL_DST_COLOR
       parameter ( GL_DST_COLOR = 774 )
       integer*4   GL_ONE_MINUS_DST_COLOR
       parameter ( GL_ONE_MINUS_DST_COLOR = 775 )
       integer*4   GL_SRC_ALPHA_SATURATE
       parameter ( GL_SRC_ALPHA_SATURATE = 776 )
C       GL_SRC_ALPHA 
C       GL_ONE_MINUS_SRC_ALPHA 
C       GL_DST_ALPHA 
C       GL_ONE_MINUS_DST_ALPHA 
C       GL_CONSTANT_COLOR_EXT 
C       GL_ONE_MINUS_CONSTANT_COLOR_EXT 
C       GL_CONSTANT_ALPHA_EXT 
C       GL_ONE_MINUS_CONSTANT_ALPHA_EXT 

C  BlendEquationModeEXT 
C       GL_LOGIC_OP 
C       GL_FUNC_ADD_EXT 
C       GL_MIN_EXT 
C       GL_MAX_EXT 
C       GL_FUNC_SUBTRACT_EXT 
C       GL_FUNC_REVERSE_SUBTRACT_EXT 
C       GL_ALPHA_MIN_SGIX 
C       GL_ALPHA_MAX_SGIX 

C  ColorMaterialFace 
C       GL_FRONT 
C       GL_BACK 
C       GL_FRONT_AND_BACK 

C  ColorMaterialParameter 
C       GL_AMBIENT 
C       GL_DIFFUSE 
C       GL_SPECULAR 
C       GL_EMISSION 
C       GL_AMBIENT_AND_DIFFUSE 

C  ColorPointerType 
C       GL_BYTE 
C       GL_UNSIGNED_BYTE 
C       GL_SHORT 
C       GL_UNSIGNED_SHORT 
C       GL_INT 
C       GL_UNSIGNED_INT 
C       GL_FLOAT 
C       GL_DOUBLE 

C  ColorTableParameterPNameSGI 
C       GL_COLOR_TABLE_SCALE_SGI 
C       GL_COLOR_TABLE_BIAS_SGI 

C  ColorTableTargetSGI 
C       GL_COLOR_TABLE_SGI 
C       GL_POST_CONVOLUTION_COLOR_TABLE_SGI 
C       GL_POST_COLOR_MATRIX_COLOR_TABLE_SGI 
C       GL_PROXY_COLOR_TABLE_SGI 
C       GL_PROXY_POST_CONVOLUTION_COLOR_TABLE_SGI 
C       GL_PROXY_POST_COLOR_MATRIX_COLOR_TABLE_SGI 
C       GL_TEXTURE_COLOR_TABLE_SGI 
C       GL_PROXY_TEXTURE_COLOR_TABLE_SGI 

C  ConvolutionBorderModeEXT 
C       GL_REDUCE_EXT 

C  ConvolutionParameterEXT 
C       GL_CONVOLUTION_BORDER_MODE_EXT 
C       GL_CONVOLUTION_FILTER_SCALE_EXT 
C       GL_CONVOLUTION_FILTER_BIAS_EXT 

C  ConvolutionTargetEXT 
C       GL_CONVOLUTION_1D_EXT 
C       GL_CONVOLUTION_2D_EXT 

C  CullFaceMode 
C       GL_FRONT 
C       GL_BACK 
C       GL_FRONT_AND_BACK 

C  DepthFunction 
C       GL_NEVER 
C       GL_LESS 
C       GL_EQUAL 
C       GL_LEQUAL 
C       GL_GREATER 
C       GL_NOTEQUAL 
C       GL_GEQUAL 
C       GL_ALWAYS 

C  DrawBufferMode 
       integer*4   GL_NONE
       parameter ( GL_NONE = 0 )
       integer*4   GL_FRONT_LEFT
       parameter ( GL_FRONT_LEFT = 1024 )
       integer*4   GL_FRONT_RIGHT
       parameter ( GL_FRONT_RIGHT = 1025 )
       integer*4   GL_BACK_LEFT
       parameter ( GL_BACK_LEFT = 1026 )
       integer*4   GL_BACK_RIGHT
       parameter ( GL_BACK_RIGHT = 1027 )
       integer*4   GL_FRONT
       parameter ( GL_FRONT = 1028 )
       integer*4   GL_BACK
       parameter ( GL_BACK = 1029 )
       integer*4   GL_LEFT
       parameter ( GL_LEFT = 1030 )
       integer*4   GL_RIGHT
       parameter ( GL_RIGHT = 1031 )
       integer*4   GL_FRONT_AND_BACK
       parameter ( GL_FRONT_AND_BACK = 1032 )
       integer*4   GL_AUX0
       parameter ( GL_AUX0 = 1033 )
       integer*4   GL_AUX1
       parameter ( GL_AUX1 = 1034 )
       integer*4   GL_AUX2
       parameter ( GL_AUX2 = 1035 )
       integer*4   GL_AUX3
       parameter ( GL_AUX3 = 1036 )

C  EnableCap 
C       GL_FOG 
C       GL_LIGHTING 
C       GL_TEXTURE_1D 
C       GL_TEXTURE_2D 
C       GL_LINE_STIPPLE 
C       GL_POLYGON_STIPPLE 
C       GL_CULL_FACE 
C       GL_ALPHA_TEST 
C       GL_BLEND 
C       GL_INDEX_LOGIC_OP 
C       GL_COLOR_LOGIC_OP 
C       GL_DITHER 
C       GL_STENCIL_TEST 
C       GL_DEPTH_TEST 
C       GL_CLIP_PLANE0 
C       GL_CLIP_PLANE1 
C       GL_CLIP_PLANE2 
C       GL_CLIP_PLANE3 
C       GL_CLIP_PLANE4 
C       GL_CLIP_PLANE5 
C       GL_LIGHT0 
C       GL_LIGHT1 
C       GL_LIGHT2 
C       GL_LIGHT3 
C       GL_LIGHT4 
C       GL_LIGHT5 
C       GL_LIGHT6 
C       GL_LIGHT7 
C       GL_TEXTURE_GEN_S 
C       GL_TEXTURE_GEN_T 
C       GL_TEXTURE_GEN_R 
C       GL_TEXTURE_GEN_Q 
C       GL_MAP1_VERTEX_3 
C       GL_MAP1_VERTEX_4 
C       GL_MAP1_COLOR_4 
C       GL_MAP1_INDEX 
C       GL_MAP1_NORMAL 
C       GL_MAP1_TEXTURE_COORD_1 
C       GL_MAP1_TEXTURE_COORD_2 
C       GL_MAP1_TEXTURE_COORD_3 
C       GL_MAP1_TEXTURE_COORD_4 
C       GL_MAP2_VERTEX_3 
C       GL_MAP2_VERTEX_4 
C       GL_MAP2_COLOR_4 
C       GL_MAP2_INDEX 
C       GL_MAP2_NORMAL 
C       GL_MAP2_TEXTURE_COORD_1 
C       GL_MAP2_TEXTURE_COORD_2 
C       GL_MAP2_TEXTURE_COORD_3 
C       GL_MAP2_TEXTURE_COORD_4 
C       GL_POINT_SMOOTH 
C       GL_LINE_SMOOTH 
C       GL_POLYGON_SMOOTH 
C       GL_SCISSOR_TEST 
C       GL_COLOR_MATERIAL 
C       GL_NORMALIZE 
C       GL_AUTO_NORMAL 
C       GL_POLYGON_OFFSET_POINT 
C       GL_POLYGON_OFFSET_LINE 
C       GL_POLYGON_OFFSET_FILL 
C       GL_VERTEX_ARRAY 
C       GL_NORMAL_ARRAY 
C       GL_COLOR_ARRAY 
C       GL_INDEX_ARRAY 
C       GL_TEXTURE_COORD_ARRAY 
C       GL_EDGE_FLAG_ARRAY 
C       GL_CONVOLUTION_1D_EXT 
C       GL_CONVOLUTION_2D_EXT 
C       GL_SEPARABLE_2D_EXT 
C       GL_HISTOGRAM_EXT 
C       GL_MINMAX_EXT 
C       GL_RESCALE_NORMAL_EXT 
C       GL_SHARED_TEXTURE_PALETTE_EXT 
C       GL_TEXTURE_3D_EXT 
C       GL_INTERLACE_READ_INGR 
C       GL_MULTISAMPLE_SGIS 
C       GL_SAMPLE_ALPHA_TO_MASK_SGIS 
C       GL_SAMPLE_ALPHA_TO_ONE_SGIS 
C       GL_SAMPLE_MASK_SGIS 
C       GL_TEXTURE_4D_SGIS 
C       GL_ASYNC_HISTOGRAM_SGIX 
C       GL_ASYNC_TEX_IMAGE_SGIX 
C       GL_ASYNC_DRAW_PIXELS_SGIX 
C       GL_ASYNC_READ_PIXELS_SGIX 
C       GL_CALLIGRAPHIC_FRAGMENT_SGIX 
C       GL_FOG_OFFSET_SGIX 
C       GL_FRAGMENT_LIGHTING_SGIX 
C       GL_FRAGMENT_COLOR_MATERIAL_SGIX 
C       GL_FRAGMENT_LIGHT0_SGIX 
C       GL_FRAGMENT_LIGHT1_SGIX 
C       GL_FRAGMENT_LIGHT2_SGIX 
C       GL_FRAGMENT_LIGHT3_SGIX 
C       GL_FRAGMENT_LIGHT4_SGIX 
C       GL_FRAGMENT_LIGHT5_SGIX 
C       GL_FRAGMENT_LIGHT6_SGIX 
C       GL_FRAGMENT_LIGHT7_SGIX 
C       GL_FRAMEZOOM_SGIX 
C       GL_INTERLACE_SGIX 
C       GL_IR_INSTRUMENT1_SGIX 
C       GL_PIXEL_TEX_GEN_SGIX 
C       GL_PIXEL_TEXTURE_SGIS 
C       GL_REFERENCE_PLANE_SGIX 
C       GL_SPRITE_SGIX 
C       GL_COLOR_TABLE_SGI 
C       GL_POST_CONVOLUTION_COLOR_TABLE_SGI 
C       GL_POST_COLOR_MATRIX_COLOR_TABLE_SGI 
C       GL_TEXTURE_COLOR_TABLE_SGI 

C  ErrorCode 
       integer*4   GL_NO_ERROR
       parameter ( GL_NO_ERROR = 0 )
       integer*4   GL_INVALID_ENUM
       parameter ( GL_INVALID_ENUM = 1280 )
       integer*4   GL_INVALID_VALUE
       parameter ( GL_INVALID_VALUE = 1281 )
       integer*4   GL_INVALID_OPERATION
       parameter ( GL_INVALID_OPERATION = 1282 )
       integer*4   GL_STACK_OVERFLOW
       parameter ( GL_STACK_OVERFLOW = 1283 )
       integer*4   GL_STACK_UNDERFLOW
       parameter ( GL_STACK_UNDERFLOW = 1284 )
       integer*4   GL_OUT_OF_MEMORY
       parameter ( GL_OUT_OF_MEMORY = 1285 )
C       GL_TABLE_TOO_LARGE_EXT 
C       GL_TEXTURE_TOO_LARGE_EXT 

C  FeedbackType 
       integer*4   GL_2D
       parameter ( GL_2D = 1536 )
       integer*4   GL_3D
       parameter ( GL_3D = 1537 )
       integer*4   GL_3D_COLOR
       parameter ( GL_3D_COLOR = 1538 )
       integer*4   GL_3D_COLOR_TEXTURE
       parameter ( GL_3D_COLOR_TEXTURE = 1539 )
       integer*4   GL_4D_COLOR_TEXTURE
       parameter ( GL_4D_COLOR_TEXTURE = 1540 )

C  FeedBackToken 
       integer*4   GL_PASS_THROUGH_TOKEN
       parameter ( GL_PASS_THROUGH_TOKEN = 1792 )
       integer*4   GL_POINT_TOKEN
       parameter ( GL_POINT_TOKEN = 1793 )
       integer*4   GL_LINE_TOKEN
       parameter ( GL_LINE_TOKEN = 1794 )
       integer*4   GL_POLYGON_TOKEN
       parameter ( GL_POLYGON_TOKEN = 1795 )
       integer*4   GL_BITMAP_TOKEN
       parameter ( GL_BITMAP_TOKEN = 1796 )
       integer*4   GL_DRAW_PIXEL_TOKEN
       parameter ( GL_DRAW_PIXEL_TOKEN = 1797 )
       integer*4   GL_COPY_PIXEL_TOKEN
       parameter ( GL_COPY_PIXEL_TOKEN = 1798 )
       integer*4   GL_LINE_RESET_TOKEN
       parameter ( GL_LINE_RESET_TOKEN = 1799 )

C  FfdMaskSGIX 
       integer*4   GL_TEXTURE_DEFORMATION_BIT_SGIX
       parameter ( GL_TEXTURE_DEFORMATION_BIT_SGIX = 1 )
       integer*4   GL_GEOMETRY_DEFORMATION_BIT_SGIX
       parameter ( GL_GEOMETRY_DEFORMATION_BIT_SGIX = 2 )

C  FfdTargetSGIX 
C       GL_GEOMETRY_DEFORMATION_SGIX 
C       GL_TEXTURE_DEFORMATION_SGIX 

C  FogMode 
C       GL_LINEAR 
       integer*4   GL_EXP
       parameter ( GL_EXP = 2048 )
       integer*4   GL_EXP2
       parameter ( GL_EXP2 = 2049 )
C       GL_FOG_FUNC_SGIS 

C  FogParameter 
C       GL_FOG_COLOR 
C       GL_FOG_DENSITY 
C       GL_FOG_END 
C       GL_FOG_INDEX 
C       GL_FOG_MODE 
C       GL_FOG_START 
C       GL_FOG_OFFSET_VALUE_SGIX 

C  FragmentLightModelParameterSGIX 
C       GL_FRAGMENT_LIGHT_MODEL_LOCAL_VIEWER_SGIX 
C       GL_FRAGMENT_LIGHT_MODEL_TWO_SIDE_SGIX 
C       GL_FRAGMENT_LIGHT_MODEL_AMBIENT_SGIX 
C       GL_FRAGMENT_LIGHT_MODEL_NORMAL_INTERPOLATION_SGIX 

C  FrontFaceDirection 
       integer*4   GL_CW
       parameter ( GL_CW = 2304 )
       integer*4   GL_CCW
       parameter ( GL_CCW = 2305 )

C  GetColorTableParameterPNameSGI 
C       GL_COLOR_TABLE_SCALE_SGI 
C       GL_COLOR_TABLE_BIAS_SGI 
C       GL_COLOR_TABLE_FORMAT_SGI 
C       GL_COLOR_TABLE_WIDTH_SGI 
C       GL_COLOR_TABLE_RED_SIZE_SGI 
C       GL_COLOR_TABLE_GREEN_SIZE_SGI 
C       GL_COLOR_TABLE_BLUE_SIZE_SGI 
C       GL_COLOR_TABLE_ALPHA_SIZE_SGI 
C       GL_COLOR_TABLE_LUMINANCE_SIZE_SGI 
C       GL_COLOR_TABLE_INTENSITY_SIZE_SGI 

C  GetConvolutionParameter 
C       GL_CONVOLUTION_BORDER_MODE_EXT 
C       GL_CONVOLUTION_FILTER_SCALE_EXT 
C       GL_CONVOLUTION_FILTER_BIAS_EXT 
C       GL_CONVOLUTION_FORMAT_EXT 
C       GL_CONVOLUTION_WIDTH_EXT 
C       GL_CONVOLUTION_HEIGHT_EXT 
C       GL_MAX_CONVOLUTION_WIDTH_EXT 
C       GL_MAX_CONVOLUTION_HEIGHT_EXT 

C  GetHistogramParameterPNameEXT 
C       GL_HISTOGRAM_WIDTH_EXT 
C       GL_HISTOGRAM_FORMAT_EXT 
C       GL_HISTOGRAM_RED_SIZE_EXT 
C       GL_HISTOGRAM_GREEN_SIZE_EXT 
C       GL_HISTOGRAM_BLUE_SIZE_EXT 
C       GL_HISTOGRAM_ALPHA_SIZE_EXT 
C       GL_HISTOGRAM_LUMINANCE_SIZE_EXT 
C       GL_HISTOGRAM_SINK_EXT 

C  GetMapQuery 
       integer*4   GL_COEFF
       parameter ( GL_COEFF = 2560 )
       integer*4   GL_ORDER
       parameter ( GL_ORDER = 2561 )
       integer*4   GL_DOMAIN
       parameter ( GL_DOMAIN = 2562 )

C  GetMinmaxParameterPNameEXT 
C       GL_MINMAX_FORMAT_EXT 
C       GL_MINMAX_SINK_EXT 

C  GetPixelMap 
       integer*4   GL_PIXEL_MAP_I_TO_I
       parameter ( GL_PIXEL_MAP_I_TO_I = 3184 )
       integer*4   GL_PIXEL_MAP_S_TO_S
       parameter ( GL_PIXEL_MAP_S_TO_S = 3185 )
       integer*4   GL_PIXEL_MAP_I_TO_R
       parameter ( GL_PIXEL_MAP_I_TO_R = 3186 )
       integer*4   GL_PIXEL_MAP_I_TO_G
       parameter ( GL_PIXEL_MAP_I_TO_G = 3187 )
       integer*4   GL_PIXEL_MAP_I_TO_B
       parameter ( GL_PIXEL_MAP_I_TO_B = 3188 )
       integer*4   GL_PIXEL_MAP_I_TO_A
       parameter ( GL_PIXEL_MAP_I_TO_A = 3189 )
       integer*4   GL_PIXEL_MAP_R_TO_R
       parameter ( GL_PIXEL_MAP_R_TO_R = 3190 )
       integer*4   GL_PIXEL_MAP_G_TO_G
       parameter ( GL_PIXEL_MAP_G_TO_G = 3191 )
       integer*4   GL_PIXEL_MAP_B_TO_B
       parameter ( GL_PIXEL_MAP_B_TO_B = 3192 )
       integer*4   GL_PIXEL_MAP_A_TO_A
       parameter ( GL_PIXEL_MAP_A_TO_A = 3193 )

C  GetPointervPName 
       integer*4   GL_VERTEX_ARRAY_POINTER
       parameter ( GL_VERTEX_ARRAY_POINTER = 32910 )
       integer*4   GL_NORMAL_ARRAY_POINTER
       parameter ( GL_NORMAL_ARRAY_POINTER = 32911 )
       integer*4   GL_COLOR_ARRAY_POINTER
       parameter ( GL_COLOR_ARRAY_POINTER = 32912 )
       integer*4   GL_INDEX_ARRAY_POINTER
       parameter ( GL_INDEX_ARRAY_POINTER = 32913 )
       integer*4   GL_TEXTURE_COORD_ARRAY_POINTER
       parameter ( GL_TEXTURE_COORD_ARRAY_POINTER = 32914 )
       integer*4   GL_EDGE_FLAG_ARRAY_POINTER
       parameter ( GL_EDGE_FLAG_ARRAY_POINTER = 32915 )
       integer*4   GL_FEEDBACK_BUFFER_POINTER
       parameter ( GL_FEEDBACK_BUFFER_POINTER = 3568 )
       integer*4   GL_SELECTION_BUFFER_POINTER
       parameter ( GL_SELECTION_BUFFER_POINTER = 3571 )
C       GL_INSTRUMENT_BUFFER_POINTER_SGIX 

C  GetPName 
       integer*4   GL_CURRENT_COLOR
       parameter ( GL_CURRENT_COLOR = 2816 )
       integer*4   GL_CURRENT_INDEX
       parameter ( GL_CURRENT_INDEX = 2817 )
       integer*4   GL_CURRENT_NORMAL
       parameter ( GL_CURRENT_NORMAL = 2818 )
       integer*4   GL_CURRENT_TEXTURE_COORDS
       parameter ( GL_CURRENT_TEXTURE_COORDS = 2819 )
       integer*4   GL_CURRENT_RASTER_COLOR
       parameter ( GL_CURRENT_RASTER_COLOR = 2820 )
       integer*4   GL_CURRENT_RASTER_INDEX
       parameter ( GL_CURRENT_RASTER_INDEX = 2821 )
       integer*4   GL_CURRENT_RASTER_TEXTURE_COORDS
       parameter ( GL_CURRENT_RASTER_TEXTURE_COORDS = 2822 )
       integer*4   GL_CURRENT_RASTER_POSITION
       parameter ( GL_CURRENT_RASTER_POSITION = 2823 )
       integer*4   GL_CURRENT_RASTER_POSITION_VALID
       parameter ( GL_CURRENT_RASTER_POSITION_VALID = 2824 )
       integer*4   GL_CURRENT_RASTER_DISTANCE
       parameter ( GL_CURRENT_RASTER_DISTANCE = 2825 )
       integer*4   GL_POINT_SMOOTH
       parameter ( GL_POINT_SMOOTH = 2832 )
       integer*4   GL_POINT_SIZE
       parameter ( GL_POINT_SIZE = 2833 )
       integer*4   GL_POINT_SIZE_RANGE
       parameter ( GL_POINT_SIZE_RANGE = 2834 )
       integer*4   GL_POINT_SIZE_GRANULARITY
       parameter ( GL_POINT_SIZE_GRANULARITY = 2835 )
       integer*4   GL_LINE_SMOOTH
       parameter ( GL_LINE_SMOOTH = 2848 )
       integer*4   GL_LINE_WIDTH
       parameter ( GL_LINE_WIDTH = 2849 )
       integer*4   GL_LINE_WIDTH_RANGE
       parameter ( GL_LINE_WIDTH_RANGE = 2850 )
       integer*4   GL_LINE_WIDTH_GRANULARITY
       parameter ( GL_LINE_WIDTH_GRANULARITY = 2851 )
       integer*4   GL_LINE_STIPPLE
       parameter ( GL_LINE_STIPPLE = 2852 )
       integer*4   GL_LINE_STIPPLE_PATTERN
       parameter ( GL_LINE_STIPPLE_PATTERN = 2853 )
       integer*4   GL_LINE_STIPPLE_REPEAT
       parameter ( GL_LINE_STIPPLE_REPEAT = 2854 )
C       GL_SMOOTH_POINT_SIZE_RANGE 
C       GL_SMOOTH_POINT_SIZE_GRANULARITY 
C       GL_SMOOTH_LINE_WIDTH_RANGE 
C       GL_SMOOTH_LINE_WIDTH_GRANULARITY 
C       GL_ALIASED_POINT_SIZE_RANGE 
C       GL_ALIASED_LINE_WIDTH_RANGE 
       integer*4   GL_LIST_MODE
       parameter ( GL_LIST_MODE = 2864 )
       integer*4   GL_MAX_LIST_NESTING
       parameter ( GL_MAX_LIST_NESTING = 2865 )
       integer*4   GL_LIST_BASE
       parameter ( GL_LIST_BASE = 2866 )
       integer*4   GL_LIST_INDEX
       parameter ( GL_LIST_INDEX = 2867 )
       integer*4   GL_POLYGON_MODE
       parameter ( GL_POLYGON_MODE = 2880 )
       integer*4   GL_POLYGON_SMOOTH
       parameter ( GL_POLYGON_SMOOTH = 2881 )
       integer*4   GL_POLYGON_STIPPLE
       parameter ( GL_POLYGON_STIPPLE = 2882 )
       integer*4   GL_EDGE_FLAG
       parameter ( GL_EDGE_FLAG = 2883 )
       integer*4   GL_CULL_FACE
       parameter ( GL_CULL_FACE = 2884 )
       integer*4   GL_CULL_FACE_MODE
       parameter ( GL_CULL_FACE_MODE = 2885 )
       integer*4   GL_FRONT_FACE
       parameter ( GL_FRONT_FACE = 2886 )
       integer*4   GL_LIGHTING
       parameter ( GL_LIGHTING = 2896 )
       integer*4   GL_LIGHT_MODEL_LOCAL_VIEWER
       parameter ( GL_LIGHT_MODEL_LOCAL_VIEWER = 2897 )
       integer*4   GL_LIGHT_MODEL_TWO_SIDE
       parameter ( GL_LIGHT_MODEL_TWO_SIDE = 2898 )
       integer*4   GL_LIGHT_MODEL_AMBIENT
       parameter ( GL_LIGHT_MODEL_AMBIENT = 2899 )
       integer*4   GL_SHADE_MODEL
       parameter ( GL_SHADE_MODEL = 2900 )
       integer*4   GL_COLOR_MATERIAL_FACE
       parameter ( GL_COLOR_MATERIAL_FACE = 2901 )
       integer*4   GL_COLOR_MATERIAL_PARAMETER
       parameter ( GL_COLOR_MATERIAL_PARAMETER = 2902 )
       integer*4   GL_COLOR_MATERIAL
       parameter ( GL_COLOR_MATERIAL = 2903 )
       integer*4   GL_FOG
       parameter ( GL_FOG = 2912 )
       integer*4   GL_FOG_INDEX
       parameter ( GL_FOG_INDEX = 2913 )
       integer*4   GL_FOG_DENSITY
       parameter ( GL_FOG_DENSITY = 2914 )
       integer*4   GL_FOG_START
       parameter ( GL_FOG_START = 2915 )
       integer*4   GL_FOG_END
       parameter ( GL_FOG_END = 2916 )
       integer*4   GL_FOG_MODE
       parameter ( GL_FOG_MODE = 2917 )
       integer*4   GL_FOG_COLOR
       parameter ( GL_FOG_COLOR = 2918 )
       integer*4   GL_DEPTH_RANGE
       parameter ( GL_DEPTH_RANGE = 2928 )
       integer*4   GL_DEPTH_TEST
       parameter ( GL_DEPTH_TEST = 2929 )
       integer*4   GL_DEPTH_WRITEMASK
       parameter ( GL_DEPTH_WRITEMASK = 2930 )
       integer*4   GL_DEPTH_CLEAR_VALUE
       parameter ( GL_DEPTH_CLEAR_VALUE = 2931 )
       integer*4   GL_DEPTH_FUNC
       parameter ( GL_DEPTH_FUNC = 2932 )
       integer*4   GL_ACCUM_CLEAR_VALUE
       parameter ( GL_ACCUM_CLEAR_VALUE = 2944 )
       integer*4   GL_STENCIL_TEST
       parameter ( GL_STENCIL_TEST = 2960 )
       integer*4   GL_STENCIL_CLEAR_VALUE
       parameter ( GL_STENCIL_CLEAR_VALUE = 2961 )
       integer*4   GL_STENCIL_FUNC
       parameter ( GL_STENCIL_FUNC = 2962 )
       integer*4   GL_STENCIL_VALUE_MASK
       parameter ( GL_STENCIL_VALUE_MASK = 2963 )
       integer*4   GL_STENCIL_FAIL
       parameter ( GL_STENCIL_FAIL = 2964 )
       integer*4   GL_STENCIL_PASS_DEPTH_FAIL
       parameter ( GL_STENCIL_PASS_DEPTH_FAIL = 2965 )
       integer*4   GL_STENCIL_PASS_DEPTH_PASS
       parameter ( GL_STENCIL_PASS_DEPTH_PASS = 2966 )
       integer*4   GL_STENCIL_REF
       parameter ( GL_STENCIL_REF = 2967 )
       integer*4   GL_STENCIL_WRITEMASK
       parameter ( GL_STENCIL_WRITEMASK = 2968 )
       integer*4   GL_MATRIX_MODE
       parameter ( GL_MATRIX_MODE = 2976 )
       integer*4   GL_NORMALIZE
       parameter ( GL_NORMALIZE = 2977 )
       integer*4   GL_VIEWPORT
       parameter ( GL_VIEWPORT = 2978 )
       integer*4   GL_MODELVIEW_STACK_DEPTH
       parameter ( GL_MODELVIEW_STACK_DEPTH = 2979 )
       integer*4   GL_PROJECTION_STACK_DEPTH
       parameter ( GL_PROJECTION_STACK_DEPTH = 2980 )
       integer*4   GL_TEXTURE_STACK_DEPTH
       parameter ( GL_TEXTURE_STACK_DEPTH = 2981 )
       integer*4   GL_MODELVIEW_MATRIX
       parameter ( GL_MODELVIEW_MATRIX = 2982 )
       integer*4   GL_PROJECTION_MATRIX
       parameter ( GL_PROJECTION_MATRIX = 2983 )
       integer*4   GL_TEXTURE_MATRIX
       parameter ( GL_TEXTURE_MATRIX = 2984 )
       integer*4   GL_ATTRIB_STACK_DEPTH
       parameter ( GL_ATTRIB_STACK_DEPTH = 2992 )
       integer*4   GL_CLIENT_ATTRIB_STACK_DEPTH
       parameter ( GL_CLIENT_ATTRIB_STACK_DEPTH = 2993 )
       integer*4   GL_ALPHA_TEST
       parameter ( GL_ALPHA_TEST = 3008 )
       integer*4   GL_ALPHA_TEST_FUNC
       parameter ( GL_ALPHA_TEST_FUNC = 3009 )
       integer*4   GL_ALPHA_TEST_REF
       parameter ( GL_ALPHA_TEST_REF = 3010 )
       integer*4   GL_DITHER
       parameter ( GL_DITHER = 3024 )
       integer*4   GL_BLEND_DST
       parameter ( GL_BLEND_DST = 3040 )
       integer*4   GL_BLEND_SRC
       parameter ( GL_BLEND_SRC = 3041 )
       integer*4   GL_BLEND
       parameter ( GL_BLEND = 3042 )
       integer*4   GL_LOGIC_OP_MODE
       parameter ( GL_LOGIC_OP_MODE = 3056 )
       integer*4   GL_INDEX_LOGIC_OP
       parameter ( GL_INDEX_LOGIC_OP = 3057 )
       integer*4   GL_LOGIC_OP
       parameter ( GL_LOGIC_OP = 3057 )
       integer*4   GL_COLOR_LOGIC_OP
       parameter ( GL_COLOR_LOGIC_OP = 3058 )
       integer*4   GL_AUX_BUFFERS
       parameter ( GL_AUX_BUFFERS = 3072 )
       integer*4   GL_DRAW_BUFFER
       parameter ( GL_DRAW_BUFFER = 3073 )
       integer*4   GL_READ_BUFFER
       parameter ( GL_READ_BUFFER = 3074 )
       integer*4   GL_SCISSOR_BOX
       parameter ( GL_SCISSOR_BOX = 3088 )
       integer*4   GL_SCISSOR_TEST
       parameter ( GL_SCISSOR_TEST = 3089 )
       integer*4   GL_INDEX_CLEAR_VALUE
       parameter ( GL_INDEX_CLEAR_VALUE = 3104 )
       integer*4   GL_INDEX_WRITEMASK
       parameter ( GL_INDEX_WRITEMASK = 3105 )
       integer*4   GL_COLOR_CLEAR_VALUE
       parameter ( GL_COLOR_CLEAR_VALUE = 3106 )
       integer*4   GL_COLOR_WRITEMASK
       parameter ( GL_COLOR_WRITEMASK = 3107 )
       integer*4   GL_INDEX_MODE
       parameter ( GL_INDEX_MODE = 3120 )
       integer*4   GL_RGBA_MODE
       parameter ( GL_RGBA_MODE = 3121 )
       integer*4   GL_DOUBLEBUFFER
       parameter ( GL_DOUBLEBUFFER = 3122 )
       integer*4   GL_STEREO
       parameter ( GL_STEREO = 3123 )
       integer*4   GL_RENDER_MODE
       parameter ( GL_RENDER_MODE = 3136 )
       integer*4   GL_PERSPECTIVE_CORRECTION_HINT
       parameter ( GL_PERSPECTIVE_CORRECTION_HINT = 3152 )
       integer*4   GL_POINT_SMOOTH_HINT
       parameter ( GL_POINT_SMOOTH_HINT = 3153 )
       integer*4   GL_LINE_SMOOTH_HINT
       parameter ( GL_LINE_SMOOTH_HINT = 3154 )
       integer*4   GL_POLYGON_SMOOTH_HINT
       parameter ( GL_POLYGON_SMOOTH_HINT = 3155 )
       integer*4   GL_FOG_HINT
       parameter ( GL_FOG_HINT = 3156 )
       integer*4   GL_TEXTURE_GEN_S
       parameter ( GL_TEXTURE_GEN_S = 3168 )
       integer*4   GL_TEXTURE_GEN_T
       parameter ( GL_TEXTURE_GEN_T = 3169 )
       integer*4   GL_TEXTURE_GEN_R
       parameter ( GL_TEXTURE_GEN_R = 3170 )
       integer*4   GL_TEXTURE_GEN_Q
       parameter ( GL_TEXTURE_GEN_Q = 3171 )
       integer*4   GL_PIXEL_MAP_I_TO_I_SIZE
       parameter ( GL_PIXEL_MAP_I_TO_I_SIZE = 3248 )
       integer*4   GL_PIXEL_MAP_S_TO_S_SIZE
       parameter ( GL_PIXEL_MAP_S_TO_S_SIZE = 3249 )
       integer*4   GL_PIXEL_MAP_I_TO_R_SIZE
       parameter ( GL_PIXEL_MAP_I_TO_R_SIZE = 3250 )
       integer*4   GL_PIXEL_MAP_I_TO_G_SIZE
       parameter ( GL_PIXEL_MAP_I_TO_G_SIZE = 3251 )
       integer*4   GL_PIXEL_MAP_I_TO_B_SIZE
       parameter ( GL_PIXEL_MAP_I_TO_B_SIZE = 3252 )
       integer*4   GL_PIXEL_MAP_I_TO_A_SIZE
       parameter ( GL_PIXEL_MAP_I_TO_A_SIZE = 3253 )
       integer*4   GL_PIXEL_MAP_R_TO_R_SIZE
       parameter ( GL_PIXEL_MAP_R_TO_R_SIZE = 3254 )
       integer*4   GL_PIXEL_MAP_G_TO_G_SIZE
       parameter ( GL_PIXEL_MAP_G_TO_G_SIZE = 3255 )
       integer*4   GL_PIXEL_MAP_B_TO_B_SIZE
       parameter ( GL_PIXEL_MAP_B_TO_B_SIZE = 3256 )
       integer*4   GL_PIXEL_MAP_A_TO_A_SIZE
       parameter ( GL_PIXEL_MAP_A_TO_A_SIZE = 3257 )
       integer*4   GL_UNPACK_SWAP_BYTES
       parameter ( GL_UNPACK_SWAP_BYTES = 3312 )
       integer*4   GL_UNPACK_LSB_FIRST
       parameter ( GL_UNPACK_LSB_FIRST = 3313 )
       integer*4   GL_UNPACK_ROW_LENGTH
       parameter ( GL_UNPACK_ROW_LENGTH = 3314 )
       integer*4   GL_UNPACK_SKIP_ROWS
       parameter ( GL_UNPACK_SKIP_ROWS = 3315 )
       integer*4   GL_UNPACK_SKIP_PIXELS
       parameter ( GL_UNPACK_SKIP_PIXELS = 3316 )
       integer*4   GL_UNPACK_ALIGNMENT
       parameter ( GL_UNPACK_ALIGNMENT = 3317 )
       integer*4   GL_PACK_SWAP_BYTES
       parameter ( GL_PACK_SWAP_BYTES = 3328 )
       integer*4   GL_PACK_LSB_FIRST
       parameter ( GL_PACK_LSB_FIRST = 3329 )
       integer*4   GL_PACK_ROW_LENGTH
       parameter ( GL_PACK_ROW_LENGTH = 3330 )
       integer*4   GL_PACK_SKIP_ROWS
       parameter ( GL_PACK_SKIP_ROWS = 3331 )
       integer*4   GL_PACK_SKIP_PIXELS
       parameter ( GL_PACK_SKIP_PIXELS = 3332 )
       integer*4   GL_PACK_ALIGNMENT
       parameter ( GL_PACK_ALIGNMENT = 3333 )
       integer*4   GL_MAP_COLOR
       parameter ( GL_MAP_COLOR = 3344 )
       integer*4   GL_MAP_STENCIL
       parameter ( GL_MAP_STENCIL = 3345 )
       integer*4   GL_INDEX_SHIFT
       parameter ( GL_INDEX_SHIFT = 3346 )
       integer*4   GL_INDEX_OFFSET
       parameter ( GL_INDEX_OFFSET = 3347 )
       integer*4   GL_RED_SCALE
       parameter ( GL_RED_SCALE = 3348 )
       integer*4   GL_RED_BIAS
       parameter ( GL_RED_BIAS = 3349 )
       integer*4   GL_ZOOM_X
       parameter ( GL_ZOOM_X = 3350 )
       integer*4   GL_ZOOM_Y
       parameter ( GL_ZOOM_Y = 3351 )
       integer*4   GL_GREEN_SCALE
       parameter ( GL_GREEN_SCALE = 3352 )
       integer*4   GL_GREEN_BIAS
       parameter ( GL_GREEN_BIAS = 3353 )
       integer*4   GL_BLUE_SCALE
       parameter ( GL_BLUE_SCALE = 3354 )
       integer*4   GL_BLUE_BIAS
       parameter ( GL_BLUE_BIAS = 3355 )
       integer*4   GL_ALPHA_SCALE
       parameter ( GL_ALPHA_SCALE = 3356 )
       integer*4   GL_ALPHA_BIAS
       parameter ( GL_ALPHA_BIAS = 3357 )
       integer*4   GL_DEPTH_SCALE
       parameter ( GL_DEPTH_SCALE = 3358 )
       integer*4   GL_DEPTH_BIAS
       parameter ( GL_DEPTH_BIAS = 3359 )
       integer*4   GL_MAX_EVAL_ORDER
       parameter ( GL_MAX_EVAL_ORDER = 3376 )
       integer*4   GL_MAX_LIGHTS
       parameter ( GL_MAX_LIGHTS = 3377 )
       integer*4   GL_MAX_CLIP_PLANES
       parameter ( GL_MAX_CLIP_PLANES = 3378 )
       integer*4   GL_MAX_TEXTURE_SIZE
       parameter ( GL_MAX_TEXTURE_SIZE = 3379 )
       integer*4   GL_MAX_PIXEL_MAP_TABLE
       parameter ( GL_MAX_PIXEL_MAP_TABLE = 3380 )
       integer*4   GL_MAX_ATTRIB_STACK_DEPTH
       parameter ( GL_MAX_ATTRIB_STACK_DEPTH = 3381 )
       integer*4   GL_MAX_MODELVIEW_STACK_DEPTH
       parameter ( GL_MAX_MODELVIEW_STACK_DEPTH = 3382 )
       integer*4   GL_MAX_NAME_STACK_DEPTH
       parameter ( GL_MAX_NAME_STACK_DEPTH = 3383 )
       integer*4   GL_MAX_PROJECTION_STACK_DEPTH
       parameter ( GL_MAX_PROJECTION_STACK_DEPTH = 3384 )
       integer*4   GL_MAX_TEXTURE_STACK_DEPTH
       parameter ( GL_MAX_TEXTURE_STACK_DEPTH = 3385 )
       integer*4   GL_MAX_VIEWPORT_DIMS
       parameter ( GL_MAX_VIEWPORT_DIMS = 3386 )
       integer*4   GL_MAX_CLIENT_ATTRIB_STACK_DEPTH
       parameter ( GL_MAX_CLIENT_ATTRIB_STACK_DEPTH = 3387 )
       integer*4   GL_SUBPIXEL_BITS
       parameter ( GL_SUBPIXEL_BITS = 3408 )
       integer*4   GL_INDEX_BITS
       parameter ( GL_INDEX_BITS = 3409 )
       integer*4   GL_RED_BITS
       parameter ( GL_RED_BITS = 3410 )
       integer*4   GL_GREEN_BITS
       parameter ( GL_GREEN_BITS = 3411 )
       integer*4   GL_BLUE_BITS
       parameter ( GL_BLUE_BITS = 3412 )
       integer*4   GL_ALPHA_BITS
       parameter ( GL_ALPHA_BITS = 3413 )
       integer*4   GL_DEPTH_BITS
       parameter ( GL_DEPTH_BITS = 3414 )
       integer*4   GL_STENCIL_BITS
       parameter ( GL_STENCIL_BITS = 3415 )
       integer*4   GL_ACCUM_RED_BITS
       parameter ( GL_ACCUM_RED_BITS = 3416 )
       integer*4   GL_ACCUM_GREEN_BITS
       parameter ( GL_ACCUM_GREEN_BITS = 3417 )
       integer*4   GL_ACCUM_BLUE_BITS
       parameter ( GL_ACCUM_BLUE_BITS = 3418 )
       integer*4   GL_ACCUM_ALPHA_BITS
       parameter ( GL_ACCUM_ALPHA_BITS = 3419 )
       integer*4   GL_NAME_STACK_DEPTH
       parameter ( GL_NAME_STACK_DEPTH = 3440 )
       integer*4   GL_AUTO_NORMAL
       parameter ( GL_AUTO_NORMAL = 3456 )
       integer*4   GL_MAP1_COLOR_4
       parameter ( GL_MAP1_COLOR_4 = 3472 )
       integer*4   GL_MAP1_INDEX
       parameter ( GL_MAP1_INDEX = 3473 )
       integer*4   GL_MAP1_NORMAL
       parameter ( GL_MAP1_NORMAL = 3474 )
       integer*4   GL_MAP1_TEXTURE_COORD_1
       parameter ( GL_MAP1_TEXTURE_COORD_1 = 3475 )
       integer*4   GL_MAP1_TEXTURE_COORD_2
       parameter ( GL_MAP1_TEXTURE_COORD_2 = 3476 )
       integer*4   GL_MAP1_TEXTURE_COORD_3
       parameter ( GL_MAP1_TEXTURE_COORD_3 = 3477 )
       integer*4   GL_MAP1_TEXTURE_COORD_4
       parameter ( GL_MAP1_TEXTURE_COORD_4 = 3478 )
       integer*4   GL_MAP1_VERTEX_3
       parameter ( GL_MAP1_VERTEX_3 = 3479 )
       integer*4   GL_MAP1_VERTEX_4
       parameter ( GL_MAP1_VERTEX_4 = 3480 )
       integer*4   GL_MAP2_COLOR_4
       parameter ( GL_MAP2_COLOR_4 = 3504 )
       integer*4   GL_MAP2_INDEX
       parameter ( GL_MAP2_INDEX = 3505 )
       integer*4   GL_MAP2_NORMAL
       parameter ( GL_MAP2_NORMAL = 3506 )
       integer*4   GL_MAP2_TEXTURE_COORD_1
       parameter ( GL_MAP2_TEXTURE_COORD_1 = 3507 )
       integer*4   GL_MAP2_TEXTURE_COORD_2
       parameter ( GL_MAP2_TEXTURE_COORD_2 = 3508 )
       integer*4   GL_MAP2_TEXTURE_COORD_3
       parameter ( GL_MAP2_TEXTURE_COORD_3 = 3509 )
       integer*4   GL_MAP2_TEXTURE_COORD_4
       parameter ( GL_MAP2_TEXTURE_COORD_4 = 3510 )
       integer*4   GL_MAP2_VERTEX_3
       parameter ( GL_MAP2_VERTEX_3 = 3511 )
       integer*4   GL_MAP2_VERTEX_4
       parameter ( GL_MAP2_VERTEX_4 = 3512 )
       integer*4   GL_MAP1_GRID_DOMAIN
       parameter ( GL_MAP1_GRID_DOMAIN = 3536 )
       integer*4   GL_MAP1_GRID_SEGMENTS
       parameter ( GL_MAP1_GRID_SEGMENTS = 3537 )
       integer*4   GL_MAP2_GRID_DOMAIN
       parameter ( GL_MAP2_GRID_DOMAIN = 3538 )
       integer*4   GL_MAP2_GRID_SEGMENTS
       parameter ( GL_MAP2_GRID_SEGMENTS = 3539 )
       integer*4   GL_TEXTURE_1D
       parameter ( GL_TEXTURE_1D = 3552 )
       integer*4   GL_TEXTURE_2D
       parameter ( GL_TEXTURE_2D = 3553 )
       integer*4   GL_FEEDBACK_BUFFER_SIZE
       parameter ( GL_FEEDBACK_BUFFER_SIZE = 3569 )
       integer*4   GL_FEEDBACK_BUFFER_TYPE
       parameter ( GL_FEEDBACK_BUFFER_TYPE = 3570 )
       integer*4   GL_SELECTION_BUFFER_SIZE
       parameter ( GL_SELECTION_BUFFER_SIZE = 3572 )
       integer*4   GL_POLYGON_OFFSET_UNITS
       parameter ( GL_POLYGON_OFFSET_UNITS = 10752 )
       integer*4   GL_POLYGON_OFFSET_POINT
       parameter ( GL_POLYGON_OFFSET_POINT = 10753 )
       integer*4   GL_POLYGON_OFFSET_LINE
       parameter ( GL_POLYGON_OFFSET_LINE = 10754 )
       integer*4   GL_POLYGON_OFFSET_FILL
       parameter ( GL_POLYGON_OFFSET_FILL = 32823 )
       integer*4   GL_POLYGON_OFFSET_FACTOR
       parameter ( GL_POLYGON_OFFSET_FACTOR = 32824 )
       integer*4   GL_TEXTURE_BINDING_1D
       parameter ( GL_TEXTURE_BINDING_1D = 32872 )
       integer*4   GL_TEXTURE_BINDING_2D
       parameter ( GL_TEXTURE_BINDING_2D = 32873 )
       integer*4   GL_TEXTURE_BINDING_3D
       parameter ( GL_TEXTURE_BINDING_3D = 32874 )
       integer*4   GL_VERTEX_ARRAY
       parameter ( GL_VERTEX_ARRAY = 32884 )
       integer*4   GL_NORMAL_ARRAY
       parameter ( GL_NORMAL_ARRAY = 32885 )
       integer*4   GL_COLOR_ARRAY
       parameter ( GL_COLOR_ARRAY = 32886 )
       integer*4   GL_INDEX_ARRAY
       parameter ( GL_INDEX_ARRAY = 32887 )
       integer*4   GL_TEXTURE_COORD_ARRAY
       parameter ( GL_TEXTURE_COORD_ARRAY = 32888 )
       integer*4   GL_EDGE_FLAG_ARRAY
       parameter ( GL_EDGE_FLAG_ARRAY = 32889 )
       integer*4   GL_VERTEX_ARRAY_SIZE
       parameter ( GL_VERTEX_ARRAY_SIZE = 32890 )
       integer*4   GL_VERTEX_ARRAY_TYPE
       parameter ( GL_VERTEX_ARRAY_TYPE = 32891 )
       integer*4   GL_VERTEX_ARRAY_STRIDE
       parameter ( GL_VERTEX_ARRAY_STRIDE = 32892 )
       integer*4   GL_NORMAL_ARRAY_TYPE
       parameter ( GL_NORMAL_ARRAY_TYPE = 32894 )
       integer*4   GL_NORMAL_ARRAY_STRIDE
       parameter ( GL_NORMAL_ARRAY_STRIDE = 32895 )
       integer*4   GL_COLOR_ARRAY_SIZE
       parameter ( GL_COLOR_ARRAY_SIZE = 32897 )
       integer*4   GL_COLOR_ARRAY_TYPE
       parameter ( GL_COLOR_ARRAY_TYPE = 32898 )
       integer*4   GL_COLOR_ARRAY_STRIDE
       parameter ( GL_COLOR_ARRAY_STRIDE = 32899 )
       integer*4   GL_INDEX_ARRAY_TYPE
       parameter ( GL_INDEX_ARRAY_TYPE = 32901 )
       integer*4   GL_INDEX_ARRAY_STRIDE
       parameter ( GL_INDEX_ARRAY_STRIDE = 32902 )
       integer*4   GL_TEXTURE_COORD_ARRAY_SIZE
       parameter ( GL_TEXTURE_COORD_ARRAY_SIZE = 32904 )
       integer*4   GL_TEXTURE_COORD_ARRAY_TYPE
       parameter ( GL_TEXTURE_COORD_ARRAY_TYPE = 32905 )
       integer*4   GL_TEXTURE_COORD_ARRAY_STRIDE
       parameter ( GL_TEXTURE_COORD_ARRAY_STRIDE = 32906 )
       integer*4   GL_EDGE_FLAG_ARRAY_STRIDE
       parameter ( GL_EDGE_FLAG_ARRAY_STRIDE = 32908 )
C       GL_CLIP_PLANE0 
C       GL_CLIP_PLANE1 
C       GL_CLIP_PLANE2 
C       GL_CLIP_PLANE3 
C       GL_CLIP_PLANE4 
C       GL_CLIP_PLANE5 
C       GL_LIGHT0 
C       GL_LIGHT1 
C       GL_LIGHT2 
C       GL_LIGHT3 
C       GL_LIGHT4 
C       GL_LIGHT5 
C       GL_LIGHT6 
C       GL_LIGHT7 
C       GL_LIGHT_MODEL_COLOR_CONTROL 
C       GL_BLEND_COLOR_EXT 
C       GL_BLEND_EQUATION_EXT 
C       GL_PACK_CMYK_HINT_EXT 
C       GL_UNPACK_CMYK_HINT_EXT 
C       GL_CONVOLUTION_1D_EXT 
C       GL_CONVOLUTION_2D_EXT 
C       GL_SEPARABLE_2D_EXT 
C       GL_POST_CONVOLUTION_RED_SCALE_EXT 
C       GL_POST_CONVOLUTION_GREEN_SCALE_EXT 
C       GL_POST_CONVOLUTION_BLUE_SCALE_EXT 
C       GL_POST_CONVOLUTION_ALPHA_SCALE_EXT 
C       GL_POST_CONVOLUTION_RED_BIAS_EXT 
C       GL_POST_CONVOLUTION_GREEN_BIAS_EXT 
C       GL_POST_CONVOLUTION_BLUE_BIAS_EXT 
C       GL_POST_CONVOLUTION_ALPHA_BIAS_EXT 
C       GL_HISTOGRAM_EXT 
C       GL_MINMAX_EXT 
C       GL_POLYGON_OFFSET_BIAS_EXT 
C       GL_RESCALE_NORMAL_EXT 
C       GL_SHARED_TEXTURE_PALETTE_EXT 
C       GL_TEXTURE_3D_BINDING_EXT 
C       GL_PACK_SKIP_IMAGES_EXT 
C       GL_PACK_IMAGE_HEIGHT_EXT 
C       GL_UNPACK_SKIP_IMAGES_EXT 
C       GL_UNPACK_IMAGE_HEIGHT_EXT 
C       GL_TEXTURE_3D_EXT 
C       GL_MAX_3D_TEXTURE_SIZE_EXT 
C       GL_VERTEX_ARRAY_COUNT_EXT 
C       GL_NORMAL_ARRAY_COUNT_EXT 
C       GL_COLOR_ARRAY_COUNT_EXT 
C       GL_INDEX_ARRAY_COUNT_EXT 
C       GL_TEXTURE_COORD_ARRAY_COUNT_EXT 
C       GL_EDGE_FLAG_ARRAY_COUNT_EXT 
C       GL_INTERLACE_READ_INGR 
C       GL_DETAIL_TEXTURE_2D_BINDING_SGIS 
C       GL_FOG_FUNC_POINTS_SGIS 
C       GL_MAX_FOG_FUNC_POINTS_SGIS 
C       GL_GENERATE_MIPMAP_HINT_SGIS 
C       GL_MULTISAMPLE_SGIS 
C       GL_SAMPLE_ALPHA_TO_MASK_SGIS 
C       GL_SAMPLE_ALPHA_TO_ONE_SGIS 
C       GL_SAMPLE_MASK_SGIS 
C       GL_SAMPLE_BUFFERS_SGIS 
C       GL_SAMPLES_SGIS 
C       GL_SAMPLE_MASK_VALUE_SGIS 
C       GL_SAMPLE_MASK_INVERT_SGIS 
C       GL_SAMPLE_PATTERN_SGIS 
C       GL_PIXEL_TEXTURE_SGIS 
C       GL_POINT_SIZE_MIN_SGIS 
C       GL_POINT_SIZE_MAX_SGIS 
C       GL_POINT_FADE_THRESHOLD_SIZE_SGIS 
C       GL_DISTANCE_ATTENUATION_SGIS 
C       GL_PACK_SKIP_VOLUMES_SGIS 
C       GL_PACK_IMAGE_DEPTH_SGIS 
C       GL_UNPACK_SKIP_VOLUMES_SGIS 
C       GL_UNPACK_IMAGE_DEPTH_SGIS 
C       GL_TEXTURE_4D_SGIS 
C       GL_MAX_4D_TEXTURE_SIZE_SGIS 
C       GL_TEXTURE_4D_BINDING_SGIS 
C       GL_ASYNC_MARKER_SGIX 
C       GL_ASYNC_HISTOGRAM_SGIX 
C       GL_MAX_ASYNC_HISTOGRAM_SGIX 
C       GL_ASYNC_TEX_IMAGE_SGIX 
C       GL_ASYNC_DRAW_PIXELS_SGIX 
C       GL_ASYNC_READ_PIXELS_SGIX 
C       GL_MAX_ASYNC_TEX_IMAGE_SGIX 
C       GL_MAX_ASYNC_DRAW_PIXELS_SGIX 
C       GL_MAX_ASYNC_READ_PIXELS_SGIX 
C       GL_CALLIGRAPHIC_FRAGMENT_SGIX 
C       GL_MAX_CLIPMAP_VIRTUAL_DEPTH_SGIX 
C       GL_MAX_CLIPMAP_DEPTH_SGIX 
C       GL_CONVOLUTION_HINT_SGIX 
C       GL_FOG_OFFSET_SGIX 
C       GL_FOG_OFFSET_VALUE_SGIX 
C       GL_FRAGMENT_LIGHTING_SGIX 
C       GL_FRAGMENT_COLOR_MATERIAL_SGIX 
C       GL_FRAGMENT_COLOR_MATERIAL_FACE_SGIX 
C       GL_FRAGMENT_COLOR_MATERIAL_PARAMETER_SGIX 
C       GL_MAX_FRAGMENT_LIGHTS_SGIX 
C       GL_MAX_ACTIVE_LIGHTS_SGIX 
C       GL_LIGHT_ENV_MODE_SGIX 
C       GL_FRAGMENT_LIGHT_MODEL_LOCAL_VIEWER_SGIX 
C       GL_FRAGMENT_LIGHT_MODEL_TWO_SIDE_SGIX 
C       GL_FRAGMENT_LIGHT_MODEL_AMBIENT_SGIX 
C       GL_FRAGMENT_LIGHT_MODEL_NORMAL_INTERPOLATION_SGIX 
C       GL_FRAGMENT_LIGHT0_SGIX 
C       GL_FRAMEZOOM_SGIX 
C       GL_FRAMEZOOM_FACTOR_SGIX 
C       GL_MAX_FRAMEZOOM_FACTOR_SGIX 
C       GL_INSTRUMENT_MEASUREMENTS_SGIX 
C       GL_INTERLACE_SGIX 
C       GL_IR_INSTRUMENT1_SGIX 
C       GL_PIXEL_TEX_GEN_SGIX 
C       GL_PIXEL_TEX_GEN_MODE_SGIX 
C       GL_PIXEL_TILE_BEST_ALIGNMENT_SGIX 
C       GL_PIXEL_TILE_CACHE_INCREMENT_SGIX 
C       GL_PIXEL_TILE_WIDTH_SGIX 
C       GL_PIXEL_TILE_HEIGHT_SGIX 
C       GL_PIXEL_TILE_GRID_WIDTH_SGIX 
C       GL_PIXEL_TILE_GRID_HEIGHT_SGIX 
C       GL_PIXEL_TILE_GRID_DEPTH_SGIX 
C       GL_PIXEL_TILE_CACHE_SIZE_SGIX 
C       GL_DEFORMATIONS_MASK_SGIX 
C       GL_REFERENCE_PLANE_EQUATION_SGIX 
C       GL_REFERENCE_PLANE_SGIX 
C       GL_SCALEBIAS_HINT_SGIX 
C       GL_SPRITE_SGIX 
C       GL_SPRITE_MODE_SGIX 
C       GL_SPRITE_AXIS_SGIX 
C       GL_SPRITE_TRANSLATION_SGIX 
C       GL_PACK_SUBSAMPLE_RATE_SGIX 
C       GL_UNPACK_SUBSAMPLE_RATE_SGIX 
C       GL_PACK_RESAMPLE_SGIX 
C       GL_UNPACK_RESAMPLE_SGIX 
C       GL_POST_TEXTURE_FILTER_BIAS_RANGE_SGIX 
C       GL_POST_TEXTURE_FILTER_SCALE_RANGE_SGIX 
C       GL_VERTEX_PRECLIP_SGIX 
C       GL_VERTEX_PRECLIP_HINT_SGIX 
C       GL_COLOR_MATRIX_SGI 
C       GL_COLOR_MATRIX_STACK_DEPTH_SGI 
C       GL_MAX_COLOR_MATRIX_STACK_DEPTH_SGI 
C       GL_POST_COLOR_MATRIX_RED_SCALE_SGI 
C       GL_POST_COLOR_MATRIX_GREEN_SCALE_SGI 
C       GL_POST_COLOR_MATRIX_BLUE_SCALE_SGI 
C       GL_POST_COLOR_MATRIX_ALPHA_SCALE_SGI 
C       GL_POST_COLOR_MATRIX_RED_BIAS_SGI 
C       GL_POST_COLOR_MATRIX_GREEN_BIAS_SGI 
C       GL_POST_COLOR_MATRIX_BLUE_BIAS_SGI 
C       GL_POST_COLOR_MATRIX_ALPHA_BIAS_SGI 
C       GL_COLOR_TABLE_SGI 
C       GL_POST_CONVOLUTION_COLOR_TABLE_SGI 
C       GL_POST_COLOR_MATRIX_COLOR_TABLE_SGI 
C       GL_TEXTURE_COLOR_TABLE_SGI 

C  GetTextureParameter 
C       GL_TEXTURE_MAG_FILTER 
C       GL_TEXTURE_MIN_FILTER 
C       GL_TEXTURE_WRAP_S 
C       GL_TEXTURE_WRAP_T 
       integer*4   GL_TEXTURE_WIDTH
       parameter ( GL_TEXTURE_WIDTH = 4096 )
       integer*4   GL_TEXTURE_HEIGHT
       parameter ( GL_TEXTURE_HEIGHT = 4097 )
       integer*4   GL_TEXTURE_INTERNAL_FORMAT
       parameter ( GL_TEXTURE_INTERNAL_FORMAT = 4099 )
       integer*4   GL_TEXTURE_COMPONENTS
       parameter ( GL_TEXTURE_COMPONENTS = 4099 )
       integer*4   GL_TEXTURE_BORDER_COLOR
       parameter ( GL_TEXTURE_BORDER_COLOR = 4100 )
       integer*4   GL_TEXTURE_BORDER
       parameter ( GL_TEXTURE_BORDER = 4101 )
       integer*4   GL_TEXTURE_RED_SIZE
       parameter ( GL_TEXTURE_RED_SIZE = 32860 )
       integer*4   GL_TEXTURE_GREEN_SIZE
       parameter ( GL_TEXTURE_GREEN_SIZE = 32861 )
       integer*4   GL_TEXTURE_BLUE_SIZE
       parameter ( GL_TEXTURE_BLUE_SIZE = 32862 )
       integer*4   GL_TEXTURE_ALPHA_SIZE
       parameter ( GL_TEXTURE_ALPHA_SIZE = 32863 )
       integer*4   GL_TEXTURE_LUMINANCE_SIZE
       parameter ( GL_TEXTURE_LUMINANCE_SIZE = 32864 )
       integer*4   GL_TEXTURE_INTENSITY_SIZE
       parameter ( GL_TEXTURE_INTENSITY_SIZE = 32865 )
       integer*4   GL_TEXTURE_PRIORITY
       parameter ( GL_TEXTURE_PRIORITY = 32870 )
       integer*4   GL_TEXTURE_RESIDENT
       parameter ( GL_TEXTURE_RESIDENT = 32871 )
C       GL_TEXTURE_DEPTH_EXT 
C       GL_TEXTURE_WRAP_R_EXT 
C       GL_DETAIL_TEXTURE_LEVEL_SGIS 
C       GL_DETAIL_TEXTURE_MODE_SGIS 
C       GL_DETAIL_TEXTURE_FUNC_POINTS_SGIS 
C       GL_GENERATE_MIPMAP_SGIS 
C       GL_SHARPEN_TEXTURE_FUNC_POINTS_SGIS 
C       GL_TEXTURE_FILTER4_SIZE_SGIS 
C       GL_TEXTURE_MIN_LOD_SGIS 
C       GL_TEXTURE_MAX_LOD_SGIS 
C       GL_TEXTURE_BASE_LEVEL_SGIS 
C       GL_TEXTURE_MAX_LEVEL_SGIS 
C       GL_DUAL_TEXTURE_SELECT_SGIS 
C       GL_QUAD_TEXTURE_SELECT_SGIS 
C       GL_TEXTURE_4DSIZE_SGIS 
C       GL_TEXTURE_WRAP_Q_SGIS 
C       GL_TEXTURE_CLIPMAP_CENTER_SGIX 
C       GL_TEXTURE_CLIPMAP_FRAME_SGIX 
C       GL_TEXTURE_CLIPMAP_OFFSET_SGIX 
C       GL_TEXTURE_CLIPMAP_VIRTUAL_DEPTH_SGIX 
C       GL_TEXTURE_CLIPMAP_LOD_OFFSET_SGIX 
C       GL_TEXTURE_CLIPMAP_DEPTH_SGIX 
C       GL_TEXTURE_COMPARE_SGIX 
C       GL_TEXTURE_COMPARE_OPERATOR_SGIX 
C       GL_TEXTURE_LEQUAL_R_SGIX 
C       GL_TEXTURE_GEQUAL_R_SGIX 
C       GL_SHADOW_AMBIENT_SGIX 
C       GL_TEXTURE_MAX_CLAMP_S_SGIX 
C       GL_TEXTURE_MAX_CLAMP_T_SGIX 
C       GL_TEXTURE_MAX_CLAMP_R_SGIX 
C       GL_TEXTURE_LOD_BIAS_S_SGIX 
C       GL_TEXTURE_LOD_BIAS_T_SGIX 
C       GL_TEXTURE_LOD_BIAS_R_SGIX 
C       GL_POST_TEXTURE_FILTER_BIAS_SGIX 
C       GL_POST_TEXTURE_FILTER_SCALE_SGIX 

C  HintMode 
       integer*4   GL_DONT_CARE
       parameter ( GL_DONT_CARE = 4352 )
       integer*4   GL_FASTEST
       parameter ( GL_FASTEST = 4353 )
       integer*4   GL_NICEST
       parameter ( GL_NICEST = 4354 )

C  HintTarget 
C       GL_PERSPECTIVE_CORRECTION_HINT 
C       GL_POINT_SMOOTH_HINT 
C       GL_LINE_SMOOTH_HINT 
C       GL_POLYGON_SMOOTH_HINT 
C       GL_FOG_HINT 
C       GL_PACK_CMYK_HINT_EXT 
C       GL_UNPACK_CMYK_HINT_EXT 
C       GL_GENERATE_MIPMAP_HINT_SGIS 
C       GL_CONVOLUTION_HINT_SGIX 
C       GL_SCALEBIAS_HINT_SGIX 
C       GL_TEXTURE_MULTI_BUFFER_HINT_SGIX 
C       GL_VERTEX_PRECLIP_HINT_SGIX 

C  HistogramTargetEXT 
C       GL_HISTOGRAM_EXT 
C       GL_PROXY_HISTOGRAM_EXT 

C  IndexPointerType 
C       GL_SHORT 
C       GL_INT 
C       GL_FLOAT 
C       GL_DOUBLE 

C  LightEnvModeSGIX 
C       GL_REPLACE 
C       GL_MODULATE 
C       GL_ADD 

C  LightEnvParameterSGIX 
C       GL_LIGHT_ENV_MODE_SGIX 

C  LightModelColorControl 
C       GL_SINGLE_COLOR 
C       GL_SEPARATE_SPECULAR_COLOR 

C  LightModelParameter 
C       GL_LIGHT_MODEL_AMBIENT 
C       GL_LIGHT_MODEL_LOCAL_VIEWER 
C       GL_LIGHT_MODEL_TWO_SIDE 
C       GL_LIGHT_MODEL_COLOR_CONTROL 

C  LightParameter 
       integer*4   GL_AMBIENT
       parameter ( GL_AMBIENT = 4608 )
       integer*4   GL_DIFFUSE
       parameter ( GL_DIFFUSE = 4609 )
       integer*4   GL_SPECULAR
       parameter ( GL_SPECULAR = 4610 )
       integer*4   GL_POSITION
       parameter ( GL_POSITION = 4611 )
       integer*4   GL_SPOT_DIRECTION
       parameter ( GL_SPOT_DIRECTION = 4612 )
       integer*4   GL_SPOT_EXPONENT
       parameter ( GL_SPOT_EXPONENT = 4613 )
       integer*4   GL_SPOT_CUTOFF
       parameter ( GL_SPOT_CUTOFF = 4614 )
       integer*4   GL_CONSTANT_ATTENUATION
       parameter ( GL_CONSTANT_ATTENUATION = 4615 )
       integer*4   GL_LINEAR_ATTENUATION
       parameter ( GL_LINEAR_ATTENUATION = 4616 )
       integer*4   GL_QUADRATIC_ATTENUATION
       parameter ( GL_QUADRATIC_ATTENUATION = 4617 )

C  ListMode 
       integer*4   GL_COMPILE
       parameter ( GL_COMPILE = 4864 )
       integer*4   GL_COMPILE_AND_EXECUTE
       parameter ( GL_COMPILE_AND_EXECUTE = 4865 )

C  DataType 
       integer*4   GL_BYTE
       parameter ( GL_BYTE = 5120 )
       integer*4   GL_UNSIGNED_BYTE
       parameter ( GL_UNSIGNED_BYTE = 5121 )
       integer*4   GL_SHORT
       parameter ( GL_SHORT = 5122 )
       integer*4   GL_UNSIGNED_SHORT
       parameter ( GL_UNSIGNED_SHORT = 5123 )
       integer*4   GL_INT
       parameter ( GL_INT = 5124 )
       integer*4   GL_UNSIGNED_INT
       parameter ( GL_UNSIGNED_INT = 5125 )
       integer*4   GL_FLOAT
       parameter ( GL_FLOAT = 5126 )
       integer*4   GL_2_BYTES
       parameter ( GL_2_BYTES = 5127 )
       integer*4   GL_3_BYTES
       parameter ( GL_3_BYTES = 5128 )
       integer*4   GL_4_BYTES
       parameter ( GL_4_BYTES = 5129 )
       integer*4   GL_DOUBLE
       parameter ( GL_DOUBLE = 5130 )
       integer*4   GL_DOUBLE_EXT
       parameter ( GL_DOUBLE_EXT = 5130 )

C  ListNameType 
C       GL_BYTE 
C       GL_UNSIGNED_BYTE 
C       GL_SHORT 
C       GL_UNSIGNED_SHORT 
C       GL_INT 
C       GL_UNSIGNED_INT 
C       GL_FLOAT 
C       GL_2_BYTES 
C       GL_3_BYTES 
C       GL_4_BYTES 

C  ListParameterName 
C       GL_LIST_PRIORITY_SGIX 

C  LogicOp 
       integer*4   GL_CLEAR
       parameter ( GL_CLEAR = 5376 )
       integer*4   GL_AND
       parameter ( GL_AND = 5377 )
       integer*4   GL_AND_REVERSE
       parameter ( GL_AND_REVERSE = 5378 )
       integer*4   GL_COPY
       parameter ( GL_COPY = 5379 )
       integer*4   GL_AND_INVERTED
       parameter ( GL_AND_INVERTED = 5380 )
       integer*4   GL_NOOP
       parameter ( GL_NOOP = 5381 )
       integer*4   GL_XOR
       parameter ( GL_XOR = 5382 )
       integer*4   GL_OR
       parameter ( GL_OR = 5383 )
       integer*4   GL_NOR
       parameter ( GL_NOR = 5384 )
       integer*4   GL_EQUIV
       parameter ( GL_EQUIV = 5385 )
       integer*4   GL_INVERT
       parameter ( GL_INVERT = 5386 )
       integer*4   GL_OR_REVERSE
       parameter ( GL_OR_REVERSE = 5387 )
       integer*4   GL_COPY_INVERTED
       parameter ( GL_COPY_INVERTED = 5388 )
       integer*4   GL_OR_INVERTED
       parameter ( GL_OR_INVERTED = 5389 )
       integer*4   GL_NAND
       parameter ( GL_NAND = 5390 )
       integer*4   GL_SET
       parameter ( GL_SET = 5391 )

C  MapTarget 
C       GL_MAP1_COLOR_4 
C       GL_MAP1_INDEX 
C       GL_MAP1_NORMAL 
C       GL_MAP1_TEXTURE_COORD_1 
C       GL_MAP1_TEXTURE_COORD_2 
C       GL_MAP1_TEXTURE_COORD_3 
C       GL_MAP1_TEXTURE_COORD_4 
C       GL_MAP1_VERTEX_3 
C       GL_MAP1_VERTEX_4 
C       GL_MAP2_COLOR_4 
C       GL_MAP2_INDEX 
C       GL_MAP2_NORMAL 
C       GL_MAP2_TEXTURE_COORD_1 
C       GL_MAP2_TEXTURE_COORD_2 
C       GL_MAP2_TEXTURE_COORD_3 
C       GL_MAP2_TEXTURE_COORD_4 
C       GL_MAP2_VERTEX_3 
C       GL_MAP2_VERTEX_4 
C       GL_GEOMETRY_DEFORMATION_SGIX 
C       GL_TEXTURE_DEFORMATION_SGIX 

C  MaterialFace 
C       GL_FRONT 
C       GL_BACK 
C       GL_FRONT_AND_BACK 

C  MaterialParameter 
       integer*4   GL_EMISSION
       parameter ( GL_EMISSION = 5632 )
       integer*4   GL_SHININESS
       parameter ( GL_SHININESS = 5633 )
       integer*4   GL_AMBIENT_AND_DIFFUSE
       parameter ( GL_AMBIENT_AND_DIFFUSE = 5634 )
       integer*4   GL_COLOR_INDEXES
       parameter ( GL_COLOR_INDEXES = 5635 )
C       GL_AMBIENT 
C       GL_DIFFUSE 
C       GL_SPECULAR 

C  MatrixMode 
       integer*4   GL_MODELVIEW
       parameter ( GL_MODELVIEW = 5888 )
       integer*4   GL_PROJECTION
       parameter ( GL_PROJECTION = 5889 )
       integer*4   GL_TEXTURE
       parameter ( GL_TEXTURE = 5890 )

C  MeshMode1 
C       GL_POINT 
C       GL_LINE 

C  MeshMode2 
C       GL_POINT 
C       GL_LINE 
C       GL_FILL 

C  MinmaxTargetEXT 
C       GL_MINMAX_EXT 

C  NormalPointerType 
C       GL_BYTE 
C       GL_SHORT 
C       GL_INT 
C       GL_FLOAT 
C       GL_DOUBLE 

C  PixelCopyType 
       integer*4   GL_COLOR
       parameter ( GL_COLOR = 6144 )
       integer*4   GL_DEPTH
       parameter ( GL_DEPTH = 6145 )
       integer*4   GL_STENCIL
       parameter ( GL_STENCIL = 6146 )

C  PixelFormat 
       integer*4   GL_COLOR_INDEX
       parameter ( GL_COLOR_INDEX = 6400 )
       integer*4   GL_STENCIL_INDEX
       parameter ( GL_STENCIL_INDEX = 6401 )
       integer*4   GL_DEPTH_COMPONENT
       parameter ( GL_DEPTH_COMPONENT = 6402 )
       integer*4   GL_RED
       parameter ( GL_RED = 6403 )
       integer*4   GL_GREEN
       parameter ( GL_GREEN = 6404 )
       integer*4   GL_BLUE
       parameter ( GL_BLUE = 6405 )
       integer*4   GL_ALPHA
       parameter ( GL_ALPHA = 6406 )
       integer*4   GL_RGB
       parameter ( GL_RGB = 6407 )
       integer*4   GL_RGBA
       parameter ( GL_RGBA = 6408 )
       integer*4   GL_LUMINANCE
       parameter ( GL_LUMINANCE = 6409 )
       integer*4   GL_LUMINANCE_ALPHA
       parameter ( GL_LUMINANCE_ALPHA = 6410 )
C       GL_ABGR_EXT 
C       GL_CMYK_EXT 
C       GL_CMYKA_EXT 
C       GL_R5_G6_B5_ICC_SGIX 
C       GL_R5_G6_B5_A8_ICC_SGIX 
C       GL_ALPHA16_ICC_SGIX 
C       GL_LUMINANCE16_ICC_SGIX 
C       GL_LUMINANCE16_ALPHA8_ICC_SGIX 
C       GL_YCRCB_422_SGIX 
C       GL_YCRCB_444_SGIX 

C  PixelMap 
C       GL_PIXEL_MAP_I_TO_I 
C       GL_PIXEL_MAP_S_TO_S 
C       GL_PIXEL_MAP_I_TO_R 
C       GL_PIXEL_MAP_I_TO_G 
C       GL_PIXEL_MAP_I_TO_B 
C       GL_PIXEL_MAP_I_TO_A 
C       GL_PIXEL_MAP_R_TO_R 
C       GL_PIXEL_MAP_G_TO_G 
C       GL_PIXEL_MAP_B_TO_B 
C       GL_PIXEL_MAP_A_TO_A 

C  PixelStoreParameter 
C       GL_UNPACK_SWAP_BYTES 
C       GL_UNPACK_LSB_FIRST 
C       GL_UNPACK_ROW_LENGTH 
C       GL_UNPACK_SKIP_ROWS 
C       GL_UNPACK_SKIP_PIXELS 
C       GL_UNPACK_ALIGNMENT 
C       GL_PACK_SWAP_BYTES 
C       GL_PACK_LSB_FIRST 
C       GL_PACK_ROW_LENGTH 
C       GL_PACK_SKIP_ROWS 
C       GL_PACK_SKIP_PIXELS 
C       GL_PACK_ALIGNMENT 
C       GL_PACK_SKIP_IMAGES_EXT 
C       GL_PACK_IMAGE_HEIGHT_EXT 
C       GL_UNPACK_SKIP_IMAGES_EXT 
C       GL_UNPACK_IMAGE_HEIGHT_EXT 
C       GL_PACK_SKIP_VOLUMES_SGIS 
C       GL_PACK_IMAGE_DEPTH_SGIS 
C       GL_UNPACK_SKIP_VOLUMES_SGIS 
C       GL_UNPACK_IMAGE_DEPTH_SGIS 
C       GL_PIXEL_TILE_WIDTH_SGIX 
C       GL_PIXEL_TILE_HEIGHT_SGIX 
C       GL_PIXEL_TILE_GRID_WIDTH_SGIX 
C       GL_PIXEL_TILE_GRID_HEIGHT_SGIX 
C       GL_PIXEL_TILE_GRID_DEPTH_SGIX 
C       GL_PIXEL_TILE_CACHE_SIZE_SGIX 
C       GL_PACK_SUBSAMPLE_RATE_SGIX 
C       GL_UNPACK_SUBSAMPLE_RATE_SGIX 
C       GL_PACK_RESAMPLE_SGIX 
C       GL_UNPACK_RESAMPLE_SGIX 

C  PixelStoreResampleMode 
C       GL_RESAMPLE_REPLICATE_SGIX 
C       GL_RESAMPLE_ZERO_FILL_SGIX 
C       GL_RESAMPLE_DECIMATE_SGIX 

C  PixelStoreSubsampleRate 
C       GL_PIXEL_SUBSAMPLE_4444_SGIX 
C       GL_PIXEL_SUBSAMPLE_2424_SGIX 
C       GL_PIXEL_SUBSAMPLE_4242_SGIX 

C  PixelTexGenMode 
C       GL_NONE 
C       GL_RGB 
C       GL_RGBA 
C       GL_LUMINANCE 
C       GL_LUMINANCE_ALPHA 
C       GL_PIXEL_TEX_GEN_ALPHA_REPLACE_SGIX 
C       GL_PIXEL_TEX_GEN_ALPHA_NO_REPLACE_SGIX 
C       GL_PIXEL_TEX_GEN_ALPHA_MS_SGIX 
C       GL_PIXEL_TEX_GEN_ALPHA_LS_SGIX 

C  PixelTexGenParameterNameSGIS 
C       GL_PIXEL_FRAGMENT_RGB_SOURCE_SGIS 
C       GL_PIXEL_FRAGMENT_ALPHA_SOURCE_SGIS 

C  PixelTransferParameter 
C       GL_MAP_COLOR 
C       GL_MAP_STENCIL 
C       GL_INDEX_SHIFT 
C       GL_INDEX_OFFSET 
C       GL_RED_SCALE 
C       GL_RED_BIAS 
C       GL_GREEN_SCALE 
C       GL_GREEN_BIAS 
C       GL_BLUE_SCALE 
C       GL_BLUE_BIAS 
C       GL_ALPHA_SCALE 
C       GL_ALPHA_BIAS 
C       GL_DEPTH_SCALE 
C       GL_DEPTH_BIAS 
C       GL_POST_CONVOLUTION_RED_SCALE_EXT 
C       GL_POST_CONVOLUTION_GREEN_SCALE_EXT 
C       GL_POST_CONVOLUTION_BLUE_SCALE_EXT 
C       GL_POST_CONVOLUTION_ALPHA_SCALE_EXT 
C       GL_POST_CONVOLUTION_RED_BIAS_EXT 
C       GL_POST_CONVOLUTION_GREEN_BIAS_EXT 
C       GL_POST_CONVOLUTION_BLUE_BIAS_EXT 
C       GL_POST_CONVOLUTION_ALPHA_BIAS_EXT 
C       GL_POST_COLOR_MATRIX_RED_SCALE_SGI 
C       GL_POST_COLOR_MATRIX_GREEN_SCALE_SGI 
C       GL_POST_COLOR_MATRIX_BLUE_SCALE_SGI 
C       GL_POST_COLOR_MATRIX_ALPHA_SCALE_SGI 
C       GL_POST_COLOR_MATRIX_RED_BIAS_SGI 
C       GL_POST_COLOR_MATRIX_GREEN_BIAS_SGI 
C       GL_POST_COLOR_MATRIX_BLUE_BIAS_SGI 
C       GL_POST_COLOR_MATRIX_ALPHA_BIAS_SGI 

C  PixelType 
       integer*4   GL_BITMAP
       parameter ( GL_BITMAP = 6656 )
C       GL_BYTE 
C       GL_UNSIGNED_BYTE 
C       GL_SHORT 
C       GL_UNSIGNED_SHORT 
C       GL_INT 
C       GL_UNSIGNED_INT 
C       GL_FLOAT 
C       GL_UNSIGNED_BYTE_3_3_2_EXT 
C       GL_UNSIGNED_SHORT_4_4_4_4_EXT 
C       GL_UNSIGNED_SHORT_5_5_5_1_EXT 
C       GL_UNSIGNED_INT_8_8_8_8_EXT 
C       GL_UNSIGNED_INT_10_10_10_2_EXT 

C  PointParameterNameSGIS 
C       GL_POINT_SIZE_MIN_SGIS 
C       GL_POINT_SIZE_MAX_SGIS 
C       GL_POINT_FADE_THRESHOLD_SIZE_SGIS 
C       GL_DISTANCE_ATTENUATION_SGIS 

C  PolygonMode 
       integer*4   GL_POINT
       parameter ( GL_POINT = 6912 )
       integer*4   GL_LINE
       parameter ( GL_LINE = 6913 )
       integer*4   GL_FILL
       parameter ( GL_FILL = 6914 )

C  ReadBufferMode 
C       GL_FRONT_LEFT 
C       GL_FRONT_RIGHT 
C       GL_BACK_LEFT 
C       GL_BACK_RIGHT 
C       GL_FRONT 
C       GL_BACK 
C       GL_LEFT 
C       GL_RIGHT 
C       GL_AUX0 
C       GL_AUX1 
C       GL_AUX2 
C       GL_AUX3 

C  RenderingMode 
       integer*4   GL_RENDER
       parameter ( GL_RENDER = 7168 )
       integer*4   GL_FEEDBACK
       parameter ( GL_FEEDBACK = 7169 )
       integer*4   GL_SELECT
       parameter ( GL_SELECT = 7170 )

C  SamplePatternPatternSGIS 
C       GL_1PASS_SGIS 
C       GL_2PASS_0_SGIS 
C       GL_2PASS_1_SGIS 
C       GL_4PASS_0_SGIS 
C       GL_4PASS_1_SGIS 
C       GL_4PASS_2_SGIS 
C       GL_4PASS_3_SGIS 

C  SeparableTargetEXT 
C       GL_SEPARABLE_2D_EXT 

C  ShadingModel 
       integer*4   GL_FLAT
       parameter ( GL_FLAT = 7424 )
       integer*4   GL_SMOOTH
       parameter ( GL_SMOOTH = 7425 )

C  StencilFunction 
C       GL_NEVER 
C       GL_LESS 
C       GL_EQUAL 
C       GL_LEQUAL 
C       GL_GREATER 
C       GL_NOTEQUAL 
C       GL_GEQUAL 
C       GL_ALWAYS 

C  StencilOp 
C       GL_ZERO 
       integer*4   GL_KEEP
       parameter ( GL_KEEP = 7680 )
       integer*4   GL_REPLACE
       parameter ( GL_REPLACE = 7681 )
       integer*4   GL_INCR
       parameter ( GL_INCR = 7682 )
       integer*4   GL_DECR
       parameter ( GL_DECR = 7683 )
C       GL_INVERT 

C  StringName 
       integer*4   GL_VENDOR
       parameter ( GL_VENDOR = 7936 )
       integer*4   GL_RENDERER
       parameter ( GL_RENDERER = 7937 )
       integer*4   GL_VERSION
       parameter ( GL_VERSION = 7938 )
       integer*4   GL_EXTENSIONS
       parameter ( GL_EXTENSIONS = 7939 )

C  TexCoordPointerType 
C       GL_SHORT 
C       GL_INT 
C       GL_FLOAT 
C       GL_DOUBLE 

C  TextureCoordName 
       integer*4   GL_S
       parameter ( GL_S = 8192 )
       integer*4   GL_T
       parameter ( GL_T = 8193 )
       integer*4   GL_R
       parameter ( GL_R = 8194 )
       integer*4   GL_Q
       parameter ( GL_Q = 8195 )

C  TextureEnvMode 
       integer*4   GL_MODULATE
       parameter ( GL_MODULATE = 8448 )
       integer*4   GL_DECAL
       parameter ( GL_DECAL = 8449 )
C       GL_BLEND 
C       GL_REPLACE_EXT 
C       GL_ADD 
C       GL_TEXTURE_ENV_BIAS_SGIX 

C  TextureEnvParameter 
       integer*4   GL_TEXTURE_ENV_MODE
       parameter ( GL_TEXTURE_ENV_MODE = 8704 )
       integer*4   GL_TEXTURE_ENV_COLOR
       parameter ( GL_TEXTURE_ENV_COLOR = 8705 )

C  TextureEnvTarget 
       integer*4   GL_TEXTURE_ENV
       parameter ( GL_TEXTURE_ENV = 8960 )

C  TextureFilterFuncSGIS 
C       GL_FILTER4_SGIS 

C  TextureGenMode 
       integer*4   GL_EYE_LINEAR
       parameter ( GL_EYE_LINEAR = 9216 )
       integer*4   GL_OBJECT_LINEAR
       parameter ( GL_OBJECT_LINEAR = 9217 )
       integer*4   GL_SPHERE_MAP
       parameter ( GL_SPHERE_MAP = 9218 )
C       GL_EYE_DISTANCE_TO_POINT_SGIS 
C       GL_OBJECT_DISTANCE_TO_POINT_SGIS 
C       GL_EYE_DISTANCE_TO_LINE_SGIS 
C       GL_OBJECT_DISTANCE_TO_LINE_SGIS 

C  TextureGenParameter 
       integer*4   GL_TEXTURE_GEN_MODE
       parameter ( GL_TEXTURE_GEN_MODE = 9472 )
       integer*4   GL_OBJECT_PLANE
       parameter ( GL_OBJECT_PLANE = 9473 )
       integer*4   GL_EYE_PLANE
       parameter ( GL_EYE_PLANE = 9474 )
C       GL_EYE_POINT_SGIS 
C       GL_OBJECT_POINT_SGIS 
C       GL_EYE_LINE_SGIS 
C       GL_OBJECT_LINE_SGIS 

C  TextureMagFilter 
       integer*4   GL_NEAREST
       parameter ( GL_NEAREST = 9728 )
       integer*4   GL_LINEAR
       parameter ( GL_LINEAR = 9729 )
C       GL_LINEAR_DETAIL_SGIS 
C       GL_LINEAR_DETAIL_ALPHA_SGIS 
C       GL_LINEAR_DETAIL_COLOR_SGIS 
C       GL_LINEAR_SHARPEN_SGIS 
C       GL_LINEAR_SHARPEN_ALPHA_SGIS 
C       GL_LINEAR_SHARPEN_COLOR_SGIS 
C       GL_FILTER4_SGIS 
C       GL_PIXEL_TEX_GEN_Q_CEILING_SGIX 
C       GL_PIXEL_TEX_GEN_Q_ROUND_SGIX 
C       GL_PIXEL_TEX_GEN_Q_FLOOR_SGIX 

C  TextureMinFilter 
C       GL_NEAREST 
C       GL_LINEAR 
       integer*4   GL_NEAREST_MIPMAP_NEAREST
       parameter ( GL_NEAREST_MIPMAP_NEAREST = 9984 )
       integer*4   GL_LINEAR_MIPMAP_NEAREST
       parameter ( GL_LINEAR_MIPMAP_NEAREST = 9985 )
       integer*4   GL_NEAREST_MIPMAP_LINEAR
       parameter ( GL_NEAREST_MIPMAP_LINEAR = 9986 )
       integer*4   GL_LINEAR_MIPMAP_LINEAR
       parameter ( GL_LINEAR_MIPMAP_LINEAR = 9987 )
C       GL_FILTER4_SGIS 
C       GL_LINEAR_CLIPMAP_LINEAR_SGIX 
C       GL_NEAREST_CLIPMAP_NEAREST_SGIX 
C       GL_NEAREST_CLIPMAP_LINEAR_SGIX 
C       GL_LINEAR_CLIPMAP_NEAREST_SGIX 
C       GL_PIXEL_TEX_GEN_Q_CEILING_SGIX 
C       GL_PIXEL_TEX_GEN_Q_ROUND_SGIX 
C       GL_PIXEL_TEX_GEN_Q_FLOOR_SGIX 

C  TextureParameterName 
       integer*4   GL_TEXTURE_MAG_FILTER
       parameter ( GL_TEXTURE_MAG_FILTER = 10240 )
       integer*4   GL_TEXTURE_MIN_FILTER
       parameter ( GL_TEXTURE_MIN_FILTER = 10241 )
       integer*4   GL_TEXTURE_WRAP_S
       parameter ( GL_TEXTURE_WRAP_S = 10242 )
       integer*4   GL_TEXTURE_WRAP_T
       parameter ( GL_TEXTURE_WRAP_T = 10243 )
C       GL_TEXTURE_BORDER_COLOR 
C       GL_TEXTURE_PRIORITY 
C       GL_TEXTURE_WRAP_R_EXT 
C       GL_DETAIL_TEXTURE_LEVEL_SGIS 
C       GL_DETAIL_TEXTURE_MODE_SGIS 
C       GL_GENERATE_MIPMAP_SGIS 
C       GL_DUAL_TEXTURE_SELECT_SGIS 
C       GL_QUAD_TEXTURE_SELECT_SGIS 
C       GL_TEXTURE_WRAP_Q_SGIS 
C       GL_TEXTURE_CLIPMAP_CENTER_SGIX 
C       GL_TEXTURE_CLIPMAP_FRAME_SGIX 
C       GL_TEXTURE_CLIPMAP_OFFSET_SGIX 
C       GL_TEXTURE_CLIPMAP_VIRTUAL_DEPTH_SGIX 
C       GL_TEXTURE_CLIPMAP_LOD_OFFSET_SGIX 
C       GL_TEXTURE_CLIPMAP_DEPTH_SGIX 
C       GL_TEXTURE_COMPARE_SGIX 
C       GL_TEXTURE_COMPARE_OPERATOR_SGIX 
C       GL_SHADOW_AMBIENT_SGIX 
C       GL_TEXTURE_MAX_CLAMP_S_SGIX 
C       GL_TEXTURE_MAX_CLAMP_T_SGIX 
C       GL_TEXTURE_MAX_CLAMP_R_SGIX 
C       GL_TEXTURE_LOD_BIAS_S_SGIX 
C       GL_TEXTURE_LOD_BIAS_T_SGIX 
C       GL_TEXTURE_LOD_BIAS_R_SGIX 
C       GL_POST_TEXTURE_FILTER_BIAS_SGIX 
C       GL_POST_TEXTURE_FILTER_SCALE_SGIX 

C  TextureTarget 
C       GL_TEXTURE_1D 
C       GL_TEXTURE_2D 
       integer*4   GL_PROXY_TEXTURE_1D
       parameter ( GL_PROXY_TEXTURE_1D = 32867 )
       integer*4   GL_PROXY_TEXTURE_2D
       parameter ( GL_PROXY_TEXTURE_2D = 32868 )
C       GL_TEXTURE_3D_EXT 
C       GL_PROXY_TEXTURE_3D_EXT 
C       GL_DETAIL_TEXTURE_2D_SGIS 
C       GL_TEXTURE_4D_SGIS 
C       GL_PROXY_TEXTURE_4D_SGIS 
C       GL_TEXTURE_MIN_LOD_SGIS 
C       GL_TEXTURE_MAX_LOD_SGIS 
C       GL_TEXTURE_BASE_LEVEL_SGIS 
C       GL_TEXTURE_MAX_LEVEL_SGIS 

C  TextureWrapMode 
       integer*4   GL_CLAMP
       parameter ( GL_CLAMP = 10496 )
       integer*4   GL_REPEAT
       parameter ( GL_REPEAT = 10497 )
C       GL_CLAMP_TO_BORDER_SGIS 
C       GL_CLAMP_TO_EDGE_SGIS 

C  PixelInternalFormat 
       integer*4   GL_R3_G3_B2
       parameter ( GL_R3_G3_B2 = 10768 )
       integer*4   GL_ALPHA4
       parameter ( GL_ALPHA4 = 32827 )
       integer*4   GL_ALPHA8
       parameter ( GL_ALPHA8 = 32828 )
       integer*4   GL_ALPHA12
       parameter ( GL_ALPHA12 = 32829 )
       integer*4   GL_ALPHA16
       parameter ( GL_ALPHA16 = 32830 )
       integer*4   GL_LUMINANCE4
       parameter ( GL_LUMINANCE4 = 32831 )
       integer*4   GL_LUMINANCE8
       parameter ( GL_LUMINANCE8 = 32832 )
       integer*4   GL_LUMINANCE12
       parameter ( GL_LUMINANCE12 = 32833 )
       integer*4   GL_LUMINANCE16
       parameter ( GL_LUMINANCE16 = 32834 )
       integer*4   GL_LUMINANCE4_ALPHA4
       parameter ( GL_LUMINANCE4_ALPHA4 = 32835 )
       integer*4   GL_LUMINANCE6_ALPHA2
       parameter ( GL_LUMINANCE6_ALPHA2 = 32836 )
       integer*4   GL_LUMINANCE8_ALPHA8
       parameter ( GL_LUMINANCE8_ALPHA8 = 32837 )
       integer*4   GL_LUMINANCE12_ALPHA4
       parameter ( GL_LUMINANCE12_ALPHA4 = 32838 )
       integer*4   GL_LUMINANCE12_ALPHA12
       parameter ( GL_LUMINANCE12_ALPHA12 = 32839 )
       integer*4   GL_LUMINANCE16_ALPHA16
       parameter ( GL_LUMINANCE16_ALPHA16 = 32840 )
       integer*4   GL_INTENSITY
       parameter ( GL_INTENSITY = 32841 )
       integer*4   GL_INTENSITY4
       parameter ( GL_INTENSITY4 = 32842 )
       integer*4   GL_INTENSITY8
       parameter ( GL_INTENSITY8 = 32843 )
       integer*4   GL_INTENSITY12
       parameter ( GL_INTENSITY12 = 32844 )
       integer*4   GL_INTENSITY16
       parameter ( GL_INTENSITY16 = 32845 )
       integer*4   GL_RGB4
       parameter ( GL_RGB4 = 32847 )
       integer*4   GL_RGB5
       parameter ( GL_RGB5 = 32848 )
       integer*4   GL_RGB8
       parameter ( GL_RGB8 = 32849 )
       integer*4   GL_RGB10
       parameter ( GL_RGB10 = 32850 )
       integer*4   GL_RGB12
       parameter ( GL_RGB12 = 32851 )
       integer*4   GL_RGB16
       parameter ( GL_RGB16 = 32852 )
       integer*4   GL_RGBA2
       parameter ( GL_RGBA2 = 32853 )
       integer*4   GL_RGBA4
       parameter ( GL_RGBA4 = 32854 )
       integer*4   GL_RGB5_A1
       parameter ( GL_RGB5_A1 = 32855 )
       integer*4   GL_RGBA8
       parameter ( GL_RGBA8 = 32856 )
       integer*4   GL_RGB10_A2
       parameter ( GL_RGB10_A2 = 32857 )
       integer*4   GL_RGBA12
       parameter ( GL_RGBA12 = 32858 )
       integer*4   GL_RGBA16
       parameter ( GL_RGBA16 = 32859 )
C       GL_RGB2_EXT 
C       GL_DUAL_ALPHA4_SGIS 
C       GL_DUAL_ALPHA8_SGIS 
C       GL_DUAL_ALPHA12_SGIS 
C       GL_DUAL_ALPHA16_SGIS 
C       GL_DUAL_LUMINANCE4_SGIS 
C       GL_DUAL_LUMINANCE8_SGIS 
C       GL_DUAL_LUMINANCE12_SGIS 
C       GL_DUAL_LUMINANCE16_SGIS 
C       GL_DUAL_INTENSITY4_SGIS 
C       GL_DUAL_INTENSITY8_SGIS 
C       GL_DUAL_INTENSITY12_SGIS 
C       GL_DUAL_INTENSITY16_SGIS 
C       GL_DUAL_LUMINANCE_ALPHA4_SGIS 
C       GL_DUAL_LUMINANCE_ALPHA8_SGIS 
C       GL_QUAD_ALPHA4_SGIS 
C       GL_QUAD_ALPHA8_SGIS 
C       GL_QUAD_LUMINANCE4_SGIS 
C       GL_QUAD_LUMINANCE8_SGIS 
C       GL_QUAD_INTENSITY4_SGIS 
C       GL_QUAD_INTENSITY8_SGIS 
C       GL_DEPTH_COMPONENT16_SGIX 
C       GL_DEPTH_COMPONENT24_SGIX 
C       GL_DEPTH_COMPONENT32_SGIX 
C       GL_RGB_ICC_SGIX 
C       GL_RGBA_ICC_SGIX 
C       GL_ALPHA_ICC_SGIX 
C       GL_LUMINANCE_ICC_SGIX 
C       GL_INTENSITY_ICC_SGIX 
C       GL_LUMINANCE_ALPHA_ICC_SGIX 
C       GL_R5_G6_B5_ICC_SGIX 
C       GL_R5_G6_B5_A8_ICC_SGIX 
C       GL_ALPHA16_ICC_SGIX 
C       GL_LUMINANCE16_ICC_SGIX 
C       GL_INTENSITY16_ICC_SGIX 
C       GL_LUMINANCE16_ALPHA8_ICC_SGIX 

C  InterleavedArrayFormat 
       integer*4   GL_V2F
       parameter ( GL_V2F = 10784 )
       integer*4   GL_V3F
       parameter ( GL_V3F = 10785 )
       integer*4   GL_C4UB_V2F
       parameter ( GL_C4UB_V2F = 10786 )
       integer*4   GL_C4UB_V3F
       parameter ( GL_C4UB_V3F = 10787 )
       integer*4   GL_C3F_V3F
       parameter ( GL_C3F_V3F = 10788 )
       integer*4   GL_N3F_V3F
       parameter ( GL_N3F_V3F = 10789 )
       integer*4   GL_C4F_N3F_V3F
       parameter ( GL_C4F_N3F_V3F = 10790 )
       integer*4   GL_T2F_V3F
       parameter ( GL_T2F_V3F = 10791 )
       integer*4   GL_T4F_V4F
       parameter ( GL_T4F_V4F = 10792 )
       integer*4   GL_T2F_C4UB_V3F
       parameter ( GL_T2F_C4UB_V3F = 10793 )
       integer*4   GL_T2F_C3F_V3F
       parameter ( GL_T2F_C3F_V3F = 10794 )
       integer*4   GL_T2F_N3F_V3F
       parameter ( GL_T2F_N3F_V3F = 10795 )
       integer*4   GL_T2F_C4F_N3F_V3F
       parameter ( GL_T2F_C4F_N3F_V3F = 10796 )
       integer*4   GL_T4F_C4F_N3F_V4F
       parameter ( GL_T4F_C4F_N3F_V4F = 10797 )

C  VertexPointerType 
C       GL_SHORT 
C       GL_INT 
C       GL_FLOAT 
C       GL_DOUBLE 

C  ClipPlaneName 
       integer*4   GL_CLIP_PLANE0
       parameter ( GL_CLIP_PLANE0 = 12288 )
       integer*4   GL_CLIP_PLANE1
       parameter ( GL_CLIP_PLANE1 = 12289 )
       integer*4   GL_CLIP_PLANE2
       parameter ( GL_CLIP_PLANE2 = 12290 )
       integer*4   GL_CLIP_PLANE3
       parameter ( GL_CLIP_PLANE3 = 12291 )
       integer*4   GL_CLIP_PLANE4
       parameter ( GL_CLIP_PLANE4 = 12292 )
       integer*4   GL_CLIP_PLANE5
       parameter ( GL_CLIP_PLANE5 = 12293 )

C  LightName 
       integer*4   GL_LIGHT0
       parameter ( GL_LIGHT0 = 16384 )
       integer*4   GL_LIGHT1
       parameter ( GL_LIGHT1 = 16385 )
       integer*4   GL_LIGHT2
       parameter ( GL_LIGHT2 = 16386 )
       integer*4   GL_LIGHT3
       parameter ( GL_LIGHT3 = 16387 )
       integer*4   GL_LIGHT4
       parameter ( GL_LIGHT4 = 16388 )
       integer*4   GL_LIGHT5
       parameter ( GL_LIGHT5 = 16389 )
       integer*4   GL_LIGHT6
       parameter ( GL_LIGHT6 = 16390 )
       integer*4   GL_LIGHT7
       parameter ( GL_LIGHT7 = 16391 )
C       GL_FRAGMENT_LIGHT0_SGIX 
C       GL_FRAGMENT_LIGHT1_SGIX 
C       GL_FRAGMENT_LIGHT2_SGIX 
C       GL_FRAGMENT_LIGHT3_SGIX 
C       GL_FRAGMENT_LIGHT4_SGIX 
C       GL_FRAGMENT_LIGHT5_SGIX 
C       GL_FRAGMENT_LIGHT6_SGIX 
C       GL_FRAGMENT_LIGHT7_SGIX 

C  VERSION_1_2 
       integer*4   GL_UNSIGNED_BYTE_3_3_2
       parameter ( GL_UNSIGNED_BYTE_3_3_2 = 32818 )
       integer*4   GL_UNSIGNED_SHORT_4_4_4_4
       parameter ( GL_UNSIGNED_SHORT_4_4_4_4 = 32819 )
       integer*4   GL_UNSIGNED_SHORT_5_5_5_1
       parameter ( GL_UNSIGNED_SHORT_5_5_5_1 = 32820 )
       integer*4   GL_UNSIGNED_INT_8_8_8_8
       parameter ( GL_UNSIGNED_INT_8_8_8_8 = 32821 )
       integer*4   GL_UNSIGNED_INT_10_10_10_2
       parameter ( GL_UNSIGNED_INT_10_10_10_2 = 32822 )
       integer*4   GL_RESCALE_NORMAL
       parameter ( GL_RESCALE_NORMAL = 32826 )
       integer*4   GL_PACK_SKIP_IMAGES
       parameter ( GL_PACK_SKIP_IMAGES = 32875 )
       integer*4   GL_PACK_IMAGE_HEIGHT
       parameter ( GL_PACK_IMAGE_HEIGHT = 32876 )
       integer*4   GL_UNPACK_SKIP_IMAGES
       parameter ( GL_UNPACK_SKIP_IMAGES = 32877 )
       integer*4   GL_UNPACK_IMAGE_HEIGHT
       parameter ( GL_UNPACK_IMAGE_HEIGHT = 32878 )
       integer*4   GL_TEXTURE_3D
       parameter ( GL_TEXTURE_3D = 32879 )
       integer*4   GL_PROXY_TEXTURE_3D
       parameter ( GL_PROXY_TEXTURE_3D = 32880 )
       integer*4   GL_TEXTURE_DEPTH
       parameter ( GL_TEXTURE_DEPTH = 32881 )
       integer*4   GL_TEXTURE_WRAP_R
       parameter ( GL_TEXTURE_WRAP_R = 32882 )
       integer*4   GL_MAX_3D_TEXTURE_SIZE
       parameter ( GL_MAX_3D_TEXTURE_SIZE = 32883 )
       integer*4   GL_UNSIGNED_BYTE_2_3_3_REV
       parameter ( GL_UNSIGNED_BYTE_2_3_3_REV = 33634 )
       integer*4   GL_UNSIGNED_SHORT_5_6_5
       parameter ( GL_UNSIGNED_SHORT_5_6_5 = 33635 )
       integer*4   GL_UNSIGNED_SHORT_5_6_5_REV
       parameter ( GL_UNSIGNED_SHORT_5_6_5_REV = 33636 )
       integer*4   GL_UNSIGNED_SHORT_4_4_4_4_REV
       parameter ( GL_UNSIGNED_SHORT_4_4_4_4_REV = 33637 )
       integer*4   GL_UNSIGNED_SHORT_1_5_5_5_REV
       parameter ( GL_UNSIGNED_SHORT_1_5_5_5_REV = 33638 )
       integer*4   GL_UNSIGNED_INT_8_8_8_8_REV
       parameter ( GL_UNSIGNED_INT_8_8_8_8_REV = 33639 )
       integer*4   GL_UNSIGNED_INT_2_10_10_10_REV
       parameter ( GL_UNSIGNED_INT_2_10_10_10_REV = 33640 )
       integer*4   GL_BGR
       parameter ( GL_BGR = 32992 )
       integer*4   GL_BGRA
       parameter ( GL_BGRA = 32993 )
       integer*4   GL_MAX_ELEMENTS_VERTICES
       parameter ( GL_MAX_ELEMENTS_VERTICES = 33000 )
       integer*4   GL_MAX_ELEMENTS_INDICES
       parameter ( GL_MAX_ELEMENTS_INDICES = 33001 )
       integer*4   GL_CLAMP_TO_EDGE
       parameter ( GL_CLAMP_TO_EDGE = 33071 )
       integer*4   GL_TEXTURE_MIN_LOD
       parameter ( GL_TEXTURE_MIN_LOD = 33082 )
       integer*4   GL_TEXTURE_MAX_LOD
       parameter ( GL_TEXTURE_MAX_LOD = 33083 )
       integer*4   GL_TEXTURE_BASE_LEVEL
       parameter ( GL_TEXTURE_BASE_LEVEL = 33084 )
       integer*4   GL_TEXTURE_MAX_LEVEL
       parameter ( GL_TEXTURE_MAX_LEVEL = 33085 )
       integer*4   GL_LIGHT_MODEL_COLOR_CONTROL
       parameter ( GL_LIGHT_MODEL_COLOR_CONTROL = 33272 )
       integer*4   GL_SINGLE_COLOR
       parameter ( GL_SINGLE_COLOR = 33273 )
       integer*4   GL_SEPARATE_SPECULAR_COLOR
       parameter ( GL_SEPARATE_SPECULAR_COLOR = 33274 )
       integer*4   GL_SMOOTH_POINT_SIZE_RANGE
       parameter ( GL_SMOOTH_POINT_SIZE_RANGE = 2834 )
       integer*4   GL_SMOOTH_POINT_SIZE_GRANULARITY
       parameter ( GL_SMOOTH_POINT_SIZE_GRANULARITY = 2835 )
       integer*4   GL_SMOOTH_LINE_WIDTH_RANGE
       parameter ( GL_SMOOTH_LINE_WIDTH_RANGE = 2850 )
       integer*4   GL_SMOOTH_LINE_WIDTH_GRANULARITY
       parameter ( GL_SMOOTH_LINE_WIDTH_GRANULARITY = 2851 )
       integer*4   GL_ALIASED_POINT_SIZE_RANGE
       parameter ( GL_ALIASED_POINT_SIZE_RANGE = 33901 )
       integer*4   GL_ALIASED_LINE_WIDTH_RANGE
       parameter ( GL_ALIASED_LINE_WIDTH_RANGE = 33902 )

C  ARB_imaging 
       integer*4   GL_CONSTANT_COLOR
       parameter ( GL_CONSTANT_COLOR = 32769 )
       integer*4   GL_ONE_MINUS_CONSTANT_COLOR
       parameter ( GL_ONE_MINUS_CONSTANT_COLOR = 32770 )
       integer*4   GL_CONSTANT_ALPHA
       parameter ( GL_CONSTANT_ALPHA = 32771 )
       integer*4   GL_ONE_MINUS_CONSTANT_ALPHA
       parameter ( GL_ONE_MINUS_CONSTANT_ALPHA = 32772 )
       integer*4   GL_BLEND_COLOR
       parameter ( GL_BLEND_COLOR = 32773 )
       integer*4   GL_FUNC_ADD
       parameter ( GL_FUNC_ADD = 32774 )
       integer*4   GL_MIN
       parameter ( GL_MIN = 32775 )
       integer*4   GL_MAX
       parameter ( GL_MAX = 32776 )
       integer*4   GL_BLEND_EQUATION
       parameter ( GL_BLEND_EQUATION = 32777 )
       integer*4   GL_FUNC_SUBTRACT
       parameter ( GL_FUNC_SUBTRACT = 32778 )
       integer*4   GL_FUNC_REVERSE_SUBTRACT
       parameter ( GL_FUNC_REVERSE_SUBTRACT = 32779 )
       integer*4   GL_CONVOLUTION_1D
       parameter ( GL_CONVOLUTION_1D = 32784 )
       integer*4   GL_CONVOLUTION_2D
       parameter ( GL_CONVOLUTION_2D = 32785 )
       integer*4   GL_SEPARABLE_2D
       parameter ( GL_SEPARABLE_2D = 32786 )
       integer*4   GL_CONVOLUTION_BORDER_MODE
       parameter ( GL_CONVOLUTION_BORDER_MODE = 32787 )
       integer*4   GL_CONVOLUTION_FILTER_SCALE
       parameter ( GL_CONVOLUTION_FILTER_SCALE = 32788 )
       integer*4   GL_CONVOLUTION_FILTER_BIAS
       parameter ( GL_CONVOLUTION_FILTER_BIAS = 32789 )
       integer*4   GL_REDUCE
       parameter ( GL_REDUCE = 32790 )
       integer*4   GL_CONVOLUTION_FORMAT
       parameter ( GL_CONVOLUTION_FORMAT = 32791 )
       integer*4   GL_CONVOLUTION_WIDTH
       parameter ( GL_CONVOLUTION_WIDTH = 32792 )
       integer*4   GL_CONVOLUTION_HEIGHT
       parameter ( GL_CONVOLUTION_HEIGHT = 32793 )
       integer*4   GL_MAX_CONVOLUTION_WIDTH
       parameter ( GL_MAX_CONVOLUTION_WIDTH = 32794 )
       integer*4   GL_MAX_CONVOLUTION_HEIGHT
       parameter ( GL_MAX_CONVOLUTION_HEIGHT = 32795 )
       integer*4   GL_POST_CONVOLUTION_RED_SCALE
       parameter ( GL_POST_CONVOLUTION_RED_SCALE = 32796 )
       integer*4   GL_POST_CONVOLUTION_GREEN_SCALE
       parameter ( GL_POST_CONVOLUTION_GREEN_SCALE = 32797 )
       integer*4   GL_POST_CONVOLUTION_BLUE_SCALE
       parameter ( GL_POST_CONVOLUTION_BLUE_SCALE = 32798 )
       integer*4   GL_POST_CONVOLUTION_ALPHA_SCALE
       parameter ( GL_POST_CONVOLUTION_ALPHA_SCALE = 32799 )
       integer*4   GL_POST_CONVOLUTION_RED_BIAS
       parameter ( GL_POST_CONVOLUTION_RED_BIAS = 32800 )
       integer*4   GL_POST_CONVOLUTION_GREEN_BIAS
       parameter ( GL_POST_CONVOLUTION_GREEN_BIAS = 32801 )
       integer*4   GL_POST_CONVOLUTION_BLUE_BIAS
       parameter ( GL_POST_CONVOLUTION_BLUE_BIAS = 32802 )
       integer*4   GL_POST_CONVOLUTION_ALPHA_BIAS
       parameter ( GL_POST_CONVOLUTION_ALPHA_BIAS = 32803 )
       integer*4   GL_HISTOGRAM
       parameter ( GL_HISTOGRAM = 32804 )
       integer*4   GL_PROXY_HISTOGRAM
       parameter ( GL_PROXY_HISTOGRAM = 32805 )
       integer*4   GL_HISTOGRAM_WIDTH
       parameter ( GL_HISTOGRAM_WIDTH = 32806 )
       integer*4   GL_HISTOGRAM_FORMAT
       parameter ( GL_HISTOGRAM_FORMAT = 32807 )
       integer*4   GL_HISTOGRAM_RED_SIZE
       parameter ( GL_HISTOGRAM_RED_SIZE = 32808 )
       integer*4   GL_HISTOGRAM_GREEN_SIZE
       parameter ( GL_HISTOGRAM_GREEN_SIZE = 32809 )
       integer*4   GL_HISTOGRAM_BLUE_SIZE
       parameter ( GL_HISTOGRAM_BLUE_SIZE = 32810 )
       integer*4   GL_HISTOGRAM_ALPHA_SIZE
       parameter ( GL_HISTOGRAM_ALPHA_SIZE = 32811 )
       integer*4   GL_HISTOGRAM_LUMINANCE_SIZE
       parameter ( GL_HISTOGRAM_LUMINANCE_SIZE = 32812 )
       integer*4   GL_HISTOGRAM_SINK
       parameter ( GL_HISTOGRAM_SINK = 32813 )
       integer*4   GL_MINMAX
       parameter ( GL_MINMAX = 32814 )
       integer*4   GL_MINMAX_FORMAT
       parameter ( GL_MINMAX_FORMAT = 32815 )
       integer*4   GL_MINMAX_SINK
       parameter ( GL_MINMAX_SINK = 32816 )
       integer*4   GL_TABLE_TOO_LARGE
       parameter ( GL_TABLE_TOO_LARGE = 32817 )
       integer*4   GL_COLOR_MATRIX
       parameter ( GL_COLOR_MATRIX = 32945 )
       integer*4   GL_COLOR_MATRIX_STACK_DEPTH
       parameter ( GL_COLOR_MATRIX_STACK_DEPTH = 32946 )
       integer*4   GL_MAX_COLOR_MATRIX_STACK_DEPTH
       parameter ( GL_MAX_COLOR_MATRIX_STACK_DEPTH = 32947 )
       integer*4   GL_POST_COLOR_MATRIX_RED_SCALE
       parameter ( GL_POST_COLOR_MATRIX_RED_SCALE = 32948 )
       integer*4   GL_POST_COLOR_MATRIX_GREEN_SCALE
       parameter ( GL_POST_COLOR_MATRIX_GREEN_SCALE = 32949 )
       integer*4   GL_POST_COLOR_MATRIX_BLUE_SCALE
       parameter ( GL_POST_COLOR_MATRIX_BLUE_SCALE = 32950 )
       integer*4   GL_POST_COLOR_MATRIX_ALPHA_SCALE
       parameter ( GL_POST_COLOR_MATRIX_ALPHA_SCALE = 32951 )
       integer*4   GL_POST_COLOR_MATRIX_RED_BIAS
       parameter ( GL_POST_COLOR_MATRIX_RED_BIAS = 32952 )
       integer*4   GL_POST_COLOR_MATRIX_GREEN_BIAS
       parameter ( GL_POST_COLOR_MATRIX_GREEN_BIAS = 32953 )
       integer*4   GL_POST_COLOR_MATRIX_BLUE_BIAS
       parameter ( GL_POST_COLOR_MATRIX_BLUE_BIAS = 32954 )
       integer*4   GL_POST_COLOR_MATRIX_ALPHA_BIAS
       parameter ( GL_POST_COLOR_MATRIX_ALPHA_BIAS = 32955 )
       integer*4   GL_COLOR_TABLE
       parameter ( GL_COLOR_TABLE = 32976 )
       integer*4   GL_POST_CONVOLUTION_COLOR_TABLE
       parameter ( GL_POST_CONVOLUTION_COLOR_TABLE = 32977 )
       integer*4   GL_POST_COLOR_MATRIX_COLOR_TABLE
       parameter ( GL_POST_COLOR_MATRIX_COLOR_TABLE = 32978 )
       integer*4   GL_PROXY_COLOR_TABLE
       parameter ( GL_PROXY_COLOR_TABLE = 32979 )
       integer*4   GL_PROXY_POST_CONVOLUTION_COLOR_TABLE
       parameter ( GL_PROXY_POST_CONVOLUTION_COLOR_TABLE = 32980 )
       integer*4   GL_PROXY_POST_COLOR_MATRIX_COLOR_TABLE
       parameter ( GL_PROXY_POST_COLOR_MATRIX_COLOR_TABLE = 32981 )
       integer*4   GL_COLOR_TABLE_SCALE
       parameter ( GL_COLOR_TABLE_SCALE = 32982 )
       integer*4   GL_COLOR_TABLE_BIAS
       parameter ( GL_COLOR_TABLE_BIAS = 32983 )
       integer*4   GL_COLOR_TABLE_FORMAT
       parameter ( GL_COLOR_TABLE_FORMAT = 32984 )
       integer*4   GL_COLOR_TABLE_WIDTH
       parameter ( GL_COLOR_TABLE_WIDTH = 32985 )
       integer*4   GL_COLOR_TABLE_RED_SIZE
       parameter ( GL_COLOR_TABLE_RED_SIZE = 32986 )
       integer*4   GL_COLOR_TABLE_GREEN_SIZE
       parameter ( GL_COLOR_TABLE_GREEN_SIZE = 32987 )
       integer*4   GL_COLOR_TABLE_BLUE_SIZE
       parameter ( GL_COLOR_TABLE_BLUE_SIZE = 32988 )
       integer*4   GL_COLOR_TABLE_ALPHA_SIZE
       parameter ( GL_COLOR_TABLE_ALPHA_SIZE = 32989 )
       integer*4   GL_COLOR_TABLE_LUMINANCE_SIZE
       parameter ( GL_COLOR_TABLE_LUMINANCE_SIZE = 32990 )
       integer*4   GL_COLOR_TABLE_INTENSITY_SIZE
       parameter ( GL_COLOR_TABLE_INTENSITY_SIZE = 32991 )
       integer*4   GL_IGNORE_BORDER
       parameter ( GL_IGNORE_BORDER = 33104 )
       integer*4   GL_CONSTANT_BORDER
       parameter ( GL_CONSTANT_BORDER = 33105 )
       integer*4   GL_WRAP_BORDER
       parameter ( GL_WRAP_BORDER = 33106 )
       integer*4   GL_REPLICATE_BORDER
       parameter ( GL_REPLICATE_BORDER = 33107 )
       integer*4   GL_CONVOLUTION_BORDER_COLOR
       parameter ( GL_CONVOLUTION_BORDER_COLOR = 33108 )

C  VERSION_1_3 
       integer*4   GL_TEXTURE0
       parameter ( GL_TEXTURE0 = 33984 )
       integer*4   GL_TEXTURE1
       parameter ( GL_TEXTURE1 = 33985 )
       integer*4   GL_TEXTURE2
       parameter ( GL_TEXTURE2 = 33986 )
       integer*4   GL_TEXTURE3
       parameter ( GL_TEXTURE3 = 33987 )
       integer*4   GL_TEXTURE4
       parameter ( GL_TEXTURE4 = 33988 )
       integer*4   GL_TEXTURE5
       parameter ( GL_TEXTURE5 = 33989 )
       integer*4   GL_TEXTURE6
       parameter ( GL_TEXTURE6 = 33990 )
       integer*4   GL_TEXTURE7
       parameter ( GL_TEXTURE7 = 33991 )
       integer*4   GL_TEXTURE8
       parameter ( GL_TEXTURE8 = 33992 )
       integer*4   GL_TEXTURE9
       parameter ( GL_TEXTURE9 = 33993 )
       integer*4   GL_TEXTURE10
       parameter ( GL_TEXTURE10 = 33994 )
       integer*4   GL_TEXTURE11
       parameter ( GL_TEXTURE11 = 33995 )
       integer*4   GL_TEXTURE12
       parameter ( GL_TEXTURE12 = 33996 )
       integer*4   GL_TEXTURE13
       parameter ( GL_TEXTURE13 = 33997 )
       integer*4   GL_TEXTURE14
       parameter ( GL_TEXTURE14 = 33998 )
       integer*4   GL_TEXTURE15
       parameter ( GL_TEXTURE15 = 33999 )
       integer*4   GL_TEXTURE16
       parameter ( GL_TEXTURE16 = 34000 )
       integer*4   GL_TEXTURE17
       parameter ( GL_TEXTURE17 = 34001 )
       integer*4   GL_TEXTURE18
       parameter ( GL_TEXTURE18 = 34002 )
       integer*4   GL_TEXTURE19
       parameter ( GL_TEXTURE19 = 34003 )
       integer*4   GL_TEXTURE20
       parameter ( GL_TEXTURE20 = 34004 )
       integer*4   GL_TEXTURE21
       parameter ( GL_TEXTURE21 = 34005 )
       integer*4   GL_TEXTURE22
       parameter ( GL_TEXTURE22 = 34006 )
       integer*4   GL_TEXTURE23
       parameter ( GL_TEXTURE23 = 34007 )
       integer*4   GL_TEXTURE24
       parameter ( GL_TEXTURE24 = 34008 )
       integer*4   GL_TEXTURE25
       parameter ( GL_TEXTURE25 = 34009 )
       integer*4   GL_TEXTURE26
       parameter ( GL_TEXTURE26 = 34010 )
       integer*4   GL_TEXTURE27
       parameter ( GL_TEXTURE27 = 34011 )
       integer*4   GL_TEXTURE28
       parameter ( GL_TEXTURE28 = 34012 )
       integer*4   GL_TEXTURE29
       parameter ( GL_TEXTURE29 = 34013 )
       integer*4   GL_TEXTURE30
       parameter ( GL_TEXTURE30 = 34014 )
       integer*4   GL_TEXTURE31
       parameter ( GL_TEXTURE31 = 34015 )
       integer*4   GL_ACTIVE_TEXTURE
       parameter ( GL_ACTIVE_TEXTURE = 34016 )
       integer*4   GL_CLIENT_ACTIVE_TEXTURE
       parameter ( GL_CLIENT_ACTIVE_TEXTURE = 34017 )
       integer*4   GL_MAX_TEXTURE_UNITS
       parameter ( GL_MAX_TEXTURE_UNITS = 34018 )
       integer*4   GL_TRANSPOSE_MODELVIEW_MATRIX
       parameter ( GL_TRANSPOSE_MODELVIEW_MATRIX = 34019 )
       integer*4   GL_TRANSPOSE_PROJECTION_MATRIX
       parameter ( GL_TRANSPOSE_PROJECTION_MATRIX = 34020 )
       integer*4   GL_TRANSPOSE_TEXTURE_MATRIX
       parameter ( GL_TRANSPOSE_TEXTURE_MATRIX = 34021 )
       integer*4   GL_TRANSPOSE_COLOR_MATRIX
       parameter ( GL_TRANSPOSE_COLOR_MATRIX = 34022 )
       integer*4   GL_MULTISAMPLE
       parameter ( GL_MULTISAMPLE = 32925 )
       integer*4   GL_SAMPLE_ALPHA_TO_COVERAGE
       parameter ( GL_SAMPLE_ALPHA_TO_COVERAGE = 32926 )
       integer*4   GL_SAMPLE_ALPHA_TO_ONE
       parameter ( GL_SAMPLE_ALPHA_TO_ONE = 32927 )
       integer*4   GL_SAMPLE_COVERAGE
       parameter ( GL_SAMPLE_COVERAGE = 32928 )
       integer*4   GL_SAMPLE_BUFFERS
       parameter ( GL_SAMPLE_BUFFERS = 32936 )
       integer*4   GL_SAMPLES
       parameter ( GL_SAMPLES = 32937 )
       integer*4   GL_SAMPLE_COVERAGE_VALUE
       parameter ( GL_SAMPLE_COVERAGE_VALUE = 32938 )
       integer*4   GL_SAMPLE_COVERAGE_INVERT
       parameter ( GL_SAMPLE_COVERAGE_INVERT = 32939 )
       integer*4   GL_MULTISAMPLE_BIT
       parameter ( GL_MULTISAMPLE_BIT = 536870912 )
       integer*4   GL_NORMAL_MAP
       parameter ( GL_NORMAL_MAP = 34065 )
       integer*4   GL_REFLECTION_MAP
       parameter ( GL_REFLECTION_MAP = 34066 )
       integer*4   GL_TEXTURE_CUBE_MAP
       parameter ( GL_TEXTURE_CUBE_MAP = 34067 )
       integer*4   GL_TEXTURE_BINDING_CUBE_MAP
       parameter ( GL_TEXTURE_BINDING_CUBE_MAP = 34068 )
       integer*4   GL_TEXTURE_CUBE_MAP_POSITIVE_X
       parameter ( GL_TEXTURE_CUBE_MAP_POSITIVE_X = 34069 )
       integer*4   GL_TEXTURE_CUBE_MAP_NEGATIVE_X
       parameter ( GL_TEXTURE_CUBE_MAP_NEGATIVE_X = 34070 )
       integer*4   GL_TEXTURE_CUBE_MAP_POSITIVE_Y
       parameter ( GL_TEXTURE_CUBE_MAP_POSITIVE_Y = 34071 )
       integer*4   GL_TEXTURE_CUBE_MAP_NEGATIVE_Y
       parameter ( GL_TEXTURE_CUBE_MAP_NEGATIVE_Y = 34072 )
       integer*4   GL_TEXTURE_CUBE_MAP_POSITIVE_Z
       parameter ( GL_TEXTURE_CUBE_MAP_POSITIVE_Z = 34073 )
       integer*4   GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
       parameter ( GL_TEXTURE_CUBE_MAP_NEGATIVE_Z = 34074 )
       integer*4   GL_PROXY_TEXTURE_CUBE_MAP
       parameter ( GL_PROXY_TEXTURE_CUBE_MAP = 34075 )
       integer*4   GL_MAX_CUBE_MAP_TEXTURE_SIZE
       parameter ( GL_MAX_CUBE_MAP_TEXTURE_SIZE = 34076 )
       integer*4   GL_COMPRESSED_ALPHA
       parameter ( GL_COMPRESSED_ALPHA = 34025 )
       integer*4   GL_COMPRESSED_LUMINANCE
       parameter ( GL_COMPRESSED_LUMINANCE = 34026 )
       integer*4   GL_COMPRESSED_LUMINANCE_ALPHA
       parameter ( GL_COMPRESSED_LUMINANCE_ALPHA = 34027 )
       integer*4   GL_COMPRESSED_INTENSITY
       parameter ( GL_COMPRESSED_INTENSITY = 34028 )
       integer*4   GL_COMPRESSED_RGB
       parameter ( GL_COMPRESSED_RGB = 34029 )
       integer*4   GL_COMPRESSED_RGBA
       parameter ( GL_COMPRESSED_RGBA = 34030 )
       integer*4   GL_TEXTURE_COMPRESSION_HINT
       parameter ( GL_TEXTURE_COMPRESSION_HINT = 34031 )
       integer*4   GL_TEXTURE_COMPRESSED_IMAGE_SIZE
       parameter ( GL_TEXTURE_COMPRESSED_IMAGE_SIZE = 34464 )
       integer*4   GL_TEXTURE_COMPRESSED
       parameter ( GL_TEXTURE_COMPRESSED = 34465 )
       integer*4   GL_NUM_COMPRESSED_TEXTURE_FORMATS
       parameter ( GL_NUM_COMPRESSED_TEXTURE_FORMATS = 34466 )
       integer*4   GL_COMPRESSED_TEXTURE_FORMATS
       parameter ( GL_COMPRESSED_TEXTURE_FORMATS = 34467 )
       integer*4   GL_CLAMP_TO_BORDER
       parameter ( GL_CLAMP_TO_BORDER = 33069 )
       integer*4   GL_CLAMP_TO_BORDER_SGIS
       parameter ( GL_CLAMP_TO_BORDER_SGIS = 33069 )
       integer*4   GL_COMBINE
       parameter ( GL_COMBINE = 34160 )
       integer*4   GL_COMBINE_RGB
       parameter ( GL_COMBINE_RGB = 34161 )
       integer*4   GL_COMBINE_ALPHA
       parameter ( GL_COMBINE_ALPHA = 34162 )
       integer*4   GL_SOURCE0_RGB
       parameter ( GL_SOURCE0_RGB = 34176 )
       integer*4   GL_SOURCE1_RGB
       parameter ( GL_SOURCE1_RGB = 34177 )
       integer*4   GL_SOURCE2_RGB
       parameter ( GL_SOURCE2_RGB = 34178 )
       integer*4   GL_SOURCE0_ALPHA
       parameter ( GL_SOURCE0_ALPHA = 34184 )
       integer*4   GL_SOURCE1_ALPHA
       parameter ( GL_SOURCE1_ALPHA = 34185 )
       integer*4   GL_SOURCE2_ALPHA
       parameter ( GL_SOURCE2_ALPHA = 34186 )
       integer*4   GL_OPERAND0_RGB
       parameter ( GL_OPERAND0_RGB = 34192 )
       integer*4   GL_OPERAND1_RGB
       parameter ( GL_OPERAND1_RGB = 34193 )
       integer*4   GL_OPERAND2_RGB
       parameter ( GL_OPERAND2_RGB = 34194 )
       integer*4   GL_OPERAND0_ALPHA
       parameter ( GL_OPERAND0_ALPHA = 34200 )
       integer*4   GL_OPERAND1_ALPHA
       parameter ( GL_OPERAND1_ALPHA = 34201 )
       integer*4   GL_OPERAND2_ALPHA
       parameter ( GL_OPERAND2_ALPHA = 34202 )
       integer*4   GL_RGB_SCALE
       parameter ( GL_RGB_SCALE = 34163 )
       integer*4   GL_ADD_SIGNED
       parameter ( GL_ADD_SIGNED = 34164 )
       integer*4   GL_INTERPOLATE
       parameter ( GL_INTERPOLATE = 34165 )
       integer*4   GL_SUBTRACT
       parameter ( GL_SUBTRACT = 34023 )
       integer*4   GL_CONSTANT
       parameter ( GL_CONSTANT = 34166 )
       integer*4   GL_PRIMARY_COLOR
       parameter ( GL_PRIMARY_COLOR = 34167 )
       integer*4   GL_PREVIOUS
       parameter ( GL_PREVIOUS = 34168 )
       integer*4   GL_DOT3_RGB
       parameter ( GL_DOT3_RGB = 34478 )
       integer*4   GL_DOT3_RGBA
       parameter ( GL_DOT3_RGBA = 34479 )

C  VERSION_1_4 
       integer*4   GL_BLEND_DST_RGB
       parameter ( GL_BLEND_DST_RGB = 32968 )
       integer*4   GL_BLEND_SRC_RGB
       parameter ( GL_BLEND_SRC_RGB = 32969 )
       integer*4   GL_BLEND_DST_ALPHA
       parameter ( GL_BLEND_DST_ALPHA = 32970 )
       integer*4   GL_BLEND_SRC_ALPHA
       parameter ( GL_BLEND_SRC_ALPHA = 32971 )
       integer*4   GL_POINT_SIZE_MIN
       parameter ( GL_POINT_SIZE_MIN = 33062 )
       integer*4   GL_POINT_SIZE_MAX
       parameter ( GL_POINT_SIZE_MAX = 33063 )
       integer*4   GL_POINT_FADE_THRESHOLD_SIZE
       parameter ( GL_POINT_FADE_THRESHOLD_SIZE = 33064 )
       integer*4   GL_POINT_DISTANCE_ATTENUATION
       parameter ( GL_POINT_DISTANCE_ATTENUATION = 33065 )
       integer*4   GL_GENERATE_MIPMAP
       parameter ( GL_GENERATE_MIPMAP = 33169 )
       integer*4   GL_GENERATE_MIPMAP_HINT
       parameter ( GL_GENERATE_MIPMAP_HINT = 33170 )
       integer*4   GL_DEPTH_COMPONENT16
       parameter ( GL_DEPTH_COMPONENT16 = 33189 )
       integer*4   GL_DEPTH_COMPONENT24
       parameter ( GL_DEPTH_COMPONENT24 = 33190 )
       integer*4   GL_DEPTH_COMPONENT32
       parameter ( GL_DEPTH_COMPONENT32 = 33191 )
       integer*4   GL_MIRRORED_REPEAT
       parameter ( GL_MIRRORED_REPEAT = 33648 )
       integer*4   GL_FOG_COORDINATE_SOURCE
       parameter ( GL_FOG_COORDINATE_SOURCE = 33872 )
       integer*4   GL_FOG_COORDINATE
       parameter ( GL_FOG_COORDINATE = 33873 )
       integer*4   GL_FRAGMENT_DEPTH
       parameter ( GL_FRAGMENT_DEPTH = 33874 )
       integer*4   GL_CURRENT_FOG_COORDINATE
       parameter ( GL_CURRENT_FOG_COORDINATE = 33875 )
       integer*4   GL_FOG_COORDINATE_ARRAY_TYPE
       parameter ( GL_FOG_COORDINATE_ARRAY_TYPE = 33876 )
       integer*4   GL_FOG_COORDINATE_ARRAY_STRIDE
       parameter ( GL_FOG_COORDINATE_ARRAY_STRIDE = 33877 )
       integer*4   GL_FOG_COORDINATE_ARRAY_POINTER
       parameter ( GL_FOG_COORDINATE_ARRAY_POINTER = 33878 )
       integer*4   GL_FOG_COORDINATE_ARRAY
       parameter ( GL_FOG_COORDINATE_ARRAY = 33879 )
       integer*4   GL_COLOR_SUM
       parameter ( GL_COLOR_SUM = 33880 )
       integer*4   GL_CURRENT_SECONDARY_COLOR
       parameter ( GL_CURRENT_SECONDARY_COLOR = 33881 )
       integer*4   GL_SECONDARY_COLOR_ARRAY_SIZE
       parameter ( GL_SECONDARY_COLOR_ARRAY_SIZE = 33882 )
       integer*4   GL_SECONDARY_COLOR_ARRAY_TYPE
       parameter ( GL_SECONDARY_COLOR_ARRAY_TYPE = 33883 )
       integer*4   GL_SECONDARY_COLOR_ARRAY_STRIDE
       parameter ( GL_SECONDARY_COLOR_ARRAY_STRIDE = 33884 )
       integer*4   GL_SECONDARY_COLOR_ARRAY_POINTER
       parameter ( GL_SECONDARY_COLOR_ARRAY_POINTER = 33885 )
       integer*4   GL_SECONDARY_COLOR_ARRAY
       parameter ( GL_SECONDARY_COLOR_ARRAY = 33886 )
       integer*4   GL_MAX_TEXTURE_LOD_BIAS
       parameter ( GL_MAX_TEXTURE_LOD_BIAS = 34045 )
       integer*4   GL_TEXTURE_FILTER_CONTROL
       parameter ( GL_TEXTURE_FILTER_CONTROL = 34048 )
       integer*4   GL_TEXTURE_LOD_BIAS
       parameter ( GL_TEXTURE_LOD_BIAS = 34049 )
       integer*4   GL_INCR_WRAP
       parameter ( GL_INCR_WRAP = 34055 )
       integer*4   GL_DECR_WRAP
       parameter ( GL_DECR_WRAP = 34056 )
       integer*4   GL_TEXTURE_DEPTH_SIZE
       parameter ( GL_TEXTURE_DEPTH_SIZE = 34890 )
       integer*4   GL_DEPTH_TEXTURE_MODE
       parameter ( GL_DEPTH_TEXTURE_MODE = 34891 )
       integer*4   GL_TEXTURE_COMPARE_MODE
       parameter ( GL_TEXTURE_COMPARE_MODE = 34892 )
       integer*4   GL_TEXTURE_COMPARE_FUNC
       parameter ( GL_TEXTURE_COMPARE_FUNC = 34893 )
       integer*4   GL_COMPARE_R_TO_TEXTURE
       parameter ( GL_COMPARE_R_TO_TEXTURE = 34894 )

C  EXT_abgr 
       integer*4   GL_ABGR_EXT
       parameter ( GL_ABGR_EXT = 32768 )

C  EXT_blend_color 
       integer*4   GL_CONSTANT_COLOR_EXT
       parameter ( GL_CONSTANT_COLOR_EXT = 32769 )
       integer*4   GL_ONE_MINUS_CONSTANT_COLOR_EXT
       parameter ( GL_ONE_MINUS_CONSTANT_COLOR_EXT = 32770 )
       integer*4   GL_CONSTANT_ALPHA_EXT
       parameter ( GL_CONSTANT_ALPHA_EXT = 32771 )
       integer*4   GL_ONE_MINUS_CONSTANT_ALPHA_EXT
       parameter ( GL_ONE_MINUS_CONSTANT_ALPHA_EXT = 32772 )
       integer*4   GL_BLEND_COLOR_EXT
       parameter ( GL_BLEND_COLOR_EXT = 32773 )

C  EXT_blend_minmax 
       integer*4   GL_FUNC_ADD_EXT
       parameter ( GL_FUNC_ADD_EXT = 32774 )
       integer*4   GL_MIN_EXT
       parameter ( GL_MIN_EXT = 32775 )
       integer*4   GL_MAX_EXT
       parameter ( GL_MAX_EXT = 32776 )
       integer*4   GL_BLEND_EQUATION_EXT
       parameter ( GL_BLEND_EQUATION_EXT = 32777 )

C  EXT_blend_subtract 
       integer*4   GL_FUNC_SUBTRACT_EXT
       parameter ( GL_FUNC_SUBTRACT_EXT = 32778 )
       integer*4   GL_FUNC_REVERSE_SUBTRACT_EXT
       parameter ( GL_FUNC_REVERSE_SUBTRACT_EXT = 32779 )

C  EXT_cmyka 
       integer*4   GL_CMYK_EXT
       parameter ( GL_CMYK_EXT = 32780 )
       integer*4   GL_CMYKA_EXT
       parameter ( GL_CMYKA_EXT = 32781 )
       integer*4   GL_PACK_CMYK_HINT_EXT
       parameter ( GL_PACK_CMYK_HINT_EXT = 32782 )
       integer*4   GL_UNPACK_CMYK_HINT_EXT
       parameter ( GL_UNPACK_CMYK_HINT_EXT = 32783 )

C  EXT_convolution 
       integer*4   GL_CONVOLUTION_1D_EXT
       parameter ( GL_CONVOLUTION_1D_EXT = 32784 )
       integer*4   GL_CONVOLUTION_2D_EXT
       parameter ( GL_CONVOLUTION_2D_EXT = 32785 )
       integer*4   GL_SEPARABLE_2D_EXT
       parameter ( GL_SEPARABLE_2D_EXT = 32786 )
       integer*4   GL_CONVOLUTION_BORDER_MODE_EXT
       parameter ( GL_CONVOLUTION_BORDER_MODE_EXT = 32787 )
       integer*4   GL_CONVOLUTION_FILTER_SCALE_EXT
       parameter ( GL_CONVOLUTION_FILTER_SCALE_EXT = 32788 )
       integer*4   GL_CONVOLUTION_FILTER_BIAS_EXT
       parameter ( GL_CONVOLUTION_FILTER_BIAS_EXT = 32789 )
       integer*4   GL_REDUCE_EXT
       parameter ( GL_REDUCE_EXT = 32790 )
       integer*4   GL_CONVOLUTION_FORMAT_EXT
       parameter ( GL_CONVOLUTION_FORMAT_EXT = 32791 )
       integer*4   GL_CONVOLUTION_WIDTH_EXT
       parameter ( GL_CONVOLUTION_WIDTH_EXT = 32792 )
       integer*4   GL_CONVOLUTION_HEIGHT_EXT
       parameter ( GL_CONVOLUTION_HEIGHT_EXT = 32793 )
       integer*4   GL_MAX_CONVOLUTION_WIDTH_EXT
       parameter ( GL_MAX_CONVOLUTION_WIDTH_EXT = 32794 )
       integer*4   GL_MAX_CONVOLUTION_HEIGHT_EXT
       parameter ( GL_MAX_CONVOLUTION_HEIGHT_EXT = 32795 )
       integer*4   GL_POST_CONVOLUTION_RED_SCALE_EXT
       parameter ( GL_POST_CONVOLUTION_RED_SCALE_EXT = 32796 )
       integer*4   GL_POST_CONVOLUTION_GREEN_SCALE_EXT
       parameter ( GL_POST_CONVOLUTION_GREEN_SCALE_EXT = 32797 )
       integer*4   GL_POST_CONVOLUTION_BLUE_SCALE_EXT
       parameter ( GL_POST_CONVOLUTION_BLUE_SCALE_EXT = 32798 )
       integer*4   GL_POST_CONVOLUTION_ALPHA_SCALE_EXT
       parameter ( GL_POST_CONVOLUTION_ALPHA_SCALE_EXT = 32799 )
       integer*4   GL_POST_CONVOLUTION_RED_BIAS_EXT
       parameter ( GL_POST_CONVOLUTION_RED_BIAS_EXT = 32800 )
       integer*4   GL_POST_CONVOLUTION_GREEN_BIAS_EXT
       parameter ( GL_POST_CONVOLUTION_GREEN_BIAS_EXT = 32801 )
       integer*4   GL_POST_CONVOLUTION_BLUE_BIAS_EXT
       parameter ( GL_POST_CONVOLUTION_BLUE_BIAS_EXT = 32802 )
       integer*4   GL_POST_CONVOLUTION_ALPHA_BIAS_EXT
       parameter ( GL_POST_CONVOLUTION_ALPHA_BIAS_EXT = 32803 )

C  EXT_histogram 
       integer*4   GL_HISTOGRAM_EXT
       parameter ( GL_HISTOGRAM_EXT = 32804 )
       integer*4   GL_PROXY_HISTOGRAM_EXT
       parameter ( GL_PROXY_HISTOGRAM_EXT = 32805 )
       integer*4   GL_HISTOGRAM_WIDTH_EXT
       parameter ( GL_HISTOGRAM_WIDTH_EXT = 32806 )
       integer*4   GL_HISTOGRAM_FORMAT_EXT
       parameter ( GL_HISTOGRAM_FORMAT_EXT = 32807 )
       integer*4   GL_HISTOGRAM_RED_SIZE_EXT
       parameter ( GL_HISTOGRAM_RED_SIZE_EXT = 32808 )
       integer*4   GL_HISTOGRAM_GREEN_SIZE_EXT
       parameter ( GL_HISTOGRAM_GREEN_SIZE_EXT = 32809 )
       integer*4   GL_HISTOGRAM_BLUE_SIZE_EXT
       parameter ( GL_HISTOGRAM_BLUE_SIZE_EXT = 32810 )
       integer*4   GL_HISTOGRAM_ALPHA_SIZE_EXT
       parameter ( GL_HISTOGRAM_ALPHA_SIZE_EXT = 32811 )
       integer*4   GL_HISTOGRAM_LUMINANCE_SIZE_EXT
       parameter ( GL_HISTOGRAM_LUMINANCE_SIZE_EXT = 32812 )
       integer*4   GL_HISTOGRAM_SINK_EXT
       parameter ( GL_HISTOGRAM_SINK_EXT = 32813 )
       integer*4   GL_MINMAX_EXT
       parameter ( GL_MINMAX_EXT = 32814 )
       integer*4   GL_MINMAX_FORMAT_EXT
       parameter ( GL_MINMAX_FORMAT_EXT = 32815 )
       integer*4   GL_MINMAX_SINK_EXT
       parameter ( GL_MINMAX_SINK_EXT = 32816 )
       integer*4   GL_TABLE_TOO_LARGE_EXT
       parameter ( GL_TABLE_TOO_LARGE_EXT = 32817 )

C  EXT_packed_pixels 
       integer*4   GL_UNSIGNED_BYTE_3_3_2_EXT
       parameter ( GL_UNSIGNED_BYTE_3_3_2_EXT = 32818 )
       integer*4   GL_UNSIGNED_SHORT_4_4_4_4_EXT
       parameter ( GL_UNSIGNED_SHORT_4_4_4_4_EXT = 32819 )
       integer*4   GL_UNSIGNED_SHORT_5_5_5_1_EXT
       parameter ( GL_UNSIGNED_SHORT_5_5_5_1_EXT = 32820 )
       integer*4   GL_UNSIGNED_INT_8_8_8_8_EXT
       parameter ( GL_UNSIGNED_INT_8_8_8_8_EXT = 32821 )
       integer*4   GL_UNSIGNED_INT_10_10_10_2_EXT
       parameter ( GL_UNSIGNED_INT_10_10_10_2_EXT = 32822 )
       integer*4   GL_UNSIGNED_BYTE_2_3_3_REV_EXT
       parameter ( GL_UNSIGNED_BYTE_2_3_3_REV_EXT = 33634 )
       integer*4   GL_UNSIGNED_SHORT_5_6_5_EXT
       parameter ( GL_UNSIGNED_SHORT_5_6_5_EXT = 33635 )
       integer*4   GL_UNSIGNED_SHORT_5_6_5_REV_EXT
       parameter ( GL_UNSIGNED_SHORT_5_6_5_REV_EXT = 33636 )
       integer*4   GL_UNSIGNED_SHORT_4_4_4_4_REV_EXT
       parameter ( GL_UNSIGNED_SHORT_4_4_4_4_REV_EXT = 33637 )
       integer*4   GL_UNSIGNED_SHORT_1_5_5_5_REV_EXT
       parameter ( GL_UNSIGNED_SHORT_1_5_5_5_REV_EXT = 33638 )
       integer*4   GL_UNSIGNED_INT_8_8_8_8_REV_EXT
       parameter ( GL_UNSIGNED_INT_8_8_8_8_REV_EXT = 33639 )
       integer*4   GL_UNSIGNED_INT_2_10_10_10_REV_EXT
       parameter ( GL_UNSIGNED_INT_2_10_10_10_REV_EXT = 33640 )

C  EXT_polygon_offset 
       integer*4   GL_POLYGON_OFFSET_EXT
       parameter ( GL_POLYGON_OFFSET_EXT = 32823 )
       integer*4   GL_POLYGON_OFFSET_FACTOR_EXT
       parameter ( GL_POLYGON_OFFSET_FACTOR_EXT = 32824 )
       integer*4   GL_POLYGON_OFFSET_BIAS_EXT
       parameter ( GL_POLYGON_OFFSET_BIAS_EXT = 32825 )

C  EXT_rescale_normal 
       integer*4   GL_RESCALE_NORMAL_EXT
       parameter ( GL_RESCALE_NORMAL_EXT = 32826 )

C  EXT_texture 
       integer*4   GL_ALPHA4_EXT
       parameter ( GL_ALPHA4_EXT = 32827 )
       integer*4   GL_ALPHA8_EXT
       parameter ( GL_ALPHA8_EXT = 32828 )
       integer*4   GL_ALPHA12_EXT
       parameter ( GL_ALPHA12_EXT = 32829 )
       integer*4   GL_ALPHA16_EXT
       parameter ( GL_ALPHA16_EXT = 32830 )
       integer*4   GL_LUMINANCE4_EXT
       parameter ( GL_LUMINANCE4_EXT = 32831 )
       integer*4   GL_LUMINANCE8_EXT
       parameter ( GL_LUMINANCE8_EXT = 32832 )
       integer*4   GL_LUMINANCE12_EXT
       parameter ( GL_LUMINANCE12_EXT = 32833 )
       integer*4   GL_LUMINANCE16_EXT
       parameter ( GL_LUMINANCE16_EXT = 32834 )
       integer*4   GL_LUMINANCE4_ALPHA4_EXT
       parameter ( GL_LUMINANCE4_ALPHA4_EXT = 32835 )
       integer*4   GL_LUMINANCE6_ALPHA2_EXT
       parameter ( GL_LUMINANCE6_ALPHA2_EXT = 32836 )
       integer*4   GL_LUMINANCE8_ALPHA8_EXT
       parameter ( GL_LUMINANCE8_ALPHA8_EXT = 32837 )
       integer*4   GL_LUMINANCE12_ALPHA4_EXT
       parameter ( GL_LUMINANCE12_ALPHA4_EXT = 32838 )
       integer*4   GL_LUMINANCE12_ALPHA12_EXT
       parameter ( GL_LUMINANCE12_ALPHA12_EXT = 32839 )
       integer*4   GL_LUMINANCE16_ALPHA16_EXT
       parameter ( GL_LUMINANCE16_ALPHA16_EXT = 32840 )
       integer*4   GL_INTENSITY_EXT
       parameter ( GL_INTENSITY_EXT = 32841 )
       integer*4   GL_INTENSITY4_EXT
       parameter ( GL_INTENSITY4_EXT = 32842 )
       integer*4   GL_INTENSITY8_EXT
       parameter ( GL_INTENSITY8_EXT = 32843 )
       integer*4   GL_INTENSITY12_EXT
       parameter ( GL_INTENSITY12_EXT = 32844 )
       integer*4   GL_INTENSITY16_EXT
       parameter ( GL_INTENSITY16_EXT = 32845 )
       integer*4   GL_RGB2_EXT
       parameter ( GL_RGB2_EXT = 32846 )
       integer*4   GL_RGB4_EXT
       parameter ( GL_RGB4_EXT = 32847 )
       integer*4   GL_RGB5_EXT
       parameter ( GL_RGB5_EXT = 32848 )
       integer*4   GL_RGB8_EXT
       parameter ( GL_RGB8_EXT = 32849 )
       integer*4   GL_RGB10_EXT
       parameter ( GL_RGB10_EXT = 32850 )
       integer*4   GL_RGB12_EXT
       parameter ( GL_RGB12_EXT = 32851 )
       integer*4   GL_RGB16_EXT
       parameter ( GL_RGB16_EXT = 32852 )
       integer*4   GL_RGBA2_EXT
       parameter ( GL_RGBA2_EXT = 32853 )
       integer*4   GL_RGBA4_EXT
       parameter ( GL_RGBA4_EXT = 32854 )
       integer*4   GL_RGB5_A1_EXT
       parameter ( GL_RGB5_A1_EXT = 32855 )
       integer*4   GL_RGBA8_EXT
       parameter ( GL_RGBA8_EXT = 32856 )
       integer*4   GL_RGB10_A2_EXT
       parameter ( GL_RGB10_A2_EXT = 32857 )
       integer*4   GL_RGBA12_EXT
       parameter ( GL_RGBA12_EXT = 32858 )
       integer*4   GL_RGBA16_EXT
       parameter ( GL_RGBA16_EXT = 32859 )
       integer*4   GL_TEXTURE_RED_SIZE_EXT
       parameter ( GL_TEXTURE_RED_SIZE_EXT = 32860 )
       integer*4   GL_TEXTURE_GREEN_SIZE_EXT
       parameter ( GL_TEXTURE_GREEN_SIZE_EXT = 32861 )
       integer*4   GL_TEXTURE_BLUE_SIZE_EXT
       parameter ( GL_TEXTURE_BLUE_SIZE_EXT = 32862 )
       integer*4   GL_TEXTURE_ALPHA_SIZE_EXT
       parameter ( GL_TEXTURE_ALPHA_SIZE_EXT = 32863 )
       integer*4   GL_TEXTURE_LUMINANCE_SIZE_EXT
       parameter ( GL_TEXTURE_LUMINANCE_SIZE_EXT = 32864 )
       integer*4   GL_TEXTURE_INTENSITY_SIZE_EXT
       parameter ( GL_TEXTURE_INTENSITY_SIZE_EXT = 32865 )
       integer*4   GL_REPLACE_EXT
       parameter ( GL_REPLACE_EXT = 32866 )
       integer*4   GL_PROXY_TEXTURE_1D_EXT
       parameter ( GL_PROXY_TEXTURE_1D_EXT = 32867 )
       integer*4   GL_PROXY_TEXTURE_2D_EXT
       parameter ( GL_PROXY_TEXTURE_2D_EXT = 32868 )
       integer*4   GL_TEXTURE_TOO_LARGE_EXT
       parameter ( GL_TEXTURE_TOO_LARGE_EXT = 32869 )

C  EXT_texture_object 
       integer*4   GL_TEXTURE_PRIORITY_EXT
       parameter ( GL_TEXTURE_PRIORITY_EXT = 32870 )
       integer*4   GL_TEXTURE_RESIDENT_EXT
       parameter ( GL_TEXTURE_RESIDENT_EXT = 32871 )
       integer*4   GL_TEXTURE_1D_BINDING_EXT
       parameter ( GL_TEXTURE_1D_BINDING_EXT = 32872 )
       integer*4   GL_TEXTURE_2D_BINDING_EXT
       parameter ( GL_TEXTURE_2D_BINDING_EXT = 32873 )
       integer*4   GL_TEXTURE_3D_BINDING_EXT
       parameter ( GL_TEXTURE_3D_BINDING_EXT = 32874 )

C  EXT_texture3D 
       integer*4   GL_PACK_SKIP_IMAGES_EXT
       parameter ( GL_PACK_SKIP_IMAGES_EXT = 32875 )
       integer*4   GL_PACK_IMAGE_HEIGHT_EXT
       parameter ( GL_PACK_IMAGE_HEIGHT_EXT = 32876 )
       integer*4   GL_UNPACK_SKIP_IMAGES_EXT
       parameter ( GL_UNPACK_SKIP_IMAGES_EXT = 32877 )
       integer*4   GL_UNPACK_IMAGE_HEIGHT_EXT
       parameter ( GL_UNPACK_IMAGE_HEIGHT_EXT = 32878 )
       integer*4   GL_TEXTURE_3D_EXT
       parameter ( GL_TEXTURE_3D_EXT = 32879 )
       integer*4   GL_PROXY_TEXTURE_3D_EXT
       parameter ( GL_PROXY_TEXTURE_3D_EXT = 32880 )
       integer*4   GL_TEXTURE_DEPTH_EXT
       parameter ( GL_TEXTURE_DEPTH_EXT = 32881 )
       integer*4   GL_TEXTURE_WRAP_R_EXT
       parameter ( GL_TEXTURE_WRAP_R_EXT = 32882 )
       integer*4   GL_MAX_3D_TEXTURE_SIZE_EXT
       parameter ( GL_MAX_3D_TEXTURE_SIZE_EXT = 32883 )

C  EXT_vertex_array 
       integer*4   GL_VERTEX_ARRAY_EXT
       parameter ( GL_VERTEX_ARRAY_EXT = 32884 )
       integer*4   GL_NORMAL_ARRAY_EXT
       parameter ( GL_NORMAL_ARRAY_EXT = 32885 )
       integer*4   GL_COLOR_ARRAY_EXT
       parameter ( GL_COLOR_ARRAY_EXT = 32886 )
       integer*4   GL_INDEX_ARRAY_EXT
       parameter ( GL_INDEX_ARRAY_EXT = 32887 )
       integer*4   GL_TEXTURE_COORD_ARRAY_EXT
       parameter ( GL_TEXTURE_COORD_ARRAY_EXT = 32888 )
       integer*4   GL_EDGE_FLAG_ARRAY_EXT
       parameter ( GL_EDGE_FLAG_ARRAY_EXT = 32889 )
       integer*4   GL_VERTEX_ARRAY_SIZE_EXT
       parameter ( GL_VERTEX_ARRAY_SIZE_EXT = 32890 )
       integer*4   GL_VERTEX_ARRAY_TYPE_EXT
       parameter ( GL_VERTEX_ARRAY_TYPE_EXT = 32891 )
       integer*4   GL_VERTEX_ARRAY_STRIDE_EXT
       parameter ( GL_VERTEX_ARRAY_STRIDE_EXT = 32892 )
       integer*4   GL_VERTEX_ARRAY_COUNT_EXT
       parameter ( GL_VERTEX_ARRAY_COUNT_EXT = 32893 )
       integer*4   GL_NORMAL_ARRAY_TYPE_EXT
       parameter ( GL_NORMAL_ARRAY_TYPE_EXT = 32894 )
       integer*4   GL_NORMAL_ARRAY_STRIDE_EXT
       parameter ( GL_NORMAL_ARRAY_STRIDE_EXT = 32895 )
       integer*4   GL_NORMAL_ARRAY_COUNT_EXT
       parameter ( GL_NORMAL_ARRAY_COUNT_EXT = 32896 )
       integer*4   GL_COLOR_ARRAY_SIZE_EXT
       parameter ( GL_COLOR_ARRAY_SIZE_EXT = 32897 )
       integer*4   GL_COLOR_ARRAY_TYPE_EXT
       parameter ( GL_COLOR_ARRAY_TYPE_EXT = 32898 )
       integer*4   GL_COLOR_ARRAY_STRIDE_EXT
       parameter ( GL_COLOR_ARRAY_STRIDE_EXT = 32899 )
       integer*4   GL_COLOR_ARRAY_COUNT_EXT
       parameter ( GL_COLOR_ARRAY_COUNT_EXT = 32900 )
       integer*4   GL_INDEX_ARRAY_TYPE_EXT
       parameter ( GL_INDEX_ARRAY_TYPE_EXT = 32901 )
       integer*4   GL_INDEX_ARRAY_STRIDE_EXT
       parameter ( GL_INDEX_ARRAY_STRIDE_EXT = 32902 )
       integer*4   GL_INDEX_ARRAY_COUNT_EXT
       parameter ( GL_INDEX_ARRAY_COUNT_EXT = 32903 )
       integer*4   GL_TEXTURE_COORD_ARRAY_SIZE_EXT
       parameter ( GL_TEXTURE_COORD_ARRAY_SIZE_EXT = 32904 )
       integer*4   GL_TEXTURE_COORD_ARRAY_TYPE_EXT
       parameter ( GL_TEXTURE_COORD_ARRAY_TYPE_EXT = 32905 )
       integer*4   GL_TEXTURE_COORD_ARRAY_STRIDE_EXT
       parameter ( GL_TEXTURE_COORD_ARRAY_STRIDE_EXT = 32906 )
       integer*4   GL_TEXTURE_COORD_ARRAY_COUNT_EXT
       parameter ( GL_TEXTURE_COORD_ARRAY_COUNT_EXT = 32907 )
       integer*4   GL_EDGE_FLAG_ARRAY_STRIDE_EXT
       parameter ( GL_EDGE_FLAG_ARRAY_STRIDE_EXT = 32908 )
       integer*4   GL_EDGE_FLAG_ARRAY_COUNT_EXT
       parameter ( GL_EDGE_FLAG_ARRAY_COUNT_EXT = 32909 )
       integer*4   GL_VERTEX_ARRAY_POINTER_EXT
       parameter ( GL_VERTEX_ARRAY_POINTER_EXT = 32910 )
       integer*4   GL_NORMAL_ARRAY_POINTER_EXT
       parameter ( GL_NORMAL_ARRAY_POINTER_EXT = 32911 )
       integer*4   GL_COLOR_ARRAY_POINTER_EXT
       parameter ( GL_COLOR_ARRAY_POINTER_EXT = 32912 )
       integer*4   GL_INDEX_ARRAY_POINTER_EXT
       parameter ( GL_INDEX_ARRAY_POINTER_EXT = 32913 )
       integer*4   GL_TEXTURE_COORD_ARRAY_POINTER_EXT
       parameter ( GL_TEXTURE_COORD_ARRAY_POINTER_EXT = 32914 )
       integer*4   GL_EDGE_FLAG_ARRAY_POINTER_EXT
       parameter ( GL_EDGE_FLAG_ARRAY_POINTER_EXT = 32915 )

C  SGIX_interlace 
       integer*4   GL_INTERLACE_SGIX
       parameter ( GL_INTERLACE_SGIX = 32916 )

C  SGIS_detail_texture 
       integer*4   GL_DETAIL_TEXTURE_2D_SGIS
       parameter ( GL_DETAIL_TEXTURE_2D_SGIS = 32917 )
       integer*4   GL_DETAIL_TEXTURE_2D_BINDING_SGIS
       parameter ( GL_DETAIL_TEXTURE_2D_BINDING_SGIS = 32918 )
       integer*4   GL_LINEAR_DETAIL_SGIS
       parameter ( GL_LINEAR_DETAIL_SGIS = 32919 )
       integer*4   GL_LINEAR_DETAIL_ALPHA_SGIS
       parameter ( GL_LINEAR_DETAIL_ALPHA_SGIS = 32920 )
       integer*4   GL_LINEAR_DETAIL_COLOR_SGIS
       parameter ( GL_LINEAR_DETAIL_COLOR_SGIS = 32921 )
       integer*4   GL_DETAIL_TEXTURE_LEVEL_SGIS
       parameter ( GL_DETAIL_TEXTURE_LEVEL_SGIS = 32922 )
       integer*4   GL_DETAIL_TEXTURE_MODE_SGIS
       parameter ( GL_DETAIL_TEXTURE_MODE_SGIS = 32923 )
       integer*4   GL_DETAIL_TEXTURE_FUNC_POINTS_SGIS
       parameter ( GL_DETAIL_TEXTURE_FUNC_POINTS_SGIS = 32924 )

C  SGIS_multisample 
       integer*4   GL_MULTISAMPLE_SGIS
       parameter ( GL_MULTISAMPLE_SGIS = 32925 )
       integer*4   GL_SAMPLE_ALPHA_TO_MASK_SGIS
       parameter ( GL_SAMPLE_ALPHA_TO_MASK_SGIS = 32926 )
       integer*4   GL_SAMPLE_ALPHA_TO_ONE_SGIS
       parameter ( GL_SAMPLE_ALPHA_TO_ONE_SGIS = 32927 )
       integer*4   GL_SAMPLE_MASK_SGIS
       parameter ( GL_SAMPLE_MASK_SGIS = 32928 )
       integer*4   GL_1PASS_SGIS
       parameter ( GL_1PASS_SGIS = 32929 )
       integer*4   GL_2PASS_0_SGIS
       parameter ( GL_2PASS_0_SGIS = 32930 )
       integer*4   GL_2PASS_1_SGIS
       parameter ( GL_2PASS_1_SGIS = 32931 )
       integer*4   GL_4PASS_0_SGIS
       parameter ( GL_4PASS_0_SGIS = 32932 )
       integer*4   GL_4PASS_1_SGIS
       parameter ( GL_4PASS_1_SGIS = 32933 )
       integer*4   GL_4PASS_2_SGIS
       parameter ( GL_4PASS_2_SGIS = 32934 )
       integer*4   GL_4PASS_3_SGIS
       parameter ( GL_4PASS_3_SGIS = 32935 )
       integer*4   GL_SAMPLE_BUFFERS_SGIS
       parameter ( GL_SAMPLE_BUFFERS_SGIS = 32936 )
       integer*4   GL_SAMPLES_SGIS
       parameter ( GL_SAMPLES_SGIS = 32937 )
       integer*4   GL_SAMPLE_MASK_VALUE_SGIS
       parameter ( GL_SAMPLE_MASK_VALUE_SGIS = 32938 )
       integer*4   GL_SAMPLE_MASK_INVERT_SGIS
       parameter ( GL_SAMPLE_MASK_INVERT_SGIS = 32939 )
       integer*4   GL_SAMPLE_PATTERN_SGIS
       parameter ( GL_SAMPLE_PATTERN_SGIS = 32940 )

C  SGIS_sharpen_texture 
       integer*4   GL_LINEAR_SHARPEN_SGIS
       parameter ( GL_LINEAR_SHARPEN_SGIS = 32941 )
       integer*4   GL_LINEAR_SHARPEN_ALPHA_SGIS
       parameter ( GL_LINEAR_SHARPEN_ALPHA_SGIS = 32942 )
       integer*4   GL_LINEAR_SHARPEN_COLOR_SGIS
       parameter ( GL_LINEAR_SHARPEN_COLOR_SGIS = 32943 )
       integer*4   GL_SHARPEN_TEXTURE_FUNC_POINTS_SGIS
       parameter ( GL_SHARPEN_TEXTURE_FUNC_POINTS_SGIS = 32944 )

C  SGI_color_matrix 
       integer*4   GL_COLOR_MATRIX_SGI
       parameter ( GL_COLOR_MATRIX_SGI = 32945 )
       integer*4   GL_COLOR_MATRIX_STACK_DEPTH_SGI
       parameter ( GL_COLOR_MATRIX_STACK_DEPTH_SGI = 32946 )
       integer*4   GL_MAX_COLOR_MATRIX_STACK_DEPTH_SGI
       parameter ( GL_MAX_COLOR_MATRIX_STACK_DEPTH_SGI = 32947 )
       integer*4   GL_POST_COLOR_MATRIX_RED_SCALE_SGI
       parameter ( GL_POST_COLOR_MATRIX_RED_SCALE_SGI = 32948 )
       integer*4   GL_POST_COLOR_MATRIX_GREEN_SCALE_SGI
       parameter ( GL_POST_COLOR_MATRIX_GREEN_SCALE_SGI = 32949 )
       integer*4   GL_POST_COLOR_MATRIX_BLUE_SCALE_SGI
       parameter ( GL_POST_COLOR_MATRIX_BLUE_SCALE_SGI = 32950 )
       integer*4   GL_POST_COLOR_MATRIX_ALPHA_SCALE_SGI
       parameter ( GL_POST_COLOR_MATRIX_ALPHA_SCALE_SGI = 32951 )
       integer*4   GL_POST_COLOR_MATRIX_RED_BIAS_SGI
       parameter ( GL_POST_COLOR_MATRIX_RED_BIAS_SGI = 32952 )
       integer*4   GL_POST_COLOR_MATRIX_GREEN_BIAS_SGI
       parameter ( GL_POST_COLOR_MATRIX_GREEN_BIAS_SGI = 32953 )
       integer*4   GL_POST_COLOR_MATRIX_BLUE_BIAS_SGI
       parameter ( GL_POST_COLOR_MATRIX_BLUE_BIAS_SGI = 32954 )
       integer*4   GL_POST_COLOR_MATRIX_ALPHA_BIAS_SGI
       parameter ( GL_POST_COLOR_MATRIX_ALPHA_BIAS_SGI = 32955 )

C  SGI_texture_color_table 
       integer*4   GL_TEXTURE_COLOR_TABLE_SGI
       parameter ( GL_TEXTURE_COLOR_TABLE_SGI = 32956 )
       integer*4   GL_PROXY_TEXTURE_COLOR_TABLE_SGI
       parameter ( GL_PROXY_TEXTURE_COLOR_TABLE_SGI = 32957 )

C  SGIX_texture_add_env 
       integer*4   GL_TEXTURE_ENV_BIAS_SGIX
       parameter ( GL_TEXTURE_ENV_BIAS_SGIX = 32958 )

C  SGIX_shadow_ambient 
       integer*4   GL_SHADOW_AMBIENT_SGIX
       parameter ( GL_SHADOW_AMBIENT_SGIX = 32959 )

C  SGI_color_table 
       integer*4   GL_COLOR_TABLE_SGI
       parameter ( GL_COLOR_TABLE_SGI = 32976 )
       integer*4   GL_POST_CONVOLUTION_COLOR_TABLE_SGI
       parameter ( GL_POST_CONVOLUTION_COLOR_TABLE_SGI = 32977 )
       integer*4   GL_POST_COLOR_MATRIX_COLOR_TABLE_SGI
       parameter ( GL_POST_COLOR_MATRIX_COLOR_TABLE_SGI = 32978 )
       integer*4   GL_PROXY_COLOR_TABLE_SGI
       parameter ( GL_PROXY_COLOR_TABLE_SGI = 32979 )
       integer*4   GL_PROXY_POST_CONVOLUTION_COLOR_TABLE_SGI
       parameter ( GL_PROXY_POST_CONVOLUTION_COLOR_TABLE_SGI = 32980 )
       integer*4   GL_PROXY_POST_COLOR_MATRIX_COLOR_TABLE_SGI
       parameter (
     +  GL_PROXY_POST_COLOR_MATRIX_COLOR_TABLE_SGI = 32981 )
       integer*4   GL_COLOR_TABLE_SCALE_SGI
       parameter ( GL_COLOR_TABLE_SCALE_SGI = 32982 )
       integer*4   GL_COLOR_TABLE_BIAS_SGI
       parameter ( GL_COLOR_TABLE_BIAS_SGI = 32983 )
       integer*4   GL_COLOR_TABLE_FORMAT_SGI
       parameter ( GL_COLOR_TABLE_FORMAT_SGI = 32984 )
       integer*4   GL_COLOR_TABLE_WIDTH_SGI
       parameter ( GL_COLOR_TABLE_WIDTH_SGI = 32985 )
       integer*4   GL_COLOR_TABLE_RED_SIZE_SGI
       parameter ( GL_COLOR_TABLE_RED_SIZE_SGI = 32986 )
       integer*4   GL_COLOR_TABLE_GREEN_SIZE_SGI
       parameter ( GL_COLOR_TABLE_GREEN_SIZE_SGI = 32987 )
       integer*4   GL_COLOR_TABLE_BLUE_SIZE_SGI
       parameter ( GL_COLOR_TABLE_BLUE_SIZE_SGI = 32988 )
       integer*4   GL_COLOR_TABLE_ALPHA_SIZE_SGI
       parameter ( GL_COLOR_TABLE_ALPHA_SIZE_SGI = 32989 )
       integer*4   GL_COLOR_TABLE_LUMINANCE_SIZE_SGI
       parameter ( GL_COLOR_TABLE_LUMINANCE_SIZE_SGI = 32990 )
       integer*4   GL_COLOR_TABLE_INTENSITY_SIZE_SGI
       parameter ( GL_COLOR_TABLE_INTENSITY_SIZE_SGI = 32991 )

C  SGIS_texture_select 
       integer*4   GL_DUAL_ALPHA4_SGIS
       parameter ( GL_DUAL_ALPHA4_SGIS = 33040 )
       integer*4   GL_DUAL_ALPHA8_SGIS
       parameter ( GL_DUAL_ALPHA8_SGIS = 33041 )
       integer*4   GL_DUAL_ALPHA12_SGIS
       parameter ( GL_DUAL_ALPHA12_SGIS = 33042 )
       integer*4   GL_DUAL_ALPHA16_SGIS
       parameter ( GL_DUAL_ALPHA16_SGIS = 33043 )
       integer*4   GL_DUAL_LUMINANCE4_SGIS
       parameter ( GL_DUAL_LUMINANCE4_SGIS = 33044 )
       integer*4   GL_DUAL_LUMINANCE8_SGIS
       parameter ( GL_DUAL_LUMINANCE8_SGIS = 33045 )
       integer*4   GL_DUAL_LUMINANCE12_SGIS
       parameter ( GL_DUAL_LUMINANCE12_SGIS = 33046 )
       integer*4   GL_DUAL_LUMINANCE16_SGIS
       parameter ( GL_DUAL_LUMINANCE16_SGIS = 33047 )
       integer*4   GL_DUAL_INTENSITY4_SGIS
       parameter ( GL_DUAL_INTENSITY4_SGIS = 33048 )
       integer*4   GL_DUAL_INTENSITY8_SGIS
       parameter ( GL_DUAL_INTENSITY8_SGIS = 33049 )
       integer*4   GL_DUAL_INTENSITY12_SGIS
       parameter ( GL_DUAL_INTENSITY12_SGIS = 33050 )
       integer*4   GL_DUAL_INTENSITY16_SGIS
       parameter ( GL_DUAL_INTENSITY16_SGIS = 33051 )
       integer*4   GL_DUAL_LUMINANCE_ALPHA4_SGIS
       parameter ( GL_DUAL_LUMINANCE_ALPHA4_SGIS = 33052 )
       integer*4   GL_DUAL_LUMINANCE_ALPHA8_SGIS
       parameter ( GL_DUAL_LUMINANCE_ALPHA8_SGIS = 33053 )
       integer*4   GL_QUAD_ALPHA4_SGIS
       parameter ( GL_QUAD_ALPHA4_SGIS = 33054 )
       integer*4   GL_QUAD_ALPHA8_SGIS
       parameter ( GL_QUAD_ALPHA8_SGIS = 33055 )
       integer*4   GL_QUAD_LUMINANCE4_SGIS
       parameter ( GL_QUAD_LUMINANCE4_SGIS = 33056 )
       integer*4   GL_QUAD_LUMINANCE8_SGIS
       parameter ( GL_QUAD_LUMINANCE8_SGIS = 33057 )
       integer*4   GL_QUAD_INTENSITY4_SGIS
       parameter ( GL_QUAD_INTENSITY4_SGIS = 33058 )
       integer*4   GL_QUAD_INTENSITY8_SGIS
       parameter ( GL_QUAD_INTENSITY8_SGIS = 33059 )
       integer*4   GL_DUAL_TEXTURE_SELECT_SGIS
       parameter ( GL_DUAL_TEXTURE_SELECT_SGIS = 33060 )
       integer*4   GL_QUAD_TEXTURE_SELECT_SGIS
       parameter ( GL_QUAD_TEXTURE_SELECT_SGIS = 33061 )

C  EXT_point_parameters 
       integer*4   GL_POINT_SIZE_MIN_EXT
       parameter ( GL_POINT_SIZE_MIN_EXT = 33062 )
       integer*4   GL_POINT_SIZE_MAX_EXT
       parameter ( GL_POINT_SIZE_MAX_EXT = 33063 )
       integer*4   GL_POINT_FADE_THRESHOLD_SIZE_EXT
       parameter ( GL_POINT_FADE_THRESHOLD_SIZE_EXT = 33064 )
       integer*4   GL_DISTANCE_ATTENUATION_EXT
       parameter ( GL_DISTANCE_ATTENUATION_EXT = 33065 )

C  SGIS_point_parameters 
       integer*4   GL_POINT_SIZE_MIN_SGIS
       parameter ( GL_POINT_SIZE_MIN_SGIS = 33062 )
       integer*4   GL_POINT_SIZE_MAX_SGIS
       parameter ( GL_POINT_SIZE_MAX_SGIS = 33063 )
       integer*4   GL_POINT_FADE_THRESHOLD_SIZE_SGIS
       parameter ( GL_POINT_FADE_THRESHOLD_SIZE_SGIS = 33064 )
       integer*4   GL_DISTANCE_ATTENUATION_SGIS
       parameter ( GL_DISTANCE_ATTENUATION_SGIS = 33065 )

C  SGIS_fog_function 
       integer*4   GL_FOG_FUNC_SGIS
       parameter ( GL_FOG_FUNC_SGIS = 33066 )
       integer*4   GL_FOG_FUNC_POINTS_SGIS
       parameter ( GL_FOG_FUNC_POINTS_SGIS = 33067 )
       integer*4   GL_MAX_FOG_FUNC_POINTS_SGIS
       parameter ( GL_MAX_FOG_FUNC_POINTS_SGIS = 33068 )

C  SGIS_texture_border_clamp 

C  SGIX_texture_multi_buffer 
       integer*4   GL_TEXTURE_MULTI_BUFFER_HINT_SGIX
       parameter ( GL_TEXTURE_MULTI_BUFFER_HINT_SGIX = 33070 )

C  SGIS_texture_edge_clamp 
       integer*4   GL_CLAMP_TO_EDGE_SGIS
       parameter ( GL_CLAMP_TO_EDGE_SGIS = 33071 )

C  SGIS_texture4D 
       integer*4   GL_PACK_SKIP_VOLUMES_SGIS
       parameter ( GL_PACK_SKIP_VOLUMES_SGIS = 33072 )
       integer*4   GL_PACK_IMAGE_DEPTH_SGIS
       parameter ( GL_PACK_IMAGE_DEPTH_SGIS = 33073 )
       integer*4   GL_UNPACK_SKIP_VOLUMES_SGIS
       parameter ( GL_UNPACK_SKIP_VOLUMES_SGIS = 33074 )
       integer*4   GL_UNPACK_IMAGE_DEPTH_SGIS
       parameter ( GL_UNPACK_IMAGE_DEPTH_SGIS = 33075 )
       integer*4   GL_TEXTURE_4D_SGIS
       parameter ( GL_TEXTURE_4D_SGIS = 33076 )
       integer*4   GL_PROXY_TEXTURE_4D_SGIS
       parameter ( GL_PROXY_TEXTURE_4D_SGIS = 33077 )
       integer*4   GL_TEXTURE_4DSIZE_SGIS
       parameter ( GL_TEXTURE_4DSIZE_SGIS = 33078 )
       integer*4   GL_TEXTURE_WRAP_Q_SGIS
       parameter ( GL_TEXTURE_WRAP_Q_SGIS = 33079 )
       integer*4   GL_MAX_4D_TEXTURE_SIZE_SGIS
       parameter ( GL_MAX_4D_TEXTURE_SIZE_SGIS = 33080 )
       integer*4   GL_TEXTURE_4D_BINDING_SGIS
       parameter ( GL_TEXTURE_4D_BINDING_SGIS = 33103 )

C  SGIX_pixel_texture 
       integer*4   GL_PIXEL_TEX_GEN_SGIX
       parameter ( GL_PIXEL_TEX_GEN_SGIX = 33081 )
       integer*4   GL_PIXEL_TEX_GEN_MODE_SGIX
       parameter ( GL_PIXEL_TEX_GEN_MODE_SGIX = 33579 )

C  SGIS_texture_lod 
       integer*4   GL_TEXTURE_MIN_LOD_SGIS
       parameter ( GL_TEXTURE_MIN_LOD_SGIS = 33082 )
       integer*4   GL_TEXTURE_MAX_LOD_SGIS
       parameter ( GL_TEXTURE_MAX_LOD_SGIS = 33083 )
       integer*4   GL_TEXTURE_BASE_LEVEL_SGIS
       parameter ( GL_TEXTURE_BASE_LEVEL_SGIS = 33084 )
       integer*4   GL_TEXTURE_MAX_LEVEL_SGIS
       parameter ( GL_TEXTURE_MAX_LEVEL_SGIS = 33085 )

C  SGIX_pixel_tiles 
       integer*4   GL_PIXEL_TILE_BEST_ALIGNMENT_SGIX
       parameter ( GL_PIXEL_TILE_BEST_ALIGNMENT_SGIX = 33086 )
       integer*4   GL_PIXEL_TILE_CACHE_INCREMENT_SGIX
       parameter ( GL_PIXEL_TILE_CACHE_INCREMENT_SGIX = 33087 )
       integer*4   GL_PIXEL_TILE_WIDTH_SGIX
       parameter ( GL_PIXEL_TILE_WIDTH_SGIX = 33088 )
       integer*4   GL_PIXEL_TILE_HEIGHT_SGIX
       parameter ( GL_PIXEL_TILE_HEIGHT_SGIX = 33089 )
       integer*4   GL_PIXEL_TILE_GRID_WIDTH_SGIX
       parameter ( GL_PIXEL_TILE_GRID_WIDTH_SGIX = 33090 )
       integer*4   GL_PIXEL_TILE_GRID_HEIGHT_SGIX
       parameter ( GL_PIXEL_TILE_GRID_HEIGHT_SGIX = 33091 )
       integer*4   GL_PIXEL_TILE_GRID_DEPTH_SGIX
       parameter ( GL_PIXEL_TILE_GRID_DEPTH_SGIX = 33092 )
       integer*4   GL_PIXEL_TILE_CACHE_SIZE_SGIX
       parameter ( GL_PIXEL_TILE_CACHE_SIZE_SGIX = 33093 )

C  SGIS_texture_filter4 
       integer*4   GL_FILTER4_SGIS
       parameter ( GL_FILTER4_SGIS = 33094 )
       integer*4   GL_TEXTURE_FILTER4_SIZE_SGIS
       parameter ( GL_TEXTURE_FILTER4_SIZE_SGIS = 33095 )

C  SGIX_sprite 
       integer*4   GL_SPRITE_SGIX
       parameter ( GL_SPRITE_SGIX = 33096 )
       integer*4   GL_SPRITE_MODE_SGIX
       parameter ( GL_SPRITE_MODE_SGIX = 33097 )
       integer*4   GL_SPRITE_AXIS_SGIX
       parameter ( GL_SPRITE_AXIS_SGIX = 33098 )
       integer*4   GL_SPRITE_TRANSLATION_SGIX
       parameter ( GL_SPRITE_TRANSLATION_SGIX = 33099 )
       integer*4   GL_SPRITE_AXIAL_SGIX
       parameter ( GL_SPRITE_AXIAL_SGIX = 33100 )
       integer*4   GL_SPRITE_OBJECT_ALIGNED_SGIX
       parameter ( GL_SPRITE_OBJECT_ALIGNED_SGIX = 33101 )
       integer*4   GL_SPRITE_EYE_ALIGNED_SGIX
       parameter ( GL_SPRITE_EYE_ALIGNED_SGIX = 33102 )

C  SGIX_clipmap 
       integer*4   GL_LINEAR_CLIPMAP_LINEAR_SGIX
       parameter ( GL_LINEAR_CLIPMAP_LINEAR_SGIX = 33136 )
       integer*4   GL_TEXTURE_CLIPMAP_CENTER_SGIX
       parameter ( GL_TEXTURE_CLIPMAP_CENTER_SGIX = 33137 )
       integer*4   GL_TEXTURE_CLIPMAP_FRAME_SGIX
       parameter ( GL_TEXTURE_CLIPMAP_FRAME_SGIX = 33138 )
       integer*4   GL_TEXTURE_CLIPMAP_OFFSET_SGIX
       parameter ( GL_TEXTURE_CLIPMAP_OFFSET_SGIX = 33139 )
       integer*4   GL_TEXTURE_CLIPMAP_VIRTUAL_DEPTH_SGIX
       parameter ( GL_TEXTURE_CLIPMAP_VIRTUAL_DEPTH_SGIX = 33140 )
       integer*4   GL_TEXTURE_CLIPMAP_LOD_OFFSET_SGIX
       parameter ( GL_TEXTURE_CLIPMAP_LOD_OFFSET_SGIX = 33141 )
       integer*4   GL_TEXTURE_CLIPMAP_DEPTH_SGIX
       parameter ( GL_TEXTURE_CLIPMAP_DEPTH_SGIX = 33142 )
       integer*4   GL_MAX_CLIPMAP_DEPTH_SGIX
       parameter ( GL_MAX_CLIPMAP_DEPTH_SGIX = 33143 )
       integer*4   GL_MAX_CLIPMAP_VIRTUAL_DEPTH_SGIX
       parameter ( GL_MAX_CLIPMAP_VIRTUAL_DEPTH_SGIX = 33144 )
       integer*4   GL_NEAREST_CLIPMAP_NEAREST_SGIX
       parameter ( GL_NEAREST_CLIPMAP_NEAREST_SGIX = 33869 )
       integer*4   GL_NEAREST_CLIPMAP_LINEAR_SGIX
       parameter ( GL_NEAREST_CLIPMAP_LINEAR_SGIX = 33870 )
       integer*4   GL_LINEAR_CLIPMAP_NEAREST_SGIX
       parameter ( GL_LINEAR_CLIPMAP_NEAREST_SGIX = 33871 )

C  SGIX_texture_scale_bias 
       integer*4   GL_POST_TEXTURE_FILTER_BIAS_SGIX
       parameter ( GL_POST_TEXTURE_FILTER_BIAS_SGIX = 33145 )
       integer*4   GL_POST_TEXTURE_FILTER_SCALE_SGIX
       parameter ( GL_POST_TEXTURE_FILTER_SCALE_SGIX = 33146 )
       integer*4   GL_POST_TEXTURE_FILTER_BIAS_RANGE_SGIX
       parameter ( GL_POST_TEXTURE_FILTER_BIAS_RANGE_SGIX = 33147 )
       integer*4   GL_POST_TEXTURE_FILTER_SCALE_RANGE_SGIX
       parameter ( GL_POST_TEXTURE_FILTER_SCALE_RANGE_SGIX = 33148 )

C  SGIX_reference_plane 
       integer*4   GL_REFERENCE_PLANE_SGIX
       parameter ( GL_REFERENCE_PLANE_SGIX = 33149 )
       integer*4   GL_REFERENCE_PLANE_EQUATION_SGIX
       parameter ( GL_REFERENCE_PLANE_EQUATION_SGIX = 33150 )

C  SGIX_ir_instrument1 
       integer*4   GL_IR_INSTRUMENT1_SGIX
       parameter ( GL_IR_INSTRUMENT1_SGIX = 33151 )

C  SGIX_instruments 
       integer*4   GL_INSTRUMENT_BUFFER_POINTER_SGIX
       parameter ( GL_INSTRUMENT_BUFFER_POINTER_SGIX = 33152 )
       integer*4   GL_INSTRUMENT_MEASUREMENTS_SGIX
       parameter ( GL_INSTRUMENT_MEASUREMENTS_SGIX = 33153 )

C  SGIX_list_priority 
       integer*4   GL_LIST_PRIORITY_SGIX
       parameter ( GL_LIST_PRIORITY_SGIX = 33154 )

C  SGIX_calligraphic_fragment 
       integer*4   GL_CALLIGRAPHIC_FRAGMENT_SGIX
       parameter ( GL_CALLIGRAPHIC_FRAGMENT_SGIX = 33155 )

C  SGIX_impact_pixel_texture 
       integer*4   GL_PIXEL_TEX_GEN_Q_CEILING_SGIX
       parameter ( GL_PIXEL_TEX_GEN_Q_CEILING_SGIX = 33156 )
       integer*4   GL_PIXEL_TEX_GEN_Q_ROUND_SGIX
       parameter ( GL_PIXEL_TEX_GEN_Q_ROUND_SGIX = 33157 )
       integer*4   GL_PIXEL_TEX_GEN_Q_FLOOR_SGIX
       parameter ( GL_PIXEL_TEX_GEN_Q_FLOOR_SGIX = 33158 )
       integer*4   GL_PIXEL_TEX_GEN_ALPHA_REPLACE_SGIX
       parameter ( GL_PIXEL_TEX_GEN_ALPHA_REPLACE_SGIX = 33159 )
       integer*4   GL_PIXEL_TEX_GEN_ALPHA_NO_REPLACE_SGIX
       parameter ( GL_PIXEL_TEX_GEN_ALPHA_NO_REPLACE_SGIX = 33160 )
       integer*4   GL_PIXEL_TEX_GEN_ALPHA_LS_SGIX
       parameter ( GL_PIXEL_TEX_GEN_ALPHA_LS_SGIX = 33161 )
       integer*4   GL_PIXEL_TEX_GEN_ALPHA_MS_SGIX
       parameter ( GL_PIXEL_TEX_GEN_ALPHA_MS_SGIX = 33162 )

C  SGIX_framezoom 
       integer*4   GL_FRAMEZOOM_SGIX
       parameter ( GL_FRAMEZOOM_SGIX = 33163 )
       integer*4   GL_FRAMEZOOM_FACTOR_SGIX
       parameter ( GL_FRAMEZOOM_FACTOR_SGIX = 33164 )
       integer*4   GL_MAX_FRAMEZOOM_FACTOR_SGIX
       parameter ( GL_MAX_FRAMEZOOM_FACTOR_SGIX = 33165 )

C  SGIX_texture_lod_bias 
       integer*4   GL_TEXTURE_LOD_BIAS_S_SGIX
       parameter ( GL_TEXTURE_LOD_BIAS_S_SGIX = 33166 )
       integer*4   GL_TEXTURE_LOD_BIAS_T_SGIX
       parameter ( GL_TEXTURE_LOD_BIAS_T_SGIX = 33167 )
       integer*4   GL_TEXTURE_LOD_BIAS_R_SGIX
       parameter ( GL_TEXTURE_LOD_BIAS_R_SGIX = 33168 )

C  SGIS_generate_mipmap 
       integer*4   GL_GENERATE_MIPMAP_SGIS
       parameter ( GL_GENERATE_MIPMAP_SGIS = 33169 )
       integer*4   GL_GENERATE_MIPMAP_HINT_SGIS
       parameter ( GL_GENERATE_MIPMAP_HINT_SGIS = 33170 )

C  SGIX_polynomial_ffd 
       integer*4   GL_GEOMETRY_DEFORMATION_SGIX
       parameter ( GL_GEOMETRY_DEFORMATION_SGIX = 33172 )
       integer*4   GL_TEXTURE_DEFORMATION_SGIX
       parameter ( GL_TEXTURE_DEFORMATION_SGIX = 33173 )
       integer*4   GL_DEFORMATIONS_MASK_SGIX
       parameter ( GL_DEFORMATIONS_MASK_SGIX = 33174 )
       integer*4   GL_MAX_DEFORMATION_ORDER_SGIX
       parameter ( GL_MAX_DEFORMATION_ORDER_SGIX = 33175 )

C  SGIX_fog_offset 
       integer*4   GL_FOG_OFFSET_SGIX
       parameter ( GL_FOG_OFFSET_SGIX = 33176 )
       integer*4   GL_FOG_OFFSET_VALUE_SGIX
       parameter ( GL_FOG_OFFSET_VALUE_SGIX = 33177 )

C  SGIX_shadow 
       integer*4   GL_TEXTURE_COMPARE_SGIX
       parameter ( GL_TEXTURE_COMPARE_SGIX = 33178 )
       integer*4   GL_TEXTURE_COMPARE_OPERATOR_SGIX
       parameter ( GL_TEXTURE_COMPARE_OPERATOR_SGIX = 33179 )
       integer*4   GL_TEXTURE_LEQUAL_R_SGIX
       parameter ( GL_TEXTURE_LEQUAL_R_SGIX = 33180 )
       integer*4   GL_TEXTURE_GEQUAL_R_SGIX
       parameter ( GL_TEXTURE_GEQUAL_R_SGIX = 33181 )

C  SGIX_depth_texture 
       integer*4   GL_DEPTH_COMPONENT16_SGIX
       parameter ( GL_DEPTH_COMPONENT16_SGIX = 33189 )
       integer*4   GL_DEPTH_COMPONENT24_SGIX
       parameter ( GL_DEPTH_COMPONENT24_SGIX = 33190 )
       integer*4   GL_DEPTH_COMPONENT32_SGIX
       parameter ( GL_DEPTH_COMPONENT32_SGIX = 33191 )

C  SGIX_ycrcb 
       integer*4   GL_YCRCB_422_SGIX
       parameter ( GL_YCRCB_422_SGIX = 33211 )
       integer*4   GL_YCRCB_444_SGIX
       parameter ( GL_YCRCB_444_SGIX = 33212 )

C  SGIS_texture_color_mask 
       integer*4   GL_TEXTURE_COLOR_WRITEMASK_SGIS
       parameter ( GL_TEXTURE_COLOR_WRITEMASK_SGIS = 33263 )

C  SGIS_point_line_texgen 
       integer*4   GL_EYE_DISTANCE_TO_POINT_SGIS
       parameter ( GL_EYE_DISTANCE_TO_POINT_SGIS = 33264 )
       integer*4   GL_OBJECT_DISTANCE_TO_POINT_SGIS
       parameter ( GL_OBJECT_DISTANCE_TO_POINT_SGIS = 33265 )
       integer*4   GL_EYE_DISTANCE_TO_LINE_SGIS
       parameter ( GL_EYE_DISTANCE_TO_LINE_SGIS = 33266 )
       integer*4   GL_OBJECT_DISTANCE_TO_LINE_SGIS
       parameter ( GL_OBJECT_DISTANCE_TO_LINE_SGIS = 33267 )
       integer*4   GL_EYE_POINT_SGIS
       parameter ( GL_EYE_POINT_SGIS = 33268 )
       integer*4   GL_OBJECT_POINT_SGIS
       parameter ( GL_OBJECT_POINT_SGIS = 33269 )
       integer*4   GL_EYE_LINE_SGIS
       parameter ( GL_EYE_LINE_SGIS = 33270 )
       integer*4   GL_OBJECT_LINE_SGIS
       parameter ( GL_OBJECT_LINE_SGIS = 33271 )

C  EXT_shared_texture_palette 
       integer*4   GL_SHARED_TEXTURE_PALETTE_EXT
       parameter ( GL_SHARED_TEXTURE_PALETTE_EXT = 33275 )

C  SGIX_convolution_accuracy 
       integer*4   GL_CONVOLUTION_HINT_SGIX
       parameter ( GL_CONVOLUTION_HINT_SGIX = 33558 )

C  SGIX_blend_alpha_minmax 
       integer*4   GL_ALPHA_MIN_SGIX
       parameter ( GL_ALPHA_MIN_SGIX = 33568 )
       integer*4   GL_ALPHA_MAX_SGIX
       parameter ( GL_ALPHA_MAX_SGIX = 33569 )

C  SGIX_scalebias_hint 
       integer*4   GL_SCALEBIAS_HINT_SGIX
       parameter ( GL_SCALEBIAS_HINT_SGIX = 33570 )

C  SGIX_async 
       integer*4   GL_ASYNC_MARKER_SGIX
       parameter ( GL_ASYNC_MARKER_SGIX = 33577 )

C  SGIX_async_histogram 
       integer*4   GL_ASYNC_HISTOGRAM_SGIX
       parameter ( GL_ASYNC_HISTOGRAM_SGIX = 33580 )
       integer*4   GL_MAX_ASYNC_HISTOGRAM_SGIX
       parameter ( GL_MAX_ASYNC_HISTOGRAM_SGIX = 33581 )

C  SGIS_pixel_texture 
       integer*4   GL_PIXEL_TEXTURE_SGIS
       parameter ( GL_PIXEL_TEXTURE_SGIS = 33619 )
       integer*4   GL_PIXEL_FRAGMENT_RGB_SOURCE_SGIS
       parameter ( GL_PIXEL_FRAGMENT_RGB_SOURCE_SGIS = 33620 )
       integer*4   GL_PIXEL_FRAGMENT_ALPHA_SOURCE_SGIS
       parameter ( GL_PIXEL_FRAGMENT_ALPHA_SOURCE_SGIS = 33621 )
       integer*4   GL_PIXEL_GROUP_COLOR_SGIS
       parameter ( GL_PIXEL_GROUP_COLOR_SGIS = 33622 )

C  SGIX_async_pixel 
       integer*4   GL_ASYNC_TEX_IMAGE_SGIX
       parameter ( GL_ASYNC_TEX_IMAGE_SGIX = 33628 )
       integer*4   GL_ASYNC_DRAW_PIXELS_SGIX
       parameter ( GL_ASYNC_DRAW_PIXELS_SGIX = 33629 )
       integer*4   GL_ASYNC_READ_PIXELS_SGIX
       parameter ( GL_ASYNC_READ_PIXELS_SGIX = 33630 )
       integer*4   GL_MAX_ASYNC_TEX_IMAGE_SGIX
       parameter ( GL_MAX_ASYNC_TEX_IMAGE_SGIX = 33631 )
       integer*4   GL_MAX_ASYNC_DRAW_PIXELS_SGIX
       parameter ( GL_MAX_ASYNC_DRAW_PIXELS_SGIX = 33632 )
       integer*4   GL_MAX_ASYNC_READ_PIXELS_SGIX
       parameter ( GL_MAX_ASYNC_READ_PIXELS_SGIX = 33633 )

C  SGIX_texture_coordinate_clamp 
       integer*4   GL_TEXTURE_MAX_CLAMP_S_SGIX
       parameter ( GL_TEXTURE_MAX_CLAMP_S_SGIX = 33641 )
       integer*4   GL_TEXTURE_MAX_CLAMP_T_SGIX
       parameter ( GL_TEXTURE_MAX_CLAMP_T_SGIX = 33642 )
       integer*4   GL_TEXTURE_MAX_CLAMP_R_SGIX
       parameter ( GL_TEXTURE_MAX_CLAMP_R_SGIX = 33643 )

C  SGIX_vertex_preclip 
       integer*4   GL_VERTEX_PRECLIP_SGIX
       parameter ( GL_VERTEX_PRECLIP_SGIX = 33774 )
       integer*4   GL_VERTEX_PRECLIP_HINT_SGIX
       parameter ( GL_VERTEX_PRECLIP_HINT_SGIX = 33775 )

C  SGIX_fragment_lighting 
       integer*4   GL_FRAGMENT_LIGHTING_SGIX
       parameter ( GL_FRAGMENT_LIGHTING_SGIX = 33792 )
       integer*4   GL_FRAGMENT_COLOR_MATERIAL_SGIX
       parameter ( GL_FRAGMENT_COLOR_MATERIAL_SGIX = 33793 )
       integer*4   GL_FRAGMENT_COLOR_MATERIAL_FACE_SGIX
       parameter ( GL_FRAGMENT_COLOR_MATERIAL_FACE_SGIX = 33794 )
       integer*4   GL_FRAGMENT_COLOR_MATERIAL_PARAMETER_SGIX
       parameter ( GL_FRAGMENT_COLOR_MATERIAL_PARAMETER_SGIX = 33795 )
       integer*4   GL_MAX_FRAGMENT_LIGHTS_SGIX
       parameter ( GL_MAX_FRAGMENT_LIGHTS_SGIX = 33796 )
       integer*4   GL_MAX_ACTIVE_LIGHTS_SGIX
       parameter ( GL_MAX_ACTIVE_LIGHTS_SGIX = 33797 )
       integer*4   GL_CURRENT_RASTER_NORMAL_SGIX
       parameter ( GL_CURRENT_RASTER_NORMAL_SGIX = 33798 )
       integer*4   GL_LIGHT_ENV_MODE_SGIX
       parameter ( GL_LIGHT_ENV_MODE_SGIX = 33799 )
       integer*4   GL_FRAGMENT_LIGHT_MODEL_LOCAL_VIEWER_SGIX
       parameter ( GL_FRAGMENT_LIGHT_MODEL_LOCAL_VIEWER_SGIX = 33800 )
       integer*4   GL_FRAGMENT_LIGHT_MODEL_TWO_SIDE_SGIX
       parameter ( GL_FRAGMENT_LIGHT_MODEL_TWO_SIDE_SGIX = 33801 )
       integer*4   GL_FRAGMENT_LIGHT_MODEL_AMBIENT_SGIX
       parameter ( GL_FRAGMENT_LIGHT_MODEL_AMBIENT_SGIX = 33802 )
       integer*4   GL_FRAGMENT_LIGHT_MODEL_NORMAL_INTERPOLATION_SGIX
       parameter (
     +  GL_FRAGMENT_LIGHT_MODEL_NORMAL_INTERPOLATION_SGIX = 33803 )
       integer*4   GL_FRAGMENT_LIGHT0_SGIX
       parameter ( GL_FRAGMENT_LIGHT0_SGIX = 33804 )
       integer*4   GL_FRAGMENT_LIGHT1_SGIX
       parameter ( GL_FRAGMENT_LIGHT1_SGIX = 33805 )
       integer*4   GL_FRAGMENT_LIGHT2_SGIX
       parameter ( GL_FRAGMENT_LIGHT2_SGIX = 33806 )
       integer*4   GL_FRAGMENT_LIGHT3_SGIX
       parameter ( GL_FRAGMENT_LIGHT3_SGIX = 33807 )
       integer*4   GL_FRAGMENT_LIGHT4_SGIX
       parameter ( GL_FRAGMENT_LIGHT4_SGIX = 33808 )
       integer*4   GL_FRAGMENT_LIGHT5_SGIX
       parameter ( GL_FRAGMENT_LIGHT5_SGIX = 33809 )
       integer*4   GL_FRAGMENT_LIGHT6_SGIX
       parameter ( GL_FRAGMENT_LIGHT6_SGIX = 33810 )
       integer*4   GL_FRAGMENT_LIGHT7_SGIX
       parameter ( GL_FRAGMENT_LIGHT7_SGIX = 33811 )

C  SGIX_resample 
       integer*4   GL_PACK_RESAMPLE_SGIX
       parameter ( GL_PACK_RESAMPLE_SGIX = 33836 )
       integer*4   GL_UNPACK_RESAMPLE_SGIX
       parameter ( GL_UNPACK_RESAMPLE_SGIX = 33837 )
       integer*4   GL_RESAMPLE_REPLICATE_SGIX
       parameter ( GL_RESAMPLE_REPLICATE_SGIX = 33838 )
       integer*4   GL_RESAMPLE_ZERO_FILL_SGIX
       parameter ( GL_RESAMPLE_ZERO_FILL_SGIX = 33839 )
       integer*4   GL_RESAMPLE_DECIMATE_SGIX
       parameter ( GL_RESAMPLE_DECIMATE_SGIX = 33840 )

C  SGIX_icc_texture 
       integer*4   GL_RGB_ICC_SGIX
       parameter ( GL_RGB_ICC_SGIX = 33888 )
       integer*4   GL_RGBA_ICC_SGIX
       parameter ( GL_RGBA_ICC_SGIX = 33889 )
       integer*4   GL_ALPHA_ICC_SGIX
       parameter ( GL_ALPHA_ICC_SGIX = 33890 )
       integer*4   GL_LUMINANCE_ICC_SGIX
       parameter ( GL_LUMINANCE_ICC_SGIX = 33891 )
       integer*4   GL_INTENSITY_ICC_SGIX
       parameter ( GL_INTENSITY_ICC_SGIX = 33892 )
       integer*4   GL_LUMINANCE_ALPHA_ICC_SGIX
       parameter ( GL_LUMINANCE_ALPHA_ICC_SGIX = 33893 )
       integer*4   GL_R5_G6_B5_ICC_SGIX
       parameter ( GL_R5_G6_B5_ICC_SGIX = 33894 )
       integer*4   GL_R5_G6_B5_A8_ICC_SGIX
       parameter ( GL_R5_G6_B5_A8_ICC_SGIX = 33895 )
       integer*4   GL_ALPHA16_ICC_SGIX
       parameter ( GL_ALPHA16_ICC_SGIX = 33896 )
       integer*4   GL_LUMINANCE16_ICC_SGIX
       parameter ( GL_LUMINANCE16_ICC_SGIX = 33897 )
       integer*4   GL_INTENSITY16_ICC_SGIX
       parameter ( GL_INTENSITY16_ICC_SGIX = 33898 )
       integer*4   GL_LUMINANCE16_ALPHA8_ICC_SGIX
       parameter ( GL_LUMINANCE16_ALPHA8_ICC_SGIX = 33899 )

C  SGIX_subsample 
       integer*4   GL_PACK_SUBSAMPLE_RATE_SGIX
       parameter ( GL_PACK_SUBSAMPLE_RATE_SGIX = 34208 )
       integer*4   GL_UNPACK_SUBSAMPLE_RATE_SGIX
       parameter ( GL_UNPACK_SUBSAMPLE_RATE_SGIX = 34209 )
       integer*4   GL_PIXEL_SUBSAMPLE_4444_SGIX
       parameter ( GL_PIXEL_SUBSAMPLE_4444_SGIX = 34210 )
       integer*4   GL_PIXEL_SUBSAMPLE_2424_SGIX
       parameter ( GL_PIXEL_SUBSAMPLE_2424_SGIX = 34211 )
       integer*4   GL_PIXEL_SUBSAMPLE_4242_SGIX
       parameter ( GL_PIXEL_SUBSAMPLE_4242_SGIX = 34212 )

C  ARB_multitexture 
       integer*4   GL_TEXTURE0_ARB
       parameter ( GL_TEXTURE0_ARB = 33984 )
       integer*4   GL_TEXTURE1_ARB
       parameter ( GL_TEXTURE1_ARB = 33985 )
       integer*4   GL_TEXTURE2_ARB
       parameter ( GL_TEXTURE2_ARB = 33986 )
       integer*4   GL_TEXTURE3_ARB
       parameter ( GL_TEXTURE3_ARB = 33987 )
       integer*4   GL_TEXTURE4_ARB
       parameter ( GL_TEXTURE4_ARB = 33988 )
       integer*4   GL_TEXTURE5_ARB
       parameter ( GL_TEXTURE5_ARB = 33989 )
       integer*4   GL_TEXTURE6_ARB
       parameter ( GL_TEXTURE6_ARB = 33990 )
       integer*4   GL_TEXTURE7_ARB
       parameter ( GL_TEXTURE7_ARB = 33991 )
       integer*4   GL_TEXTURE8_ARB
       parameter ( GL_TEXTURE8_ARB = 33992 )
       integer*4   GL_TEXTURE9_ARB
       parameter ( GL_TEXTURE9_ARB = 33993 )
       integer*4   GL_TEXTURE10_ARB
       parameter ( GL_TEXTURE10_ARB = 33994 )
       integer*4   GL_TEXTURE11_ARB
       parameter ( GL_TEXTURE11_ARB = 33995 )
       integer*4   GL_TEXTURE12_ARB
       parameter ( GL_TEXTURE12_ARB = 33996 )
       integer*4   GL_TEXTURE13_ARB
       parameter ( GL_TEXTURE13_ARB = 33997 )
       integer*4   GL_TEXTURE14_ARB
       parameter ( GL_TEXTURE14_ARB = 33998 )
       integer*4   GL_TEXTURE15_ARB
       parameter ( GL_TEXTURE15_ARB = 33999 )
       integer*4   GL_TEXTURE16_ARB
       parameter ( GL_TEXTURE16_ARB = 34000 )
       integer*4   GL_TEXTURE17_ARB
       parameter ( GL_TEXTURE17_ARB = 34001 )
       integer*4   GL_TEXTURE18_ARB
       parameter ( GL_TEXTURE18_ARB = 34002 )
       integer*4   GL_TEXTURE19_ARB
       parameter ( GL_TEXTURE19_ARB = 34003 )
       integer*4   GL_TEXTURE20_ARB
       parameter ( GL_TEXTURE20_ARB = 34004 )
       integer*4   GL_TEXTURE21_ARB
       parameter ( GL_TEXTURE21_ARB = 34005 )
       integer*4   GL_TEXTURE22_ARB
       parameter ( GL_TEXTURE22_ARB = 34006 )
       integer*4   GL_TEXTURE23_ARB
       parameter ( GL_TEXTURE23_ARB = 34007 )
       integer*4   GL_TEXTURE24_ARB
       parameter ( GL_TEXTURE24_ARB = 34008 )
       integer*4   GL_TEXTURE25_ARB
       parameter ( GL_TEXTURE25_ARB = 34009 )
       integer*4   GL_TEXTURE26_ARB
       parameter ( GL_TEXTURE26_ARB = 34010 )
       integer*4   GL_TEXTURE27_ARB
       parameter ( GL_TEXTURE27_ARB = 34011 )
       integer*4   GL_TEXTURE28_ARB
       parameter ( GL_TEXTURE28_ARB = 34012 )
       integer*4   GL_TEXTURE29_ARB
       parameter ( GL_TEXTURE29_ARB = 34013 )
       integer*4   GL_TEXTURE30_ARB
       parameter ( GL_TEXTURE30_ARB = 34014 )
       integer*4   GL_TEXTURE31_ARB
       parameter ( GL_TEXTURE31_ARB = 34015 )
       integer*4   GL_ACTIVE_TEXTURE_ARB
       parameter ( GL_ACTIVE_TEXTURE_ARB = 34016 )
       integer*4   GL_CLIENT_ACTIVE_TEXTURE_ARB
       parameter ( GL_CLIENT_ACTIVE_TEXTURE_ARB = 34017 )
       integer*4   GL_MAX_TEXTURE_UNITS_ARB
       parameter ( GL_MAX_TEXTURE_UNITS_ARB = 34018 )

C  ARB_transpose_matrix 
       integer*4   GL_TRANSPOSE_MODELVIEW_MATRIX_ARB
       parameter ( GL_TRANSPOSE_MODELVIEW_MATRIX_ARB = 34019 )
       integer*4   GL_TRANSPOSE_PROJECTION_MATRIX_ARB
       parameter ( GL_TRANSPOSE_PROJECTION_MATRIX_ARB = 34020 )
       integer*4   GL_TRANSPOSE_TEXTURE_MATRIX_ARB
       parameter ( GL_TRANSPOSE_TEXTURE_MATRIX_ARB = 34021 )
       integer*4   GL_TRANSPOSE_COLOR_MATRIX_ARB
       parameter ( GL_TRANSPOSE_COLOR_MATRIX_ARB = 34022 )

C  ARB_multisample 
       integer*4   GL_MULTISAMPLE_ARB
       parameter ( GL_MULTISAMPLE_ARB = 32925 )
       integer*4   GL_SAMPLE_ALPHA_TO_COVERAGE_ARB
       parameter ( GL_SAMPLE_ALPHA_TO_COVERAGE_ARB = 32926 )
       integer*4   GL_SAMPLE_ALPHA_TO_ONE_ARB
       parameter ( GL_SAMPLE_ALPHA_TO_ONE_ARB = 32927 )
       integer*4   GL_SAMPLE_COVERAGE_ARB
       parameter ( GL_SAMPLE_COVERAGE_ARB = 32928 )
       integer*4   GL_SAMPLE_BUFFERS_ARB
       parameter ( GL_SAMPLE_BUFFERS_ARB = 32936 )
       integer*4   GL_SAMPLES_ARB
       parameter ( GL_SAMPLES_ARB = 32937 )
       integer*4   GL_SAMPLE_COVERAGE_VALUE_ARB
       parameter ( GL_SAMPLE_COVERAGE_VALUE_ARB = 32938 )
       integer*4   GL_SAMPLE_COVERAGE_INVERT_ARB
       parameter ( GL_SAMPLE_COVERAGE_INVERT_ARB = 32939 )
       integer*4   GL_MULTISAMPLE_BIT_ARB
       parameter ( GL_MULTISAMPLE_BIT_ARB = 536870912 )

C  ARB_texture_env_add 

C  ARB_texture_cube_map 
       integer*4   GL_NORMAL_MAP_ARB
       parameter ( GL_NORMAL_MAP_ARB = 34065 )
       integer*4   GL_REFLECTION_MAP_ARB
       parameter ( GL_REFLECTION_MAP_ARB = 34066 )
       integer*4   GL_TEXTURE_CUBE_MAP_ARB
       parameter ( GL_TEXTURE_CUBE_MAP_ARB = 34067 )
       integer*4   GL_TEXTURE_BINDING_CUBE_MAP_ARB
       parameter ( GL_TEXTURE_BINDING_CUBE_MAP_ARB = 34068 )
       integer*4   GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB
       parameter ( GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB = 34069 )
       integer*4   GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB
       parameter ( GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB = 34070 )
       integer*4   GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB
       parameter ( GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB = 34071 )
       integer*4   GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB
       parameter ( GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB = 34072 )
       integer*4   GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB
       parameter ( GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB = 34073 )
       integer*4   GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB
       parameter ( GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB = 34074 )
       integer*4   GL_PROXY_TEXTURE_CUBE_MAP_ARB
       parameter ( GL_PROXY_TEXTURE_CUBE_MAP_ARB = 34075 )
       integer*4   GL_MAX_CUBE_MAP_TEXTURE_SIZE_ARB
       parameter ( GL_MAX_CUBE_MAP_TEXTURE_SIZE_ARB = 34076 )

C  ARB_texture_compression 
       integer*4   GL_COMPRESSED_ALPHA_ARB
       parameter ( GL_COMPRESSED_ALPHA_ARB = 34025 )
       integer*4   GL_COMPRESSED_LUMINANCE_ARB
       parameter ( GL_COMPRESSED_LUMINANCE_ARB = 34026 )
       integer*4   GL_COMPRESSED_LUMINANCE_ALPHA_ARB
       parameter ( GL_COMPRESSED_LUMINANCE_ALPHA_ARB = 34027 )
       integer*4   GL_COMPRESSED_INTENSITY_ARB
       parameter ( GL_COMPRESSED_INTENSITY_ARB = 34028 )
       integer*4   GL_COMPRESSED_RGB_ARB
       parameter ( GL_COMPRESSED_RGB_ARB = 34029 )
       integer*4   GL_COMPRESSED_RGBA_ARB
       parameter ( GL_COMPRESSED_RGBA_ARB = 34030 )
       integer*4   GL_TEXTURE_COMPRESSION_HINT_ARB
       parameter ( GL_TEXTURE_COMPRESSION_HINT_ARB = 34031 )
       integer*4   GL_TEXTURE_COMPRESSED_IMAGE_SIZE_ARB
       parameter ( GL_TEXTURE_COMPRESSED_IMAGE_SIZE_ARB = 34464 )
       integer*4   GL_TEXTURE_COMPRESSED_ARB
       parameter ( GL_TEXTURE_COMPRESSED_ARB = 34465 )
       integer*4   GL_NUM_COMPRESSED_TEXTURE_FORMATS_ARB
       parameter ( GL_NUM_COMPRESSED_TEXTURE_FORMATS_ARB = 34466 )
       integer*4   GL_COMPRESSED_TEXTURE_FORMATS_ARB
       parameter ( GL_COMPRESSED_TEXTURE_FORMATS_ARB = 34467 )

C  ARB_texture_border_clamp 
       integer*4   GL_CLAMP_TO_BORDER_ARB
       parameter ( GL_CLAMP_TO_BORDER_ARB = 33069 )

C  ARB_point_parameters 
       integer*4   GL_POINT_SIZE_MIN_ARB
       parameter ( GL_POINT_SIZE_MIN_ARB = 33062 )
       integer*4   GL_POINT_SIZE_MAX_ARB
       parameter ( GL_POINT_SIZE_MAX_ARB = 33063 )
       integer*4   GL_POINT_FADE_THRESHOLD_SIZE_ARB
       parameter ( GL_POINT_FADE_THRESHOLD_SIZE_ARB = 33064 )
       integer*4   GL_POINT_DISTANCE_ATTENUATION_ARB
       parameter ( GL_POINT_DISTANCE_ATTENUATION_ARB = 33065 )

C  ARB_vertex_blend 
       integer*4   GL_MAX_VERTEX_UNITS_ARB
       parameter ( GL_MAX_VERTEX_UNITS_ARB = 34468 )
       integer*4   GL_ACTIVE_VERTEX_UNITS_ARB
       parameter ( GL_ACTIVE_VERTEX_UNITS_ARB = 34469 )
       integer*4   GL_WEIGHT_SUM_UNITY_ARB
       parameter ( GL_WEIGHT_SUM_UNITY_ARB = 34470 )
       integer*4   GL_VERTEX_BLEND_ARB
       parameter ( GL_VERTEX_BLEND_ARB = 34471 )
       integer*4   GL_CURRENT_WEIGHT_ARB
       parameter ( GL_CURRENT_WEIGHT_ARB = 34472 )
       integer*4   GL_WEIGHT_ARRAY_TYPE_ARB
       parameter ( GL_WEIGHT_ARRAY_TYPE_ARB = 34473 )
       integer*4   GL_WEIGHT_ARRAY_STRIDE_ARB
       parameter ( GL_WEIGHT_ARRAY_STRIDE_ARB = 34474 )
       integer*4   GL_WEIGHT_ARRAY_SIZE_ARB
       parameter ( GL_WEIGHT_ARRAY_SIZE_ARB = 34475 )
       integer*4   GL_WEIGHT_ARRAY_POINTER_ARB
       parameter ( GL_WEIGHT_ARRAY_POINTER_ARB = 34476 )
       integer*4   GL_WEIGHT_ARRAY_ARB
       parameter ( GL_WEIGHT_ARRAY_ARB = 34477 )
       integer*4   GL_MODELVIEW0_ARB
       parameter ( GL_MODELVIEW0_ARB = 5888 )
       integer*4   GL_MODELVIEW1_ARB
       parameter ( GL_MODELVIEW1_ARB = 34058 )
       integer*4   GL_MODELVIEW2_ARB
       parameter ( GL_MODELVIEW2_ARB = 34594 )
       integer*4   GL_MODELVIEW3_ARB
       parameter ( GL_MODELVIEW3_ARB = 34595 )
       integer*4   GL_MODELVIEW4_ARB
       parameter ( GL_MODELVIEW4_ARB = 34596 )
       integer*4   GL_MODELVIEW5_ARB
       parameter ( GL_MODELVIEW5_ARB = 34597 )
       integer*4   GL_MODELVIEW6_ARB
       parameter ( GL_MODELVIEW6_ARB = 34598 )
       integer*4   GL_MODELVIEW7_ARB
       parameter ( GL_MODELVIEW7_ARB = 34599 )
       integer*4   GL_MODELVIEW8_ARB
       parameter ( GL_MODELVIEW8_ARB = 34600 )
       integer*4   GL_MODELVIEW9_ARB
       parameter ( GL_MODELVIEW9_ARB = 34601 )
       integer*4   GL_MODELVIEW10_ARB
       parameter ( GL_MODELVIEW10_ARB = 34602 )
       integer*4   GL_MODELVIEW11_ARB
       parameter ( GL_MODELVIEW11_ARB = 34603 )
       integer*4   GL_MODELVIEW12_ARB
       parameter ( GL_MODELVIEW12_ARB = 34604 )
       integer*4   GL_MODELVIEW13_ARB
       parameter ( GL_MODELVIEW13_ARB = 34605 )
       integer*4   GL_MODELVIEW14_ARB
       parameter ( GL_MODELVIEW14_ARB = 34606 )
       integer*4   GL_MODELVIEW15_ARB
       parameter ( GL_MODELVIEW15_ARB = 34607 )
       integer*4   GL_MODELVIEW16_ARB
       parameter ( GL_MODELVIEW16_ARB = 34608 )
       integer*4   GL_MODELVIEW17_ARB
       parameter ( GL_MODELVIEW17_ARB = 34609 )
       integer*4   GL_MODELVIEW18_ARB
       parameter ( GL_MODELVIEW18_ARB = 34610 )
       integer*4   GL_MODELVIEW19_ARB
       parameter ( GL_MODELVIEW19_ARB = 34611 )
       integer*4   GL_MODELVIEW20_ARB
       parameter ( GL_MODELVIEW20_ARB = 34612 )
       integer*4   GL_MODELVIEW21_ARB
       parameter ( GL_MODELVIEW21_ARB = 34613 )
       integer*4   GL_MODELVIEW22_ARB
       parameter ( GL_MODELVIEW22_ARB = 34614 )
       integer*4   GL_MODELVIEW23_ARB
       parameter ( GL_MODELVIEW23_ARB = 34615 )
       integer*4   GL_MODELVIEW24_ARB
       parameter ( GL_MODELVIEW24_ARB = 34616 )
       integer*4   GL_MODELVIEW25_ARB
       parameter ( GL_MODELVIEW25_ARB = 34617 )
       integer*4   GL_MODELVIEW26_ARB
       parameter ( GL_MODELVIEW26_ARB = 34618 )
       integer*4   GL_MODELVIEW27_ARB
       parameter ( GL_MODELVIEW27_ARB = 34619 )
       integer*4   GL_MODELVIEW28_ARB
       parameter ( GL_MODELVIEW28_ARB = 34620 )
       integer*4   GL_MODELVIEW29_ARB
       parameter ( GL_MODELVIEW29_ARB = 34621 )
       integer*4   GL_MODELVIEW30_ARB
       parameter ( GL_MODELVIEW30_ARB = 34622 )
       integer*4   GL_MODELVIEW31_ARB
       parameter ( GL_MODELVIEW31_ARB = 34623 )

C  ARB_texture_env_combine 
       integer*4   GL_COMBINE_ARB
       parameter ( GL_COMBINE_ARB = 34160 )
       integer*4   GL_COMBINE_RGB_ARB
       parameter ( GL_COMBINE_RGB_ARB = 34161 )
       integer*4   GL_COMBINE_ALPHA_ARB
       parameter ( GL_COMBINE_ALPHA_ARB = 34162 )
       integer*4   GL_SOURCE0_RGB_ARB
       parameter ( GL_SOURCE0_RGB_ARB = 34176 )
       integer*4   GL_SOURCE1_RGB_ARB
       parameter ( GL_SOURCE1_RGB_ARB = 34177 )
       integer*4   GL_SOURCE2_RGB_ARB
       parameter ( GL_SOURCE2_RGB_ARB = 34178 )
       integer*4   GL_SOURCE0_ALPHA_ARB
       parameter ( GL_SOURCE0_ALPHA_ARB = 34184 )
       integer*4   GL_SOURCE1_ALPHA_ARB
       parameter ( GL_SOURCE1_ALPHA_ARB = 34185 )
       integer*4   GL_SOURCE2_ALPHA_ARB
       parameter ( GL_SOURCE2_ALPHA_ARB = 34186 )
       integer*4   GL_OPERAND0_RGB_ARB
       parameter ( GL_OPERAND0_RGB_ARB = 34192 )
       integer*4   GL_OPERAND1_RGB_ARB
       parameter ( GL_OPERAND1_RGB_ARB = 34193 )
       integer*4   GL_OPERAND2_RGB_ARB
       parameter ( GL_OPERAND2_RGB_ARB = 34194 )
       integer*4   GL_OPERAND0_ALPHA_ARB
       parameter ( GL_OPERAND0_ALPHA_ARB = 34200 )
       integer*4   GL_OPERAND1_ALPHA_ARB
       parameter ( GL_OPERAND1_ALPHA_ARB = 34201 )
       integer*4   GL_OPERAND2_ALPHA_ARB
       parameter ( GL_OPERAND2_ALPHA_ARB = 34202 )
       integer*4   GL_RGB_SCALE_ARB
       parameter ( GL_RGB_SCALE_ARB = 34163 )
       integer*4   GL_ADD_SIGNED_ARB
       parameter ( GL_ADD_SIGNED_ARB = 34164 )
       integer*4   GL_INTERPOLATE_ARB
       parameter ( GL_INTERPOLATE_ARB = 34165 )
       integer*4   GL_SUBTRACT_ARB
       parameter ( GL_SUBTRACT_ARB = 34023 )
       integer*4   GL_CONSTANT_ARB
       parameter ( GL_CONSTANT_ARB = 34166 )
       integer*4   GL_PRIMARY_COLOR_ARB
       parameter ( GL_PRIMARY_COLOR_ARB = 34167 )
       integer*4   GL_PREVIOUS_ARB
       parameter ( GL_PREVIOUS_ARB = 34168 )

C  ARB_texture_env_crossbar 

C  ARB_texture_env_dot3 
       integer*4   GL_DOT3_RGB_ARB
       parameter ( GL_DOT3_RGB_ARB = 34478 )
       integer*4   GL_DOT3_RGBA_ARB
       parameter ( GL_DOT3_RGBA_ARB = 34479 )

C  ARB_depth_texture 
       integer*4   GL_DEPTH_COMPONENT16_ARB
       parameter ( GL_DEPTH_COMPONENT16_ARB = 33189 )
       integer*4   GL_DEPTH_COMPONENT24_ARB
       parameter ( GL_DEPTH_COMPONENT24_ARB = 33190 )
       integer*4   GL_DEPTH_COMPONENT32_ARB
       parameter ( GL_DEPTH_COMPONENT32_ARB = 33191 )
       integer*4   GL_TEXTURE_DEPTH_SIZE_ARB
       parameter ( GL_TEXTURE_DEPTH_SIZE_ARB = 34890 )
       integer*4   GL_DEPTH_TEXTURE_MODE_ARB
       parameter ( GL_DEPTH_TEXTURE_MODE_ARB = 34891 )

C  ARB_shadow 
       integer*4   GL_TEXTURE_COMPARE_MODE_ARB
       parameter ( GL_TEXTURE_COMPARE_MODE_ARB = 34892 )
       integer*4   GL_TEXTURE_COMPARE_FUNC_ARB
       parameter ( GL_TEXTURE_COMPARE_FUNC_ARB = 34893 )
       integer*4   GL_COMPARE_R_TO_TEXTURE_ARB
       parameter ( GL_COMPARE_R_TO_TEXTURE_ARB = 34894 )

C  ARB_shadow_ambient 
       integer*4   GL_TEXTURE_COMPARE_FAIL_VALUE_ARB
       parameter ( GL_TEXTURE_COMPARE_FAIL_VALUE_ARB = 32959 )

C  ARB_window_pos 

C  ARB_vertex_program 
       integer*4   GL_COLOR_SUM_ARB
       parameter ( GL_COLOR_SUM_ARB = 33880 )
       integer*4   GL_VERTEX_PROGRAM_ARB
       parameter ( GL_VERTEX_PROGRAM_ARB = 34336 )
       integer*4   GL_VERTEX_ATTRIB_ARRAY_ENABLED_ARB
       parameter ( GL_VERTEX_ATTRIB_ARRAY_ENABLED_ARB = 34338 )
       integer*4   GL_VERTEX_ATTRIB_ARRAY_SIZE_ARB
       parameter ( GL_VERTEX_ATTRIB_ARRAY_SIZE_ARB = 34339 )
       integer*4   GL_VERTEX_ATTRIB_ARRAY_STRIDE_ARB
       parameter ( GL_VERTEX_ATTRIB_ARRAY_STRIDE_ARB = 34340 )
       integer*4   GL_VERTEX_ATTRIB_ARRAY_TYPE_ARB
       parameter ( GL_VERTEX_ATTRIB_ARRAY_TYPE_ARB = 34341 )
       integer*4   GL_CURRENT_VERTEX_ATTRIB_ARB
       parameter ( GL_CURRENT_VERTEX_ATTRIB_ARB = 34342 )
       integer*4   GL_PROGRAM_LENGTH_ARB
       parameter ( GL_PROGRAM_LENGTH_ARB = 34343 )
       integer*4   GL_PROGRAM_STRING_ARB
       parameter ( GL_PROGRAM_STRING_ARB = 34344 )
       integer*4   GL_MAX_PROGRAM_MATRIX_STACK_DEPTH_ARB
       parameter ( GL_MAX_PROGRAM_MATRIX_STACK_DEPTH_ARB = 34350 )
       integer*4   GL_MAX_PROGRAM_MATRICES_ARB
       parameter ( GL_MAX_PROGRAM_MATRICES_ARB = 34351 )
       integer*4   GL_CURRENT_MATRIX_STACK_DEPTH_ARB
       parameter ( GL_CURRENT_MATRIX_STACK_DEPTH_ARB = 34368 )
       integer*4   GL_CURRENT_MATRIX_ARB
       parameter ( GL_CURRENT_MATRIX_ARB = 34369 )
       integer*4   GL_VERTEX_PROGRAM_POINT_SIZE_ARB
       parameter ( GL_VERTEX_PROGRAM_POINT_SIZE_ARB = 34370 )
       integer*4   GL_VERTEX_PROGRAM_TWO_SIDE_ARB
       parameter ( GL_VERTEX_PROGRAM_TWO_SIDE_ARB = 34371 )
       integer*4   GL_VERTEX_ATTRIB_ARRAY_POINTER_ARB
       parameter ( GL_VERTEX_ATTRIB_ARRAY_POINTER_ARB = 34373 )
       integer*4   GL_PROGRAM_ERROR_POSITION_ARB
       parameter ( GL_PROGRAM_ERROR_POSITION_ARB = 34379 )
       integer*4   GL_PROGRAM_BINDING_ARB
       parameter ( GL_PROGRAM_BINDING_ARB = 34423 )
       integer*4   GL_MAX_VERTEX_ATTRIBS_ARB
       parameter ( GL_MAX_VERTEX_ATTRIBS_ARB = 34921 )
       integer*4   GL_VERTEX_ATTRIB_ARRAY_NORMALIZED_ARB
       parameter ( GL_VERTEX_ATTRIB_ARRAY_NORMALIZED_ARB = 34922 )
       integer*4   GL_PROGRAM_ERROR_STRING_ARB
       parameter ( GL_PROGRAM_ERROR_STRING_ARB = 34932 )
       integer*4   GL_PROGRAM_FORMAT_ASCII_ARB
       parameter ( GL_PROGRAM_FORMAT_ASCII_ARB = 34933 )
       integer*4   GL_PROGRAM_FORMAT_ARB
       parameter ( GL_PROGRAM_FORMAT_ARB = 34934 )
       integer*4   GL_PROGRAM_INSTRUCTIONS_ARB
       parameter ( GL_PROGRAM_INSTRUCTIONS_ARB = 34976 )
       integer*4   GL_MAX_PROGRAM_INSTRUCTIONS_ARB
       parameter ( GL_MAX_PROGRAM_INSTRUCTIONS_ARB = 34977 )
       integer*4   GL_PROGRAM_NATIVE_INSTRUCTIONS_ARB
       parameter ( GL_PROGRAM_NATIVE_INSTRUCTIONS_ARB = 34978 )
       integer*4   GL_MAX_PROGRAM_NATIVE_INSTRUCTIONS_ARB
       parameter ( GL_MAX_PROGRAM_NATIVE_INSTRUCTIONS_ARB = 34979 )
       integer*4   GL_PROGRAM_TEMPORARIES_ARB
       parameter ( GL_PROGRAM_TEMPORARIES_ARB = 34980 )
       integer*4   GL_MAX_PROGRAM_TEMPORARIES_ARB
       parameter ( GL_MAX_PROGRAM_TEMPORARIES_ARB = 34981 )
       integer*4   GL_PROGRAM_NATIVE_TEMPORARIES_ARB
       parameter ( GL_PROGRAM_NATIVE_TEMPORARIES_ARB = 34982 )
       integer*4   GL_MAX_PROGRAM_NATIVE_TEMPORARIES_ARB
       parameter ( GL_MAX_PROGRAM_NATIVE_TEMPORARIES_ARB = 34983 )
       integer*4   GL_PROGRAM_PARAMETERS_ARB
       parameter ( GL_PROGRAM_PARAMETERS_ARB = 34984 )
       integer*4   GL_MAX_PROGRAM_PARAMETERS_ARB
       parameter ( GL_MAX_PROGRAM_PARAMETERS_ARB = 34985 )
       integer*4   GL_PROGRAM_NATIVE_PARAMETERS_ARB
       parameter ( GL_PROGRAM_NATIVE_PARAMETERS_ARB = 34986 )
       integer*4   GL_MAX_PROGRAM_NATIVE_PARAMETERS_ARB
       parameter ( GL_MAX_PROGRAM_NATIVE_PARAMETERS_ARB = 34987 )
       integer*4   GL_PROGRAM_ATTRIBS_ARB
       parameter ( GL_PROGRAM_ATTRIBS_ARB = 34988 )
       integer*4   GL_MAX_PROGRAM_ATTRIBS_ARB
       parameter ( GL_MAX_PROGRAM_ATTRIBS_ARB = 34989 )
       integer*4   GL_PROGRAM_NATIVE_ATTRIBS_ARB
       parameter ( GL_PROGRAM_NATIVE_ATTRIBS_ARB = 34990 )
       integer*4   GL_MAX_PROGRAM_NATIVE_ATTRIBS_ARB
       parameter ( GL_MAX_PROGRAM_NATIVE_ATTRIBS_ARB = 34991 )
       integer*4   GL_PROGRAM_ADDRESS_REGISTERS_ARB
       parameter ( GL_PROGRAM_ADDRESS_REGISTERS_ARB = 34992 )
       integer*4   GL_MAX_PROGRAM_ADDRESS_REGISTERS_ARB
       parameter ( GL_MAX_PROGRAM_ADDRESS_REGISTERS_ARB = 34993 )
       integer*4   GL_PROGRAM_NATIVE_ADDRESS_REGISTERS_ARB
       parameter ( GL_PROGRAM_NATIVE_ADDRESS_REGISTERS_ARB = 34994 )
       integer*4   GL_MAX_PROGRAM_NATIVE_ADDRESS_REGISTERS_ARB
       parameter (
     +  GL_MAX_PROGRAM_NATIVE_ADDRESS_REGISTERS_ARB = 34995 )
       integer*4   GL_MAX_PROGRAM_LOCAL_PARAMETERS_ARB
       parameter ( GL_MAX_PROGRAM_LOCAL_PARAMETERS_ARB = 34996 )
       integer*4   GL_MAX_PROGRAM_ENV_PARAMETERS_ARB
       parameter ( GL_MAX_PROGRAM_ENV_PARAMETERS_ARB = 34997 )
       integer*4   GL_PROGRAM_UNDER_NATIVE_LIMITS_ARB
       parameter ( GL_PROGRAM_UNDER_NATIVE_LIMITS_ARB = 34998 )
       integer*4   GL_TRANSPOSE_CURRENT_MATRIX_ARB
       parameter ( GL_TRANSPOSE_CURRENT_MATRIX_ARB = 34999 )
       integer*4   GL_MATRIX0_ARB
       parameter ( GL_MATRIX0_ARB = 35008 )
       integer*4   GL_MATRIX1_ARB
       parameter ( GL_MATRIX1_ARB = 35009 )
       integer*4   GL_MATRIX2_ARB
       parameter ( GL_MATRIX2_ARB = 35010 )
       integer*4   GL_MATRIX3_ARB
       parameter ( GL_MATRIX3_ARB = 35011 )
       integer*4   GL_MATRIX4_ARB
       parameter ( GL_MATRIX4_ARB = 35012 )
       integer*4   GL_MATRIX5_ARB
       parameter ( GL_MATRIX5_ARB = 35013 )
       integer*4   GL_MATRIX6_ARB
       parameter ( GL_MATRIX6_ARB = 35014 )
       integer*4   GL_MATRIX7_ARB
       parameter ( GL_MATRIX7_ARB = 35015 )
       integer*4   GL_MATRIX8_ARB
       parameter ( GL_MATRIX8_ARB = 35016 )
       integer*4   GL_MATRIX9_ARB
       parameter ( GL_MATRIX9_ARB = 35017 )
       integer*4   GL_MATRIX10_ARB
       parameter ( GL_MATRIX10_ARB = 35018 )
       integer*4   GL_MATRIX11_ARB
       parameter ( GL_MATRIX11_ARB = 35019 )
       integer*4   GL_MATRIX12_ARB
       parameter ( GL_MATRIX12_ARB = 35020 )
       integer*4   GL_MATRIX13_ARB
       parameter ( GL_MATRIX13_ARB = 35021 )
       integer*4   GL_MATRIX14_ARB
       parameter ( GL_MATRIX14_ARB = 35022 )
       integer*4   GL_MATRIX15_ARB
       parameter ( GL_MATRIX15_ARB = 35023 )
       integer*4   GL_MATRIX16_ARB
       parameter ( GL_MATRIX16_ARB = 35024 )
       integer*4   GL_MATRIX17_ARB
       parameter ( GL_MATRIX17_ARB = 35025 )
       integer*4   GL_MATRIX18_ARB
       parameter ( GL_MATRIX18_ARB = 35026 )
       integer*4   GL_MATRIX19_ARB
       parameter ( GL_MATRIX19_ARB = 35027 )
       integer*4   GL_MATRIX20_ARB
       parameter ( GL_MATRIX20_ARB = 35028 )
       integer*4   GL_MATRIX21_ARB
       parameter ( GL_MATRIX21_ARB = 35029 )
       integer*4   GL_MATRIX22_ARB
       parameter ( GL_MATRIX22_ARB = 35030 )
       integer*4   GL_MATRIX23_ARB
       parameter ( GL_MATRIX23_ARB = 35031 )
       integer*4   GL_MATRIX24_ARB
       parameter ( GL_MATRIX24_ARB = 35032 )
       integer*4   GL_MATRIX25_ARB
       parameter ( GL_MATRIX25_ARB = 35033 )
       integer*4   GL_MATRIX26_ARB
       parameter ( GL_MATRIX26_ARB = 35034 )
       integer*4   GL_MATRIX27_ARB
       parameter ( GL_MATRIX27_ARB = 35035 )
       integer*4   GL_MATRIX28_ARB
       parameter ( GL_MATRIX28_ARB = 35036 )
       integer*4   GL_MATRIX29_ARB
       parameter ( GL_MATRIX29_ARB = 35037 )
       integer*4   GL_MATRIX30_ARB
       parameter ( GL_MATRIX30_ARB = 35038 )
       integer*4   GL_MATRIX31_ARB
       parameter ( GL_MATRIX31_ARB = 35039 )

C  ARB_fragment_program 
       integer*4   GL_FRAGMENT_PROGRAM_ARB
       parameter ( GL_FRAGMENT_PROGRAM_ARB = 34820 )
       integer*4   GL_PROGRAM_ALU_INSTRUCTIONS_ARB
       parameter ( GL_PROGRAM_ALU_INSTRUCTIONS_ARB = 34821 )
       integer*4   GL_PROGRAM_TEX_INSTRUCTIONS_ARB
       parameter ( GL_PROGRAM_TEX_INSTRUCTIONS_ARB = 34822 )
       integer*4   GL_PROGRAM_TEX_INDIRECTIONS_ARB
       parameter ( GL_PROGRAM_TEX_INDIRECTIONS_ARB = 34823 )
       integer*4   GL_PROGRAM_NATIVE_ALU_INSTRUCTIONS_ARB
       parameter ( GL_PROGRAM_NATIVE_ALU_INSTRUCTIONS_ARB = 34824 )
       integer*4   GL_PROGRAM_NATIVE_TEX_INSTRUCTIONS_ARB
       parameter ( GL_PROGRAM_NATIVE_TEX_INSTRUCTIONS_ARB = 34825 )
       integer*4   GL_PROGRAM_NATIVE_TEX_INDIRECTIONS_ARB
       parameter ( GL_PROGRAM_NATIVE_TEX_INDIRECTIONS_ARB = 34826 )
       integer*4   GL_MAX_PROGRAM_ALU_INSTRUCTIONS_ARB
       parameter ( GL_MAX_PROGRAM_ALU_INSTRUCTIONS_ARB = 34827 )
       integer*4   GL_MAX_PROGRAM_TEX_INSTRUCTIONS_ARB
       parameter ( GL_MAX_PROGRAM_TEX_INSTRUCTIONS_ARB = 34828 )
       integer*4   GL_MAX_PROGRAM_TEX_INDIRECTIONS_ARB
       parameter ( GL_MAX_PROGRAM_TEX_INDIRECTIONS_ARB = 34829 )
       integer*4   GL_MAX_PROGRAM_NATIVE_ALU_INSTRUCTIONS_ARB
       parameter (
     +  GL_MAX_PROGRAM_NATIVE_ALU_INSTRUCTIONS_ARB = 34830 )
       integer*4   GL_MAX_PROGRAM_NATIVE_TEX_INSTRUCTIONS_ARB
       parameter (
     +  GL_MAX_PROGRAM_NATIVE_TEX_INSTRUCTIONS_ARB = 34831 )
       integer*4   GL_MAX_PROGRAM_NATIVE_TEX_INDIRECTIONS_ARB
       parameter (
     +  GL_MAX_PROGRAM_NATIVE_TEX_INDIRECTIONS_ARB = 34832 )
       integer*4   GL_MAX_TEXTURE_COORDS_ARB
       parameter ( GL_MAX_TEXTURE_COORDS_ARB = 34929 )
       integer*4   GL_MAX_TEXTURE_IMAGE_UNITS_ARB
       parameter ( GL_MAX_TEXTURE_IMAGE_UNITS_ARB = 34930 )

C  EXT_texture_cube_map 
       integer*4   GL_NORMAL_MAP_EXT
       parameter ( GL_NORMAL_MAP_EXT = 34065 )
       integer*4   GL_REFLECTION_MAP_EXT
       parameter ( GL_REFLECTION_MAP_EXT = 34066 )
       integer*4   GL_TEXTURE_CUBE_MAP_EXT
       parameter ( GL_TEXTURE_CUBE_MAP_EXT = 34067 )
       integer*4   GL_TEXTURE_BINDING_CUBE_MAP_EXT
       parameter ( GL_TEXTURE_BINDING_CUBE_MAP_EXT = 34068 )
       integer*4   GL_TEXTURE_CUBE_MAP_POSITIVE_X_EXT
       parameter ( GL_TEXTURE_CUBE_MAP_POSITIVE_X_EXT = 34069 )
       integer*4   GL_TEXTURE_CUBE_MAP_NEGATIVE_X_EXT
       parameter ( GL_TEXTURE_CUBE_MAP_NEGATIVE_X_EXT = 34070 )
       integer*4   GL_TEXTURE_CUBE_MAP_POSITIVE_Y_EXT
       parameter ( GL_TEXTURE_CUBE_MAP_POSITIVE_Y_EXT = 34071 )
       integer*4   GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_EXT
       parameter ( GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_EXT = 34072 )
       integer*4   GL_TEXTURE_CUBE_MAP_POSITIVE_Z_EXT
       parameter ( GL_TEXTURE_CUBE_MAP_POSITIVE_Z_EXT = 34073 )
       integer*4   GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_EXT
       parameter ( GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_EXT = 34074 )
       integer*4   GL_PROXY_TEXTURE_CUBE_MAP_EXT
       parameter ( GL_PROXY_TEXTURE_CUBE_MAP_EXT = 34075 )
       integer*4   GL_MAX_CUBE_MAP_TEXTURE_SIZE_EXT
       parameter ( GL_MAX_CUBE_MAP_TEXTURE_SIZE_EXT = 34076 )

C  EXT_texture_edge_clamp 
       integer*4   GL_CLAMP_TO_EDGE_EXT
       parameter ( GL_CLAMP_TO_EDGE_EXT = 33071 )

C  EXT_clip_volume_hint 
       integer*4   GL_CLIP_VOLUME_CLIPPING_HINT_EXT
       parameter ( GL_CLIP_VOLUME_CLIPPING_HINT_EXT = 33008 )

C  EXT_compiled_vertex_array 
       integer*4   GL_ARRAY_ELEMENT_LOCK_FIRST_EXT
       parameter ( GL_ARRAY_ELEMENT_LOCK_FIRST_EXT = 33192 )
       integer*4   GL_ARRAY_ELEMENT_LOCK_COUNT_EXT
       parameter ( GL_ARRAY_ELEMENT_LOCK_COUNT_EXT = 33193 )

C  EXT_draw_range_elements 
       integer*4   GL_MAX_ELEMENTS_VERTICES_EXT
       parameter ( GL_MAX_ELEMENTS_VERTICES_EXT = 33000 )
       integer*4   GL_MAX_ELEMENTS_INDICES_EXT
       parameter ( GL_MAX_ELEMENTS_INDICES_EXT = 33001 )

C  EXT_bgra 
       integer*4   GL_BGR_EXT
       parameter ( GL_BGR_EXT = 32992 )
       integer*4   GL_BGRA_EXT
       parameter ( GL_BGRA_EXT = 32993 )

C  HP_occlusion_test 
       integer*4   GL_OCCLUSION_TEST_HP
       parameter ( GL_OCCLUSION_TEST_HP = 33125 )
       integer*4   GL_OCCLUSION_TEST_RESULT_HP
       parameter ( GL_OCCLUSION_TEST_RESULT_HP = 33126 )

C  EXT_separate_specular_color 
       integer*4   GL_LIGHT_MODEL_COLOR_CONTROL_EXT
       parameter ( GL_LIGHT_MODEL_COLOR_CONTROL_EXT = 33272 )
       integer*4   GL_SINGLE_COLOR_EXT
       parameter ( GL_SINGLE_COLOR_EXT = 33273 )
       integer*4   GL_SEPARATE_SPECULAR_COLOR_EXT
       parameter ( GL_SEPARATE_SPECULAR_COLOR_EXT = 33274 )

C  EXT_secondary_color 
       integer*4   GL_COLOR_SUM_EXT
       parameter ( GL_COLOR_SUM_EXT = 33880 )
       integer*4   GL_CURRENT_SECONDARY_COLOR_EXT
       parameter ( GL_CURRENT_SECONDARY_COLOR_EXT = 33881 )
       integer*4   GL_SECONDARY_COLOR_ARRAY_SIZE_EXT
       parameter ( GL_SECONDARY_COLOR_ARRAY_SIZE_EXT = 33882 )
       integer*4   GL_SECONDARY_COLOR_ARRAY_TYPE_EXT
       parameter ( GL_SECONDARY_COLOR_ARRAY_TYPE_EXT = 33883 )
       integer*4   GL_SECONDARY_COLOR_ARRAY_STRIDE_EXT
       parameter ( GL_SECONDARY_COLOR_ARRAY_STRIDE_EXT = 33884 )
       integer*4   GL_SECONDARY_COLOR_ARRAY_POINTER_EXT
       parameter ( GL_SECONDARY_COLOR_ARRAY_POINTER_EXT = 33885 )
       integer*4   GL_SECONDARY_COLOR_ARRAY_EXT
       parameter ( GL_SECONDARY_COLOR_ARRAY_EXT = 33886 )

C  EXT_multi_draw_arrays 

C  EXT_fog_coord 
       integer*4   GL_FOG_COORDINATE_SOURCE_EXT
       parameter ( GL_FOG_COORDINATE_SOURCE_EXT = 33872 )
       integer*4   GL_FOG_COORDINATE_EXT
       parameter ( GL_FOG_COORDINATE_EXT = 33873 )
       integer*4   GL_FRAGMENT_DEPTH_EXT
       parameter ( GL_FRAGMENT_DEPTH_EXT = 33874 )
       integer*4   GL_CURRENT_FOG_COORDINATE_EXT
       parameter ( GL_CURRENT_FOG_COORDINATE_EXT = 33875 )
       integer*4   GL_FOG_COORDINATE_ARRAY_TYPE_EXT
       parameter ( GL_FOG_COORDINATE_ARRAY_TYPE_EXT = 33876 )
       integer*4   GL_FOG_COORDINATE_ARRAY_STRIDE_EXT
       parameter ( GL_FOG_COORDINATE_ARRAY_STRIDE_EXT = 33877 )
       integer*4   GL_FOG_COORDINATE_ARRAY_POINTER_EXT
       parameter ( GL_FOG_COORDINATE_ARRAY_POINTER_EXT = 33878 )
       integer*4   GL_FOG_COORDINATE_ARRAY_EXT
       parameter ( GL_FOG_COORDINATE_ARRAY_EXT = 33879 )

C  EXT_texture_env_combine 
       integer*4   GL_COMBINE_EXT
       parameter ( GL_COMBINE_EXT = 34160 )
       integer*4   GL_COMBINE_RGB_EXT
       parameter ( GL_COMBINE_RGB_EXT = 34161 )
       integer*4   GL_COMBINE_ALPHA_EXT
       parameter ( GL_COMBINE_ALPHA_EXT = 34162 )
       integer*4   GL_RGB_SCALE_EXT
       parameter ( GL_RGB_SCALE_EXT = 34163 )
       integer*4   GL_ADD_SIGNED_EXT
       parameter ( GL_ADD_SIGNED_EXT = 34164 )
       integer*4   GL_INTERPOLATE_EXT
       parameter ( GL_INTERPOLATE_EXT = 34165 )
       integer*4   GL_CONSTANT_EXT
       parameter ( GL_CONSTANT_EXT = 34166 )
       integer*4   GL_PRIMARY_COLOR_EXT
       parameter ( GL_PRIMARY_COLOR_EXT = 34167 )
       integer*4   GL_PREVIOUS_EXT
       parameter ( GL_PREVIOUS_EXT = 34168 )
       integer*4   GL_SOURCE0_RGB_EXT
       parameter ( GL_SOURCE0_RGB_EXT = 34176 )
       integer*4   GL_SOURCE1_RGB_EXT
       parameter ( GL_SOURCE1_RGB_EXT = 34177 )
       integer*4   GL_SOURCE2_RGB_EXT
       parameter ( GL_SOURCE2_RGB_EXT = 34178 )
       integer*4   GL_SOURCE0_ALPHA_EXT
       parameter ( GL_SOURCE0_ALPHA_EXT = 34184 )
       integer*4   GL_SOURCE1_ALPHA_EXT
       parameter ( GL_SOURCE1_ALPHA_EXT = 34185 )
       integer*4   GL_SOURCE2_ALPHA_EXT
       parameter ( GL_SOURCE2_ALPHA_EXT = 34186 )
       integer*4   GL_OPERAND0_RGB_EXT
       parameter ( GL_OPERAND0_RGB_EXT = 34192 )
       integer*4   GL_OPERAND1_RGB_EXT
       parameter ( GL_OPERAND1_RGB_EXT = 34193 )
       integer*4   GL_OPERAND2_RGB_EXT
       parameter ( GL_OPERAND2_RGB_EXT = 34194 )
       integer*4   GL_OPERAND0_ALPHA_EXT
       parameter ( GL_OPERAND0_ALPHA_EXT = 34200 )
       integer*4   GL_OPERAND1_ALPHA_EXT
       parameter ( GL_OPERAND1_ALPHA_EXT = 34201 )
       integer*4   GL_OPERAND2_ALPHA_EXT
       parameter ( GL_OPERAND2_ALPHA_EXT = 34202 )

C  EXT_blend_func_separate 
       integer*4   GL_BLEND_DST_RGB_EXT
       parameter ( GL_BLEND_DST_RGB_EXT = 32968 )
       integer*4   GL_BLEND_SRC_RGB_EXT
       parameter ( GL_BLEND_SRC_RGB_EXT = 32969 )
       integer*4   GL_BLEND_DST_ALPHA_EXT
       parameter ( GL_BLEND_DST_ALPHA_EXT = 32970 )
       integer*4   GL_BLEND_SRC_ALPHA_EXT
       parameter ( GL_BLEND_SRC_ALPHA_EXT = 32971 )

C  INGR_interlace_read 
       integer*4   GL_INTERLACE_READ_INGR
       parameter ( GL_INTERLACE_READ_INGR = 34152 )

C  EXT_stencil_wrap 
       integer*4   GL_INCR_WRAP_EXT
       parameter ( GL_INCR_WRAP_EXT = 34055 )
       integer*4   GL_DECR_WRAP_EXT
       parameter ( GL_DECR_WRAP_EXT = 34056 )

C  NV_texgen_reflection 
       integer*4   GL_NORMAL_MAP_NV
       parameter ( GL_NORMAL_MAP_NV = 34065 )
       integer*4   GL_REFLECTION_MAP_NV
       parameter ( GL_REFLECTION_MAP_NV = 34066 )

C  EXT_texgen_reflection 

C  EXT_texture_env_add 

C  EXT_texture_lod_bias 
       integer*4   GL_MAX_TEXTURE_LOD_BIAS_EXT
       parameter ( GL_MAX_TEXTURE_LOD_BIAS_EXT = 34045 )
       integer*4   GL_TEXTURE_FILTER_CONTROL_EXT
       parameter ( GL_TEXTURE_FILTER_CONTROL_EXT = 34048 )
       integer*4   GL_TEXTURE_LOD_BIAS_EXT
       parameter ( GL_TEXTURE_LOD_BIAS_EXT = 34049 )

C  EXT_texture_filter_anisotropic 
       integer*4   GL_TEXTURE_MAX_ANISOTROPY_EXT
       parameter ( GL_TEXTURE_MAX_ANISOTROPY_EXT = 34046 )
       integer*4   GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT
       parameter ( GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT = 34047 )

C  NV_blend_square 

C  EXT_texture_compression_s3tc 
       integer*4   GL_COMPRESSED_RGB_S3TC_DXT1_EXT
       parameter ( GL_COMPRESSED_RGB_S3TC_DXT1_EXT = 33776 )
       integer*4   GL_COMPRESSED_RGBA_S3TC_DXT1_EXT
       parameter ( GL_COMPRESSED_RGBA_S3TC_DXT1_EXT = 33777 )
       integer*4   GL_COMPRESSED_RGBA_S3TC_DXT3_EXT
       parameter ( GL_COMPRESSED_RGBA_S3TC_DXT3_EXT = 33778 )
       integer*4   GL_COMPRESSED_RGBA_S3TC_DXT5_EXT
       parameter ( GL_COMPRESSED_RGBA_S3TC_DXT5_EXT = 33779 )

C  EXT_texture_env_dot3 
       integer*4   GL_DOT3_RGB_EXT
       parameter ( GL_DOT3_RGB_EXT = 34624 )
       integer*4   GL_DOT3_RGBA_EXT
       parameter ( GL_DOT3_RGBA_EXT = 34625 )

C  ATI_texture_mirror_once 
       integer*4   GL_MIRROR_CLAMP_ATI
       parameter ( GL_MIRROR_CLAMP_ATI = 34626 )
       integer*4   GL_MIRROR_CLAMP_TO_EDGE_ATI
       parameter ( GL_MIRROR_CLAMP_TO_EDGE_ATI = 34627 )

C  ATI_envmap_bumpmap 
       integer*4   GL_BUMP_ROT_MATRIX_ATI
       parameter ( GL_BUMP_ROT_MATRIX_ATI = 34677 )
       integer*4   GL_BUMP_ROT_MATRIX_SIZE_ATI
       parameter ( GL_BUMP_ROT_MATRIX_SIZE_ATI = 34678 )
       integer*4   GL_BUMP_NUM_TEX_UNITS_ATI
       parameter ( GL_BUMP_NUM_TEX_UNITS_ATI = 34679 )
       integer*4   GL_BUMP_TEX_UNITS_ATI
       parameter ( GL_BUMP_TEX_UNITS_ATI = 34680 )
       integer*4   GL_DUDV_ATI
       parameter ( GL_DUDV_ATI = 34681 )
       integer*4   GL_DU8DV8_ATI
       parameter ( GL_DU8DV8_ATI = 34682 )
       integer*4   GL_BUMP_ENVMAP_ATI
       parameter ( GL_BUMP_ENVMAP_ATI = 34683 )
       integer*4   GL_BUMP_TARGET_ATI
       parameter ( GL_BUMP_TARGET_ATI = 34684 )

C  ATI_fragment_shader 
       integer*4   GL_FRAGMENT_SHADER_ATI
       parameter ( GL_FRAGMENT_SHADER_ATI = 35104 )
       integer*4   GL_REG_0_ATI
       parameter ( GL_REG_0_ATI = 35105 )
       integer*4   GL_REG_1_ATI
       parameter ( GL_REG_1_ATI = 35106 )
       integer*4   GL_REG_2_ATI
       parameter ( GL_REG_2_ATI = 35107 )
       integer*4   GL_REG_3_ATI
       parameter ( GL_REG_3_ATI = 35108 )
       integer*4   GL_REG_4_ATI
       parameter ( GL_REG_4_ATI = 35109 )
       integer*4   GL_REG_5_ATI
       parameter ( GL_REG_5_ATI = 35110 )
       integer*4   GL_REG_6_ATI
       parameter ( GL_REG_6_ATI = 35111 )
       integer*4   GL_REG_7_ATI
       parameter ( GL_REG_7_ATI = 35112 )
       integer*4   GL_REG_8_ATI
       parameter ( GL_REG_8_ATI = 35113 )
       integer*4   GL_REG_9_ATI
       parameter ( GL_REG_9_ATI = 35114 )
       integer*4   GL_REG_10_ATI
       parameter ( GL_REG_10_ATI = 35115 )
       integer*4   GL_REG_11_ATI
       parameter ( GL_REG_11_ATI = 35116 )
       integer*4   GL_REG_12_ATI
       parameter ( GL_REG_12_ATI = 35117 )
       integer*4   GL_REG_13_ATI
       parameter ( GL_REG_13_ATI = 35118 )
       integer*4   GL_REG_14_ATI
       parameter ( GL_REG_14_ATI = 35119 )
       integer*4   GL_REG_15_ATI
       parameter ( GL_REG_15_ATI = 35120 )
       integer*4   GL_REG_16_ATI
       parameter ( GL_REG_16_ATI = 35121 )
       integer*4   GL_REG_17_ATI
       parameter ( GL_REG_17_ATI = 35122 )
       integer*4   GL_REG_18_ATI
       parameter ( GL_REG_18_ATI = 35123 )
       integer*4   GL_REG_19_ATI
       parameter ( GL_REG_19_ATI = 35124 )
       integer*4   GL_REG_20_ATI
       parameter ( GL_REG_20_ATI = 35125 )
       integer*4   GL_REG_21_ATI
       parameter ( GL_REG_21_ATI = 35126 )
       integer*4   GL_REG_22_ATI
       parameter ( GL_REG_22_ATI = 35127 )
       integer*4   GL_REG_23_ATI
       parameter ( GL_REG_23_ATI = 35128 )
       integer*4   GL_REG_24_ATI
       parameter ( GL_REG_24_ATI = 35129 )
       integer*4   GL_REG_25_ATI
       parameter ( GL_REG_25_ATI = 35130 )
       integer*4   GL_REG_26_ATI
       parameter ( GL_REG_26_ATI = 35131 )
       integer*4   GL_REG_27_ATI
       parameter ( GL_REG_27_ATI = 35132 )
       integer*4   GL_REG_28_ATI
       parameter ( GL_REG_28_ATI = 35133 )
       integer*4   GL_REG_29_ATI
       parameter ( GL_REG_29_ATI = 35134 )
       integer*4   GL_REG_30_ATI
       parameter ( GL_REG_30_ATI = 35135 )
       integer*4   GL_REG_31_ATI
       parameter ( GL_REG_31_ATI = 35136 )
       integer*4   GL_CON_0_ATI
       parameter ( GL_CON_0_ATI = 35137 )
       integer*4   GL_CON_1_ATI
       parameter ( GL_CON_1_ATI = 35138 )
       integer*4   GL_CON_2_ATI
       parameter ( GL_CON_2_ATI = 35139 )
       integer*4   GL_CON_3_ATI
       parameter ( GL_CON_3_ATI = 35140 )
       integer*4   GL_CON_4_ATI
       parameter ( GL_CON_4_ATI = 35141 )
       integer*4   GL_CON_5_ATI
       parameter ( GL_CON_5_ATI = 35142 )
       integer*4   GL_CON_6_ATI
       parameter ( GL_CON_6_ATI = 35143 )
       integer*4   GL_CON_7_ATI
       parameter ( GL_CON_7_ATI = 35144 )
       integer*4   GL_CON_8_ATI
       parameter ( GL_CON_8_ATI = 35145 )
       integer*4   GL_CON_9_ATI
       parameter ( GL_CON_9_ATI = 35146 )
       integer*4   GL_CON_10_ATI
       parameter ( GL_CON_10_ATI = 35147 )
       integer*4   GL_CON_11_ATI
       parameter ( GL_CON_11_ATI = 35148 )
       integer*4   GL_CON_12_ATI
       parameter ( GL_CON_12_ATI = 35149 )
       integer*4   GL_CON_13_ATI
       parameter ( GL_CON_13_ATI = 35150 )
       integer*4   GL_CON_14_ATI
       parameter ( GL_CON_14_ATI = 35151 )
       integer*4   GL_CON_15_ATI
       parameter ( GL_CON_15_ATI = 35152 )
       integer*4   GL_CON_16_ATI
       parameter ( GL_CON_16_ATI = 35153 )
       integer*4   GL_CON_17_ATI
       parameter ( GL_CON_17_ATI = 35154 )
       integer*4   GL_CON_18_ATI
       parameter ( GL_CON_18_ATI = 35155 )
       integer*4   GL_CON_19_ATI
       parameter ( GL_CON_19_ATI = 35156 )
       integer*4   GL_CON_20_ATI
       parameter ( GL_CON_20_ATI = 35157 )
       integer*4   GL_CON_21_ATI
       parameter ( GL_CON_21_ATI = 35158 )
       integer*4   GL_CON_22_ATI
       parameter ( GL_CON_22_ATI = 35159 )
       integer*4   GL_CON_23_ATI
       parameter ( GL_CON_23_ATI = 35160 )
       integer*4   GL_CON_24_ATI
       parameter ( GL_CON_24_ATI = 35161 )
       integer*4   GL_CON_25_ATI
       parameter ( GL_CON_25_ATI = 35162 )
       integer*4   GL_CON_26_ATI
       parameter ( GL_CON_26_ATI = 35163 )
       integer*4   GL_CON_27_ATI
       parameter ( GL_CON_27_ATI = 35164 )
       integer*4   GL_CON_28_ATI
       parameter ( GL_CON_28_ATI = 35165 )
       integer*4   GL_CON_29_ATI
       parameter ( GL_CON_29_ATI = 35166 )
       integer*4   GL_CON_30_ATI
       parameter ( GL_CON_30_ATI = 35167 )
       integer*4   GL_CON_31_ATI
       parameter ( GL_CON_31_ATI = 35168 )
       integer*4   GL_MOV_ATI
       parameter ( GL_MOV_ATI = 35169 )
       integer*4   GL_ADD_ATI
       parameter ( GL_ADD_ATI = 35171 )
       integer*4   GL_MUL_ATI
       parameter ( GL_MUL_ATI = 35172 )
       integer*4   GL_SUB_ATI
       parameter ( GL_SUB_ATI = 35173 )
       integer*4   GL_DOT3_ATI
       parameter ( GL_DOT3_ATI = 35174 )
       integer*4   GL_DOT4_ATI
       parameter ( GL_DOT4_ATI = 35175 )
       integer*4   GL_MAD_ATI
       parameter ( GL_MAD_ATI = 35176 )
       integer*4   GL_LERP_ATI
       parameter ( GL_LERP_ATI = 35177 )
       integer*4   GL_CND_ATI
       parameter ( GL_CND_ATI = 35178 )
       integer*4   GL_CND0_ATI
       parameter ( GL_CND0_ATI = 35179 )
       integer*4   GL_DOT2_ADD_ATI
       parameter ( GL_DOT2_ADD_ATI = 35180 )
       integer*4   GL_SECONDARY_INTERPOLATOR_ATI
       parameter ( GL_SECONDARY_INTERPOLATOR_ATI = 35181 )
       integer*4   GL_NUM_FRAGMENT_REGISTERS_ATI
       parameter ( GL_NUM_FRAGMENT_REGISTERS_ATI = 35182 )
       integer*4   GL_NUM_FRAGMENT_CONSTANTS_ATI
       parameter ( GL_NUM_FRAGMENT_CONSTANTS_ATI = 35183 )
       integer*4   GL_NUM_PASSES_ATI
       parameter ( GL_NUM_PASSES_ATI = 35184 )
       integer*4   GL_NUM_INSTRUCTIONS_PER_PASS_ATI
       parameter ( GL_NUM_INSTRUCTIONS_PER_PASS_ATI = 35185 )
       integer*4   GL_NUM_INSTRUCTIONS_TOTAL_ATI
       parameter ( GL_NUM_INSTRUCTIONS_TOTAL_ATI = 35186 )
       integer*4   GL_NUM_INPUT_INTERPOLATOR_COMPONENTS_ATI
       parameter ( GL_NUM_INPUT_INTERPOLATOR_COMPONENTS_ATI = 35187 )
       integer*4   GL_NUM_LOOPBACK_COMPONENTS_ATI
       parameter ( GL_NUM_LOOPBACK_COMPONENTS_ATI = 35188 )
       integer*4   GL_COLOR_ALPHA_PAIRING_ATI
       parameter ( GL_COLOR_ALPHA_PAIRING_ATI = 35189 )
       integer*4   GL_SWIZZLE_STR_ATI
       parameter ( GL_SWIZZLE_STR_ATI = 35190 )
       integer*4   GL_SWIZZLE_STQ_ATI
       parameter ( GL_SWIZZLE_STQ_ATI = 35191 )
       integer*4   GL_SWIZZLE_STR_DR_ATI
       parameter ( GL_SWIZZLE_STR_DR_ATI = 35192 )
       integer*4   GL_SWIZZLE_STQ_DQ_ATI
       parameter ( GL_SWIZZLE_STQ_DQ_ATI = 35193 )
       integer*4   GL_SWIZZLE_STRQ_ATI
       parameter ( GL_SWIZZLE_STRQ_ATI = 35194 )
       integer*4   GL_SWIZZLE_STRQ_DQ_ATI
       parameter ( GL_SWIZZLE_STRQ_DQ_ATI = 35195 )
       integer*4   GL_RED_BIT_ATI
       parameter ( GL_RED_BIT_ATI = 1 )
       integer*4   GL_GREEN_BIT_ATI
       parameter ( GL_GREEN_BIT_ATI = 2 )
       integer*4   GL_BLUE_BIT_ATI
       parameter ( GL_BLUE_BIT_ATI = 4 )
       integer*4   GL_2X_BIT_ATI
       parameter ( GL_2X_BIT_ATI = 1 )
       integer*4   GL_4X_BIT_ATI
       parameter ( GL_4X_BIT_ATI = 2 )
       integer*4   GL_8X_BIT_ATI
       parameter ( GL_8X_BIT_ATI = 4 )
       integer*4   GL_HALF_BIT_ATI
       parameter ( GL_HALF_BIT_ATI = 8 )
       integer*4   GL_QUARTER_BIT_ATI
       parameter ( GL_QUARTER_BIT_ATI = 16 )
       integer*4   GL_EIGHTH_BIT_ATI
       parameter ( GL_EIGHTH_BIT_ATI = 32 )
       integer*4   GL_SATURATE_BIT_ATI
       parameter ( GL_SATURATE_BIT_ATI = 64 )
       integer*4   GL_COMP_BIT_ATI
       parameter ( GL_COMP_BIT_ATI = 2 )
       integer*4   GL_NEGATE_BIT_ATI
       parameter ( GL_NEGATE_BIT_ATI = 4 )
       integer*4   GL_BIAS_BIT_ATI
       parameter ( GL_BIAS_BIT_ATI = 8 )

C  ATI_pn_triangles 
       integer*4   GL_PN_TRIANGLES_ATI
       parameter ( GL_PN_TRIANGLES_ATI = 34800 )
       integer*4   GL_MAX_PN_TRIANGLES_TESSELATION_LEVEL_ATI
       parameter ( GL_MAX_PN_TRIANGLES_TESSELATION_LEVEL_ATI = 34801 )
       integer*4   GL_PN_TRIANGLES_POINT_MODE_ATI
       parameter ( GL_PN_TRIANGLES_POINT_MODE_ATI = 34802 )
       integer*4   GL_PN_TRIANGLES_NORMAL_MODE_ATI
       parameter ( GL_PN_TRIANGLES_NORMAL_MODE_ATI = 34803 )
       integer*4   GL_PN_TRIANGLES_TESSELATION_LEVEL_ATI
       parameter ( GL_PN_TRIANGLES_TESSELATION_LEVEL_ATI = 34804 )
       integer*4   GL_PN_TRIANGLES_POINT_MODE_LINEAR_ATI
       parameter ( GL_PN_TRIANGLES_POINT_MODE_LINEAR_ATI = 34805 )
       integer*4   GL_PN_TRIANGLES_POINT_MODE_CUBIC_ATI
       parameter ( GL_PN_TRIANGLES_POINT_MODE_CUBIC_ATI = 34806 )
       integer*4   GL_PN_TRIANGLES_NORMAL_MODE_LINEAR_ATI
       parameter ( GL_PN_TRIANGLES_NORMAL_MODE_LINEAR_ATI = 34807 )
       integer*4   GL_PN_TRIANGLES_NORMAL_MODE_QUADRATIC_ATI
       parameter ( GL_PN_TRIANGLES_NORMAL_MODE_QUADRATIC_ATI = 34808 )

C  ATI_vertex_array_object 
       integer*4   GL_STATIC_ATI
       parameter ( GL_STATIC_ATI = 34656 )
       integer*4   GL_DYNAMIC_ATI
       parameter ( GL_DYNAMIC_ATI = 34657 )
       integer*4   GL_PRESERVE_ATI
       parameter ( GL_PRESERVE_ATI = 34658 )
       integer*4   GL_DISCARD_ATI
       parameter ( GL_DISCARD_ATI = 34659 )
       integer*4   GL_OBJECT_BUFFER_SIZE_ATI
       parameter ( GL_OBJECT_BUFFER_SIZE_ATI = 34660 )
       integer*4   GL_OBJECT_BUFFER_USAGE_ATI
       parameter ( GL_OBJECT_BUFFER_USAGE_ATI = 34661 )
       integer*4   GL_ARRAY_OBJECT_BUFFER_ATI
       parameter ( GL_ARRAY_OBJECT_BUFFER_ATI = 34662 )
       integer*4   GL_ARRAY_OBJECT_OFFSET_ATI
       parameter ( GL_ARRAY_OBJECT_OFFSET_ATI = 34663 )

C  EXT_vertex_shader 
       integer*4   GL_VERTEX_SHADER_EXT
       parameter ( GL_VERTEX_SHADER_EXT = 34688 )
       integer*4   GL_VERTEX_SHADER_BINDING_EXT
       parameter ( GL_VERTEX_SHADER_BINDING_EXT = 34689 )
       integer*4   GL_OP_INDEX_EXT
       parameter ( GL_OP_INDEX_EXT = 34690 )
       integer*4   GL_OP_NEGATE_EXT
       parameter ( GL_OP_NEGATE_EXT = 34691 )
       integer*4   GL_OP_DOT3_EXT
       parameter ( GL_OP_DOT3_EXT = 34692 )
       integer*4   GL_OP_DOT4_EXT
       parameter ( GL_OP_DOT4_EXT = 34693 )
       integer*4   GL_OP_MUL_EXT
       parameter ( GL_OP_MUL_EXT = 34694 )
       integer*4   GL_OP_ADD_EXT
       parameter ( GL_OP_ADD_EXT = 34695 )
       integer*4   GL_OP_MADD_EXT
       parameter ( GL_OP_MADD_EXT = 34696 )
       integer*4   GL_OP_FRAC_EXT
       parameter ( GL_OP_FRAC_EXT = 34697 )
       integer*4   GL_OP_MAX_EXT
       parameter ( GL_OP_MAX_EXT = 34698 )
       integer*4   GL_OP_MIN_EXT
       parameter ( GL_OP_MIN_EXT = 34699 )
       integer*4   GL_OP_SET_GE_EXT
       parameter ( GL_OP_SET_GE_EXT = 34700 )
       integer*4   GL_OP_SET_LT_EXT
       parameter ( GL_OP_SET_LT_EXT = 34701 )
       integer*4   GL_OP_CLAMP_EXT
       parameter ( GL_OP_CLAMP_EXT = 34702 )
       integer*4   GL_OP_FLOOR_EXT
       parameter ( GL_OP_FLOOR_EXT = 34703 )
       integer*4   GL_OP_ROUND_EXT
       parameter ( GL_OP_ROUND_EXT = 34704 )
       integer*4   GL_OP_EXP_BASE_2_EXT
       parameter ( GL_OP_EXP_BASE_2_EXT = 34705 )
       integer*4   GL_OP_LOG_BASE_2_EXT
       parameter ( GL_OP_LOG_BASE_2_EXT = 34706 )
       integer*4   GL_OP_POWER_EXT
       parameter ( GL_OP_POWER_EXT = 34707 )
       integer*4   GL_OP_RECIP_EXT
       parameter ( GL_OP_RECIP_EXT = 34708 )
       integer*4   GL_OP_RECIP_SQRT_EXT
       parameter ( GL_OP_RECIP_SQRT_EXT = 34709 )
       integer*4   GL_OP_SUB_EXT
       parameter ( GL_OP_SUB_EXT = 34710 )
       integer*4   GL_OP_CROSS_PRODUCT_EXT
       parameter ( GL_OP_CROSS_PRODUCT_EXT = 34711 )
       integer*4   GL_OP_MULTIPLY_MATRIX_EXT
       parameter ( GL_OP_MULTIPLY_MATRIX_EXT = 34712 )
       integer*4   GL_OP_MOV_EXT
       parameter ( GL_OP_MOV_EXT = 34713 )
       integer*4   GL_OUTPUT_VERTEX_EXT
       parameter ( GL_OUTPUT_VERTEX_EXT = 34714 )
       integer*4   GL_OUTPUT_COLOR0_EXT
       parameter ( GL_OUTPUT_COLOR0_EXT = 34715 )
       integer*4   GL_OUTPUT_COLOR1_EXT
       parameter ( GL_OUTPUT_COLOR1_EXT = 34716 )
       integer*4   GL_OUTPUT_TEXTURE_COORD0_EXT
       parameter ( GL_OUTPUT_TEXTURE_COORD0_EXT = 34717 )
       integer*4   GL_OUTPUT_TEXTURE_COORD1_EXT
       parameter ( GL_OUTPUT_TEXTURE_COORD1_EXT = 34718 )
       integer*4   GL_OUTPUT_TEXTURE_COORD2_EXT
       parameter ( GL_OUTPUT_TEXTURE_COORD2_EXT = 34719 )
       integer*4   GL_OUTPUT_TEXTURE_COORD3_EXT
       parameter ( GL_OUTPUT_TEXTURE_COORD3_EXT = 34720 )
       integer*4   GL_OUTPUT_TEXTURE_COORD4_EXT
       parameter ( GL_OUTPUT_TEXTURE_COORD4_EXT = 34721 )
       integer*4   GL_OUTPUT_TEXTURE_COORD5_EXT
       parameter ( GL_OUTPUT_TEXTURE_COORD5_EXT = 34722 )
       integer*4   GL_OUTPUT_TEXTURE_COORD6_EXT
       parameter ( GL_OUTPUT_TEXTURE_COORD6_EXT = 34723 )
       integer*4   GL_OUTPUT_TEXTURE_COORD7_EXT
       parameter ( GL_OUTPUT_TEXTURE_COORD7_EXT = 34724 )
       integer*4   GL_OUTPUT_TEXTURE_COORD8_EXT
       parameter ( GL_OUTPUT_TEXTURE_COORD8_EXT = 34725 )
       integer*4   GL_OUTPUT_TEXTURE_COORD9_EXT
       parameter ( GL_OUTPUT_TEXTURE_COORD9_EXT = 34726 )
       integer*4   GL_OUTPUT_TEXTURE_COORD10_EXT
       parameter ( GL_OUTPUT_TEXTURE_COORD10_EXT = 34727 )
       integer*4   GL_OUTPUT_TEXTURE_COORD11_EXT
       parameter ( GL_OUTPUT_TEXTURE_COORD11_EXT = 34728 )
       integer*4   GL_OUTPUT_TEXTURE_COORD12_EXT
       parameter ( GL_OUTPUT_TEXTURE_COORD12_EXT = 34729 )
       integer*4   GL_OUTPUT_TEXTURE_COORD13_EXT
       parameter ( GL_OUTPUT_TEXTURE_COORD13_EXT = 34730 )
       integer*4   GL_OUTPUT_TEXTURE_COORD14_EXT
       parameter ( GL_OUTPUT_TEXTURE_COORD14_EXT = 34731 )
       integer*4   GL_OUTPUT_TEXTURE_COORD15_EXT
       parameter ( GL_OUTPUT_TEXTURE_COORD15_EXT = 34732 )
       integer*4   GL_OUTPUT_TEXTURE_COORD16_EXT
       parameter ( GL_OUTPUT_TEXTURE_COORD16_EXT = 34733 )
       integer*4   GL_OUTPUT_TEXTURE_COORD17_EXT
       parameter ( GL_OUTPUT_TEXTURE_COORD17_EXT = 34734 )
       integer*4   GL_OUTPUT_TEXTURE_COORD18_EXT
       parameter ( GL_OUTPUT_TEXTURE_COORD18_EXT = 34735 )
       integer*4   GL_OUTPUT_TEXTURE_COORD19_EXT
       parameter ( GL_OUTPUT_TEXTURE_COORD19_EXT = 34736 )
       integer*4   GL_OUTPUT_TEXTURE_COORD20_EXT
       parameter ( GL_OUTPUT_TEXTURE_COORD20_EXT = 34737 )
       integer*4   GL_OUTPUT_TEXTURE_COORD21_EXT
       parameter ( GL_OUTPUT_TEXTURE_COORD21_EXT = 34738 )
       integer*4   GL_OUTPUT_TEXTURE_COORD22_EXT
       parameter ( GL_OUTPUT_TEXTURE_COORD22_EXT = 34739 )
       integer*4   GL_OUTPUT_TEXTURE_COORD23_EXT
       parameter ( GL_OUTPUT_TEXTURE_COORD23_EXT = 34740 )
       integer*4   GL_OUTPUT_TEXTURE_COORD24_EXT
       parameter ( GL_OUTPUT_TEXTURE_COORD24_EXT = 34741 )
       integer*4   GL_OUTPUT_TEXTURE_COORD25_EXT
       parameter ( GL_OUTPUT_TEXTURE_COORD25_EXT = 34742 )
       integer*4   GL_OUTPUT_TEXTURE_COORD26_EXT
       parameter ( GL_OUTPUT_TEXTURE_COORD26_EXT = 34743 )
       integer*4   GL_OUTPUT_TEXTURE_COORD27_EXT
       parameter ( GL_OUTPUT_TEXTURE_COORD27_EXT = 34744 )
       integer*4   GL_OUTPUT_TEXTURE_COORD28_EXT
       parameter ( GL_OUTPUT_TEXTURE_COORD28_EXT = 34745 )
       integer*4   GL_OUTPUT_TEXTURE_COORD29_EXT
       parameter ( GL_OUTPUT_TEXTURE_COORD29_EXT = 34746 )
       integer*4   GL_OUTPUT_TEXTURE_COORD30_EXT
       parameter ( GL_OUTPUT_TEXTURE_COORD30_EXT = 34747 )
       integer*4   GL_OUTPUT_TEXTURE_COORD31_EXT
       parameter ( GL_OUTPUT_TEXTURE_COORD31_EXT = 34748 )
       integer*4   GL_OUTPUT_FOG_EXT
       parameter ( GL_OUTPUT_FOG_EXT = 34749 )
       integer*4   GL_SCALAR_EXT
       parameter ( GL_SCALAR_EXT = 34750 )
       integer*4   GL_VECTOR_EXT
       parameter ( GL_VECTOR_EXT = 34751 )
       integer*4   GL_MATRIX_EXT
       parameter ( GL_MATRIX_EXT = 34752 )
       integer*4   GL_VARIANT_EXT
       parameter ( GL_VARIANT_EXT = 34753 )
       integer*4   GL_INVARIANT_EXT
       parameter ( GL_INVARIANT_EXT = 34754 )
       integer*4   GL_LOCAL_CONSTANT_EXT
       parameter ( GL_LOCAL_CONSTANT_EXT = 34755 )
       integer*4   GL_LOCAL_EXT
       parameter ( GL_LOCAL_EXT = 34756 )
       integer*4   GL_MAX_VERTEX_SHADER_INSTRUCTIONS_EXT
       parameter ( GL_MAX_VERTEX_SHADER_INSTRUCTIONS_EXT = 34757 )
       integer*4   GL_MAX_VERTEX_SHADER_VARIANTS_EXT
       parameter ( GL_MAX_VERTEX_SHADER_VARIANTS_EXT = 34758 )
       integer*4   GL_MAX_VERTEX_SHADER_INVARIANTS_EXT
       parameter ( GL_MAX_VERTEX_SHADER_INVARIANTS_EXT = 34759 )
       integer*4   GL_MAX_VERTEX_SHADER_LOCAL_CONSTANTS_EXT
       parameter ( GL_MAX_VERTEX_SHADER_LOCAL_CONSTANTS_EXT = 34760 )
       integer*4   GL_MAX_VERTEX_SHADER_LOCALS_EXT
       parameter ( GL_MAX_VERTEX_SHADER_LOCALS_EXT = 34761 )
       integer*4   GL_MAX_OPTIMIZED_VERTEX_SHADER_INSTRUCTIONS_EXT
       parameter (
     +  GL_MAX_OPTIMIZED_VERTEX_SHADER_INSTRUCTIONS_EXT = 34762 )
       integer*4   GL_MAX_OPTIMIZED_VERTEX_SHADER_VARIANTS_EXT
       parameter (
     +  GL_MAX_OPTIMIZED_VERTEX_SHADER_VARIANTS_EXT = 34763 )
       integer*4   GL_MAX_OPTIMIZED_VERTEX_SHADER_LOCAL_CONSTANTS_EXT
       parameter (
     +  GL_MAX_OPTIMIZED_VERTEX_SHADER_LOCAL_CONSTANTS_EXT = 34764 )
       integer*4   GL_MAX_OPTIMIZED_VERTEX_SHADER_INVARIANTS_EXT
       parameter (
     +  GL_MAX_OPTIMIZED_VERTEX_SHADER_INVARIANTS_EXT = 34765 )
       integer*4   GL_MAX_OPTIMIZED_VERTEX_SHADER_LOCALS_EXT
       parameter ( GL_MAX_OPTIMIZED_VERTEX_SHADER_LOCALS_EXT = 34766 )
       integer*4   GL_VERTEX_SHADER_INSTRUCTIONS_EXT
       parameter ( GL_VERTEX_SHADER_INSTRUCTIONS_EXT = 34767 )
       integer*4   GL_VERTEX_SHADER_VARIANTS_EXT
       parameter ( GL_VERTEX_SHADER_VARIANTS_EXT = 34768 )
       integer*4   GL_VERTEX_SHADER_INVARIANTS_EXT
       parameter ( GL_VERTEX_SHADER_INVARIANTS_EXT = 34769 )
       integer*4   GL_VERTEX_SHADER_LOCAL_CONSTANTS_EXT
       parameter ( GL_VERTEX_SHADER_LOCAL_CONSTANTS_EXT = 34770 )
       integer*4   GL_VERTEX_SHADER_LOCALS_EXT
       parameter ( GL_VERTEX_SHADER_LOCALS_EXT = 34771 )
       integer*4   GL_VERTEX_SHADER_OPTIMIZED_EXT
       parameter ( GL_VERTEX_SHADER_OPTIMIZED_EXT = 34772 )
       integer*4   GL_X_EXT
       parameter ( GL_X_EXT = 34773 )
       integer*4   GL_Y_EXT
       parameter ( GL_Y_EXT = 34774 )
       integer*4   GL_Z_EXT
       parameter ( GL_Z_EXT = 34775 )
       integer*4   GL_W_EXT
       parameter ( GL_W_EXT = 34776 )
       integer*4   GL_NEGATIVE_X_EXT
       parameter ( GL_NEGATIVE_X_EXT = 34777 )
       integer*4   GL_NEGATIVE_Y_EXT
       parameter ( GL_NEGATIVE_Y_EXT = 34778 )
       integer*4   GL_NEGATIVE_Z_EXT
       parameter ( GL_NEGATIVE_Z_EXT = 34779 )
       integer*4   GL_NEGATIVE_W_EXT
       parameter ( GL_NEGATIVE_W_EXT = 34780 )
       integer*4   GL_ZERO_EXT
       parameter ( GL_ZERO_EXT = 34781 )
       integer*4   GL_ONE_EXT
       parameter ( GL_ONE_EXT = 34782 )
       integer*4   GL_NEGATIVE_ONE_EXT
       parameter ( GL_NEGATIVE_ONE_EXT = 34783 )
       integer*4   GL_NORMALIZED_RANGE_EXT
       parameter ( GL_NORMALIZED_RANGE_EXT = 34784 )
       integer*4   GL_FULL_RANGE_EXT
       parameter ( GL_FULL_RANGE_EXT = 34785 )
       integer*4   GL_CURRENT_VERTEX_EXT
       parameter ( GL_CURRENT_VERTEX_EXT = 34786 )
       integer*4   GL_MVP_MATRIX_EXT
       parameter ( GL_MVP_MATRIX_EXT = 34787 )
       integer*4   GL_VARIANT_VALUE_EXT
       parameter ( GL_VARIANT_VALUE_EXT = 34788 )
       integer*4   GL_VARIANT_DATATYPE_EXT
       parameter ( GL_VARIANT_DATATYPE_EXT = 34789 )
       integer*4   GL_VARIANT_ARRAY_STRIDE_EXT
       parameter ( GL_VARIANT_ARRAY_STRIDE_EXT = 34790 )
       integer*4   GL_VARIANT_ARRAY_TYPE_EXT
       parameter ( GL_VARIANT_ARRAY_TYPE_EXT = 34791 )
       integer*4   GL_VARIANT_ARRAY_EXT
       parameter ( GL_VARIANT_ARRAY_EXT = 34792 )
       integer*4   GL_VARIANT_ARRAY_POINTER_EXT
       parameter ( GL_VARIANT_ARRAY_POINTER_EXT = 34793 )
       integer*4   GL_INVARIANT_VALUE_EXT
       parameter ( GL_INVARIANT_VALUE_EXT = 34794 )
       integer*4   GL_INVARIANT_DATATYPE_EXT
       parameter ( GL_INVARIANT_DATATYPE_EXT = 34795 )
       integer*4   GL_LOCAL_CONSTANT_VALUE_EXT
       parameter ( GL_LOCAL_CONSTANT_VALUE_EXT = 34796 )
       integer*4   GL_LOCAL_CONSTANT_DATATYPE_EXT
       parameter ( GL_LOCAL_CONSTANT_DATATYPE_EXT = 34797 )

C  ATI_vertex_streams 
       integer*4   GL_MAX_VERTEX_STREAMS_ATI
       parameter ( GL_MAX_VERTEX_STREAMS_ATI = 34667 )
       integer*4   GL_VERTEX_STREAM0_ATI
       parameter ( GL_VERTEX_STREAM0_ATI = 34668 )
       integer*4   GL_VERTEX_STREAM1_ATI
       parameter ( GL_VERTEX_STREAM1_ATI = 34669 )
       integer*4   GL_VERTEX_STREAM2_ATI
       parameter ( GL_VERTEX_STREAM2_ATI = 34670 )
       integer*4   GL_VERTEX_STREAM3_ATI
       parameter ( GL_VERTEX_STREAM3_ATI = 34671 )
       integer*4   GL_VERTEX_STREAM4_ATI
       parameter ( GL_VERTEX_STREAM4_ATI = 34672 )
       integer*4   GL_VERTEX_STREAM5_ATI
       parameter ( GL_VERTEX_STREAM5_ATI = 34673 )
       integer*4   GL_VERTEX_STREAM6_ATI
       parameter ( GL_VERTEX_STREAM6_ATI = 34674 )
       integer*4   GL_VERTEX_STREAM7_ATI
       parameter ( GL_VERTEX_STREAM7_ATI = 34675 )
       integer*4   GL_VERTEX_SOURCE_ATI
       parameter ( GL_VERTEX_SOURCE_ATI = 34676 )

C  ATI_element_array 
       integer*4   GL_ELEMENT_ARRAY_ATI
       parameter ( GL_ELEMENT_ARRAY_ATI = 34664 )
       integer*4   GL_ELEMENT_ARRAY_TYPE_ATI
       parameter ( GL_ELEMENT_ARRAY_TYPE_ATI = 34665 )
       integer*4   GL_ELEMENT_ARRAY_POINTER_ATI
       parameter ( GL_ELEMENT_ARRAY_POINTER_ATI = 34666 )

C  NV_occlusion_query 
       integer*4   GL_PIXEL_COUNTER_BITS_NV
       parameter ( GL_PIXEL_COUNTER_BITS_NV = 34916 )
       integer*4   GL_CURRENT_OCCLUSION_QUERY_ID_NV
       parameter ( GL_CURRENT_OCCLUSION_QUERY_ID_NV = 34917 )
       integer*4   GL_PIXEL_COUNT_NV
       parameter ( GL_PIXEL_COUNT_NV = 34918 )
       integer*4   GL_PIXEL_COUNT_AVAILABLE_NV
       parameter ( GL_PIXEL_COUNT_AVAILABLE_NV = 34919 )

C  S3_s3tc 
       integer*4   GL_RGB_S3TC
       parameter ( GL_RGB_S3TC = 33696 )
       integer*4   GL_RGB4_S3TC
       parameter ( GL_RGB4_S3TC = 33697 )
       integer*4   GL_RGBA_S3TC
       parameter ( GL_RGBA_S3TC = 33698 )
       integer*4   GL_RGBA4_S3TC
       parameter ( GL_RGBA4_S3TC = 33699 )

C  ATI_draw_buffers 
       integer*4   GL_MAX_DRAW_BUFFERS_ATI
       parameter ( GL_MAX_DRAW_BUFFERS_ATI = 34852 )
       integer*4   GL_DRAW_BUFFER0_ATI
       parameter ( GL_DRAW_BUFFER0_ATI = 34853 )
       integer*4   GL_DRAW_BUFFER1_ATI
       parameter ( GL_DRAW_BUFFER1_ATI = 34854 )
       integer*4   GL_DRAW_BUFFER2_ATI
       parameter ( GL_DRAW_BUFFER2_ATI = 34855 )
       integer*4   GL_DRAW_BUFFER3_ATI
       parameter ( GL_DRAW_BUFFER3_ATI = 34856 )
       integer*4   GL_DRAW_BUFFER4_ATI
       parameter ( GL_DRAW_BUFFER4_ATI = 34857 )
       integer*4   GL_DRAW_BUFFER5_ATI
       parameter ( GL_DRAW_BUFFER5_ATI = 34858 )
       integer*4   GL_DRAW_BUFFER6_ATI
       parameter ( GL_DRAW_BUFFER6_ATI = 34859 )
       integer*4   GL_DRAW_BUFFER7_ATI
       parameter ( GL_DRAW_BUFFER7_ATI = 34860 )
       integer*4   GL_DRAW_BUFFER8_ATI
       parameter ( GL_DRAW_BUFFER8_ATI = 34861 )
       integer*4   GL_DRAW_BUFFER9_ATI
       parameter ( GL_DRAW_BUFFER9_ATI = 34862 )
       integer*4   GL_DRAW_BUFFER10_ATI
       parameter ( GL_DRAW_BUFFER10_ATI = 34863 )
       integer*4   GL_DRAW_BUFFER11_ATI
       parameter ( GL_DRAW_BUFFER11_ATI = 34864 )
       integer*4   GL_DRAW_BUFFER12_ATI
       parameter ( GL_DRAW_BUFFER12_ATI = 34865 )
       integer*4   GL_DRAW_BUFFER13_ATI
       parameter ( GL_DRAW_BUFFER13_ATI = 34866 )
       integer*4   GL_DRAW_BUFFER14_ATI
       parameter ( GL_DRAW_BUFFER14_ATI = 34867 )
       integer*4   GL_DRAW_BUFFER15_ATI
       parameter ( GL_DRAW_BUFFER15_ATI = 34868 )

C  ATI_map_object_buffer 

C  ATI_separate_stencil 
       integer*4   GL_STENCIL_BACK_FUNC_ATI
       parameter ( GL_STENCIL_BACK_FUNC_ATI = 34816 )
       integer*4   GL_STENCIL_BACK_FAIL_ATI
       parameter ( GL_STENCIL_BACK_FAIL_ATI = 34817 )
       integer*4   GL_STENCIL_BACK_PASS_DEPTH_FAIL_ATI
       parameter ( GL_STENCIL_BACK_PASS_DEPTH_FAIL_ATI = 34818 )
       integer*4   GL_STENCIL_BACK_PASS_DEPTH_PASS_ATI
       parameter ( GL_STENCIL_BACK_PASS_DEPTH_PASS_ATI = 34819 )

C  ATI_vertex_attrib_array_object 

C ***********************************************************


       character*8   FGL_NULL
       parameter ( FGL_NULL = char(0)//char(0)//char(0)//
     *                        char(0)//char(0)//char(0)//
     *                        char(0)//char(0) )


       character*128       fglGetString
       integer             fglGetError
       integer*4           fglFinishAsyncSGIX
       integer*4           fglGetInstrumentsSGIX
       integer*4           fglPollAsyncSGIX
       integer*4           fglPollInstrumentsSGIX
       integer*4           fglRenderMode
       logical*1           fglAreTexturesResident
       logical*1           fglAreTexturesResidentEXT
       logical*1           fglIsAsyncMarkerSGIX
       logical*1           fglIsEnabled
       logical*1           fglIsList
       logical*1           fglIsTexture
       logical*1           fglIsTextureEXT
       logical*4           fglGenAsyncMarkersSGIX
       logical*4           fglGenLists
