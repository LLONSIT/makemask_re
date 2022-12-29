#ifndef _XtHacks_h
#define _XtHacks_h

#include <stdio.h>
#include <X11/Intrinsic.h>

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif
/*
** ForceShellIconic is left in solely for binary compatibility.
** It is no longer used by ViewKit (it used to be used by VkSimpleWindow).
** It is not needed if you do everything else right (i.e. per ICCCM).
**
** Oops -- something is broken somewhere -- it is needed in
** VkSimpleWindow or else cvd's execution view fails to come up iconic.
*/
extern void ForceShellIconic(Widget w);

extern char * XtClassName(Widget w);
extern int isPoppedUp(Widget w);
extern int isBeingDestroyed(Widget w);
extern void setPopupCursors(Widget, const Cursor);
#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

/*
 * Xt returns a resource value in a word long enough to hold anything.
 * Extracting the right thing and passing it back to the user is enough
 * of a trick that we encapsulate it in this macro.
 */
#define _CHECK_ONE(size, return_value, type) \
	  if ((size) == sizeof(type)) return (XtPointer)(ptrdiff_t) *(type *) return_value

#if _MIPS_SZINT == _MIPS_SZLONG
#define RETURN_INTEGRAL_VALUE(size, return_value)	\
        _CHECK_ONE(size, return_value, long);		\
        _CHECK_ONE(size, return_value, short);		\
        _CHECK_ONE(size, return_value, char);		\
	fprintf (stderr, "Vk Error: IF test should not fall through here\n");
#else
#define RETURN_INTEGRAL_VALUE(size, return_value)	\
        _CHECK_ONE(size, return_value, long);		\
        _CHECK_ONE(size, return_value, int);		\
        _CHECK_ONE(size, return_value, short);		\
        _CHECK_ONE(size, return_value, char);		\
	fprintf (stderr, "Vk Error: IF test should not fall through here\n");
#endif

#endif /*_Xthacks_h*/
/* DON'T ADD STUFF AFTER THIS #endif */
