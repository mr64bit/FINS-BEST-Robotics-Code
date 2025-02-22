#pragma config(Motor,  port2,           left_servo,    tmotorServoStandard, openLoop)
#pragma config(Motor,  port3,           right_servo,   tmotorServoStandard, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
float left = 0.1;
float right = 0.1;
float tmpL = 0;
float tmpR = 0;
float i = 0;
task main()
{
	while(true)
		{
			//if(vexRT[Btn5U] == 1)
			//	{
			//		left = left + 5;
			//		right = right -5;
			//	}
			//if(vexRT[Btn5D] == 1)
			//	{
			//		left = left - 5;
			//		right = right + 5;
			//	}
				tmpL = vexRT[Ch2];
				tmpR = vexRT[Ch2];
				if((tmpL > -10) && tmpL < 10) { tmpL = 0; }
				if((tmpR > -10) && tmpR < 10) { tmpR = 0; }
				left = left + (tmpL / 100);
				right = right + (tmpR / -100);
				i = .4 + .5;
				//left = left + (vexRT[Ch2] / 100);
				//right = right + (vexRT[Ch2] / -100);
				if(left > 127) { left = 127; }
				if(left < -128) { left = -128; }
				if(right > 127) { right = 127; }
				if(right < -128) { right = -128; }
				motor[left_servo] = left;
				motor[right_servo] = right;
				wait1Msec(10);
		}
}
