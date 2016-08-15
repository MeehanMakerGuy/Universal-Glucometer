/********************************************************************
*
*
*
*********************************************************************
* FileName:        glucose_meter_main.c
* Dependencies:    See INCLUDES section below
* Processor:       PIC16LF1786
* Compiler:        XC8
* Company:         Microchip Technology, Inc.
* Tom Meehan           8/02/2016  Re-purposed version for Universal Glucometer
*
* Software License Agreement:
*
* The software supplied herewith by Microchip Technology Incorporated
* (the "Company") for its PICmicro® Microcontroller is intended and
* supplied to you, the Company's customer, for use solely and
* exclusively on Microchip PICmicro Microcontroller products. The
* software is owned by the Company and/or its supplier, and is
* protected under applicable copyright laws. All rights are reserved.
* Any use in violation of the foregoing restrictions may subject the
* user to criminal sanctions under applicable laws, as well as to
* civil liability for the breach of the terms and conditions of this
* license.
*
* THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTIES,
* WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
* TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
* IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
* CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
*********************************************************************/

/*
* File Description: Main module with the main() function. It includes
*                   the glucose meter application code controlling the
*                   application's behavior.
*
* Change History:
* Author               Date        Version
* Namrata Dalvi        10/18/2013  First version of code
* Tom Meehan           8/02/2016  Re-purposed version for Universal Glucometer
*********************************************************************

//*****************************************************************************
// Include and Header files
//*****************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <xc.h>         /* XC8 General Include File */
#include "user.h"
#include "variables.h"
#include "nokia.h"
#include "EEPROM.h"
/*
 * 
 */
//*****************************************************************************
// PIC Configuration
//*****************************************************************************
// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function enabled)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable (Brown-out Reset disabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = OFF       // Internal/External Switchover (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is disabled)

// CONFIG2
#pragma config WRT = OFF       // Flash Memory Self-Write Protection (Write protection off)
#pragma config PLLEN = OFF     // PLL Enable (4x PLL disabled)
#pragma config STVREN = ON     // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO       // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LPBOR = OFF     // Low Power Brown-Out Reset Enable Bit (Low power brown-out is disabled)
#pragma config LVP = OFF       // Low-Voltage Programming Enable (Low-voltage programming disabled)





