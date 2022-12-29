#ifndef __SYS_ELF_H__
#define __SYS_ELF_H__

/*	Copyright (c) 1990, 1991 UNIX System Laboratories, Inc.	*/
/*	Copyright (c) 1984, 1986, 1987, 1988, 1989, 1990 AT&T	*/
/*	  All Rights Reserved  	*/
/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF     	*/
/*	UNIX System Laboratories, Inc.                     	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/
/*
 * Copyright 1992,2002 Silicon Graphics,  Inc.
 * ALL RIGHTS RESERVED
 * 
 * THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF SGI
 * The copyright notice above does not evidence any  actual  or
 * intended  publication of this source code and material is an
 * unpublished work by Silicon  Graphics,  Inc.  This  material
 * contains CONFIDENTIAL INFORMATION that is the property and a
 * trade secret of Silicon Graphics, Inc. Any use,  duplication
 * or  disclosure  not  specifically  authorized  in writing by
 * Silicon Graphics is  strictly  prohibited.  THE  RECEIPT  OR
 * POSSESSION  OF  THIS SOURCE CODE AND/OR INFORMATION DOES NOT
 * CONVEY ANY RIGHTS TO REPRODUCE, DISCLOSE OR  DISTRIBUTE  ITS
 * CONTENTS,  OR  TO MANUFACTURE, USE, OR SELL ANYTHING THAT IT
 * MAY DESCRIBE, IN WHOLE OR IN PART.
 * 
 * U.S. GOVERNMENT RESTRICTED RIGHTS LEGEND
 * Use, duplication or disclosure by the Government is  subject
 * to  restrictions  as  set  forth  in  FAR 52.227.19(c)(2) or
 * subparagraph (c)(1)(ii) of the Rights in Technical Data  and
 * Computer  Software  clause  at  DFARS 252.227-7013 and/or in
 * similar or successor clauses in the FAR, or the DOD or  NASA
 * FAR  Supplement.  Unpublished  --  rights reserved under the
 * Copyright Laws of the United States. Contractor/manufacturer
 * is Silicon Graphics, Inc., 2011 N. Shoreline Blvd., Mountain
 * View, CA 94039-7311
 */

/* WARNING:  This file is included in, and logically a part of,
 * /usr/include/elf.h.  The distribution of material between them
 * is artificial, generally reflecting the distinction between generic
 * and system-dependent, and may change.  Do not include this file
 * directly -- include /usr/include/elf.h instead.
 */

/*
 *	elf.h	file organization for Irix on MIPS
 *	----------------------------------------------------
 *
 *	(1) /usr/include/elf.h
 *		This is generally processor and operating system independent
 *		information, typically common to all elf files.
 *
 *	(2) /usr/include/sys/elf.h
 *		This is  IRIX and MIPS specific information.
 *
 *      The *_IRIX_* names are generally new names and
 *      have *_MIPS_* versions which are the traditional names.
 *      Continue to use the *_MIPS_* versions.
 *      Avoid using the *_IRIX_* names.
 *	
 */

#include <sys/elftypes.h> 

/* 
 * Random constants
 */

#define _TEXT_ALIGN 0x10000
#define _DATA_ALIGN 0x10000
#define ELF_IRIX_MAXPGSZ (64*1024)
#define ELF_IRIX_MINPGSZ (0x1000)

#define MS_ALIAS        0x1	/* ???? */


/* ====================================================================
 *
 * Elf header
 *
 * ====================================================================
 */

/*
 * e_type
 */

#define ET_IR	(ET_LOPROC + 0)	 /* file is a 32-bit or 64-bit WHIRL file*/



/* ====================================================================
 *
 * Elf auxilliary header  
 *
 * ====================================================================
 *
 * The Elf auxilliary header is new to Irix as of v7.4 of the compilers.
 *
 * This is an Irix-specific extension to the elf header; it is used to
 * hold information that should go into the elf header (because it describes
 * the format of the file AND needs to be in the first page) but for which
 * there is no reasonable field in the elf header that we can use.
 *
 * This record, if present, immediately follows the Ehdr.  It's presence
 * is indicated by either (or both) of two distinct methods:
 *
 *	(1) e_ehsize in the Ehdr is larger than the actual elf header;
 *	    the difference being the size of the auxilliary header.
 *
 *	(2) The immediate 4 bytes after the Ehdr holding the bytes 'IRIX'
 *
 * Or stated a little more precisely:
 *
 *	Let EH_P  be a pointer to the elfheader.
 *	Let EHX_P be a pointer to the first byte after the elfheader.
 *	
 *	(1)  EHX_P		== EH_P + sizeof(Elf_Ehdr)
 *	(2)  *EHX_P		== 'Irix'
 *	(3)  EHX_P->ex_exhsize	== EH_P->e_ehsize    - sizeof(Elf_Ehdr)
 *	(2)  EH_P->e_ehsize	== sizeof(Elf_EXhdr) + sizeof(Elf_Ehdr) 
 * 
 * ====================================================================
 */

#define	EX_NIDENT	4

#if (defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS) )
typedef struct {
	unsigned char	ex_ident[EX_NIDENT];	/* magic string = 'IRIX'*/
	Elf32_Half	ex_exhsize;		/* exhdr length in bytes*/
	Elf32_Half	ex_version;		/* exhdr version number	*/

	/* added in ex_version 1 */
	Elf32_Word	ex_eversion;		/* elf file version number */

} Elf_EXhdr;
#endif

/*
 *	ex_ident
 *
 *	Always defined to be the string 'IRIX'
 */
#if (defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS) )
#define	IS_ELFX(exhdr) ( 			\
		(exhdr).ex_ident[0]='I'  &&	\
		(exhdr).ex_ident[0]='R'  &&	\
		(exhdr).ex_ident[0]='I'  &&	\
		(exhdr).ex_ident[0]='X'  &&	\
		)
#endif

/*
 *	ex_version
 *
 *	Indicates the revision level of the Elf_EXhdr record.  In
 *	particular, whenever a new field is added to the Elf_EXhdr
 *	record, we bump the ex_version number.  This allows programs
 *	to know which fields in the record are valid.
 *
 *	EX_VERSION	CHANGE
 *	----------	-----------------------------------------------
 *	0		Initial checkin.
 *	1		Added	ex_version field.
 *
 */
#define	EX_VERSION	1

/*
 *	ex_eversion
 *
 *	This is the version number of the elf file format.  Every
 *	time we change/modify/add/delete anthing from the elf file
 *	format we increas this number.
 *
 *	It would be better to use the e_version field out of the actual
 *	Elf header record, but that field is, unfortunately, defined
 *	to be 1.  Therefore, we created a new version field.
 *
 *	Most object file utilities should not have to look at this
 *	field.
 *
 *	EX_EVERSION	CHANGE
 *	-----------	-----------------------------------------------
 *	0		Initial checkin
 *	1		Removed new section types from SHT_MIDPROC
 *			range and put back in the SHT_LOPROC range.
 *
 */
#define	EX_EVERSION	1



/*
 * e_flags -- used by Irix
 */

#define	EF_IRIX_ABI64		0x00000010	
	/* If the bit is set   (1) then this is a 64bit ABI file
	 * If the bit is clear (0) then this is a 32bit ABI file.
	 * If set, this is a 64bit ABI elf file using the LP64 data model.
	 * And if this is a WHIRL file, (ie. e_type == ET_IR) then this 
	 * holds 64bit-format WHIRL code.
	 *
	 * If not set, this is a 32bit ABI elf file using the ILP32 
	 * data model.  And if it is a WHIRL file, (ie. e_type == ET_IR) this 
	 * holds 32bit format WHIRL code.
	 *
	 * NOTE: This flag did not exist before MIPSpro7.4
	 * Applications should not test for this since many
	 * 64 bit objects won't have this flag.
	 * Test e_ident[EI_CLASS] for  ELFCLASS32 or ELFCLASS64
	 * instead (on IRIX this is the only reliable test). 
	 */


/* ====================================================================
 *
 * Program header
 *
 * ====================================================================
 */

/* ====================================================================
 *
 * Section Headers
 *
 * ====================================================================
 */

/* 
 * Special Irix section indices
 */

#define SHN_IRIX_ACOMMON	(SHN_LOPROC + 0)
#define SHN_IRIX_TEXT		(SHN_LOPROC + 1)
#define SHN_IRIX_DATA		(SHN_LOPROC + 2)
#define SHN_IRIX_SCOMMON	(SHN_LOPROC + 3)
#define SHN_IRIX_SUNDEFINED	(SHN_LOPROC + 4)
#define SHN_IRIX_LCOMMON	(SHN_LOPROC + 5)
#define SHN_IRIX_LUNDEFINED	(SHN_LOPROC + 6)


/*
 * sh_type
 *
 *	Irix section types are allocated starting at 
 *	SHT_LOPROC == 0x70000000 and increasing values.
 *
 *	NOTE: Not all of the defined section types are
 *	valid on all processor type nor on all versions
 *	of Irix.
 */
#define SHT_IRIX_LIBLIST	(SHT_LOPROC + 0)
#define SHT_IRIX_MSYM		(SHT_LOPROC + 1)
#define SHT_IRIX_CONFLICT	(SHT_LOPROC + 2)
#define SHT_IRIX_GPTAB		(SHT_LOPROC + 3)
#define SHT_IRIX_UCODE		(SHT_LOPROC + 4)
#define SHT_IRIX_DEBUG          (SHT_LOPROC + 5)
#define SHT_IRIX_REGINFO        (SHT_LOPROC + 6)

#ifdef __osf__
#define	SHT_IRIX_PACKAGE	(SHT_LOPROC + 7)
#define	SHT_IRIX_PACKSYM	(SHT_LOPROC + 8)
#endif /* __osf__ */

#define SHT_IRIX_RELD		(SHT_LOPROC + 9)
#define SHT_IRIX_DONTUSE	(SHT_LOPROC + 10)

