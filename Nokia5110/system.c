/******************************************************************************
 *
 * FileName:            NokiaTest          system.c
 * Dependencies:        see INCLUDES section 
 * Processor:           PIC16F1786
 * Compiler:            XC8
 * 
 ****************************************************************************** 
/* 
 * File Description:    system.c
 * Change History:
 * Author           Date        Version
 * Tom Meehan       7/24/16     V1.1
 * Adapted from: 
 * http://aranna.altervista.org/dragonsnest/microcontroller-projects/nokia-5110
 * -example-c-source-pic16f/?doing_wp_cron=1469323499.5610311031341552734375
 * 
 * ****************************************************************************
 * 
 * Include and Header files   
 *                                                         
/******************************************************************************/

#include <xc.h>             /* XC8 General Include File */
#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition - boolean*/

#include "system.h"

/* Refer to the device datasheet for information about available
oscillator configurations. */
void ConfigureOscillator(void)
{
    /* TODO Add clock switching code if appropriate.  */

    /* Typical actions in this function are to tweak the oscillator tuning
    register, select new clock sources, and to wait until new clock sources
    are stable before resuming execution of the main project. */
}