/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
/********************************************************************
* Function:             Main
*
* PreCondition: 	None
*
* Side Effects: 	None
*/
/**
* @ingroup  		Main
*
* @brief    		Main function of the application.It includes functions
*                       controlling the application behavior.
*
* @note    		None
*/
/*******************************************************************/
void main(void)
{
    HwInit(); //configure oscillator, initialize peripherals 
    LCDInit();
    LCDClear();
    gotoXY(0,0);   //upper left corner
   // LCDString("123456789123"); 
    //__delay_ms(250);
   // gotoXY(1,1);
   // LCDString("KLMNOPQRSTUV"); 
    LCDClear();
    __delay_ms(250);
    gotoXY(10,1); //26
    LCDString("Learn");
    gotoXY(23,2);  
    LCDString("By");
    gotoXY(30,3);  
    LCDString("Making");
    Delay_1_Second();
    LCDClear();
    gotoXY(12,1 );  
    LCDString("UNIVERSAL");
    gotoXY(6,3);  
    LCDString("GLUCOMETER");
    __delay_ms(500);
    LCDWrite(0, 0x20); //We must send 0x20 before modifying the display control mode
    LCDWrite(0, 0x0D); //Set display control,0x0C normal mode. 0x0D for inverse
    __delay_ms(500);//Delay_1_Second();
    LCDWrite(0, 0x20); //We must send 0x20 before modifying the display control mode
    LCDWrite(0, 0x0C); //Set display control,0x0C normal mode. 0x0D for inverse
    __delay_ms(500);//Delay_1_Second();
   // LCDWrite(0, 0x20); //We must send 0x20 before modifying the display control mode
   // LCDWrite(0, 0x0D); //Set display control,0x0C normal mode. 0x0D for inverse
  
    while(1)   //while 1 infinite loop
    {

        if (gSetDateTime == TRUE)
        {
            SetTime();
            gSetDateTime = FALSE;
            gSleepMode = TRUE;
            NOP();
            EnterDeepSleep();
            NOP();
            NOP();
            NOP();
        }
        else if (gExitMemoryMode == TRUE)
        {
            gExitMemoryMode = FALSE;
            gtimeOutCount = TIMEOUT_COUNT ;
            while(gtimeOutCount!=0)gtimeOutCount--;
            EnterDeepSleep();
            NOP();
            NOP();
            NOP();
        }
        else if (gMemorymode == TRUE)
        {
            if ((gSavedReadingCnt==0) && (gOneReadingDisplyed==0))
            {
               // LCD_PWR = LCD_POWER_ON;        // power up the lcd controller
                LCDInit();
                LCDClear();
               // LCDString("..ReadingNotSaved");
                gotoXY(0,1);
                //sprinf(" Time= %02d:%02d:%02d", Hours, Minutes,Seconds );
                gDisplayPreviousReading = 0;
                gOneReadingDisplyed=1;
            }
            else if (gSavedReadingCnt)
            {
                if(gOneReadingDisplyed == FALSE)
                {
                   // LCD_PWR = LCD_POWER_ON;        // power up the lcd controller
                    LCDInit();
                    ReadSavedGlucoReading(gSavedReadingCnt-1);
                    DisplaySavedGlucoReading();
                    gOneReadingDisplyed=1;
                    RedingCount = gSavedReadingCnt-1;
                }
                else if (gDisplayPreviousReading)
                {
                    if (RedingCount)
                    RedingCount--;
                    else
                        RedingCount = gSavedReadingCnt-1;

                    ReadSavedGlucoReading(RedingCount);
                    DisplaySavedGlucoReading();
                    gDisplayPreviousReading=0;
                }
            }
       }
        else if (gSleepMode)
        {
            NOP();
            SLEEP();
            NOP();
            NOP();
        }
        else // active/idle mode
        {
            DACCON1 = DAC400MVCOUNT;
            SenseTestStrip();
            if(gglucDataReady == TRUE)
            {
                gglucDataReady = 0;
                //gAverageGlucose = (gSigmaGlucoseValue >> 7);          // Average Voltage of 128 readings
                gAverageGlucose = gSigmaGlucoseValue;
                gcaptured2SValue = (int)gAverageGlucose;

                CalcGlucose();                                      // Calculate Glucose Concentration
                gYint = (int)gY;
                if (gYint<=0) gYint=0;
                gYmmol=gY/18;
                gYmmolchar = (char)gYmmol;
                gYmmoldecimal=(gYmmol - gYmmolchar)*10;
                gYmmoldecimalchar= (char)gYmmoldecimal;
                if (gYmmolchar <= 0) gYmmolchar=0;
                if (gYmmoldecimalchar <= 0) gYmmoldecimalchar=0;
// uncomment below code for Reading Temperature
//                Ad_Set_Chan(8);
//                _delay(10);
//                Ad_Convert();
//                gReadTemp = ADRESL;
//                gReadTemp += ADRESH << 8;
//                gReadTemp = (gReadTemp - TEMPOFFSET);
//                gTemp = (float)gReadTemp;
//                gTemp = gTemp* TEMPSCALE;
                //gTempint = (int)gTemp;
               // gTempint2 = (int)(gTemp *100);
 // uncomment above code for reading temperature
                LCDClear();
               // LCDString("%03dmg/dl%02d/%02d/%02d", gYint, Month, Days, Year); // display glucose reading in mg/dl along with date
               //Need to change to print correctly - separate function - SPRINF saves to string then send string to print
                gotoXY(0,1);
               // sprintf("ADC = %d    ",gcaptured2SValue);
              //  sprintf("%d.%dmmol/L %02d:%02d", gYmmolchar,gYmmoldecimalchar, Hours, Minutes);// display glucose reading in mmol/L along with time
                //sprintf("..Temp.: %d" "\xdf" "C!.", gTempint);
                //sprintf("\r\n Temperature int: %d deg", gTempint2);
                SaveGlucoReading(); // save glucose reading to EEPROM
                
                TEMP_SENSE_VDD = 0;
                Ad_Set_Chan(0);
//                gtimeOutCount = TIMEOUT_COUNT;
//                while(gtimeOutCount!=0)gtimeOutCount--;
                while (!(PORTB & 0x01));
                EnterDeepSleep();
                NOP();
                NOP();
                NOP();

            }
            if (gBloodNotInsetrted == TRUE)
            {
                gBloodNotInsetrted = 0;
                LCDClear();
//                LCDString("   Sample Not   ");
                gotoXY(0,1);
//                LCDString("    Inserted    ");
                gtimeOutCount = TIMEOUT_COUNT;
                while(gtimeOutCount!=0)gtimeOutCount--;
                EnterDeepSleep();
                NOP();
                NOP();
                NOP();
            }
        }
    } 

}
/********************************************************************
* Function:             SenseTestStrip
*
* PreCondition: 	None
*
* Side Effects: 	None
*/
/**
* @ingroup  		Main
*
* @brief    		This function detects the insertion of the test strip
*
* @note    		None
*/
/*******************************************************************/
void SenseTestStrip(void)
{
    unsigned char index=0;
    int temp_adc=0;

    gSenseTestStrip = PORTB & 0x01;

    if((gSenseTestStrip == STRIP_INSERTED ) & (gStripInserted == FALSE))
    {
        InitADC();
        INTCONbits.PEIE = 1;
        PIR1bits.ADIF = 0;
        PIE1bits.ADIE=0;
        Ad_Set_Chan(0);
        for (index=0; index<8; index++)
        {
            __delay_us(200);
            Ad_Convert();
            gReadData = ADRESL;
            gReadData += ADRESH << 8;
            temp_adc += gReadData;
        }
        temp_adc= temp_adc >>3;

        if(temp_adc >= FAULTY_STRIP_VOLTAGE)
        {
            PIR1bits.ADIF = 0;
            PIE1bits.ADIE=1;
            LCDClear();
//            LCDString("...Faulty Strip..");
            gotoXY(0,1);
//            LCDString(" Time= %02d:%02d  ", Hours, Minutes );
            gtimeOutCount = TIMEOUT_COUNT;
            while(gtimeOutCount!=0)gtimeOutCount--;
            EnterDeepSleep();
            NOP();
            NOP();
        }
        else
        {
            LCDClear();
//            LCDString("...Strip Inserted");
            gotoXY(0,1);
//            LCDString("Place the Sample");
            gStripInserted = 1;
            gStripRemoved = 0;
            gcountIdleTime = COUNT_IDLE_TIME;
            gStripIdleTime = STRIP_IDLE_TIME;
            PIR1bits.ADIF = 0;
            PIE1bits.ADIE=1;        // enable ADC interrupt
            ADCON0bits.ADGO = 1;    // start ADC
            REF_OUT = 0;
        }
    }

    if((gSenseTestStrip == STRIP_NOT_INSERTED) & (gStripRemoved == FALSE))
    {
        LCDClear();
      //  LCDString("InsertTestStrip");
        gotoXY(0,1);
       // LCDString("                ");
        gStripRemoved = 1;
        gStripInserted = 0;
        REF_OUT = 0;
    }

    if((gSenseTestStrip == STRIP_NOT_INSERTED) & (gStripRemoved == TRUE))
    {
        if(gStripIdleTime <= 1)
        gStripIdleTime = 1;
        else
        gStripIdleTime--;

        if(gStripIdleTime == 1)
        {
            LCDClear();
//            LCDString("StripNotInserted");
            gotoXY(0,1);
           // LCDString("                ");
            gtimeOutCount = TIMEOUT_COUNT;
            while(gtimeOutCount!=0)gtimeOutCount--;
            EnterDeepSleep();
            NOP();
            NOP();
            NOP();
        } //(gStripIdleTime == 1)
    }
}
/********************************************************************
* Function:             CalcGlucose
*
* PreCondition: 	ADC read
*
* Side Effects: 	None
*/
/**
* @ingroup  		Main
*
* @brief    		This function calculates the glucose concentration according to the polyfit equation
*
* @note    		None
*/
/*******************************************************************/
void CalcGlucose(void)
{
    // PolyFit equation derived by statistical method using Excel or MATLAB
    // Y = mXadc + C,
    // y is the glucometer reading in mg/dl
    // Xadc is the adc count of voltage input to glucometer in mV
    gXadc = (float) gcaptured2SValue;       // Value of voltage after 2 secondsflo

    if (gXadc <=POLYFITBOUNDRY)
    {
        gY = (SLOPE1 * gXadc) + GLUCO_OFFSET1;         // gY=glucose reading in mg/dl

    }
    else
    {
        gY = (SLOPE2 * gXadc) + GLUCO_OFFSET2;         // gY=glucose reading in mg/dl
    }

}


