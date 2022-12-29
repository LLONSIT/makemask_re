#ifndef VKUNDOMANAGER_H
#define VKUNDOMANAGER_H


#include <Vk/VkCmd.h>
#include <Vk/VkCallbackObject.h>

#ifndef Boolean
typedef char Boolean;
#endif

/*******************************************************
CLASS
    VkUndoManager

    A list of Cmd objects that supports undo and redo. This class is
    not used directly. Use the VkCmdManager class instead.

******************************************************/

class VkUndoManager {

  public:

    VkUndoManager();

    ////////////
    //  Undo the command at the top of the stack
    void undo();

    ////////////
    // Redo the last undone command
    void redo();
    
    ////////////
    // Add an item to the undo stack
    void add(VkCmd*);

    ////////////
    // Alias for add()
    void push(VkCmd* cmd) { add(cmd); }

    ////////////
    // Completely empty the stack
    void clear();

    ////////////
    // Clear all redoCmds
    void flushRedoCmds();

    ////////////
    // Get the current item at the top of the undo stack
    VkCmd *getNextUndoCmd();

    ////////////
    // Get the current candidate for redo
    VkCmd *getNextRedoCmd();

    ////////////
    // Get the current item at the top of the undo stack
    const char *getRedoLabel();

    ////////////
    // Get the current candidate for redo
    const char *getUndoLabel();

    ////////////
    // Set a maximum number of commands to be maintained on the list
    void setMaxStackSize(int limit) { _maxStackSize = limit; }


    ////////////
    // Return TRUE if a command can currently be undone
    Boolean canUndo(void);

    ////////////
    // Return TRUE if a command can curretly be redone
    Boolean canRedo(void);


    ////////////
    // Return a specific command on the list
    //
    VkCmd *operator[] ( int i );

    int size() { return _numCmds;}

  protected:

    VkCmd** _contents; 
    int     _numCmds; 
    int     _ptr;           // Points to current item
    int     _maxStackSize;  // Maximum levels of undo

  private:

    // This class is not intended to be copied.  Strangers will get a
    // compile-time error.  Because there is no implementing code, friends
    // and inadvertant local use will get an ld-time error.  If a copy
    // constructor or operator= is ever needed, simply write them and
    // make these entries public.
    VkUndoManager(const VkUndoManager&);
    VkUndoManager &operator= (const VkUndoManager&);
};

#endif

