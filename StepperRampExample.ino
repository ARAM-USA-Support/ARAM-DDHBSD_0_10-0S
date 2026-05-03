//ARAM-DDHBSD_0_13-0S      Example Code                rev: 4/29/2026
#include "ARAM_FS_Stepper.h"

#define CNTRL_PIN_A 7 //change this to your cntrl A pin for your board
#define CNTRL_PIN_B 8  //change this to your cntrl B pin for your board
#define MICROS_TO_SECONDS 1000000.0

uint32_t timeClock;
uint32_t nextSwitch;
uint32_t startClock;
uint32_t rampEnd;

// Set frequencies in Hz
double startFreq = 10.0; // Start at 10Hz //change this to adjust your staritng speed
double endFreq = 300.0;  // Target at 300Hz //change this to adjust your final speed
double RAMP_TIME = 80.0;   // (Seconds) // Change this to make the speed up happen quicker

// Calculate rate of change in frequency (Hz per second)
double accel = (endFreq - startFreq) / RAMP_TIME;

//calculate current timestep based on starting speed
double actualTimeStep = MICROS_TO_SECONDS / startFreq;

//declare stepper motor
STEPPER stepper(CNTRL_PIN_A, CNTRL_PIN_B);


void setup() {
  //get start time
  startClock = micros();
  nextSwitch = startClock;
  //calculate end of ramp
  rampEnd = startClock + (uint32_t)(RAMP_TIME * MICROS_TO_SECONDS);
}

void loop() {
  //get current time
  timeClock = micros();

  //if it's time to step do so now
  if(timeClock > nextSwitch){
    stepper.moveStepperCCW();
    
    //if we're still in the early speed ramp up phase increase speed now
    if(timeClock < rampEnd){
      // Calculate elapsed time in seconds
      double t = (double)(timeClock - startClock) / MICROS_TO_SECONDS;
     
      // Current Frequency = Start Frequency + (Accel * Time)
      double currentFreq = startFreq + (accel * t);
      actualTimeStep = MICROS_TO_SECONDS / currentFreq;
    }
    
    // Schedule next step
    nextSwitch = timeClock + (uint32_t)actualTimeStep;
  }
}

