/ARAM-DDHBSD_0_13-0S      Example Code                rev: 4/29/2026

#define CNTRL_PIN_A 2     //change me to your desired cntrl pin A
#define CNTRL_PIN_B 1     //change me to your desired cntrl pin B
#define MICROS_TO_SECONDS (1000000)
uint32_t timeClock;
uint32_t nextSwitchA;
uint32_t nextSwitchB;
int switchAFrequency = 10; //change me to your desired switching frequency (1/seconds)
int switchBFrequency = 20; //change me to your desired switching frequency (1/seconds)
double timeStepA = MICROS_TO_SECONDS/switchAFrequency;
double timeStepB = MICROS_TO_SECONDS/switchBFrequency;
int stateA = 0;
int stateB = 0;

void setup() {
  nextSwitchB = micros();
  nextSwitchA = nextSwitchB;
  pinMode(CNTRL_PIN_A,OUTPUT);
  pinMode(CNTRL_PIN_B,OUTPUT);
}

void loop() {
  timeClock = micros();
  //every time we want to switch polarity simple shift the control pin from low to high or vise versa
  //switch polarity for A
  if(timeClock > nextSwitchA){
    nextSwitchA = timeClock + timeStepA;
    if(stateA)digitalWrite(CNTRL_PIN_A,HIGH);
    else digitalWrite(CNTRL_PIN_A,LOW);

    stateA = !stateA;
  }
  //switch polarity for B
  if(timeClock > nextSwitchB){
    nextSwitchB = timeClock + timeStepB;
    if(stateB)digitalWrite(CNTRL_PIN_B,HIGH);
    else digitalWrite(CNTRL_PIN_B,LOW);

    stateB = !stateB;
  }
}
