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
 |   $Revision: 2.8 $
 |
 |   Description:
 |	This file contains the definition of the SoInput class.
 |
 |   Classes:
 |	SoInput, SoInputFile (internal)
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_INPUT_
#define  _SO_INPUT_

#include <Inventor/misc/SoBasic.h>
#include <Inventor/SbDict.h>
#include <Inventor/SbPList.h>
#include <Inventor/SbString.h>
#include <Inventor/SoDB.h>

class SoNode;
class SoPath;
class SoBase;
class SoDB;
class SbStringList;

//////////////////////////////////////////////////////////////////////////////
//
//  Structure: SoInputFile (internal)
//
//  This structure holds info about an opened file for use in the SoInput
//  class.
//
//  One of the items is a dictionary that correlates reference names
//  in files to nodes and paths (SoBase instances).
//
//////////////////////////////////////////////////////////////////////////////

SoINTERNAL struct SoInputFile {
    SbString		name;		// Name of file
    SbString		fullName;	// Name of file with full path
    FILE		*fp;		// File pointer
    void		*buffer;	// Buffer to read from (or NULL)
    char		*curBuf;	// Current location in buffer
    size_t		bufSize;	// Buffer size
    int			lineNum;	// Number of line currently reading
    SbBool		openedHere;	// TRUE if opened by SoInput
    SbBool		binary;		// TRUE if file has binary data
    SbBool		readHeader;	// TRUE if header was checked for A/B
    SbBool		headerOk;	// TRUE if header was read ok
    SbDict		*refDict;	// Node/path reference dictionary
    SbBool		borrowedDict;	// TRUE if dict from another SoInput
    float		ivVersion;	// Version if standard Inventor file;
    SbString		headerString;	// The header string of the input file
    SoDBHeaderCB	*postReadCB;	// CB to be called after reading file
    void		*CBData;	// User data to pass to the postReadCB

    SoInputFile();			// Too complex for inlining
};

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoInput
//
//  This file contains the definition of the SoInput (input stream)
//  class. This class is used for reading Inventor data files; it
//  supports both ASCII (default) and binary formats. It skips over
//  Inventor comments (from '#' to end of line) and can stack input
//  files when file inclusion is encountered; when EOF is reached, the
//  stack is popped.
//
//  Another feature is file opening. This will open a named file,
//  looking for it in any of several user-specified directories.
//  Alternatively, the caller can specify a buffer in memory (and its
//  size) to read from.
//
//  SoInput also contains a dictionary that correlates node and path
//  pointers to temporary names written to files. This is so
//  references to previously defined nodes and paths are written
//  correctly.
//
//////////////////////////////////////////////////////////////////////////////

class SoInput {
 public:

    // Constructor (default SoInput reads from stdin)
    SoInput();

    // Destructor closes file if SoInput opened it.
    ~SoInput();

    // Adds a directory to list of directories to search to find named
    // files to open. Directories searched in order. By default, the list
    // contains just the current directory.
    static void		addDirectoryFirst(const char *dirName);
    static void		addDirectoryLast(const char *dirName);

    // Adds directories that are named in the value of the given
    // environment variable. Directories may be separated by colons
    // or whitespace in the value.
    static void		addEnvDirectoriesFirst(const char *envVarName);
    static void		addEnvDirectoriesLast(const char *envVarName);

    // Removes given directory from list.
    static void		removeDirectory(const char *dirName);

    // Clears list of directories, including the current directory.
    static void		clearDirectories();

    // Returns the current list of directories.
    static const SbStringList &getDirectories();

    // Sets initial file pointer to read from. Clears stack if necessary.
    void		setFilePointer(FILE *newFP);

    // Opens named file, sets file pointer to result. Clears stack if
    // necessary. Returns FALSE on error. If okIfNotFound is FALSE
    // (the default), it prints an error message if the file could not
    // be found.
    SbBool		openFile(const char *fileName,
				 SbBool okIfNotFound = FALSE);

    // Opens named file, pushes resulting file pointer onto stack.
    // Returns FALSE on error
    SbBool		pushFile(const char *fileName);

    // Closes all files on stack opened with openFile or pushFile
    void		closeFile();

    // Returns TRUE if currently open file is a valid file;
    // that is, it begins with a header that has been registered
    // with SoDB::registerHeader.
    SbBool		isValidFile();

    // Returns pointer to current file, or NULL if reading from buffer
    FILE *		getCurFile() const;

    // Returns full name of current file, or NULL if reading from buffer
    const char *	getCurFileName() const;

    // Sets up buffer to read from and its size
    void		setBuffer(void *bufPointer, size_t bufSize);

    // Returns number of bytes read from buffer. Returns 0 if not
    // reading from a buffer.
    size_t		getNumBytesRead() const;

    // Returns the header of the file being read
    SbString		getHeader();
    
    // Returns the Inventor version of the file being read.
    float		getIVVersion()	
	{ return curFile->ivVersion; }
    
    
  SoEXTENDER public:
    // Returns whether current file/buffer being read is binary
    SbBool		isBinary();

    // Reads next character from current file/buffer. Returns FALSE on
    // EOF or error.
    SbBool		get(char &c);

    // Reads next ASCII character from current buffer. Returns FALSE on
    // EOF or error.
    SbBool		getASCIIBuffer(char &c);

    // Reads next ASCII character from current file. Returns FALSE on
    // EOF or error.
    SbBool		getASCIIFile(char &c);

