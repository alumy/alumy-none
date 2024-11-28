#include "cmsis_compiler.h"
#include "durian.h"

__BEGIN_DECLS

/*..........................................................................*/
Q_NORETURN Q_onAssert(char const Q_ROM * const module, int loc) {
    /*
    * NOTE: add here your application-specific error handling
    */
    (void)module;
    (void)loc;

	__disable_irq();
	AL_ERROR(1, "Assertion failed in %s, line %d", module, loc);
    for(;;);
}
__END_DECLS
