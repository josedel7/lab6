#include <stdio.h>
#include <wiringPi.h>
#include<stdlib.h> 
#include <string.h>
#include "ifttt.h"
int readTemperature();
void sendIFTTT(int l, int c, int h);
int main(int argc, char *argv[])
{
	int currTemperature=0;
	int lowestTemperature, highestTemperature;
	int oldTemperature;
	while(1)
	{	
		if(currTemperature==0)
		{
			currTemperature=readTemperature();
			lowestTemperature=currTemperature;
			highestTemperature=currTemperature;
			printf("Sending ifttt");
			sendIFTTT(lowestTemperature, currTemperature, highestTemperature);
		}
		else
		{
			oldTemperature=currTemperature;
			currTemperature=readTemperature();
			if(currTemperature>highestTemperature)
			{
				highestTemperature=currTemperature;
			}
			else if(currTemperature<lowestTemperature)
			{
				lowestTemperature=currTemperature;
			}
			if((oldTemperature>currTemperature)||(oldTemperature<currTemperature))
			{
	sendIFTTT(lowestTemperature, currTemperature, highestTemperature);
		
			}	
		
		}
		/*printf("Lowest: %d, Current: %d, Highest: %d", lowestTemperature, currTemperature, highestTemperature);
		*/
		delay(1000);
	}
	return 0;
}
int readTemperature()
{
	int i=0;
  	char output[1024];
  	char str[20];
	int temperature=0; 
        FILE *read;
        read=fopen("/sys/bus/w1/devices/28-0118423369ff/w1_slave","r");
        while(fgets(output, 150, read));
        for(i=29; i<34;i++)
        {
		str[i-29]=output[i];
        }
	fclose(read);       
        temperature=(atoi(str))/1000;
	return temperature;
}
void sendIFTTT(int l, int c, int h)
{
	char *currTemp=(char *) malloc(1);
	char  *lowestTemp=(char *) malloc(1);
	char  *highestTemp=(char *) malloc(1);
	sprintf(currTemp, "%d", c);
	sprintf(lowestTemp, "%d", l);
	sprintf(highestTemp, "%d", h);
	ifttt("https://maker.ifttt.com/trigger/temperature_change/with/key/9UekB0Eah3Y8GVtY4_0gL", lowestTemp, currTemp, highestTemp); 
}
