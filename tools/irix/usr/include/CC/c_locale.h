#ifdef __cplusplus
extern "C" {
#endif
/*
 * It is impossible to write the C++ locale library in terms of locales
 * as defined in the C standard.  Instead, we write the C++ locale and I/O
 * library in terms of a low level C-like interface.  This file defines
 * that interface.
 *
 * The low-level locale interface can't be written portably; there
 * must be a version of it for each platform that the C++ library
 * is ported to.  On many systems this interface may be a thin wrapper
 * for existing functionality.
 */

/*
 * Implementation dependent definitions
 */
#include <sgidefs.h>
#include <standards.h>

#ifdef ROOT_65
#include <wchar.h>
#include <ctype.h>

#else

#if !defined(_SIZE_T) && !defined(_SIZE_T_)
#define _SIZE_T
#if (_MIPS_SZLONG == 32)
typedef unsigned int    size_t;
#endif
#if (_MIPS_SZLONG == 64)
typedef unsigned long   size_t;
#endif
#endif

#ifndef _WCHAR_T
#define _WCHAR_T
#if (_MIPS_SZLONG == 32)
typedef long wchar_t;
#endif
#if (_MIPS_SZLONG == 64)
typedef __int32_t wchar_t;
#endif
#endif

#ifndef _WINT_T
#   define _WINT_T
#if (_MIPS_SZLONG == 32)
        typedef long    wint_t;
#endif
#if (_MIPS_SZLONG == 64)
        typedef __int32_t wint_t;
#endif
#endif

#ifndef _MBSTATE_T
#   define _MBSTATE_T
        typedef char    mbstate_t;
#endif

#endif

/*
 * GENERAL FRAMEWORK
 */


#define _Locale_MAX_SIMPLE_NAME 256

/*
 * A number: the maximum length of a simple locale name.
 * (i.e. a name like like en_US, as opposed to a name like
 * en_US/de_AT/de_AT/es_MX/en_US/en_US) */
#define _Locale_MAX_COMPOSITE_NAME 6*(_Locale_MAX_SIMPLE_NAME+3)
/*
 * Maximum length of a composite locale.
 */

struct _Locale_ctype;
struct _Locale_numeric;
struct _Locale_time;
struct _Locale_collate;
struct _Locale_monetary;
struct _Locale_messages;

struct _Locale_ctype    * _Locale_ctype_create(const char *);
struct _Locale_numeric  * _Locale_numeric_create(const char *);
struct _Locale_time     * _Locale_time_create(const char *);
struct _Locale_collate  * _Locale_collate_create(const char *);
struct _Locale_monetary * _Locale_monetary_create(const char *);
struct _Locale_messages * _Locale_messages_create(const char *);

/*
 * The char* argument is a simple locale name, which may not
 * be "".  These functions return NULL to indicate failure.
 */

const char * _Locale_ctype_default(char * __buf);
const char * _Locale_numeric_default(char * __buf);
const char * _Locale_time_default(char * __buf);
const char * _Locale_collate_default(char * __buf);
const char * _Locale_monetary_default(char * __buf);
const char * _Locale_messages_default(char * __buf);

/*
 * Returns the name of the user's default locale in each
 * category, as a null-terminated string.  A NULL value
 * means the default "C" locale.
 */


char * _Locale_ctype_name(const struct _Locale_ctype *,       char *buf);
char * _Locale_numeric_name(const struct _Locale_numeric *,   char *buf);
char * _Locale_time_name(const struct _Locale_time *,         char *buf);
char * _Locale_collate_name(const struct _Locale_collate *,   char *buf);
char * _Locale_monetary_name(const struct _Locale_monetary *, char *buf);
char * _Locale_messages_name(const struct _Locale_messages *, char *buf);

/*
 * buf points to a buffer that can hold at least _Locale_MAX_SIMPLE_NAME
 * characters.  These functions store the name, as a null-terminated
 * string, in buf.
 */

void _Locale_ctype_destroy(struct _Locale_ctype *);
void _Locale_numeric_destroy(struct _Locale_numeric *);
void _Locale_time_destroy(struct _Locale_time *);
void _Locale_collate_destroy(struct _Locale_collate *);
void _Locale_monetary_destroy(struct _Locale_monetary *);
void _Locale_messages_destroy(struct _Locale_messages *);


char * _Locale_extract_ctype_name(const char *cname, char *buf);
char * _Locale_extract_numeric_name(const char *cname, char *buf);
char * _Locale_extract_time_name(const char *cname, char *buf);
char * _Locale_extract_collate_name(const char *cname, char *buf);
char * _Locale_extract_monetary_name(const char *cname, char *buf);
char * _Locale_extract_messages_name(const char *cname, char *buf);

/*
 * cname is a (possibly composite) locale name---i.e. a name that can
 * be passed to setlocale.  Buf points to an array large enough to
 * store at least _Locale_MAX_SIMPLE_NAME characters, and each of these
 * functions extracts the name of a single category, stores it in buf
 * as a null-terminated string, and returns buf.
 */

char * _Locale_compose_name(char *buf,
                            const char *ctype, const char *numeric,
                            const char *time, const char *collate,
                            const char *monetary, const char *messages);

/*
 * The inputs to this function are six null-terminated strings: the
 * names of a locale's six categories.  Buf is a pointer to an array
 * large enough to store at least _Locale_MAX_COMPOSITE_NAME characters.
 * This function constructs a (possibly composite) name describing the
 * locale as a whole, stores that name in buf as a null-terminated
 * string, and returns buf.
 */

/*
 * FUNCTIONS THAT USE CTYPE
 */

/*
 * For narrow characters, we expose the lookup table interface.
 */

/*
  Bitmask macros.  
*/

/* Internal bitmask macros, specific to IRIX */
#define _Locale_S      0x00000008      /* Spacing character */
#define _Locale_A      0x00004000      /* Alphabetical characters only */
#define _Locale_B      0x00000040      /* Obsolete: was space char only */
#define _Locale_PR     0x00008000      /* Printable characters only */
#define _Locale_G      0x40000000      /* Graphic characters only */
#define _Locale_BL     0x80000000      /* The blank character class */

/* Public bitmask macros, must be defined for every OS. These values, of
 * course, are specific to IRIX. */

#define _Locale_CNTRL  0x00000020      /* Control character */
#define _Locale_UPPER  0x00000001      /* Upper case */
#define _Locale_LOWER  0x00000002      /* Lower case */
#define _Locale_DIGIT  0x00000004      /* Numeral (digit) */
#define _Locale_XDIGIT 0x00000080      /* heXadecimal digit */
#define _Locale_PUNCT  0x00000010      /* Punctuation */
#define _Locale_SPACE  (_Locale_S | _Locale_BL)
#define _Locale_PRINT  (_Locale_PUNCT | _Locale_UPPER | _Locale_LOWER | \
                        _Locale_DIGIT | _Locale_A | _Locale_XDIGIT | \
                        _Locale_PR)
