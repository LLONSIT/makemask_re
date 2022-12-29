
//////////////////////////////////////////////////////////////
//
// Header file for DMFXDialog
//
//////////////////////////////////////////////////////////////
#ifndef _DM_FX_DIALOG_H
#define _DM_FX_DIALOG_H

#include <Vk/VkApp.h>
#include <Vk/VkGenericDialog.h>
#include <Vk/VkComponent.h>
#include "PremiereXAPI.h"
#include "fx_image_viewer.h"

///////////////////////////////////////////////////////
// DMFXDialogItem
///////////////////////////////////////////////////////

class DMFXDialogItem : public VkComponent {

    public:

	DMFXDialogItem(Widget, char *) {}
	~DMFXDialogItem() {}
	
    protected:
	
    private:
 
};


///////////////////////////////////////////////////////
// DMFXDialogToggle
///////////////////////////////////////////////////////

class DMFXDialogToggle : public DMFXDialogItem {
    
    public:
	DMFXDialogToggle(   Widget parent, 
		    char *name, 
		    Boolean set, 
		    Boolean activated);
	    
	~DMFXDialogToggle() {}

	Boolean getValue();
	void	setValue(Boolean value);
    
    protected:
	
    private:
    
};

///////////////////////////////////////////////////////
// DMFXDialogScale
///////////////////////////////////////////////////////

class DMFXDialogScale : public DMFXDialogItem {
    
    public:
	DMFXDialogScale(    Widget parent, 
		    char *name,
		    int value, 
		    int minimum,
		    int maximum, 
		    unsigned char orientation, 
		    Boolean activated);
	~DMFXDialogScale() {}

	int	getValue();
	void	setValue(int value);
    
    protected:
	
    private:
    
};

///////////////////////////////////////////////////////
// DMFXDialogImage
///////////////////////////////////////////////////////

class DMFXDialogImage : public DMFXDialogItem {
    
    public:
	DMFXDialogImage(    Widget parent, 
		    char *name,
		    unsigned int w,
		    unsigned int h,
		    Boolean allowPan, 
		    Boolean allowZoom, 
		    Boolean activated);
	~DMFXDialogImage();

	DMFXImageViewer *myImage;
	
    protected:
   
    private:
};





class DMFXDialog: public VkGenericDialog { 

    public:

	DMFXDialog ( const char * name, Widget parent, const String * resources );
	~DMFXDialog();
	const char *className();
	
	//
	// methods for adding components to dialog
	//			
	DMFXDialogScale	    *addScale ( char *name,
				int value, 
				int minimum,
				int maximum, 
				unsigned char orientation = XmHORIZONTAL, 
				Boolean activated = True);
			
	DMFXDialogImage	    *addImage ( char *name,
				unsigned int w,
				unsigned int h,
				Boolean allowPan = True, 
				Boolean allowZoom = True, 
				Boolean activated = True);
			
	DMFXDialogToggle    *addToggle (char *name,
				Boolean set = False, 
				Boolean activated = True);
			
	static const char *const changedCallback;
	
	Widget	getWorkAreaRowColumn()	{ return myWorkArea; }
	
	virtual VkDialogManager::VkDialogReason postAndWait (
		    const char *message	    = NULL, 
		    int ok		    = -1, 
		    int cancel		    = -1, 
		    int apply		    = -1, 
		    const char *helpString  = NULL, 		       
		    VkSimpleWindow *parent  = NULL,
		    Widget parentWidget	    = NULL);

	virtual Widget postBlocked ( 
		    const char      *message	    = NULL, 
		    XtCallbackProc   okCB	    = NULL, 
		    XtCallbackProc   cancelCB	    = NULL, 
		    XtCallbackProc   applyCB	    = NULL, 
		    XtPointer        clientData	    = NULL,
		    const char      *helpString	    = NULL, 		       
		    VkSimpleWindow  *parent	    = NULL,
		    Widget           parentWidget   = NULL);			       				 


	Widget postBlocked ( const char *msg, 
			   VkSimpleWindow *parent)
			   
			   { return postBlocked(msg, NULL, NULL, NULL, NULL, NULL, parent); }
	
	Widget postBlocked ( const char     *msg, 
			   const char     *helpString, 		       
			   VkSimpleWindow *parent)
			   
			   { return postBlocked(msg, NULL, NULL, NULL, NULL, helpString, parent); }
	
	Widget postBlocked ( const char      *msg, 
			   XtCallbackProc   okCB, 
			   XtPointer        clientData,
			   VkSimpleWindow  *parent = NULL)
			   
			   { return postBlocked(msg, okCB, NULL, NULL, clientData, NULL, parent); }
	
	Widget postBlocked ( const char      *msg, 
			   XtCallbackProc   okCB, 
			   XtPointer        clientData,
			   const char     *helpString, 		       
			   VkSimpleWindow  *parent = NULL)
			   
