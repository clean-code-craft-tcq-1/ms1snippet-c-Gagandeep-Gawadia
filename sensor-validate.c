#include "sensor-validate.h"

#define soc_delta 0.05f
#define currentreading_delta 0.1f
//#define NULL (void *) 0
#include <cstddef>
#include <cstdio>

int NospikeIsDetected(double value, double nextValue, double maxDelta) {
  if(nextValue - value > maxDelta) {
    return 0;
  }
  return 1;
}
int evaluationofspikedetected(double* values, int numOfValues, float deltadifference )
{
	int lastButOneIndex = numOfValues - 1;
	for (int i = 0; i < lastButOneIndex; i++) {
		if (!NospikeIsDetected(values[i], values[i + 1], deltadifference)) {
			return 0;
		}
	}
	
	return 1;
}

int parametersAreValidIfSet(double* values, int numOfValues, float deltadifference, parametername parname, typeofcommunicationerror *communicationfailuredetails) {
	
	if ((values != NULL)&& (numOfValues)) // Neither a NULL pointer nor an empty array set is passed
	{ 
		int spikedetectedifclear = evaluationofspikedetected(values, numOfValues, deltadifference);
		return spikedetectedifclear;
		//communicationfailuredetails[parname] = nocommunicationfailure; 
		
	}
	else
	{
		communicationfailuredetails[parname] = communicationfailed;
		return 0;
	}
	
}

int SensorValidation(double * values_soc, int numOfdataset_soc , double * values_current, int numOfdataset_current, typeofcommunicationerror *communicationfailuredetails)
{  
		int currentNoSpikeDetectedIfTrue = 1;
		int socNoSpikeDetectedIfTrue = 1;
		int sensorNotNoisyIfTrue = 1;

		communicationfailuredetails[soc] = nocommunicationfailure;
		communicationfailuredetails[current] = nocommunicationfailure;
		socNoSpikeDetectedIfTrue = parametersAreValidIfSet(values_soc, numOfdataset_soc, soc_delta, soc, communicationfailuredetails);
		currentNoSpikeDetectedIfTrue = parametersAreValidIfSet(values_current, numOfdataset_current, currentreading_delta, current, communicationfailuredetails);
		
		//Sensor is detected as not noisy if neither soc or current has spike detected 
		sensorNotNoisyIfTrue = (socNoSpikeDetectedIfTrue & currentNoSpikeDetectedIfTrue);

		const char* sensorStateString = sensorStateFlag2StringConversion(sensorNotNoisyIfTrue);
		datamessage breach = evaluateBreachState(communicationfailuredetails);
		printToConsole(breach, sensorStateString);


		return  sensorNotNoisyIfTrue;
	
}


datamessage evaluateBreachState(typeofcommunicationerror *communicationfailuredetails)
{
	// If either soc or current reading had communication failure we cannot validate the sensor
	if ((communicationfailuredetails[soc] | communicationfailuredetails[current]))
	{
		return cannotvalidatesensor;
	}
	else
	{
		return canvalidatesensor;
	}
}


void printToConsole(datamessage breach, const char * sensorStateString)
{
	switch (breach)
	{
	case cannotvalidatesensor:
		printf("Error in communication \n");
		break;
	case canvalidatesensor:
		printf(" %s \n ", sensorStateString);
		break;
	}
}

const char* sensorStateFlag2StringConversion(int sensorNotNoisyIfTrue) {
	if (sensorNotNoisyIfTrue)
	{
		return "Sensor is not noisy";
	}
	else
	{
		return "Sensor is noisy";
	}

};

