/*
 * Copyright 1991-1996, Silicon Graphics, Inc.
 * ALL RIGHTS RESERVED
 *
 * UNPUBLISHED -- Rights reserved under the copyright laws of the United
 * States.   Use of a copyright notice is precautionary only and does not
 * imply publication or disclosure.
 *
 * U.S. GOVERNMENT RESTRICTED RIGHTS LEGEND:
 * Use, duplication or disclosure by the Government is subject to restrictions
 * as set forth in FAR 52.227.19(c)(2) or subparagraph (c)(1)(ii) of the Rights
 * in Technical Data and Computer Software clause at DFARS 252.227-7013 and/or
 * in similar or successor clauses in the FAR, or the DOD or NASA FAR
 * Supplement.  Contractor/manufacturer is Silicon Graphics, Inc.,
 * 2011 N. Shoreline Blvd. Mountain View, CA 94039-7311.
 *
 * THE CONTENT OF THIS WORK CONTAINS CONFIDENTIAL AND PROPRIETARY
 * INFORMATION OF SILICON GRAPHICS, INC. ANY DUPLICATION, MODIFICATION,
 * DISTRIBUTION, OR DISCLOSURE IN ANY FORM, IN WHOLE, OR IN PART, IS STRICTLY
 * PROHIBITED WITHOUT THE PRIOR EXPRESS WRITTEN PERMISSION OF SILICON
 * GRAPHICS, INC.
 */
//  -*- C++ -*-