			   { return postBlocked(msg, okCB, NULL, NULL, clientData, helpString, parent); }
	
	
	Widget postBlocked ( const char     *msg, 
			   XtCallbackProc  okCB, 
			   XtCallbackProc  cancelCB, 
			   XtPointer       clientData,
			   VkSimpleWindow *parent = NULL)
			   
			   { return postBlocked(msg, okCB, cancelCB, NULL, clientData, NULL, parent); }
	
	Widget postBlocked ( const char     *msg, 
			   XtCallbackProc  okCB, 
			   XtCallbackProc  cancelCB, 
			   XtPointer       clientData,
			   char            *helpString,
			   VkSimpleWindow *parent = NULL)
			   
			   { return postBlocked(msg, okCB, cancelCB, NULL, clientData, helpString, parent); }
	
	Widget postBlocked ( const char     *msg, 
			   XtCallbackProc  okCB, 
			   XtCallbackProc  cancelCB, 
			   XtCallbackProc  applyCB, 
			   XtPointer       clientData,
			   VkSimpleWindow *parent)
			   
			   { return postBlocked(msg, okCB, cancelCB, applyCB, clientData, NULL, parent); }
	
	
	Widget postBlocked ( const char *msg, 
			   Widget parent)
			   
			   { return postBlocked(msg, NULL, NULL, NULL, NULL, NULL, NULL, parent); }
	
	Widget postBlocked ( const char     *msg, 
			   const char     *helpString, 		       
			   Widget parent)
			   
			   { return postBlocked(msg, NULL, NULL, NULL, NULL, helpString, NULL, parent); }
	
	Widget postBlocked ( const char      *msg, 
			   XtCallbackProc   okCB, 
			   XtPointer        clientData,
			   Widget parent)
			   
			   { return postBlocked(msg, okCB, NULL, NULL, clientData, NULL, NULL, parent); }
	
	Widget postBlocked ( const char      *msg, 
			   XtCallbackProc   okCB, 
			   XtPointer        clientData,
			   const char     *helpString, 		       
			   Widget parent)
			   
			   { return postBlocked(msg, okCB, NULL, NULL, clientData, helpString, NULL, parent); }
	
	
	Widget postBlocked ( const char     *msg, 
			   XtCallbackProc  okCB, 
			   XtCallbackProc  cancelCB, 
			   XtPointer       clientData,
			   Widget parent)
			   
			   { return postBlocked(msg, okCB, cancelCB, NULL, clientData, NULL, NULL, parent); }
	
	Widget postBlocked ( const char     *msg, 
			   XtCallbackProc  okCB, 
			   XtCallbackProc  cancelCB, 
			   XtPointer       clientData,
			   char            *helpString,
			   Widget parent)
			   
			   { return postBlocked(msg, okCB, cancelCB, NULL, clientData, helpString, NULL, parent); }
	
	Widget postBlocked ( const char     *msg, 
			   XtCallbackProc  okCB, 
			   XtCallbackProc  cancelCB, 
			   XtCallbackProc  applyCB, 
			   XtPointer       clientData,
			   Widget parent)
			   
			   { return postBlocked(msg, okCB, cancelCB, applyCB, clientData, NULL, NULL, parent); }


	VkDialogReason postAndWait (
		    const char      *message, 
		    const char      *helpString, 		       
		    VkSimpleWindow  *parent = NULL)
	
		    {
			return postAndWait( message, 
					    -1, -1, -1, 
					    helpString, parent, NULL);
		    }

	VkDialogReason postAndWait ( 
		    const char      *message, 
		    VkSimpleWindow  *parent) 
		    
		    {
			return postAndWait( message, 
					    -1, -1, -1, 
					    NULL, parent, NULL);
		    }
	
	VkDialogReason postAndWait (
		    const char      *message, 
		    const char      *helpString, 		       
		    Widget          parentWidget)
	
		    {
			return postAndWait( message, 
					    -1, -1, -1, 
					    helpString, NULL, parentWidget);
		    }

	VkDialogReason postAndWait (
		    const char      *message, 
		    Widget          parentWidget)
		    
		    {
			return postAndWait( message, 
					    -1, -1, -1, 
					    NULL, NULL, parentWidget);
		    }


    protected:
      
	virtual Widget createDialog ( Widget );
    
	void addWidgetToChangedCallback(    Widget w, 
					    String callback_name, 
					    XtPointer clientData);
  
	void addComponentToChangedCallback( VkComponent *comp, 
					    String callback_name, 
					    XtPointer clientData);
  
    private:
    
	Widget myDialog;
	Widget myWorkArea;
	
	static void widgetChangedCallback ( Widget, XtPointer, XtPointer );
};

#endif
