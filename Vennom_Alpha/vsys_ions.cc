#include "vsys_ions.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <ctime>

//VNNM_ions_system::VNNM_ions_system(std::string fn, VNNM_System * v_parent)			//Setting default rate parameters + Initial Conditions
//{
//		
//	Parent = v_parent;
//	Type = 2;	// Declare as SubSystem

//	std::fstream f(fn.c_str(),std::ios::in);
//	
//	std::string dum1;
//	int dum2;
//		
//	f >> dum1 >> dum2;	//Read string id, class id
//	f >> doIntegrate;	//Read integration instruction	
//	f >> Nstates;		// Number of states
//	
//	Nparams = 2+Nstates*11;	// 4 - gx,Ex, <pow1...powN>, <alpha*5,beta*5>*Nstate
//	
//	for(int i=0;i<Nparams;i++)
//	{
//		double g;
//		f >> g;
//		Params.push_back(g);
//	}
//	
//	f.close();
//	

//	for(int i=0;i<Nstates;i++)
//	{  

//		   if(doIntegrate==0)
//		   {
//		    	State.push_back(1);
//		    	for(int j=0;j<5;j++)
//		    	{
//		    		TempState[j].push_back(1);
//		    		KTempState[j].push_back(1);
//		    	}
//		    	
//		   }
//		   else   
//		   {
//		    	State.push_back(0);
//		    	for(int j=0;j<5;j++)
//		    	{
//		    		TempState[j].push_back(0);
//		    		KTempState[j].push_back(0);
//		    	}
//		   }

//	}
//	
//}

int VNNM_ions_system::Init(std::string fn, std::vector<double> P, VNNM_System * v_parent)		//Setting default rate parameters + Initial Conditions
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
	
	
	Nparams = 2+Nstates*11;
	
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

int  VNNM_ions_system::Info()
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

int VNNM_ions_system :: SetParameters(std::vector<double>& P)
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

int VNNM_ions_system :: SetParameter(int index,double val)
{
	if(Params.size()==Nparams)
		Params[index] = val; 
	return 0;
}

int VNNM_ions_system :: diff(double t, double dt, const std::vector<double> & curr_state, std::vector<double> & diff_state, int Order) //TODO: Add checking conditions for vector lengths
{
	int p_step = 2+Nstates;	//skip past gx,Ex and state powers
	
		//Assuming Parent will always be a neuron / compartment
	
	double V = 0;
	 	(*Parent)(t,&V,Order);
		
	// return  (r.A * (V - r.B) + r.E) / (exp((V-r.B)/r.C) - r.D);
	double rf1=0,rf2=0;
	
	#ifdef VSYS_APPROX
	
	for(int i=0;i<Nstates;i++)
	{
	// Calculate Rate functions for alpha_m, beta_m, alpha_h and beta_h
	rf1 = ((Params[0+p_step] * (V - Params[1+p_step]) + Params[4+p_step]) / (fastexp((V-Params[1+p_step])/Params[2+p_step]) - Params[3+p_step]));
	p_step += 5;
	rf2 = ((Params[0+p_step] * (V - Params[1+p_step]) + Params[4+p_step]) / (fastexp((V-Params[1+p_step])/Params[2+p_step]) - Params[3+p_step]));
	p_step += 5;
	
	diff_state[i] = rf1 * (1 - curr_state[i]) - (rf2*curr_state[i]);	
	}
	
	#else
	
	for(int i=0;i<Nstates;i++)
	{
	// Calculate Rate functions for alpha_m, beta_m, alpha_h and beta_h
	rf1 = ((Params[0+p_step] * (V - Params[1+p_step]) + Params[4+p_step]) / (exp((V-Params[1+p_step])/Params[2+p_step]) - Params[3+p_step]));
	p_step += 5;
	rf2 = ((Params[0+p_step] * (V - Params[1+p_step]) + Params[4+p_step]) / (exp((V-Params[1+p_step])/Params[2+p_step]) - Params[3+p_step]));
	p_step += 5;
	
	diff_state[i] = rf1 * (1 - curr_state[i]) - (rf2*curr_state[i]);	
	}
	
	#endif
	
	return 0;
}

int VNNM_ions_system :: operator()(double t, double * ret, int Order)
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
		 	double pow_val = Params[2+i];
		 	if(pow_val>1)
		 	#ifdef VSYS_APPROX
		 		stateproduct*=fastpow(State[i],pow_val);
		 	#else
		 		stateproduct*=pow(State[i],pow_val);
		 	#endif
		 	else
		 		stateproduct*=State[i];
		 }
	 
		 ret[0] = Params[0]*stateproduct*(V-Params[1]);
	}
	else
	{
		if(doIntegrate)
		for(int i=0;i<Nstates;i++)
		{
			double pow_val = Params[2+i];
			if(pow_val>1)
			#ifdef VSYS_APPROX
		 		stateproduct*=fastpow(TempState[Order][i],pow_val);
		 	#else
		 		stateproduct*=pow(TempState[Order][i],pow_val);
		 	#endif
		 	else
		 		stateproduct*=TempState[Order][i];
		 }
	 
		 ret[0] = Params[0]*stateproduct*(V-Params[1]);
	}

	return 0;
}
