#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "sensor-validate.h"

TEST_CASE("reports error when soc jumps abruptly") {
  struct validationdataset * Sensordataset;
  enum typeofcommunicationerror communicationfailuredetails;
  
	double socReadings[] = { 0.0, 0.01, 0.5, 0.51 };
	Sensordataset->numOfdataset_soc = sizeof(socReadings) / sizeof(socReadings[0]);
	int i = 0;
	int numofelements = Sensordataset->numOfdataset_soc;
	while (!numofelements)
	{
		Sensordataset->values_soc[i] = socReadings[i];
		i++;
		numofelements--;
	}


	double currentReadings[] = { 0.0, 0.02, 0.03, 0.33 };
	Sensordataset->numOfdataset_current = sizeof(currentReadings) / sizeof(currentReadings[0]);

	i = 0;
	numofelements = Sensordataset->numOfdataset_current;
	while (!numofelements)
	{
		Sensordataset->values_current[i] = currentReadings[i];
		i++;
		numofelements--;
	}

  REQUIRE(SensorValidation(struct validationdataset * Sensordataset,communicationfailuredetails) == 0);
}

//TEST_CASE("reports error when current jumps abruptly") {
//  double currentReadings[] = {0.0, 0.02, 0.03, 0.33};
//  int numOfCurReadings = sizeof(currentReadings) / sizeof(currentReadings[0]);
// REQUIRE(int SensorValidation(struct validationdataset * Sensordataset,enum typeofcommunicationerror communicationfailuredetails)(currentReadings, numOfCurReadings) == 0);
//}