#define SHT_IRIX_IFACE		(SHT_LOPROC + 11)
#define SHT_IRIX_CONTENT	(SHT_LOPROC + 12)
#define SHT_IRIX_OPTIONS	(SHT_LOPROC + 13)

#define SHT_IRIX_SHDR		(SHT_LOPROC + 16)
#define SHT_IRIX_FDESC		(SHT_LOPROC + 17)
#define SHT_IRIX_EXTSYM		(SHT_LOPROC + 18)
#define SHT_IRIX_DENSE		(SHT_LOPROC + 19)
#define SHT_IRIX_PDESC		(SHT_LOPROC + 20)
#define SHT_IRIX_LOCSYM		(SHT_LOPROC + 21)
#define SHT_IRIX_AUXSYM		(SHT_LOPROC + 22)
#define SHT_IRIX_OPTSYM		(SHT_LOPROC + 23)
#define SHT_IRIX_LOCSTR		(SHT_LOPROC + 24)
#define SHT_IRIX_LINE		(SHT_LOPROC + 25)
#define SHT_IRIX_RFDESC		(SHT_LOPROC + 26)

#define SHT_IRIX_DELTASYM	(SHT_LOPROC + 27)
#define SHT_IRIX_DELTAINST	(SHT_LOPROC + 28)
#define SHT_IRIX_DELTACLASS	(SHT_LOPROC + 29)

#define SHT_IRIX_DWARF		(SHT_LOPROC + 30)
#define SHT_IRIX_DELTADECL	(SHT_LOPROC + 31)
#define SHT_IRIX_SYMBOL_LIB	(SHT_LOPROC + 32)
#define SHT_IRIX_EVENTS        	(SHT_LOPROC + 33)
#define SHT_IRIX_TRANSLATE     	(SHT_LOPROC + 34)
#define SHT_IRIX_PIXIE     	(SHT_LOPROC + 35)
#define SHT_IRIX_XLATE		(SHT_LOPROC + 36)
#define SHT_IRIX_XLATE_DEBUG	(SHT_LOPROC + 37)
#define SHT_IRIX_WHIRL		(SHT_LOPROC + 38)
#define SHT_IRIX_EH_REGION	(SHT_LOPROC + 39)
#define SHT_IRIX_XLATE_OLD	(SHT_LOPROC + 40)
#define SHT_IRIX_PDR_EXCEPTION	(SHT_LOPROC + 41)

/* The next five section types are valid only on irix  */
#define SHT_IRIX_EXT            (SHT_LOPROC + 42)
#define SHT_IRIX_UNWIND         (SHT_LOPROC + 43)
#define SHT_IRIX_UNWIND_INFO    (SHT_LOPROC + 44)
#define SHT_IRIX_PLT            (SHT_LOPROC + 45)
#define SHT_IRIX_PLTOFF         (SHT_LOPROC + 46)
#define SHT_MIPS_XLATE_PIX_CORD	(SHT_LOPROC + 47)


#define SHT_IRIX_NUM		48
	/* SHT_IRIX_NUM is one more than the highest offset to SHT_LOCPROC;
	 * it is the number of extensions, but is *NOT* a section type.
	 */

/*
 * sh_flags
 */
#define SHF_IRIX_GPREL          0x10000000
#define SHF_IRIX_MERGE          0x20000000
#define SHF_IRIX_ADDR           0x40000000	/* Reserved for future	*/
#define SHF_IRIX_STRINGS        0x80000000	/* Reserved for future	*/
#define SHF_IRIX_NOSTRIP        0x08000000
#define SHF_IRIX_LOCAL          0x04000000
#define SHF_IRIX_NAMES          0x02000000	/* Reserved for future	*/
#define SHF_IRIX_NODUPE         0x01000000	/* Reserved for future	*/


/* ====================================================================
 *
 * Symbol table
 *
 * ====================================================================
 */

/*
 * Special Irix st_other
 */
#define STO_DEFAULT		0x0
#define STO_INTERNAL		0x1
#define STO_HIDDEN		0x2
#define STO_PROTECTED		0x3
#define STO_OPTIONAL		0x4
#define STO_SC_ALIGN_UNUSED	0xff	/* No longer used 		*/

/*
 * Special Irix st_info
 */
#define STB_SPLIT_COMMON	(STB_LOPROC+0)

/* ====================================================================
 *
 * .IRIX.options Section
 *
 * sh_type:	SHT_MIPS_OPTIONS 
 *
 * ====================================================================
 */

#if (defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS))
typedef struct
{
	Elf64_Byte	kind;		/* determines interpretation of the */
					/* variable part of descriptor	    */
	Elf64_Byte	size;		/* size of descriptor, incl. header */
	Elf64_Section	section;	/* section header index of section  */
					/* affected, 0 for global options   */
	Elf64_Word	info;		/* Kind-specific information	    */
} Elf_Options;
#endif


/*
 * 	Elf_Options.kind		Options descriptor kinds
 */
#define ODK_NULL                 0      /* Undefined */
#define ODK_MIPS_REGINFO         1      /* MIPS Register usage information */
#define ODK_REGINFO              1      /* MIPS Register usage information */
#define ODK_MIPS_EXCEPTIONS      2      /* MIPS Exception processing options  */
#define ODK_EXCEPTIONS		 2      /* MIPS Exception processing options  */
#define ODK_PAD                  3      /* Section padding options */
#define ODK_MIPS_HWPATCH         4      /* MIPS Hardware workarounds performed*/
#define ODK_HWPATCH		 4      /* MIPS Hardware workarounds performed*/
#define ODK_FILL                 5      /* The fill value used by the linker */
#define ODK_TAGS                 6      /* Space for desktop tools to write */
#define ODK_MIPS_HWAND           7      /* HW workarounds.'AND' when merging */
#define ODK_HWAND		 7      /* HW workarounds.'AND' when merging */
#define ODK_MIPS_HWOR            8      /* HW workarounds.'OR'  when merging */
#define ODK_HWOR		 8      /* HW workarounds.'OR'  when merging */
#define ODK_GP_GROUP             9      /* GP group for text/data sections */
#define ODK_IDENT               10      /* ID information */
#define ODK_PAGESIZE            12      /* Alternate segment page size */

#define ODK_SEGINFO             15      /* Used for large segment information */

/*
 *      Elf_Options.kind == ODK_PAD
 *
 *      masks for Elf_Options.info
 */
#define OPAD_PREFIX	0x1	
#define OPAD_POSTFIX	0x2
#define OPAD_SYMBOL	0x4

/*
 *      Elf_Options.kind == ODK_GP_GROUP
 *
 *      masks for Elf_Options.info
 */
#define OGP_GROUP	0x0000ffff	/* GP group number */
#define OGP_SELF	0x00010000	/* Self-contained GP groups */

/*
 *      Elf_Options.kind == ODK_PAGESIZE
 *
 *      masks for Elf_Options.info
 */
#define OPS_DATA	0x000000ff	/* Data (static/heap) pagesize */
#define OPS_STACK	0x0000ff00	/* Stack data pagesize */
#define OPS_TEXT	0x00ff0000	/* Text pagesize */
/*
 *	These bytes are exponents of 2, so 2**b gives the actual
 *	pagesize desired, except for the following three special
 *	values:
 */
#define OPS_NOSPEC	0x00	/* No specification */
#define OPS_DEFAULT	0x01	/* Use system default */
#define OPS_MAXSIZE	0x02	/* Use system maximum */
/* Other values smaller than the system minimum are to be ignored. */

/*
 *      Elf_Options.kind == ODK_MIPS_HWAND
 *      Elf_Options.kind == ODK_MIPS_HWOR
 *
 *	These option descriptors are used by the kernel and 
 *	various tools to track HW specific bugs/issues/features.
 *
 *	In addition to using the info word, it can also use the
 *	the following 8-bytes for more bit masks, if needed.
 *	This record is defined below as Elf_Options_Hw.
 *
 *	The ODK_HWAND option is used for those bits that should be
 *	AND'd by the linker when merged and the ODK_HWOR option is
 *	used for those bits that should be OR'd by the linker.
 *
 *	EXAMPLE:
 *      --------
 *	Suppose the kernel wanted to know if a program used CMOV 
 *	instructions.  We might define the following :
 *		#define	OHWA0_CMOV_CHECKED	0x00000001
 *		#define OHWO0_CMOV_PRESENT	0x00000001
 *
 *	Assume, for this example, that  'eo_hw_and'   and   'eo_hw_or'
 *	are pointers to the two different options.  If the compiler 
 *	checked an object and found it generated no CMOV instructions 
 *	it would generate the following:
 *		eo_hw_and->info |= OHWA0_CMOV_CHECKED;
 *		eo_hw_or->info  |= OHWO0_CMOV_PRESENT;
 *	
 *	The linker would merge these two options by AND'ing all HW_AND
 *	options and OR'ing all HW_OR options.  After all copies are merged
 *	by the linker the meaning of the fields would be:
 *
 *	    CHECKED  PRESENT	MEANING
 *		1	1	All objects checked, CMOVS in binary.
 *		1	0	All objects checked, no CMOVS in binary.
 *		0	1	Some objects checked, CMOVS in binary.
 *		0	0	Some objects checked, CMOVS may be in binary.
 *
 *	NOTES:
 *	------
 *	(1) Dummy defines are included below to indicate naming conventions
 *	    for these fields.
 *	(2) Often it will be appropriate to have both a CHECKED bit and
 *	    a PRESENT bit, but it is not required.  It is up to the 
 *	    implementors to make the choice.
 *	(3) This is a SGI specific feature.  These option words should
 *	    be ignored by any other vendor.
 *	(4) {A|O}0 refers to the info field;
 *	    {A|O}1 refers to the hwp_flags1 field;
 *	    {A|O}2 refers to the hwp_flags2 field.
 *      (5) Any name can be used for bit define's but here is a suggested
 *          naming convention:
 *              OHW{A|O}{0|1|2}_<topic>_{CHECKED|PRESENT}
 *
 * ====================================================================
 */
