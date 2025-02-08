#include "vsys_custom.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <ctime>
#include <cstdlib>

int VNNM_custom::Init(std::string fn, std::vector<double> P, VNNM_System * v_parent)		//Setting default rate parameters + Initial Conditions
{

	if(Parent==NULL)
		Parent = v_parent;
	else
		return -2;

	std::fstream f(fn.c_str(),std::ios::in);	//Ion file
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
	
	f >> Nparams;		// !!!Very Important!!! User must specify number of parameters before hand.
	
	for(int i=0;i<Nparams;i++)
	{
		double g;
		f >> g;
		Params.push_back(g);
	}
	
	std::string user_lib;
	
	f >> user_lib;
	
	if(user_lib.length() > 2)
	{

#ifdef _WIN32
		user_lib = "userlib\\" + user_lib + ".dll";
		std::wstring w_user_lib = s2ws(user_lib);
		hinstLib = LoadLibrary(w_user_lib.c_str());
		
		if (hinstLib == NULL)
		{
			std::cout << "Unable to find/open DLL library: " << user_lib << std::endl;
			exit(-1);
		}
		diff_fn = (DFPTR)GetProcAddress(hinstLib, "diff");
		main_fn = (AFPTR)GetProcAddress(hinstLib, "aux");
		
#else	//UNIX DLL CODE SEGMENT
		user_lib = "userlib/" + user_lib + ".so";
   		lib_handle = dlopen(user_lib.c_str(), RTLD_NOW);
   		if (!lib_handle) 
   		{
      			fprintf(stderr, "%s\n", dlerror());
      			exit(-1);
   		}
		diff_fn = (DFPTR)dlsym(lib_handle, "diff");
		main_fn = (AFPTR)dlsym(lib_handle, "aux");
#endif
		if (diff_fn == NULL)
		{
			std::cout << "Missing function \"diff\" in user library:" << user_lib << std::endl;
			exit(-1);
		}

		if (main_fn == NULL)
		{
			std::cout << "Missing function \"aux\" in user library:" << user_lib << std::endl;
			exit(-1);
		}
		
	}	
	else
	{
		std::cout << "Invalid or unspecified library. " << std::endl;
		exit(-1);
	}
	
	std::vector <std::string> dependencies;
	
	while(!f.eof())
	{
		std::string dfn;
		f >> dfn;
		if(!f.eof())
		{
			if(dfn.size()>2)
			 dependencies.push_back(dfn);
		
		}
	
	}
	
	if(dependencies.size()==0)
		std::cout << "No Dependencies detected for " << sID << std::endl;
	else
		for(int i=0;i<dependencies.size();i++)
			std::cout << "Dependency " << i + 1 << " : " << dependencies[i] << std::endl;
	
	f.close();
	
	if(State.size()<1)
	for(int i=0;i<Nstates;i++)
	{    
	   if(!doIntegrate)
	   {
	    	State.push_back(1);
	    		for(int j=0;j<NUM_INT_MAX;j++)
		    	{
		    		TempState[j].push_back(1);
		    		KTempState[j].push_back(1);
		    	}
	   }
	   else if(doIntegrate)
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

int VNNM_custom :: SetParameters(std::vector<double>& P)
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

int VNNM_custom :: SetParameter(int index,double val)
{
	if(Params.size()==Nparams)
		Params[index] = val; 
	return 0;
}


int VNNM_custom :: diff(double t, double dt, const std::vector<double> & curr_state, std::vector<double> & diff_state, int Order)
{

	(*diff_fn)(Nstates, t, dt, Params, curr_state, diff_state, dState, Order, Parent);
	
	return 0;

}

int VNNM_custom :: operator()(double t, double * ret, int Order)
{

	if(Order==0)
		(*main_fn)(Nstates, t, ret, Params, State, dState, Order, Parent);
	else
		(*main_fn)(Nstates, t, ret, Params, TempState[Order], dState, Order, Parent);
		
	return 0;

}