/********************************************************************
* Function:             EnterDeepSleep
*
* PreCondition: 	None
*
* Side Effects: 	None
*/
/**
* @ingroup  		Main
*
* @brief    		This function prepares cpu for the sleep mode and cpu in entered in to the sleep mode
*
* @note    		None
*/
/*******************************************************************/
void EnterDeepSleep(void)
{
    gSleepMode = 1;
    gStripInserted = 0;
    gStripRemoved = 0;
    gBloodNotInsetrted = 0;
    gSigmaGlucoseValue = 0;
    FVRCONbits.FVREN = 0;
    TEMP_SENSE_VDD = 0;
    TRISC = 0xFC; // make it input port except RC0 and RC1

//    LCD_PWR = LCD_POWER_OFF;        //switch off the power to the lcd

    LATBbits.LATB7 = 0;
    LATBbits.LATB6 = 0;
    LATBbits.LATB5 = 0;
    LATBbits.LATB1 = 0;

    TRISBbits.TRISB7 = 1;   // make it input port
    TRISBbits.TRISB6 = 1;   // make it input port
    TRISBbits.TRISB5 = 1;   // make it input port
    TRISBbits.TRISB1 = 1;   // make it input port

    LATAbits.LATA7 = 0;
    LATAbits.LATA6 = 0;
    TRISAbits.TRISA7 = 1;   // make it input port
    TRISAbits.TRISA6 = 1;   // make it input port
    TRISAbits.TRISA3 = 1;   // make it input port

    OPA1CONbits.OPA1EN = 0; // disable opamp
    DACCON0bits.DACEN = 0;  //disable DAC
    DACCON0bits.DACOE1= 0;
    ADCON0bits.ADON = 0;    // disable ADC
    NOP();
    SLEEP();
    NOP();
    NOP();
    NOP();
}
/********************************************************************
* Function:             interrupt isr
*
* PreCondition: 	Interrupt
*
* Side Effects: 	None
*/
/**
* @ingroup  		interrupt
*
* @brief    		This is interrupt isr for strip insertion, ADC, Switch 1 &3 press and timer 1 for RTCC
*
* @note    		None
*/
/*******************************************************************/
void interrupt isr(void)
{
     if (PIR1bits.TMR1IF == 1)
     {
         PIR1bits.TMR1IF = 0;

         TMR1H  |= 0x80;
         Seconds++;                           //   Increment number of seconds

          if (Seconds == 60) {Minutes++; Seconds=0;
            if (Minutes == 60) {Hours++; Minutes=0;
              if (Hours == 24) {Days++; Hours=0;
                if (  (Days == 29 && Month==2 && !Is_Leap(Year))                        // February in leap year
                   || (Days == 30 && Month==2)                                          // February in normal years
                   || (Days == 31 && (Month==4 || Month==6 || Month==9 || Month==11 ))  // All months with 30 days
                   || (Days == 32)                                                      // All months with 31 days
                   ) {Month++; Days=1;}
                if (Month == 13) {Year++; Month=1;}
          }}}

      }

    if (INTCONbits.INTF == 1)
    {
        INTCONbits.INTF = 0;
        gcountIdleTime = 120000;
        gStripIdleTime = STRIP_IDLE_TIME;
        gStripInserted = 0;
        gStripRemoved = 0;
        gBloodNotInsetrted = 0;
        TRISC = 0;
        TRISBbits.TRISB5 = 0;
        TRISBbits.TRISB1 = 0;
        TRISAbits.TRISA7 = 0;
        TRISAbits.TRISA6 = 0;
        TRISAbits.TRISA3 = 0;
        FVRCONbits.FVREN = 1;
        OPA1CONbits.OPA1EN = 1;
        DACCON0bits.DACEN = 1;
        DACCON0bits.DACOE1= 1;
        ADCON0bits.ADON = 1;
        REF_OUT = 0;
//        LCD_PWR = LCD_POWER_ON;        // power up the lcd controller
        LCDInit();
        NOP();
        gSleepMode = 0;
    }
    
    if (INTCONbits.IOCIF == 1)
    {
        INTCONbits.IOCIF = 0;
        if (IOCBFbits.IOCBF4)
        {
            IOCBFbits.IOCBF4 = 0;
            if (gMemorymode == TRUE)
            {
                gExitMemoryMode = TRUE;
                gMemorymode = FALSE;
            }
            else if (gSleepMode == TRUE)
            {
                gExitMemoryMode = FALSE;
                gMemorymode = TRUE;
                gOneReadingDisplyed = FALSE;
            }
            else
            {
                gExitMemoryMode = FALSE;
                gMemorymode = FALSE;
                gOneReadingDisplyed = FALSE;
            }
            gDisplayPreviousReading = FALSE;
            __delay_ms(50);
        }
        if (IOCBFbits.IOCBF3 == 1)
        {
            IOCBFbits.IOCBF3 = 0;

            if (gMemorymode == TRUE)
            {

                gDisplayPreviousReading = TRUE;
                gSetDateTime = 0;
                __delay_ms(50);
            }
            else if (gSleepMode == TRUE)
            {
                gSetDateTime = TRUE;
                gMemorymode = FALSE;
                while(!(PORTB & 0x08));
                __delay_ms(50);
            }
            else
            {
                gSetDateTime = FALSE;
                gMemorymode = FALSE;
            }


        }
    }
    if (PIR1bits.ADIF == 1)
    {
       PIR1bits.ADIF = 0;

       if(ADRESH > 127){ADRESH = 0;ADRESL = 0;}
       gReadData = ADRESL;
       gReadData += ADRESH << 8;

        if(gReadData >= CAPTURE_START_VOLTAGE)                           // Threshold Value of 600mV checked here
        {
//           if (gcounter == COUNT_RESET_1)
//           {
//               LATCbits.LATC7 = 0;
//           } // uncomment above code for debug to test wating period for ADC capture
           
           if(gcounter <= 0)
           {
               gcounter = 0;
//               LATCbits.LATC7 = 1; // uncomment for debug to test wating period for ADC capture
           }

           else
           gcounter--;

           if(gcounter == 0)     // Wait for 2 seconds before capturing data
           {
                if(gglucoseIndex <= GLUCO_READ_COUNT)
                {
                      gSigmaGlucoseValue = (gSigmaGlucoseValue + gReadData)>>1;// moving average
                      gglucoseIndex++;
                      LATAbits.LATA3 = 1;
                }
                else
                {
                    INTCONbits.PEIE = 1;
                    PIE1bits.ADIE=1;
                    gglucDataReady = 1;
                    gglucoseIndex = 0;
                    gcounter = COUNT_RESET;
                    LATAbits.LATA3 = 0;
                }
            }
        } //(gReadData >= CAPTURE_START_VOLTAGE)
        else
        {
            
            if(gcountIdleTime <= 1)
            gcountIdleTime = 1;

            else
            gcountIdleTime--;

            if(gcountIdleTime == 1)
            {
                gBloodNotInsetrted=1;
            } 
         }

        if (gglucDataReady == 0)
        ADCON0bits.ADGO = 1;


    } // (PIR1bits.ADIF == 1)

    
}





