// Target: Nucleo-401RE dev board
// IDE: mbed online compilier


#include "mbed.h"

// Class instances
DigitalOut  led(LED1);
PwmOut      servo_1(D1);
PwmOut      servo_2(D2);
PwmOut      servo_3(D3);
PwmOut      servo_4(D4);
PwmOut      servo_5(D5);
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
    led = 1;                                        // On to start
    count = 6;                                      // The first states
    action = true;                                  // Go straight into first state action
    countdown.attach(&down, 1);                     // Point to ticker
    
    servo_1.period(0.001f);                         // Frequency of pwm to drive servo
    while(count > 0){                               // Keep in loop until count reaches zero
        if(action){                                 // Ticker has to start an action
            switch(count){
                case 6:     servo_1.write(0.5f);
                            wait(0.5);
                            servo_1.write(0.0f);
                            break;
                            
                case 5:     servo_1.write(0.45f);
                            wait(0.5);
                            servo_1.write(0.0f);
                            break;
                            
                case 4:     servo_1.write(0.3f);
                            wait(0.5);
                            servo_1.write(0.0f);
                            break;
                            
                case 3:     servo_1.write(0.25f);
                            wait(0.5);
                            servo_1.write(0.0f);
                            break;
                            
                case 2:     servo_1.write(0.2f);
                            wait(0.5);
                            servo_1.write(0.0f);
                            break;
                            
                case 1:     servo_1.write(0.15f);
                            wait(0.5);
                            servo_1.write(0.0f);
                            break;
            }
            action = false;
        }
    }

    while(1){}  // Lock up, job done
