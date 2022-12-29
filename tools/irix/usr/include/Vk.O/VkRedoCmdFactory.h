#ifndef VKREDOCMDFACTORY_H
#define VKREDOCMDFACTORY_H

#include <Vk/VkUndoCmdFactory.h>

class VkRedoCmdFactory : public VkUndoCmdFactory {
    
  public:

    ////////////
    // Constructor.
    VkRedoCmdFactory ( const char *name ); 

    ////////////
    // Destructor
    virtual ~VkRedoCmdFactory ();          


    ////////////
    // Have the cmd manager associated with this command redo an item
    virtual VkCmdResult doit(void *data = NULL);  

    ////////////
    // Called by the VkCmdManager when anything changes
    // used to update the active status when redo is or
    // is not available
    virtual void update(VkCallbackObject *, void *, void *);

  private:

    ////////////
    // Not used
    virtual VkCmdResult doit(VkCmdManager *cmdMgr, void *data= NULL);  

  private:

    // This class is not intended to be copied.  Strangers will get a
    // compile-time error.  Because there is no implementing code, friends
    // and inadvertant local use will get an ld-time error.  If a copy
    // constructor or operator= is ever needed, simply write them and
    // make these entries public.
    VkRedoCmdFactory(const VkRedoCmdFactory&);
    VkRedoCmdFactory &operator= (const VkRedoCmdFactory&);
};

#endif
