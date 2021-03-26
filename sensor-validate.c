#include "sensor-validate.h"

#define soc_delta 0.05f
#define currentreading_delta 0.1f
//#define NULL (void *) 0
#include <cstddef>


int NospikeIsDetected(double value, double nextValue, double maxDelta) {
  if(nextValue - value > maxDelta) {
    return 0;
  }
  return 1;
}


int parametersAreValidIfSet(double* values, int numOfValues, float deltadifference, parametername parname, typeofcommunicationerror *communicationfailuredetails) {
	
	if (numOfValues) //Not an empty array  
	{
		int lastButOneIndex = numOfValues - 1;
		for (int i = 0; i < lastButOneIndex; i++) {
			if (!NospikeIsDetected(values[i], values[i + 1], deltadifference)) {
				return 0;
			}
		}
		//communicationfailuredetails[parname] = nocommunicationfailure; 
		return 1;
	}
	else //Incase of empty array or NULL
	{
		communicationfailuredetails[parname] = communicationfailed;
		return 0;
	}
	
}

int SensorValidation(struct validationdataset * Sensordataset, typeofcommunicationerror *communicationfailuredetails)
{  
	if (Sensordataset != NULL)
	{
		int currentNoSpikeDetectedIfTrue = 1;
		int socNoSpikeDetectedIfTrue = 1;
		int sensorNotNoisyIfTrue = 1;

		communicationfailuredetails[soc] = nocommunicationfailure;
		communicationfailuredetails[current] = nocommunicationfailure;
		socNoSpikeDetectedIfTrue = parametersAreValidIfSet(Sensordataset->values_soc, Sensordataset->numOfdataset_soc, soc_delta, soc, communicationfailuredetails);
		currentNoSpikeDetectedIfTrue = parametersAreValidIfSet(Sensordataset->values_current, Sensordataset->numOfdataset_current, currentreading_delta, current, communicationfailuredetails);
		
		//Sensor is detected as not noisy if neither soc or current has spike detected 
		sensorNotNoisyIfTrue = (socNoSpikeDetectedIfTrue & currentNoSpikeDetectedIfTrue);
		return  sensorNotNoisyIfTrue;
	}
	else
	{ 
		communicationfailuredetails[soc] = communicationfailed;
		communicationfailuredetails[current] = communicationfailed;
		return 0;
	}
}


void readData( validationdataset *Sensordataset) {
	
	//write data to the structure after sampling
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

void printToConsole(datamessage breach, int sensornoisyisfalse)
{
	switch (breach)
	{
	case cannotvalidatesensor:
		printf("error in communication");
		break;
	case canvalidatesensor:
		if (!sensornoisyisfalse)
		{
			printf("Sensor is Noisy");
		}
		break;
	}
}

void runSensorAnalysis() {

	validationdataset intializedataset = { 0 };
        //Initialization of variables
	validationdataset * Sensordataset = &intializedataset;
        typeofcommunicationerror communicationfailuredetails[2] = { nocommunicationfailure,nocommunicationfailure };
	datamessage breach;

	readData(Sensordataset);
        int sensorNotNoisyIfTrue = SensorValidation(Sensordataset, communicationfailuredetails);
	breach = evaluateBreachState(communicationfailuredetails);
	printToConsole(breach , sensorNotNoisyIfTrue);

}
