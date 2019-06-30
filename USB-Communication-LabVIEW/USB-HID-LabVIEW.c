/*
This program uses USB-HID protocol to interact with LabVIEW
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
   USB_Interrupt_Proc();           // USB servicing is done inside the interrupt
}
void main(void){ 
 TRISD = 0xFF; //Configuración PORTB como salida
  TRISB=0;
  LATB=0; // Disable comparators
  HID_Enable(&readbuff,&writebuff);       // Enable HID communication

  while(1){
    while(!HID_Read());
    for(cnt=0;cnt<64;cnt++)
      writebuff[cnt]=readbuff[cnt];
      PORTB=readbuff[cnt];
    for(cnt=0;cnt<64;cnt++)
      writebuff[cnt]=PORTD;
    while(!HID_Write(&writebuff,64));
  }}
