#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "../vsys.h"

extern "C" {


	double sigmoid(double x)
	{
	
		return 1.0/(1 + exp(-x));
	
	}

	int diff (int Nstates, double t, double dt, const std::vector<double> & Params, const std::vector<double> & curr_state, std::vector<double> & diff_state, std::vector<int> & integrate_flags, int Order, VNNM_System * Parent)
	{
	
		for(int i=0;i<diff_state.size();i++)
		{
			diff_state[i] = 0;
		
		}
		
		return 0;
	
	}
	
	int aux (int Nstates, double t, double * ret, const std::vector<double> & Params, const std::vector<double> & curr_state, std::vector<int> & integrate_flags, int Order, VNNM_System * Parent)
	{
		
		*ret = 0;
		
		std::cout << "Template2 lib works: " << *ret << std::endl;
		
		return 0;
	
	}

}
