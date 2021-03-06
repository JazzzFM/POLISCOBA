/* MCU: PIC16F886 4MHz
Este programa emplea señales provenientes de las señales ópticas reflexivos con
el fin de determinar el comportamiento del dispositivo móvil y, de este modo,
dotarlo de la capacidad de esquivar obstáculo y realizar un barrido o limpieza
uniforme.
Asimismo, este programa esta estructurado de forma modular, con el fin de poder
acoplar facilmente el brazo robótico al dispositivo movil con el fin de
llegar a lugares inaccesibles.
*/
sbit b_secuencia at RB6_bit;
sbit stop at RB5_bit;
sbit brazo at RB4_bit;
sbit output at RA0_bit;
sbit retro at RA1_bit;
sbit sensor1 at RB0_bit;
sbit sensor2 at RB1_bit;
sbit sensor3 at RB2_bit;
sbit sensor4 at RB3_bit;
sbit motor1_derecha at RC1_bit;
sbit motor1_izquierda at RC3_bit;
sbit motor2_derecha at RC2_bit;
sbit motor2_izquierda at RC0_bit;
sbit enable at RC7_bit;
void avanza(); //Se define la función para avanzar en línea recta
void parar(); //Se define la función para detenerse
void config(); //Se define la función para configurar puertos y bits
void derecha(); //Se define la función para avanzar a la derecha
void izquierda();//Se define la función para avanzar a la izquierda
void arm();
//Se define la función para el acoplamiento del brazo
void main()
{
config(); //Se llama a la función config()
while(1) //Bucle infinito
{
while((b_secuencia==0)&&(stop==0)) //Se ejecuta lo demás cuando enable sea 1
{}
while(sensor1==0) //Mientras el sensor 1 no detecte nada el dispositivo
{avanza();} //seguira avanzando
delay_ms(100); //Se establece un retardo de 100 milisegundos
parar();
//Se detiene el dispositivo
36while(sensor2==0) //El dispositivo girará hacia la derecha mientras
{ derecha(); //el sensor 2 no detecte una pared que indique que
delay_ms(50); //ya se encuentra a 180 grados de esta respecto al
}
//norte del dispositivo
parar();
delay_ms(100);
avanza(); //Avanza por 600 milisegundos
delay_ms(550);
parar();
delay_ms(200);
while(sensor4==0) //El dispositivo girará a la derecha mientras el
{ derecha(); //el sensor 4 no detecte una pared que le indique
delay_ms(50); //que se encuentra a 90 grados de esta respecto al
}
//norte del dispositivo
parar();
delay_ms(200);
while(sensor1==0)
{avanza();}
delay_ms(100);
parar();
while(sensor3==0)
{ izquierda();
delay_ms(50);
}
parar();
delay_ms(100);
avanza();
delay_ms(550);
parar();
delay_ms(200);
while(sensor4==0)
{ izquierda();
delay_ms(50);
}
}
}
void config()
{
ANSEL=0;
ANSELH=0;
TRISA=0x00;
TRISB=0xFF;
TRISC=0x00;
PORTB=PORTA=PORTC=0;
C1ON_bit=0;
C2ON_bit=0;
PWM1_Init(5000);
37PWM2_Init(5000);
}
void avanza()
{ enable=1;
PWM1_Start();
PWM2_Start();
PWM1_Set_Duty(120);
PWM2_Set_Duty(130);
delay_ms(50);
}
void derecha()
{ enable=1;
PWM1_Start();
PWM2_Start();
PWM1_Set_Duty(0);
PWM2_Set_Duty(130);
delay_ms(50);
}
void izquierda()
{ enable=1;
PWM1_Start();
PWM2_Start();
PWM1_Set_Duty(120);
PWM2_Set_Duty(0);
delay_ms(50);
}
void parar()
{ enable=0;
motor1_derecha=0;
motor1_izquierda=0;
motor2_derecha=0;
motor2_izquierda=0;
PWM1_Set_Duty(0);
PWM2_Set_Duty(0);
PWM1_Stop();
PWM2_Stop();
}
void arm()
{ if(brazo==1)
{ output=1;
delay_ms(300);
while(retro==0)
{}
}
}