#if (defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS))
typedef struct
{
	Elf32_Word	hwp_flags1;	/* extra flags */
	Elf32_Word	hwp_flags2;	/* extra flags */
} Elf_Options_Hw;
#endif

/* ====================================================================
 *
 * Stucture for ODK_SEGINFO
 *
 * Kind:	ODK_SEGINFO
 * Size:	sizeof(struct Elf_Options) + sizeof(Elf_Options_Seginfo)
 * Section:	0
 * Info:	Index into the program header for this segment
 *
 *
 * ====================================================================
 */
#if (defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS))
typedef enum {
    OSEGINFO_UNKNOWN,	/* segment type not explictly known */
    OSEGINFO_TEXT,   	/* part of this segment has executable instructions */
    OSEGINFO_DATA,   	/* part of this segment has initialized data */
    OSEGINFO_LDATA,  	/* thread local data */
    OSEGINFO_BSS,    	/* uninitialized data only */
    OSEGINFO_SIZE    	/* number of specified types */
} op_seginfo_enum;

typedef struct
{
        Elf64_Xword     pagesize;   /* 2^x pagesize */
	Elf64_Word    	unused;	    /* padding for 8 byte alignment */
        Elf64_Half      timeout;    /* # of seconds to search for pagesize */
        Elf64_Byte      segtype;    /* See op_seginfo_enum above */
        Elf64_Byte      mandatory;  /* # requires the page sizing (0 false, 1 true)*/
} Elf_Options_Seginfo;
#endif


/* ====================================================================
 *
 * .interfaces Section
 *
 * sh_type:	SHT_*_IFACE
 * sh_link:	section header index of associated symbol table
 * sh_info:	0
 * attributes:	SHF_ALLOC, SHF_IRIX_NOSTRIP
 *
 * --- WARNING ---- WARNING ---- WARNING ---- WARNING ---- WARNING ----
 *
 *      TBD:  .interface section needs to be processor specific
 *		In particular the Elf_Ifd.fpmask won't work.
 *
 * ====================================================================
 */

#if (defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS))

typedef struct {
    Elf64_Word symbol;		/* symbol table index of subprogram, or 0 */
    Elf64_Half attrs;		/* Attributes: See list below */
    Elf64_Byte pcnt;		/* Parameter count */
    Elf64_Byte fpmask;		/* bit on indicates an FP parameter register */
} Elf_Ifd;

typedef Elf_Ifd Elf_Interface_Descriptor;  /* for compatibility */

/* Flags that can be set in the 'attrs' field of Elf_Interface_Descriptor */
#define SA_PROTOTYPED	0x8000	/* Does def or ref have prototype ? */
#define SA_VARARGS	0x4000	/* Is this a varargs subprogram ? */
#define SA_PIC		0x2000	/* Are memory references PIC? */
#define SA_DSO_ENTRY	0x1000	/* Is subprogram valid DSO entry? */
#define SA_ADDRESSED	0x0800	/* Is subprogram address taken? */
#define SA_FUNCTION	0x0400	/* Does subprogram return a result? */
#define SA_NESTED	0x0200	/* Is subprogram nested? */
#define SA_IGNORE_ERROR	0x0100	/* Ignore consistency errors? */
#define SA_DEFINITION	0x0080	/* Is this a definition (no just call)? */
#define SA_AT_FREE	0x0040	/* Is the at register free at all branches? */
#define SA_FREE_REGS	0x0020	/* Free register mask precedes parm profile */
#define SA_PARAMETERS	0x0010	/* Parameter profile follows descriptor? */
#define SA_ALTINTERFACE 0x0008	/* Alternate descriptor follows? */

/* Parameter descriptor masks */
#define PDM_TYPE	0x00ff	/* Fundamental type of parameter */
#define PDM_REFERENCE	0x4000	/* Reference parameter ? */
#define PDM_SIZE	0x2000	/* Followed by explicit 32-bit byte count? */
#define PDM_Qualifiers	0x0f00	/* Count of type qualifiers << 8 */

/* Parameter descriptor mask flags */
#define PDMF_REFERENCE  0x40
#define PDMF_SIZE       0x20
#define PDMF_Qualifiers 0x0f

/* Fundamental Parameter Types */
#define FT_unknown         0x0000
#define FT_signed_char     0x0001
#define FT_unsigned_char   0x0002
#define FT_signed_short    0x0003
#define FT_unsigned_short  0x0004
#define FT_signed_int32    0x0005
#define FT_unsigned_int32  0x0006
#define FT_signed_int64    0x0007
#define FT_unsigned_int64  0x0008
#define FT_pointer32       0x0009
#define FT_pointer64       0x000a
#define FT_float32         0x000b
#define FT_float64         0x000c
#define FT_float128        0x000d
#define FT_complex64       0x000e
#define FT_complex128      0x000f
#define FT_complex256      0x0010
#define FT_void            0x0011
#define FT_bool32          0x0012
#define FT_bool64          0x0013
#define FT_label32         0x0014
#define FT_label64         0x0015
#define FT_struct          0x0020
#define FT_union           0x0021
#define FT_enum            0x0022
#define FT_typedef         0x0023
#define FT_set             0x0024
#define FT_range           0x0025
#define FT_member_ptr      0x0026
#define FT_virtual_ptr     0x0027
#define FT_class           0x0028

/* Parameter Qualifiers (aka Modifiers)  */
#define MOD_pointer_to     0x01
#define MOD_reference_to   0x02
#define MOD_const          0x03
#define MOD_volatile       0x04
#define MOD_function       0x80
#define MOD_array_of       0x81

#endif

/* ====================================================================
 *
 * .liblist Section
 *
 * ====================================================================
 */

#if (defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS))
typedef struct
{
	Elf32_Word	l_name;
	Elf32_Word	l_time_stamp;
	Elf32_Word	l_checksum;
	Elf32_Word	l_version;
	Elf32_Word	l_flags;
} Elf32_Lib;
#endif


/*
 * l_flags  These flags exist in each liblist entry.
 * The dynamic section flag bit RHF_SGI_ONLY
 * must be on for most of these to be honored by rld(1).
 * LL_DELAY_LOAD is honored regardless of RHF_SGI_ONLY.
 * If RHF_SGI_ONLY is not on no version matches are done
 * (just as if LL_IGNORE_INT_VER were on).
 * 
 * Recall that a liblist entry has a version string with a single version,
 * while the dynamic section on a DSO has a version string with
 * possibly multiple versions listed (separated by :).  man dso for
 * more details on multiple versions.
 *
 * By default version matches do NOT consider the minor version number.
 *
 * LL_EXACT_MATCH means (if on) that only a DSO with exactly the
 * checksum and timestamp and version from the liblist entry
 * (which were gotten at static-link time but might have
 * been updated by rqs(1)) will match.
 *
 * LL_REQUIRE_MINOR means (if on) that the version match must
 * match the minor version number.
 *
 * LL_NONE is just a convenient name requesting the default checks.
 *
 * LL_DELAY_LOAD means  (if on) that  rld will not load the DSO
 * refered to by the liblist entry till something in the DSO
 * is called.
 *
 * LL_EXPORTS is ignored by rld. It informs that ld exported symbols 
 * from the liblist-entry DSO into the main DSO (that this
 * liblist entry is part of).
 *
 * LL_IGNORE_INT_VER means (if on) that all version checks
 * should be suppressed and the DSO accepted based on
 * name alone.
 *
 * LL_DELTA means that the DSO referenced is Delta C++.
 *
 */

#define LL_NONE			0
#define LL_EXACT_MATCH		0x1 
#define LL_IGNORE_INT_VER	0x2
#define LL_REQUIRE_MINOR	0x4
#define LL_EXPORTS		0x8
#define LL_DELAY_LOAD		0x10

#define LL_DELTA                0x20

/* ====================================================================
 *
 * .conflict Section
 *
 * ====================================================================
 */

#if (defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS))
typedef Elf32_Addr Elf32_Conflict;
#endif

#if (defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS))
extern Elf32_Conflict	_ConflictList [];
#endif

#define RLD_VERSION            1


/* ====================================================================
 *
 * .got Section
 *
 * ====================================================================
 */

#if (defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS))
typedef struct
{
	Elf32_Addr	g_index;
} Elf32_Got;


typedef struct
{
	Elf64_Addr	g_index;
} Elf64_Got;

extern Elf32_Got	_GlobalOffsetTable [];
extern Elf64_Got	_GlobalOffsetTable64 [];

#endif


/* ====================================================================
 *
 * .package Section
 *
 * Multiple package entries for the same package are allowed
 * in order to express out of order symbols in a package.
 *
 * ====================================================================
 */

#ifdef __osf__

#if (defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS))
typedef struct {
	Elf32_Word	pkg_name;	/* index into String Space of name */
	Elf32_Word	pkg_version;	/* index into String Space of version string */
	Elf32_Half	pkg_flags;	/* package flags */
} Elf32_Package;
#endif

#if (defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS))
extern Elf32_Package	_PackageList [];
#endif


/*
 * pkg_name --
 * index of a string that identifies the name of this package
 * implementation, which cannot be the null string; the offset is in
 * bytes of a zero terminated string from the start of the .dynstr section
 * pkg_version --
 * index of a string that identifies the version of this package
 * implementation, which may be the null string; the offset is in
 * bytes of a zero terminated string from the start of the .dynstr section
 * pkg_flags --
 * export flag means package is exported, import flag means package is imported,
 * both flags must be set if a package is exported and is also used by other
 * packages within the shared library.  continuance flag means that this
 * package entry defines additional symbols for a previously defined
 * package.  continuance entries must exactly match the original entry in each
 * field, except for the pkg_start, pkg_count, and continuance flag in the pkg_flags.
 * The conflict flag is a possibility for future support for symbol preemption.
 */

/*
 * pkg_flags
 */

#define PKGF_EXPORT	0x1
#define PKGF_IMPORT	0x2
/* #define PKGF_CONFLICT	0x8 */

