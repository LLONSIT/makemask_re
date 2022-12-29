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
#ifndef VKPREFITEM_H
#define VKPREFITEM_H

#include <Vk/VkComponent.h>

enum VkPrefItemType { PI_none, PI_group, PI_list, PI_radio, PI_text, PI_toggle,
		      PI_option, PI_custom, PI_empty, PI_label, PI_separator };

class VkPrefItem : public VkComponent {

   friend class VkPrefGroup;
   friend class VkPrefList;
   friend class VkPrefRadio;
   friend class VkPrefDialog;
   friend class VkPrefTabDialog;	// graphkit thing.
  
  public:

     ~VkPrefItem();
     virtual const char *className();
     virtual VkPrefItemType type();

     void activate()    { setActivated(TRUE); }
     void deactivate()  { setActivated(FALSE); }

     virtual Boolean changed();
     virtual Boolean isContainer();
     Dimension labelHeight();
     Dimension baseHeight();
     void setLabelHeight(Dimension h);
     void setBaseHeight(Dimension h);
     Widget labelWidget();

  protected:

    void buildLabel(Widget parent);
    Dimension getHeight(Widget w);
    void setHeight(Widget w, Dimension h);

    Widget   _labelWidget;
    char    *_baseName, *_labelName;
    Boolean  _activated, _homogeneous;
   
    VkPrefItem(const char *name);
    virtual void build(Widget parent);
    virtual void build(Widget labelParent, Widget baseParent) = 0;
    void installDestroyHandlers();
    virtual void updateValue() = 0;
    virtual void revertValue() = 0;
    virtual void setActivated(Boolean);
    virtual void deleteChildren();
    void    setHomogeneous(Boolean flag);

  private:

    static void labelDestroyedCallback(Widget, XtPointer, XtPointer);

  private:

    // This class is not intended to be copied.  Strangers will get a
    // compile-time error.  Because there is no implementing code, friends
    // and inadvertant local use will get an ld-time error.  If a copy
    // constructor or operator= is ever needed, simply write them and
    // make these entries public.
    VkPrefItem(const VkPrefItem&);
    VkPrefItem &operator= (const VkPrefItem&);
};


class VkPrefGroup : public VkPrefItem {

  public:

            VkPrefGroup(const char *name, 
       		       Boolean horizOrientation = False,
		       Boolean noLabel = False);
            ~VkPrefGroup();

    virtual void build(Widget parent);
    virtual void show();
    virtual void deleteChildren();
            void addItem(VkPrefItem *item);
    virtual Boolean okToQuit();
    virtual Boolean isContainer();
    virtual const char *className();
    virtual VkPrefItemType type();
    virtual Boolean changed();
    virtual Dimension baseHeight();
            VkPrefItem *item(int which);
           int size();
 
    virtual void updateValue();
    virtual void revertValue();

  protected:

    virtual void setActivated(Boolean v);


    virtual void build(Widget labelParent, Widget baseParent);

    void checkHomogeneous();
    virtual void buildVertical(Widget baseParent);
    virtual void buildHorizontal(Widget baseParent);

    Widget _leftStuff, _rightStuff;
    VkPrefItem **_itemList;
    int _itemCount, _itemListSize;
    Boolean _horiz, _noLabel;

  private:

    static void mapHandler(Widget w, XtPointer client_data, XEvent *event);

  private:

    // This class is not intended to be copied.  Strangers will get a
    // compile-time error.  Because there is no implementing code, friends
    // and inadvertant local use will get an ld-time error.  If a copy
    // constructor or operator= is ever needed, simply write them and
    // make these entries public.
    VkPrefGroup(const VkPrefGroup&);
    VkPrefGroup &operator= (const VkPrefGroup&);
};


class VkPrefList : public VkPrefGroup {

  public:

    VkPrefList(const char *name);
    ~VkPrefList();

    virtual void build(Widget parent);

    virtual const char *className();
    virtual VkPrefItemType type();

  protected:

     virtual void build(Widget labelParent, Widget baseParent);

  private:

    // This class is not intended to be copied.  Strangers will get a
    // compile-time error.  Because there is no implementing code, friends
    // and inadvertant local use will get an ld-time error.  If a copy
    // constructor or operator= is ever needed, simply write them and
    // make these entries public.
    VkPrefList(const VkPrefList&);
    VkPrefList &operator= (const VkPrefList&);
};


class VkPrefRadio : public VkPrefGroup {

  public:

    VkPrefRadio(const char *name, 
		Boolean horizOrientation = False,
   	        Boolean noLabel = False);
    ~VkPrefRadio();

    virtual void build(Widget parent);
    virtual const char *className();
    virtual VkPrefItemType type();

  protected:

     virtual void build(Widget labelParent, Widget baseParent);

  private:

    // This class is not intended to be copied.  Strangers will get a
    // compile-time error.  Because there is no implementing code, friends
    // and inadvertant local use will get an ld-time error.  If a copy
    // constructor or operator= is ever needed, simply write them and
    // make these entries public.
    VkPrefRadio(const VkPrefRadio&);
    VkPrefRadio &operator= (const VkPrefRadio&);
};


class VkPrefText : public VkPrefItem {


  public:

     VkPrefText(const char *name, int columns = 5);
     ~VkPrefText();
      virtual const char *className();

      virtual VkPrefItemType type();

      virtual Boolean changed();

      void setValue(const char *str);
      char *getValue();

  protected:

      int   _columns;
      char *_value;

      virtual void build(Widget labelParent, Widget baseParent);
      virtual void build(Widget parent);
      virtual void updateValue();
      virtual void revertValue();

