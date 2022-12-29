#ifndef VKCMDREGISTRY_H
#define VKCMDREGISTRY_H

class VkCmd;

typedef VkCmd* (*VkCmdCreateProc) ();

/*******************************************************
CLASS
    VkCmdRegistry

    A central location in which to register classes by name, for later
    use by VkCmdManager or VkCmdFactory objects. See VkCmd for more
    details.

******************************************************/


class VkCmdRegistry {
    
  public:

    ////////////
    // Default constructor.  Needed because of the private constructors
    VkCmdRegistry() {}

    ////////////
    // Register a command by providing a name and a function to be
    // called to create a command object
    static void registerCmd(const char *name, VkCmdCreateProc proc);

    ////////////
    // Create and return a new command object by name
    static VkCmd *create(const char *name);

    class VkCmdRecord {
      public:
	const char *_name;
	VkCmdCreateProc _proc;
	VkCmdRecord *_next;
    };

  private:

    // Use linked list for now. Should be a hash table.

    static VkCmdRecord *_list;

  private:

    // This class is not intended to be copied.  Strangers will get a
    // compile-time error.  Because there is no implementing code, friends
    // and inadvertant local use will get an ld-time error.  If a copy
    // constructor or operator= is ever needed, simply write them and
    // make these entries public.
    VkCmdRegistry(const VkCmdRegistry&);
    VkCmdRegistry &operator= (const VkCmdRegistry&);
};

#endif