#if (defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS))
typedef Elf32_Word Elf32_Package_Symbol;
#endif

#if (defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS))
#define	PACKSYM_NULL_INDEX	((Elf32_Word) 0)
#endif

#endif /* __osf__ */


/* ====================================================================
 *
 * .dynamic Section
 *
 * ====================================================================
 */


/* ====================================================================
 * ====================================================================
 *
 * 64-bit declarations
 *
 * ====================================================================
 * ====================================================================
 */

#define ELF64_FSZ_ADDR		8
#define ELF64_FSZ_HALF		2
#define ELF64_FSZ_OFF		8
#define ELF64_FSZ_SWORD		4
#define ELF64_FSZ_WORD		4
#define ELF64_FSZ_SXWORD	8
#define ELF64_FSZ_XWORD		8


/* ====================================================================
 *
 * ELF header
 *
 * ====================================================================
 */

#if (defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS))
typedef struct {
	unsigned char	e_ident[EI_NIDENT];	/* ident bytes */
	Elf64_Half	e_type;			/* file type */
	Elf64_Half	e_machine;		/* target machine */
	Elf64_Word	e_version;		/* file version */
	Elf64_Addr	e_entry;		/* start address */
	Elf64_Off	e_phoff;		/* phdr file offset */
	Elf64_Off	e_shoff;		/* shdr file offset */
	Elf64_Word	e_flags;		/* file flags */
	Elf64_Half	e_ehsize;		/* sizeof ehdr */
	Elf64_Half	e_phentsize;		/* sizeof phdr */
	Elf64_Half	e_phnum;		/* number phdrs */
	Elf64_Half	e_shentsize;		/* sizeof shdr */
	Elf64_Half	e_shnum;		/* number shdrs */
	Elf64_Half	e_shstrndx;		/* shdr string index */
} Elf64_Ehdr;
#endif


/* ====================================================================
 *
 * Program header
 *
 * ====================================================================
 */

#if (defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS))
typedef struct {
	Elf64_Word	p_type;		/* entry type */
	Elf64_Word	p_flags;	/* entry flags */
	Elf64_Off	p_offset;	/* file offset */
	Elf64_Addr	p_vaddr;	/* virtual address */
	Elf64_Addr	p_paddr;	/* physical address */
	Elf64_Xword	p_filesz;	/* file size */
	Elf64_Xword	p_memsz;	/* memory size */
	Elf64_Xword	p_align;	/* memory/file alignment */
} Elf64_Phdr;
#endif


/* ====================================================================
 *
 * Section Headers
 *
 * ====================================================================
 */

#if (defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS))
typedef struct {
	Elf64_Word	sh_name;	/* section name */
	Elf64_Word	sh_type;	/* SHT_... */
	Elf64_Xword	sh_flags;	/* SHF_... */
	Elf64_Addr	sh_addr;	/* virtual address */
	Elf64_Off	sh_offset;	/* file offset */
	Elf64_Xword	sh_size;	/* section size */
	Elf64_Word	sh_link;	/* misc info */
	Elf64_Word	sh_info;	/* misc info */
	Elf64_Xword	sh_addralign;	/* memory alignment */
	Elf64_Xword	sh_entsize;	/* entry size if table */
} Elf64_Shdr;
#endif


/* ====================================================================
 *
 * .symtab Section
 *
 * ====================================================================
 */

#if (defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS))
typedef struct {
	Elf64_Word	st_name;
	unsigned char	st_info;	/* bind, type: ELF_64_ST_... */
	unsigned char	st_other;
	Elf64_Half	st_shndx;	/* SHN_... */
	Elf64_Addr	st_value;
	Elf64_Xword	st_size;
} Elf64_Sym;
#endif


/*	The macros compose and decompose values for S.st_info
 *
 *	bind = ELF64_ST_BIND(S.st_info)
 *	type = ELF64_ST_TYPE(S.st_info)
 *	S.st_info = ELF64_ST_INFO(bind, type)
 */

#if (defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS))
#define ELF64_ST_BIND(info)		((info) >> 4)
#define ELF64_ST_TYPE(info)		((info) & 0xf)
#define ELF64_ST_INFO(bind,type)	(((bind)<<4)+((type)&0xf))
#endif


/* ====================================================================
 *
 * .rel, .rela Section
 *
 * WARNING:  The Elf64_Rel and Elf64_Rela structures must be identical
 * except for the r_addend field.
 *
 * --- WARNING ---- WARNING ---- WARNING ---- WARNING ---- WARNING ----
 *
 *      TBD:  .rel, .rela sections needs to be processor specific
 *
 * ====================================================================
 */

#if (defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS))

typedef struct {
	Elf64_Addr	r_offset;
	Elf64_Word	r_sym;		/* Symbol index */
	Elf64_Byte	r_ssym;		/* Special symbol */
	Elf64_Byte	r_type3;	/* 3rd relocation op type */
	Elf64_Byte	r_type2;	/* 2nd relocation op type */
	Elf64_Byte	r_type;		/* 1st relocation op type */
} Elf64_Rel;

typedef struct {
	Elf64_Addr	r_offset;
	Elf64_Word	r_sym;		/* Symbol index */
	Elf64_Byte	r_ssym;		/* Special symbol */
	Elf64_Byte	r_type3;	/* 3rd relocation op type */
	Elf64_Byte	r_type2;	/* 2nd relocation op type */
	Elf64_Byte	r_type;		/* 1st relocation op type */
	Elf64_Sxword	r_addend;
} Elf64_Rela;

/* Values for the r_ssym field: */
typedef enum {
    RSS_UNDEF	= 0,	/* Undefined */
    RSS_GP	= 1,	/* Context pointer (gp) value */
    RSS_GP0	= 2,	/* gp value used to create object being relocated */
    RSS_LOC	= 3	/* Address of location being relocated */
} Elf64_Rel_Ssym;

#endif

/*	The macros compose and decompose values for Rel.r_info, Rela.f_info
 *
 *	sym = ELF64_R_SYM(R.r_info)
 *	type = ELF64_R_TYPE(R.r_info)
 *	R.r_info = ELF64_R_INFO(sym, type)
 */

#if (defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS))
#define ELF64_R_SYM(info)	((info)>>8)
#define ELF64_R_TYPE(info)	((unsigned char)(info))
#define ELF64_R_INFO(sym,type)	(((sym)<<8)+(unsigned char)(type))
#endif


/* ====================================================================
 *
 * .conflict Section
 *
 * ====================================================================
 */

#if (defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS))
typedef Elf64_Addr Elf64_Conflict;

extern Elf64_Conflict   _ConflictList64 [];
#endif


/* ====================================================================
 *
 * .dynamic Section
 *
 * ====================================================================
 */

#if (defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS))
typedef struct {
	Elf64_Xword	d_tag;
	union {
		Elf64_Xword	d_val;
		Elf64_Addr	d_ptr;
	} d_un;
} Elf64_Dyn;
#endif


/* ====================================================================
 *
 * .liblist Section
 *
 * ====================================================================
 */

#if (defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS))
typedef struct
{
        Elf64_Word      l_name;
        Elf64_Word      l_time_stamp;
        Elf64_Word      l_checksum;
        Elf64_Word      l_version;
        Elf64_Word      l_flags;
} Elf64_Lib;
#endif



/*
 *	Any symbol definition in this file of the form
 *
 *		#define	  pre_MIPS_suf	pre_IRIX_suf
 *
 *	is included for backwards compatibility.  New code 
 *	should use the   pre_IRIX_suf   symbol.
 *
 */

/* 
 * Random constants
 */

#define ELF_MIPS_MAXPGSZ ELF_IRIX_MAXPGSZ
#define ELF_MIPS_MINPGSZ ELF_IRIX_MINPGSZ


/* ====================================================================
 *
 * Elf header
 *
 * ====================================================================
 */

/*
 * e_flags
 */

#define EF_MIPS_NOREORDER	0x00000001
#define EF_MIPS_OPSEX		EF_MIPS_NOREORDER
#define EF_MIPS_PIC		0x00000002
#define EF_MIPS_CPIC		0x00000004
#define EF_MIPS_XGOT		0x00000008
#define EF_MIPS_OPTIONS_FIRST	0x00000080 
/* obsolete names */
#define EF_MIPS_UGEN_ALLOC	EF_MIPS_XGOT
#define EF_MIPS_UGEN_RESERVED	EF_MIPS_64BIT_WHIRL

#define EF_MIPS_ABI64		EF_IRIX_ABI64
	/* see explanation in /usr/include/sys/elf.h	*/

#define EF_MIPS_64BIT_WHIRL	EF_MIPS_ABI64
	/* This is here for compatibility with pre-v7.4 compiler objects. */

#define EF_MIPS_ABI2		0x00000020 
	/* indicates n32 as opposed to o32 */

/*
 *	The EF_MIPS_ARCH field of e_flags describes the ISA of the object.
 *		size:	4 bits
 *		type:	int
 */
#define EF_MIPS_ARCH		0xf0000000	/* mask: 4 bit field */
#define EF_MIPS_ARCH_1		0x00000000	/* MIPS I ISA */
#define EF_MIPS_ARCH_2		0x10000000	/* MIPS II ISA */
#define EF_MIPS_ARCH_3		0x20000000	/* MIPS III ISA */
#define EF_MIPS_ARCH_4		0x30000000	/* MIPS IV ISA */
#define EF_MIPS_ARCH_5		0x40000000	/* MIPS V ISA */
#define EF_MIPS_ARCH_6		0x50000000
#define EF_MIPS_ARCH_32		0x50000000	/* MIPS32 ISA */
#define EF_MIPS_ARCH_64		0x60000000	/* MIPS64 ISA */

/*
 *	The EF_MIPS_ARCH_ASE field of e_flags describes the set of 
 *	Application Specific Extensions used by the object.
 *		size:	4 bits
 *		type:	bit-field
 */
