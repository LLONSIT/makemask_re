#ifndef _DM_FX_IMAGE_VIEWER_H_
#define _DM_FX_IMAGE_VIEWER_H_

#define Object  _XT_OBJECT_
#define Boolean _XT_BOOLEAN_
#include <X11/Intrinsic.h>
#undef Boolean
#undef Object

#include <GL/GLwMDrawA.h>
#include <GL/glx.h>

class DMFXImageViewer
{
  public:
    DMFXImageViewer(Widget w);
    ~DMFXImageViewer();

    //
    // setBuf() -- takes a pointer to an ABGR image that is to be
    // displayed in the gl widget.  The image is resized as needed to
    // show up in the window.  Ownership of the pointer remains with
    // the caller, *but* this object retains a pointer to it until the
    // next setBuf call.  It is OK to call setBuf with NULL.
    //
    // PlugIns that render with OpenGL, and want to render directly to
    // the screen can use the setGLContext(), and restoreGLContext() calls
    // (see below).
    //
    // No explicit redraw() is necessary after a setBuf call().
    //
    // When using setBuf(), expose events are handled by the image viewer
    // class, and the plugin does not need to handle them.
    //

    void setBuf(const void *, unsigned int w, unsigned int h, unsigned int rb);

    //
    // Force a redraw of the current buffer.
    //

    void redraw();

    //
    // setGLContext() and restoreGLContext() - used by plugins that render
    // exclusively with OpenGL to set up for rendering directly into the
    // DMFXImageViewer object, and then restore the previous OpenGL
    // rendering context.
    //
    // The typical usage of these calls follows:
    //
    //     view->setExposeCallback(exposeCB, clientData);
    //
    //     view->setGLContext();
    //     renderWithOpenGL();
    //     view->restoreGLContext();
    //
    // The caller should pass an expose event handler via setExposeCallback.
    // When an expose event is generated on the window, the expose handler is
    // called with the GL context set appropriately.  The caller's expose
    // handler does not have to set the GL context.
    //
    // The expose callback would look like:
    //
    // void exposeCB(Widget w, XtPointer clientData, const XEvent *xev)
    // {
    //     renderWithOpenGL();
    // }
    //

    typedef void (*ExposeCallback)(Widget w,
      XtPointer clientData, const XEvent *xev);

    void setExposeCallback(ExposeCallback exposeCB, XtPointer clientData);
    void setGLContext();
    void restoreGLContext();

    //
    // when "keepAspectRatio" is set (the default is TRUE), the widget
    // will be padded with black, as needed, to preserve the aspect
    // ratio of the image. 
    //

    Boolean setKeepAspectRatio(Boolean);
    Boolean getKeepAspectRatio();

  private:
    void clear();

    void createContext();
    void expose(Widget w, const XEvent *xev);
    void resize(unsigned int w, unsigned int h);

    static void initCallback(Widget w, XtPointer clientD, XtPointer callD);
    static void resizeCallback(Widget w, XtPointer clientD, XtPointer callD);
    static void exposeCallback(Widget w, XtPointer clientD, XtPointer callD);

    Widget myWidget;
    GLXContext myGLXContext;

    ExposeCallback myExposeCB;
    XtPointer      myExposeCBClientData;

    const void *myImageBuf;
    unsigned int myImageWidth;
    unsigned int myImageHeight;
    unsigned int myRowBytes;
    Boolean myKeepAspectRatio;

    GLXDrawable curDrawable;
    GLXContext  curContext;
    Display* curDisplay;
};

#endif // _DM_FX_IMAGE_VIEWER_H_
