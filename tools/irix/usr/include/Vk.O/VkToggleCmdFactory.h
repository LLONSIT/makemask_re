#ifndef VKTOGGLECMDFACTORY_H
#define VKTOGGLECMDFACTORY_H

#include <Vk/VkCmdFactory.h>
#include <Vk/VkCallbackObject.h>

class VkToggleState;

/*******************************************************
CLASS
    VkToggleCmdFactory

    A special subclass of VkCmdFactory that toggles between two states.

OVERVIEW

   The VkToggleCmdFactory class supports commands that toggle between
   two states. It can be used as-is, or subclassed. Executing a
   VkToggleCmdFactory cmd (doit()) simply toggles a state variable
   maintained by the class. The VkToggleCmdFactory automatically
   creates a VkToggleCmd object, which is recorded with a VkCmdManager
   object if one is provided, supporting undo and redo. 

   Unlike most other command scenarios, when using the
   VkToggleCmdFactory, the program is mostly unaware of the
   VkToggleCmd object. Instead programs can use the VkToggleCmdFactory
   object as the primary focus. This is because of the simple, and
   common nature of a 2-state command. Applications can subclass
   VkToggleCmdFactory and override set() and unset() to get
   notification of changes in state. Applications can also register
   updateCallbacks, which are invoked on each change of state.

   VkToggleCmdFactory objects can be registered directly with any
   VkMenu, producing a toggle menu item. Multiple instances of
   VkToggleCmdFactory can be registered a VkRadioCmdManager object to
   produce mutually exclusive states among the toggles.

   See also VkCmd, VkMenu::addCmd,  VkCmdIcon, VkRadioCmdManager.

******************************************************/

class VkToggleCmdFactory : public VkCmdFactory {

    friend class VkToggleCmd;

  public:

    ////////////
    // Constructor. Specify name, active/inactive, and initial
    // set state.
    VkToggleCmdFactory(const char *name  = "VkToggleCmd", 
		       Boolean set       = FALSE, 
		       const char *label = NULL, 
		       int active        = TRUE);
    
    ////////////
    // Destructor
    ~VkToggleCmdFactory();

    ////////////
    //  Return the current state
    Boolean isSet() { return _set; }

    ////////////
    // Set the state to TRUE
    virtual void set();

    ////////////
    // Set the state to FALSE
    virtual void unset();

    ////////////
    // Create and execute a command
    VkCmdResult doit(void *data = NULL);  

    ////////////
    // Create and execute a command, passing it to the
    // given cmd manager
    VkCmdResult doit(VkCmdManager *cmdMgr, void *data= NULL);  

    void setCmdMode(VkCmdResult m) { _mode = m; }

    virtual const char * className () { return ( "VkToggleCmdFactory" ); }

  protected:

    ////////////
    //
    const char *getLabel();

    char *_label;
    Boolean _set;
    VkCmdResult _mode;

  private:

    // This class is not intended to be copied.  Strangers will get a
    // compile-time error.  Because there is no implementing code, friends
    // and inadvertant local use will get an ld-time error.  If a copy
    // constructor or operator= is ever needed, simply write them and
    // make these entries public.
    VkToggleCmdFactory(const VkToggleCmdFactory&);
    VkToggleCmdFactory &operator= (const VkToggleCmdFactory&);
};


/*******************************************************
CLASS
    VkRadioCmdManager

    Manage a group  of mutually exclusive VkToggleCmdFactory objects

OVERVIEW
  
   VkRadioCmdManager can be used to tie together a set of
   VkToggleCmdFactory objects to enforce radio behavior between
   them. By enforcing the radio behavior at the semantic level of the
   Cmd object, the associated user Factory elements will automatically
   reflect the correct state. To use VkRadioCmdManager, simply
   instantiate an object and add each VkToggleCmdFactory object to it.

    See also VkCmd, VkToggleCmdFactory, VkCmdManager,
    VkMenu, VkCmdIcon.

******************************************************/

class VkRadioCmdManager : public VkCallbackObject  {

   public:

    ////////////
    // Constructor. If alwaysOneSet is TRUE, don't allow
    // all managed toggles to be FALSE at one time

    VkRadioCmdManager(Boolean alwaysOneSet = FALSE);

    ////////////
    // Add a VkToggleCmdFactory to the list of managed toggles
    //
    void add(VkToggleCmdFactory *);

    VkToggleCmdFactory *operator[] (int i);

    int size() { return _numCmds; }

   protected:

    ////////////
    // Internal callback used to track toggle cmds
    void toggleChangedCallback(VkCallbackObject*, void *, void*);

    Boolean _alwaysOneSet;

    VkToggleCmdFactory **_cmds;
    int                 _numCmds;

  private:

    // This class is not intended to be copied.  Strangers will get a
    // compile-time error.  Because there is no implementing code, friends
    // and inadvertant local use will get an ld-time error.  If a copy
    // constructor or operator= is ever needed, simply write them and
    // make these entries public.
    VkRadioCmdManager(const VkRadioCmdManager&);
    VkRadioCmdManager &operator= (const VkRadioCmdManager&);
};

#endif
