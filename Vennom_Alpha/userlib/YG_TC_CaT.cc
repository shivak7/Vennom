#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "../vsys.h"

#if defined DLL_EXPORT
#define DECLDIR __declspec(dllexport)
#else
#define DECLDIR __declspec(dllimport)
#endif

extern "C" {

#ifdef _WIN32
	DECLDIR int diff(int Nstates, double t, double dt, const std::vector<double> & Params, const std::vector<double> & curr_state, std::vector<double> & diff_state, std::vector<int> & integrate_flags, int Order, VNNM_System * Parent);
	DECLDIR int aux(int Nstates, double t, double * ret, const std::vector<double> & Params, const std::vector<double> & curr_state, std::vector<int> & integrate_flags, int Order, VNNM_System * Parent);
#endif

//------------------------------------------------------------------------------------------------------------

	double x_tau(double V, double k, double t0, double m0, double s0)
	{
	
		double b = k*(t0 + exp(-(V-m0)/s0));
		
		return b;
	
	}
	
	double x_inf(double V, double m0, double s0)
	{
		return 1.0/(1+ exp(-(V - m0)/s0));
	}

	int diff (int Nstates, double t, double dt, const std::vector<double> & Params, const std::vector<double> & curr_state, std::vector<double> & diff_state, std::vector<int> & integrate_flags, int Order, VNNM_System * Parent)
	{
	
		
		int p_step = 2+Nstates*2; //Skip gx,Vx, [powers] and [phi_X]
		
		double V = 0;
	 	(*Parent)(t,&V,Order);		//Assume Parent is a neuron
		
		for(int i=0;i<Nstates;i++)
		{
			if(integrate_flags[i]==1)
			{
				diff_state[i] = Params[2+Nstates+i]*(x_inf(V,Params[p_step+0],Params[p_step+1]) - curr_state[i])/x_tau(V,Params[p_step+2],Params[p_step+3],Params[p_step+4],Params[p_step+5]);
			}
			p_step+=6;
		}
		
		return 0;
	
	}
	
	int aux (int Nstates, double t, double * ret, const std::vector<double> & Params, const std::vector<double> & curr_state, std::vector<int> & integrate_flags, int Order, VNNM_System * Parent)
	{
		
		double stateproduct = 1;
		double V = 0;
		(*Parent)(t,&V,Order);
		
		int p_step = 2+Nstates*2;
		for(int i=0;i<Nstates;i++)
		{
	  		 if(integrate_flags[i]==1)	// if normal ODE
			 {
			 	double pow_val = Params[2+i];
			 	if(pow_val>1)
			 		stateproduct*=pow(curr_state[i],pow_val);
			 	else
			 		stateproduct*=curr_state[i];
			 }
			 else if(integrate_flags[i]==2)	// Instantaneous case
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
		 	 p_step+=6;
		 	 ret[0] = Params[0]*stateproduct*(V-Params[1]);
		}
				
		return 0;
	
	}

}
