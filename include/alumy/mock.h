#ifndef __AL_MOCK_H
#define __AL_MOCK_H 1

#include "alumy/base.h"

__BEGIN_DECLS

#if defined(AL_UT)
  #ifndef __mock
    #define __mock              __weak
  #endif
#else
  #define __mock
#endif

__END_DECLS

#endif

