/******************************************************************************
 *
 * FileName:            NokiaTest       system.h
 * Dependencies:        see INCLUDES section 
 * Processor:           PIC16F1786
 * Compiler:            XC8
 * 
 ****************************************************************************** 
/* 
 * File Description:    system.h
 * Change History:
 * Author           Date        Version
 * Tom Meehan       7/24/16     V1.1
 * Adapted from: 
 * http://aranna.altervista.org/dragonsnest/microcontroller-projects/nokia-5110
 * -example-c-source-pic16f/?doing_wp_cron=1469323499.5610311031341552734375
 * 
/******************************************************************************/
/* System Level #define Macros                                                */
/******************************************************************************/

/* TODO Define system operating frequency */

/* Microcontroller MIPs (FCY) */
//#define SYS_FREQ        800000L
//#define FCY             SYS_FREQ/4

//extern unsigned char spk_bit;  //not sure what "spk" variables are for, yet
//extern unsigned char led_bit;
//extern unsigned char spk_enable,spk_enable2;
//extern unsigned int led_counter;

/******************************************************************************/
/* System Function Prototypes                                                 */
/******************************************************************************/

/* Custom oscillator configuration funtions, reset source evaluation
functions, and other non-peripheral microcontroller initialization functions
go here. */

//void ConfigureOscillator(void); /* Handles clock switching/osc initialization */
//this routine is empty