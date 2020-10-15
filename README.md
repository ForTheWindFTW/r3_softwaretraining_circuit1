# r3_softwaretraining_circuit1

## Objective
Wire and program 2 motors to an Arduino Uno using the L293D motor controller, and use a potentiometer to control their speeds with PWM. Program different control modes which is controlled using a dip switch, all done in [TinkerCAD](https://www.tinkercad.com/).

Starting off, many parts of this training package were confusing, but after working through these main steps, I became much more comfortable working with circuits and [TinkerCAD](https://www.tinkercad.com/).

## Requirements
- Control 2 motors with PWM and a 4 DIP switch
- Read and use a potentiometer to control motor speed
- Program all drive modes (forward, reverse, rotate (C)CW

## Steps
- Created a [smaller circuit](https://www.tinkercad.com/things/9jNt476gUKP) (3x flashing LEDs) to gain experience
![Image of 3x-LED circuit](/images/3x-LED.png)
  - Watched [videos](https://youtu.be/8gvJzrjwjds) on basic electricity and LED connections
  - Used Arduino's [Language Reference](https://www.arduino.cc/reference/en/)
- Tested and learned more about the Hobby Gearmotors and DIP switches
- Completed [Circuit1 design](https://www.tinkercad.com/things/5R3EwdZ4ZUq)
![Image of Circuit1](/images/R3-SoftwareTraining-Circuit1.png)
- Learned about [Markdown](https://guides.github.com/features/mastering-markdown/), reviewed [Git](https://www.notion.so/Introduction-to-Git-ac396a0697704709a12b6a0e545db049) and [GitHub](https://github.com/ForTheWindFTW/r3_softwaretraining_circuit1) commands.

## How it Works
- When the Arduino Uno is connected, all pins are initalized, for the DIP switches, potentiometer, and motor connections. One thing to note is that only pin 13 functions properly when set to INPUT mode as a DIP switch. All other connections, digital or analog, must be set to OUTPUT to properly read inputs. Otherwise, they will always output 1 or 1023 when read in digital or analog mode.
- Once the setup is finished, the loop which performs logic will run. In the beginning of each loop, the inputs are read through `readInputs()`, which updates the values of global variables `dip` and `pot`.
- After reading the inputs, the current `pwr`, which is the motor PWM power, is calculated by mapping the value of `pot`, the potentiometer, from 0 - 1024 to 0 - 255.
- Then, to figure out how the motors are run, there are a series of if-else-if statements. The first block if all four switches are on, the second checks if only `dip[0]` is on and the others are all off, the third checks if only `dip[1]` is on, the fourth checks if only `dip[2]` is on, and the last checks if only `dip[3]` is on. Each block will either stop the motors, drive them forward, drive in reverse, turn left (CCW), or turn right (CW). The motors will be set to a power of `pwr`, which was previously calculated.
- In `motorDrive(byte* pins, short pwr)`, `pins` should be an array with 2 elements (`MOTOR_L` and `MOTOR_R` are used) which gives the negative and positive inputs to the motor driver. `pwr` is simply the power of the motors; if it is from 1 to 255, the motor will drive forwards, and if it is -255 to -1, it will drive in reverse.
- Finally, after setting the current motor speeds, there is a delay of 50 ms, which in turn will make the loop get called every ~20 Hz.

## Reflection
As a first-year, my lack of experience with circuits made it much harder to start out in [TinkerCAD](https://www.tinkercad.com/). However, using many resources to learn about [TinkerCAD](https://www.tinkercad.com/) and circuits incrementally made this project much easier to work on. After piecing together those pieces of knowledge, it became much easier to work in [TinkerCAD](https://www.tinkercad.com/). I also noticed that the coding felt extremely familiar, since I had previous experience with [RobotC](http://www.robotc.net/) in my highschool's Robotics Team. This exercise was great in allowing me to review and train my skills, and I am looking forward to everything else that R3 is involved in!