#define _Locale_ALPHA  (_Locale_UPPER | _Locale_LOWER | _Locale_A)


/*
* All of these except for graph and blank are from the C standard;
* graph and blank are XPG4.  (graph in XPG4 doesn't mean quite the
* same thing as graph in the C++ library)
*/

/*
 * Typedefs:
 */

typedef unsigned int _Locale_mask_t;

/*
 * Narrow character functions:
 */

_Locale_mask_t * _Locale_ctype_table(struct _Locale_ctype *);

/*
 * Returns a pointer to the beginning of the ctype table.  The table is
 * at least 257 bytes long; if p is the pointer returned by this
 * function, then p[c] is valid if c is EOF or if p is any value of
 * type unsigned char.
 */

int _Locale_toupper(struct _Locale_ctype *, int c);
int _Locale_tolower(struct _Locale_ctype *, int c);

/*
 * c is either EOF, or an unsigned char value.
 */

/*
 * Wide character functions:
 */
_Locale_mask_t _Locale_wchar_ctype(struct _Locale_ctype *, wint_t c);
wint_t _Locale_wchar_tolower(struct _Locale_ctype *, wint_t c);
wint_t _Locale_wchar_toupper(struct _Locale_ctype *, wint_t c);

/*
 * Multibyte functions:
 */

