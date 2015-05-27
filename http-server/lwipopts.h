/**
  ******************************************************************************
  * @file    lwipopts.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    31-October-2011
  * @brief   lwIP Options Configuration.
  *          This file is based on Utilities\lwip_v1.3.2\src\include\lwip\opt.h 
  *          and contains the lwIP configuration for the STM32F4x7 demonstration.
  *
  *          heavily modified by Mike Stuart, spaceorbot@gmail.com.
  *
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

#ifndef __LWIPOPTS_H__
#define __LWIPOPTS_H__

#include "eth_mac.h" // defines ethernet buffer size

/**
 * SYS_LIGHTWEIGHT_PROT==1: if you want inter-task protection for certain
 * critical regions during buffer allocation, deallocation and memory
 * allocation and deallocation.
 */
#define SYS_LIGHTWEIGHT_PROT    0

/**
 * NO_SYS==1: Provides VERY minimal functionality. Otherwise,
 * use lwIP facilities.
 */
#define NO_SYS                  0

/**
 * use system timeval (set 0), not LWIP one
 */
#define LWIP_TIMEVAL_PRIVATE	0

/* ---------- Memory options ---------- */
/* MEM_ALIGNMENT: should be set to the alignment of the CPU for which
   lwIP is compiled. 4 byte alignment -> define MEM_ALIGNMENT to 4, 2
   byte alignment -> define MEM_ALIGNMENT to 2. */
#define MEM_ALIGNMENT           4

/* MEM_SIZE: the size of the heap memory. If the application will send
a lot of data that needs to be copied, this should be set high. */
#define MEM_SIZE                (8*1024)

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
#define MEMP_NUM_TCP_PCB_LISTEN 6
/* MEMP_NUM_TCP_SEG: the number of simultaneously queued TCP
   segments. */
#define MEMP_NUM_TCP_SEG        12
/* MEMP_NUM_SYS_TIMEOUT: the number of simulateously active
   timeouts. */
#define MEMP_NUM_SYS_TIMEOUT    10

/* MEMP_NUM_NETCONN: the number of simulateously active
   netconns. */
#define MEMP_NUM_NETCONN        16

/* ---------- Pbuf options ---------- */
/* PBUF_POOL_SIZE: the number of buffers in the pbuf pool. */
#define PBUF_POOL_SIZE          12

/* PBUF_POOL_BUFSIZE: the size of each pbuf in the pbuf pool. */
#define PBUF_POOL_BUFSIZE       512


/* ---------- TCP options ---------- */

/**
 * note: MAX_ETH_PAYLOAD is located in stm32_eth.h, or enc28j60.h
 */

#define LWIP_TCP                1
#define TCP_TTL                 255

/* Controls if TCP should queue segments that arrive out of
   order. Define to 0 if your device is low on memory. */
#define TCP_QUEUE_OOSEQ         0

/* TCP Maximum segment size. */
#define TCP_MSS                 (MAX_ETH_PAYLOAD - 40)	  /* TCP_MSS = (Ethernet MTU - IP header size - TCP header size) */

/* TCP sender buffer space (bytes). */
#define TCP_SND_BUF             (4*TCP_MSS)

/*  TCP_SND_QUEUELEN: TCP sender buffer space (pbufs). This must be at least
  as much as (2 * TCP_SND_BUF/TCP_MSS) for things to work. */

#define TCP_SND_QUEUELEN        (2* TCP_SND_BUF/TCP_MSS)

/* TCP receive window. */
#define TCP_WND                 (2*TCP_MSS)

#define TCP_TMR_INTERVAL        50

/* ---------- TCPIP options ---------- */
#define TCPIP_THREAD_STACKSIZE	configMINIMAL_STACK_SIZE + 800
#define TCPIP_THREAD_PRIO		tskIDLE_PRIORITY + NET_TASK_PRIORITY
#define TCPIP_MBOX_SIZE			32


/* ---------- ICMP options ---------- */
#define LWIP_ICMP                       1


/* ---------- DHCP options ---------- */
/* Define LWIP_DHCP to 1 if you want DHCP configuration of
   interfaces. DHCP is not implemented in lwIP 0.5.1, however, so
   turning this on does currently not work. */
#define LWIP_DHCP               1
#define LWIP_DNS                1
#define LWIP_NETIF_HOSTNAME     1


