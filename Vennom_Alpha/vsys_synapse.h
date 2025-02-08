#include "vsys.h"

#define DT_SYNAPSE 8
class VNNM_synapse_system: public VNNM_System
{
	protected:
	int dum;
	VNNM_System * preNeuron;
	public:
	int connectFrom(VNNM_System *);
	
	VNNM_synapse_system(){Parent=NULL;}			//Default Constructor 
	int Init(std::string,std::vector<double>, VNNM_System *);			// Alternative Initializer
	int Info();
	int SetParameters(std::vector<double>&);
	int SetParameter(int,double);
	int getCID(){return cID;}
	std::string getSID(){return sID;}
	VNNM_System ** findSiblings(std::vector<std::string>){ return NULL; };
	int diff(double, double, const std::vector<double> & curr_state, std::vector<double> & diff_state,int Order);
	int operator()(double, double *, int Order);

};