int _Locale_mb_cur_max (struct _Locale_ctype *);
/*
 * Returns the number of bytes of the longest allowed multibyte
 * character in the current encoding.
 */

int _Locale_mb_cur_min (struct _Locale_ctype *);
/*
 * Returns the number of bytes of the shortest allowed multibyte
 * character in the current encoding.
 */

int _Locale_is_stateless (struct _Locale_ctype *);
/*
 * Returns 1 if the current multibyte encoding is stateless
 * and does not require the use of an mbstate_t value.
 */

wint_t _Locale_btowc(struct _Locale_ctype *, int c);
int _Locale_wctob(struct _Locale_ctype *, wint_t c);

/*
 * Just like btowc and wctob, from 4.6.5.1 of the C standard, Normative
 * Addendum 1.  (And just like widen/narrow, from clause 22 of the C++
 * standard.)
 */

size_t _Locale_mbtowc(struct _Locale_ctype *,
                      wchar_t *to,
                      const char *from, size_t n,
                      mbstate_t *shift_state);

/*
 * Almost identical to mbrtowc, from 4.6.5.3.2 of NA1.  The only
 * important difference is that mbrtowc treats null wide characters
 * as special, and we don't.  Specifically: examines the characters
 * in [from, from + n), extracts a single wide character, and stores
 * it in *to.  Modifies shift_state if appropriate.  The return value,
 * which is always positive, is the number of characters extracted from
 * the input sequence.  Return value is (size_t) -1 if there was an
 * encoding error in the input sequence, and (size_t) -2 if
 * [from, from + n) is correct but not complete.  None of the pointer
 * arguments may be null pointers.
 */

size_t _Locale_wctomb(struct _Locale_ctype *,
                      char *to, size_t n,
                      const wchar_t c,
                      mbstate_t *shift_state);

/*
 * Again, very similar to wcrtomb.  The differences are that (1) it
 * doesn't treat null characters as special; and (2) it stores at most
 * n characters.  Converts c to a multibyte sequence, stores that
 * sequence in the array 'to', and returns the length of the sequence.
 * Modifies shift_state if appropriate.  The return value is (size_t) -1
 * if c is not a valid wide character, and (size_t) -2 if the length of
 * the multibyte character sequence is greater than n.
 */

size_t _Locale_unshift(struct _Locale_ctype *,
                       mbstate_t *st,
                       char *buf, size_t n, char **next);

/*
 * Inserts whatever characters are necessary to restore st to an
 * initial shift state.  Sets *next to buf + m, where m is the number
 * of characters inserted.  (0 <= m <= n.)  Returns m to indicate
 * success, (size_t) -1 to indicate error, (size_t) -2 to indicate
 * partial success (more than n character needed).  For success or partial
 * success, sets *next to buf + m.
 */


/*
 * FUNCTIONS THAT USE COLLATE
 */

int _Locale_strcmp(struct _Locale_collate *,
                   const char *s1, size_t n1,
                   const char *s2, size_t n2);
int _Locale_strwcmp(struct _Locale_collate *,
                    const wchar_t *s1, size_t n1,
                    const wchar_t *s2, size_t n2);

/*
 * Compares the two sequences [s1, s1 + n1) and [s2, s2 + n2).  Neither
 * sequence is assumed to be null-terminated, and null characters
 * aren't special.  If the two sequences are the same up through
 * min(n1, n2), then the sequence that compares less is whichever one
 * is shorter.
 */

size_t _Locale_strxfrm(struct _Locale_collate *,
                       char *s1, size_t n1,
                       const char *s2, size_t n2);
size_t _Locale_strwxfrm(struct _Locale_collate *,
                        wchar_t *s1, size_t n1,
                        const wchar_t *s2, size_t n2);

