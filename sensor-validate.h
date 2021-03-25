//#include <stdbool.h>
#include "typedef.h"

int parametersAreValidIfSet(double* values, int numOfValues, float deltadifference);
int SensorValidation(struct validationdataset * Sensordataset, enum typeofcommunicationerror communicationfailuredetails);
int suddenJumpInDataIsDetected(double value, double nextValue, double maxDelta);
