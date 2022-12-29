/*
 * Copyright 1991-1996, Silicon Graphics, Inc.
 * ALL RIGHTS RESERVED
 *
 * UNPUBLISHED -- Rights reserved under the copyright laws of the United
 * States.   Use of a copyright notice is precautionary only and does not
 * imply publication or disclosure.
 *
 * U.S. GOVERNMENT RESTRICTED RIGHTS LEGEND:
 * Use, duplication or disclosure by the Government is subject to restrictions
 * as set forth in FAR 52.227.19(c)(2) or subparagraph (c)(1)(ii) of the Rights
 * in Technical Data and Computer Software clause at DFARS 252.227-7013 and/or
 * in similar or successor clauses in the FAR, or the DOD or NASA FAR
 * Supplement.  Contractor/manufacturer is Silicon Graphics, Inc.,
 * 2011 N. Shoreline Blvd. Mountain View, CA 94039-7311.
 *
 * THE CONTENT OF THIS WORK CONTAINS CONFIDENTIAL AND PROPRIETARY
 * INFORMATION OF SILICON GRAPHICS, INC. ANY DUPLICATION, MODIFICATION,
 * DISTRIBUTION, OR DISCLOSURE IN ANY FORM, IN WHOLE, OR IN PART, IS STRICTLY
 * PROHIBITED WITHOUT THE PRIOR EXPRESS WRITTEN PERMISSION OF SILICON
 * GRAPHICS, INC.
 */
//  -*- C++ -*-