/*
 * Creates a transformed version of the string [s2, s2 + n2).  The
 * string may contain embedded null characters; nulls aren't special.
 * The transformed string begins at s1, and contains at most n1
 * characters.  The return value is the length of the transformed
 * string.  If the return value is greater than n1 then this is an
 * error condition: it indicates that there wasn't enough space.  In
 * that case, the contents of [s1, s1 + n1) is unspecified.
*/

/*
 * FUNCTIONS THAT USE NUMERIC
 */

char _Locale_decimal_point(struct _Locale_numeric *);
char _Locale_thousands_sep(struct _Locale_numeric *);
const char * _Locale_grouping(struct _Locale_numeric *);

/*
 * Equivalent to the first three fields in struct lconv.  (C standard,
 * section 7.4.)
 */

const char * _Locale_true(struct _Locale_numeric *);
const char * _Locale_false(struct _Locale_numeric *);

/*
 * Return "true" and "false" in English locales, and something
 * appropriate in non-English locales.
 */

/*
[Note: I'm not including any functionality for C++'s num_get and
num_put facets, because it's not necessary.  They can be implemented
portably in terms of the specified _Locale_ctype and _Locale_numeric
interface.  For similar reasons, I don't include any functionality for
money_get and money_put.]
*/

/*
 * FUNCTIONS THAT USE MONETARY
 */

const char * _Locale_int_curr_symbol(struct _Locale_monetary *);
const char * _Locale_currency_symbol(struct _Locale_monetary *);
char         _Locale_mon_decimal_point(struct _Locale_monetary *);
char         _Locale_mon_thousands_sep(struct _Locale_monetary *);
const char * _Locale_mon_grouping(struct _Locale_monetary *);
const char * _Locale_positive_sign(struct _Locale_monetary *);
const char * _Locale_negative_sign(struct _Locale_monetary *);
char         _Locale_int_frac_digits(struct _Locale_monetary *);
char         _Locale_frac_digits(struct _Locale_monetary *);
int          _Locale_p_cs_precedes(struct _Locale_monetary *);
int          _Locale_p_sep_by_space(struct _Locale_monetary *);
int          _Locale_p_sign_posn(struct _Locale_monetary *);
int          _Locale_n_cs_precedes(struct _Locale_monetary *);
int          _Locale_n_sep_by_space(struct _Locale_monetary *);
int          _Locale_n_sign_posn(struct _Locale_monetary *);

/*
 * Return the obvious fields of struct lconv.
 */

/*
 * FUNCTIONS THAT USE TIME
 */

const char ** _Locale_full_monthname(struct _Locale_time *);
const char ** _Locale_abbrev_monthname(struct _Locale_time *);

/*
 * month is in the range [0, 12).
 */

const char ** _Locale_full_dayofweek(struct _Locale_time *);
const char ** _Locale_abbrev_dayofweek(struct _Locale_time *);

/*
 * day is in the range [0, 7).  Sunday is 0.
 */

const char * _Locale_d_t_fmt(struct _Locale_time *);
const char * _Locale_d_fmt(struct _Locale_time *);
const char * _Locale_t_fmt(struct _Locale_time *);
const char * _Locale_am_str(struct _Locale_time *);
const char * _Locale_pm_str(struct _Locale_time *);
const char * _Locale_t_fmt_ampm(struct _Locale_time *);

/*
 * FUNCTIONS THAT USE MESSAGES
 */

int _Locale_catopen(struct _Locale_messages * L, const char* name);

/*
 * Very similar to catopen, except that it uses L to determine
 * which catalog to open.
 */

void _Locale_catclose(struct _Locale_messages *, int catalog);

/*
 * catalog is a value that was returned by a previous call to
 * _Locale_catopen
 */

const char * _Locale_catgets(struct _Locale_messages *, int catalog,
                             int set_num, int msg_num,
                             const char *dfault);

/*
 * Returns a string, identified by a set index and a message index,
 * from an opened message catalog.  Returns default if no such
 * string exists.
 */


#ifdef __cplusplus
}
#endif
