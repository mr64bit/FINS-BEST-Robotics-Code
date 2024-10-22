#pragma config(Sensor, in1,    pot1,           sensorPotentiometer)
#pragma config(Sensor, in2,    pot2,           sensorPotentiometer)
#pragma config(Sensor, dgtl1,  eStop,          sensorTouch)
#pragma config(Sensor, dgtl2,  armStop,        sensorTouch)
#pragma config(Motor,  port4,           turn,          tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port5,           base,          tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port6,           belt,          tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port7,           chain,         tmotorServoContinuousRotation, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

const int joyCutoff = 10;
float joy1 = 0;
float joy2 = 0;
float joy3 = 0;
float joy4 = 0;

float basePos = 0;
float gripPos = 0;
float basePot = 0;
float gripPot = 0;
float pot1Low = 0;
float pot1High = 75;
float pot2Low = 2632;
float pot2High = 3657;

float basePower = 0;
float gripPower = 0;

bool lock = false;
float lockPos = 0;

const float baseKonst = 7;
float baseError = 0;

//const float gripKonst = 7;
float gripError = 0;

void joyInput()
{
	if((vexRT[Ch1] <= -joyCutoff) || (vexRT[Ch1] >= joyCutoff)) { joy1 = vexRT[Ch1]; } else { joy1 = 0; }
	if((vexRT[Ch2] <= -joyCutoff) || (vexRT[Ch2] >= joyCutoff)) { joy2 = vexRT[Ch2]; } else { joy2 = 0; }
	if((vexRT[Ch3] <= -joyCutoff) || (vexRT[Ch3] >= joyCutoff)) { joy3 = vexRT[Ch3]; } else { joy3 = 0; }
	if((vexRT[Ch4] <= -joyCutoff) || (vexRT[Ch4] >= joyCutoff)) { joy4 = vexRT[Ch4]; } else { joy4 = 0; }
}

void potInput()
{
	basePot = ((SensorValue[pot1] - pot1Low) * (256 / (pot1High - pot1Low))) - 127;
	gripPot = ((SensorValue[pot2] - pot2Low) * (256 / (pot2High - pot2Low))) - 127;
}

void potTesting()
{
	pot1Low = 9999999; pot1High = 0;
	pot2Low = 9999999; pot2High = 0;
	while(true)
	{
		potInput();
		joyInput();
		wait1Msec(1);
		motor[turn] = joy4;
		motor[base] = joy3;
		motor[belt] = joy2;
		if(pot1Low >= SensorValue[pot1]) { pot1Low = SensorValue[pot1]; }
		if(pot1High <= SensorValue[pot1]) { pot1High = SensorValue[pot1]; }
		if(pot2Low >= SensorValue[pot2]) { pot2Low = SensorValue[pot2]; }
		if(pot2High <= SensorValue[pot2]) { pot2High = SensorValue[pot2]; }
		if(vexRT[Btn5D] == 1) { pot1Low = 9999999; pot1High = 0; }
		if(vexRT[Btn5U] == 1) { pot2Low = 9999999; pot2High = 0; }
		if(vexRT[Btn8U] == 1) { motor[chain] = -64; }
		if(vexRT[Btn8D] == 1) { motor[chain] = 64; }
		if(vexRT[Btn6U] == 1) { motor[chain] = 128; }
		if(vexRT[Btn6D] == 1) { motor[chain] = -128; }
		if((vexRT[Btn8D] == 0) && (vexRT[Btn8U] == 0) && (vexRT[Btn6D] == 0) && (vexRT[Btn6U] == 0)) { motor[chain] = 0; }
	}
}

void baseLoop();
// void gripLoop();

task main()
{
	wait1Msec(1000);
	if((vexRT[Btn7L] == 1) && (vexRT[Btn7R] == 1)) { potTesting(); StopAllTasks(); }
	potInput();
	basePos = basePot;
	gripPos = basePot;
	while(true)
	{
		if(SensorValue[eStop] == 1) { StopAllTasks(); }
		wait1Msec(10);
		joyInput();
		potInput();
		if(vexRT[Btn7U] == 1) { lock = true; lockPos = basePos = gripPos; }
		if(vexRT[Btn7D] == 1) { lock = false; lockPos = 0; }

		baseLoop();
		//gripLoop();

		if(vexRT[Btn8U] == 1) { motor[chain] = -64; }
		if(vexRT[Btn8D] == 1) { motor[chain] = 64; }
		if(vexRT[Btn6U] == 1) { motor[chain] = 128; }
		if(vexRT[Btn6D] == 1) { motor[chain] = -128; }
		if((vexRT[Btn8D] == 0) && (vexRT[Btn8U] == 0) && (vexRT[Btn6D] == 0) && (vexRT[Btn6U] == 0)) { motor[chain] = 0; }
		motor[base] = basePower;
		//motor[belt] = gripPower;
		motor[belt] = joy2;
		motor[turn] = joy4;
		}
}

void baseLoop()
{
	basePos += joy3 / 512;
	if(basePos < -128) { basePos = -128; }
	if(basePos > 127) { basePos = 127; }
	baseError = basePos - basePot;
	basePower = baseError * baseKonst;
}

//void gripLoop()
//{
//	gripPos += joy2 / 512;
//	if(gripPos < -128) { gripPos = -128; }
//	if(gripPos > 127) { gripPos = 127; }
//	gripError = gripPos - gripPot;
//	gripPower = gripError * gripKonst;
//}
