#ifndef __AL_PRINTF_COLOR_H
#define __AL_PRINTF_COLOR_H 1

#define AL_PRI_BLACK   "30"
#define AL_PRI_RED     "31"
#define AL_PRI_GREEN   "32"
#define AL_PRI_BROWN   "33"
#define AL_PRI_BLUE    "34"
#define AL_PRI_PURPLE  "35"
#define AL_PRI_CYAN    "36"
#define AL_PRI_COLOR(COLOR)  "\033[0;" COLOR "m"
#define AL_PRI_BOLD(COLOR)   "\033[1;" COLOR "m"
#define AL_PRI_RESET_COLOR   "\033[0m"

#endif
