#ifndef __AL_ERRNO_H
#define __AL_ERRNO_H 1

#include <errno.h>
#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"

__BEGIN_DECLS

#if defined(__CC_ARM)
/*
defined in armcc/errno.h

#define EDOM    1
#define ERANGE  2
#define EILSEQ  4
#define ESIGNUM 3
#define EINVAL  5
#define ENOMEM  6
*/
#define ERRNO_BASE    7

#elif defined(__IAR_SYSTEMS_ICC__)
/* defined in iar/errno.h
#define EDOM    33
#define ERANGE  34
#define EFPOS   35
#define EILSEQ  36
*/
#define ERRNO_BASE    36

#else

#define ERRNO_BASE    0
#endif

#if AL_USE_ERRNO

#define EPERM            (ERRNO_BASE + 1)
#define ENOENT           (ERRNO_BASE + 2)
#define ESRCH            (ERRNO_BASE + 3)
#define EINTR            (ERRNO_BASE + 4)
#define EIO              (ERRNO_BASE + 5)
#define ENXIO            (ERRNO_BASE + 6)
#define E2BIG            (ERRNO_BASE + 7)
#define ENOEXEC          (ERRNO_BASE + 8)
#define EBADF            (ERRNO_BASE + 9)
#define ECHILD          (ERRNO_BASE + 10)
#define EAGAIN          (ERRNO_BASE + 11)

#ifndef ENOMEM
#define ENOMEM          (ERRNO_BASE + 12)
#endif

#define EACCES          (ERRNO_BASE + 13)
#define EFAULT          (ERRNO_BASE + 14)
#define ENOTBLK         (ERRNO_BASE + 15)
#define EBUSY           (ERRNO_BASE + 16)
#define EEXIST          (ERRNO_BASE + 17)
#define EXDEV           (ERRNO_BASE + 18)
#define ENODEV          (ERRNO_BASE + 19)
#define ENOTDIR         (ERRNO_BASE + 20)
#define EISDIR          (ERRNO_BASE + 21)

#ifndef EINVAL
#define EINVAL          (ERRNO_BASE + 22)
#endif

#define ENFILE          (ERRNO_BASE + 23)
#define EMFILE          (ERRNO_BASE + 24)
#define ENOTTY          (ERRNO_BASE + 25)
#define ETXTBSY         (ERRNO_BASE + 26)
#define EFBIG           (ERRNO_BASE + 27)
#define ENOSPC          (ERRNO_BASE + 28)
#define ESPIPE          (ERRNO_BASE + 29)
#define EROFS           (ERRNO_BASE + 30)
#define EMLINK          (ERRNO_BASE + 31)
#define EPIPE           (ERRNO_BASE + 32)

#ifndef EDOM
#define EDOM            (ERRNO_BASE + 33)
#endif

#ifndef ERANGE
#define ERANGE          (ERRNO_BASE + 34)
#endif

#define EDEADLK         (ERRNO_BASE + 35)
#define ENAMETOOLONG    (ERRNO_BASE + 36)
#define ENOLCK          (ERRNO_BASE + 37)
#define ENOSYS          (ERRNO_BASE + 38)
#define ENOTEMPTY       (ERRNO_BASE + 39)
#define ELOOP           (ERRNO_BASE + 40)
#define EWOULDBLOCK     EAGAIN
#define ENOMSG          (ERRNO_BASE + 42)
#define EIDRM           (ERRNO_BASE + 43)
#define ECHRNG          (ERRNO_BASE + 44)
#define EL2NSYNC        (ERRNO_BASE + 45)
#define EL3HLT          (ERRNO_BASE + 46)
#define EL3RST          (ERRNO_BASE + 47)
#define ELNRNG          (ERRNO_BASE + 48)
#define EUNATCH         (ERRNO_BASE + 49)
#define ENOCSI          (ERRNO_BASE + 50)
#define EL2HLT          (ERRNO_BASE + 51)
#define EBADE           (ERRNO_BASE + 52)
#define EBADR           (ERRNO_BASE + 53)
#define EXFULL          (ERRNO_BASE + 54)
#define ENOANO          (ERRNO_BASE + 55)
#define EBADRQC         (ERRNO_BASE + 56)
#define EBADSLT         (ERRNO_BASE + 57)
#define EDEADLOCK       EDEADLK
#define EBFONT          (ERRNO_BASE + 59)
#define ENOSTR          (ERRNO_BASE + 60)
#define ENODATA         (ERRNO_BASE + 61)
#define ETIME           (ERRNO_BASE + 62)
#define ENOSR           (ERRNO_BASE + 63)
#define ENONET          (ERRNO_BASE + 64)
#define ENOPKG          (ERRNO_BASE + 65)
#define EREMOTE         (ERRNO_BASE + 66)
#define ENOLINK         (ERRNO_BASE + 67)
#define EADV            (ERRNO_BASE + 68)
#define ESRMNT          (ERRNO_BASE + 69)
#define ECOMM           (ERRNO_BASE + 70)
#define EPROTO          (ERRNO_BASE + 71)
#define EMULTIHOP       (ERRNO_BASE + 72)
#define EDOTDOT         (ERRNO_BASE + 73)
#define EBADMSG         (ERRNO_BASE + 74)
#define EOVERFLOW       (ERRNO_BASE + 75)
#define ENOTUNIQ        (ERRNO_BASE + 76)
#define EBADFD          (ERRNO_BASE + 77)
#define EREMCHG         (ERRNO_BASE + 78)
#define ELIBACC         (ERRNO_BASE + 79)
#define ELIBBAD         (ERRNO_BASE + 80)
#define ELIBSCN         (ERRNO_BASE + 81)
#define ELIBMAX         (ERRNO_BASE + 82)
#define ELIBEXEC        (ERRNO_BASE + 83)

