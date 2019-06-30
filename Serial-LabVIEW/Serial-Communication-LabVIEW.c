/*
This program maintains a serial communication with a LabVIEW program to read and write values
*/

char datoanalog;
char datoserial;
void main() {
TRISB = 0; //Configuración PORTB como salida
LATB = 0; //Limpiar PORT

TRISD = 0xFF; //Configuración PORTB como salida

UART1_Init(9600);
Delay_ms(100);
while(1){

if (UART1_Data_Ready()) {
   datoserial = UART1_Read();      //Leo terminal
   datoanalog = PORTD;                           //Leo analogico
   UART1_Write(datoanalog);                                     //Mando para la terminal el analogico
   LATB=datoserial;                                             //LED de terminal
   Delay_ms(500);
}
}
}
