/************************************************************
Copyright 1995 by Silicon Graphics, Inc.

Permission to use, copy, modify, and distribute this
software and its documentation for any purpose and without
fee is hereby granted, provided that the above copyright
no- tice appear in all copies and that both that copyright
no- tice and this permission notice appear in supporting
docu- mentation, and that the name of SGI not be used in
advertising or publicity pertaining to distribution of the
software without specific prior written permission.
S.G.I. makes no representation about the suitability of
this software for any purpose. It is provided "as is"
without any express or implied warranty.

SGI DISCLAIMS ALL WARRANTIES WITH REGARD TO  THIS  SOFTWARE,
INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FIT-
NESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL SUN BE  LI-
ABLE  FOR  ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,  DATA  OR
PROFITS,  WHETHER  IN  AN  ACTION OF CONTRACT, NEGLIGENCE OR
OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION  WITH
THE USE OR PERFORMANCE OF THIS SOFTWARE.
************************************************************/

typedef int (*ReqProc) (
#if NeedNestedPrototypes
    ClientPtr /* pClient */
#endif
);
extern void (* ReplySwapVector[256]) ();

#define MAXREQUEST 256L

#define MAC_ACCESS               1
#define DAC_ACCESS               2
#define TP_ACCESS                3

/* X objects used in audit */
#define DRAWABLE                 0
#define GFX                      1    
#define WINDOW                   2
#define FONT                     3
#define SELECTION                4
#define PROPERTY                 5
#define COLORMAP                 6
#define COLORCELL                7
#define PIXMAP                   8
#define CURSOR                   9
#define ATOM                     10
#define DEVICE                   11
#define SERVER                   12
#define CLIENT                   13
#define EXTENSION                14

/* MAC & DAC access modes */
#define READ                     0
#define WRITE                    1
#define CREATE                   2
#define MODIFY                   3
#define DESTROY                  4
#define REPARENT                 5

#define GETPROPERTY              6
#define CHANGEPROPERTY           7
#define DELETEPROPERTY           8

#define GETSELECTIONOWNER        9
#define SETSELECTIONOWNER        10
#define CONVERTSELECTION         11

/* Macros */
#define PrintMACLabel(label) \
    mac_to_text(&label, NULL)
#define CHECK_RESOURCE_ACCESS(Event, Mode, client, pResource)       \
    (CheckAccess(Event, Mode, client, (pResource)->id))
#define CHECK_DRAWABLE_ACCESS(Mode, client, pDraw)                  \
    ((pDraw->type == DRAWABLE_PIXMAP)   ?                               \
         CHECK_RESOURCE_ACCESS(PIXMAP, Mode, client, (ResourcePtr) pDraw) : \
         CheckWindowAccess (Mode, client, (WindowPtr) pDraw, NULL))
#define FIND_X_RESOURCE(ObjType, id, resType) \
( ObjType ) LookupIDByType(id, resType)
#define AC_CREATE_ATOM(AtomName, Length, MakeIt) \
        MakeAtom((AtomName), (Length), (MakeIt))
#define AC_VALID_ATOM(a) ValidAtom((a))
#define AC_LOOKUP_WINDOW(id, client) \
(WindowPtr) LookupWindow(id, client)
#define AC_FIND_WINDOW(id, client) \
{ \
      if (!(pWin = AC_LOOKUP_WINDOW(id, client)) ) \
      { \
          client->errorValue = id; \
          return(BadWindow); \
      } \
}
#define CLIENT_REQUEST(client, stuff) \
	client->requestBuffer = (pointer)stuff
#define RETURN_CLIENT(client, stuff) \
        return ( (*((ReqProc *) client->devPrivates[AccessClientPrivateIndex].ptr) \
              [stuff->reqType]) (client) )

#define WINPTR_WID(w)        ((w)->drawable.id)
#define WINPTR_DEPTH(w)      ((w)->drawable.depth)
#define WINPTR_FIRSTCHILD(w) ((w)->firstChild)
#define WINPTR_LASTCHILD(w)  ((w)->lastChild)
#define WINPTR_PREVSIB(w)    ((w)->prevSib)
#define WINPTR_NEXTSIB(w)    ((w)->nextSib)
#define REALCHILDHEAD(w)     RealChildHead(w)
#define SEL_SELECTION(s)     ((s).selection)
#define SEL_WINDOW(s)        ((s).window)
#define PROP_PTR_NAME(p)     ((p)->propertyName)

typedef struct {
    int mode;
    char *name;
} binding;

static binding access_mode[] =
{
    { READ, "READ"   },
    { WRITE, "WRITE" },
    { CREATE, "CREATE" },
    { MODIFY, "MODIFY" },
    { DESTROY, "DESTROY" },   
    { REPARENT, "REPARENT" },
    { GETPROPERTY, "GETPROPERTY" },             
    { CHANGEPROPERTY, "CHANGEPROPERTY" },
    { DELETEPROPERTY, "DELETEPROPERTY" },
    { GETSELECTIONOWNER, "GETSELECTIONOWNER" },
    { SETSELECTIONOWNER, "SETSELECTIONOWNER" },
    { CONVERTSELECTION, "CONVERTSELECTION" },
    { 0, 0 }
};

static binding audit_obj[] =
{
    { DRAWABLE, "DRAWABLE"   },
    { GFX, "GC" },
    { WINDOW, "WINDOW" },
    { FONT, "FONT" },
    { SELECTION, "SELECTION" },    
    { PROPERTY, "PROPERTY" },
    { COLORMAP, "COLORMAP" },
    { COLORCELL, "COLORCELL" },
    { PIXMAP, "PIXMAP" },
    { CURSOR, "CURSOR" },
    { ATOM, "ATOM" },
    { DEVICE, "DEVICE" },
    { SERVER, "SERVER" },
    { CLIENT, "CLIENT" },   
    { EXTENSION, "EXTENSION" },
    { 0, 0 }
};
