

//#include <TimerOne.h>

//#define pot A0   //potentiometer output pin

 const uint8_t pace =200;   //speed of the motor

//hall sensor input
 uint8_t h_y = 2;
 uint8_t h_b = 18;
 uint8_t h_g = 19;

//output pin to motor,all pins are active high
const uint8_t pwm_y_hin = 9;
const uint8_t pwm_b_hin = 10;
const uint8_t pwm_g_hin = 11;
const uint8_t y_lin = 6;
const uint8_t b_lin = 7;
const uint8_t g_lin = 8;

uint8_t hall_y, hall_b, hall_g;


//throttle operation

//routine to update the pwm value according to throttle output
//void timerOneISR() {
//  pace = map(analogRead(pot), 0, 250, 0, 1023);
//}


void runMotor() { 

  reset();
  
  hall_y = digitalRead(h_y);
  hall_b = digitalRead(h_b);
  hall_g = digitalRead(h_g);

  if (hall_y == 1 && hall_b == 0 && hall_g == 1) {//010
   analogWrite(pwm_y_hin, pace);
   // digitalWrite(pwm_y_hin, HIGH);
    digitalWrite(b_lin, HIGH);
  }
  else if (hall_y == 1 && hall_b == 0 && hall_g == 0) {//011
    analogWrite(pwm_y_hin, pace);
    digitalWrite(g_lin, HIGH);

  }
  else if (hall_y == 1 && hall_b == 1 && hall_g == 0) { //001
    analogWrite(pwm_b_hin, pace);
   // digitalWrite(pwm_b_hin, HIGH);
    digitalWrite(g_lin, HIGH);
  }
  else if (hall_y == 0 && hall_b == 1 && hall_g == 0) {//101
    analogWrite(pwm_b_hin, pace);
    digitalWrite(y_lin, HIGH);
  }
  else if (hall_y == 0 && hall_b == 1 && hall_g == 1) { //100
    analogWrite(pwm_g_hin, pace);
    digitalWrite(y_lin, HIGH);
  }
  
  else if (hall_y == 0 && hall_b == 0 && hall_g == 1) {//110
    analogWrite(pwm_g_hin, pace);
    digitalWrite(b_lin, HIGH);
  }
}

void printSensorVal(){
  Serial.print(hall_y);
  Serial.print("\t");
  Serial.print(hall_b);
  Serial.print("\t");
  Serial.print(hall_g);
  Serial.println("\t");
  
}

void reset(){
  analogWrite(pwm_y_hin, 0);
  analogWrite(pwm_b_hin, 0);
  analogWrite(pwm_g_hin, 0);

  digitalWrite(y_lin, LOW);
  digitalWrite(b_lin, LOW);
  digitalWrite(g_lin, LOW);
}

/*************************************** setup ****************************************/
void setup() {
  Serial.begin(9600);

  //timer interrupt
//  Timer1.initialize(25000);   //100millis
//  Timer1.attachInterrupt(timerOneISR);


//  pinMode(pot, INPUT);
  pinMode(h_y, INPUT_PULLUP);
  pinMode(h_b, INPUT_PULLUP);
  pinMode(h_g, INPUT_PULLUP);


  pinMode(pwm_y_hin, OUTPUT);
  pinMode(pwm_b_hin, OUTPUT);
  pinMode(pwm_g_hin, OUTPUT);

  pinMode(y_lin, OUTPUT);
  pinMode(b_lin, OUTPUT);
  pinMode(g_lin, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(2), runMotor, CHANGE);
  attachInterrupt(digitalPinToInterrupt(18), runMotor, CHANGE);
  attachInterrupt(digitalPinToInterrupt(19), runMotor, CHANGE);

  //initializing all gate driver input pins to zero at first
  reset();
}


/*************************************** main loop ****************************************/
void loop() {

 runMotor();
while(1){
  printSensorVal();
  delay(100);
}
}
