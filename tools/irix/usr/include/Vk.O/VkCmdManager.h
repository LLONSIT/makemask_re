#ifndef _VKCMDMANAGER_H_
#define _VKCMDMANAGER_H_

#include <Vk/VkCallbackObject.h>
#include <Vk/VkCmd.h>

class VkUndoManager;

#ifndef Boolean
#define Boolean char
#endif

/*******************************************************
CLASS
    VkCmdManager

    Execute commands, and support undo and redo

OVERVIEW

   The VkCmdManager class provides a central place for executing
   commands and managing them on a undo/redo stacks. The management of
   the VkCmdManager is left to the application, which may wish to have
   a single CmdManager, or multiple instances, depending on the
   application architecture. 

   The VkCmdManager class can execute a cmd given a VkCmd object, a
   VkCmdFactory object, or a idintifying string, if the VkCmd has been
   registered with the VkCmdRegistry. Commands are executed by calling
   run():

   cmdManager->run("CutCommand");

   an optional argument to all forms of run can be supplied to be
   passed to the command (via the VkCmd::setData() method) before the
   cmd is executed. This data is uninterpreted by the VkCmdManager,
   and must be agreed upon by the cmd object and the caller.

   Interaction with the undo management facilties of the VkCmdManager
   are most easily accessed by the VkMenu class's addUndoAction() and
   addRedoAction() methods. The methods connect an instance of
   VkCmdManager with the appropriate menu commands.

INCOMPLETE

   The VkCmdManager will offer support for journalling to and from a
   file when it is complete.

SEE ALSO

   VkCmd, VkCmdFactory, VkCmdRegistry, VkToggleCmd


******************************************************/

class VkCmdManager : public VkCallbackObject
{
  public:

    ////////////
    // Invoked before a cmd is executed
    static const char *const executeCmdCallback;

    ////////////
    // Invoked after a cmd is executed
    static const char *const cmdExecutedCallback;

    ////////////
    // Invoked if a cmd fails
    static const char *const cmdFailedCallback;

    ////////////
    // Constructor
    VkCmdManager();

    ////////////
    // Destructor
    virtual ~VkCmdManager();
    
    ////////////
    // Run a command by name
    VkCmdResult run(const char *name, void *data = NULL);
    
    ////////////
    // Execute a VkCmd object
    VkCmdResult run(VkCmd *cmd, void *data = NULL);

    ////////////
    // Execute a cmd, given a VkCmdFactory object
    VkCmdResult run(VkCmdFactory *ci, void *data = NULL);
    
    ////////////
    // Undo the last command
    void undo(void);

    ////////////
    // Redo the last undone command
    void redo(void);

    ////////////
    // Get the text associated with the item next to be undone
    const char *getUndoLabel();

    ////////////
    // Get the text associated with the item next to be redone
    const char *getRedoLabel();

    ////////////
    // Clear all Cmd objects from the undo stack
    void flushUndoStack(void);

    ////////////
    // Determine whether a given string represents a valid registered Cmd
    Boolean isCmd(char *name);

    ////////////
    // start logging of commands to the journal as commands are executed
    void startJournal(const char *journalPath = NULL);

    ////////////
    // Stop logging of commands to the journal as commands are executed
    void stopJournal(void);

    ////////////
    // read and execute commands from the journal
    void loadJournal(const char *journalPath = NULL);

    ////////////
    // check whether the current VkCmd can be undone
    Boolean canUndo(void);

    ////////////
    // check whether the current VkCmd can be undone
    Boolean canRedo(void);

  private:

    ////////////
    // undo stack and handler
    VkUndoManager *_undoManager;

  private:

    // This class is not intended to be copied.  Strangers will get a
    // compile-time error.  Because there is no implementing code, friends
    // and inadvertant local use will get an ld-time error.  If a copy
    // constructor or operator= is ever needed, simply write them and
    // make these entries public.
    VkCmdManager(const VkCmdManager&);
    VkCmdManager &operator= (const VkCmdManager&);
};

#endif