#define EF_MIPS_ARCH_ASE	0x0f000000	/* mask: 4 bit field	*/
#define EF_MIPS_ARCH_ASE_MDMX	0x08000000	/* multi-media extensions*/
#define EF_MIPS_ARCH_ASE_M16	0x04000000	/* MIPS16 isa extensions */

/*
 *	Please reserve these 8 bits of e_flags for future
 *	expansion of the EF_MIPS_ARCH_ASE field;  increasing
 *	the field from 4 bits to 12 bits.
 *	
 *		0x00ff0000	
 *	
 *	If and when we expand it, we'll redefine the EF_MIPS_ARCH_ASE 
 *	macro to be:
 *	
 *		0x0fff0000.
 */

/* ====================================================================
 *
 * Program header
 *
 * ====================================================================
 */


/* 
 * special Program header types
 */

#define PT_MIPS_REGINFO		(PT_LOPROC + 0)	/* n32,n64 -- obsolete	*/
#define PT_MIPS_RTPROC		(PT_LOPROC + 1)	/* o32 -- runtime proc tbl */
#define PT_MIPS_OPTIONS		(PT_LOPROC + 2) /* irix/mips		*/


/* 
 * special p_flags
 */

#define PF_MIPS_LOCAL		0x10000000

/* ====================================================================
 *
 * Section Headers
 *
 * ====================================================================
 */

/* 
 * Special mips section indices
 */

#define SHN_MIPS_ACOMMON	SHN_IRIX_ACOMMON
#define SHN_MIPS_TEXT		SHN_IRIX_TEXT
#define SHN_MIPS_DATA		SHN_IRIX_DATA
#define SHN_MIPS_SCOMMON	SHN_IRIX_SCOMMON
#define SHN_MIPS_SUNDEFINED	SHN_IRIX_SUNDEFINED
#define SHN_MIPS_LCOMMON	SHN_IRIX_LCOMMON
#define SHN_MIPS_LUNDEFINED	SHN_IRIX_LUNDEFINED


/*
 * sh_type
 *
 *	These SHT_MIPS_* names are included for backwards
 *	compatibility. 
 */

#define SHT_MIPS_LIBLIST	SHT_IRIX_LIBLIST
#define SHT_MIPS_MSYM		SHT_IRIX_MSYM
#define SHT_MIPS_CONFLICT	SHT_IRIX_CONFLICT
#define SHT_MIPS_GPTAB		SHT_IRIX_GPTAB
#define SHT_MIPS_UCODE		SHT_IRIX_UCODE
#define SHT_MIPS_DEBUG		SHT_IRIX_DEBUG
#define SHT_MIPS_REGINFO	SHT_IRIX_REGINFO
#ifdef __osf__
#define SHT_MIPS_PACKAGE	SHT_IRIX_PACKAGE
#define SHT_MIPS_PACKSYM	SHT_IRIX_PACKSYM
#endif /* __osf__ */

#define SHT_MIPS_RELD		SHT_IRIX_RELD
#define SHT_MIPS_DONTUSE	SHT_IRIX_DONTUSE
/* Don't  use 10 until after the ragnarok beta */
#define SHT_MIPS_IFACE		SHT_IRIX_IFACE
#define SHT_MIPS_CONTENT	SHT_IRIX_CONTENT
#define SHT_MIPS_OPTIONS	SHT_IRIX_OPTIONS

#define SHT_MIPS_SHDR		SHT_IRIX_SHDR
#define SHT_MIPS_FDESC		SHT_IRIX_FDESC
#define SHT_MIPS_EXTSYM		SHT_IRIX_EXTSYM
#define SHT_MIPS_DENSE		SHT_IRIX_DENSE
#define SHT_MIPS_PDESC		SHT_IRIX_PDESC
#define SHT_MIPS_LOCSYM		SHT_IRIX_LOCSYM
#define SHT_MIPS_AUXSYM		SHT_IRIX_AUXSYM
#define SHT_MIPS_OPTSYM		SHT_IRIX_OPTSYM
#define SHT_MIPS_LOCSTR		SHT_IRIX_LOCSTR
#define SHT_MIPS_LINE		SHT_IRIX_LINE
#define SHT_MIPS_RFDESC		SHT_IRIX_RFDESC

#define SHT_MIPS_DELTASYM	SHT_IRIX_DELTASYM
#define SHT_MIPS_DELTAINST	SHT_IRIX_DELTAINST
#define SHT_MIPS_DELTACLASS	SHT_IRIX_DELTACLASS

#define SHT_MIPS_DWARF		SHT_IRIX_DWARF
#define SHT_MIPS_DELTADECL	SHT_IRIX_DELTADECL
#define SHT_MIPS_SYMBOL_LIB	SHT_IRIX_SYMBOL_LIB
#define SHT_MIPS_EVENTS		SHT_IRIX_EVENTS
#define SHT_MIPS_TRANSLATE	SHT_IRIX_TRANSLATE
#define SHT_MIPS_PIXIE		SHT_IRIX_PIXIE
#define SHT_MIPS_XLATE		SHT_IRIX_XLATE
#define SHT_MIPS_XLATE_DEBUG	SHT_IRIX_XLATE_DEBUG
#define SHT_MIPS_WHIRL		SHT_IRIX_WHIRL
#define SHT_MIPS_EH_REGION	SHT_IRIX_EH_REGION
#define SHT_MIPS_XLATE_OLD	SHT_IRIX_XLATE_OLD
#define SHT_MIPS_PDR_EXCEPTION	SHT_IRIX_PDR_EXCEPTION

#define SHT_MIPS_NUM		SHT_IRIX_NUM

/*
 * sh_flags
 */

#define SHF_MIPS_GPREL		SHF_IRIX_GPREL
#define SHF_MIPS_MERGE		SHF_IRIX_MERGE
#define SHF_MIPS_ADDR		SHF_IRIX_ADDR
#define SHF_MIPS_STRINGS	SHF_IRIX_STRINGS
#define SHF_MIPS_NOSTRIP 	SHF_IRIX_NOSTRIP
#define SHF_MIPS_LOCAL		SHF_IRIX_LOCAL
#define SHF_MIPS_NAMES		SHF_IRIX_NAMES
#define SHF_MIPS_NODUPE		SHF_IRIX_NODUPE

/*
 * special section names
 *
 */
#define MIPS_LIBLIST            ".liblist"
#define MIPS_MSYM               ".msym"
#define MIPS_CONFLICT           ".conflict"
#define MIPS_SDATA              ".sdata"
#define MIPS_REL_SDATA          ".rel.sdata"
#define MIPS_SRDATA             ".srdata"
#define MIPS_RDATA              ".rdata"
#define MIPS_SBSS               ".sbss"
#define MIPS_LIT4               ".lit4"
#define MIPS_LIT8               ".lit8"
#define MIPS_LIT16              ".lit16"
#define MIPS_EVENTS             ".MIPS.events"
#define MIPS_INTERFACES         ".MIPS.interfaces"
#define MIPS_OPTIONS            ".MIPS.options"
#define MIPS_SYMBOL_LIB         ".MIPS.symlib"
#define MIPS_DEBUG_INFO         ".debug_info"
#define MIPS_DEBUG_LINE         ".debug_line"
#define MIPS_DEBUG_ABBREV       ".debug_abbrev"
#define MIPS_DEBUG_FRAME        ".debug_frame"
#define MIPS_DEBUG_ARANGES      ".debug_aranges"
#define MIPS_DEBUG_PUBNAMES     ".debug_pubnames"
#define MIPS_DEBUG_STR          ".debug_str"
#define MIPS_DEBUG_FUNCNAMES    ".debug_funcnames"
#define MIPS_DEBUG_TYPENAMES    ".debug_typenames"
#define MIPS_DEBUG_VARNAMES     ".debug_varnames"
#define MIPS_DEBUG_WEAKNAMES    ".debug_weaknames"
#define MIPS_XLATE              ".MIPS.Xlate"
#define MIPS_XLATE_DEBUG	".MIPS.Xlate_debug"
#define MIPS_CONTENT		".MIPS.content"
#define MIPS_WHIRL              ".WHIRL"	/* Mips uses this name       */
/* #define MIPS_WHIRL           ".MIPS.WHIRL"*/ /* Should have use this name */

#ifdef __osf__
#define MIPS_PACKAGE            ".package"
#define MIPS_PACKSYM            ".packsym"
#endif /* __osf__ */

/*
 * special section names
 *
 *	These are the section names for sections
 *	that are unique to Irix/mips.
 */
#define MIPS_REGINFO		".reginfo"
#define MIPS_RHEADER		".rheader"
#define MIPS_GPTAB_SDATA	".gptab.sdata"
#define MIPS_GPTAB_DATA		".gptab.data"
#define MIPS_GPTAB_BSS		".gptab.bss"
#define MIPS_GPTAB_SBSS		".gptab.sbss"
#define MIPS_LBSS		".lbss"
#define MIPS_UCODE		".ucode"
#define MIPS_MDEBUG		".mdebug"
#define MIPS_COMPACT_RELOC	".compact_rel"
#define MIPS_DELTACLASS		".MIPS.dclass"
#define MIPS_DELTASYM		".MIPS.dsym"
#define MIPS_DELTAINST		".MIPS.dinst"
#define MIPS_DELTADECL		".MIPS.ddecl"
#define MIPS_REL_DELTA		".rel.delta"
#define MIPS_XLATE_DEBUG	".MIPS.Xlate_debug"
#define MIPS_XLATE_OLD		".MIPS.Xlate_old"
#define MIPS_PERF_FUNCTIONS    	".MIPS.Perf_function"
#define MIPS_PERF_WEAKNAMES	".MIPS.Perf_weak_names"
#define MIPS_PERF_CALLGRAPH	".MIPS.Perf_call_graph"
#define MIPS_PERF_BBOFFSETS	".MIPS.Perf_bb_offsets"
#define MIPS_PERF_TABLE		".MIPS.Perf_table"
#define MIPS_PERF_ARGTRACE  	".MIPS.Perf_argtrace"
#define MIPS_EH_REGION		"_MIPS_eh_region"
#define MIPS_EH_REGION_SUPP	"_MIPS_eh_region_supp"
#define MIPS_PDR_EXCEPTION	".MIPS.pdr_exception"


