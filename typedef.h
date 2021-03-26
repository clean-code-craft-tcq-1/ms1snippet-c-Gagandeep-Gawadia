/******************************************************************************/
/***    \file        sensor-validate.h
 ***    \author      Gagandeep Gawadia
 ***
 ***    \brief       File contains declaration for sensor-validate.c functions 
/*****************************************************************************/

/*---------------------------------- Datatypes ------------------------------*/
typedef enum 
{         soc,
          current,
}parametername;

typedef enum 
{
	nocommunicationfailure,
	communicationfailure,

}typeofcommunicationerror;

typedef enum 
{ 
	cannotvalidatesensor,
	canvalidatesensor,
}datamessage;

