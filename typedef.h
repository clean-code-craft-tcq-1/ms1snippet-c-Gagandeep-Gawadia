
typedef enum 
{         soc,
          current,
}parametername;

typedef enum 
{
	nocommunicationfailure,
	communicationfailed,

}typeofcommunicationerror;

typedef enum 
{ 
	cannotvalidatesensor,
	canvalidatesensor,
}datamessage;

typedef struct validationdataset
{
	double * values_soc;
	int     numOfdataset_soc;
	bool    status_socreading;
	double * values_current;
	int     numOfdataset_current;
	bool    status_currentreading;
	
}validationdataset;
