#include "algo_utils.h"

void SplineDeriv(std::vector<double> &Out, std::vector<double> &Derivs, int columns)
{
	
	double p=0, sig = 0, qn = 0, un = 0;

	std::vector<double> u;
	
	std::cout << "Total samples: " << Out.size()/(columns) << std::endl;
	
	for(int j=0;j<columns;j++)
	{	
		Derivs.push_back(0);
		u.push_back(0);
	}
	
	for(int i=1;i<(Out.size()/(columns))-1;i++)
	{
		double x1 = Out[0 + (columns)*i];
		double x0 = Out[0 + (columns)*(i-1)];
		double x2 = Out[0 + (columns)*(i+1)];
		
		sig = (x1 - x0)/(x2 - x0);
		
		Derivs.push_back(0);	// These take care of time column (1st column)
		u.push_back(0);		// These don't need derivatives calculated
		for(int j=1;j<columns;j++)
		{
			double y0 = Out[j + (columns)*(i-1)];
			double y1 = Out[j + (columns)*i];
			double y2 = Out[j + (columns)*(i+1)];

		   p = sig*Derivs[j + (columns)*(i-1)] + 2;
		   Derivs.push_back((sig - 1.0)/p);
		   u.push_back( (y2 - y1)/(x2 - x1) - (y1 - y0)/(x1 - x0) );
		   u[u.size()-1] = ((6 * u[u.size()-1] / (x2 - x0)) - sig*u[u.size()-2])/p;
		
		}
	
	}
	
	//Derivs for end points
	
	Derivs.push_back(0);	// These take care of time column (1st column)
	u.push_back(0);		// These don't need derivatives calculated
	
	for(int j=1;j<columns;j++)
	{
	
	   int Last = (u.size() - 1)- 1*columns;
	   double u_pre = u[j + Last];
	   double d_pre = Derivs[j + Last];
	   double val = (un - qn * u_pre)/(qn * d_pre + 1.0);
	   Derivs.push_back(val);
	   u.push_back(0);
	}

	std::cout << "Total Deriv samples: " << Derivs.size()/(columns) << std::endl;
	std::cout << "Total u samples: " << u.size()/(columns) << std::endl;
	
	// Final routine for backsubstituition of tridiagnol algorithm
	
	for(int i= (Out.size()/(columns))-1;i>=0;i--)
	{
		for(int j=1;j<columns;j++)
		{
			Derivs[j + (columns)*i] = Derivs[j + (columns)*i] * Derivs[j + (columns)*(i+1)] + u[j + (columns)*i];
		}
	}
}


void Spline(std::vector<double> &Out, std::vector<double> &Derivs, std::vector<int> &reg_idx, std::vector<double> &Out_sampled, int columns, double dt)
{
	for(int i=0;i<columns;i++)
	 Out_sampled.push_back(Out[i]);		//Store all first values

	for(int i=1;i<reg_idx.size()-1;i++)	//first value [0] is not estimated
	{
	
		double t_samp = dt*i;
		int idx_pre = reg_idx[i] - 1;
		int idx_post = reg_idx[i] + 1;
		
		double t_pre = Out[0 + (columns)*idx_pre];
		double t_post = Out[0 + (columns)*idx_post];
		
		double h = t_post - t_pre;
		
		double a = (t_post - t_samp)/h;
		double b = (t_samp - t_pre)/h;
		
		Out_sampled.push_back(t_samp);	//Push time in as the first column
		
		for(int j=1;j<columns;j++)
		{
			double y_pre = Out[j + (columns)*idx_pre];
			double y_post = Out[j + (columns)*idx_post];
			double y2_pre = Derivs[j + (columns)*idx_pre];
			double y2_post = Derivs[j + (columns)*idx_post];
			
			double y = a*y_pre + b*y_post + ((a*a*a -a)*y2_pre + (b*b*b -b)*y2_post)*(h*h)/6.0;
			
			Out_sampled.push_back(y);	
		}
	}
	
	for(int i=0;i<columns;i++)
	 Out_sampled.push_back(Out[Out.size() - columns +i ]);		//Store all last values values
	
	std::cout << "Total re-samples: " << Out_sampled.size()/(columns) << std::endl;
}
