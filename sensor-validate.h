//#include <stdbool.h>
#define maxnumofdataset 10

enum typeofcommunicationerror
{
	nocommunicationfailure,
	communicationfailedwithsocsensor,
	communicationfailedwithcurrentsensor,
	communicationfailureothers
};

struct validationdataset
{
	double  values_soc[maxnumofdataset];
	int     numOfdataset_soc;
	bool    status_socreading;
	double  values_current[maxnumofdataset];
	int     numOfdataset_current;
	bool    status_currentreading;
};

int parametersAreValidIfSet(double* values, int numOfValues, float deltadifference);
int SensorValidation(struct validationdataset * Sensordataset, enum typeofcommunicationerror communicationfailuredetails);
int suddenJumpInDataIsDetected(double value, double nextValue, double maxDelta);
