/*
This program reads an analog value from a Dipswitch, a value from the terminal and writes them to the terminal and LEDs
*/
char datoanalog;
char datoserial;
void main() {
TRISB = 0; //Configuración PORTB como salida
LATB = 0; //Limpiar PORT

TRISD = 0xFF; //Configuración PORTD como entrada

UART1_Init(9600);
Delay_ms(100);
while(1){

if (UART1_Data_Ready()) {
   datoserial = UART1_Read();      //Leo terminal
   datoanalog = PORTD;             //Leo valor analógico
   UART1_Write(datoanalog);        //Enviar a la terminal el valor analógico
   LATB=datoserial;                //LED de terminal
   Delay_ms(500);
}}}
