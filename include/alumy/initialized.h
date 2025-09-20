/**
 * @file initialized.h
 * @brief Reference-counted initialization management utilities
 * 
 * This header provides utilities for managing reference-counted initialization
 * and cleanup operations. It's useful for scenarios where multiple components
 * may need to initialize/cleanup the same resource, and you want to ensure
 * the resource is only actually initialized once and cleaned up when no longer needed.
 */

#ifndef __AL_INITIALIZED_H
#define __AL_INITIALIZED_H 1

#include "alumy/byteorder.h"
#include "alumy/byteswap.h"
#include "alumy/types.h"
#include "alumy/base.h"

__BEGIN_DECLS

/**
 * @brief Define an initialization counter variable
 * @param name Variable name
 * 
 * This macro defines a uint32_t variable with initial value 0,
 * used for tracking initialization state.
 */
#ifndef AL_INITIALIZED
#define AL_INITIALIZED(name)        uint32_t name = 0
#endif

/**
 * @brief Initialize the counter
 * @param initialized Pointer to the initialization counter
 * @return true if this is the first initialization call, false if already initialized
 * 
 * This function implements reference-counted initialization. Only the first call
 * returns true, subsequent calls increment the counter but return false.
 */
__static_inline__ bool al_initialized_init(uint32_t *initialized)
{
    if ((*initialized)++) {
        return false;
    }

    return true;
}

/**
 * @brief Cleanup the counter
 * @param initialized Pointer to the initialization counter
 * @return true if counter reaches 0 (actual cleanup needed), false if still has references or not initialized
 * 
 * This function implements reference-counted cleanup. Only returns true when
 * the counter decrements to 0, indicating actual cleanup should be performed.
 */
__static_inline__ bool al_initialized_cleanup(uint32_t *initialized)
{
    if (!(*initialized)) {
        return false;
    }

    if (--(*initialized)) {
        return false;
    }

    return true;
}

/**
 * @brief Check if initialized
 * @param initialized Pointer to the initialization counter
 * @return true if initialized (counter > 0), false if not initialized
 * 
 * This function checks the current initialization state.
 */
__static_inline__ bool al_initialized_is_init(uint32_t *initialized)
{
    return (*initialized);
}

__END_DECLS

#endif
