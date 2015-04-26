#include "DS1631.h"

/* Pinos do LCD */
sbit LCD_RS at RB0_bit;
sbit LCD_EN at RB1_bit;
sbit LCD_D4 at RB2_bit;
sbit LCD_D5 at RB3_bit;
sbit LCD_D6 at RB4_bit;
sbit LCD_D7 at RB5_bit;
sbit LCD_RS_Direction at TRISB0_bit;
sbit LCD_EN_Direction at TRISB1_bit;
sbit LCD_D4_Direction at TRISB2_bit;
sbit LCD_D5_Direction at TRISB3_bit;
sbit LCD_D6_Direction at TRISB4_bit;
sbit LCD_D7_Direction at TRISB5_bit;

/* Pinos do DS1631 */
sbit Soft_I2C_Scl at RB6_bit;
sbit Soft_I2C_Sda at RB7_bit;
sbit Soft_I2C_Scl_Direction at TRISB6_bit;
sbit Soft_I2C_Sda_Direction at TRISB7_bit;

DS1631 termometro; //configuração do DS1631
char msg[12]; //texto que será exibido no display

void main()
{
    Lcd_Init();
    Lcd_Cmd( _LCD_CLEAR );
    Lcd_Cmd( _LCD_CURSOR_OFF );

    termometro.ONE_SHOT = 0; //modo continuo
    termometro.POL = 1; //Tout ativado com nível lógico alto
    termometro.R = 0b11; //resolucao 12 bits
    //Inicializa o DS1631
    DS1631_Init( 0, &termometro );
    //Define os valores de TL e TH
    DS1631_Write( 0, 25, 30 );
    //Inicia a conversao
    DS1631_Start( 0 );

    while(1)
    {
           Delay_ms( 750 );
           //Realiza a leitura da temperatura e converte para string
           FloatToStr( DS1631_ReadT( 0 ), msg );
           //Escreve no display LCD
           Lcd_Cmd( _LCD_CLEAR );
           Lcd_Out( 1, 5, "DS1631" );
           Lcd_Out( 2, 1, "Temp: " );
           Lcd_Out_CP( msg );
           Lcd_Chr_CP( 223 );
           Lcd_Chr_CP( 'C' );
    }
}