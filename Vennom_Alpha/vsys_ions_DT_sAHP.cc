#include "vsys_ions_DT_sAHP.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <ctime>
/*


	dX/dt = phi_X [(X_inf(V) - X)/tau_X(V)]
	
	X_inf(V) = 1/{1 + exp[-(V-theta_X)/sigma_X]} - K OR optional 1/[1 + exp(-theta_X/sigma_X)]
	
	tau_X(V) = theta_0X + theta1X/{1 + exp[-(V-theta_t_X)/sigma_t_X]}

*/

int VNNM_ions_DT_sAHP::Init(std::string fn, std::vector<double> P, VNNM_System * v_parent)		//Setting default rate parameters + Initial Conditions
{

	if(Parent==NULL)
		Parent = v_parent;
	else
		return -2;

	
	std::fstream f(fn.c_str(),std::ios::in);
	
	Type = 2;	// Declare as SubSystem
	
		
	f >> sID >> cID;	//Read string id, class id
	f >> doIntegrate;	//Read integration instruction
	f >> Nstates;		// Number of states


//	for(int i=0;i<Nstates;i++)
//	{	
//		double s = 0;
//		f >> s;		//Read integration instruction per state
//		dState.push_back(s);
//	}
	
	
	Nparams = 2+ Nstates*3;
	
	for(int i=0;i<Nparams;i++)
	{
		double g;
		f >> g;
		Params.push_back(g);
	}

	std::vector<std::string> lookup;
	std::string Ca_names;
	f >> Ca_names;
	lookup.push_back(Ca_names);
	f >> Ca_names;
	lookup.push_back(Ca_names);
	
	Siblings = Parent->findSiblings(lookup); //delete with destructor
	
	if(Siblings==NULL)
	{ std::cout << "Missing dependent calcium ion specification!\n"; exit(-1);}

	
	for(int i=0;i<lookup.size();i++)
	if(Siblings[i]==NULL)
	{ std::cout << "Missing DT Calcium ions!\n"; exit(-1);}

	
	f.close();
	
	if(State.size()<1)
	for(int i=0;i<Nstates;i++)
	{    
	    	State.push_back(0);
	    		for(int j=0;j<NUM_INT_MAX;j++)
		    	{
		    		TempState[j].push_back(1);
		    		KTempState[j].push_back(1);
		    	}
	   
	}
		
	return cID;
}

int  VNNM_ions_DT_sAHP::Info()
{
	std::cout << "Unique ID :\t" << sID << std::endl;
	std::cout << "Class ID :\t" << cID << std::endl;
	std::cout << "Do Integration :\t" << doIntegrate << std::endl;
	std::cout << "Number of states :\t" << Nstates << std::endl;
	
	std::cout << "Channel Conductance and Reversal potential :\t" << Params[0] << '\t' << Params[1] << std::endl;
	
	std::cout << "Epsilon, Kca, K1: \t" << Params[2] << '\t' << Params[3] << '\t' << Params[4] << std::endl;  	
	
	std::cout << std::endl << std::endl << std::endl;
	return 0;
}

int VNNM_ions_DT_sAHP :: SetParameters(std::vector<double>& P)
{
	if((P.size()==Nparams)&&(Params.size()==Nparams))
		for(int i=0;i<Nparams;i++)
		{
			Params[i] = P[i];
		}
	else
		return -1;
	return 0;
}

int VNNM_ions_DT_sAHP :: SetParameter(int index,double val)
{
	if(Params.size()==Nparams)
		Params[index] = val; 
	return 0;
}

static double x_inf(double V, double theta, double sigma)
{

	return 1.0/(1 + exp(-(V-theta)/sigma));

}


static double x_tau(double V,double tau_0, double tau_1, double tau_theta, double tau_sigma, double m, double n)
{

	if(n==1)
		return tau_0 + tau_1/(m + exp(-(V - tau_theta)/tau_sigma));
	else
		return tau_0 + tau_1/(m + exp(-pow((V - tau_theta)/tau_sigma,n)));
}


int VNNM_ions_DT_sAHP::diff(double t, double dt, const std::vector<double> & curr_state, std::vector<double> & diff_state, int Order)
{

	int p_step = 2;

	double V = 0;
	 	(*Parent)(t,&V,Order);

	//assert in Init that Nstates = 1 for this class

	if(doIntegrate==1)  
	{
			double Ca_current_1, Ca_current_2; 
			(*Siblings[0])(t,&Ca_current_1,Order);
			(*Siblings[1])(t,&Ca_current_2,Order);
			diff_state[0] = Params[p_step+0] * (-Ca_current_1 -Ca_current_2 - Params[p_step+1]*curr_state[0]);
			//std::cout << "dX/dt = " << diff_state[0] << std::endl;
	}
	
	
	return 0;

}

int VNNM_ions_DT_sAHP :: operator()(double t, double * ret, int Order)
{

	double stateproduct = 1;
	
	double V = 0;
	(*Parent)(t,&V,Order);
	//if(doIntegrate==true) std::cout << "For no leak, voltage is: " << Parent->State[0] << std::endl;
	ret[0] = 0;

	int p_step = 2;

	if(Order==0)
	{	
		 	 
		ret[0] = Params[0]* (State[0]/(State[0]+Params[p_step+2])) *(V-Params[1]);
		//std::cout << "X(t) = " << (State[0]/(State[0]+Params[p_step+2])) << std::endl;		
	}
	else
	{
		ret[0] = Params[0]* (TempState[Order][0]/(TempState[Order][0]+Params[p_step+2])) *(V-Params[1]);
		//std::cout << "X(t) = " << TempState[Order][0] << std::endl;		
	}

	return 0;
}
