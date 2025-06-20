#include "alumy/config.h"
#include "alumy/byteorder.h"
#include "alumy/types.h"
#include "alumy/base.h"
#include "alumy/osal.h"
#include "SEGGER_RTT.h"

__BEGIN_DECLS

__weak void al_putc(int_t c)
{
    SEGGER_RTT_PutChar(0, c);
}

__END_DECLS

