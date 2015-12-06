// Target: Nucleo-401RE dev board
// IDE: mbed online compilier


#include "mbed.h"

#define PERIOD 0.02f

// Class instances
DigitalOut  led(LED1);
DigitalIn   index_flip(USER_BUTTON);
DigitalIn   trigger(D7);
PwmOut      cdi_rocket(D6);
PwmOut      wat_rocket(D5);
PwmOut      css_rocket(D4);
DigitalOut  sol_rocket(D3);
DigitalOut  flipchart(D2);
Ticker      countdown;


// Globals
volatile int count;

// Ticks down once every ms
void down() {
    count--;
}

int main() {
    int trigger_state;
    int count_last;
    
    // PWM setup
    cdi_rocket.period(PERIOD);                         // Frequency of pwm to drive servo
    wat_rocket.period(PERIOD);
    css_rocket.period(PERIOD);

    // Digital out setup
    sol_rocket = 0;
    flipchart = 0;
    led = 0;
    
    
    // Hang until trigger changes state and index if needed
    while(trigger == 0){
        if(index_flip){
            flipchart = 0;    
        }else{
            flipchart = 1;    
        }
    }

    
    // Countdown start
    count = 18001;                                   // Time in 1ms chunks
    count_last = count;
    countdown.attach(&down, 0.001);                 // Point to ticker, start counting
    
    
    // Do the routine which updates every 1ms
    while(count > 0){                               // Keep in loop until count reaches zero
        if(count != count_last){                    // Ticker has to start an action
            switch(count){  
            
                // Reveal flipchart 5
                case 18000:  led = 1;
                            flipchart = 1;
                            break;
                            
                case 17400:  led = 0;
                            flipchart = 0;
                            break;
                            
                            
                // Reveal flipchart 4
                case 15000:  led = 1;
                            flipchart = 1;
                            break;
                            
                case 14400:  led = 0;
                            flipchart = 0;
                            break;
                            
                
                // Reveal flipchart 3 and launch water rocket
                case 12000:  led = 1;
                            flipchart = 1;
                            wat_rocket.write(0.1f);
                            break;
                            
                case 11400: led = 0;
                            flipchart = 0;
                            break;
                            
                case 9001: wat_rocket.write(0.0f);
                            break;
                
                // Reveal flipchart 2 and launch c02 rocket
                case 9000:  led = 1;
                            flipchart = 1;
                            cdi_rocket.write(0.1f);
                            break;
                            
                case 8400:  led = 0;
                            flipchart = 0;
                            cdi_rocket.write(0.0f);
                            break;
                            
                      
                // Reveal flipchart 1 and launch solid rocket
                case 6000:  led = 1;
                            flipchart = 1;
                            sol_rocket = 1;
                            break;
                            
                case 5400: led = 0;
                            flipchart = 0;
                            sol_rocket = 0;
                            break;   
                            
                            
                // Reveal flipchart 0 and launch css rocket
                case 3000:  led = 1;
                            flipchart = 1;
                            css_rocket.write(0.1f);
                            break;
                            
                case 2400:  led = 0;
                            flipchart = 0;
                            css_rocket.write(0.0f);
                            break;   
                            
                            
                
               
            }
            count_last = count;
        }
    }

    while(1){}  // Lock up, job done
}