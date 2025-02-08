#include <vector>
#include "vsys.h"

#define VSYS_DT_CaT 6
/*
	Special Class to model Terman STN/GPe low threshold Calcium current

	dX/dt = phi_X [(X_inf(V) - X)/tau_X(V)]
	
	X_inf(V) = 1/{1 + exp[-(V-theta_X)/sigma_X]} - K OR optional 1/[1 + exp(-theta_X/sigma_X)]
	
	tau_X(V) = theta_0X + theta1X/{1 + exp[-(V-theta_t_X)/sigma_t_X]}


*/

class VNNM_ions_DT_CaT : public VNNM_System
{
	protected:
	int dum;
	public:
	VNNM_ions_DT_CaT(){Parent=NULL;}			//Default Constructor 
	int Init(std::string,std::vector<double>, VNNM_System * );			// Alternative Initializer
	int Info();
	int SetParameters(std::vector<double>&);
	int getCID(){return cID;}
	std::string getSID(){return sID;};
	VNNM_System ** findSiblings(std::vector<std::string>){ return NULL; };
	int SetParameter(int,double);
	int diff(double, double, const std::vector<double> & curr_state, std::vector<double> & diff_state, int Order);
	int operator()(double, double *,int Order);

};
