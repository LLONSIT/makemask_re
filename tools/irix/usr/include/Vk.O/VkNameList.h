
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

//////////////////////////////////////////////////////////////////////////////
//
//	VkNameList Class Definition 
//
//
//////////////////////////////////////////////////////////////////////////////

#ifndef VKNAMELIST_H
#define VKNAMELIST_H

#include <Xm/Xm.h>

void FreeIdTable (char**);

class VkNameList {

    public:

	VkNameList ();
	VkNameList (const VkNameList&);
	VkNameList (char*);
	~VkNameList ();

	void clear	();

	void add	(char*);	             // dups input
	void add	(const VkNameList&);	     // dups input
        void addCommaSeparated (const char* list);   // dups input

	// Would like the following to be "remove (char*, int=1), but that
	// would change the signature, causing binary compatibility
	// problems.  You can get the same effect by
	//    "remove (getIndex (char*), int=1)"
	void remove	(char*);
	void remove	(int, int count=1);	// Remove several strings
	int getIndex	(const char *) const;	// Locate a string in the list

	void sort	();		// uses qsort
        void reverse	();
	void removeDuplicates ();

	int  size   () const { return _size; }
	int  exists (char*) const;	// returns 1 if char* matches atleast
					// 1 item in the list.

	VkNameList&  operator=	   (const VkNameList&);
	int	     operator==	   (const VkNameList&) const;

    // The following operators are problematical, because the allocate
    // storage that must be freed.  It is better to use the equivalent
    /// "getXxxxx" function, because then the need to free is clear.
    //
	char*	     operator[]	   (int index)		const;
	char*	     getString	   (int index)		const;

	VkNameList   operator[]	   (char *subString)	const;
	VkNameList*  getSubstrings (char *subString)	const;

	operator     char**	   ()			const;
	char**	     getStringTable()			const;

	operator     XmStringTable ()			const;
	XmStringTable getXmStringTable()		const;
	static void  freeXmStringTable (XmStringTable);



	char*	 mostCommonString () const;

	virtual VkNameList* completeName (char* name, char*& completedName, int& nMatching);
	// attempt to complete <name>
	//
	//----------------------------------------------------------------------
	// condition		return val    completedName 	    nMatching
	//----------------------------------------------------------------------
	// no match		null list     longest sub-string    0
	//				      matching at least one 
	//----------------------------------------------------------------------
	// more than one	all those     most common string    # of matches
	// match		who match     among the matched
	//
	//----------------------------------------------------------------------
	// exactly one match	matched	      copy of matched	    1
	//			(completed)   string
	//			string
	//----------------------------------------------------------------------

    private:

	char**	_names;
	int	_size;

};

#endif /* VKNAMELIST_H */
