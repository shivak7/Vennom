#include "vsys_hh_cell.h"
#include <cmath>
#include <fstream>
#include <iostream>


int VNNM_HHcell_system :: Init(std::string fn, std::vector<double> P, VNNM_System * v_parent)			//Setting default rate parameters + Initial Conditions
{
	
	Parent = v_parent;
	Type = 2;	// Declare as SubSystem

	std::fstream f(fn.c_str(),std::ios::in);

	int Nsubsys;
		
	f >> sID >> cID;	//Read string id, class id
	f >> doIntegrate;	//Read integration instruction	
	f >> Nstates;		// Number of states
	f >> Nsubsys;
	
	Nparams = 1;
	SubSystemCount = Nsubsys;
	
	for(int i=0;i<Nsubsys;i++)
	{
		std::string g;
		f >> g;
	}
	
	double C;
	double Idc;
	f >> C >> Idc;
	Params.push_back(C);
	Params.push_back(Idc);
	
	for(int i=0;i<Nstates;i++)
	{    
	   State.push_back(0);
	   
	   for(int j=0;j<NUM_INT_MAX;j++)
	    {
	    	TempState[j].push_back(0);
	    	KTempState[j].push_back(0);
	    }
	   	
	   
	}
	f.close();

	return cID;
}

int VNNM_HHcell_system :: SetParameters(std::vector<double>& P)
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

int VNNM_HHcell_system :: SetParameter(int index,double val)
{
	if(Params.size()==Nparams)
		Params[index] = val; 

	return 0;
}


VNNM_System ** VNNM_HHcell_system :: findSiblings(std::vector<std::string> lookup)
{

	VNNM_System ** ptrs=NULL;
	ptrs = new VNNM_System * [lookup.size()];
	int p = 0;
	
	for(int i=0;i<lookup.size();i++)
		for(int j=0;j<SubSystemCount;j++)
		{	  
			std::cout << lookup[i] << '\t' << SubSystems[j]->getSID() << std::endl;
			if(lookup[i]==SubSystems[j]->getSID())	//Bug: 
			{
				ptrs[p++] = SubSystems[j];
				j = SubSystemCount;
			}
			else ptrs[p] = NULL;					
		}	

	if(p==0)
	{
		std::cout << "Failed to find requested subsystem matches!" << std::endl;
		delete ptrs;
		ptrs = NULL;
	}
	
	return ptrs;
}


int VNNM_HHcell_system :: diff(double t, double dt, const std::vector<double> & curr_state, std::vector<double> & diff_state, int Order) //TODO: Add checking conditions for vector lengths
{
	
	for(int i=0;i<Nstates;i++)
	{	
		diff_state[i] = 0;
		for(int j=0;j<SubSystemCount;j++)
			{
				double a=0;
				(*SubSystems[j])(t,&a, Order);
				diff_state[i] -= a;
				//std::cout << "Ion current: " << j << " is : " << a << std::endl;
			}
			
		diff_state[i] += Params[1];	//DC current
		//if((t>=2000)&&(t<=2600))
		//	diff_state[i] -=25;
		
		
	//	std::cout << "Neuron diff volt: " << diff_state[i] << std::endl;
		diff_state[i] *= 1.0/Params[0];
		
	}

	return 0;
}


int VNNM_HHcell_system :: operator()(double t, double * ret, int Order)
{
	if(Order==0)
	{
		for(int i=0;i<Nstates;i++)	
			ret[i] = State[i];
	}
	else
	{
			for(int i=0;i<Nstates;i++)	
			ret[i] = TempState[Order][i];
	}

	return 0;
}

