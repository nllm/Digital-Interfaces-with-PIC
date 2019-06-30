/*
This program let the user communicate via Bluetooth, which is used as a serial ccmmunication 
*/

                       // LCD module connections
sbit LCD_RS at LATD4_bit;
sbit LCD_EN at LATD5_bit;
sbit LCD_D4 at LATD0_bit;
sbit LCD_D5 at LATD1_bit;
sbit LCD_D6 at LATD2_bit;
sbit LCD_D7 at LATD3_bit;

sbit LCD_RS_Direction at TRISD4_bit;
sbit LCD_EN_Direction at TRISD5_bit;
sbit LCD_D4_Direction at TRISD0_bit;
sbit LCD_D5_Direction at TRISD1_bit;
sbit LCD_D6_Direction at TRISD2_bit;
sbit LCD_D7_Direction at TRISD3_bit;
// End LCD module connections
char dato1;
char dato2;
void main() {
ADCON1 |= 0x0F;
CMCON  |= 7;

  Lcd_Init();                // Inicializa LCD
  Lcd_Cmd(_Lcd_CLEAR);       // Limpiar display
  Lcd_Cmd(_Lcd_CURSOR_OFF);  // Desactivar cursor

TRISB = 0; //Configuración PORTB como salida
LATB = 0; //Limpiar PORT
UART1_Init(38400);
Delay_ms(100);
Lcd_Out(1,1,"Bluetooth-lcd");
Lcd_Out(2,1,"Connecting...");
Delay_ms(2000);
Lcd_Cmd(_LCD_CLEAR);               // Clear display


while(1){

if (UART1_Data_Ready()) {
   dato1 = UART1_Read();
   //UART1_Write(dato2);
   Lcd_Chr_Cp(dato1);
   Delay_ms(1000);
   //Lcd_Cmd(_LCD_CLEAR);
}
}
