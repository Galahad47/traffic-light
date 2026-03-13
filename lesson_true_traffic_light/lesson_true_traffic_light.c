/*
 * lesson_true_traffic_light.c
 *
 * Created: 13.03.2026 10:11:20
 *  Author: akovalev
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
volatile uint8_t tiks; // если переменная изменяется в препрывании, то она не должна быть оптимизирвоана, т.е является константой
#define RED		PB0
#define GREEN	PB1
#define Button	PB2

#include <avr/io.h>
//Инициализация светодиодов
void led_ini(void){
	DDRB|=(1<<D1) | (1<<D2);
}

void red(){
	PORTB &=~ (1<<RED);
	PORTB|=(1<<GREEN);
}

void green(){
	PORTB&=~(1<<D2);
	PORTB|=(1<<D1);
}


uint8_t button(void){
	if(!(PINB&(1<<PB2))) return 1;
	return 0;
}



//Инициализация кнопок
void button_ini(void){
	PORTB|=(1<<D3);
}
//Таймер
void timer_ini(void){
	TCCR0B |=(1<<CS01) | (1<<CS00);//делитель 64
	TIMSK0 |=(1<<TOIE0); //разрешение на примененеие таймера
	TCNT0 = 106;// 256 - 150 = 106
}

ISR(TIM0_OVF_vect){
	if (tiks) tiks--;
	TCNT0 = 106;
}


int main(void)
{
	led_ini();button_ini();timer_ini();
	
	uint8_t status=0;
	sei();
    while(1)
    {
		switch (status){
			case 0:
			D1_D2_tik;
			tiks=250; // чрез 2 секунды
			status=1;
			break;
			
			case 1:
			if (!tiks) status=2;
			if(button()) status=2;
			break;
			
			case 2:
			D2_D1_tik();
			tiks=125;
			status = 3;
			break;
			case 3:
			if (!tiks) status=0;
			break;
		}
    }
}