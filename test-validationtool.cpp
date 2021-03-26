#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "sensor-validate.h"

TEST_CASE("reports error when soc jumps abruptly") {
        

	 typeofcommunicationerror communicationfailuredetails[2] = { nocommunicationfailure,nocommunicationfailure };

	 double socReadings[] =     { 0.0, 0.01, 0.5, 0.51 };
	 double currentReadings[] = { 0.0, 0.02, 0.03, 0.02 };

  	REQUIRE((SensorValidation( socReadings, 4, currentReadings,4, communicationfailuredetails)) == 0);
	
}
TEST_CASE("reports error when current jumps abruptly") {


	 typeofcommunicationerror communicationfailuredetails_1[2] = { nocommunicationfailure,nocommunicationfailure };

	 double socReadings_1[] =  { 0.01, 0.01, 0.04, 0.02 };
	 double currentReadings_1[] = { 0.0, 0.02, 0.03, 0.33 };
         
	REQUIRE((SensorValidation( socReadings_1 ,4, currentReadings_1, 4, communicationfailuredetails_1)) == 0);
	
}
TEST_CASE("reports error when empty array is passed ") {
        

	 typeofcommunicationerror communicationfailuredetails_2[2] = { nocommunicationfailure,nocommunicationfailure };

	 double socReadings_2[] =     { 0.0, 0.01, 0.5, 0.51 };
	 double currentReadings_2[] = { 0.0, 0.02, 0.03, 0.02 };

  	REQUIRE((SensorValidation( socReadings_2 , 0, currentReadings_2 ,0, communicationfailuredetails_2)) == 0);
	
}
TEST_CASE("reports error when NULL pointer is passed ") {
        
       typeofcommunicationerror communicationfailuredetails_2[2] = { nocommunicationfailure,nocommunicationfailure };
        REQUIRE((SensorValidation( (double*)NULL , 4, (double*)NULL , 4, communicationfailuredetails_2)) == 0);
	
}


