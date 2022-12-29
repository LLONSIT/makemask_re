#ifndef VKTOGGLECMD_H
#define VKTOGGLECMD_H

#include <Vk/VkCmd.h>

class VkToggleCmdFactory;

/*******************************************************
CLASS
    VkToggleCmd

    A simple two state command used in conjuntion with the
    VkToggleFactory class. VkToggleCmd is rarely used
    directly. Subclass VkToggleCmdFactory instead.

******************************************************/

class VkToggleCmd : public VkCmd {

    VK_CMD_DECLARE;

  public:

    ////////////
    // Constructor.
    VkToggleCmd (); 

    ////////////
    // Destructor
    virtual ~VkToggleCmd ();          

    ////////////
    // Execute a command. 
    virtual VkCmdResult doit();  

    ////////////
    //  Undo a command. 
    virtual void undoit();

    ////////////
    // Return a label for this command
    virtual const char *getLabel();

    ////////////
    // Attach a factory object to this command
    void setFactory(VkToggleCmdFactory *f) { _factory = f; }

  protected:
    
    VkToggleCmdFactory *_factory;

  private:

    // This class is not intended to be copied.  Strangers will get a
    // compile-time error.  Because there is no implementing code, friends
    // and inadvertant local use will get an ld-time error.  If a copy
    // constructor or operator= is ever needed, simply write them and
    // make these entries public.
    VkToggleCmd(const VkToggleCmd&);
    VkToggleCmd &operator= (const VkToggleCmd&);
};

#endif
