#ifndef __AL_DRV_GRAPHICS_RGB_H
#define __AL_DRV_GRAPHICS_RGB_H 1

#ifndef AL_RGB565
#define AL_RGB565(r, g, b)		\
	((((r) >> 3) << 11) | (((g) >> 2) << 5) | ((b) >> 3))
#endif

#endif

