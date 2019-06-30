/*
This program uses USB-HID communication to read and write digital and analog values
*/

unsigned char readbuff[64] absolute 0x500;   // Buffers should be in USB RAM
unsigned char writebuff[64] absolute 0x540;
char cnt;
char kk;
unsigned char dato[5];
unsigned int adc;
float temperature;
char datoanalog;
void interrupt(){
   USB_Interrupt_Proc();
                      // USB servicing is done inside the interrupt
}
void main(void){
  //ADCON1 |= 0x0F;                         // Configure all ports with analog function as digital
  //CMCON  |= 7;
  //ADCON1=0b00001111;
  //TRISA.TRISA0 = 1;
  //TRISA.TRISA1 = 1;
  TRISD = 0xFF; //Configuración PORTB como salida
  TRISB=0;
  LATB=0;
                              // Disable comparators
  HID_Enable(&readbuff,&writebuff);       // Enable HID communication

  while(1){
  
    //adc =  ADC_Read(1);
    //temperature = (adc * 5.0 ) / 1023.0;
    //FloatToStr(temperature,dato);

    while(!HID_Read());
    for(cnt=0;cnt<64;cnt++)
      writebuff[cnt]=readbuff[cnt];
      PORTB=readbuff[cnt];
    for(cnt=0;cnt<64;cnt++)
      writebuff[cnt]=PORTD;



      //Delay_ms(1000);
      //datoanalog = PORTD;

    while(!HID_Write(&writebuff,64))

      ;
  }
}
