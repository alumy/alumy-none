/*
 * FreeModbus Libary: BARE Port
 * Copyright (C) 2006 Christian Walter <wolti@sil.at>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * File: $Id$
 */

#include "alumy/config.h"
#include "alumy/types.h"
#include "alumy/base.h"

/* ----------------------- Platform includes --------------------------------*/
#include "alumy/freemodbus/port/port.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "alumy/freemodbus/mb.h"
#include "alumy/freemodbus/mbport.h"

/* ----------------------- static functions ---------------------------------*/
__weak void prvvTIMERExpiredISR( void );

/* ----------------------- Start implementation -----------------------------*/
__weak BOOL
xMBPortTimersInit( USHORT usTim1Timerout50us )
{
    return FALSE;
}


__weak inline void
vMBPortTimersEnable(  )
{
    /* Enable the timer with the timeout passed to xMBPortTimersInit( ) */
}

__weak inline void
vMBPortTimersDisable(  )
{
    /* Disable any pending timers. */
}

/* Create an ISR which is called whenever the timer has expired. This function
 * must then call pxMBPortCBTimerExpired( ) to notify the protocol stack that
 * the timer has expired.
 */
__weak void prvvTIMERExpiredISR( void )
{
    ( void )pxMBPortCBTimerExpired(  );
}

