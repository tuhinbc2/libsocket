#ifndef LIBSOCKET_SOCK_HEADER
#define LIBSOCKET_SOCK_HEADER

#ifdef _LINUX
# include <unistd.h> // read()/write()
# include <sys/socket.h>
# include <sys/types.h>
# include <netdb.h> // getaddrinfo()
# include <errno.h>
# include <sys/ioctl.h>
# include <net/if.h>
# include <netinet/in.h> // e.g. struct sockaddr_in on OpenBSD

#ifdef BD_ANDROID
#define LIBSOCKET_LINUX 0
#else
#define LIBSOCKET_LINUX 1
#endif
#define LIBSOCKET_FREEBSD 0
#define LIBSOCKET_SUNOS 0

#elif _WIN32
#include <io.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>

#if defined(_MSC_VER)
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#endif

#define	SHUT_RD		0		/* shut down the reading side */
#define	SHUT_WR		1		/* shut down the writing side */
#define	SHUT_RDWR	2		/* shut down both sides */


#define SOCK_NONBLOCK FIONBIO
#endif

#endif //LIBSOCKET_SOCK_HEADER