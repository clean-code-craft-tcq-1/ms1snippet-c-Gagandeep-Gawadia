
#include "typedef.h"

int parametersAreValidIfSet(double* values, int numOfValues, float deltadifference, parametername individualpar, typeofcommunicationerror *communicationfailuredetails);
int SensorValidation( validationdataset * Sensordataset, typeofcommunicationerror *communicationfailuredetails);
int NospikeIsDetected(double value, double nextValue, double maxDelta);
void runSensorAnalysis();
void readData( validationdataset *Sensordataset);
datamessage evaluateBreachState(typeofcommunicationerror *communicationfailuredetails);
void printToConsole(datamessage breach, int sensornoisyisfalse);
