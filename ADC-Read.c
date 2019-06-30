/*
This program reads an Analog Voltage from a LM35 sensor and sends the value with serial communication
*/

unsigned char dato[5];
unsigned char dato2[5];
unsigned char bin;
unsigned int adc;
unsigned int adc2;
float temperature;
float temperature2;
void main()
{
ADCON1=0b00001111;
TRISA.TRISA0 = 1;
TRISA.TRISA1 = 1;
TRISD = 0;
TRISB = 0;
LATB = 0;
Delay_ms(100);
UART1_Init(9600);

         while(1)
                 {
                 if (UART1_Data_Ready() == 1)
                 {
                 adc =  ADC_Read(1);
                 PORTB = adc;
                 PORTD = adc >> 8;
                 temperature = (adc * 5.0 ) / 1023.0;
                 FloatToStr(temperature,dato);
                 UART1_Write_Text("Vol:");
                 UART1_Write_Text(dato);
                 UART1_Write_Text("\r\n");
                 adc2 =  ADC_Read(0);
                 temperature2 = (adc2 * 5.0 *100.0 ) / 1023.0;
                 FloatToStr(temperature2,dato2);
                 UART1_Write_Text("LM35:");
                 UART1_Write_Text(dato2);
                 UART1_Write_Text("\r\n");
                 UART1_Write_Text("\r\n");
                 Delay_ms(1000);
}}}
