/*
 * File:   test_capteur.c
 * Author: PittetL02
 *
 * Created on May 23, 2025, 1:00 PM
 */

// CONFIG1
#pragma config FEXTOSC = OFF    // External Oscillator Mode Selection bits (Oscillator not enabled)
#pragma config RSTOSC =  HFINTOSC_1MHZ// Power-up Default Value for COSC bits (HFINTOSC (32 MHz))
#pragma config CLKOUTEN = OFF   // Clock Out Enable bit (CLKOUT function is disabled; I/O function on RA4)
#pragma config VDDAR = HI       // VDD Range Analog Calibration Selection bit (Internal analog systems are calibrated for operation between VDD = 2.3V - 5.5V)

// CONFIG2
#pragma config MCLRE = EXTMCLR  // Master Clear Enable bit (If LVP = 0, MCLR pin is MCLR; If LVP = 1, RA3 pin function is MCLR)
#pragma config PWRTS = PWRT_OFF // Power-up Timer Selection bits (PWRT is disabled)
#pragma config WDTE = ON        // WDT Operating Mode bits (WDT enabled regardless of Sleep; SEN bit is ignored)
#pragma config BOREN = ON       // Brown-out Reset Enable bits (Brown-out Reset Enabled, SBOREN bit is ignored)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection bit (Brown-out Reset Voltage (VBOR) set to 1.9V)
#pragma config PPS1WAY = ON     // PPSLOCKED One-Way Set Enable bit (The PPSLOCKED bit can be set once after an unlocking sequence is executed; once PPSLOCKED is set, all future changes to PPS registers are prevented)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable bit (Stack Overflow or Underflow will cause a reset)

// CONFIG3

// CONFIG4
#pragma config BBSIZE = BB512   // Boot Block Size Selection bits (512 words boot block size)
#pragma config BBEN = OFF       // Boot Block Enable bit (Boot Block is disabled)
#pragma config SAFEN = OFF      // SAF Enable bit (SAF is disabled)
#pragma config WRTAPP = OFF     // Application Block Write Protection bit (Application Block is not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot Block is not write-protected)
#pragma config WRTC = OFF       // Configuration Registers Write Protection bit (Configuration Registers are not write-protected)
#pragma config WRTSAF = OFF     // Storage Area Flash (SAF) Write Protection bit (SAF is not write-protected)
#pragma config LVP = ON         // Low Voltage Programming Enable bit (Low Voltage programming enabled. MCLR/Vpp pin function is MCLR. MCLRE Configuration bit is ignored.)

// CONFIG5
#pragma config CP = OFF         // User Program Flash Memory Code Protection bit (User Program Flash Memory code protection is disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdint.h>

//----- Constant Definiton  ----------------------------

#define _XTAL_FREQ 4000000  // Fréquence d'oscillateur interne


//----- Global Variable Definitions------------------------
// LFSR 8 bits : taps sur bits 7, 5, 4, 3 (polynôme x^8 + x^6 + x^5 + x^4 + 1)
uint8_t lfsr = 0xA5;  // 0x75 (Wikipédia) // 0xA5 (ChatGPT)(meilleur seed)

//----- Function Declarations -----------------------------
uint8_t lfsr_next(void); 
void InitPic(void);

//===== Main Function Implementation ======================

void main(void) 
{
    InitPic();

    while (1)
    {
        uint8_t out = lfsr_next();       // bit pseudo-aléatoire
        LATAbits.LATA5 = out;            // sortie sur RA5
        __delay_ms(10);                  // fréquence de sortie (ajuste au besoin)
    }
}

//---------------------------------------------------------

//---------------------------------------------------------
// Sous programme lfsr_next
// Auteur: yassinn
// Desc.: Initialisation du PIC
// Ver. Date: V00 20230207 Création (YYYYMMDD)	
//--------------------------------------------------------

uint8_t lfsr_next(void) 
{
    uint8_t bit = (((lfsr >> 7) ^ (lfsr >> 5)) ^ (lfsr >> 4) ^ (lfsr >> 3)) & 1; // Bit 0,2,3 et 4 passé dans des XOR.
    lfsr = (lfsr << 1) | bit; // décalage de bit
    return lfsr & 1;
}

//---------------------------------------------------------

//---------------------------------------------------------
// Sous programme InitPic
// Auteur: yassinn
// Desc.: Initialisation du PIC
// Ver. Date: V00 20230207 Création (YYYYMMDD)	
//--------------------------------------------------------
void InitPic(void) 
{
//    TRISA0 = 0;           // RA0 en sortie
//    ANSELA = 0;           // Tous les ports A en numérique
//    LATAbits.LATA0 = 0;   // État initial
    
    // Config Oscillator    
    OSCCON = 0b01101010;  // 4 MHz



    //Configuration AD PIC
    ANSELA = 0; // Configuration des IO en mode Digital 
    //ANSELB = 0; // Configuration des IO en mode Digital 
    //ANSELC = 0; // Configuration des IO en mode Digital

    //Config Port
    LATA = 0b00000000; //
    //LATB = 0b00000000; //
    //LATC = 0b00000000; //

    //Config Tris
    TRISA = 0b00000000; //RA2 = input (Switch), RA0 output
    //TRISB = 0b00000000; //tout outputs
    //TRISC = 0b00000000; //
    
}
