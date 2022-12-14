#ifndef _GLwDrawA_h
#define _GLwDrawA_h

#include <GL/glx.h>
#include <GL/gl.h>

/****************************************************************
 *
 * GLwDrawingArea widgets
 *
 ****************************************************************/

/* Resources:

 Name		     Class		RepType		Default Value
 ----		     -----		-------		-------------
 attribList	     AttribList		int *		NULL
 visualInfo	     VisualInfo		VisualInfo	NULL
 installColormap     InstallColormap	Boolean		TRUE
 allocateBackground  AllocateColors	Boolean		FALSE
 allocateOtherColors AllocateColors	Boolean		FALSE
 installBackground   InstallBackground	Boolean		TRUE
 exposeCallback      Callback		Pointer		NULL
 ginitCallback       Callback		Pointer		NULL
 inputCallback       Callback		Pointer		NULL
 resizeCallback      Callback		Pointer		NULL

*** The following resources all correspond to the GLX configuration
*** attributes and are used to create the attribList if it is NULL
 bufferSize	     BufferSize		int		0
 level		     Level		int		0
 rgba		     Rgba		Boolean		FALSE
 doublebuffer	     Doublebuffer	Boolean		FALSE
 stereo		     Stereo		Boolean		FALSE
 auxBuffers	     AuxBuffers		int		0
 redSize	     ColorSize		int		1
 greenSize	     ColorSize		int		1
 blueSize	     ColorSize		int		1
 alphaSize	     AlphaSize		int		0
 depthSize	     DepthSize		int		0
 stencilSize	     StencilSize	int		0
 accumRedSize	     AccumColorSize	int		0
 accumGreenSize	     AccumColorSize	int		0
 accumBlueSize	     AccumColorSize	int		0
 accumAlphaSize	     AccumAlphaSize	int		0
*/

#define GLwNattribList		"attribList"
#define GLwCAttribList		"AttribList"
#define GLwNvisualInfo		"visualInfo"
#define GLwCVisualInfo		"VisualInfo"
#define GLwRVisualInfo		"VisualInfo"

#define GLwNinstallColormap	"installColormap"
#define GLwCInstallColormap	"InstallColormap"
#define GLwNallocateBackground	"allocateBackground"
#define GLwNallocateOtherColors	"allocateOtherColors"
#define GLwCAllocateColors	"AllocateColors"
#define GLwNinstallBackground	"installBackground"
#define GLwCInstallBackground	"InstallBackground"

#define GLwCCallback		"Callback"
#define GLwNexposeCallback	"exposeCallback"
#define GLwNginitCallback	"ginitCallback"
#define GLwNresizeCallback	"resizeCallback"
#define GLwNinputCallback	"inputCallback"

#define GLwNbufferSize		"bufferSize"
#define GLwCBufferSize		"BufferSize"
#define GLwNlevel		"level"
#define GLwCLevel		"Level"
#define GLwNrgba		"rgba"
#define GLwCRgba		"Rgba"
#define GLwNdoublebuffer	"doublebuffer"
#define GLwCDoublebuffer	"Doublebuffer"
#define GLwNstereo		"stereo"
#define GLwCStereo		"Stereo"
#define GLwNauxBuffers		"auxBuffers"
#define GLwCAuxBuffers		"AuxBuffers"
#define GLwNredSize		"redSize"
#define GLwNgreenSize		"greenSize"
#define GLwNblueSize		"blueSize"
#define GLwCColorSize		"ColorSize"
#define GLwNalphaSize		"alphaSize"
#define GLwCAlphaSize		"AlphaSize"
#define GLwNdepthSize		"depthSize"
#define GLwCDepthSize		"DepthSize"
#define GLwNstencilSize		"stencilSize"
#define GLwCStencilSize		"StencilSize"
#define GLwNaccumRedSize	"accumRedSize"
#define GLwNaccumGreenSize	"accumGreenSize"
#define GLwNaccumBlueSize	"accumBlueSize"
#define GLwCAccumColorSize	"AccumColorSize"
#define GLwNaccumAlphaSize	"accumAlphaSize"
#define GLwCAccumAlphaSize	"AccumAlphaSize"

#ifdef __GLX_MOTIF
#if XmVERSION > 1

#define GLwDrawingAreaMakeCurrent GLwDrawingArea21MakeCurrent
#define GLwDrawingAreaSwapBuffers GLwDrawingArea21SwapBuffers

#define glwMDrawingAreaWidgetClass	glwM21DrawingAreaWidgetClass
#define GLwMDrawingAreaClassRec GLwM21DrawingAreaClassRec

typedef struct _GLwM21DrawingAreaClassRec	*GLwM21DrawingAreaWidgetClass;
typedef struct _GLwM21DrawingAreaRec	*GLwM21DrawingAreaWidget;
#endif
typedef struct _GLwMDrawingAreaClassRec	*GLwMDrawingAreaWidgetClass;
typedef struct _GLwMDrawingAreaRec	*GLwMDrawingAreaWidget;

extern WidgetClass glwMDrawingAreaWidgetClass;
#else /* not __GLX_MOTIF */
typedef struct _GLwDrawingAreaClassRec	*GLwDrawingAreaWidgetClass;
typedef struct _GLwDrawingAreaRec	*GLwDrawingAreaWidget;

extern WidgetClass glwDrawingAreaWidgetClass;
#endif

/* Callback reasons */
#ifdef __GLX_MOTIF
#define GLwCR_EXPOSE	XmCR_EXPOSE
#define GLwCR_RESIZE	XmCR_RESIZE
#define GLwCR_INPUT	XmCR_INPUT
#else /* not __GLX_MOTIF */
/* The same values as Motif, but don't use Motif constants */
#define GLwCR_EXPOSE	38
#define GLwCR_RESIZE	39
#define GLwCR_INPUT	40
#endif /* __GLX_MOTIF */

#define GLwCR_GINIT	32135	/* Arbitrary number that should neverr clash*/

typedef struct
{
    int     reason;
    XEvent  *event;
    Dimension width, height;		/* for resize callback */
} GLwDrawingAreaCallbackStruct;

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

/* front ends to glXMakeCurrent and glXSwapBuffers */
extern void GLwDrawingAreaMakeCurrent (Widget w, GLXContext ctx);
extern void GLwDrawingAreaSwapBuffers (Widget w);

#ifdef __GLX_MOTIF
#ifdef _NO_PROTO
extern Widget GLwCreateMDrawingArea ();
#else /* _NO_PROTO */

extern Widget GLwCreateMDrawingArea (Widget parent, char *name,
				     ArgList arglist, Cardinal argcount);
#endif /* _NO_PROTO */

#endif /* __GLX_MOTIF */

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif /* _GLwDrawA_h */
