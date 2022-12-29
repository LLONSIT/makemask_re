////////////////////////////////////////////////////////////////////////////////
///////   Copyright 1992, Silicon Graphics, Inc.  All Rights Reserved.   ///////
//                                                                            //
// This is UNPUBLISHED PROPRIETARY SOURCE CODE of Silicon Graphics, Inc.;     //
// the contents of this file may not be disclosed to third parties, copied    //
// or duplicated in any form, in whole or in part, without the prior written  //
// permission of Silicon Graphics, Inc.                                       //
//                                                                            //
// RESTRICTED RIGHTS LEGEND:                                                  //
// Use,duplication or disclosure by the Government is subject to restrictions //
// as set forth in subdivision (c)(1)(ii) of the Rights in Technical Data     //
// and Computer Software clause at DFARS 252.227-7013, and/or in similar or   //
// successor clauses in the FAR, DOD or NASA FAR Supplement. Unpublished -    //
// rights reserved under the Copyright Laws of the United States.             //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
#ifndef _VK_LIST_SEARCH_
#define _VK_LIST_SEARCH_

#include <Xm/Xm.h>

typedef void (*VkListSetPosProc)(Widget, int, caddr_t);
typedef void (*VkListSetMiddlePosProc)(Widget, int, caddr_t);
typedef Boolean (*VkListIsViewablePosProc)(Widget, int, caddr_t);
typedef void (*VkListDeselectAllItemsProc)(Widget, caddr_t);
typedef void (*VkListSelectPosProc)(Widget, int, Boolean, caddr_t);

class VkListSearch {

  public:

    VkListSearch(Widget list, Widget text, Boolean usingVkList = False);
    ~VkListSearch();
    void setData(caddr_t d) { data = d; }
    void setListSetPos(VkListSetPosProc p) { listSetPos = p; }
    void setListSetMiddlePos(VkListSetMiddlePosProc p) { listSetMiddlePos = p; }
    void setListIsViewablePos(VkListIsViewablePosProc p) { listIsViewablePos = p; }
    void setListDeselectAllItems(VkListDeselectAllItemsProc p) { listDeselectAllItems = p; }
    void setListSelectPos(VkListSelectPosProc p) { listSelectPos = p; }
    
    static void search_change_stub(Widget widget, caddr_t tag,
				   XmAnyCallbackStruct *data);
    static void xmListSetPos(Widget w, int position, caddr_t data);
    static void xmListSetMiddlePos(Widget w, int position, caddr_t data);
    static Boolean xmListIsViewablePos(Widget w, int position, caddr_t data);
    static void xmListDeselectAllItems(Widget w, caddr_t data);
    static void xmListSelectPos(Widget w, int position, Boolean notify,
				caddr_t data);
    static void vkListSetPos(Widget w, int position, caddr_t data);
    static void vkListSetMiddlePos(Widget w, int position, caddr_t data);
    static void vkListDeselectAllItems(Widget w, caddr_t data);
    static void vkListSelectPos(Widget w, int position, Boolean notify,
				caddr_t data);
  private:

    void search_change(Widget widget, caddr_t tag, XmAnyCallbackStruct *data);
    Boolean do_search(int pos, char *value);
    
    Widget listWidget, textWidget;
    char *lastSearch;
    Boolean searchFailed;
    int selected_index;
    VkListSetPosProc listSetPos;
    VkListSetMiddlePosProc listSetMiddlePos;
    VkListIsViewablePosProc listIsViewablePos;
    VkListDeselectAllItemsProc listDeselectAllItems;
    VkListSelectPosProc listSelectPos;
    caddr_t data;

  private:

    // This class is not intended to be copied.  Strangers will get a
    // compile-time error.  Because there is no implementing code, friends
    // and inadvertant local use will get an ld-time error.  If a copy
    // constructor or operator= is ever needed, simply write them and
    // make these entries public.
    VkListSearch(const VkListSearch&);
    VkListSearch &operator= (const VkListSearch&);
};

#endif
