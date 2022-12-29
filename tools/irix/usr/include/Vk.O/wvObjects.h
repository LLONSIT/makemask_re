// -*- c++ -*-
////////////////////////////////////////////////////////////////////////////////
///////   Copyright 1997  Silicon Graphics, Inc.  All Rights Reserved.   ///////
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
#pragma once
#ifndef wvObjects_H
#define wvObjects_H

// Needed because o32 doesn't define bool,  but n32 does
#ifndef _BOOL
#define _BOOL 1
typedef unsigned char bool;
static const unsigned char true = 1;
static const unsigned char false = 0;
#endif // _BOOL

#include <assert.h>
#include <time.h>		// for time_t
#include <stdlib.h>

#ifndef _XtIntrinsic_h
typedef char		Boolean;
#endif // _XtIntrinsic_h

#if defined(sgi) || defined(unix)
#define WV(x) VkWebViewer##x
#else
#define WV(x) SgHTMLedit##x
#endif

class WV(LoaderContext)
{
public:
  virtual void Spawn() = 0;
  virtual void Abort(const char *reason) = 0;
  virtual void SetCredentials(const char *credentials) = 0;
  virtual char *GetChallenge() = 0;
  virtual const char *Url() = 0;
};

//
// Class AVPair
//
// Used to store form information 
//
class WV(AVPair) {
public:
  WV(AVPair)() {};
  virtual ~WV(AVPair)();
};

class WV(AList) {
public:
  virtual const char* getAttribute(const char*, const char* = NULL) const = 0;
};

class wvPen;

class WV(Form) {
public:
  WV(AList)*		getAttributes();
  WV(AVPair)*		getField(void** iter); // *iter = NULL to start
  void			setField(const char* field, const char* value);
  void			setField(const WV(AVPair) *av);
  void			resetFields();
  // True to submit, False to reset
  void			submit(Boolean); 
};


// Convenient inline functions

inline long max(long a, long b) {
  return a > b ? a : b;
}

inline long min(long a, long b) {
  return a < b ? a : b;
}


//
// A helper class encapsulating a single cookie.
//
class WV(Cookie) {
protected:
  WV(Cookie)();
public:
  virtual ~WV(Cookie)();

  // Access methods to query a Cookie.
  virtual const char *	getName() const = 0;
  virtual const char *	getValue() const = 0;
  virtual time_t	getExpiration() const = 0;
  virtual const char *	getPath() const	= 0;
  virtual const char *	getDomain() const = 0;
  virtual Boolean	getWildcardDomain() const = 0;
  virtual Boolean	getSecure() const = 0;

  // A special expriation time for cookies that have session-duration only.
  enum { SESSION_EXPIRATION = -1 };

  // The cookie verifier is invoked just before a cookie is set, or on
  // demand.  A NULL VerifyProc is assumed to always return TRUE,
  // approving the cookie.
  class CookieVerifier {
  public:
    typedef Boolean (*VerifyProc) (const WV(Cookie)& cookie, 
				   const char *url,
				   void *& context);
    VerifyProc	proc;
    void *	context;
  };

  // The fileChanged notifier is invoked when the default cookie file
  // changes unexpectedly (perhaps because another browser is running).  
  // A NULL FileChangedProc is assumed to always return COMBINE_FILE.
  class FileChangedNotifier {
  public:
    typedef enum { 
      COMBINE_FILE,		// Merge with file and re-write the file.
				// This may resurrect deleted cookies.
      OVERWRITE_FILE,		// Replace file contents with our cookies.
      RELOAD_FILE,		// Replace our cookies with file contents,
				// discarding any unsaved changes.
      IGNORE_FILE		// Neither read nor write the cookie file.
				// Unsaved changes will remain unsaved.
    } Action;
    typedef Action (*FileChangedProc) (Boolean unsaved_changes,
				       const char *filename,
				       void *& context);
    FileChangedProc	proc;
    void *		context;
  };
};

class wvPoint {
public:
  wvPoint() {}
  wvPoint(int xx, int yy) {
    x = xx;
    y = yy;
  }
  wvPoint(const wvPoint& p) {
    assign(p);
  }
  wvPoint& operator=(const wvPoint& p) {
    assign(p);
    return *this;
  }
  void assign(const wvPoint& p) {
    x = p.x;
    y = p.y;
  }
  int	x, y;
};

template<class T> class wvPtr;

template<class T> class wvPtrObj {
  friend wvPtr<T>;
private:
  int	refCount;
  T	*obj;

  wvPtrObj(T *v) {
    obj = v;
    refCount = 1;
  }
  int	dec() {
    if (--refCount <= 0) {
      delete obj;
      return 1;
    }
    return 0;
  }
  void	inc() {
    refCount++;
  }	
};

template<class T> class wvPtr {
private:
  wvPtrObj<T>	*data;

  void		inc() { if (data != NULL) data->inc(); }
  void		dec() { if (data != NULL && data->dec()) delete data; }
public:
  wvPtr() { 
    data = NULL; 
  }
  wvPtr(T* t) { 
    data = new wvPtrObj<T>(t); 
  }
  wvPtr(const wvPtr<T>& t) {
    data = t.data;
    inc();
  }
  ~wvPtr() {
    dec();
    data = NULL;
  }

  wvPtr<T>& operator=(const wvPtr<T>& t) {
    dec();
    data = t.data;
    inc();
    return *this;
  }
  wvPtr<T>& operator=(T* t) {
    dec();
    data = (t != NULL) ? new wvPtrObj<T>(t) : NULL;
    return *this;
  }
  bool operator==(const wvPtr<T>& t) const {
    T* a = data != NULL ? data->obj : NULL;
    T* b = t.data != NULL ? t.data->obj : NULL;

    return a == b;
  }
  bool operator!=(const wvPtr<T>& t) const {
    T* a = data != NULL ? data->obj : NULL;
    T* b = t.data != NULL ? t.data->obj : NULL;

    return a != b;
  }
  operator 	T*() const {
    if (data == NULL)
      return NULL;
    return data->obj;
  }
  T*		operator->() {
    if (data == NULL)
      return NULL;
    return data->obj;
  }
  const T* 	operator->() const {
    if (data == NULL)
      return NULL;
    return (const T*) data->obj;
  }
  int		refCount() const {
    if (data == NULL) 
      return 0;
    else
      return data->refCount;
  }
};

class WV(Document) {
public:
  virtual ~WV(Document)() = 0;

  static wvPtr<WV(Document)>	
    create(wvPen* p, const char* buffer, const char* base_url);
  // No instance variables,  just functions for data access 
  // in subclasses
  unsigned int	formCount();
  void*		getForm(unsigned int);
  // Iter should be a pointer to NULL to start,  formGetData will allocate an iter and
  // free it after the last pair is returned.  This call will return NULL
  // like this:
  // iter_variable = NULL;
  // ... formGetData(form, &iter_variable);
  WV(AVPair) 	*formGetData(void* form, void** iter);
  // Pairs should be freed after calls to formSetData
  void		formSetData(void* form, WV(AVPair)*);
  void		formResetData(void* form);
};

#endif // wvObjects_H