/* ====================================================================
 *
 * Symbol table
 *
 * ====================================================================
 */


/* ====================================================================
 *
 * .IRIX.options Section	
 *
 *	[ Mips specific information documented in this file. ]
 *
 * ====================================================================
 */

/*
 *	Elf_Options.kind == ODK_MIPS_EXCEPTIONS	
 *
 *      masks for Elf_Options.info
 */
#define OEX_PAGE0       0x10000 /* page zero must be mapped */
#define OEX_SMM         0x20000 /* Force sequential memory mode? */
#define OEX_FPDBUG      0x40000 /* Force floating point debug mode? */
#define OEX_PRECISEFP   OEX_FPDBUG
#define OEX_DISMISS     0x80000 /* Dismiss invalid address faults? */
#define OEX_FPU_MIN     0x1f    /* FPE's which MUST be enabled */
#define OEX_FPU_MAX     0x1f00  /* FPE's which MAY be enabled */
#define OEX_FPU_INVAL   0x10
#define OEX_FPU_DIV0    0x08
#define OEX_FPU_OFLO    0x04
#define OEX_FPU_UFLO    0x02
#define OEX_FPU_INEX    0x01

/*
 *	Elf_Options.kind == ODK_MIPS_HWPATCH
 *
 *      masks for Elf_Options.info
 */
#define OHW_R4KEOP      0x1     /* R4000 end-of-page patch */
#define OHW_R8KPFETCH   0x2     /* may need R8000 prefetch patch */
#define OHW_R5KEOP      0x4     /* R5000 end-of-page patch */
#define OHW_R5KCVTL     0x8     /* R5000 cvt.[ds].l bug.  clean=1 */
#define OHW_R10KLDL     0x10    /* R10000 requires LDL patch    */

/*
 *      Elf_Options.kind == ODK_MIPS_HWAND
 *
 *      masks for Elf_Options.info
 */
 	    /*
	     * Marks an executable as r4k end of page bug safe.
	     * Both bits must be AND'd for the executable to be
	     * certified safe.
	     *
	     * CHECKED  PRESENT	MEANING
	     *	    1	    1	    certified clean of r4k eop bug
	     * All other variations will render the executable
	     * suspect.
	     */
#define	OHWA0_R4KEOP_CHECKED	0x00000001
#define OHWA0_R4KEOP_CLEAN	0x00000002

/*
 *      Elf_Options.kind == ODK_MIPS_HWAND
 *
 *      masks for following Elf_Options.hwp_flags1
 */
/* #define OHWA1_... */


/*
 *      Elf_Options.kind == ODK_MIPS_HWAND
 *
 *      masks for following Elf_Options.hwp_flags2
 */
/* #define OHWA2_... */

/*
 *      Elf_Options.kind == ODK_MIPS_HWOR
 *
 *      masks for Elf_Options.info
 */
#define OHWO0_FIXADE	0x00000001	/* Object requires FIXADE call */


/*
 *      Elf_Options.kind == ODK_MIPS_HWOR
 *
 *      masks for following Elf_Options.hwp_flags1
 */
/* #define OHWO1_... */


/*
 *      Elf_Options.kind == ODK_MIPS_HWOR
 *
 *      masks for following Elf_Options.hwp_flags2
 */
/* #define OHWO2_... */



/* ====================================================================
 *
 * .gptab Section
 *
 * ====================================================================
 */

#if (defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS))
typedef union
{
	struct
	{
		Elf32_Word	gt_current_g_value;
		Elf32_Word	gt_unused;
	} gt_header;
	struct
	{
		Elf32_Word	gt_g_value;
		Elf32_Word	gt_bytes;
	} gt_entry;
} Elf32_Gptab;
#endif


/* ====================================================================
 *
 * .reginfo Section
 *
 *      The compiler may generate this section and the linker
 *      may generate the corresponding reginfo segment, but
 *      the information contained herein is ignored by Irix.
 *      Instead, Irix gets the appropriate information from
 *      the options segment.
 *
 * ====================================================================
 */

#if (defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS))
typedef struct
{
	Elf32_Word	ri_gprmask;
	Elf32_Word	ri_cprmask[4];
	Elf32_Sword	ri_gp_value;
} Elf32_RegInfo;

typedef struct
{
	Elf64_Word      ri_gprmask;     /* mask of general regs used */
	Elf64_Word      ri_pad;         /* for alignment */
	Elf64_Word      ri_cprmask[4];  /* mask of cop regs used */
	Elf64_Addr      ri_gp_value;    /* initial value of gp */
} Elf64_RegInfo;

#endif


/* ====================================================================
 *
 * .rel, .rela Section
 *
 * ====================================================================
 */

/*
 * relocation types
 */

#define R_MIPS_NONE		0
#define R_MIPS_16		1
#define R_MIPS_32		2
#define R_MIPS_ADD		R_MIPS_32
#define R_MIPS_REL		3
#define R_MIPS_REL32		R_MIPS_REL
#define R_MIPS_26		4
#define R_MIPS_HI16		5
#define R_MIPS_LO16		6
#define R_MIPS_GPREL		7
#define R_MIPS_GPREL16		R_MIPS_GPREL
#define R_MIPS_LITERAL		8
#define R_MIPS_GOT		9
#define R_MIPS_GOT16		R_MIPS_GOT
#define R_MIPS_PC16		10
#define R_MIPS_CALL		11
#define R_MIPS_CALL16		R_MIPS_CALL
#define R_MIPS_GPREL32		12

#define R_MIPS_SHIFT5		16
#define R_MIPS_SHIFT6		17
#define R_MIPS_64		18
#define R_MIPS_GOT_DISP		19
#define R_MIPS_GOT_PAGE		20
#define R_MIPS_GOT_OFST		21
#define R_MIPS_GOT_HI16		22
#define R_MIPS_GOT_LO16		23
#define R_MIPS_SUB		24
#define R_MIPS_INSERT_A		25
#define R_MIPS_INSERT_B		26
#define R_MIPS_DELETE		27
#define R_MIPS_HIGHER		28
#define R_MIPS_HIGHEST		29
#define R_MIPS_CALL_HI16	30
#define R_MIPS_CALL_LO16	31
#define R_MIPS_SCN_DISP		32
#define	R_MIPS_REL16		33
#define R_MIPS_ADD_IMMEDIATE    34
#define R_MIPS_PJUMP    	35
#define R_MIPS_RELGOT		36
#define R_MIPS_JALR	    	37

#define _R_MIPS_COUNT_		38	/* Number of relocations */
	/* _R_MIPS_COUNT_ is not a relocation type, it is
	** a count of relocation types. 
        ** Must be one greater than the highest relocation
        ** type.
	*/

#define R_MIPS_LOVEND0R		100 /* Vendor specific relocations */
#define R_MIPS_HIVENDOR		127



/* ====================================================================
 *
 * .MIPS.content Section
 *
 * sh_type:	SHT_MIPS_CONTENT
 * sh_link:	section header index of section classified
 * sh_info:	0
 * attributes:	SHF_ALLOC, SHF_MIPS_NOSTRIP
 *
 * ====================================================================
 */

#if (defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS))
typedef union {
	struct {                            /* Normal descriptor */
		Elf64_Word      con_info;
		Elf64_Word      con_start;
	} con_y;
	Elf64_Xword con_xval;               /* Extension descriptor */
} Elf64_Content;

/* con_info masks: */
#define __CON64_EMASK   0x80000000
#define __CON64_ESHIFT  31
#define __CON64_KMASK   0x7f000000
#define __CON64_KSHIFT  24
#define __CON64_LMASK   0x00ffffff
#define __CON64_VMASK   0x7fffffffffffffffll

/* Access macros: */
#define ELF64_CON_EXTN(c) \
	(((c).con_y.con_info & __CON64_EMASK)>>__CON64_ESHIFT)
#define ELF64_CON_KIND(c) \
	(((c).con_y.con_info & __CON64_KMASK)>>__CON64_KSHIFT)
#define ELF64_CON_LENGTH(c)     ((c).con_y.con_info & __CON64_LMASK)
#define ELF64_CON_XVAL(c)       ((c).con_xval & __CON64_VMASK)

/* Content kind -- valid for ELF-32 and ELF-64: */
typedef enum {
    CK_NULL	= 0,	    /* Invalid, same as EK_NULL */
    CK_DEFAULT	= 0x30,	    /* Default type of data for section */
    CK_ALIGN	= 0x31,	    /* Alignment for described range */
    CK_INSTR	= 0x32,	    /* Instructions */
    CK_DATA	= 0x33,	    /* Non-address data */
    CK_SADDR_32	= 0x34,	    /* Simple 32-bit addresses */
    CK_GADDR_32	= 0x35,	    /* GP-relative 32-bit addresses */
    CK_CADDR_32	= 0x36,	    /* Complex 32-bit addresses */
    CK_SADDR_64	= 0x37,	    /* Simple 64-bit addresses */
    CK_GADDR_64	= 0x38,	    /* GP-relative 64-bit addresses */
    CK_CADDR_64	= 0x39,	    /* Complex 64-bit addresses */
    CK_NO_XFORM	= 0x3a,	    /* No transformations allowed in this range */
    CK_NO_REORDER = 0x3b,   /* No reordering allowed in this range */
    CK_GP_GROUP = 0x3c,	    /* Text/data in range with length given by
			       second argument references GP group given
			       by first. */
    CK_STUBS	= 0x3d	    /* Text in range is stub code. ULEB */
} Elf_MIPS_Content_Kind;
typedef	Elf_MIPS_Content_Kind	Elf_Content_Kind;


#endif


/* ====================================================================
 *
 * .MIPS.events Section
 *
 * sh_type:	SHT_MIPS_EVENTS
 * sh_link:	section header index of section whose events tracked
 * sh_info:	section header index of associated interface section
 * attributes:	SHF_ALLOC, SHF_MIPS_NOSTRIP
 *
 * ====================================================================
 */