#ifndef EILSEQ
#define EILSEQ          (ERRNO_BASE + 84)
#endif

#define ERESTART        (ERRNO_BASE + 85)
#define ESTRPIPE        (ERRNO_BASE + 86)
#define EUSERS          (ERRNO_BASE + 87)
#define ENOTSOCK        (ERRNO_BASE + 88)
#define EDESTADDRREQ    (ERRNO_BASE + 89)
#define EMSGSIZE        (ERRNO_BASE + 90)
#define EPROTOTYPE      (ERRNO_BASE + 91)
#define ENOPROTOOPT     (ERRNO_BASE + 92)
#define EPROTONOSUPPORT (ERRNO_BASE + 93)
#define ESOCKTNOSUPPORT (ERRNO_BASE + 94)
#define EOPNOTSUPP      (ERRNO_BASE + 95)
#define ENOTSUP         EOPNOTSUPP
#define EPFNOSUPPORT    (ERRNO_BASE + 96)
#define EAFNOSUPPORT    (ERRNO_BASE + 97)
#define EADDRINUSE      (ERRNO_BASE + 98)
#define EADDRNOTAVAIL   (ERRNO_BASE + 99)
#define ENETDOWN        (ERRNO_BASE + 100)
#define ENETUNREACH     (ERRNO_BASE + 101)
#define ENETRESET       (ERRNO_BASE + 102)
#define ECONNABORTED    (ERRNO_BASE + 103)
#define ECONNRESET      (ERRNO_BASE + 104)
#define ENOBUFS         (ERRNO_BASE + 105)
#define EISCONN         (ERRNO_BASE + 106)
#define ENOTCONN        (ERRNO_BASE + 107)
#define ESHUTDOWN       (ERRNO_BASE + 108)
#define ETOOMANYREFS    (ERRNO_BASE + 109)
#define ETIMEDOUT       (ERRNO_BASE + 110)
#define ECONNREFUSED    (ERRNO_BASE + 111)
#define EHOSTDOWN       (ERRNO_BASE + 112)
#define EHOSTUNREACH    (ERRNO_BASE + 113)
#define EALREADY        (ERRNO_BASE + 114)
#define EINPROGRESS     (ERRNO_BASE + 115)
#define ESTALE          (ERRNO_BASE + 116)
#define EUCLEAN         (ERRNO_BASE + 117)
#define ENOTNAM         (ERRNO_BASE + 118)
#define ENAVAIL         (ERRNO_BASE + 119)
#define EISNAM          (ERRNO_BASE + 120)
#define EREMOTEIO       (ERRNO_BASE + 121)
#define EDQUOT          (ERRNO_BASE + 122)
#define ENOMEDIUM       (ERRNO_BASE + 123)
#define EMEDIUMTYPE     (ERRNO_BASE + 124)
#define ECANCELED       (ERRNO_BASE + 125)
#define ENOKEY          (ERRNO_BASE + 126)
#define EKEYEXPIRED     (ERRNO_BASE + 127)
#define EKEYREVOKED     (ERRNO_BASE + 128)
#define EKEYREJECTED    (ERRNO_BASE + 129)
#define EOWNERDEAD      (ERRNO_BASE + 130)
#define ENOTRECOVERABLE (ERRNO_BASE + 131)
#define ERFKILL         (ERRNO_BASE + 132)
#define EHWPOISON       (ERRNO_BASE + 133)

#endif

void set_errno(int errnum);

__END_DECLS

#endif
