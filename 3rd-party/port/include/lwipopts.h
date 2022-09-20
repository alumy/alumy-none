#ifndef __LWIPOPTS_H__
#define __LWIPOPTS_H__

/**
 * NO_SYS==1: Provides VERY minimal functionality. Otherwise,
 * use lwIP facilities.
 */
#define NO_SYS                  0

/**
 * SYS_LIGHTWEIGHT_PROT==0: disable inter-task protection (and task-vs-interrupt
 * protection) for certain critical regions during buffer allocation, deallocation
 * and memory allocation and deallocation.
 */
#define SYS_LIGHTWEIGHT_PROT    1

/* ---------- Memory options ---------- */
/* MEM_ALIGNMENT: should be set to the alignment of the CPU for which
   lwIP is compiled. 4 byte alignment -> define MEM_ALIGNMENT to 4, 2
   byte alignment -> define MEM_ALIGNMENT to 2. */
#define MEM_ALIGNMENT           4

/* MEM_SIZE: the size of the heap memory. If the application will send
a lot of data that needs to be copied, this should be set high. */
#define MEM_SIZE                (10240)

/* MEMP_NUM_PBUF: the number of memp struct pbufs. If the application
   sends a lot of data out of ROM (or other static memory), this
   should be set high. */
#define MEMP_NUM_PBUF           10
/* MEMP_NUM_UDP_PCB: the number of UDP protocol control blocks. One
   per active UDP "connection". */
#define MEMP_NUM_UDP_PCB        6
/* MEMP_NUM_TCP_PCB: the number of simulatenously active TCP
   connections. */
#define MEMP_NUM_TCP_PCB        10
/* MEMP_NUM_TCP_PCB_LISTEN: the number of listening TCP
   connections. */
#define MEMP_NUM_TCP_PCB_LISTEN 5
/* MEMP_NUM_TCP_SEG: the number of simultaneously queued TCP
   segments. */
#define MEMP_NUM_TCP_SEG        8
/* MEMP_NUM_SYS_TIMEOUT: the number of simulateously active
   timeouts. */
#define MEMP_NUM_SYS_TIMEOUT    10


/* ---------- Pbuf options ---------- */
/* PBUF_POOL_SIZE: the number of buffers in the pbuf pool. */
#define PBUF_POOL_SIZE          8

/* PBUF_POOL_BUFSIZE: the size of each pbuf in the pbuf pool. */
#define PBUF_POOL_BUFSIZE       1524

/* ---------- TCP options ---------- */
#define LWIP_TCP                1
#define TCP_TTL                 255

/* Controls if TCP should queue segments that arrive out of
   order. Define to 0 if your device is low on memory. */
#define TCP_QUEUE_OOSEQ         0

/* TCP Maximum segment size. */
#define TCP_MSS                 (1500 - 40)	  /* TCP_MSS = (Ethernet MTU - IP header size - TCP header size) */

#define TCP_OVERSIZE			0

/* TCP sender buffer space (bytes). */
#define TCP_SND_BUF             (4*TCP_MSS)

/*  TCP_SND_QUEUELEN: TCP sender buffer space (pbufs). This must be at least
  as much as (2 * TCP_SND_BUF/TCP_MSS) for things to work. */

#define TCP_SND_QUEUELEN        (2* TCP_SND_BUF/TCP_MSS)

/* TCP receive window. */
#define TCP_WND                 (2*TCP_MSS)


/* ---------- ICMP options ---------- */
#define LWIP_ICMP                       1


/* ---------- DHCP options ---------- */
#define LWIP_DHCP               1


/* ---------- UDP options ---------- */
#define LWIP_UDP                1
#define UDP_TTL                 255


/* ---------- Statistics options ---------- */
#define LWIP_STATS              1
#define LWIP_STATS_DISPLAY      1

#if LWIP_STATS
#define LINK_STATS              1
#define IP_STATS                1
#define ICMP_STATS              1
#define IGMP_STATS              1
#define IPFRAG_STATS            1
#define UDP_STATS               1
#define TCP_STATS               1
#define MEM_STATS               1
#define MEMP_STATS              1
#define PBUF_STATS              1
#define SYS_STATS               1
#endif /* LWIP_STATS */

/* ---------- link callback options ---------- */
/* LWIP_NETIF_LINK_CALLBACK==1: Support a callback function from an interface
 * whenever the link changes (i.e., link down)
 */
#define LWIP_NETIF_LINK_CALLBACK        1
#define LWIP_NETIF_STATUS_CALLBACK      1
#define LWIP_NETIF_EXT_STATUS_CALLBACK  1

#define LWIP_HAVE_LOOPIF           1
#define LWIP_NETIF_LOOPBACK        1
#define LWIP_LOOPBACK_MAX_PBUFS    10

/* #define LWIP_DEBUG */

#ifdef LWIP_DEBUG

