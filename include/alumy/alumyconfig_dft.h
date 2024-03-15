#ifndef __ALUMYCONFIG_DFT_H
#define __ALUMYCONFIG_DFT_H 1

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __BYTE_ORDER
#define __BYTE_ORDER		__LITTLE_ENDIAN
#endif
    
#ifndef __SIZEOF_INT__
#define __SIZEOF_INT__      4
#endif

/* Verbose log */
#ifndef AL_LOG
#define AL_LOG                  1
#endif

#ifndef AL_DRV_RTC_LOG
#define AL_DRV_RTC_LOG          0
#endif

#ifndef AL_LOG_FS
#define AL_LOG_FS               0
#endif

#ifndef AL_LOG_FS_API
#define AL_LOG_FS_API           0
#endif

#ifndef AL_LOG_COLOR
#define AL_LOG_COLOR            1
#endif

#ifndef AL_LOG_CRYPTO
#define AL_LOG_CRYPTO		0
#endif

#ifndef AL_PROVIDE_ERRNO
#define AL_PROVIDE_ERRNO	0
#endif

#ifndef AL_HAVE_SYS_CDEFS
#define AL_HAVE_SYS_CDEFS       0
#endif

#ifndef AL_HAVE_SYS_TYPES
#define AL_HAVE_SYS_TYPES       0
#endif

#ifndef AL_HAVE_STDINT
#define AL_HAVE_STDINT			1
#endif

#ifndef AL_HAVE_STDBOOL
#define AL_HAVE_STDBOOL			1
#endif

#ifndef AL_HAVE_STDDEF
#define AL_HAVE_STDDEF			1
#endif

#ifndef AL_DYNAMIC_CRC_TABLE
#define AL_DYNAMIC_CRC_TABLE    0
#endif

#ifndef AL_CONFIG_HW_WATCHDOG
#define AL_CONFIG_HW_WATCHDOG		0		/* Hardware watchdog */
#endif

#ifndef AL_CONFIG_WATCHDOG
#define AL_CONFIG_WATCHDOG			0		/* Maybe a software watchdog */
#endif

#ifndef AL_WATCHDOG_RESET
#define AL_WATCHDOG_RESET()			(void)(0)
#endif

#ifndef AL_LIGHT_UPDATE_FREQ_HZ
#define AL_LIGHT_UPDATE_FREQ_HZ	10 // How often al_light_routine() is called
#endif

#ifndef FLEX_BTN_SCAN_FREQ_HZ
#define FLEX_BTN_SCAN_FREQ_HZ 100 // How often flex_button_scan () is called
#endif

// SPIFFS_LOCK and SPIFFS_UNLOCK protects spiffs from reentrancy on api level
// These should be defined on a multithreaded system

// define this to enter a mutex if you're running on a multithreaded system
#ifndef SPIFFS_LOCK
#define SPIFFS_LOCK(fs)
#endif
// define this to exit a mutex if you're running on a multithreaded system
#ifndef SPIFFS_UNLOCK
#define SPIFFS_UNLOCK(fs)
#endif

#ifdef __cplusplus
extern }
#endif
	
#endif
