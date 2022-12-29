/********************************************************
Copyright 1995 by Silicon Graphics, Inc.

Permission to use, copy, modify, and distribute this
software and its documentation for any purpose and without
fee is hereby granted, provided that the above copyright
no- tice appear in all copies and that both that copyright
no- tice and this permission notice appear in supporting
docu- mentation, and that the name of SGI not be used in
advertising or publicity pertaining to distribution of the
software without specific prior written permission.
S.G.I. makes no representation about the suitability of
this software for any purpose. It is provided "as is"
without any express or implied warranty.

SGI DISCLAIMS ALL WARRANTIES WITH REGARD TO  THIS  SOFTWARE,
INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FIT-
NESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL SUN BE  LI-
ABLE  FOR  ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,  DATA  OR
PROFITS,  WHETHER  IN  AN  ACTION OF CONTRACT, NEGLIGENCE OR
OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION  WITH
THE USE OR PERFORMANCE OF THIS SOFTWARE.

********************************************************/

/********************************************************
  
  FACILITY: SGI-AccessControl extension

  MODULE: Privilege access modes and definitions

********************************************************/

/********************************************************

                      OVERVIEW 
POLICIES

    READ 
        An X client can read access any resource that the client's
        label dominates. 

    WRITE 
        An X client cannot modify any resource unless the label
        of the resource and the label of the client are equal.

    CREATE-DESTROY
        An X client cannot create or destroy any resource unless
        the label of the client and the label of the parent resource
        are equal.  Exceptions are when the parent is a public resource.

    PUBLIC OBJECTS 
        Static resources (public objects) are accessible to all clients
        but may not be modified by them.

    GLOBAL EXCEPTIONS 
        Appropriately privileged X clients may change any of the previous
        three policies.

PRIVILEGES

    PRIV_PUBLIC_ADMIN
        Client can modify public X server objects and resources.

    PRIV_SYS_TRUSTED_PATH
        Client is part of the Trusted Computing Base (TCB).
        
    PRIV_GET_TCB
    PRIV_SET_TCB
    
    PRIV_GET_MAC
    PRIV_SET_MAC

    PRIV_DEVICE_GRAB
        
********************************************************/

/********************************************************
  
Pixmap, Atom, Cursor, Colormap Objects

CREATE
DESTROY
WRITE
    Requesting X client label must equal X object label. 
    
READ
    Requesting X client label must dominate X object label. 
    
SET_MAC
    Requesting X client must have PRIV_SET_MAC privilege. 

GET_MAC
    Requesting X client must have PRIV_GET_MAC privilege, 
    and requesting X client label must dominate X object label
    
SET_TCB
    Requesting X client must have PRIV_SET_TCB privilege. 

GET_TCB
    Requesting X client must have PRIV_GET_TCP privilege, 
    and requesting X client label must dominate X object label

    
********************************************************/


/********************************************************

Window Objects

WRITE
    Requesting X client label must equal window label. 
    
READ
    Requesting X client label must dominate X window label.

CREATE
    Requesting X client label must equal parent window label unless
    parent is root window.  Any client may create a child window of a
    root window.

DESTROY
    Requesting X client label must equal window label.  Destroying root
    window requires PRIV_PUBLIC_ADMIN privilege. 

DESTROY_SUBWINDOWS
    If window is root window, requesting X client must have
    PRIV_PUBLIC_ADMIN privilege.  Otherwise, requesting X client
    label must equal window label. 

CHANGE_SAVE_SET
   Requesting X client must have PRIV_PUBLIC_ADMIN privilege.

REPARENT
   Requesting X client must have READ and WRITE access to source window,
   new parent window and previous parent window.  
   
********************************************************/

/********************************************************

Property Objects

READ
    Requesting X client must have READ access to X window label.
    Requesting X client label must dominate X property label.

WRITE (CHANGE/DESTROY)
    If window is root window, requesting X client must have
    PRIV_PUBLIC_ADMIN privilege, otherwise X client label must
    equal window label.  Requesting X client label must equal
    X property label. 
         
         
********************************************************/

/********************************************************

Selection Objects

READ
    Requesting X client must have READ access to X window label.
    Requesting X client label must dominate X property label.

WRITE (CHANGE/DESTROY)
    If window is root window, requesting X client must have
    PRIV_PUBLIC_ADMIN privilege, otherwise X client label must
    equal window label.  Requesting X client label must equal
    X property label. 
         
                         
********************************************************/
