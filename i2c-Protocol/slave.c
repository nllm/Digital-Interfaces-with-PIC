//1.============================================================================
//This program lets two PIC communicate with an i2c protocol
//Slave program
//==============================================================================
//2. ARCHIVOS DE CABECERA
//==============================================================================
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
// 3.===========================================================================
// DECLARACIÓN DE VARIABLES GLOBALES.
//==============================================================================
unsigned char rxbuffer,address,buff,dato, direccion;
unsigned short tx_data;
int ass=0;
// 4.===========================================================================
// DECLARACIÓN DE PROTOTIPOS DE PROCEDIMIENTOS Y FUNCIONES.
//==============================================================================
void initPerifericos();
unsigned short BcdToShort( unsigned short bcd );
unsigned short ShortToBcd( unsigned short valor);
// 5.===========================================================================
// DEFINICIÓN DE PROCEDIMIENTOS Y FUNCIONES DE LAS INTERRUPCIONES.
//==============================================================================

// 6.===========================================================================
// DEFINICIÓN DEL PROCEDIMIENTO DE ATENCIÓN A LAS INTERRUPCIONES.
//==============================================================================
void interrupt(){
     if (PIR1.SSPIF){                  //Comprueba si la interrupción es por I2C
        //PIR1.SSPIF = 0;                //Apagamos la bandera SSP
        if(!SSPSTAT.R_W & SSPSTAT.D_A & SSPSTAT.BF ){
            ass++;
            PORTB=2;
            if (ass==1){
               address=SSPBUF;        //Guardamos la dirección de almacenamiento
            }                         //del dato recibido.
            if (ass==2){
               rxbuffer=SSPBUF;       //Guardamos el dato recibido
               ass=0;
            }
            PIR1.SSPIF = 0;           //Apagamos la bandera SSP
        }

        if( !SSPSTAT.R_W & !SSPSTAT.D_A & SSPSTAT.BF ){
            buff = SSPBUF;
            PIR1.SSPIF = 0;
        }
        PIR1.SSPIF = 0;                //Apagamos la bandera SSP
        PIR2.BCLIF=0;
     }
}
// 7.===========================================================================
// DEFINICIÓN DE PROCEDIMIENTOS Y FUNCIONES DEL PROGRAMA PRINCIPAL.
//==============================================================================
void initPerifericos(){
     ADCON1 = 7;                     // Todos los puertos como digitales
     CMCON = 0b00000111;             // Deshabilita comparadores
     TRISA = 0;                      // Set PORTA as output
     //TRISB = 0;                      // Set PORTB as output
     //TRISC = 0b00011000;             // Set SCL y SDA como ingresos
     //TRISC.B3 = 1; // Set SCL (PORTC,3) pin como ingreso
     //TRISC.B4 = 1; // Set SDA (PORTC,4) pin como ingreso
     //PortB=0;
     TRISB = 0XFF; // Set SCL (PORTC,3) pin como ingreso

     //Configuracion de interrupciones
     INTCON = 0b11000000;
     SSPCON1 = 0b00111110;         // Modo esclavo 7 bits de direccion.
     SSPCON2 = 0x00;
     SSPADD = 0xB0;               //Dirección del dispositivo
     SSPSTAT=0x00;
     SSPCON1.SSPEN = 1;
     SSPSTAT.SMP = 1;
     SSPSTAT.CKE = 1;
     PIR1.SSPIF = 0;
     PIR2.BCLIF=0;

     PIE1.SSPIE = 1;         // Habilita la interrupcion del modulo SSP
     //INTCON.PEIE = 1;        // Habilita las interrupciones de los perifericos
     //INTCON.GIE = 1;         // Habilita las interrupciones globales!
}

unsigned short BcdToShort( unsigned short bcd ){
     unsigned short LV, HV;
     LV = bcd&0x0F;
     HV = (bcd>>4)&0x0F;
     return LV + HV*10;
}
unsigned short ShortToBcd( unsigned short valor){
     unsigned short HV, LV;
     HV = valor/10;
     LV = valor - HV*10;
     return LV + HV*16;
}
// 8.===========================================================================
// DEFINICIÓN DEL PROGRAMA PRINCIPAL.
//==============================================================================
void main(){
     char as[6];
     //ADCON1 |= 0x0F;
     //CMCON  |= 7;
     UART1_Init(9600);
     initPerifericos();
     Lcd_Init();               // Initialize LCD
     Lcd_Cmd(_LCD_CLEAR);       // Clear LCD display
     Lcd_Cmd(_LCD_CURSOR_OFF);  // Turn cursor off
     lcd_Out(1,1,"SLAVE");
     while (1){
           if (address==4){            //Si la dirección es 4 es dato del pot.
              intToStr(rxbuffer,as);
              lcd_out(1,10,as);
              delay_ms(50);

           }
           if (address!= 4){           //Si es diferente de 4 mostrar datos en
              dato=rxbuffer;           //el LCD.
              direccion=address;
              lcd_chr(2,direccion,dato);
           }
     }
}
