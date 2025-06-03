/*
 * File:   test_capteur.c
 * Author: PittetL02
 *
 * Created on May 15, 2025, 2:16 PM
 */

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillateur interne
#pragma config WDTE = OFF       // Watchdog Timer OFF
#pragma config PWRTE = OFF      // Power-up Timer OFF
#pragma config MCLRE = ON       // MCLR pin enabled
#pragma config CP = OFF         // Code Protection OFF
#pragma config BOREN = ON       // Brown-out Reset enabled
#pragma config CLKOUTEN = OFF   // CLKOUT function disabled

// CONFIG2
#pragma config LVP = OFF        // Low-Voltage Programming OFF

#include <xc.h>
#include <stdint.h>

//----- Constant Definiton  ----------------------------

#define _XTAL_FREQ 4000000UL    // Fréquence pour __delay_ms()


//----- Global Variable Definitions------------------------
uint8_t lfsr = 0xAC; // Seed non nul

//----- Function Declarations -----------------------------
uint8_t lfsr_next(void); 
void InitPic(void);

//===== Main Function Implementation ======================

void main(void) 
{
    
    InitPic();
    
    while (1) 
    {
        uint8_t out = lfsr_next();
        LATAbits.LATA0 = out;  // Écrit sur RA0
        __delay_ms(50);        // Ajuster selon le besoin
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
    uint8_t bit = ((lfsr >> 7) ^ (lfsr >> 5) ^ (lfsr >> 4) ^ (lfsr >> 3)) & 1;
    lfsr = (lfsr << 1) | bit;
    return lfsr & 1;  // Renvoie le LSB
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
    ANSELB = 0; // Configuration des IO en mode Digital 
    ANSELC = 0; // Configuration des IO en mode Digital

    //Config Port
    LATA = 0b00000000; //
    LATB = 0b00000000; //
    LATC = 0b00000000; //

    //Config Tris
    TRISA = 0b00000100; //RA2 = input (Switch), RA0 output
    TRISB = 0b00000000; //tout outputs
    TRISC = 0b00000000; //
}
