#ifndef SGIFASTATOM_H
#define SGIFASTATOM_H

/*
 * X11/SGIFastAtoms.h - a performance optimiation for round-trip less X atom interning.
 *
 * Copyright 1991, Silicon Graphics, Inc.
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

#define SGI_XA_SGI_EXTRA_PREDEFINES ((Atom)69)
#define SGI_XA_AVERAGE_WIDTH ((Atom)70)
#define SGI_XA_BACKGROUND ((Atom)71)
#define SGI_XA_CLIPBOARD ((Atom)72)
#define SGI_XA_CLIP_TEMPORARY ((Atom)73)
#define SGI_XA_COMPOUND_TEXT ((Atom)74)
#define SGI_XA_EXTENDED_TARGETS ((Atom)75)
#define SGI_XA_FOREGROUND ((Atom)76)
#define SGI_XA_INCR ((Atom)77)
#define SGI_XA_LENGTH ((Atom)78)
#define SGI_XA_MOTIF_DESTINATION ((Atom)79)
#define SGI_XA_MULTIPLE ((Atom)80)
#define SGI_XA_NATIVE_TARGETS ((Atom)81)
#define SGI_XA_NULL ((Atom)82)
#define SGI_XA_PIXEL ((Atom)83)
#define SGI_XA_PIXEL_SIZE ((Atom)84)
#define SGI_XA_RESOLUTION_Y ((Atom)85)
#define SGI_XA_SCREEN_RESOURCES ((Atom)86)
#define SGI_XA_SERVER_OVERLAY_VISUALS ((Atom)87)
#define SGI_XA_SM_CLIENT_ID ((Atom)88)
#define SGI_XA_TARGETS ((Atom)89)
#define SGI_XA_TEXT ((Atom)90)
#define SGI_XA_TIMESTAMP ((Atom)91)
#define SGI_XA_WM_CHANGE_STATE ((Atom)92)
#define SGI_XA_WM_CLIENT_LEADER ((Atom)93)
#define SGI_XA_WM_COLORMAP_WINDOWS ((Atom)94)
#define SGI_XA_WM_DELETE_WINDOW ((Atom)95)
#define SGI_XA_WM_LOCALE_NAME ((Atom)96)
#define SGI_XA_WM_PROTOCOLS ((Atom)97)
#define SGI_XA_WM_STATE ((Atom)98)
#define SGI_XA_WM_WINDOW_ROLE ((Atom)99)
#define SGI_XA_XDCCC_CORRECT_ATOM_NAME ((Atom)100)
#define SGI_XA_XDCCC_MATRIX_ATOM_NAME ((Atom)101)
#define SGI_XA__MOTIF_BINDINGS ((Atom)102)
#define SGI_XA__MOTIF_CANCEL_DROP_EFFECT ((Atom)103)
#define SGI_XA__MOTIF_CLIP_DATA_DELETE ((Atom)104)
#define SGI_XA__MOTIF_CLIP_DATA_REQUEST ((Atom)105)
#define SGI_XA__MOTIF_CLIP_HEADER ((Atom)106)
#define SGI_XA__MOTIF_CLIP_LOCK ((Atom)107)
#define SGI_XA__MOTIF_CLIP_LOCK_ACCESS_VALID ((Atom)108)
#define SGI_XA__MOTIF_CLIP_MESSAGE ((Atom)109)
#define SGI_XA__MOTIF_CLIP_TIME ((Atom)110)
#define SGI_XA__MOTIF_DEFAULT_BINDINGS ((Atom)111)
#define SGI_XA__MOTIF_DRAG_ATOMS ((Atom)112)
#define SGI_XA__MOTIF_DRAG_ATOM_PAIRS ((Atom)113)
#define SGI_XA__MOTIF_DRAG_INITIATOR_INFO ((Atom)114)
#define SGI_XA__MOTIF_DRAG_PROXY_WINDOW ((Atom)115)
#define SGI_XA__MOTIF_DRAG_RECEIVER_INFO ((Atom)116)
#define SGI_XA__MOTIF_DRAG_TARGETS ((Atom)117)
#define SGI_XA__MOTIF_DRAG_WINDOW ((Atom)118)
#define SGI_XA__MOTIF_DROP ((Atom)119)
#define SGI_XA__MOTIF_PROXY_WINDOW ((Atom)120)
#define SGI_XA__MOTIF_WINDOW ((Atom)121)
#define SGI_XA__MOTIF_WM_HINTS ((Atom)122)
#define SGI_XA__MOTIF_WM_INFO ((Atom)123)
#define SGI_XA__MOTIF_WM_MESSAGES ((Atom)124)
#define SGI_XA__MOTIF_WM_OFFSET ((Atom)125)
#define SGI_XA__WM_QUIT_APP ((Atom)126)
#define SGI_XA__XM_TEXT_I_S_PROP ((Atom)127)
#define SGI_XA__XT_SELECTION_0 ((Atom)128)
#define SGI_XA_SGI_HELP_REQUEST ((Atom)129)
#define SGI_XA_SGI_HELP_SERVER ((Atom)130)
#define SGI_XA__SGI_GAMMA_FLAG ((Atom)131)
#define SGI_XA__SGI_ICON ((Atom)132)
#define SGI_XA__SGI_ICONS_VISUALS ((Atom)133)
#define SGI_XA__SGI__MENU_WINDOW ((Atom)134)
#define SGI_XA_Compose ((Atom)135)
#define SGI_XA_close ((Atom)136)
#define SGI_XA_play ((Atom)137)
#define SGI_XA_install ((Atom)138)
#define SGI_XA_level ((Atom)139)
#define SGI_XA_mute ((Atom)140)
#define SGI_XA__SGI_SoundScheme ((Atom)141)
#define SGI_XA_DELETE ((Atom)142)
#define SGI_XA_INSERT_SELECTION ((Atom)143)
#define SGI_XA_ATOM_PAIR ((Atom)144)
#define SGI_XA_Editres ((Atom)145)
#define SGI_XA_EditresCommand ((Atom)146)
#define SGI_XA_EditresClientVal ((Atom)147)
#define SGI_XA_EditresProtocol ((Atom)148)
#define SGI_XA__MOTIF_WM_MENU ((Atom)149)

/* Motif 2.1 atoms */
#define SGI_XA_CHARACTER_POSITION ((Atom)150)
#define SGI_XA_CLASS ((Atom)151)
#define SGI_XA_CLIENT_WINDOW ((Atom)152)
#define SGI_XA_CLIPBOARD_MANAGER ((Atom)153)
#define SGI_XA_COLUMN_NUMBER ((Atom)154)
#define SGI_XA_DONE ((Atom)155)
#define SGI_XA_FILE ((Atom)156)
#define SGI_XA_FILE_NAME ((Atom)157)
#define SGI_XA_HOST_NAME ((Atom)158)
#define SGI_XA_INSERT_PROPERTY ((Atom)159)
#define SGI_XA_LINE_NUMBER ((Atom)160)
#define SGI_XA_LINK_SELECTION ((Atom)161)
#define SGI_XA_LIST_LENGTH ((Atom)162)
#define SGI_XA_MODULE ((Atom)163)
#define SGI_XA_NAME ((Atom)164)
#define SGI_XA_None ((Atom)165)
#define SGI_XA_ODIF ((Atom)166)
#define SGI_XA_OWNER_OS ((Atom)167)
#define SGI_XA_PDM_EXIT_CANCEL ((Atom)168)
#define SGI_XA_PDM_EXIT_ERROR ((Atom)169)
#define SGI_XA_PDM_EXIT_OK ((Atom)170)
#define SGI_XA_PDM_REPLY ((Atom)171)
#define SGI_XA_PDM_START ((Atom)172)
#define SGI_XA_PDM_START_ERROR ((Atom)173)
#define SGI_XA_PDM_START_OK ((Atom)174)
#define SGI_XA_PDM_START_PXAUTH ((Atom)175)
#define SGI_XA_PDM_START_VXAUTH ((Atom)176)
#define SGI_XA_PROCEDURE ((Atom)177)
#define SGI_XA_PROCESS ((Atom)178)
#define SGI_XA_Pixel_Sets ((Atom)179)
#define SGI_XA_SDT_Pixel_Set ((Atom)180)
#define SGI_XA_SPAN ((Atom)181)
#define SGI_XA_TASK ((Atom)182)
#define SGI_XA_TRANSFER_FAILURE ((Atom)183)
#define SGI_XA_TRANSFER_SUCCESS ((Atom)184)
#define SGI_XA_USER ((Atom)185)
#define SGI_XA__MOTIF_ATOM_0 ((Atom)186)
#define SGI_XA__MOTIF_CLIPBOARD_TARGETS ((Atom)187)
#define SGI_XA__MOTIF_COMPOUND_STRING ((Atom)188)
#define SGI_XA__MOTIF_CURRENT_TIME ((Atom)189)
#define SGI_XA__MOTIF_DEFERRED_CLIPBOARD_TARGETS ((Atom)190)
#define SGI_XA__MOTIF_DESTINATION ((Atom)191)
#define SGI_XA__MOTIF_DRAG_OFFSET ((Atom)192)
#define SGI_XA__MOTIF_ENCODING_REGISTRY ((Atom)193)
#define SGI_XA__MOTIF_EXPORT_TARGETS ((Atom)194)
#define SGI_XA__MOTIF_LOSE_SELECTION ((Atom)195)
#define SGI_XA__MOTIF_RENDER_TABLE ((Atom)196)
#define SGI_XA__MOTIF_SELECTION_TEXT ((Atom)197)
#define SGI_XA__MOTIF_SNAPSHOT ((Atom)198)
#define SGI_XA__MOTIF_WM_ALL_CLIENTS ((Atom)199)
#define SGI_XA__MOTIF_WM_QUERY ((Atom)200)


