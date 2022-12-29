#ifndef _MEDIA_VIEWER_H_
#define _MEDIA_VIEWER_H_

/*
 * Copyright 1995-1997, Silicon Graphics, Inc.
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

// forward references
class ResourceFile;
class ViewerManager;
class FtrTargets;

// base class
#include <Vk/VkComponent.h>

#if (_MIPS_SIM == _MIPS_SIM_NABI32)
static const char _defaultDBFile[] = "/usr/lib32/mediaw/mediawrc";
#else
static const char _defaultDBFile[] = "/usr/lib/mediaw/mediawrc";
#endif

class MediaViewer : public VkComponent
{
    public:
        MediaViewer(const char *vkname, Widget wParent,
            const char *dbFile = _defaultDBFile);
        virtual ~MediaViewer();
        virtual const char *className() { return "MediaViewer"; }

        // view a file
        virtual void viewFile(const char *filename);

        // view a piece of typed data
        virtual void viewData(const char *labelName,
            Atom typeAtom, void *data, unsigned long length);
        virtual void viewData(const char *labelName,
            const char *typeName, void *data, unsigned long length);

        // convenience accessors (use only after viewData())
        virtual const char *getFtrTypeName();
        virtual const char *getFtrDescription();
        virtual const char *getTargetName();

	// set to False to hide the viewer frame and label
	void showViewerFrame(Boolean);

	// RapidApp support
	static VkComponent *CreateMediaViewer(const char *, Widget);

    protected:
        virtual void viewFileI(const char *type, const char *name);
        virtual void viewError();

        // included classes
        ResourceFile *rf;
        FtrTargets *ftr;
        ViewerManager *vm;

    private:
	Boolean viewDirectory(const char* filename,
			      const char* dataName,
			      const char* targetType);

	static void viewDirInputProc(XtPointer clientData,
				     int* fd,
				     XtInputId* id);
	// for RapidApp
	static void *RegisterMediaViewerInterface();
};

#endif // _MEDIA_VIEWER_H_
