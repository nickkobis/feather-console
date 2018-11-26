#ifndef F_CPU
#define F_CPU 1000000UL
#endif
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#define BUTTON_LEFT (1 << PB4)
#define BUTTON_RIGHT (1 << PB3)
#define LEFT_DATA (1 << PB1)
#define RIGHT_DATA (1 << PB0)


//xxxx x(left)(right)(shoot), 0 for no press, 1 for pressed
volatile enum button_state {Pressed, Released} left_state, right_state;


void turn_left_on(){
    DDRB = DDRB | LEFT_DATA;
    PORTB = PORTB | LEFT_DATA;
}
void turn_right_on(){
    DDRB = DDRB | RIGHT_DATA;
    PORTB = PORTB | RIGHT_DATA;
}

void turn_left_off(){
    DDRB = DDRB | LEFT_DATA;
    PORTB &= ~LEFT_DATA;
}
void turn_right_off(){
    DDRB = DDRB | RIGHT_DATA;
    PORTB &= ~RIGHT_DATA;
}


void output_state(){
    
    if(left_state == Pressed){
        turn_left_on();
    }else{
        turn_left_off();
    }
    if(right_state == Pressed){
        turn_right_on();
    }else{
        turn_right_off();
    }
    
}
<<<<<<< HEAD


=======
//not finished yet
ISR(PCINT0_vect){
    
    if(PINB & LISTENER){
        send_1;
        _delay_ms(100);
        clear();
        _delay_ms(100);
        send_1;
        _delay_ms(100);
        clear();
        _delay_ms(100);
        send_1;
        _delay_ms(100);
        clear();
    }else{
        
    }
    
}
>>>>>>> 20e5f275d7d2e36fff775835c1358196690b0d58

void main(){
    DDRB |= LEFT_DATA | RIGHT_DATA;
    PORTB = 0;
    uint8_t history_l =0;
    uint8_t history_r =0;
    uint8_t pin_read = 0;
    
    while(1){
        //read button states
        history_l = history_l << 1;
        history_r = history_r << 1;
        
        pin_read = PINB;
        if(pin_read & BUTTON_LEFT){
            history_l |=0x01;
        }
        
        if(pin_read & BUTTON_RIGHT){
            history_r |=0x01;
        }
        
        if(history_l == 0){
            left_state = Released;
        }
        if(history_r == 0){
            right_state = Released;
        }
        
        if(history_l == 0xff){
            left_state = Pressed;
        }
        if(history_r == 0xff){
            right_state =Pressed;
        }
        output_state();
    }
    
    
}
 
}
