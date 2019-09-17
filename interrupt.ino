
// these are the pins for sensors
int sensor_left = 5 ;
int sensor_right = 4 ;
int sensor_midin = 2 ; // interrupt on this pin.
int sensor_greenhunter = 3; 
volatile byte blk_line = LOW; // The variable for the black line detection.
// int white = 0; int black = 1;

// these are the pins for motor 
//Left_pos 8 
//Left_neg 9 
//Right_pos 10 
//Right_neg 11 
int turn_tune = 100; //ms

void setup() {
  // put your setup code here, to run once:
DDRB = DDRB | B00001111 ; //init the motors pin
pinMode(sensor_left, INPUT);
pinMode(sensor_right, INPUT);
pinMode(sensor_midin, INPUT);
attachInterrupt(digitalPinToInterrupt(sensor_midin), dicision, FALLING);// suddenly from white to black 
}

void loop() {
  // put your main code here, to run repeatedly:

}
/* Usage
 *  hexa_drive the motors driving code. 1 represent forward , 2 represent backward , 3 represent turnleft and 4 represent turn right 
 *  interv is interval or how long does motor need te spin in milsec.
 */
void motor_Drive(int hexa_drive, int interv){ //Drive the motors using pin manipulation 
  //By using pin 8 9 10 and 11 which are PB0 PB1 PB2 and PB3. We use this because it convenience to manipulate.
  PORTB = 0x00 ; //Clear the f*ck out and stop all motor
  if (hexa_drive == 0){//forward
  PORTB = 0x0A ; // 1010
  }else if (hexa_drive == 1){//backward
  PORTB = 0x05 ; // 0101
  }else if (hexa_drive == 2){//turn left
  PORTB = 0x06 ; // 0110
  }else if (hexa_drive == 3){//turn right
  PORTB = 0x09 ; // 1001
  }else {
  PORTB = 0x00 ; //Clear the f*ck out and stop all motor
  return ; 
  }
  if(interv == 0){return;}
  delay(interv);
  PORTB = 0x00 ; //Clear the f*ck out and stop all motor
  
}
/* take dicision to determine if the line was thinck or thin 
 * this will occur when midin sensor detect black stip at the border or black bridge. 
 */
void dicision(){
  PORTB = 0x00 ; //Clear the f*ck out and stop all motor
  if ((sensor_midin == 1) && ((sensor_left | sensor_right) == 0)){ // detect the black line 
  motor_Drive(1, 100); //backward 100ms
  motor_Drive(2,turn_tune); 
  }else if ((sensor_midin == 1) && ((sensor_left & sensor_right) == 1)){// detect the thick black strip
  return ; // go back to void loop and go forward. 
  }else {
  
  }   
}
