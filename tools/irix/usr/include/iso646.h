#ifndef __ISO646_H__
#define __ISO646_H__

/* For C++ the EDG frontend predefines these */

#if !(defined(__cplusplus) && defined(__EDG_VERSION__) && (__EDG_VERSION__ >=245))

#define and    &&
#define and_eq &=
#define bitand &
#define bitor  |
#define compl  ~
#define not    !
#define not_eq !=
#define or     ||
#define or_eq  |=
#define xor    ^
#define xor_eq ^=

#endif

#endif /* __ISO646_H__ */
