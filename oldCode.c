#pragma config(Motor,  port2,           driveLeft,     tmotorNormal, openLoop)
#pragma config(Motor,  port3,           boxGate,       tmotorServoStandard, openLoop)
#pragma config(Motor,  port4,           track,         tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port6,           armJoint,      tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port7,           gripper,       tmotorServoStandard, openLoop)
#pragma config(Motor,  port9,           driveRight,    tmotorNormal, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

float motorMultiplier = 1;
bool motorLock = true;

task motorToggles()
{
  while(true)
  {
    if(vexRT(Btn8L) == 1)
    {
      motorLock = true;
    }
    if(vexRT(Btn8U) == 1)
    {
      motorLock = false;
    }
    if(vexRT(Btn8R) == 1)
    {
      motorMultiplier = 1;
    }
    if(vexRT(Btn8D) == 1)
    {
      motorMultiplier = .3;
    }
  }
}

task gripperServo()
{
  int pos = -64;      //ititialze the position variable
  while(true)     //endless loop
  {
    motor[gripper] = pos;     //set the servo position to the position variable
    if(vexRT(Btn5D) == 1)      //if the upper left button on the top of the joystick is pressed...
    {
      pos += 15;      //increment the position variable by 10
    }
    if(vexRT(Btn5U) == 1)     //if the lower left button on the top of the joystick is pressed...
    {
      pos -= 15;      //decrement the position variable by 10
    }
    if(pos > 128)      //keep value inside upper servo range
    {
      pos = 127;      //!!!CHANGE AS NEEDED!!!
    }
    if(pos < -64)     //keep value inside lower servo range
    {
      pos = -64;     //!!!CHANGE AS NEEDED!!!
    }
    wait1Msec(50);     //wait for the servos to run
  }
}

task boxServo()
{
  int pos = 127;      //ititialze the position variable
  while(true)     //endless loop
  {
    motor[boxGate] = pos;     //set the servo position to the position variable
    if(vexRT(Btn6D) == 1)     //if the lower left button on the top of the controler is pressed...
    {
      pos = -128;      //set the servo position variable to -127 (closed)
    }
    if(vexRT(Btn6U) == 1)     //if the upper left button on the top of the controler is pressed...
    {
      pos = 127;      //set the servo position variable to 127 (open)
    }
    wait1Msec(100);     //wait for the servos to run
  }
}

task main()
{
  StartTask(boxServo);      //start the two servo tasks
  StartTask(gripperServo);
  StartTask(motorToggles);
  while(true)     //endless loop
  {
    motor[driveLeft] = ((vexRT(Ch2) + vexRT(Ch1)) * motorMultiplier);     //left and right drive motors power sot to the position
    motor[driveRight] = ((vexRT(Ch2) - vexRT(Ch1)) * motorMultiplier);      //of the right joystick, arcade style
    motor[armJoint] = vexRT(Ch3);     //set the power of the arm joint motor the the position of the X axis of the right joystick
    if(vexRT(Btn7U) == 1)     //if the upper button on the left of the joystick is pressed...
    {
      motor[track] = 127;      //move the track motor at full power foreward
    }
    if(vexRT(Btn7D) == 1)     //if the lower button on the left of the joystick is pressed...
    {
      motor[track] = -128;     //move the track motor at full power backward
    }
    if((vexRT(Btn7U) == 0) && (vexRT(Btn7D) == 0))      //if neither upper nor lower button on the left of the joystick is pressed...
    {
      motor[track] = 0;     //stop the track motor
    }
  }
}