#if (defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS))
/* Event kind -- valid for ELF-32 and ELF-64: */
typedef enum {
    EK_NULL = 0x00,	    /* No valid information */
    EK_ADDR_RESET = 0x01,   /* Reset offset into associated text section */
    EK_INCR_LOC_EXT = 0x02, /* Increment offset into associated text section */
    EK_ENTRY = 0x03,	    /* Subprogram entrypoint */
    EK_IF_ENTRY = 0x04,	    /* Subprogram entrypoint with associated interface offset */
    EK_EXIT = 0x05,	    /* Subprogram exit */
    EK_PEND = 0x06,	    /* Subprogram end (last instruction) */

    EK_SWITCH_32 = 0x7,	    /* jr for switch stmt, table entries are 32bit */
    EK_SWITCH_64 = 0x8,	    /* jr for switch stmt, table entries are 64bit */
    EK_DUMMY = 0x09,	    /* empty slot */

    EK_BB_START = 0x0a,	    /* Basic block beginning */
    EK_INCR_LOC_UNALIGNED = 0x0b,    /* Increment unaligned byte offset */
    EK_GP_PROLOG_HI = 0x0c, /* Establish high 16bits of GP */
    EK_GP_PROLOG_LO = 0x0d, /* Establish low 16bits of GP */
    EK_GOT_PAGE = 0x0e,	    /* Compact relocation: GOT page pointer */
    EK_GOT_OFST = 0x0f,     /* Compact relocation: GOT page offset */
    EK_HI = 0x10,	    /* Compact relocation: high 16bits of abs. addr */
    EK_LO = 0x11,	    /* Compact relocation: low 16bits of abs. addr */
    EK_64_HIGHEST = 0x12,   /* Compact relocation: most significant 16 bits
			       of a 64bit absolute address */
    EK_64_HIGHER = 0x13,    /* Compact relocation: second most significant
			       16 bits of a 64bit absolute address */
    EK_64_HIGH = 0x14,	    /* Compact relocation: third most significant
			       16 bits of a 64bit absolute address */
    EK_64_LOW = 0x15,       /* Compact relocation: least significant 16 bits
			       of a 64bit absolute address */
    EK_GPREL = 0x16,        /* Compact relocation: GP relative reference */

    EK_DEF = 0x17,	    /* Define new event kind format */

    EK_FCALL_LOCAL = 0x18,	/* point-of-call (jalr) to a local procedure */
    EK_FCALL_EXTERN = 0x19,	/* jalr to extern procedure (small got case) */
    EK_FCALL_EXTERN_BIG = 0x1a,	/* jalr to extern procedure (large got case) */
    EK_FCALL_MULT = 0x1b,	/* jalr to more than one procedure */
    EK_FCALL_MULT_PARTIAL = 0x1c, /* jalr to multiple + unknown procedures */

    EK_LTR_FCALL = 0x1d,	/* jalr to rld lazy-text res.  index of
				   symbol associated. */
    EK_PCREL_GOT0 = 0x1e, 	/* immediate is hi 16 bits of 32-bit
				   constant.  Argument is offset to lo,
				   in instructions, not bytes*/

    /* The following events are reserved for supporting Purify-type tools: */
    EK_MEM_COPY_LOAD = 0x1f,    /* load only for copying data */
    EK_MEM_COPY_STORE = 0x20,   /* store only for copying data --
                                   LEB128 operand is word offset to
                                   paired load */
    EK_MEM_PARTIAL_LOAD = 0x21, /* load for reference to a subset of bytes --
                                   BYTE operand's 8 bits indicate which
                                   bytes are actually used */
    EK_MEM_EAGER_LOAD = 0x22,   /* load is speculative */
    EK_MEM_VALID_LOAD = 0x23,   /* load of data known to be valid */

				  
		/*
		 * Yet to be defined kinds with no fields (like EK_EXIT)
		 */
    EK_CK_UNUSED_NONE_0 = 0x50, /*  */
    EK_CK_UNUSED_NONE_1 = 0x51, /*  */
    EK_CK_UNUSED_NONE_2 = 0x52, /*  */
    EK_CK_UNUSED_NONE_3 = 0x53, /*  */
    EK_CK_UNUSED_NONE_4 = 0x54, /*  */

		/*
		 * Yet to be defined kinds with 1 16 bit field
		 */
    EK_CK_UNUSED_16BIT_0 = 0x55,
    EK_CK_UNUSED_16BIT_1 = 0x56,
    EK_CK_UNUSED_16BIT_2 = 0x57, /*  */
    EK_CK_UNUSED_16BIT_3 = 0x58, /*  */
    EK_CK_UNUSED_16BIT_4 = 0x59, /*  */

		/*
		 * Yet to be defined kinds with 1 32 bit field
		 */
    EK_CK_UNUSED_32BIT_0 = 0x5a, /*  */
    EK_CK_UNUSED_32BIT_1 = 0x5b, /*  */
    EK_CK_UNUSED_32BIT_2 = 0x5c, /*  */

		/*
		 * Yet to be defined kinds with 1 64 bit field
		 */

    EK_CK_UNUSED_64BIT_0 = 0x5d,
    EK_CK_UNUSED_64BIT_1 = 0x5e,
    EK_CK_UNUSED_64BIT_2 = 0x5f, /*  */
    EK_CK_UNUSED_64BIT_3 = 0x60, /*  */
    EK_CK_UNUSED_64BIT_4 = 0x61, /*  */

		/*
		 * Yet to be defined kinds with 1 uleb128 field
		 */
    EK_CK_UNUSED_ULEB128_0 = 0x62, /* */
    EK_CK_UNUSED_ULEB128_1 = 0x63, /*  */
    EK_CK_UNUSED_ULEB128_2 = 0x64, /*  */
    EK_CK_UNUSED_ULEB128_3 = 0x65, /*  */
    EK_CK_UNUSED_ULEB128_4 = 0x66, /*  */
    EK_CK_UNUSED_ULEB128_5 = 0x67, /*  */
    EK_CK_UNUSED_ULEB128_6 = 0x68, /*  */
    EK_CK_UNUSED_ULEB128_7 = 0x69, /*  */
    EK_CK_UNUSED_ULEB128_8 = 0x6a, /*  */
    EK_CK_UNUSED_ULEB128_9 = 0x6b, /*  */


    EK_INCR_LOC = 0x80	    /* Increment offset into associated text section */

} Elf_MIPS_Event_Kind;
typedef	Elf_MIPS_Event_Kind Elf_Event_Kind;

/* The following defines list the various types of operands that are 
 * supported with the EK_DEF event kind.
 */
#define EK_DEF_UCHAR	(1)	    /* unsigned char (8 bits) */
#define EK_DEF_USHORT	(2)	    /* unsigned short (16 bits) */
#define EK_DEF_UINT	(3)	    /* unsigned int (32 bits) */
#define EK_DEF_ULONG	(4)	    /* unsigned long (64 bits) */
#define EK_DEF_ULEB128	(5)	    /* unsigned LEB128 encoded number */
#define EK_DEF_CHAR	(6)	    /* signed char (8 bits) */
#define EK_DEF_SHORT	(7)	    /* signed short (16 bits) */
#define EK_DEF_INT	(8)	    /* signed int (32 bits) */
#define EK_DEF_LONG	(9)	    /* signed long (64 bits) */
#define EK_DEF_LEB128	(10)	    /* signed LEB128 encoded number */
#define EK_DEF_STRING	(11)	    /* null terminated string */
#define EK_DEF_VAR	(12)	    /* variable length field: the first 2
				       bytes is an unsigned short
				       specifying the total number of bytes
				       of this field including the first 2
				       bytes */
#define CK_DEF EK_DEF    

#endif


/* ====================================================================
 *
 * .dynamic Section
 *
 * ====================================================================
 */

#define DT_MIPS_RLD_VERSION     0x70000001
#define DT_MIPS_TIME_STAMP      0x70000002
#define DT_MIPS_ICHECKSUM       0x70000003
#define DT_MIPS_IVERSION        0x70000004
#define DT_MIPS_FLAGS           0x70000005
#define DT_MIPS_BASE_ADDRESS    0x70000006
#define DT_MIPS_MSYM            0x70000007
#define DT_MIPS_CONFLICT        0x70000008
#define DT_MIPS_LIBLIST         0x70000009
#define DT_MIPS_LOCAL_GOTNO     0x7000000A
#define DT_MIPS_CONFLICTNO      0x7000000B
#define DT_MIPS_LIBLISTNO       0x70000010

/* The value of DT_MIPS_SYMTABNO is the number of .dynsym  entries.
*/
#define DT_MIPS_SYMTABNO        0x70000011

#define DT_MIPS_UNREFEXTNO      0x70000012

/* With single GOT,
   the value of DT_MIPS_GOTSYM is the number of the first .dynsym
   symbol with a GOT entry for it. , and the GOT entry
   corresponding is DT_MIPS_LOCAL_GOTNO 
*/
#define DT_MIPS_GOTSYM          0x70000013

#ifndef __osf__

#define DT_MIPS_HIPAGENO        0x70000014
#define DT_MIPS_70000015	0x70000015 	  /* reserved */
#define DT_MIPS_RLD_MAP         0x70000016


/*
 *	The following tags are for DELTA_C_PLUS_PLUS only
 *	and are obsolete.  
 */
#if	(defined(_DELTA_C_PLUS_PLUS) && (_DELTA_C_PLUS_PLUS==1))

