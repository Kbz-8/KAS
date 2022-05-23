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

E(0,            "kmlib : No error information")

E(KM_EILSEQ,       "kmlib : Illegal byte sequence")
E(KM_EDOM,         "kmlib : Domain error")
E(KM_ERANGE,       "kmlib : Result not representable")

E(KM_ENOTTY,       "kmlib : Not a tty")
E(KM_EACCES,       "kmlib : Permission denied")
E(KM_EPERM,        "kmlib : Operation not permitted")
E(KM_ENOENT,       "kmlib : No such file or directory")
E(KM_ESRCH,        "kmlib : No such process")
E(KM_EEXIST,       "kmlib : File exists")

E(KM_EOVERFLOW,    "kmlib : Value too large for data type")
E(KM_ENOSPC,       "kmlib : No space left on device")
E(KM_ENOMEM,       "kmlib : Out of memory")

E(KM_EBUSY,        "kmlib : Resource busy")
E(KM_EINTR,        "kmlib : Interrupted system call")
E(KM_EAGAIN,       "kmlib : Resource temporarily unavailable")
E(KM_ESPIPE,       "kmlib : Invalid seek")

E(KM_EXDEV,        "kmlib : Cross-device link")
E(KM_EROFS,        "kmlib : Read-only file system")
E(KM_ENOTEMPTY,    "kmlib : Directory not empty")

E(KM_ECONNRESET,   "kmlib : Connection reset by peer")
E(KM_ETIMEDOUT,    "kmlib : Operation timed out")
E(KM_ECONNREFUSED, "kmlib : Connection refused")
E(KM_EHOSTDOWN,    "kmlib : Host is down")
E(KM_EHOSTUNREACH, "kmlib : Host is unreachable")
E(KM_EADDRINUSE,   "kmlib : Address in use")

E(KM_EPIPE,        "kmlib : Broken pipe")
E(KM_EIO,          "kmlib : I/O error")
E(KM_ENXIO,        "kmlib : No such device or address")
E(KM_ENOTBLK,      "kmlib : Block device required")
E(KM_ENODEV,       "kmlib : No such device")
E(KM_ENOTDIR,      "kmlib : Not a directory")
E(KM_EISDIR,       "kmlib : Is a directory")
E(KM_ETXTBSY,      "kmlib : Text file busy")
E(KM_ENOEXEC,      "kmlib : Exec format error")

E(KM_EINVAL,       "kmlib : Invalid argument")

E(KM_E2BIG,        "kmlib : Argument list too long")
E(KM_ELOOP,        "kmlib : Symbolic link loop")
E(KM_ENAMETOOLONG, "kmlib : Filename too long")
E(KM_ENFILE,       "kmlib : Too many open files in system")
E(KM_EMFILE,       "kmlib : No file descriptors available")
E(KM_EBADF,        "kmlib : Bad file descriptor")
E(KM_ECHILD,       "kmlib : No child process")
E(KM_EFAULT,       "kmlib : Bad address")
E(KM_EFBIG,        "kmlib : File too large")
E(KM_EMLINK,       "kmlib : Too many links")
E(KM_ENOLCK,       "kmlib : No locks available")

E(KM_EDEADLK,      "kmlib : Resource deadlock would occur")
E(KM_ENOTRECOVERABLE, "kmlib : State not recoverable")
E(KM_EOWNERDEAD,   "kmlib : Previous owner died")
E(KM_ECANCELED,    "kmlib : Operation canceled")
E(KM_ENOSYS,       "kmlib : Function not implemented")
E(KM_ENOMSG,       "kmlib : No message of desired type")
E(KM_EIDRM,        "kmlib : Identifier removed")
E(KM_ENOSTR,       "kmlib : Device not a stream")
E(KM_ENODATA,      "kmlib : No data available")
E(KM_ETIME,        "kmlib : Device timeout")
E(KM_ENOSR,        "kmlib : Out of streams resources")
E(KM_ENOLINK,      "kmlib : Link has been severed")
E(KM_EPROTO,       "kmlib : Protocol error")
E(KM_EBADMSG,      "kmlib : Bad message")
E(KM_EBADFD,       "kmlib : File descriptor in bad state")
E(KM_ENOTSOCK,     "kmlib : Not a socket")
E(KM_EDESTADDRREQ, "kmlib : Destination address required")
E(KM_EMSGSIZE,     "kmlib : Message too large")
E(KM_EPROTOTYPE,   "kmlib : Protocol wrong type for socket")
E(KM_ENOPROTOOPT,  "kmlib : Protocol not available")
E(KM_EPROTONOSUPPORT,"Protocol not supported")
E(KM_ESOCKTNOSUPPORT,"Socket type not supported")
E(KM_ENOTSUP,      "kmlib : Not supported")
E(KM_EPFNOSUPPORT, "kmlib : Protocol family not supported")
E(KM_EAFNOSUPPORT, "kmlib : Address family not supported by protocol")
E(KM_EADDRNOTAVAIL,"Address not available")
E(KM_ENETDOWN,     "kmlib : Network is down")
E(KM_ENETUNREACH,  "kmlib : Network unreachable")
E(KM_ENETRESET,    "kmlib : Connection reset by network")
E(KM_ECONNABORTED, "kmlib : Connection aborted")
E(KM_ENOBUFS,      "kmlib : No buffer space available")
E(KM_EISCONN,      "kmlib : Socket is connected")
E(KM_ENOTCONN,     "kmlib : Socket not connected")
E(KM_ESHUTDOWN,    "kmlib : Cannot send after socket shutdown")
E(KM_EALREADY,     "kmlib : Operation already in progress")
E(KM_EINPROGRESS,  "kmlib : Operation in progress")
E(KM_ESTALE,       "kmlib : Stale file handle")
E(KM_EREMOTEIO,    "kmlib : Remote I/O error")
E(KM_EDQUOT,       "kmlib : Quota exceeded")
E(KM_ENOMEDIUM,    "kmlib : No medium found")
E(KM_EMEDIUMTYPE,  "kmlib : Wrong medium type")
E(KM_EMULTIHOP,    "kmlib : Multihop attempted")
E(KM_ENOKEY,       "kmlib : Required key not available")
E(KM_EKEYEXPIRED,  "kmlib : Key has expired")
E(KM_EKEYREVOKED,  "kmlib : Key has been revoked")
E(KM_EKEYREJECTED, "kmlib : Key was rejected by service")
