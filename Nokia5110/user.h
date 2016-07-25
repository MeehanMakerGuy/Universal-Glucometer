/******************************************************************************
 *
 * FileName:            NokiaTest       user.h
 * Dependencies:        see INCLUDES section 
 * Processor:           PIC16F1786
 * Compiler:            XC8
 * 
 ****************************************************************************** 
/* 
 * File Description:    user.h
 * Change History:
 * Author           Date        Version
 * Tom Meehan       7/24/16     V1.1
 * Adapted from: 
 * http://aranna.altervista.org/dragonsnest/microcontroller-projects/nokia-5110
 * -example-c-source-pic16f/?doing_wp_cron=1469323499.5610311031341552734375
 * 
/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/

/* TODO Application specific user parameters used in user.c may go here       */

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

/* TODO User level functions prototypes (i.e. InitApp) go here                */

void LCDWrite(unsigned char data_or_command, unsigned char data);
void gotoXY(int x, int y);
void LCDBitmap(char my_array[]);
void LCDCharacter(char character);
void LCDString(char *characters);
void LCDClear(void);
void LCDInit(void) ;

void InitApp(void);         /* I/O and Peripheral Initialization */
