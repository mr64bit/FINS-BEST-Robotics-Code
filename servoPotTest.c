#pragma config(Sensor, in1,    pot,            sensorPotentiometer)
#pragma config(Motor,  port2,           servo,         tmotorServoStandard, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

float potNorm = 0;
const float potMult = 0.206618240516; //(256 / 1239);
int lowest = 4000;
int highest = 0;

task main()
{
	while(true)
	{
		wait1Msec(1);
		potNorm = (SensorValue(pot) - 2856) * potMult;
		if(lowest >= potNorm) { lowest = potNorm; }
		if(highest <= potNorm) { highest = potNorm; }
		motor[servo] = -1 * (potNorm - 128);
	}
}
