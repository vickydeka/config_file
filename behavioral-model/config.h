/* config.h.  Generated from config.h.in by configure.  */
/* config.h.in.  Generated from configure.ac by autoheader.  */

/* "Link with gcov." */
/* #undef COVERAGE */

/* Enable debugger */
/* #undef DEBUG_ON */

/* Enable nanomsg event logger */
/* #undef ELOG_ON */

/* Enable dynamic loading of modules */
#define ENABLE_MODULES /**/

/* Define to 1 if you have the <algorithm> header file. */
#define HAVE_ALGORITHM 1

/* Define to 1 if you have the <array> header file. */
#define HAVE_ARRAY 1

/* Define to 1 if you have the <cassert> header file. */
#define HAVE_CASSERT 1

/* Define to 1 if you have the <cmath> header file. */
#define HAVE_CMATH 1

/* Define to 1 if you have the <cstdio> header file. */
#define HAVE_CSTDIO 1

/* Define to 1 if you have the <ctime> header file. */
#define HAVE_CTIME 1

/* define if the compiler supports basic C++11 syntax */
#define HAVE_CXX11 1

/* Define to 1 if you have the <dlfcn.h> header file. */
#define HAVE_DLFCN_H 1

/* Found dlopen */
#define HAVE_DLOPEN /**/

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have the `atomic' library (-latomic). */
/* #undef HAVE_LIBATOMIC */

/* Define to 1 if you have the `boost_thread' library (-lboost_thread). */
#define HAVE_LIBBOOST_THREAD 1

/* Define to 1 if you have the `gcov' library (-lgcov). */
/* #undef HAVE_LIBGCOV */

/* Define to 1 if you have the `gmp' library (-lgmp). */
#define HAVE_LIBGMP 1

/* Define to 1 if you have the `nanomsg' library (-lnanomsg). */
#define HAVE_LIBNANOMSG 1

/* Define to 1 if you have the `pcap' library (-lpcap). */
#define HAVE_LIBPCAP 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the <PI/p4info.h> header file. */
/* #undef HAVE_PI_P4INFO_H */

/* Define to 1 if you have the <PI/pi.h> header file. */
/* #undef HAVE_PI_PI_H */

/* Define to 1 if you have the <PI/target/pi_imp.h> header file. */
/* #undef HAVE_PI_TARGET_PI_IMP_H */

/* Define if you have POSIX threads libraries and header files. */
#define HAVE_PTHREAD 1

/* Have PTHREAD_PRIO_INHERIT. */
#define HAVE_PTHREAD_PRIO_INHERIT 1

/* Define to 1 if you have the <queue> header file. */
#define HAVE_QUEUE 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the <string> header file. */
#define HAVE_STRING 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Found Thrift stdcxx wrapper */
/* #undef HAVE_THRIFT_STDCXX_H */

/* Define to 1 if you have the <tuple> header file. */
#define HAVE_TUPLE 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define to 1 if you have the <unordered_map> header file. */
#define HAVE_UNORDERED_MAP 1

/* Define to 1 if you have the <utility> header file. */
#define HAVE_UTILITY 1

/* Define to 1 if you have the <vector> header file. */
#define HAVE_VECTOR 1

/* Enable compile-time macro for debug logging */
/* #undef LOG_DEBUG_ON */

/* Enable compile-time macro for trace logging */
/* #undef LOG_TRACE_ON */

/* Define to the sub-directory where libtool stores uninstalled libraries. */
#define LT_OBJDIR ".libs/"

/* Enable Nanomsg support */
#define NANOMSG_ON /**/

/* Name of package */
#define PACKAGE "bm"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "antonin@barefootnetworks.com"

/* Define to the full name of this package. */
#define PACKAGE_NAME "bm"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "bm 1.15.0-f16d0de3"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "bm"

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION "1.15.0-f16d0de3"

/* Define to necessary symbol if this constant uses a non-standard name on
   your system. */
/* #undef PTHREAD_CREATE_JOINABLE */

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Enable Thrift support */
#define THRIFT_ON /**/

/* Thrift version string extracted from thrift/config.h */
#define THRIFT_VERSION 1300

/* Version number of package */
#define VERSION "1.15.0-f16d0de3"

/* Implement stacks as per P4_16 spec */
#define WP4_16_STACKS /**/

/* Define for Solaris 2.5.1 so the uint64_t typedef from <sys/synch.h>,
   <pthread.h>, or <semaphore.h> is not used. If the typedef were allowed, the
   #define below would cause a syntax error. */
/* #undef _UINT64_T */

/* Define to `unsigned int' if <sys/types.h> does not define. */
/* #undef size_t */

/* Define to the type of an unsigned integer type of width exactly 64 bits if
   such a type exists and the standard includes do not define it. */
/* #undef uint64_t */