    // Reads next ASCII format hex value from current file/buffer.
    // Returns FALSE on EOF or error.
    SbBool		readHex(uint32_t &l);

    // Reads item of particular type from current file pointer/buffer. All
    // skip white space before reading and return FALSE on EOF or if
    // item could not be read.
    SbBool		read(char	    &c);
    SbBool		read(SbString       &s);
    SbBool		read(SbName	    &n, SbBool validIdent = FALSE);
    SbBool		read(int	    &i);
    SbBool		read(unsigned int   &i);
    SbBool		read(short	    &s);
    SbBool		read(unsigned short &s);
    // was ... C-api: name=readInt32
    //     but typedef makes this redundant.
    //SbBool		read(int32_t	    &l);
    // was ... C-api: name=readUInt32
    //     but typedef makes this redundant.
    //SbBool		read(uint32_t	    &l);
    SbBool		read(float	    &f);
    SbBool		read(double	    &d);
    SbBool		readBinaryArray(unsigned char *c, int length);
    SbBool		readBinaryArray(int32_t *l, int length);
    SbBool		readBinaryArray(float *f, int length);
    SbBool		readBinaryArray(double *d, int length);

    // Returns TRUE if current file/buffer is at EOF
    SbBool		eof() const;

  SoINTERNAL public:
    // 	Init function sets up global directory list
    static void		init();

    // Constructor that gets reference dictionary from another SoInput
    SoInput(SoInput *dictIn);

    // Fills in passed string to contain description of current
    // location in all open input files
    void		getLocationString(SbString &string) const;

    // Puts a just-read character or string back in input stream/buffer
    void		putBack(char c);
    void		putBack(const char *string);

    // Adds a reference to dictionary in current file.  This may also
    // add a reference to the global dictionary if addToGlobalDict is
    // TRUE (the default).
    void		addReference(const SbName &name, SoBase *base,
				     SbBool addToGlobalDict = TRUE);

    // Removes a reference to dictionary in current file.  This may
    // also remove a reference from the global dictionary.
    void		removeReference(const SbName &name);

    // Looks up a reference, returning the base pointer or NULL
    SoBase *		findReference(const SbName &name) const;

  private:
    static SbStringList *directories;	// Directory search path.
    SbPList		files;		// Stack of SoInputFiles (depth >=1)
    struct SoInputFile	*curFile;	// Top of stack
    SbString		backBuf;	// For strings that are put back
    int			backBufIndex;	// Index into backBuf (-1 if no buf)

    void                *tmpBuffer;     // Buffer for binary read from file
    char                *curTmpBuf;     // Current location in temporary buffer
    size_t              tmpBufSize;     // Size of temporary buffer

    char                backupBuf[8];   // Buffer for storing data that
                                        // has been read but can't be put back.
    SbBool              backupBufUsed;  // True if backupBuf contains data
    
    // Set the Inventor version number of the current file
    void		setIVVersion(float version) 
	{ curFile->ivVersion = version; }

    // Looks for named file and opens it. Returns NULL if not found.
    FILE *		findFile(const char *fileName,
				 SbString &fullName) const;

    // Initializes reading from file
    void		initFile(FILE *newFP, const char *fileName,
				 SbString *fullName, SbBool openedHere,
				 SbDict *refDict = NULL);

    // Checks current file for ASCII/binary header comment. Returns
    // FALSE if no header was found.
    SbBool		checkHeader();

    // Returns TRUE if reading from memory buffer rather than file
    SbBool		fromBuffer() const
	{ return (curFile->buffer != NULL); }

    // Skips over white space in input. Pops file if EOF is hit.
    // Returns FALSE on error.
    SbBool		skipWhiteSpace();

    // Pops current file from stack, if possible.
    SbBool		popFile();

    // Returns number of bytes left in current buffer
    size_t		freeBytesInBuf() const
	{ return (curFile->bufSize -
		  (curFile->curBuf - (char *) curFile->buffer)); }

    // Reads integer, unsigned integer, or floating-point number.
    // Returns FALSE on EOF or error
    SbBool		readInteger(int32_t &l);
    SbBool		readUnsignedInteger(uint32_t &l);
    SbBool		readReal(double &d);

    // Reads unsigned integer string into str. Accepts decimal, octal,
    // and hex integers. Returns FALSE on EOF or error
    SbBool		readUnsignedIntegerString(char *str);

    // Reads string of decimal or hexadecimal digits into string.
    // Returns number of bytes read.
    int			readDigits(char *string);
    int			readHexDigits(char *string);

    // Reads given character from buffer into string. Returns 0 or 1
    int			readChar(char *string, char charToRead);

    // Make room in the temporary buffer for reading from a binary file
    SbBool              makeRoomInBuf(size_t nBytes);

    // Convert datatypes to network format during writing
    void                convertShort(char *from, short *s);
    void                convertInt32(char *from, int32_t *l);
    void                convertFloat(char *from, float *f);
    void                convertDouble(char *from, double *d);
    void                convertShortArray( char *from, register short *to,
                             register int len);
    void                convertInt32Array( char *from, register int32_t *to,
                             register int len);
    void                convertFloatArray( char *from, register float *to,
                             register int len);
    void                convertDoubleArray( char *from, register double *to,
                             register int len);
friend class SoBase;
friend class SoDB;
};

#endif /* _SO_INPUT_ */
