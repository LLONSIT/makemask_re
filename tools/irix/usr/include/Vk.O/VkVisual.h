// This class is to simplify handling visuals:
//	* default visuals
//	* widget visuals
//	* semantically-defined visuals (e.g. "deepest overlay visual")
//
// This should make it simple enough to do things right that users can
// replace default visuals code with use of this class.

#ifndef VKVISUAL_H
#define VKVISUAL_H

#include <X11/Intrinsic.h>
#include <X11/Xmd.h>
#include <Vk/VkBase.h>

class VkComponent;

struct VkVisualInfo {
    XVisualInfo xv;		// Standard X11 visual information
    CARD32 overlayType;		// 0=none, xparent pixel=1, transparency mask=2
    CARD32 overlayPixel;	// Pixel value or transparency mask
    INT32 level;		// <0=underlay, 0=normal, >0=overlay planes
    Colormap cmap;		// Application's colormap for this visual
};


class
VkVisual : public VkBase {

    public:

      // Static functions -- useful even without the object.
	static  Widget		visualParent( Widget w, Visual ** );
	static  void		visualParentArgs(Widget parent, Arg *a, int *n);

      // Enums that describe visuals, and routines to convert them to strings.
      // The string routines are mainly used for things like debug printing.
      // MAX_UNDERLAY_LEVEL means closest to zero -- usually -1 (if any are
      // available at all).
	enum colors   {MAX_AVAILABLE_COLORS=0};

	enum index    {MAX_VISUALS=999,
		       RESET=1000, FIRST=1001, NEXT=1002, LAST=1003};
	virtual const char *indexString(index i) const;

	enum planes   {MAX_EXPLICIT=999, NORMAL_LEVEL=1000,
		       OVERLAY_LEVEL=1001, UNDERLAY_LEVEL=1002,
		       MAX_OVERLAY_LEVEL=1003,  MIN_OVERLAY_LEVEL=1004,
		       MAX_UNDERLAY_LEVEL=1005, MIN_UNDERLAY_LEVEL=1006,
		       ANY_LEVEL=1007};
	virtual const char *planesString(planes i) const;

	// SUCCESS=0 because that allows "if (!SUCCESS) ..."
	enum status {FAILURE=-1, SUCCESS=0, ALMOST=1};
	virtual const char *statusString(status i) const;

	enum transparency	// For SERVER_OVERLAY_VISUALS related stuff
		{TRANSPARENT_NONE=0, TRANSPARENT_PIXEL=1,
		 TRANSPARENT_MASK=2,  TRANSPARENT_DONT_CARE=3};
	virtual const char *transparencyString(CARD32 i) const;

	virtual const char *visualClassString(int i) const;

      // Set up visuals appropriate to the supplied widget.  If null, default
      // visuals will be used.  This can be overriden later with a
      // setVisual() call.
	VkVisual (Widget=NULL, Boolean forceNewCmap=FALSE);
	VkVisual (const VkComponent*, Boolean forceNewCmap=FALSE);
	VkVisual ( int visualClass, int level=NORMAL_LEVEL,
			int colors=MAX_AVAILABLE_COLORS,
			CARD32 xparentRequested=TRANSPARENT_DONT_CARE,
			Boolean forceNewCmap=FALSE);

	VkVisual (const VkVisual&);		// Copy constructor
	VkVisual &operator =(const VkVisual&);

	virtual ~VkVisual();
	virtual const char* className( void ) const;

      // Set information

	// Set a new colormap.  If cmap is NULL, just make an empty new
	// one like the current one.
	virtual Colormap setColormap(Colormap cmap=NULL,
				 Boolean setDefault=False);

	// Reset the class to be for a different visual environment
      	// These pretty much mirror the constructors.
	virtual void setVisual( Widget w=NULL, Boolean forceNewCmap=FALSE);
	virtual void setVisual (const VkComponent*, Boolean forceNewCmap=FALSE);
	virtual status setVisual
		( int visualClass, int level, int colors,
		CARD32 transparent, Boolean forceNewCmap=FALSE);

	// Allow the application to switch color // maps if it needs to do so.


      // Retrieve visual information.
	virtual int		argCnt() const;	// # items in the arglist

	// Ptr to a read-only arglist.  Return val not const so can pass to X11
	virtual ArgList		argList() const;

	// Copies argCnt() items into the caller's arglist
	virtual void		argList(Arg *args, Cardinal *offset) const;
	inline void		argList(Arg *args, int *offset) const
					{argList(args, (Cardinal*)offset);}

	virtual Colormap	colormap() const;
	virtual Boolean		colormapCreated() const;
	virtual int		depth() const;
	virtual int		maxLevel() const;
	virtual int		minLevel() const;
	virtual int		numColors() const;
	virtual Visual         *visual() const;
	virtual VisualID	visualID() const;
	virtual const VkVisualInfo *vkVisualInfo( VisualID vid ) const;
	virtual const VkVisualInfo *vkVisualInfo( const Visual *vis=NULL) const;
	virtual const VkVisualInfo *vkVisualInfo( const Widget w ) const;
	virtual const VkVisualInfo *vkVisualInfo( int index ) const;

      // The window is useful for such things as creating pixmaps.  A
      // suitable window will be created iff there is not already one for
      // this visual.
	virtual Window		window() const;	// Window w/same visual info


      // Debugging
	virtual void printAll() const;
	virtual void print () const;
	virtual void print (VisualID vid) const;
	virtual void print (const Visual *vis) const;
	virtual void print (const Widget w) const;
	virtual void print (int index) const;
	virtual void print (const VkVisualInfo* v) const;


    protected:


    private:
	struct os { long vid;			// VisualID
		    long transparent_type;	// CARD32
		    long pixel;			// CARD32
		    long level;};		// INT32

	Window getVisualWindow() const;

	// Set all visual info to the default
	void setDefaultInfo(Boolean forceNewCmap=FALSE);

	// An application should not use a pointer returned by vkVisualInfo() 
	// for writing.  However, the library needs to.  This function allows
	// that.  "vis" is not const, because otherwise we cannot do the
	// overload.
	VkVisualInfo *vkVisualInfo( Visual *vis=NULL ) const;

	void   VkVisualInit( );

	ArgList   _argList;		// So we can cache it
	Colormap  _colormap;
	Boolean	  _colormapCreated;	// True iff we created it
	Display  *_dpy;
	int       _depth;
	Window	  _rootWindow;
	Screen   *_scr;
	Visual   *_visual;
	VkVisualInfo * _visualInfo;	// The current visual structure
	Widget    _widget;

// We keep derived infomation about all visuals is static data so that only
// the first instance that needs it has to create it.  Since we are not
// reference counting, this could show as a memory leak -- but only if you
// delete all of your VkVisual's before the end of your program.

	// This following is to keep track of windows that can be passed
	// to routines that use a window to determine visual information,
	// such as the XPM routines.  These are common to all instances.
	struct pixmapWindow { Visual *v; Window w; };
	static pixmapWindow *_window;		// Visual/window pairs
	static int _numWindows;			// How many pairs we have
	static int _maxWindows;			// How much room there is

	// Information about the SERVER_OVERLAY_VISUALS property
	static int	  _maxLevel, _minLevel;
	static ulong	  _overlayCnt;		// # of structs
	static ulong	  _overlayVisNum;	// # of 32-bit values
	static struct os *_overlayVisProp;	// --> property value

	// Miscellaneous other static variables
	static VkVisualInfo * _visualInfoList;	// A list of all the visuals
	static int        _numVkVisuals;	// How many visuals there are
	static int        _lastVkVisual;	// Last one retrieved
};

#endif // VKVISUAL_H
