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
int globalSpeed = 20;
void setup() {
  // put your setup code here, to run once:
  pinMode(sensor_left, INPUT);
  pinMode(sensor_right, INPUT);
  digitalWrite(15, HIGH);
  pinMode(sensor_midin, INPUT);
  fd();
  delay(1300);
  attachInterrupt(INT2, dicision, FALLING);// suddenly from white to black
}

void loop() {
  // put your main code here, to run repeatedly
  //attachInterrupt(INT2, dicision, FALLING);// suddenly from white to black
  

}
/* Usage
 *  hexa_drive the motors driving code. 1 represent forward , 2 represent backward , 3 represent turnleft and 4 represent turn right
 *  interv is interval or how long does motor need te spin in milsec.
 */

/* take dicision to determine if the line was thinck or thin
 * this will occur when midin sensor detect black stip at the border or black bridge.
 */
void fd() // ฟังก์ชั่นเดินหน้า
{
  motor(1, globalSpeed);
  motor(2, globalSpeed);
}
void bk(int bwspd) // ฟังก์ชั่นถอยหลัง
{
  motor(1, -bwspd);
  motor(2, -bwspd);
}
void tl() // ฟังก์ชั่นเลี้ยวซ้าย
{
  motor(1, globalSpeed);
  motor(2, -globalSpeed);
}
void tr() // ฟังก์ชั่นเลี้ยวขวา
{
  motor(1, -globalSpeed);
  motor(2, globalSpeed);
}

void dicision() {
  turn_count = turn_count + 1 ;
  sei();
  motor(1, 0); motor(2, 0); // stop motor
  delay(65);
  if ((digitalRead(sensor_midin) == 0) && ((digitalRead(sensor_left) && digitalRead(sensor_right)) == 1)) { // detect the black line
    if (turn_count == 4 || turn_count == 11 || turn_count == 12 || turn_count == 18 || turn_count == 19 || turn_count == 20) { // turn left normally
      bk(globalSpeed);
      delay(300);
      tl();
      delay(548);
      fd();
      cli();
      return;
    } else if (turn_count == 8) { // L F R F
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
    } else if (turn_count == 14) {// R R F
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
    } else if (turn_count == 15) {// L F L F
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
    } else if (turn_count == 21) {
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
  }else if ((digitalRead(sensor_midin) == 0) && ((digitalRead(sensor_left) && digitalRead(sensor_right)) == 0)) { // detect the thick black strip
    if (turn_count == 3) {
      bk(globalSpeed);
      delay(300);
      tr();
      delay(548);
      fd();
      cli();
      return;
    } else {
      fd();
      delay(2000);
      cli();
      return;
    }
  }else {
      bk(globalSpeed);
      delay(300);
      tr();
      delay(548);
      fd();
      cli();
      return;
  }
}