/*
 *
 _______________________________________________________________________
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 |
 |   $Revision: 2.6 $
 |
 |   Description:
 |	This file contains definitions of the SbString and SbName
 |	classes, which are useful variations on our friend, the
 |	character string.
 |
 |   Author(s)		: Paul S. Strauss, Nick Thompson
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef _SB_STRING_
#define _SB_STRING_

#include <Inventor/SbBasic.h>

#include <string.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SbString
//
//  "Smart" character strings, which allow things like concatenation
//  with the "+=" operator and automatic storage management.
//
//////////////////////////////////////////////////////////////////////////////

class SbString {
  public:

    // Default constructor
    SbString()				{ string = staticStorage; 
					  string[0] = '\0'; }

    // Constructor that initializes to given character string
    SbString(const char *str)		{ string = staticStorage;
					  *this = str; }

    // Constructor that initializes to given character string
    SbString(const char *str, int start, int end);

    // Constructor that initializes to given SbString
    SbString(const SbString &str)	{ string = staticStorage;
					  *this = str.string; }

    // Constructor that initializes to string formed from given integer.
    // For example, SbString(1234) gives the string "1234".
    SbString(int digitString);

    // Destructor
    ~SbString();

    // Returns a reasonable hash key for string
    uint32_t		hash()		{ return SbString::hash(string); }

    // Returns length of string
    int			getLength() const	{ return strlen(string); }

    // Sets string to be the empty string (""). If freeOld is TRUE
    // (default), any old storage is freed up
    void		makeEmpty(SbBool freeOld = TRUE);

    // Returns pointer to the character string
    const char *	getString() const	{ return string; }

    // Returns new string representing sub-string from startChar to
    // endChar, inclusive. If endChar is -1 (the default), the
    // sub-string from startChar until the end is returned.
    SbString		getSubString(int startChar, int endChar = -1) const;

    // Deletes the characters from startChar to endChar, inclusive,
    // from the string. If endChar is -1 (the default), all characters
    // from startChar until the end are deleted.
    void		deleteSubString(int startChar, int endChar = -1);

    // Assignment operator for character string, SbString
    SbString &		operator =(const char *str);
    SbString &		operator =(const SbString &str)
	{ return (*this = str.string); }

    // Concatenation operator "+=" for string, SbString
    SbString &		operator +=(const char *str);

    SbString &		operator +=(const SbString &str);

    // Unary "not" operator; returns TRUE if string is empty ("")
    int			operator !() const { return (string[0] == '\0'); }

    // Equality operator for SbString/char* and SbString/SbString comparison
    friend int		operator ==(const SbString &str, const char *s);

    friend int		operator ==(const char *s, const SbString &str)
	{ return (str == s); }


    friend int		operator ==(const SbString &str1, const SbString &str2)
	{ return (str1 == str2.string); }

    // Inequality operator for SbString/char* and SbString/SbString comparison
    friend int		operator !=(const SbString &str, const char *s);

    friend int		operator !=(const char *s, const SbString &str)
	{ return (str != s); }

    friend int		operator !=(const SbString &str1,
				    const SbString &str2)
	{ return (str1 != str2.string); }

  SoINTERNAL public:

    static uint32_t	hash(const char *s);    // Hash function

  private:
    char		*string;		// String pointer
    int			storageSize;

    // This is used if the string fits in a reasonably small space
#define SB_STRING_STATIC_STORAGE_SIZE		32
    char		staticStorage[SB_STRING_STATIC_STORAGE_SIZE];

    void		expand(int bySize);	// Makes more room
};

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SbNameEntry (internal to SB)
//
//  This is used to make lists of SbName instances.
//
//////////////////////////////////////////////////////////////////////////////


SoINTERNAL class SbNameEntry {

  public:
    // Returns TRUE if entry's string is empty ("")
    SbBool		isEmpty() const   { return (string[0] == '\0'); }

    // Returns TRUE if entry's string is same as passed string
    SbBool		isEqual(const char *s) const
	{ return (string[0] == s[0] && ! strcmp(string, s)); }

  private:
    static int		nameTableSize;	// Number of buckets in name table
    static SbNameEntry	**nameTable;	// Array of name entries
    static struct SbNameChunk *chunk;	// Chunk of memory for string storage

    const char		*string;	// String for this entry
    uint32_t		hashValue;	// Its hash value
    SbNameEntry		*next;		// Pointer to next entry

    // Initializes SbNameEntry class - done only once
    static void		initClass();

    // Constructor
    SbNameEntry(const char *s, uint32_t h, SbNameEntry *n)
	{ string = s; hashValue = h; next = n; }

    // Inserts string in table
    static const SbNameEntry *	insert(const char *s);

friend class SbName;
};

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SbName
//
//  An SbName is a character string that is stored in a special table.
//  When a string is stored in this table, a pointer to the storage is
//  returned. Two identical strings will return the same pointer. This
//  means that comparison of two SbNames for equality can be
//  accomplished by comparing their pointers!
//
//////////////////////////////////////////////////////////////////////////////


class SbName {
  public:
    // Default constructor
    SbName();

    // Constructor that initializes to given character string
    SbName(const char *s)		{ entry = SbNameEntry::insert(s); }

    // Constructor that initializes to given SbString
    SbName(const SbString &s)	{ entry = SbNameEntry::insert(s.getString()); }


    // Constructor that initializes to another SbName
    SbName(const SbName &n)			{ entry = n.entry; }

    ~SbName()					{}

    // Returns pointer to the character string
    const char		*getString() const	{ return entry->string; }

    // Returns length of string
    int			getLength() const   { return strlen(entry->string); }

    // Returns TRUE if given character is a legal starting character
    // for an identifier
    static SbBool 	isIdentStartChar(char c);

    // Returns TRUE if given character is a legal nonstarting
    // character for an identifier
    static SbBool	isIdentChar(char c);

    // Returns TRUE if given character is a legal starting character
    // for an SoBase's name
    static SbBool 	isBaseNameStartChar(char c);

    // Returns TRUE if given character is a legal nonstarting
    // character for an SoBase's name
    static SbBool	isBaseNameChar(char c);

    // Unary "not" operator; returns TRUE if string is empty ("")
    int			operator !() const   { return entry->isEmpty(); }

    // Equality operator for SbName/char* and SbName/SbName comparison
    friend int		operator ==(const SbName &n, const char *s)
	{ return n.entry->isEqual(s); }

    friend int		operator ==(const char *s, const SbName &n)
	{ return n.entry->isEqual(s); }

    friend int 		operator ==(const SbName &n1, const SbName &n2)
	{ return n1.entry == n2.entry; }

    // Inequality operator for SbName/char* and SbName/SbName comparison
    friend int		operator !=(const SbName &n, const char *s)
	{ return ! n.entry->isEqual(s); }

    friend int		operator !=(const char *s, const SbName &n)
	{ return ! n.entry->isEqual(s); }

    friend int 		operator !=(const SbName &n1, const SbName &n2)
	{ return n1.entry != n2.entry; }

  private:
    const SbNameEntry	*entry;		// Name string storage
};

#endif /* _SB_STRING_ */
