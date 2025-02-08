#include "vsys_synapse.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <ctime>


/*
	Synapse 1 dim ODE equation, taken from D. Terman 2002 STN-GPe paper
	
	dS/dt = alpha*H_inf*(v_pre - theta)(1 - S) - (beta*s)
	
*/

int VNNM_synapse_system::Init(std::string fn, std::vector<double> P, VNNM_System * v_parent)		//Setting default rate parameters + Initial Conditions
{

	if(Parent==NULL)
		Parent = v_parent;
	else
		return -2;

	Parent->SubSystems.push_back(this);	//Connect self to parent
	Parent->SubSystemCount++;
	
	std::fstream f(fn.c_str(),std::ios::in);
	std::string par_file;
	
	Type = 2;	// Declare as SubSystem
	
		
	f >> sID >> cID;	//Read string id, class id
	f >> doIntegrate;	//Read integration instruction	
	f >> Nstates;		// Number of states
		
	Nparams = 2+5;
	
	for(int i=0;i<Nparams;i++)
	{
		double g;
		f >> g; 
		Params.push_back(g);
	}
	
	f.close();
	
	for(int i=0;i<Nstates;i++)
	{    
	   if(doIntegrate==0)
	   {
	    	State.push_back(1);
	    		for(int j=0;j<NUM_INT_MAX;j++)
		    	{
		    		TempState[j].push_back(1);
		    		KTempState[j].push_back(1);
		    	}
	   }
	   else   
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

int  VNNM_synapse_system::Info()
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
	   if(j%5==0) std::cout << std::endl;
	   j++;
	}

	std::cout << std::endl << std::endl << std::endl;
	return 0;
}

int VNNM_synapse_system :: SetParameters(std::vector<double>& P)
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

int VNNM_synapse_system :: SetParameter(int index,double val)
{
	if(Params.size()==Nparams)
		Params[index] = val; 
	return 0;
}


int VNNM_synapse_system :: connectFrom(VNNM_System * ptr)
{
	preNeuron = ptr;		
	return 0;
}


static double x_inf(double V, double theta, double sigma)
{

	return 1.0/(1 + exp(-(V-theta)/sigma));

}


/*
	Synapse 1 dim ODE equation, taken from D. Terman 2002 STN-GPe paper
	
	dS/dt = alpha*H_inf*(v_pre - theta)(1 - S) - (beta*s)
	
*/

int VNNM_synapse_system :: diff(double t, double dt, const std::vector<double> & curr_state, std::vector<double> & diff_state, int Order)
{
	double V = 0;
	 	(*preNeuron)(t,&V,Order);
	 
	 int p_step = 2;
	 int i = 0;	//Assume only single dimensional ODE (1 state)
	 {
		diff_state[i] = ((Params[p_step+0]*x_inf(V-Params[p_step+1],Params[p_step+2],Params[p_step+3]))*(1 - curr_state[i])) - (Params[p_step+4]*curr_state[i]);
		
	 }
	 return 0;
}

int VNNM_synapse_system :: operator()(double t, double * ret, int Order)
{
	double stateproduct = 1;
	
	double V = 0;
	(*Parent)(t,&V,Order);
	//if(doIntegrate==true) std::cout << "For no leak, voltage is: " << Parent->State[0] << std::endl;
	ret[0] = 0;
	
	if(Order==0)
	{	
		if(doIntegrate)
		for(int i=0;i<Nstates;i++)
		 {	
		 		stateproduct*=State[i];
		 }
	 
		 ret[0] = Params[0]*stateproduct*(V-Params[1]);
	}
	else
	{
		if(doIntegrate)
		for(int i=0;i<Nstates;i++)
		{
		 		stateproduct*=TempState[Order][i];
		}
	 
		 ret[0] = Params[0]*stateproduct*(V-Params[1]);
	}

	return 0;
}
