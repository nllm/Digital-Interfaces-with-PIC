/*
This program lets the PIC interact with the mbed and LabVIEW as a slave
*/


//Declaración de variables 
char DIP;
char led,K;
int asc=113;
unsigned char LEDS[5];
unsigned short duty;
unsigned int adc;
unsigned char dato[5];
unsigned char PWM[5];
float temperature;

//Programa principal
void main() {

//Inicio de Puerto serial y bluetooth
UART1_Init(9600);
Delay_ms(2000);
UART1_Write_Text("$$$");
Delay_ms(1000);
UART1_Write_Text("SM,0\n");
Delay_ms(1000);
UART1_Write_Text("---\n");
Delay_ms(1000);

//Declaracion de puertos analógicos y digitales
ADCON1=0b00001111;
TRISA.TRISA1 = 1;
TRISB = 0;
LATB = 0;
TRISD = 0xFF;
PORTC = 0;                          // set PORTC to 0
TRISC = 0;                          // designate PORTC pins as output
//Inicio de PWM
PWM1_Init(5000);                    // Initialize PWM1 module at 5KHz
Delay_ms(100);
PWM1_Start();
PWM1_Set_Duty(10);
Delay_ms(1000);

//Limpieza de buffer
K=UART1_Read();

//Ciclo infinito
while(1){
         //Si existe un dato por leer
         if (UART1_Data_Ready() == 1) {

         //Lectura de string de la mbed
         UART_Read_Text(LEDS, "%", 5);
         UART_Read_Text(PWM, "#", 6);
         
         //Conversion de valor string a char e impresión en leds
         led=LEDS[0];
         PORTB = led;

         //Conversion de string a entero e impresion como PWM
         duty=atoi(PWM);
         PWM1_Set_Duty(duty);
         Delay_ms(100);

         //Lectura de DIP y envio por serial
         DIP = PORTD;
         UART1_Write(DIP);
         UART1_Write_Text(",");
	
         //Adquisicion de temperatura, conversion e impresion por serial
         adc =  ADC_Read(1);
         temperature = (adc * 5.0 *100.0 ) / 1023.0;
         FloatToStr(temperature,dato);
         UART1_Write_Text(dato);
         UART1_Write_Text("\n");
         Delay_ms(500);

         }  }
}
