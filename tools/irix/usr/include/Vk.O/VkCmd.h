#ifndef VKCMD_H
#define VKCMD_H

#include <Vk/VkCmdRegistry.h>

enum  VkCmdResult { VkCmdUndoable, VkCmdNotUndoable, VkCmdTransparent, VkCmdFailed };

class VkCmdFactory;

/*******************************************************
CLASS
    VkCmd
    
     A simple Cmd object for supporting doable, redoable and undoable
     actions

OVERVIEW

    VkCmd is the simplest element in the set of ViewKit objects that
    support undoable commands. VkCmd can be subclassed to support
    commands that can be executed directly, or via a VkCmdManager
    object. Subclasses can override the doit() method to define how a
    command should be performed, and undoit() to define how it should
    be reversed. An optional redoit() method allows commands that need
    to perform an action differently if the command is repeated to do
    so. If not defined, this method defaults to calling doit().

    In the simplest usage, applications would subclass VkCmd to define
    doit() and undoit(), instantiate a Cmd object and call doit(), or
    udoit() as desired:

    VkCmd *cmd = new MyCmd();
    cmd->doit();

UNDO SUPPORT

    The main benefit of Cmd objects comes from the ability to
    undo commands. VkCmd can be used with the VkCmdManager to achieve
    this. One can ask the VkCmdManager to execute a cmd object:

    VkCmdManager *cmdManager = new VkCmdManager();

    cmdManager->run(new MyCmd());

    This places the cmd on an undo history list, if the cmd can be
    undone. Whether a command can be undone depends on the return
    value of the doit() method, which must be one of:


    VkCmdUndoable: The cmd is undoable, and is added to the undo
                   stack. if any cmds are currently available for redo,
		   the VkCmdManager flushes them.
    
    VkCmdNotUndoable: This cmd is not undoable. The VkCmdManager flushes
                      all cmds on the undo and redo stack

    VkCmdTransparent: The command does not affect the undo/redo stack.


    When used in conjunction with the VkCmdManager and VkMenu
    addUndoAction() and addRedoAction() methods, a VkCmd object should
    override the getLabel() method, to supply a label to appear in the
    Undo and Redo menu commands.

COMMAND REGISTRY

   Commands can also be executed by name, provided the command
   registers itself with the VkCmdRegistry, a globally available list
   that links unique names to a mechanism for creating command
   objects. Once registered, a command can be invoked by the
   VkCmdManager by name:

   cmdManager->run("CutCommand");

   To participate in this scheme, commands must register
   themselves. This is made easy by two macros. The class record
   should include the line:

   VK_CMD_DECLARE;

   in the public portion of the class record, and also include the
   line:

   VK_CMD_IMPLEMENT(ClassName, "ClassName");

   somewhere in the source file. The first argument is the class name,
   while the second is a unique identifier for this command, which is
   usually the class name as well.

   Before the first time the class is used, the program must call:

   ClassName::initClass();

   where ClassName is the same of the class. In the future, the should
   be a class that is able to extract and invoke the initClass()
   method from a DSO, allowing for "plugin" commands.

SEE ALSO

    VkCmdManager, VkCmdRegistry, VkCmdFactory, VkToggleCmd, 
    VkToggleCmdFactory

******************************************************/

class VkCmd {

  public:

    ////////////
    // Destructor
    virtual ~VkCmd ();          

    ////////////
    // Execute a command. 
    virtual VkCmdResult doit() = 0;  

    ////////////
    // Redo the command
    virtual void redoit();  

    ////////////
    //  Undo a command. 
    virtual void undoit();

    ////////////
    // Return the name of this command. The name is an identifier,
    // and should be unique.
    virtual const char *getName();

    ////////////
    // Return a label for this command. This label might appear
    // in an Undo/Redo command when the command is eliglble to
    // be executed.
    virtual const char *getLabel();

    ////////////
    // A hook to pass data when command is executed. The data type
    // must be agreed upon by caller and object. This is usually
    // called from a VkCmdFactory or VkCmdManager object.
    virtual void setData(void *);

  protected:
    
    ////////////
    // Constructor.
    VkCmd (); 

  private:

    // This class is not intended to be copied.  Strangers will get a
    // compile-time error.  Because there is no implementing code, friends
    // and inadvertant local use will get an ld-time error.  If a copy
    // constructor or operator= is ever needed, simply write them and
    // make these entries public.
    VkCmd(const VkCmd&);
    VkCmd &operator= (const VkCmd&);
};



// Use in a command's .h file.

#define VK_CMD_DECLARE                                      \
  public:                                                   \
    static VkCmd *create();                                 \
    static void initClass()


// Use in a command's c++ file
// by this macro.
#define VK_CMD_IMPLEMENT(CMD_CLASS, CMD_TOKEN)                         \
            VK_CREATE_OBJ_SOURCE(CMD_CLASS)                            \
            VK_INIT_CLASS_SOURCE(CMD_CLASS, CMD_TOKEN)

// You can use these sub-macros separately, if you want to write
// one of these routines by hand yourself.
#define VK_CREATE_OBJ_SOURCE(CMD_CLASS)                                  \
    /* static */                                                         \
    VkCmd * CMD_CLASS::create()                                          \
    {                                                                    \
        return (VkCmd *) (new CMD_CLASS);                                \
    }
    
#define VK_INIT_CLASS_SOURCE(CMD_CLASS, CMD_TOKEN)                       \
    /* static */                                                         \
    void CMD_CLASS::initClass()                                          \
    {                                                                    \
	 VkCmdRegistry::registerCmd(                                     \
	     CMD_TOKEN,                                                  \
  	     CMD_CLASS::create);                                         \
    }


#endif
