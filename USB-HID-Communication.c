/*
This program uses USB-HID communication to read and write values
*/

unsigned char readbuff[64] absolute 0x500;   // Buffers should be in USB RAM
unsigned char writebuff[64] absolute 0x540;
char cnt;
char kk;
void interrupt(){
   USB_Interrupt_Proc();
                      // USB servicing is done inside the interrupt
}
void main(void){
  ADCON1 |= 0x0F;                         // Configure all ports with analog function as digital
  CMCON  |= 7;
  TRISB=0;
  LATB=0;                            // Disable comparators
  HID_Enable(&readbuff,&writebuff);       // Enable HID communication
  while(1){
    while(!HID_Read());
    for(cnt=0;cnt<64;cnt++)
      writebuff[cnt]=readbuff[cnt];
      PORTB=readbuff[cnt];
      Delay_ms(1000);
    while(!HID_Write(&writebuff,64))

      ;
  }
}