/* ---------- UDP options ---------- */
#define LWIP_UDP                1
#define UDP_TTL                 255


/* ---------- Statistics options ---------- */
#define LWIP_STATS 1

#define DEFAULT_RAW_RECVMBOX_SIZE       32
#define DEFAULT_UDP_RECVMBOX_SIZE       32
#define DEFAULT_TCP_RECVMBOX_SIZE       32
#define DEFAULT_ACCEPTMBOX_SIZE         32


/*
   --------------------------------------
   ---------- Checksum options ----------
   --------------------------------------
*/

/* 
The STM32F4x7 allows computing and verifying the IP, UDP, TCP and ICMP checksums by hardware:
 - To use this feature let the following define uncommented.
 - To disable it and process by CPU comment the  the checksum.
*/
#ifndef CHECKSUM_BY_HARDWARE
#define CHECKSUM_BY_HARDWARE              0
#endif


#if CHECKSUM_BY_HARDWARE
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

  #define CHECKSUM_GEN_ICMP				  0
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

  #define CHECKSUM_GEN_ICMP				  1
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
#define LWIP_COMPAT_SOCKETS				0
#define LWIP_POSIX_SOCKETS_IO_NAMES		0

#include <limits.h>
#define LWIP_SO_SNDTIMEO                0
#define LWIP_SO_RCVTIMEO                0
#define LWIP_SO_RCVBUF                  1

/*
   ----------------------------------------
   ---------- Lwip use callbacks ----------
   ----------------------------------------
*/
#define LWIP_NETIF_STATUS_CALLBACK		1
#define LWIP_NETIF_LINK_CALLBACK		1

/*
   ----------------------------------------
   ---------- Lwip Debug options ----------
   ----------------------------------------
*/
#include <stdio.h>
#define LWIP_PLATFORM_DIAG 				printf

//#define LWIP_DEBUG
#define LWIP_DBG_TYPES_ON (LWIP_DBG_ON | LWIP_DBG_TRACE | LWIP_DBG_STATE | LWIP_DBG_FRESH | LWIP_DBG_HALT)
#define LWIP_DBG_MIN_LEVEL 0


#ifdef LWIP_DEBUG
#define DEBUG_ALL						LWIP_DBG_ON
#else
#define DEBUG_ALL						LWIP_DBG_OFF
#endif
#define ETHARP_DEBUG                    DEBUG_ALL
#define PBUF_DEBUG                      DEBUG_ALL
#define API_LIB_DEBUG                   DEBUG_ALL
#define API_MSG_DEBUG                   DEBUG_ALL
#define SOCKETS_DEBUG                   DEBUG_ALL
#define ICMP_DEBUG                      DEBUG_ALL
#define IGMP_DEBUG                      DEBUG_ALL
#define INET_DEBUG                      DEBUG_ALL
#define IP_DEBUG                        DEBUG_ALL
#define IP_REASS_DEBUG                  DEBUG_ALL
#define RAW_DEBUG                       DEBUG_ALL
#define MEM_DEBUG                       DEBUG_ALL
#define MEMP_DEBUG                      DEBUG_ALL
#define SYS_DEBUG                       DEBUG_ALL
#define TCP_DEBUG                       DEBUG_ALL
#define TCP_INPUT_DEBUG                 DEBUG_ALL
#define TCP_FR_DEBUG                    DEBUG_ALL
#define TCP_RTO_DEBUG                   DEBUG_ALL
#define TCP_CWND_DEBUG                  DEBUG_ALL
#define TCP_WND_DEBUG                   DEBUG_ALL
#define TCP_OUTPUT_DEBUG                DEBUG_ALL
#define TCP_RST_DEBUG                   DEBUG_ALL
#define TCP_QLEN_DEBUG                  DEBUG_ALL
#define UDP_DEBUG                       DEBUG_ALL
#define TCPIP_DEBUG                     DEBUG_ALL
#define PPP_DEBUG                       DEBUG_ALL
#define SLIP_DEBUG                      DEBUG_ALL
#define DHCP_DEBUG                      DEBUG_ALL
#define AUTOIP_DEBUG                    DEBUG_ALL
#define SNMP_MSG_DEBUG                  DEBUG_ALL
#define SNMP_MIB_DEBUG                  DEBUG_ALL
#define DNS_DEBUG                       DEBUG_ALL


#endif /* __LWIPOPTS_H__ */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
