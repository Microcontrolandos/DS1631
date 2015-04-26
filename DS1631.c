/* 
	DS1631.c - High-Precision Digital Thermometer and Thermostat library for MikroC PRO PIC
	Author: Tiago Melo
	Blog: microcontrolandos.blogspot.com.br
*/

#include "DS1631.h"

static int DS1631_Read( char address, char reg )
{
int rData;
   Soft_I2C_Start(); //sinal de start
   Soft_I2C_Write( DS1631_ADDRESS( address ) ); //envia o endereço do dispositivo + modo de escrita
   Soft_I2C_Write( reg ); //envia o comando de acesso ao registro
   Soft_I2C_Start(); //sinal de start
   Soft_I2C_Write( DS1631_ADDRESS( address ) | 1 ); //envia o endereço do dispositivo + modo de leitura
   ((char*)&rData)[1] = Soft_I2C_Read( 1 ); //le o byte mais significativo
   ((char*)&rData)[0] = Soft_I2C_Read( 0 ); //le o byte menos significativo
   Soft_I2C_Stop(); //sinal de stop
   return rData;
}

void DS1631_Init( char address, DS1631 * config )
{
   Soft_I2C_Start(); //sinal de start
   Soft_I2C_Write( DS1631_ADDRESS( address ) ); //envia o endereço do dispositivo + modo de escrita
   Soft_I2C_Write( DS1631_CMD_ACCESS_CFG ); //envia o comando de acesso ao registro de configuração
   Soft_I2C_Write( *(char*)config ); //envia o valor da configuração
   Soft_I2C_Stop(); //sinal de stop
   Delay_ms( 10 ); //EEPROM Write Cycle Time
}

void DS1631_Start( char address )
{
   Soft_I2C_Start(); //sinal de start
   Soft_I2C_Write( DS1631_ADDRESS( address ) ); //envia o endereço do dispositivo + modo de escrita
   Soft_I2C_Write( DS1631_CMD_START_CONVERT );  //envia o comando para iniciar a conversão
   Soft_I2C_Stop(); //sinal de stop
}

void DS1631_Stop( char address )
{
   Soft_I2C_Start(); //sinal de start
   Soft_I2C_Write( DS1631_ADDRESS( address ) ); //envia o endereço do dispositivo + modo de escrita
   Soft_I2C_Write( DS1631_CMD_STOP_CONVERT );  //envia o comando para parar a conversão
   Soft_I2C_Stop(); //sinal de stop
}

void DS1631_Reset( char address )
{
   Soft_I2C_Start(); //sinal de start
   Soft_I2C_Write( DS1631_ADDRESS( address ) ); //envia o endereço do dispositivo + modo de escrita
   Soft_I2C_Write( DS1631_CMD_SOFT_POR ); //envia o comando de reset
   Soft_I2C_Stop(); //sinal de stop
}

float DS1631_ReadT( char address )
{
   return (float)( DS1631_Read( address, DS1631_CMD_READ ) >> 4 ) * 0.0625;
}

float DS1631_ReadTL( char address )
{
   return (float)( DS1631_Read( address, DS1631_CMD_ACCESS_TL ) >> 4 ) * 0.0625;
}

float DS1631_ReadTH( char address )
{
   return (float)( DS1631_Read( address, DS1631_CMD_ACCESS_TH ) >> 4 ) * 0.0625;
}

void DS1631_Write( char address, float tl, float th )
{
int temperature;
   temperature = (int)( th * 256 );
   Soft_I2C_Start();
   Soft_I2C_Write( DS1631_ADDRESS( address ) );
   Soft_I2C_Write( DS1631_CMD_ACCESS_TH );
   Soft_I2C_Write( ((char*)&temperature)[1] ); //MSB
   Soft_I2C_Write( ((char*)&temperature)[0] ); //LSB
   Soft_I2C_Stop();
   
   Delay_ms( 10 ); //EEPROM Write Cycle Time

   temperature = (int)( tl * 256 );
   Soft_I2C_Start();
   Soft_I2C_Write( DS1631_ADDRESS( address ) );
   Soft_I2C_Write( DS1631_CMD_ACCESS_TL );
   Soft_I2C_Write( ((char*)&temperature)[1] ); //MSB
   Soft_I2C_Write( ((char*)&temperature)[0] ); //LSB
   Soft_I2C_Stop();

   Delay_ms( 10 ); //EEPROM Write Cycle Time
}