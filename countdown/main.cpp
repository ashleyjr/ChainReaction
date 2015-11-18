// Target: Nucleo-401RE dev board
// IDE: mbed online compilier


#include "mbed.h"

#define PERIOD 0.02f

// Class instances
DigitalOut  led(LED1);
DigitalIn   trigger(USER_BUTTON);
PwmOut      servo_1(D2);
PwmOut      servo_2(D3);
PwmOut      servo_3(D4);
PwmOut      servo_4(D5);
PwmOut      servo_5(D6);
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
    servo_3.period(PERIOD);
    servo_4.period(PERIOD);
    servo_5.period(PERIOD);
    
    
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
                            servo_2.write(0.2f);
                            servo_3.write(0.3f);
                            servo_4.write(0.4f);
                            servo_5.write(0.5f);
                            wait(0.6);
                            servo_1.write(0.0f);
                            servo_2.write(0.0f);
                            servo_3.write(0.0f);
                            servo_4.write(0.0f);
                            servo_5.write(0.0f);
                            break;
                            
                case 5:     servo_1.write(0.5f);
                            servo_2.write(0.4f);
                            servo_3.write(0.3f);
                            servo_4.write(0.2f);
                            servo_5.write(0.1f);
                            wait(0.5);
                            servo_1.write(0.0f);
                            servo_2.write(0.0f);
                            servo_3.write(0.0f);
                            servo_4.write(0.0f);
                            servo_5.write(0.0f);
                            break;
                            
                case 4:     servo_1.write(0.9f);
                            servo_2.write(0.9f);
                            servo_3.write(0.9f);
                            servo_4.write(0.9f);
                            servo_5.write(0.9f);
                            wait(0.4);
                            servo_1.write(0.0f);
                            servo_2.write(0.0f);
                            servo_3.write(0.0f);
                            servo_4.write(0.0f);
                            servo_5.write(0.0f);
                            break;
                            
                case 3:     servo_1.write(0.5f);
                            servo_2.write(0.5f);
                            servo_3.write(0.5f);
                            servo_4.write(0.5f);
                            servo_5.write(0.5f);
                            wait(0.3);
                            servo_1.write(0.0f);
                            servo_2.write(0.0f);
                            servo_3.write(0.0f);
                            servo_4.write(0.0f);
                            servo_5.write(0.0f);
                            break;
                            
                case 2:     servo_1.write(0.5f);
                            servo_2.write(0.5f);
                            servo_3.write(0.5f);
                            servo_4.write(0.5f);
                            servo_5.write(0.5f);
                            wait(0.2);
                            servo_1.write(0.0f);
                            servo_2.write(0.0f);
                            servo_3.write(0.0f);
                            servo_4.write(0.0f);
                            servo_5.write(0.0f);
                            break;
                            
                case 1:     servo_1.write(0.5f);
                            servo_2.write(0.5f);
                            servo_3.write(0.5f);
                            servo_4.write(0.5f);
                            servo_5.write(0.5f);
                            wait(0.1);
                            servo_1.write(0.0f);
                            servo_2.write(0.0f);
                            servo_3.write(0.0f);
                            servo_4.write(0.0f);
                            servo_5.write(0.0f);
                            break;
            }
            action = false;
        }
    }

    while(1){}  // Lock up, job done
}