/*
 *
 _______________________________________________________________________
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 |
 |   $Revision: 2.1 $
 |
 |   Description:
 |      This class defines a component for starting print processes.
 |
 |   Author(s): Dave Immel
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef SO_XT_PRINT_DIALOG_
#define SO_XT_PRINT_DIALOG_

#include <X11/Intrinsic.h>
#include <Xm/Xm.h>

#include <Inventor/SbBasic.h>
#include <Inventor/Xt/SoXtComponent.h>
#include <Inventor/misc/SoCallbackList.h>

class SbPList;
class SoNode;
class SoPath;
class SoGLRenderAction;
class SoXtPrintDialog;


// callback function prototypes
typedef void SoXtPrintDialogCB(void *userData, SoXtPrintDialog *dialog);

///////////////////////////////////////////////////////////////////////
//
// class: SoXtPrintDialog
//
///////////////////////////////////////////////////////////////////////

class SoXtPrintDialog : public SoXtComponent {
  public:
    // Constructors and destructor.
    SoXtPrintDialog(
	Widget parent = NULL,
	const char *name = NULL, 
	SbBool buildInsideParent = TRUE);
    SoXtPrintDialog(
        SoGLRenderAction *act,
	Widget parent = NULL,
	const char *name = NULL, 
	SbBool buildInsideParent = TRUE);
   ~SoXtPrintDialog();

    // Sets/gets the node to be used for printing
    void        setSceneGraph( SoPath *path );
    void        setSceneGraph( SoNode *root );

    SoNode      *getSceneGraph()   	{ return rootNode; }
    SoPath      *getSceneGraphPath()   	{ return rootPath; }

    void 	setGLRenderAction(const SoGLRenderAction *act);
    SoGLRenderAction *getGLRenderAction();

    // Sets the size of the printing
    void        setPrintSize( const SbVec2f &s );
    void        setPrintSize( const SbVec2s &s );

    // These two callbacks are used before and after a print
    // action is performed.
    inline void	setBeforePrintCallback(
			SoXtPrintDialogCB *f,
			void *userData = NULL);
    inline void	setAfterPrintCallback(
			SoXtPrintDialogCB *f,
			void *userData = NULL);

  protected:

    // This constructor takes a boolean whether to build the widget now.
    // Subclasses can pass FALSE, then call SoXtPrintDialog::buildWidget()
    // when they are ready for it to be built.
    SoXtPrintDialog(
	Widget parent,
	const char *name, 
	SbBool buildInsideParent, 
	SbBool buildNow);

    // redefine these
    virtual const char *    getDefaultWidgetName() const;
    virtual const char *    getDefaultTitle() const;
    virtual const char *    getDefaultIconTitle() const;
    
    SoNode          *rootNode;
    SoPath          *rootPath;
    SbBool          printDone;
    SbBool	    highQuality;
    SbBool	    portraitFormat;
    SbBool	    printerOutput, postScriptOutput;
    SbBool          nodeMostRecent;
    SbBool          WYSIWYGflag;
    Widget          messageWidget, printButton, quitButton;
    Widget	    messageLabelWidget, fileFormatWidget;
    Widget          toPrinterWidget, toPostScriptFileWidget, toRGBFileWidget;
    Widget          printerHorizSize, printerVertSize;
    Widget          postScriptHorizSize, postScriptVertSize;
    Widget          rgbHorizSize, rgbVertSize;
    Widget          printerDPIField, postScriptDPIField;
    Widget 	    rgbFilenameWidget, postScriptFilenameWidget;
    SbPList 	    *printers;
    char            *defaultPrinter;
    int	    	    whichPrinter;   	// index into printers list
    SbVec2f         printSize;
    SbVec2s         printRes;
    SoCallbackList  beforeList, afterList;
    SbBool          alreadyUpdated;

    void    	    print();	    	// called by printCallback
    void            getPrinterList();
    void            printToPostScript( SoNode *, char *, int, int );
    
    // Methods used to build the print dialog.
    void            buildToPrinterWidget( Widget parent );
    void            buildToPostScriptFileWidget( Widget parent );
    void            buildToRGBFileWidget( Widget parent );
    void            placeBottomOfDialog( SoXtPrintDialog * );
    void            buildRadioButton( char *,  char *, char *, int, int,
                            Widget, XtCallbackProc );
    void            buildSizeFields( char *, int, Widget, Widget &, Widget &,
                            XtCallbackProc, XtCallbackProc );
    void            buildDPIField( int, Widget, Widget &, XtCallbackProc );
    void            updateTextports();

    //
    // Callback routines.
    //
    static void     qualityCB(  Widget, SoXtPrintDialog *,
                              XmAnyCallbackStruct * );
    static void     pageFormatCB(  Widget, SoXtPrintDialog *,
                              XmAnyCallbackStruct * );
    static void     fileFormatCB(  Widget, SoXtPrintDialog *,
                              XmAnyCallbackStruct * );
    static void     printerHorizSizeCB(  Widget, SoXtPrintDialog *,
                              XmAnyCallbackStruct * );
    static void     printerVertSizeCB(  Widget, SoXtPrintDialog *,
                              XmAnyCallbackStruct * );
    static void     postScriptHorizSizeCB(  Widget, SoXtPrintDialog *,
                              XmAnyCallbackStruct * );
    static void     postScriptVertSizeCB(  Widget, SoXtPrintDialog *,
                              XmAnyCallbackStruct * );
    static void     rgbHorizSizeCB( Widget, SoXtPrintDialog *,
                              XmAnyCallbackStruct * );
    static void     rgbVertSizeCB(  Widget, SoXtPrintDialog *,
                              XmAnyCallbackStruct * );
    static void     printerDPICB(   Widget, SoXtPrintDialog *,
                              XmAnyCallbackStruct * );
    static void     postScriptDPICB( Widget, SoXtPrintDialog *,
                              XmAnyCallbackStruct * );
    static void     outputCB( Widget, SoXtPrintDialog *,
                              XmAnyCallbackStruct * );
    static void     printCB(  Widget, SoXtPrintDialog *,
                              XmAnyCallbackStruct * );
    static void     quitCB(   Widget, SoXtPrintDialog *,
                              XmAnyCallbackStruct * );
    static void	    listPick( Widget, SoXtPrintDialog *ml,
    	    	    	      XmAnyCallbackStruct * );

    // Widget for controlling the Print Style
    Widget          styleButton;
    int             currentStyle;

  private:
    // Builds the widget.
    Widget	    buildWidget(Widget parent);

    // this is called by both constructors
    void constructorCommon(SbBool buildNow);
};

// Inline methods
void
SoXtPrintDialog::setBeforePrintCallback(
    SoXtPrintDialogCB *f,
    void *userData )
{ 
    beforeList.clearCallbacks();
    beforeList.addCallback((SoCallbackListCB *) f, userData);
}

void
SoXtPrintDialog::setAfterPrintCallback(
    SoXtPrintDialogCB *f,
    void *userData )
{
    afterList.clearCallbacks();
    afterList.addCallback((SoCallbackListCB *) f, userData);
}


#endif /* SO_XT_PRINT_DIALOG_ */

