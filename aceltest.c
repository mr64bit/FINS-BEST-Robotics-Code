#pragma config(Motor,  port2,           arm,           tmotorServoContinuousRotation, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
int acel = 0;
task main()
{
	while(true)
		{
			acel = vexRT[AccelY];
			motor[arm] = acel;
		}
}