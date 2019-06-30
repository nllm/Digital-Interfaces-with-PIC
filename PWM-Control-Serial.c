/*
This program lets the user control a PWM output via serial communication
*/

unsigned short current_duty, old_duty, current_duty1, old_duty1;
unsigned char bin;

void InitMain() {
  PORTA = 255;
  TRISA = 255;                        // configure PORTA pins as input
  PORTB = 0;                          // set PORTB to 0
  TRISB = 0;                          // designate PORTB pins as output
  PORTC = 0;                          // set PORTC to 0
  TRISC = 0;                          // designate PORTC pins as output
  PWM1_Init(5000);                    // Initialize PWM1 module at 5KHz
  PWM2_Init(5000);                    // Initialize PWM2 module at 5KHz
  UART1_Init(9600);
}

void main() {
  InitMain();
  current_duty  = 16;                 // initial value for current_duty
  current_duty1 = 16;                 // initial value for current_duty1

  PWM1_Start();                       // start PWM1
  PWM2_Start();                       // start PWM2
  PWM1_Set_Duty(current_duty);        // Set current duty for PWM1
  PWM2_Set_Duty(current_duty1);       // Set current duty for PWM2

  while (1) {                         // endless loop
  if (UART1_Data_Ready() == 1){
  bin=UART1_Read();
    if (bin == 'w') {                    // button on RA0 pressed
      Delay_ms(40);
      current_duty++;                 // increment current_duty
      PWM1_Set_Duty(current_duty);
     }

    if (bin == 's') {                    // button on RA1 pressed
      Delay_ms(40);
      current_duty--;                 // decrement current_duty
      PWM1_Set_Duty(current_duty);
     }

    if (bin=='d') {                    // button on RA2 pressed
      Delay_ms(40);
      current_duty1++;                // increment current_duty1
      PWM2_Set_Duty(current_duty1);
     }

    if (bin=='a') {                    // button on RA3 pressed
      Delay_ms(40);
      current_duty1--;                // decrement current_duty1
      PWM2_Set_Duty(current_duty1);
     }

    Delay_ms(5);                      // slow down change pace a little
  }}}
