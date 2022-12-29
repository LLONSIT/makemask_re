/* ====================================================================
 * ====================================================================
 *
 * Module: elfaccess.h
 * $Revision: 1.4 $
 * $Date: 1998/01/26 20:53:53 $
 * $Author: mpm $
 * $Source: /isms/cmplrs.src/v7.4/include/RCS/elfaccess.h,v $
 *
 * Revision history:
 *  03-Jun-93 - Original Version
 *
 * Description:
 *
 * This file provides access macros for the ELF structures defined in
 * /usr/include/elf.h and /usr/include/sys/elf.h
 *
 * In general, we define 32-bit and 64-bit versions of the access
 * macros; where they are identical, we also define a common macro.
 *
 * Names follow the convention:   an all-caps
 * prefix indicating the struct type, with a 32 or 64 if appropriate,
 * and a lower-case suffix matching the field name.  (However, the
 * field name prefixes commonly used in the ELF definitions are not
 * part of this name.)  For macros which are not common to 32-bit and
 * 64-bit versions, we define a non-specific version for the "current"
 * model, as indicated by the cpp symbol _64BIT_OBJECTS.
 *
 * We follow the practice of not shifting flags into
 * the lower bit in the macros, for maximum test efficiency.  We also
 * favor efficiency over robustness in other cases.
 *
 * ====================================================================
 * ====================================================================
 */

#ifndef elfaccess_INCLUDED
#define elfaccess_INCLUDED


/* ====================================================================
 *
 * .rel, .rela Section
 *
 * ====================================================================
 */

/* r_info masks for 32-bit: */
#define REL32_SYM_MASK	0xffffff00
#define REL32_SYM_SHIFT	8
#define REL32_TYPE_MASK	0x000000ff

/* Field access macros, for either .rel or .rela sections: */
#define     REL_offset(r)	((r).r_offset)
#define     REL32_offset(r)	REL_offset(r)
#define     REL32_offset(r)	REL_offset(r)

#define     REL32_sym(r)	ELF32_R_SYM((r).r_info)
#define Set_REL32_sym(r,v) \
    ((r).r_info = ((r).r_info & ~REL32_SYM_MASK) + (v<<REL32_SYM_SHIFT))
#define     REL32_type(r)	ELF32_R_TYPE((r).r_info)
#define Set_REL32_type(r,v) \
    ((r).r_info = ((r).r_info & ~REL32_TYPE_MASK) + (v&REL32_TYPE_MASK))
#define Set_REL32_info(r,s,t) \
    ((r).r_info = ((s)<<REL32_SYM_SHIFT) | ((t)&REL32_TYPE_MASK))

#define     REL64_sym(r)	((r).r_sym)
#define Set_REL64_sym(r,v)	(REL64_sym(r)=v)
#define     REL64_type(r)	((r).r_type)
#define Set_REL64_type(r,v)	(REL64_type(r)=v)
#define Set_REL64_info(r,s,t)	(Set_REL64_sym(r,s),Set_REL64_type(r,t))

/* 64-bit only: */
#define     REL64_ssym(r)	((r).r_ssym)
#define     REL64_type2(r)	((r).r_type2)
#define     REL64_type3(r)	((r).r_type3)

/* .rela only: */
#define     REL_addend(r)	((r).r_addend)
#define     REL32_addend(r)	REL_addend(r)
#define     REL32_addend(r)	REL_addend(r)

/* Model-specific selection: */
#ifdef _64BIT_OBJECTS

#define     REL_sym	REL64_sym
#define Set_REL_sym	Set_REL64_sym
#define     REL_type	REL64_type
#define Set_REL_type	Set_REL64_type
#define Set_REL_info	Set_REL64_info

#else /* 32-bit objects: */

#define     REL_sym	REL32_sym
#define Set_REL_sym	Set_REL32_sym
#define     REL_type	REL32_type
#define Set_REL_type	Set_REL32_type
#define Set_REL_info	Set_REL32_info

#endif

#endif /* elfaccess_INCLUDED */
