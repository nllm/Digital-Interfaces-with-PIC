//1.============================================================================
//This program lets two PIC communicate with i2c protocol
//Master program
//==============================================================================
//2. ARCHIVOS DE CABECERA
//==============================================================================
// 3.===========================================================================
// DECLARACIÓN DE VARIABLES GLOBALES.
//==============================================================================
unsigned int lectura;
// 4.===========================================================================
// DECLARACIÓN DE PROTOTIPOS DE PROCEDIMIENTOS Y FUNCIONES.
//==============================================================================
void escribir_Pic(unsigned int address,
                  unsigned int send_data);   // Escribe al ESCLAVO
unsigned short leer_Pic();                   // Lee datos del ESCLAVO
void Init_Perifericos();                     //Iniciliza el PIC
// 5.===========================================================================
// DEFINICIÓN DE PROCEDIMIENTOS Y FUNCIONES DE LAS INTERRUPCIONES.
//==============================================================================

// 6.===========================================================================
// DEFINICIÓN DEL PROCEDIMIENTO DE ATENCIÓN A LAS INTERRUPCIONES.
//==============================================================================

// 7.===========================================================================
// DEFINICIÓN DE PROCEDIMIENTOS Y FUNCIONES DEL PROGRAMA PRINCIPAL.
//==============================================================================
void escribir_Pic(unsigned int address, unsigned int send_data){
     I2C1_Start();            //Inicia Bus I2C
     I2C1_Wr(0xB0);           //Envía dirección del ESCLAVO (dirección + W)
     I2C1_Wr(address);        //Envía dirección de almacenamiento en el ESCLAVO
     I2C1_Wr(send_data);      //Envía el dato a escribir en el ESCLAVO
     I2C1_Stop();             //Detiene Bus I2C
     delay_ms(50);
}

unsigned short leer_Pic(){
  unsigned short read_data;
  I2C1_Start();                //Inicia Bus I2C
  I2C1_Wr(0xB1);               //Envía dirección del ESCLAVO (dirección + R)
  read_data = I2C1_Rd(0);
  delay_ms(100);
  I2C1_Stop();                 //Detiene Bus I2C
  return read_data;
}

void Init_Perifericos(){
     ADCON1 = 0x0E;             // RA0 como entrada analógica, RA1-RA6 Digitales
     CMCON = 0b00000111;        // Deshabilita comparadores
     INTCON2 = 0x80;            // Deshabilita pull up en el puerto B

     // clears internal latches
     LATA = 0xFF;
     LATC = 0x00;
     LATD = 0x00;
     LATE = 0x00;

     TRISA = 0xFF;
     TRISB = 0x00;
     TRISC = 0x00;
     TRISD = 0x00;
     TRISE = 0x00;
}
// 8.===========================================================================
// DEFINICIÓN DEL PROGRAMA PRINCIPAL.
//==============================================================================
void main(){
   bit oldstate,oldstate1;
   Init_Perifericos();
   ADC_Init();
   UART1_Init(9600);
   I2C1_Init(100000);       //Inicializar Bus I2C a 100kHz
   delay_ms(500);
   while (1){
         lectura = ADC_Read(0)/4;       //Obtener una lectura de 8bits
         escribir_Pic(4,lectura);       //Escribimos al ESCLAVO
         Delay_ms(100);
         RC0_bit = 0;
         Delay_ms(100);

         if (Button(&PORTA, 1, 1, 1)) {               // Detect logical one
            oldstate = 1;                             // Update flag
         }
         if (oldstate && Button(&PORTA, 1, 1, 0)) { // Detect one-to-zero transition
            escribir_Pic(1,0x55);     //Escribimos una "U" al esclavo
            delay_ms(20);
            escribir_Pic(2,0x50);     //Escribimos una "P" al esclavo
            delay_ms(20);
            escribir_Pic(3,0x53);     //Escribimos una "S" al esclavo
            oldstate = 0;                              // Update flag
         }
   }
}
