#ifndef VK_CMD_ICON_H
#define VK_CMD_ICON_H

#include <Vk/VkExpComponent.h>

class VkCmdFactory;
class VkToggleCmdFactory;
class VkCmdManager;


/*******************************************************
CLASS
    VkCmdIcon

    Abstract class used in a VkIconPalette

OVERVIEW

    The VkCmdIcon is intended to be used in a VkIconPalette container,
    which allows icons to be rearranged, as well as dragged and
    dropped between palettes. The VkCmdIcon can also execute and track
    the state of an associated command object.

******************************************************/

class VkCmdIcon : public VkExpComponent {

  public:

    enum Type {
	PUSH,		// Single-click activation (default)
	TOGGLE		// Click to toggle state
    };


    ////////////
    // Callback invoked when this object is selected
    static const char *const actionCallback;

    ////////////
    // Constructor
    VkCmdIcon(const char *name, VkCmdFactory *);

    ////////////
    // Constructor
    VkCmdIcon(const char *name, VkToggleCmdFactory *);

    ////////////
    // Constructor
    VkCmdIcon(const char *name = "unknown");

    ////////////
    // Constructor
    VkCmdIcon(const char *name, Widget parent);

    ////////////
    // Copy constructor
    VkCmdIcon(const VkCmdIcon &copyFrom);

    ////////////
    // Destructor
    virtual ~VkCmdIcon();

    ////////////
    // Assignment operator
    VkCmdIcon& operator=(const VkCmdIcon& copyFrom);


    Pixmap getDragPixmap(int &width, int& height, int& depth);

    ////////////
    // Sets/returns the type of button
    void		setType(VkCmdIcon::Type t)	{ _type = t; }

    ////////////
    // Return the type of this button
    VkCmdIcon::Type	getType() const			{ return _type; }

    ////////////
    // Specify an XPM Pixmap description inclusing one for when the
    // icon is insensitive. The sensitive pixmap be installed using
    // VkSetHighlightingPixmap, which handles the arm color and
    // highlight color
    void setPixmap(const char **xpmpixmap, const char **insenspixmap = NULL);

    ////////////
    // Specify the filename of XPM Pixmap. This pixmap will
    // be installed using VkSetHighlightingPixmap, which
    // handles the arm color and highlight color
    void setPixmap(const char *filename, const char *insensfile = NULL);

    ///////////////////////
    // Invokes the Cmd associated with the button. This can be called
    // to simulate the action taken by a button press. 
    void		invokeAction();

    ///////////////////////////
    // Builds the widget for the button in the given parent widget
    virtual void  create(Widget parent);

    ///////////////////////////
    // Set a cmd object for this icon
    virtual void  setCmd(VkCmdFactory *cmd);

    ///////////////////////////
    // Set a toggle cmd object for this icon
    virtual void  setCmd(VkToggleCmdFactory *cmd);

    ////////////
    // Installed with VkCmd objects to automatically update
    // the icon
    void handleCmdUpdate(VkCallbackObject *cmd, void *, void *);

    ////////////
    // Specify an undo manager object for commands executed
    // from this button
    void setCmdManager(VkCmdManager *um) { _cmdManager = um; }

    ////////////
    // Set the data to be passed to the Cmd Factory object
    void setData(void *data) { _data = data; }

  protected:

    Type         _type;
    const char **_xpmdesc;
    const char **_xpminsens;
    const char  *_pixmapFile;
    const char  *_insensFile;
    VkCmdFactory   *_cmd;
    VkCmdManager   *_cmdManager;
    void           *_data;  // Data to be passed to cmdfactory

    static void  activateCallback(Widget, XtPointer, XtPointer);
};


#endif

