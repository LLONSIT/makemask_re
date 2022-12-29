#ifndef VKCMDFACTORY_H
#define VKCMDFACTORY_H

#include <Vk/VkCallbackObject.h>
#include <Vk/VkCmd.h>

class VkComponent;
class VkCmdManager;

#ifndef Boolean
typedef char Boolean;
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef NULL
#define NULL 0L
#endif

/*******************************************************
CLASS
    VkCmdFactory
    
    A class that produces VkCmd objects and also serves as a liason
    between cmds and VkComponent interfaces.

OVERVIEW

   The VkCmdFactory is an optional class that provides some useful
   services for applications that use VkCmd objects. Although VkCmd
   objects can be executed directly or via a VkCmdManager, the
   VkCmdFactory is useful when commands can be executed from multiple
   sources. For example, some applications might make an operation
   available to the user from a menu bar, a toolbar, a popup menu, and
   perhaps other parts of a user interface. A VkCmdFactory provides a
   central object that multiple interfaces can communicate with to
   launch the same command. 

   Any VkComponent can register itself with a VkCmFactory object, to
   track the availability of the command. If the VkCmdFactory is
   deactivated, all registered components will be desensitized
   automatically. In addition, any VkComponent, registered or not, can
   register an cmdExecutedCallback member function with A VkCmdFactory
   object. This callback will be invoked when a command is executed by
   the Factory.

   A VkCmdFactory object can execute a VkCmd object instantiated by
   the application, but it is most useful in conjuntion with VkCmd
   objects that have registered themselves by name with the
   VkCmdRegistry. In this case, the name given to a VkCmdFactory
   instance specifies the name of the object to be
   created. Alternately, A VkCmdFactory object can be given a function
   to call to create a VkCmd object when one is needed.

CALLBACKS

    This class supports the following callbacks:

        activateStateChangedCallback
	cmdExecutedCallback

SEE ALSO

    VkCmd, VkToggleCmd, VkToggleCmdFactory, VkCmdManager, VkMenu,
    VkCmdIcon

******************************************************/


class VkCmdFactory : public VkCallbackObject {
    
  public:

    ////////////
    // A callback hook for objects that want to be 
    // notifified when a Command has been made
    // active or inactive
    static const char *const activeStateChangedCallback;

    ////////////
    // A callback hook for objects that want to be 
    // notifified when a Command has been executed
    static const char *const cmdExecutedCallback;

    ////////////
    // Constructor. The name specifie the name of a 
    // registered command (See VKCmdRegistry) to be executed
    VkCmdFactory ( const char *name,  
		   int active   = TRUE); 

    ////////////
    // Constructor. The creation proc provides a way
    // to create a specific type of command object
    // as needed
    VkCmdFactory ( VkCmdCreateProc  proc,
		   int active   = TRUE); 
    
    ////////////
    // Destructor
    virtual ~VkCmdFactory ();          

    ////////////
    // Create and return a VkCmd object, using either the
    // registered name, or the creation proc
    virtual VkCmd *create();

    ////////////
    // Create a command and hand it off to the given VkCmdManager for 
    // execution
    virtual VkCmdResult doit(VkCmdManager *cmdMgr, void *data= NULL);  

    ////////////
    // Create and execute a command
    virtual VkCmdResult doit(void *data = NULL);  

    ////////////
    // Make the command "active". Components associated with the
    // command will be made sensitive and the command will respond to
    // doit() calls
    virtual void activate();  

    ////////////
    // Make the command "inactive". Components associated with the
    // command will be made insensitive and the command will not
    // respond to doit() calls
    virtual void deactivate();

    ////////////
    // Register a VkComponent used to execute this command
    // The sensitivity of registered components can be bmanaged 
    // automatically by activating/deactivating this command
    void registerComponent ( VkComponent * );

    ////////////
    // Register a VkComponent used to execute this command and specify
    // a method that shoudl be called when this Cmd is executed or undone
    void registerComponent ( VkComponent *, VkCallbackMethod updateMethod);
    
    ////////////
    // Return TRUE if this object is active.    
    virtual Boolean isActive ();

    ////////////
    // Return the class  name of this object
    virtual const char * className () { return ( "VkCmdFactory" ); }

    ////////////
    // Return the name of this command
    const char *getName() { return _name; }

    ////////////
    // Return a label that could be used by an interface to this
    // command. Defaults to the name.
    virtual const char *getLabel();

    ////////////
    // Specify a VkCmdManager to use when executing commands. If given, there
    // is no need to supply one when calling run() or doit().
    virtual void setCmdManager(VkCmdManager *cm);

    ////////////
    // Return the Cmd Manager, if any, registered with this object
    VkCmdManager* getCmdManager() { return _cmdManager;}

    void setData(void *d) { _data = d;}
    void* getData() { return _data;}
    
  protected:

    char            *_name;
    Boolean          _active;
    VkCmdCreateProc  _createproc;
    VkCmdManager    *_cmdManager;
    void *_data;

  private:

    // This class is not intended to be copied.  Strangers will get a
    // compile-time error.  Because there is no implementing code, friends
    // and inadvertant local use will get an ld-time error.  If a copy
    // constructor or operator= is ever needed, simply write them and
    // make these entries public.
    VkCmdFactory(const VkCmdFactory&);
    VkCmdFactory &operator =(const VkCmdFactory&);
};

#endif