#define DT_MIPS_DELTA_CLASS 	0x70000017	/* DCC class definitions      */
#define DT_MIPS_DELTA_CLASS_NO 	0x70000018	/* No. DCC class definitions  */
#define DT_MIPS_DELTA_INSTANCE	0x70000019	/* DCC class instances        */
#define DT_MIPS_DELTA_INSTANCE_NO 0x7000001A	/* No. DCC class instances    */
#define DT_MIPS_DELTA_RELOC	0x7000001B	/* DCC relocations            */
#define DT_MIPS_DELTA_RELOC_NO	0x7000001C	/* No.  DCC relocations       */
#define DT_MIPS_DELTA_SYM	0x7000001D	/* DCC symbols Refered to by
						 * DCC relocations            */
#define DT_MIPS_DELTA_SYM_NO	0x7000001E	/* No. DCC symbols	      */
#define DT_MIPS_DELTA_CLASSSYM	0x70000020	/* DCC class declarations     */
#define DT_MIPS_DELTA_CLASSSYM_NO 0x70000021	/* No. DCC class declarations */

#endif	/* _DELTA_C_PLUS_PLUS */


#define	DT_MIPS_CXX_FLAGS	0x70000022	/* Flags:  C++ flavor         */
#define	DT_MIPS_PIXIE_INIT	0x70000023	/* Init code for pixie	      */
#define	DT_MIPS_SYMBOL_LIB	0x70000024
#define DT_MIPS_LOCALPAGE_GOTIDX 0x70000025
#define DT_MIPS_LOCAL_GOTIDX	0x70000026

/* With single GOT,
   The value of DT_MIPS_HIDDEN_GOTIDX is the number of the first
   GOT entry that is STO_HIDDEN.
*/
#define DT_MIPS_HIDDEN_GOTIDX	0x70000027

/* With single GOT,
   The value of DT_MIPS_PROTECTED_GOTIDX is the number of the first
   GOT entry that is STO_PROTECTED.
*/
#define DT_MIPS_PROTECTED_GOTIDX 0x70000028
#define DT_MIPS_OPTIONS		0x70000029	/* Address of .options        */
#define DT_MIPS_INTERFACE	0x7000002a	/* Address of .interface      */
#define DT_MIPS_DYNSTR_ALIGN	0x7000002b
#define DT_MIPS_INTERFACE_SIZE	0x7000002c	/* size of the .interface     */
#define	DT_MIPS_RLD_TEXT_RESOLVE_ADDR 0x7000002d /* Addr of rld_text_resolve  */
#define	DT_MIPS_PERF_SUFFIX	0x7000002e	/* suffix to be added to dso
						 * name before dlopen() call  */
#define DT_MIPS_COMPACT_SIZE	0x7000002f	/* (O32)Size of .compact_rel  */
#define DT_MIPS_GP_VALUE	0x70000030	/* gp value for aux gots      */
#define DT_MIPS_AUX_DYNAMIC	0x70000031      /* Address of aux .dynamic    */
#define DT_MIPS_DIRECT	    	0x70000032  	/* -Bdirect on link line */


/* Rld callbacks for dlopen/dlclose and delay loaded DSOs notification */
#define DT_MIPS_RLD_OBJ_UPDATE	0x70000033      /* dynsym index of a symbol   
                                     * representing a function or subroutine
                                     * rld(1) should call on any update of rld's
                                     * list of objects. The symbol must be an
                                     * extrnal marked STO_HIDDEN in the dynsym. 
                                     * the symbol is of type void (*)(int) 
                                     */

#else  /* __osf__ */

#define DT_MIPS_PACKAGE        	0x70000014
#define DT_MIPS_PACKAGENO       0x70000015
#define DT_MIPS_PACKSYM		0x70000016
#define DT_MIPS_PACKSYMNO	0x70000017
#define	DT_MIPS_IMPACKNO	0x70000018
#define	DT_MIPS_EXPACKNO	0x70000019
#define	DT_MIPS_IMPSYMNO	0x7000001A
#define	DT_MIPS_EXPSYMNO	0x7000001B
#define DT_MIPS_HIPAGENO        0x7000001C

#endif /* __osf__ */

#define RHF_NONE                    0x00000000
			/* A handy name for 'no flags at all'.
			*/

#define RHF_QUICKSTART              0x00000001
			/* RHF_QUICKSTART is turned on by ld if
			   ld determines that at link time the
			   object is quickstartable.
			*/
#define RHF_NOTPOT                  0x00000002 	
			/* RHF_NOTPOT bit non-zero if elf hash 
			   table element count
			   is NOT a Power Of Two 
			   If 0, rld uses mask, else rld uses %
			   (mod) operator to turn hash into index.
			*/
#define RHF_NO_LIBRARY_REPLACEMENT  0x00000004
			/* RHF_NO_LIBRARY_REPLACEMENT
			   is set by ld -no_library_replacement
			   and tells rld not to  honor _RLD*_ROOT
			   or _RLD*_PATH environment variables.
			   from the time detected (during the
			   program execution).
			*/

#define RHF_NO_MOVE                 0x00000008
			/* If RHF_NO_MOVE  is on and a DSO is moved
			   from the address it was linked at, rld
			   will give a fatal error and exit.
			   If it was a dlopen()-type call, the call
			   will fail (but the app will not exit).
			*/
#define RHF_SGI_ONLY                0x00000010
			/* RHF_SGI_ONLY enables various flags, such as the
			   liblist flags so that rld pays
			   attention tothe flags
			*/


#define RHF_GUARANTEE_INIT	    0x00000020
			/* RHF_GUARANTEE_INIT, if on, provokes a fatal
			   error if rld detects a call into a DSO
			   for which the -init code has not been run.

			   This could happen if dso B has dso C on B's
			   liblist and DSO C's init code calls something
			   int DSO B and DSO B has RHF_GUARANTEE_INIT on.
			   This was designed to help implement C++ 
			   initializations in an early C++ release (5.3?).
			   Not used by C++ for quite some time.
			   Also causes rld(1) to behave as if the
			   environment variable LD_BIND_NOW were set to 1.
			*/
#define RHF_DELTA_C_PLUS_PLUS	    0x00000040
			/* RHF_DELTA_C_PLUS_PLUS tells rld that the
			   executable/DSO is Delta C++.
			*/
#define RHF_GUARANTEE_START_INIT    0x00000080
			/* RHF_GUARANTEE_START_INIT, if on, causes rld to
			   run a target DSO's -init  code
			   in result of a call into that DSO.

			   This could happen if dso B has dso C on B's
			   liblist and DSO C's init code calls something
			   int DSO B and DSO B has 
			   RHF_GUARANTEE_START_INIT on.
			   rld will start running DSO C's -init code and
			   when that calls a DSO  B function, 
			   DSO B's -init code is run before the
			   call to B is allowed to run.
			   Also changes the order of running -init code
		           to an old undocumented order, not ABI 
			   conformant. Do not use this flag.
			*/

#define RHF_PIXIE    		    0x00000100
                /* RHF_PIXIE is set in pixified DSOs/executables.
		   Notifies rld(1) to do special handling of
		   dlopen() strings and to save/restore pixie
		   registers (which save/restore is actually not
		   needed as of SpeedShop 1.3).
                */

	
#define	RHF_DEFAULT_DELAY_LOAD	    0x00000200
			/* If DSO B is linked into  DSO A
			   and RHF_DEFAULT_DELAY_LOAD is on in DSO B,
			   ld will mark (in the liblist of DSO A) that
			   DSO B should be delay-loaded by rld, not
			   loaded at the same time A is.
			   (data-dependencies may turn the delay-load off).
			*/
#define	RHF_REQUICKSTART	    0x00000400
			/* If RHF_REQUICKSTART is on, rqs will
			   process the object. If off, 
			   rqs will not process the object unless
			   -force_requickstart  option used.
			   Set by ld or rqs.
			   ld sets it if ld believes the object should
			   allow rqs-ing.  -abi objects do not have
			   this turned on by ld.
			*/
#define	RHF_REQUICKSTARTED          0x00000800
			/* RHF_REQUICKSTARTED  bit non-zero if
			   rqs has processed the object
			   Set by rqs.
			*/
#define RHF_CORD                    0x00001000
			/* RHF_CORD bit is non-zero if
			   the object  has been cord(1)ed
			   set by cord.
			*/
#define RHF_NO_UNRES_UNDEF	    0x00002000
			/* RHF_NO_UNRES_UNDEF is non-zero if
			   every external symbol is resolved
			   (ie, no externals are undefined)
			   Set by ld or rqs.
			*/
#define RHF_RLD_ORDER_SAFE	    0x00004000
			/* If on, RHF_RLD_ORDER_SAFE tells rld it
			   can stop searching for UNDEFineds to
			   resolve when the
			   first non-ABS, non-UNDEF is found
			   (saving time in rld).
			   Set by ld.
			*/
#define RHF_LD_BIND_NOW	     	    0x00008000
			/* If on, RHF_LD_BIND_NOW tells rld(1)
			   to set it's internal ld_bind_now flag
		           so that for this particular program
			   everything loaded from the time this is seen
			   will be fully resolved as if the environment
			   variable LD_BIND_NOW were set to 1.
		           Intended to be set in executables, but can
			   be set in DSOs.   
			   When set startup slightly slower but it 
		           avoids deadlocks
                           a few pthreaded apps have with 
		           lazy-text-resolution and pthread_create()
			   inside dlopen() (you don't really want
			   to do pthread_create inside a dlopen,
			   meaning in -init code...).
		           Specifically does this one job.
			   RHF_GUARANTEE_INIT has this effect plus
			   another small effect.  First appearing
			   in rld 7.4.2, so apps needing this for
			   earlier rld should set RHF_GUARANTEE_INIT
			   instead, even though that has another
			   effect.
			   Setting both this and RHF_GUARANTEE_INIT
			   is identical to setting just RHF_GUARANTEE_INIT.
		        */
#define RHF_LOCAL_LD_BIND_NOW	   0x00010000
			/*If on, RHF_LOCAL_LD_BIND_NOW tells rld that
		          the function calls should be resolved 
			  on load, not waiting for lazy-text-resolution.
			  As if LD_BIND_NOW were 1 just for this one DSO.
			  Also applicable to the executable.
			*/

#endif /* __SYS_ELF_H__ */
