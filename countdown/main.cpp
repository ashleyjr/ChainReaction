// Target: Nucleo-401RE dev board
// IDE: mbed online compilier


#include "mbed.h"

#define PERIOD 0.02f

// Class instances
DigitalOut  led(LED1);
DigitalIn   trigger(USER_BUTTON);
PwmOut      servo_1(D2);
PwmOut      servo_2(D3);
DigitalOut  relay(D4);
Ticker      countdown;


// Globals
volatile int count;
volatile bool action;

// Ticks down once every second
void down() {
    led = !led;
    count--;
    action = true;
}

int main() {
    int trigger_state;
    
    // PWM setup
    servo_1.period(PERIOD);                         // Frequency of pwm to drive servo
    servo_2.period(PERIOD);


    // Digital out setup
    relay = 0;
    
    
    // Hang until trigger changes state
    trigger_state = trigger;
    while(trigger_state == trigger);
    led = 1;                                        // On to start
    count = 6;                                      // The first states
    action = true;                                  // Go straight into first state action
    countdown.attach(&down, 1);                     // Point to ticker, start counting
    
    
    // Do the routine
    while(count > 0){                               // Keep in loop until count reaches zero
        if(action){                                 // Ticker has to start an action
            switch(count){
                case 6:     servo_1.write(0.1f);
                            wait(0.5);
                            servo_1.write(0.0f);
                            break;
                            
                case 5:     servo_2.write(0.1f);
                            wait(0.5);
                            servo_2.write(0.0f);
                            break;
                            
                case 4:     relay = 1;
                            wait(0.1);
                            relay = 0;
                            wait(0.1);
                            relay = 1;
                            wait(0.1);
                            relay = 0;
                            wait(0.1);
                            relay = 1;
                            wait(0.1);
                            relay = 0;
                            wait(0.1);
                            relay = 1;
                            wait(0.1);
                            relay = 0;
                            wait(0.1);
                            break;
                            
                case 3:     servo_2.write(0.1f);
                            wait(0.5);
                            servo_2.write(0.0f);
                            break;
                            
                case 2:     servo_1.write(0.1f);
                            wait(0.5);
                            servo_1.write(0.0f);
                            break;
                            
                case 1:     
                            break;
            }
            action = false;
        }
    }

    while(1){}  // Lock up, job done
}