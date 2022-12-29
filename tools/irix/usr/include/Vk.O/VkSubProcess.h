////////////////////////////////////////////////////////////////////////////////
///////   Copyright 1992, Silicon Graphics, Inc.  All Rights Reserved.   ///////
//                                                                            //
// This is UNPUBLISHED PROPRIETARY SOURCE CODE of Silicon Graphics, Inc.;     //
// the contents of this file may not be disclosed to third parties, copied    //
// or duplicated in any form, in whole or in part, without the prior written  //
// permission of Silicon Graphics, Inc.                                       //
//                                                                            //
// RESTRICTED RIGHTS LEGEND:                                                  //
// Use,duplication or disclosure by the Government is subject to restrictions //
// as set forth in subdivision (c)(1)(ii) of the Rights in Technical Data     //
// and Computer Software clause at DFARS 252.227-7013, and/or in similar or   //
// successor clauses in the FAR, DOD or NASA FAR Supplement. Unpublished -    //
// rights reserved under the Copyright Laws of the United States.             //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
#ifndef _VKPROCESS_H
#define _VKPROCESS_H

#include <Xm/Xm.h>
#include <signal.h>
#include <Vk/VkCallbackObject.h>

// These classes implement the necessary logic for building
// reference counted objects and the associated pointers.

class VkSPCounted : public VkCallbackObject {
    friend class VkSPRPtr_base;
    int nreferences;    // number of references to this object
    void addRef()
        { nreferences++; }
    void delRef()
        {
            if (--nreferences <= 0)
              delete this;
        }
  public:
    VkSPCounted() : VkCallbackObject()
        { nreferences = 0; }
    virtual ~VkSPCounted();

  private:

    // This class is not intended to be copied.  Strangers will get a
    // compile-time error.  Because there is no implementing code, friends
    // and inadvertant local use will get an ld-time error.  If a copy
    // constructor or operator= is ever needed, simply write them and
    // make these entries public.
    VkSPCounted(const VkSPCounted&);
    VkSPCounted &operator= (const VkSPCounted&);
} ;

class VkSPRPtr_base {
  public:
    operator void*()
	{ return (void *)ptr; }
    VkSPRPtr_base& operator=(VkSPCounted *tp)
        { if (ptr) ptr->delRef();
          ptr = tp;
          if (ptr) ptr->addRef();
          return *this; 
        }
    VkSPRPtr_base& operator=(const VkSPRPtr_base& r)
        { if (ptr) ptr->delRef();
          ptr = r.ptr;
          if (ptr) ptr->addRef();
          return *this; 
        }


  protected:
    VkSPCounted *ptr;
    VkSPRPtr_base() { ptr = 0; }
    VkSPRPtr_base(const VkSPRPtr_base& r)
    {
	ptr = r.ptr;
	if (ptr) ptr->addRef();
    }
    VkSPRPtr_base(VkSPCounted *tp)
        { ptr = tp;
          if (ptr) ptr->addRef();
        }
    ~VkSPRPtr_base()
        { if (ptr)  ptr->delRef(); }
} ;

class	VkSubProcessRep;

class RPtr_VkSubProcessRep : public VkSPRPtr_base {
  public:	
    RPtr_VkSubProcessRep();	
    RPtr_VkSubProcessRep(VkSubProcessRep *tp);	
    RPtr_VkSubProcessRep(const RPtr_VkSubProcessRep& that) : VkSPRPtr_base(that) {} 
    ~RPtr_VkSubProcessRep();	
    RPtr_VkSubProcessRep& operator=(VkSubProcessRep *tp)	
        { *((VkSPRPtr_base *) this) = (VkSPCounted *) tp; 	
          return *this; }       
	
    VkSubProcessRep& operator *();	
    VkSubProcessRep *operator->();	
    int operator !()	
        { return !ptr; }	
};



typedef RPtr_VkSubProcessRep VkSubProcess;

class VkSubProcessPtrQueue;

class	VkProgram;
class	VkPipe;


class VkSubProcessRep : public VkSPCounted {
    public:
static	VkSubProcess	create( char*		cmd,
				int		killChildOnExit,
				int redirectIn);

        static const char *const  stdoutCallback;
        static const char *const  stderrCallback;
        static const char *const  exitCallback;

	/* Useful info about running process */
	pid_t		pid()	 const		{ return _pid; }
	int		exitStatus() const	{ return _exitStatus; }

	/* send a signal to the process */
	void		signal(int sig);

	/* kill off the process */
	void		kill(int sig = SIGTERM);

	int		stdinfd() const { return(_stdinfd); } 

	/* Let us use VkSubProcess without going to the Xt event loop */
        VkPipe*         getStdoutPipe() { return stdoutPipe; }
        VkPipe*         getStderrPipe() { return stderrPipe; }

	/* Actually create VkSubProcess */
	void		run();

    protected:

        const char **_argv;

       void handleExitCallback(VkCallbackObject *, void *, void * callData);

	/* Constructor and  destructor */
			VkSubProcessRep(const char*	prog,
					char **argv,
					int		killChildOnExit,
					int 		redirectIn);

			~VkSubProcessRep();


	/* exec() utility function */
	void		exec(const char*	argv[]);

	/* I/O file descriptors and pipes */
	int		in, out, err;
	VkPipe*		stdoutPipe;
	VkPipe*		stderrPipe;
	int		_stdinfd;

	/* Keep track of running children */
static	int		childCount;
	void		addChild();
static	void		deleteChild(XtPointer, int*, XtInputId*);
	void		processExited(int status);

	/* Ignore interrupt/quit while child is running */
static	SIG_PF		interruptHandler, quitHandler;
static	void		ignoreSignals();
static	void		restoreSignals();

	/* Handler for asynchronous termination of child */
static	void		childHandler(int, ...);
static	int		signalPipe[2];		// To signal termination

	/* Queue to hold list of active Child VkSubProcesses */
static	VkSubProcessPtrQueue	*children;

	/* Name of VkProgram being run */
	const char*	progname;
	const int	killChildOnExit;

	/* Variables generated internally */
volatile	pid_t	_pid;		// Process ID of child
volatile	int	_exitStatus;	// Exit status of child

	/* Static Initialization flag */
static	int		doneStaticInit;

  private:

    // This class is not intended to be copied.  Strangers will get a
    // compile-time error.  Because there is no implementing code, friends
    // and inadvertant local use will get an ld-time error.  If a copy
    // constructor or operator= is ever needed, simply write them and
    // make these entries public.
    VkSubProcessRep(const VkSubProcessRep&);
    VkSubProcessRep &operator= (const VkSubProcessRep&);
};

#endif
