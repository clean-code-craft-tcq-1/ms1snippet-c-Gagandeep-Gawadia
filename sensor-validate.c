/*****************************************************************************/
/***    \file        sensor-validate.c
 ***    \author      Gagandeep Gawadia
 ***
 ***    \brief       File contains function to evaluate sensor state 
/*****************************************************************************/

/*-------------------------------  Include files  -------------------------------------------*/
#include "sensor-validate.h"
#include <cstddef>
#include <cstdio>

/*-------------------------------  Macro definition ----------------------------------------- */
#define soc_delta 0.05f
#define currentreading_delta 0.1f

/* -------------------------------- Function definition--------------------------------------- */


/*****************************************************************************
Function name:  NospikeIsDetected                                        *//*!
\brief          Evaluates if spike is detected with consecutive dataset
\return         true, if spike is not detected
                false otherwise
*//**************************************************************************/


int NospikeIsDetected(double value, double nextValue, double maxDelta) {
  if(nextValue - value > maxDelta) {
    return 0;
  }
  return 1;
}

/*****************************************************************************
Function name:  evaluationofspikedetected                            *//*!
\brief          Evaluates if spike is detected with provide input array set
\return         false, if spike is detected
                true otherwise
*//**************************************************************************/

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

/*****************************************************************************
Function name:  parametersAreValidIfSet                                  *//*!
\brief          Evaluates if parameter provided are valid
                if,  Null pointer or empty array is provided as input 
		     communication error is detected 
		otherwise  evaluationofspikedetected is called.
\return         false, if spike is detected / communication failure
                true otherwise
*//**************************************************************************/


int parametersAreValidIfSet(double* values, int numOfValues, float deltadifference, parametername parname, typeofcommunicationerror *communicationfailuredetails) {
	
	if ((values != NULL)&& (numOfValues)) // Neither a NULL pointer nor an empty array set is passed
	{ 
		int spikedetectedifclear = evaluationofspikedetected(values, numOfValues, deltadifference);
		return spikedetectedifclear;
		//communicationfailuredetails[parname] = nocommunicationfailure; 
		
	}
	else
	{
		communicationfailuredetails[parname] = communicationfailure;
		return 0;
	}
	
}

/**************************************************************************8***
Function name:  SensorValidation                                           *//*!
\brief          \main sensor validation function which invloves following steps
                 calls parametersAreValidIfSet to evaluate sensor state
		 calls sensorStateFlag2StringConversion converts sensor state 
		       flag to other format
		 calls evaluateBreachState to see if data could be validated 
		 calls printToConsole to print the evaluation result
\return          false, if sensor is noisy / communication failure
                 true otherwise
*//**************************************************************************/

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

/*****************************************************************************
Function name:  sensorStateFlag2StringConversion                          *//*!
\brief          converts sensor state flag to printable string

\return         string is Sensor is noisy/not
*//**************************************************************************/

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

/*****************************************************************************
Function name:  evaluateBreachState                                  *//*!
\brief          Evaluates breach state depending on if
                data could be validated or there was communication error
		
\return         cannotvalidatesensor, if communication failure is present
                canvalidatesensor,   otherwise
*//**************************************************************************/
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


/*****************************************************************************
Function name:  printToConsole                                  *//*!
\brief          prints error message or evaluation result 

\return         
*//**************************************************************************/

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
/*================== EoF (sensor-validate.c) ===============*/
