#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "sensor-validate.h"

TEST_CASE("reports error when soc jumps abruptly") {
        

	 typeofcommunicationerror communicationfailuredetails[2] = { nocommunicationfailure,nocommunicationfailure };

	 double socReadings[] =     { 0.0, 0.01, 0.5, 0.51 };
	 double currentReadings[] = { 0.0, 0.02, 0.03, 0.02 };

	 validationdataset Sensordataset = { {socReadings},
		                              sizeof(socReadings) / sizeof(socReadings[0]),
		                              0,
					      {currentReadings},
		                              sizeof(currentReadings) / sizeof(currentReadings[0]),
		                              0,
	                                    };
  	REQUIRE(SensorValidation(Sensordataset,communicationfailuredetails) == 0);
  	REQUIRE(Sensordataset->status_socreading == 0);	
}
TEST_CASE("reports error when current jumps abruptly") {


	 typeofcommunicationerror communicationfailuredetails[2] = { nocommunicationfailure,nocommunicationfailure };

	 double socReadings[] =  { 0.01, 0.01, 0.04, 0.02 };
	 double currentReadings[] = { 0.0, 0.02, 0.03, 0.33 };

	 validationdataset Sensordataset = { {socReadings},
		                              sizeof(socReadings) / sizeof(socReadings[0]),
		                              0,
					      {currentReadings},
		                              sizeof(currentReadings) / sizeof(currentReadings[0]),
		                              0,
	                                    };
  	REQUIRE(SensorValidation(Sensordataset,communicationfailuredetails) == 0);
}


