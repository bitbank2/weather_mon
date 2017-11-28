//
// Weather monitor
//
// Copyright (c) 2017 BitBank Software, Inc.
// Written by Larry Bank
// project started 11/28/2017
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <bme280.h>
#include <oled96.h>
#include <ccs811.h>
#include <pthread.h>

static int bRunning;
static int T, P, H, CO2, VOC;
static FILE *pf;

void RecordValues(void)
{
char szTemp[256];

	sprintf(szTemp, "%2.1f, %2.1f, %4.1f, %d\n", (float)T/100.0, (float)H/1024.0, (float)P/256.0, VOC);
	fwrite(szTemp, 1, strlen(szTemp), pf);
} /* RecordValues() */

void FlushValues(void)
{
	fflush(pf);
	fclose(pf);
} /* FlushValues() */

void UpdateOLED(void)
{
char szTemp[32];

	oledWriteString(0,0,"Temperature",0);
	oledWriteString(0,2,"Humidity",0);
	oledWriteString(0,4,"Pressure",0);
	oledWriteString(0,6,"VOCs",0);
// Draw the new values and erase the old
	sprintf(szTemp, "%2.1fC / %2.1fF   ", (float)T/100.0, 32.0 + (float)(9*T)/500.0);
	oledWriteString(0,1,szTemp,0);
	sprintf(szTemp, "%2.1f%%", (float)H/1024.0);
	oledWriteString(0,3,szTemp,0);
	sprintf(szTemp, "%4.1f hPa", (float)P/256.0);
	oledWriteString(0,5,szTemp,0);
	sprintf(szTemp, "%d      ", VOC);
	oledWriteString(0,7,szTemp,0);
} /* UpdateOLED() */

void *MonitorThread(void *pArg)
{
	while (bRunning)
	{
		bme280ReadValues(&T, &P, &H);
		T -= 150; // for some reason, the sensor reports temperatures too high
		ccs811ReadValues(&CO2, &VOC);
		UpdateOLED();
		RecordValues();
		usleep(10000000); // sleep 10 seconds
	}
return NULL;
} /* MonitorThread() */

int main(int argc, char *argv[])
{
int i;
pthread_t tinfo;
int iI2C_Channel = 0; // check your hardware if this should be 0 or 1

	i = bme280Init(iI2C_Channel, 0x76);
	if (i != 0)
	{
		return -1; // problem - quit
	}
	i = ccs811Init(iI2C_Channel, 0x5b);
	if (i != 0)
	{
		return -1; // error
	}
	i = oledInit(iI2C_Channel, 0x3c, 0, 0);
	if (i != 0)
	{
		return -1;
	}
	oledFill(0);
	oledSetContrast(85); // set it to a lower brightness to not burn it

	printf("Sensor devices successfully opened, beginning capture...\n");
	pf = fopen("weather.csv","w");

	bRunning = 1;
	pthread_create(&tinfo, NULL, MonitorThread, NULL);
	printf("Press ENTER to quit\n");

	getchar(); // wait for user to press enter
	bRunning = 0;
	oledShutdown();
	FlushValues();
return 0;
} /* main() */
