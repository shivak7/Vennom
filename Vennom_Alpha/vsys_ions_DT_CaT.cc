#include "vsys_ions_DT_CaT.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <ctime>
/*


	dX/dt = phi_X [(X_inf(V) - X)/tau_X(V)]
	
	X_inf(V) = 1/{1 + exp[-(V-theta_X)/sigma_X]} - K OR optional 1/[1 + exp(-theta_X/sigma_X)]
	
	tau_X(V) = theta_0X + theta1X/{1 + exp[-(V-theta_t_X)/sigma_t_X]}


*/

int VNNM_ions_DT_CaT::Init(std::string fn, std::vector<double> P, VNNM_System * v_parent)		//Setting default rate parameters + Initial Conditions
{

	if(Parent==NULL)
		Parent = v_parent;
	else
		return -2;

	std::fstream f(fn.c_str(),std::ios::in);
	std::string par_file;
	
	Type = 2;	// Declare as SubSystem
	
		
	f >> sID >> cID;	//Read string id, class id
	f >> doIntegrate;	//Read integration instruction
	f >> Nstates;		// Number of states


	for(int i=0;i<Nstates;i++)
	{	
		double s = 0;
		f >> s;		//Read integration instruction per state
		dState.push_back(s);
	}
		
	Nparams = 2+ Nstates*10;
	
	for(int i=0;i<Nparams;i++)
	{
		double g;
		f >> g;
		Params.push_back(g);
	}
	
	f.close();
	
	if(State.size()<1)
	for(int i=0;i<Nstates;i++)
	{    
	   if((dState[i]==0)||(dState[i]==2)||(dState[i] == 3)) //
	   {
	    	State.push_back(1);
	    		for(int j=0;j<NUM_INT_MAX;j++)
		    	{
		    		TempState[j].push_back(1);
		    		KTempState[j].push_back(1);
		    	}
	   }
	   else if(dState[i]==1)
	   {
	    	State.push_back(0);
	    		for(int j=0;j<NUM_INT_MAX;j++)
		    	{
		    		TempState[j].push_back(1);
		    		KTempState[j].push_back(1);
		    	}
	   }
	}
		
	return cID;
}

int  VNNM_ions_DT_CaT::Info()
{
	std::cout << "Unique ID :\t" << sID << std::endl;
	std::cout << "Class ID :\t" << cID << std::endl;
	std::cout << "Do Integration :\t" << doIntegrate << std::endl;
	std::cout << "Number of states :\t" << Nstates << std::endl;
	
	std::cout << "Channel Conductance and Reversal potential :\t" << Params[0] << '\t' << Params[1] << std::endl;
	
	std::cout << "State powers :\t";
	for(int i=0;i<Nstates;i++)
		std::cout << Params[2+i] << '\t';
	std::cout << std::endl;
	
	std::cout << "Alpha/Beta parameters: \n";

	int j=1;
	for(int i=Nstates+2;i<Nparams;i++)
	{
	   std::cout << Params[i] << " ";
	   if(j%8==0) std::cout << std::endl;
	   j++;
	}

	std::cout << std::endl << std::endl << std::endl;
	return 0;
}

int VNNM_ions_DT_CaT :: SetParameters(std::vector<double>& P)
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

int VNNM_ions_DT_CaT :: SetParameter(int index,double val)
{
	if(Params.size()==Nparams)
		Params[index] = val; 
	return 0;
}

static double x_inf(double V, double theta, double sigma)
{

	return 1.0/(1 + exp(-(V-theta)/sigma));

}

static double x_inf2(double r, double theta, double sigma)
{

	return x_inf(r,theta,sigma) - x_inf(0,theta,sigma);

}


static double x_tau(double V,double tau_0, double tau_1, double tau_theta, double tau_sigma, double m, double n)
{

	if(n==1)
		return tau_0 + tau_1/(m + exp(-(V - tau_theta)/tau_sigma));
	else
		return tau_0 + tau_1/(m + exp(-pow((V - tau_theta)/tau_sigma,n)));
}


int VNNM_ions_DT_CaT::diff(double t, double dt, const std::vector<double> & curr_state, std::vector<double> & diff_state, int Order)
{

	int p_step = 2+Nstates*2;

	double V = 0;
	 	(*Parent)(t,&V,Order);

	for(int i=0;i<Nstates;i++)	//assume first state is 'r' (ode)
	{
	 	if(dState[i]==1)
	 	{
			diff_state[i] = Params[2+Nstates+i]*(x_inf(V,Params[p_step+0],Params[p_step+1]) - curr_state[i])/x_tau(V,Params[p_step+2],Params[p_step+3],Params[p_step+4],Params[p_step+5], Params[p_step+6], Params[p_step+7]);
	 	}
		p_step+=8;
	}

	return 0;
}

int VNNM_ions_DT_CaT :: operator()(double t, double * ret, int Order)
{

	double stateproduct = 1;
	
	double V = 0;
	(*Parent)(t,&V,Order);
	//if(doIntegrate==true) std::cout << "For no leak, voltage is: " << Parent->State[0] << std::endl;
	ret[0] = 0;

	int p_step = 2+Nstates*2;

	if(Order==0)
	{	
		for(int i=0;i<Nstates;i++)
		{
			 if(dState[i]==2)	// Instantaneous case
			 {
			 	double pow_val = Params[2+i];
			 	if(pow_val>1)
					{
					 double temp = x_inf(V, Params[p_step + 0], Params[p_step + 1]);
			 		 stateproduct*=pow(temp,pow_val);
					}
			 	else
			 		stateproduct*=x_inf(V, Params[p_step + 0], Params[p_step + 1]);
			 }
			 else if(dState[i]==3)	// Instantaneous case dependent on r instead of v
			 {
			 	double pow_val = Params[2+i];
			 	if(pow_val>1)
					{
					 double temp = x_inf2(State[0], Params[p_step + 0], Params[p_step + 1]);
			 		 stateproduct*=pow(temp,pow_val);
					}
			 	else
			 		stateproduct*=x_inf2(State[0], Params[p_step + 0], Params[p_step + 1]);
			 }
		 	 p_step+=8;
		 	 ret[0] = Params[0]*stateproduct*(V-Params[1]);
		}
	}
	else
	{
		for(int i=0;i<Nstates;i++)
		{
			 
			 if(dState[i]==2)	// Instantaneous case
			 {
			 	double pow_val = Params[2+i];
			 	if(pow_val>1)
					{
					 double temp = x_inf(V, Params[p_step + 0], Params[p_step + 1]);
			 		 stateproduct*=pow(temp,pow_val);
					}
			 	else
			 		stateproduct*=x_inf(V, Params[p_step + 0], Params[p_step + 1]);
			 }
			 else if(dState[i]==3)	// Instantaneous case
			 {
			 	double pow_val = Params[2+i];
			 	if(pow_val>1)
					{
					 double temp = x_inf2(TempState[Order][0], Params[p_step + 0], Params[p_step + 1]);
			 		 stateproduct*=pow(temp,pow_val);
					}
			 	else
			 		stateproduct*=x_inf2(TempState[Order][0], Params[p_step + 0], Params[p_step + 1]);
			 }
		 	 p_step+=8;
			 ret[0] = Params[0]*stateproduct*(V-Params[1]);
		}
	}
	return 0;
}