  private:

    // This class is not intended to be copied.  Strangers will get a
    // compile-time error.  Because there is no implementing code, friends
    // and inadvertant local use will get an ld-time error.  If a copy
    // constructor or operator= is ever needed, simply write them and
    // make these entries public.
    VkPrefText(const VkPrefText&);
    VkPrefText &operator= (const VkPrefText&);
    
};


class VkPrefToggle : public VkPrefItem {

  public:

     VkPrefToggle(const char *name, Boolean forceLabelFormat = False);
     ~VkPrefToggle();
      virtual const char *className();
      virtual VkPrefItemType type();
      virtual Boolean changed();

      void setValue(Boolean v);
      Boolean getValue();

  protected:

     Boolean _value, _forceLabel;
     virtual void updateValue();
     virtual void revertValue();
     virtual void build(Widget labelParent, Widget baseParent);
     virtual void build(Widget parent);

  private:

    // This class is not intended to be copied.  Strangers will get a
    // compile-time error.  Because there is no implementing code, friends
    // and inadvertant local use will get an ld-time error.  If a copy
    // constructor or operator= is ever needed, simply write them and
    // make these entries public.
    VkPrefToggle(const VkPrefToggle&);
    VkPrefToggle &operator= (const VkPrefToggle&);
};


class VkPrefOption : public VkPrefItem {

  public:
    
    VkPrefOption(const char *name, int numEntries);
    ~VkPrefOption();
    
    void setValue(int index);
    int getValue();
    
    int size() { return _num; }
    void setSize(int numEntries);
    
    void setLabel(int index, const char *label);
    char *getLabel(int index);
    Widget getButton(int index) { return _buttons[index]; }
    
    virtual const char *className();
    virtual VkPrefItemType type();
    virtual Boolean changed();
    
  protected:
    
    Widget _pulldown, *_buttons;
    int _num, _size, _value;
    char **_labels;
    
    virtual void build(Widget labelParent, Widget baseParent);
    virtual void build(Widget parent);
    virtual void updateValue();
    virtual void revertValue();

  private:

    // This class is not intended to be copied.  Strangers will get a
    // compile-time error.  Because there is no implementing code, friends
    // and inadvertant local use will get an ld-time error.  If a copy
    // constructor or operator= is ever needed, simply write them and
    // make these entries public.
    VkPrefOption(const VkPrefOption&);
    VkPrefOption &operator= (const VkPrefOption&);
    
};


class VkPrefCustom : public VkPrefItem {

  public:

     VkPrefCustom(const char *name);
    ~VkPrefCustom();
     virtual const char *className();
      virtual VkPrefItemType type();
      virtual Boolean changed();

  protected:

    virtual void build(Widget labelParent, Widget baseParent);
    virtual void build(Widget parent);

    virtual void updateValue();
    virtual void revertValue();

  private:

    // This class is not intended to be copied.  Strangers will get a
    // compile-time error.  Because there is no implementing code, friends
    // and inadvertant local use will get an ld-time error.  If a copy
    // constructor or operator= is ever needed, simply write them and
    // make these entries public.
    VkPrefCustom(const VkPrefCustom&);
    VkPrefCustom &operator= (const VkPrefCustom&);
};


class VkPrefEmpty : public VkPrefCustom {

  public:

    VkPrefEmpty();
    ~VkPrefEmpty();
     virtual const char *className();

    virtual VkPrefItemType type();
    virtual Boolean changed();

  protected:

    virtual void build(Widget labelParent, Widget baseParent);
    virtual void build(Widget parent);

  private:

    // This class is not intended to be copied.  Strangers will get a
    // compile-time error.  Because there is no implementing code, friends
    // and inadvertant local use will get an ld-time error.  If a copy
    // constructor or operator= is ever needed, simply write them and
    // make these entries public.
    VkPrefEmpty(const VkPrefEmpty&);
    VkPrefEmpty &operator= (const VkPrefEmpty&);
};


class VkPrefLabel : public VkPrefItem {

  public:

    VkPrefLabel(const char *name);
    ~VkPrefLabel();
    virtual const char *className();

    virtual VkPrefItemType type();
    virtual Boolean changed();

  protected:
   
     virtual void build(Widget labelParent, Widget baseParent);
     virtual void build(Widget parent);
     virtual void updateValue();
     virtual void revertValue();

  private:

    // This class is not intended to be copied.  Strangers will get a
    // compile-time error.  Because there is no implementing code, friends
    // and inadvertant local use will get an ld-time error.  If a copy
    // constructor or operator= is ever needed, simply write them and
    // make these entries public.
    VkPrefLabel(const VkPrefLabel&);
    VkPrefLabel &operator= (const VkPrefLabel&);
};


class VkPrefSeparator : public VkPrefItem {
  
   public:

     VkPrefSeparator(const char *name);
     ~VkPrefSeparator();
     virtual const char *className();
     virtual VkPrefItemType type();
     virtual Boolean changed();

   protected:

     virtual void build(Widget labelParent, Widget baseParent);
     virtual void build(Widget parent);
     virtual void updateValue();
     virtual void revertValue();

  private:

    // This class is not intended to be copied.  Strangers will get a
    // compile-time error.  Because there is no implementing code, friends
    // and inadvertant local use will get an ld-time error.  If a copy
    // constructor or operator= is ever needed, simply write them and
    // make these entries public.
    VkPrefSeparator(const VkPrefSeparator&);
    VkPrefSeparator &operator= (const VkPrefSeparator&);
};


#endif
