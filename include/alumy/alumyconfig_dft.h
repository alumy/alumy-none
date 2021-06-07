#ifndef __ALUMYCONFIG_H
#define __ALUMYCONFIG_H 1

#ifdef __cplusplus
extern "C" {
#endif

#define __BYTE_ORDER		__LITTLE_ENDIAN

/* Verbose log */
#define AL_LOG                  1
#define AL_LOG_COLOR            1
#define AL_USE_ERRNO            0
#define AL_HAVE_SYS_CDEFS       0
#define AL_HAVE_SYS_TYPES       0

#define AL_DYNAMIC_CRC_TABLE

#define CMB_CPU_PLATFORM_TYPE		CMB_CPU_ARM_CORTEX_M0

#define FLEX_BTN_SCAN_FREQ_HZ 100 // How often flex_button_scan () is called

#ifdef __cplusplus
extern }
#endif
	
#endif
