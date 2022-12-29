////////////////////////////////////////////////////////////
// VkCmdList.h: Maintain a list of Cmd objects
////////////////////////////////////////////////////////////
#ifndef VKCMDLIST_H
#define VKCMDLIST_H

#include <Vk/VkCmd.h>


/*******************************************************
CLASS
    VkCmdList

    A VkCmd subclass that is a list of Cmds.

OVERVIEW

    The VkCmdList class is used internally by the VkCmd classes to
    maintain lists of Cmd objects. For example, VkUndoManager, which
    maintains a list of commands to be undone, is a subclass of
    VkCmdList. VkCmdList can also be used directly to compile lists of
    command objects that can be executed in sequence.

******************************************************/

class VkCmdList : public VkCmd {
    
  public:

    ////////////
    // Constructor

    VkCmdList ( );

    ////////////
    // Destructor destroys list, but not objects in list
    virtual ~VkCmdList();  

    ////////////
    // Invokes doit() on all Cmds on this list 
    virtual VkCmdResult doit();

    ////////////
    // Invokes undoit() on all Cmds on this list 
    virtual void undoit();

    ////////////
    // Invokes undoit() on all Cmds on this list 
    virtual void redoit();

    ////////////
    // Add a VkCmd object to the end of the list
    virtual void add ( VkCmd *cmd );

    ////////////
    // Remove the first instance of cmd on the list
    virtual void remove ( VkCmd *cmd );

    ////////////
    // Remove all entries from the list
    virtual void clear();

    ////////////
    // The number of command objects on the list
    int size() { return ( _numCmds );  }

    ////////////
    // Access an entry in the list, using an array subscript notation
    VkCmd *operator[] ( int i );

 protected:

    VkCmd** _contents; 
    int     _numCmds; 

  private:

    // This class is not intended to be copied.  Strangers will get a
    // compile-time error.  Because there is no implementing code, friends
    // and inadvertant local use will get an ld-time error.  If a copy
    // constructor or operator= is ever needed, simply write them and
    // make these entries public.
    VkCmdList(const VkCmdList&);
    VkCmdList &operator= (const VkCmdList&);
};

#endif
