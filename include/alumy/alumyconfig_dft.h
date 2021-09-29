#ifndef __ALUMYCONFIG_DFT_H
#define __ALUMYCONFIG_DFT_H 1

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __BYTE_ORDER
#define __BYTE_ORDER		__LITTLE_ENDIAN
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

#ifndef AL_LOG_COLOR
#define AL_LOG_COLOR            1
#endif

#ifndef AL_USE_ERRNO
#define AL_USE_ERRNO            0
#endif

#ifndef AL_HAVE_SYS_CDEFS
#define AL_HAVE_SYS_CDEFS       1
#endif

#ifndef AL_HAVE_SYS_TYPES
#define AL_HAVE_SYS_TYPES       1
#endif

#ifndef AL_DYNAMIC_CRC_TABLE
#define AL_DYNAMIC_CRC_TABLE
#endif

#ifndef CMB_CPU_PLATFORM_TYPE
#define CMB_CPU_PLATFORM_TYPE		CMB_CPU_ARM_CORTEX_M4
#endif

#ifndef FLEX_BTN_SCAN_FREQ_HZ
#define FLEX_BTN_SCAN_FREQ_HZ 100 // How often flex_button_scan () is called
#endif

#ifdef __cplusplus
extern }
#endif
	
#endif