#define SGI_XA_LAST_EXTRA_PREDEFINED SGI_XA__MOTIF_WM_QUERY

#ifndef _XSERVER_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if 0 /* COMMENT */

To portably use fast atoms in X your code, put this in your #include section:

#include <X11/Xatom.h>  /* This defines _SGI_EXTRA_PREDEFINES if fast atoms are supported. */
#ifdef _SGI_EXTRA_PREDEFINES
#include <X11/SGIFastAtom.h>
#else
#define XSGIFastInternAtom(dpy,string,fast_name,how) XInternAtom(dpy,string,how)
#endif

Then, where you would normally use XInternAtom or XmInternAtom, use:

  atom = XSGIFastInternAtom(dpy, "WM_DELETE_WINDOW", SGI_XA_WM_DELETE_WINDOW, False);

This lets your X source code using fast atoms work when compiled on X
implementations that lack SGI's fast atoms optimizations.

#endif /* END COMMENT */

#define XSGIFastInternAtom(dpy,string,fast_name,how) _XSGIFastInternAtom(dpy,fast_name,how)

extern Atom _XSGIFastInternAtom(
#if NeedFunctionPrototypes
    Display *dpy,
    int fast_name,
    Bool onlyIfExists
#endif
);
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* SGIFASTATOM_H */
