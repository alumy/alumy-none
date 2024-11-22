#ifndef __AL_MATH_H
#define __AL_MATH_H 1

#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/byteorder.h"
#include "alumy/math/abs.h"
#include "alumy/math/matrix.h"
#include "alumy/math/cholesky.h"

__BEGIN_DECLS

#define al_p_n(n)		(~(n) + 1)
#define al_p2n(n)		al_p_n((n))
#define al_n2p(n)		al_p_n((n))

#define DIV_ROUND_UP(n,d) (((n) + (d) - 1) / (d))

__END_DECLS

#endif
