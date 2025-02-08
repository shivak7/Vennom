#include "vsys.h"

#define VSYS_HH 3

class VNNM_HHcell_system: public VNNM_System
{
	protected:
	int dum;
	
	public:
	VNNM_HHcell_system(){Parent=NULL;}			//Default Constructor 
	int Init(std::string,std::vector<double>, VNNM_System * );			// Alternative Initializer
	int Info() { return 0;}
	int SetParameters(std::vector<double>&);
	int SetParameter(int,double);
	std::string getSID(){return sID;}
	int getCID(){return cID;}
	VNNM_System ** findSiblings(std::vector<std::string>);
	int diff(double, double, const std::vector<double> & curr_state, std::vector<double> & diff_state,int Order);
	int operator()(double, double *, int Order);

};
