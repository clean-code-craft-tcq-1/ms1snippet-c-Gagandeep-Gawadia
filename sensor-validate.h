/******************************************************************************/
/****    \file        sensor-validate.h
 ***    \author      Gagandeep Gawadia
 ***
 ***    \brief       File contains declaration for sensor-validate.c functions 
******************************************************************************/

/*----------------------------------Include file ------------------------------*/
#include "typedef.h"
 
/*---------------------------------- Function declaration ------------------------------*/
int parametersAreValidIfSet(double* values, int numOfValues, float deltadifference, parametername individualpar, typeofcommunicationerror *communicationfailuredetails);
int SensorValidation(double * values_soc, int numOfdataset_soc, double * values_current, int numOfdataset_current, typeofcommunicationerror *communicationfailuredetails);
int NospikeIsDetected(double value, double nextValue, double maxDelta);
datamessage evaluateBreachState(typeofcommunicationerror *communicationfailuredetails);
void printToConsole(datamessage breach, const char * sensorstate);
int evaluationofspikedetected(double* values, int numOfValues, float deltadifference);
const char* sensorStateFlag2StringConversion(int sensorNotNoisyIfTrue);

/*================== EoF (sensor-validate.h) ===============*/
