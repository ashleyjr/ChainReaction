// Target: Nucleo-401RE dev board
// IDE: mbed online compilier


#include "mbed.h"

#define PERIOD 0.02f

// Class instances
DigitalOut  led(LED1);
DigitalIn   trigger(USER_BUTTON);
PwmOut      cdi_rocket(D2);
PwmOut      wat_rocket(D3);
PwmOut      css_rocket(D4);
DigitalOut  sol_rocket(D5);
DigitalOut  flipchart(D6);
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
    
    
    // Hang until trigger changes state
    trigger_state = trigger;
    while(trigger_state == trigger);
    
    // Countdown start
    count = 6001;                                   // Time in 1ms chunks
    count_last = count;
    countdown.attach(&down, 0.001);                 // Point to ticker, start counting
    
    
    // Do the routine which updates every 1ms
    while(count > 0){                               // Keep in loop until count reaches zero
        if(count != count_last){                    // Ticker has to start an action
            switch(count){  
            
                // Reveal flipchart 5
                case 6000:  led = 1;
                            flipchart = 1;
                            break;
                            
                case 5800:  led = 0;
                            flipchart = 0;
                            break;
                            
                            
                // Reveal flipchart 4
                case 5000:  led = 1;
                            flipchart = 1;
                            break;
                            
                case 4800:  led = 0;
                            flipchart = 0;
                            break;
                            
                
                // Reveal flipchart 3 and launch water rocket
                case 4000:  led = 1;
                            flipchart = 1;
                            wat_rocket.write(0.1f);
                            break;
                            
                case 3800:  led = 0;
                            flipchart = 0;
                            wat_rocket.write(0.0f);
                            break;
                            
                
                // Reveal flipchart 2 and launch c02 rocket
                case 3000:  led = 1;
                            flipchart = 1;
                            cdi_rocket.write(0.1f);
                            break;
                            
                case 2800:  led = 0;
                            flipchart = 0;
                            cdi_rocket.write(0.0f);
                            break;
                            
                      
                // Reveal flipchart 1 and launch solid rocket
                case 2000:  led = 1;
                            flipchart = 1;
                            sol_rocket = 1;
                            break;
                            
                case 1800:  led = 0;
                            flipchart = 0;
                            sol_rocket = 0;
                            break;   
                            
                            
                // Reveal flipchart 0 and launch css rocket
                case 1000:  led = 1;
                            flipchart = 1;
                            cdi_rocket.write(0.1f);
                            break;
                            
                case 800:   led = 0;
                            flipchart = 0;
                            cdi_rocket.write(0.0f);
                            break;   
                
                
               
            }
            count_last = count;
        }
    }

    while(1){}  // Lock up, job done
}
