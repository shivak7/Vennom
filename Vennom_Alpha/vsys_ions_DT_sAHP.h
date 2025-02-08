#include <vector>
#include "vsys.h"
#include <cstdlib>

#define VSYS_DT_sAHP 7

class VNNM_ions_DT_sAHP : public VNNM_System
{
	protected:
	int dum; 
	VNNM_System ** Siblings;
	public:
	~VNNM_ions_DT_sAHP(){delete Siblings;}
	VNNM_ions_DT_sAHP(){Parent=NULL;}			//Default Constructor 
	//VNNM_ions_system(std::string, VNNM_System * );			//Constructor 2
	int Init(std::string,std::vector<double>, VNNM_System * );			// Alternative Initializer
	std::string getSID(){return sID;}
	int getCID(){return cID;}
	int Info();
	int SetParameters(std::vector<double>&);
	int SetParameter(int,double);
	VNNM_System ** findSiblings(std::vector<std::string>){ return NULL; };
	int diff(double, double, const std::vector<double> & curr_state, std::vector<double> & diff_state, int Order);
	int operator()(double, double *,int Order);
};
