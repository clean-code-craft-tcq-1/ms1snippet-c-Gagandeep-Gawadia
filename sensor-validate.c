#include "sensor-validate.h"

#define soc_delta 0.05f
#define currentreading_delta 0.1f
#define NULL (void *) 0

int suddenJumpInDataIsDetected(double value, double nextValue, double maxDelta) {
  if(nextValue - value > maxDelta) {
    return 0;
  }
  return 1;
}

int parametersAreValidIfSet(double* values, int numOfValues, float deltadifference) {
	int lastButOneIndex = numOfValues - 1;
	for (int i = 0; i < lastButOneIndex; i++) {
		if (!suddenJumpInDataIsDetected(values[i], values[i + 1], deltadifference)) {
			return 0;
		}
	}
	return 1;
}

int SensorValidation(struct validationdataset * Sensordataset,enum typeofcommunicationerror communicationfailuredetails)
{   
	if (Sensordataset != NULL)
	{   
		communicationfailuredetails = nocommunicationfailure;

		int currentParIsValidatedIfTrue = 1;
		int sOCParIsValidatedIfTrue = 1;
		int sensorIsHealthyIfTrue = 1;

		sOCParIsValidatedIfTrue = parametersAreValidIfSet(Sensordataset->values_soc, Sensordataset->numOfdataset_soc, soc_delta);
		currentParIsValidatedIfTrue = parametersAreValidIfSet(Sensordataset->values_current, Sensordataset->numOfdataset_current, currentreading_delta);

		sensorIsHealthyIfTrue = (sOCParIsValidatedIfTrue&currentParIsValidatedIfTrue);
		return  sensorIsHealthyIfTrue;
	}
	else
	{
		communicationfailuredetails = communicationfailureothers;
		return 0;
	}
}
