/**
 * This file is a part of the kmlib (kbz_8 main library)
 *
 * Copyright (C) 2022 @kbz_8
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef __KM_ERRNO_INCLUDE__
#define __KM_ERRNO_INCLUDE__

int* __km_get_errno();
#define km_errno (*__km_get_errno())

char* km_strerror(int e);

#define KM_EPERM            1
#define KM_ENOENT           2
#define KM_ESRCH            3
#define KM_EINTR            4
#define KM_EIO              5
#define KM_ENXIO            6
#define KM_E2BIG            7
#define KM_ENOEXEC          8
#define KM_EBADF            9
#define KM_ECHILD          10
#define KM_EAGAIN          11
#define KM_ENOMEM          12
#define KM_EACCES          13
#define KM_EFAULT          14
#define KM_ENOTBLK         15
#define KM_EBUSY           16
#define KM_EEXIST          17
#define KM_EXDEV           18
#define KM_ENODEV          19
#define KM_ENOTDIR         20
#define KM_EISDIR          21
#define KM_EINVAL          22
#define KM_ENFILE          23
#define KM_EMFILE          24
#define KM_ENOTTY          25
#define KM_ETXTBSY         26
#define KM_EFBIG           27
#define KM_ENOSPC          28
#define KM_ESPIPE          29
#define KM_EROFS           30
#define KM_EMLINK          31
#define KM_EPIPE           32
#define KM_EDOM            33
#define KM_ERANGE          34
#define KM_EDEADLK         35
#define KM_ENAMETOOLONG    36
#define KM_ENOLCK          37
#define KM_ENOSYS          38
#define KM_ENOTEMPTY       39
#define KM_ELOOP           40
#define KM_EWOULDBLOCK     KM_EAGAIN
#define KM_ENOMSG          42
#define KM_EIDRM           43
#define KM_ECHRNG          44
#define KM_EL2NSYNC        45
#define KM_EL3HLT          46
#define KM_EL3RST          47
#define KM_ELNRNG          48
#define KM_EUNATCH         49
#define KM_ENOCSI          50
#define KM_EL2HLT          51
#define KM_EBADE           52
#define KM_EBADR           53
#define KM_EXFULL          54
#define KM_ENOANO          55
#define KM_EBADRQC         56
#define KM_EBADSLT         57
#define KM_EDEADLOCK       KM_EDEADLK
#define KM_EBFONT          59
#define KM_ENOSTR          60
#define KM_ENODATA         61
#define KM_ETIME           62
#define KM_ENOSR           63
#define KM_ENONET          64
#define KM_ENOPKG          65
#define KM_EREMOTE         66
#define KM_ENOLINK         67
#define KM_EADV            68
#define KM_ESRMNT          69
#define KM_ECOMM           70
#define KM_EPROTO          71
#define KM_EMULTIHOP       72
#define KM_EDOTDOT         73
#define KM_EBADMSG         74
#define KM_EOVERFLOW       75
#define KM_ENOTUNIQ        76
#define KM_EBADFD          77
#define KM_EREMCHG         78
#define KM_ELIBACC         79
#define KM_ELIBBAD         80
#define KM_ELIBSCN         81
#define KM_ELIBMAX         82
#define KM_ELIBEXEC        83
#define KM_EILSEQ          84
#define KM_ERESTART        85
#define KM_ESTRPIPE        86
#define KM_EUSERS          87
#define KM_ENOTSOCK        88
#define KM_EDESTADDRREQ    89
#define KM_EMSGSIZE        90
#define KM_EPROTOTYPE      91
#define KM_ENOPROTOOPT     92
#define KM_EPROTONOSUPPORT 93
#define KM_ESOCKTNOSUPPORT 94
#define KM_EOPNOTSUPP      95
#define KM_ENOTSUP         KM_EOPNOTSUPP
#define KM_EPFNOSUPPORT    96
#define KM_EAFNOSUPPORT    97
#define KM_EADDRINUSE      98
#define KM_EADDRNOTAVAIL   99
#define KM_ENETDOWN        100
#define KM_ENETUNREACH     101
#define KM_ENETRESET       102
#define KM_ECONNABORTED    103
#define KM_ECONNRESET      104
#define KM_ENOBUFS         105
#define KM_EISCONN         106
#define KM_ENOTCONN        107
#define KM_ESHUTDOWN       108
#define KM_ETOOMANYREFS    109
#define KM_ETIMEDOUT       110
#define KM_ECONNREFUSED    111
#define KM_EHOSTDOWN       112
#define KM_EHOSTUNREACH    113
#define KM_EALREADY        114
#define KM_EINPROGRESS     115
#define KM_ESTALE          116
#define KM_EUCLEAN         117
#define KM_ENOTNAM         118
#define KM_ENAVAIL         119
#define KM_EISNAM          120
#define KM_EREMOTEIO       121
#define KM_EDQUOT          122
#define KM_ENOMEDIUM       123
#define KM_EMEDIUMTYPE     124
#define KM_ECANCELED       125
#define KM_ENOKEY          126
#define KM_EKEYEXPIRED     127
#define KM_EKEYREVOKED     128
#define KM_EKEYREJECTED    129
#define KM_EOWNERDEAD      130
#define KM_ENOTRECOVERABLE 131
#define KM_ERFKILL         132
#define KM_EHWPOISON       133

#endif // __KM_ERRNO_INCLUDE__
