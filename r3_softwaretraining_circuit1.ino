/**
 * R3-SoftwareTraining-Circuit Code
 * 
 * Both motors turn at a speed based on the potentiometer
 * 
 * The motors will move:
 * - Forwards if only dip switch 1 is on
 * - Reverse if only dip switch 2 is on
 * - Move Left (rotate CCW) if only dip switch 3 is on
 * - Move Right (rotate CW) if only dip switch 4 is on
 *  - The motors will stop if the potentiometer is 0 or
 *    all dip switches are off
 * 
 * Note: The motors' negative RPM indicates a "forward" drive
 *       rotation, while a positive RPM indicates a "reverse"
 *       drive rotation
 * 
 * Stanley Chow
 * v1.0.1 2020/10/14
 */

#define DIP1 13
#define DIP2 12
#define DIP3 8
#define DIP4 7
#define POT A0
#define POT_MIN 0
#define POT_MAX 1023
#define PWR_MIN 0
#define PWR_MAX 255

/**
 * Grouping the L293D motor driver inputs
 */
byte MOTOR_L[2] = {5, 3};
byte MOTOR_R[2] = {9, 6};

int dip[4];
int pot;

void setup() {
  /**
   * For some reason, only pin 13 works properly when set to
   * INPUT mode for dip switches, and all other pins (analog or
   * digital) must be set to OUTPUT mode to function correctly
   */
  pinMode(DIP1, INPUT);
  pinMode(DIP2, OUTPUT);
  pinMode(DIP3, OUTPUT);
  pinMode(DIP4, OUTPUT);
  
  pinMode(POT, INPUT);
}

void loop() {
  readInputs();
  
  int pwr = map(pot, POT_MIN, POT_MAX, PWR_MIN, PWR_MAX);
  
  /* Note: !a && !b && ... can be simplified to !(a || b || ...)
   * but is left as-is to improve readability
   */
  if(!dip[0] && !dip[1] && !dip[2] && !dip[3]) {
    driveForward(0);
  } else if(dip[0] && !dip[1] && !dip[2] && !dip[3]) {
    driveForward(pwr);
  } else if(!dip[0] && dip[1] && !dip[2] && !dip[3]) {
    driveReverse(pwr);
  } else if(!dip[0] && !dip[1] && dip[2] && !dip[3]) {
    driveRotateCCW(pwr);
  } else if(!dip[0] && !dip[1] && !dip[2] && dip[3]) {
    driveRotateCW(pwr);
  }
  
  /**
   * Loop updates at a rate of ~20Hz
   */
  delay(50);
}

/**
 * Simply reads the values of the dip switch and potentiometer
 * and updates the values in stored in dip and pot, respectively
 */
void readInputs() {
  dip[0] = digitalRead(DIP1);
  dip[1] = digitalRead(DIP2);
  dip[2] = digitalRead(DIP3);
  dip[3] = digitalRead(DIP4);
  pot = analogRead(POT);
}

/**
 * Given (MOTOR_L or MOTOR_R) and pwr, the motor will be set to
 * drive forwards if pwr >= 0, and reverse if pwr < 0
 */
void motorDrive(byte* pins, short pwr) {
  if(pwr >= 0) {
    analogWrite(pins[0], 0);
  	analogWrite(pins[1], pwr);
  } else {
    analogWrite(pins[0], abs(pwr));
    analogWrite(pins[1], 0);
  }
}

/**
 * Given a pwr value from 0 - 255 inclusive,
 * both motors will drive forward at that specified power
 * Note: If pwr is negative, the motors will reverse
 */
void driveForward(short pwr) {
  motorDrive(MOTOR_L, pwr);
  motorDrive(MOTOR_R, pwr);
}

/**
 * Given a pwr value from 0 - 255 inclusive,
 * both motors will reverse at that specified power
 * Note: If pwr is negative, the motors will drive forward
 */
void driveReverse(short pwr) {
  motorDrive(MOTOR_L, -pwr);
  motorDrive(MOTOR_R, -pwr);
}

/**
 * Given a pwr value from 0 - 255 inclusive,
 * the left motor will revers, and the right will drive forward,
 * resulting in differential/skid steering to the left (or CCW)
 * Note: If pwr is negative, the motors will turn right (CW)
 */
void driveRotateCCW(short pwr) {
  motorDrive(MOTOR_L, -pwr);
  motorDrive(MOTOR_R, pwr);
}

/**
 * Given a pwr value from 0 - 255 inclusive,
 * the left motor will drive forward and the right will reverse,
 * resulting in differential/skid steering to the right (or CW)
 * Note: If pwr is negative, the motors will turn left (CCW)
 */
void driveRotateCW(short pwr) {
  motorDrive(MOTOR_L, pwr);
  motorDrive(MOTOR_R, -pwr);
}
