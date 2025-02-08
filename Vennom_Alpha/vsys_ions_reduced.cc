#include "vsys_ions_reduced.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <ctime>
/*


	Zero state System


*/

int VNNM_ions_reduced::Init(std::string fn, std::vector<double> P, VNNM_System * v_parent)		//Setting default rate parameters + Initial Conditions
{

	if(Parent==NULL)
		Parent = v_parent;
	else
		return -2;

	std::fstream f(fn.c_str(),std::ios::in);	//Ion file
	std::string par_file;
	
	Type = 2;	// Declare as SubSystem
	
		
	f >> sID >> cID;	//Read string id, class id
	f >> doIntegrate;	//Read integration instruction	//should be 0
	f >> Nstates;		// Number of states 0/1

	for(int i=0;i<Nstates;i++)
	{	
		double s = 0;
		f >> s;		//Read integration instruction per state
		dState.push_back(s);
	}

	
	Nparams = 4;
	
	for(int i=0;i<Nparams;i++)
	{
		double g;
		f >> g;
		Params.push_back(g);
	}

	std::vector<std::string> lookup;
	std::string depend_name;
	f >> depend_name;
	lookup.push_back(depend_name);
	
	std::cout << "Lookup: " << depend_name << std::endl;
	std::cout << "Trying our luck 2! \n";
	std::cout << this->getSID() << std::endl;
	std::cout << "It worked! \n";


	Complement = Parent->findSiblings(lookup); //delete with destructor
	std::cout << "Name2: " << depend_name << "\n";

	if(Complement==NULL)
	{ std::cout << "Missing dependent ion specification!" << std::endl; exit(-1);}
	
	for(int i=0;i<lookup.size();i++)
		if(Complement[i]==NULL)
			{ std::cout << "Missing dependent ion specification!" << std::endl; exit(-1);}

	f.close();		
	return cID;
}

int VNNM_ions_reduced :: SetParameters(std::vector<double>& P)
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

int VNNM_ions_reduced :: SetParameter(int index,double val)
{
	if(Params.size()==Nparams)
		Params[index] = val; 
	return 0;
}

int VNNM_ions_reduced :: diff(double t, double dt, const std::vector<double> & curr_state, std::vector<double> & diff_state, int Order)
{
	return 1;
}

int VNNM_ions_reduced :: operator()(double t, double * ret, int Order)
{
	double V = 0;
	(*Parent)(t,&V,Order);
	
	double h = 0;
	if(Order==0)
		h = Complement[0]->State[1];
	else
		h = Complement[0]->TempState[Order][1];
		
	ret[0] = Params[0]*pow(Params[2]*(1-h),Params[3])*(V - Params[1]);

	return 0;
}
