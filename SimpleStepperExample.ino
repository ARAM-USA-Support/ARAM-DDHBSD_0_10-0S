#define CNTRL_PIN_A 2     //change me to your desired cntrl pin A
#define CNTRL_PIN_B 1     //change me to your desired cntrl pin B
#define MICROS_TO_SECONDS (1000000)
uint32_t timeClock;
uint32_t nextSwitch;
int switchFrequency = 100; //change me to your desired switching frequency (Hertz))
double timeStep = MICROS_TO_SECONDS/switchFrequency;

int stepperIndex;
STEPPER stepper;

void setup() {
  nextSwitch = micros();
  //declare stepper object using the two designated control pins
  stepper = STEPPER(CNTRL_PIN_A,CNTRL_PIN_B);
}

void loop() {
  timeClock = micros();
  //if it's time to take our next step do so
  if(timeClock > nextSwitch){
    nextSwitch = timeClock + timeStep;
    //this is the command you use to step counter clock wise
    stepper.moveStepperCCW();
    //or use the following command to step clock wise
    //  stepper.moveStepperCW();
  }
}
