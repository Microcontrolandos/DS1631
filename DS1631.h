/* 
	DS1631.h - High-Precision Digital Thermometer and Thermostat library for MikroC PRO PIC
	Author: Tiago Melo
	Blog: microcontrolandos.blogspot.com.br
*/

#define DS1631_ADDRESS( addr ) (0x90 | ( addr << 1 ))

/* Comandos */
#define DS1631_CMD_START_CONVERT 0x51
#define DS1631_CMD_STOP_CONVERT 0x22
#define DS1631_CMD_READ 0xAA
#define DS1631_CMD_ACCESS_TH 0xA1
#define DS1631_CMD_ACCESS_TL 0xA2
#define DS1631_CMD_ACCESS_CFG 0xAC
#define DS1631_CMD_SOFT_POR 0x54

typedef union
{
   char ONE_SHOT : 1; // 1 - One-Shot Mode, 0 - Continuous Conversion Mode
   char POL : 1;  // 1 - TOUT is active high, 0 - TOUT is active low
   char R : 2;    //00 -> 9 bits, 01 -> 10 bits, 10 -> 11 bits, 11 -> 12 bits
   char NVB : 1;  //A write to EEPROM memory is in progress
   char TLF : 1;
   char THF : 1;
   char DONE : 1; //Temperature conversion is complete.
}DS1631;

/* private */
static int DS1631_Read( char address, char reg );

/* public */
void DS1631_Init( char address, DS1631 * config );
void DS1631_Start( char address );
void DS1631_Stop( char address );
void DS1631_Reset( char address );
float DS1631_ReadT( char address );
float DS1631_ReadTL( char address );
float DS1631_ReadTH( char address );
void DS1631_Write( char address, float tl, float th );