#define LWIP_DBG_MIN_LEVEL         LWIP_DBG_LEVEL_ALL
#define SLIP_DEBUG				   LWIP_DBG_OFF
#define PPP_DEBUG                  LWIP_DBG_OFF
#define MEM_DEBUG                  LWIP_DBG_OFF
#define MEMP_DEBUG                 LWIP_DBG_OFF
#define PBUF_DEBUG                 LWIP_DBG_OFF
#define API_LIB_DEBUG              LWIP_DBG_OFF
#define API_MSG_DEBUG              LWIP_DBG_OFF
#define TCPIP_DEBUG                LWIP_DBG_OFF
#define NETIF_DEBUG                LWIP_DBG_OFF
#define SOCKETS_DEBUG              LWIP_DBG_OFF
#define DNS_DEBUG                  LWIP_DBG_OFF
#define AUTOIP_DEBUG               LWIP_DBG_OFF
#define DHCP_DEBUG                 LWIP_DBG_OFF
#define IP_DEBUG                   LWIP_DBG_OFF
#define IP_REASS_DEBUG             LWIP_DBG_OFF
#define ICMP_DEBUG                 LWIP_DBG_OFF
#define IGMP_DEBUG                 LWIP_DBG_OFF
#define UDP_DEBUG                  LWIP_DBG_OFF
#define TCP_DEBUG                  LWIP_DBG_OFF
#define TCP_INPUT_DEBUG            LWIP_DBG_OFF
#define TCP_OUTPUT_DEBUG           LWIP_DBG_OFF
#define TCP_RTO_DEBUG              LWIP_DBG_OFF
#define TCP_CWND_DEBUG             LWIP_DBG_OFF
#define TCP_WND_DEBUG              LWIP_DBG_OFF
#define TCP_FR_DEBUG               LWIP_DBG_OFF
#define TCP_QLEN_DEBUG             LWIP_DBG_OFF
#define TCP_RST_DEBUG              LWIP_DBG_OFF
#endif

#define LWIP_DBG_TYPES_ON         (LWIP_DBG_ON|LWIP_DBG_TRACE|LWIP_DBG_STATE|LWIP_DBG_FRESH|LWIP_DBG_HALT)

/*
   --------------------------------------
   ---------- Checksum options ----------
   --------------------------------------
*/

/*
The STM32F4xx allows computing and verifying the IP, UDP, TCP and ICMP checksums by hardware:
 - To use this feature let the following define uncommented.
 - To disable it and process by CPU comment the  the checksum.
*/
/* #define CHECKSUM_BY_HARDWARE */


#ifdef CHECKSUM_BY_HARDWARE
  /* CHECKSUM_GEN_IP==0: Generate checksums by hardware for outgoing IP packets.*/
  #define CHECKSUM_GEN_IP                 0
  /* CHECKSUM_GEN_UDP==0: Generate checksums by hardware for outgoing UDP packets.*/
  #define CHECKSUM_GEN_UDP                0
  /* CHECKSUM_GEN_TCP==0: Generate checksums by hardware for outgoing TCP packets.*/
  #define CHECKSUM_GEN_TCP                0
  /* CHECKSUM_CHECK_IP==0: Check checksums by hardware for incoming IP packets.*/
  #define CHECKSUM_CHECK_IP               0
  /* CHECKSUM_CHECK_UDP==0: Check checksums by hardware for incoming UDP packets.*/
  #define CHECKSUM_CHECK_UDP              0
  /* CHECKSUM_CHECK_TCP==0: Check checksums by hardware for incoming TCP packets.*/
  #define CHECKSUM_CHECK_TCP              0
  /* CHECKSUM_CHECK_ICMP==0: Check checksums by hardware for incoming ICMP packets.*/
  #define CHECKSUM_GEN_ICMP               0
#else
  /* CHECKSUM_GEN_IP==1: Generate checksums in software for outgoing IP packets.*/
  #define CHECKSUM_GEN_IP                 1
  /* CHECKSUM_GEN_UDP==1: Generate checksums in software for outgoing UDP packets.*/
  #define CHECKSUM_GEN_UDP                1
  /* CHECKSUM_GEN_TCP==1: Generate checksums in software for outgoing TCP packets.*/
  #define CHECKSUM_GEN_TCP                1
  /* CHECKSUM_CHECK_IP==1: Check checksums in software for incoming IP packets.*/
  #define CHECKSUM_CHECK_IP               1
  /* CHECKSUM_CHECK_UDP==1: Check checksums in software for incoming UDP packets.*/
  #define CHECKSUM_CHECK_UDP              1
  /* CHECKSUM_CHECK_TCP==1: Check checksums in software for incoming TCP packets.*/
  #define CHECKSUM_CHECK_TCP              1
  /* CHECKSUM_CHECK_ICMP==1: Check checksums by hardware for incoming ICMP packets.*/
  #define CHECKSUM_GEN_ICMP               1
#endif


/*
   ----------------------------------------------
   ---------- Sequential layer options ----------
   ----------------------------------------------
*/
/**
 * LWIP_NETCONN==1: Enable Netconn API (require to use api_lib.c)
 */
#define LWIP_NETCONN                    1

/*
   ------------------------------------
   ---------- Socket options ----------
   ------------------------------------
*/
/**
 * LWIP_SOCKET==1: Enable Socket API (require to use sockets.c)
 */
#define LWIP_SOCKET                     1

#define LWIP_SO_RCVTIMEO				1
#define LWIP_SO_SNDTIMEO				1
#define LWIP_TCP_KEEPALIVE				1


#define DEFAULT_UDP_RECVMBOX_SIZE		10
#define DEFAULT_TCP_RECVMBOX_SIZE		10
#define DEFAULT_ACCEPTMBOX_SIZE			10
#define DEFAULT_THREAD_STACKSIZE		1024

#define TCPIP_THREAD_NAME				"TCP/IP"
#define TCPIP_THREAD_STACKSIZE			2048
#define TCPIP_MBOX_SIZE					8
#define TCPIP_THREAD_PRIO				28

#define SLIPIF_THREAD_STACKSIZE			512
#define SLIPIF_THREAD_PRIO				28

#define LWIP_COMPAT_MUTEX				1
#define LWIP_COMPAT_MUTEX_ALLOWED
/* #define LWIP_SKIP_CONST_CHECK */

#endif /* __LWIPOPTS_H__ */

