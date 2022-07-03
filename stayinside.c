/*
 \file		stayinside.c
 \author	MOHAMMAD HABIB SHAH ERSHAD BIN MOHD AZRUL SHAZRIL
 \date		2/7/2022
 \brief		Robot will move inside the black tape.
*/

#include <ev3.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float rf = 2.75;

//declare counter
int i=1;

//declare motor rotation angle
int r;
char str[20];


void init(){

	InitEV3(); //Declare library function
	setAllSensorMode(NO_SEN,US_DIST_MM,COL_COLOR,NO_SEN); //set what input corresponds to what sensor
}

int a(int rangle)
{
	int lower = -200, upper = 200, count = 500;
	int i;
    srand(time(0));
	int angle[500];

   // printf("The random numbers are: ");
    for (i = 0; i < count; i++) {
        int num = (rand() % (upper - lower + 1)) + lower;
        if(num < 70 && num > 0)
        {
        	num = num + 90;
		}
		else if (num > -70 && num <=0)
		{
			num = num - 90;
		}
		else
		{
			num = num;
		}

        angle[i]=num;
    }

		rangle = angle[455];
    return rangle;
}

void turn(){
	int b, c;
	c = a(b);
	if (c<0)
		{
			r = -c*rf; //multiply rotation factor
			RotateMotorEx(OUT_BC, 50, r, -200 , true, true);
			Wait(MS_500);
		}
		else
		{
			r = c*rf; //multiply rotation factor
			RotateMotorEx(OUT_BC, 50, r, 200 , true, true);
			Wait(MS_500);
		}

}

int main(void)
{

	init();
		char SONAR[20],DISTANCE[20];
		int port = IN_2;
		int port1 = IN_3;
		int sensor = abs(ReadSensor(port));
		int sensor1 = abs(ReadSensor(port1));
		int temp;
		temp = sensor;
		while(ButtonIsUp(BTNCENTER) == 1){
			sensor = sensor/10;
			LcdClean();
			if (sensor1 > 100)
			{
				sensor1 = sensor1 - 3840;
			}
			if (sensor1 < 0)
			{
				sensor1 = 15;
			}
		sprintf(SONAR, "%d", sensor);
		sprintf(DISTANCE, "%d", sensor1);
		TermPrintln("DISTANCE    : %s",SONAR, "mm");
		TermPrintln("COLOR    : %s",DISTANCE);

		if (sensor1 <=1)
		{
			RotateMotor(OUT_BC, -50, 360);
			Wait(MS_100);
			turn();
		}
		else if (sensor1 >11)
		{
			OnFwdEx(OUT_BC, 50,	true);
		}

		Wait(MS_100);
		temp = sensor;
		sensor = abs(ReadSensor(port));
		sensor1 = abs(ReadSensor(port1));
		}


	return 0;
}
