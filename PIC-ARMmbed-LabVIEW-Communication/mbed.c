/*
This program lets the mbed interact with the PIC as a master, and as a slave with LabVIEW
*/

#include "mbed.h"
//Declaracion de puertos digitales y de comunicacion
Serial pic(p28, p27);
DigitalOut L1(p20);
DigitalOut L2(p19);
DigitalOut L3(p18);
DigitalOut L4(p17);
DigitalIn D1(p6);
DigitalIn D2(p7);
DigitalIn D3(p8);
DigitalIn D4(p9);

//Inicio del programa principal
int main() {
    //Inicia configuracion del bluetooth
    wait(6);
    pic.printf("$$$");
    wait(1);
    pic.printf("SM,1\n");
    wait(1);
    pic.printf("C,0006666A4CF4\n");
    wait(1);
    pic.printf("---\n");
    wait(1);

    //Definir puertos digitales de entrada como PullUp
    D1.mode(PullUp);
    D2.mode(PullUp);
    D3.mode(PullUp);
    D4.mode(PullUp);
	
    //Declaración de variables
    int d1,d2,d3,d4,i=0,g=0;
    char delab[20];
    char dembed[20];

    //Limpieza del buffer del bluetooth
    pic.scanf("%");
    pic.scanf("%s", &dembed);
    pic.scanf("%s", &dembed);

    //Ciclo infinito
    while(1) {
	
        //Esperar por instruccion para empezar como maestro o como esclavo
        float start;
        if(g==0){
        scanf(" %f", &start);
        scanf("%");
        g=1;}
        
        //Inicio como maestro
        if(start==1){
        float l1,l2,l3,l4;

        //Lectura de cuatro leds virtuales y escritura en fisicos
        scanf("%f,%f,%f,%f", &l4,&l3,&l2,&l1);
        L1=l1;
        L2=l2;
        L3=l3;
        L4=l4;
       
       //Lectura de DIP y escritura en leds virtuales
        d1=D1.read();
        d2=D2.read();
        d3=D3.read();
        d4=D4.read();
        printf(" %i %i %i %i",d1,d2,d3,d4);
        scanf("%");
        wait(0.1);}
        
        //Programa del esclavo
        if(start==2){
        
        //Lectura de string labview y escritura en PIC
        scanf("%s", &delab);
        pic.printf("%s", delab);
     
        //Lectura de string de PIC y escritura en labview
        pic.scanf("%s", &dembed);
        printf("%s", dembed);
        scanf("%");
        wait(0.3);}
}}
