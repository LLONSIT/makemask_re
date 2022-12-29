#ifndef VkUNDOCMDFACTORY_H
#define VkUNDOCMDFACTORY_H

#include <Vk/VkCmdFactory.h>

/*******************************************************
CLASS
    VkUndoCmdFactory

    A command factory that can be used to support undo
    in menus or other interfaces

OVERVIEW




******************************************************/


class VkUndoCmdFactory : public VkCmdFactory {
    
  public:

    ////////////
    // Constructor.
    VkUndoCmdFactory ( const char *name ); 
    
    ////////////
    // Destructor
    virtual ~VkUndoCmdFactory ();          

    ////////////
    // Have the cmd manager associated with this command undo an item
    virtual VkCmdResult doit(void *data= NULL);  

    ////////////
    // Override this function so we can arrange to watch the
    // cmd manager for status changes
    virtual void setCmdManager(VkCmdManager *cm);

    ////////////
    // Called by the VkCmdManager when anything changes
    // used to update the active status when undo is or
    // is not available
    virtual void update(VkCallbackObject *, void *, void *);

    ////////////
    // Change the label for this command, triggering an update 
    // callback. NULL defaults back to the name.
    void setLabel(const char *label = NULL);

    ////////////
    // Return a label like Undo <Action>
    const char *getLabel();

  protected:

    char *_label;

  private:
    ////////////
    // Not used. 
    virtual VkCmdResult doit(VkCmdManager *cmdMgr, void *data= NULL);  

  private:

    // This class is not intended to be copied.  Strangers will get a
    // compile-time error.  Because there is no implementing code, friends
    // and inadvertant local use will get an ld-time error.  If a copy
    // constructor or operator= is ever needed, simply write them and
    // make these entries public.
    VkUndoCmdFactory(const VkUndoCmdFactory&);
    VkUndoCmdFactory &operator= (const VkUndoCmdFactory&);
};

#endif
