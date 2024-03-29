#include <ipst.h>
// these are the pins for sensors
int sensor_left = 17 ;
int sensor_right = 16 ;
int sensor_midin = 18 ; // interrupt on this pin.
//int sensor_greenhunter = 3;
volatile byte blk_line = LOW; // The variable for the black line detection.
// int white = 0; int black = 1;
// these are the pins for motor
//Left_pos 8
//Left_neg 9
//Right_pos 10
//Right_neg 11
int turn_count = 0; //ms
int blk_count = 0 ;
int globalSpeed = 20;
void setup() {
  // put your setup code here, to run once:
  pinMode(sensor_left, INPUT);
  pinMode(sensor_right, INPUT);
  digitalWrite(15, HIGH);
  pinMode(sensor_midin, INPUT);
  fd();
  delay(1300);
  attachInterrupt(INT2, decision, FALLING);// suddenly from white to black
}

void loop() {
  // put your main code here, to run repeatedly
  //attachInterrupt(INT2, dicision, FALLING);// suddenly from white to black


}
/* Usage
 *  hexa_drive the motors driving code. 1 represent forward , 2 represent backward , 3 represent turnleft and 4 represent turn right
 *  interv is interval or how long does motor need te spin in milsec.
 */

/* take decision to determine if the line was thinck or thin
 * this will occur when midin sensor detect black stip at the border or black bridge.
 */
void fd() // moving foward using global speed
{
  motor(1, globalSpeed);
  motor(2, globalSpeed);
}
void bk(int bwspd) // moving backward using global speed
{
  motor(1, -bwspd);
  motor(2, -bwspd);
}
void tl() // turn left 
{
  motor(1, globalSpeed);
  motor(2, -globalSpeed);
}
void tr() // turn right
{
  motor(1, -globalSpeed);
  motor(2, globalSpeed);
}

void decision() {

  sei();// Disable interrupt to make delay works
  motor(1, 0); motor(2, 0); // stop motor
  delay(65);
  if ((digitalRead(sensor_midin) == 0) && ((digitalRead(sensor_left) && digitalRead(sensor_right)) == 1)) { // detect the black line
    turn_count = turn_count + 1 ;
    if (turn_count == 3 || turn_count == 10 || turn_count == 11 || turn_count == 17 || turn_count == 18 || turn_count == 19) { // turn left normally
      bk(globalSpeed);
      delay(300);
      tl();
      delay(548);
      fd();
      cli();
      return;
    } else if (turn_count == 7) { // L F R F
      bk(globalSpeed);
      delay(300);
      tl();
      delay(548);
      fd();
      delay(1300);
      tl();
      delay(548);
      fd();
      cli();
      return;
    } else if (turn_count == 13) {// R R F
      bk(globalSpeed);
      delay(300);
      tr();
      delay(548);
      tr();
      delay(548);
      fd();
      delay(548);
      cli();
      return;
    } else if (turn_count == 14) {// L F L F
      bk(globalSpeed);
      delay(300);
      tl();
      delay(548);
      fd();
      delay(1300);
      tl();
      delay(548);
      fd();
      cli();
      return;
    } else if (turn_count == 20) {
      fd();
      delay(700);
      motor(1, 0); motor(2, 0); // stop motor
      cli();
      return;
    } else {// turn right
      bk(globalSpeed);
      delay(300);
      tr();
      delay(548);
      fd();
      cli();
      return;
    }
  } else if ((digitalRead(sensor_midin) == 0) && ((digitalRead(sensor_left) || digitalRead(sensor_right)) == 0)) { // detect the thick black strip
    blk_count = blk_count + 1 ;
    if (blk_count == 1) {
      bk(globalSpeed);
      delay(300);
      tr();
      delay(548);
      fd();
      cli();
      return;
    } else if (blk_count == 2) {
      digitalWrite(14, HIGH);
      delay(200);
      digitalWrite(14, LOW);
      delay(100);
      tr();
      delay(548);
      tr();
      delay(548);
      fd();
      delay(1300);
      tr();
      delay(548);
      fd();
      cli();
      return;
    } else if (blk_count == 3){
    bk(globalSpeed);
    delay(300);
    fd();
    delay(2599);
    tr();
    delay(548);
    fd();
    cli();
    return;
    }
    else if (blk_count == 4) {
      digitalWrite(14, HIGH);
      delay(200);
      digitalWrite(14, LOW);
      delay(100);
      tr();
      delay(548);
      tr();
      delay(548);
      fd();
      cli();
      return;
    }else if (blk_count == 5){
      digitalWrite(14, HIGH);
      delay(200);
      digitalWrite(14, LOW);
      delay(100);
      tr();
      delay(548);
      tr();
      delay(548);
      fd();
      cli();
      return;
    }else if (blk_count == 6){
    digitalWrite(14, HIGH);
      delay(200);
      digitalWrite(14, LOW);
      delay(100);
      tr();
      delay(548);
      tr();
      delay(548);
      fd();
      delay(1300);
      tr();
      delay(548);
      cli();
      return;
    }else {
      fd();
      delay(2000);
      cli();
      return;
    }
  } else {
    bk(globalSpeed);
    delay(300);
    tr();
    delay(548);
    fd();
    cli();
    return;
  }
}
