/** @file
 *
 * @brief This is the header file for the elf_sgi library.
 *
 * If you're looking for information on how to use the libelf_sgi
 * library, you'll find the documentation much more friendly than
 * that which can be found in this file. 
 */

#ifndef ELF_SGI_INCLUDE_GUARD
#define ELF_SGI_INCLUDE_GUARD

#include <stddef.h>
#include <sys/types.h>
#include <elf.h>

#if !defined(__sgi)
/** This is copied from the IRIX headers for portability to other systems */ 
#define	EX_NIDENT	4
/** This is copied from the IRIX headers for portability to other systems */ 
typedef struct {
	unsigned char	ex_ident[EX_NIDENT];	/* magic string = 'IRIX'*/
	Elf32_Half	ex_exhsize;		/* exhdr length in bytes*/
	Elf32_Half	ex_version;		/* exhdr version number	*/

	/* added in ex_version 1 */
	Elf32_Word	ex_eversion;		/* elf file version number */

} Elf_EXhdr;
/** This is copied from the IRIX headers for portability to other systems */ 
#define	EX_VERSION	1
#endif

#if defined(__cplusplus)
extern "C" {
#endif

struct elf_sgi;
enum elf_sgi_error_type { ELF_SGI_ERROR_OK, ELF_SGI_ERROR_BAD_ALLOC, ELF_SGI_ERROR_ERRNO, ELF_SGI_ERROR_FORMAT, ELF_SGI_ERROR_TOO_BIG, ELF_SGI_ERROR_DEMOTE_OVERFLOW };
#if defined(__GNUC__)
struct elf_sgi* elf_sgi_new(void) __attribute__((malloc));
#else
struct elf_sgi* elf_sgi_new(void);
#endif
enum elf_sgi_error_type elf_sgi_begin_fd(struct elf_sgi* const d, int const fd, off64_t const offset);
enum elf_sgi_error_type elf_sgi_begin_image(struct elf_sgi* const d, void* const image, size_t const size);
void elf_sgi_free(struct elf_sgi* const d);
void elf_sgi_end(struct elf_sgi* const d);
void elf_sgi_free_section(struct elf_sgi* const d, Elf64_Section const section_index);
enum elf_sgi_error_type elf_sgi_phdr_count(struct elf_sgi* const d, Elf64_Half* const return_pointer);
enum elf_sgi_error_type elf_sgi_section_count(struct elf_sgi* const d, Elf64_Section* const return_pointer);
enum elf_sgi_error_type elf_sgi_has_irix_exhdr(struct elf_sgi* const d, /*bool*/Elf64_Word* const return_pointer);
enum elf_sgi_error_type elf_sgi_ehdr(struct elf_sgi* const d, Elf64_Ehdr* const target);
enum elf_sgi_error_type elf_sgi_irix_exhdr(struct elf_sgi* const d, Elf_EXhdr* const target);
enum elf_sgi_error_type elf_sgi_phdr(struct elf_sgi* const d, Elf64_Half const phdr_index, Elf64_Phdr* const target);
enum elf_sgi_error_type elf_sgi_shdr(struct elf_sgi* const d, Elf64_Section const section_index, Elf64_Shdr* const target);
enum elf_sgi_error_type elf_sgi_section(struct elf_sgi* const d, Elf64_Section const section_index, void** const return_pointer);
enum elf_sgi_error_type elf_sgi_section_translated(struct elf_sgi* const d, Elf64_Section const section_index, void** const return_pointer);
enum elf_sgi_error_type elf_sgi_string(struct elf_sgi* const d, Elf64_Section const section_index, Elf64_Off const offset, char const** const return_pointer);
enum elf_sgi_error_type elf_sgi_ident(struct elf_sgi* const d, unsigned char const** const return_pointer);
enum elf_sgi_error_type elf_sgi_irix_exhdr_direct(struct elf_sgi* const d, Elf_EXhdr const** const return_pointer);
enum elf_sgi_error_type elf_sgi_ehdr32(struct elf_sgi* const d, Elf32_Ehdr const** const return_pointer);
enum elf_sgi_error_type elf_sgi_ehdr64(struct elf_sgi* const d, Elf64_Ehdr const** const return_pointer);
enum elf_sgi_error_type elf_sgi_phdr32(struct elf_sgi* const d, Elf32_Phdr const** const return_pointer);
enum elf_sgi_error_type elf_sgi_phdr64(struct elf_sgi* const d, Elf64_Phdr const** const return_pointer);
enum elf_sgi_error_type elf_sgi_shdr32(struct elf_sgi* const d, Elf32_Shdr const** const return_pointer);
enum elf_sgi_error_type elf_sgi_shdr64(struct elf_sgi* const d, Elf64_Shdr const** const return_pointer);

enum elf_sgi_error_type elf_sgi_begin_fd_create(struct elf_sgi* const d, int const fd, off64_t const offset, unsigned char const* const ident);
enum elf_sgi_error_type elf_sgi_update(struct elf_sgi* const d);
enum elf_sgi_error_type elf_sgi_set_ehdr(struct elf_sgi* const d, Elf64_Ehdr const* const ehdr);
enum elf_sgi_error_type elf_sgi_set_irix_exhdr(struct elf_sgi* const d, Elf_EXhdr const* const irix_exhdr);
enum elf_sgi_error_type elf_sgi_set_phdr(struct elf_sgi* const d, Elf64_Half const phdr_index, Elf64_Phdr const* const phdr);
enum elf_sgi_error_type elf_sgi_set_shdr(struct elf_sgi* const d, Elf64_Section const section_index, Elf64_Shdr const* const shdr);
enum elf_sgi_error_type elf_sgi_put_section(struct elf_sgi* const d, Elf64_Section const section_index, void const* const section);
enum elf_sgi_error_type elf_sgi_put_section_translated(struct elf_sgi* const d, Elf64_Section const section_index, void const* const section);
enum elf_sgi_error_type elf_sgi_set_phdr_count(struct elf_sgi* const d, Elf64_Half const count);
enum elf_sgi_error_type elf_sgi_set_section_count(struct elf_sgi* const d, Elf64_Section const count);

#if defined(__GNUC__)
Elf64_Word elf_sgi_hash(unsigned char const* name) __attribute__((pure));
#else
Elf64_Word elf_sgi_hash(unsigned char const* name);
#endif
#if defined(__sgi)
#pragma no side effects (elf_sgi_hash)
#endif

#if defined(__cplusplus)
} /* extern "C" */
#endif

#endif /* include guard */
