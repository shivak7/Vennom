#include <vector>
#include "vsys.h"

#define VSYS_RC_IONS 4
/* -----------------Structure of alpha and beta functions--------------------
	
			dX/dt = alpha(v)*(1-X) - beta(v)*X
	
			alpha OR beta 	= N(v)/D(v)
				
					= [A * (V-B) + E] / {exp[(V-B)/C] - D}
					
					
			We require 5 parameters per alpha/beta rate function
					
	   -------------------------------------------------------------------------*/

/*
	double rate_func(struct rate_params_type r, double V)
	{
		return  (r.A * (V - r.B) + r.E) / (exp((V-r.B)/r.C) - r.D);
	}
	
*/

class VNNM_ions_system : public VNNM_System
{
	protected:
	int dum;
	public:
	VNNM_ions_system(){Parent=NULL;}			//Default Constructor 
	VNNM_ions_system(std::string, VNNM_System * );			//Constructor 2
	int Init(std::string,std::vector<double>, VNNM_System * );			// Alternative Initializer
	int getCID(){return cID;}
	std::string getSID(){return sID;}
	int Info();
	int SetParameters(std::vector<double>&);
	int SetParameter(int,double);
	VNNM_System ** findSiblings(std::vector<std::string>) { return NULL; };
	int diff(double, double, const std::vector<double> & curr_state, std::vector<double> & diff_state, int Order);
	int operator()(double, double *,int Order);
};
