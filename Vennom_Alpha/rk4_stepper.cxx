// routine rk4_stepper
// adaptive step size Runge Kutta ODE solver
// uses rk4_step 
#include <iostream>
#include <fstream>
#include<ostream>
#include <math.h>
#include <minmax.h>

using namespace std;

void rk4_stepper(double y_old[],int nODE, double xstart, double xmax,
		double hstep, double eps, int &nxstep)
{
    void rk4_step(double *, double *, double *,int , double ,double);
	double heps; // the product of the step size and the chosen error
	double yerrmax=.99; // the max error in a step, 
	int i=0;
	double const REDUCE=-.22 ; // reduce stepzise power
	double esmall ;// the lower limit of precision, if the result is smaller
		       //than this we increase the step size
	double ydiff[nODE];
	double y[nODE];
	double hnew; // new step size
	double x0;
	double xtemp; // temporary x for rk4_step
	double step_lolim; // lower limit for step size
	double step_hilim; // upper limit for step size
		  
		  
	// here we create a file for storing the claculated functions
	ofstream out_file;
	out_file.open("rk4.dat");
	 out_file.setf(ios::showpoint | ios ::scientific | ios::right);
	
	x0=xstart;

		for(i=0 ; i<=nODE-1 ; i++)
		 {
		    
		// store starting values
			out_file <<  x0 << "  "<<y_old[i]<<"\n";
		  } 
	       
	esmall=eps/50.; 
	heps=eps*hstep;
	
	step_lolim=hstep/10.; // the step size should not go lower than 10 %
	step_hilim=hstep*10.; // We don't want larger step size
	        for(i=0;i<=nODE-1;i++)
		 {
		 y[i]=y_old[i];
		 }
		  
	for( ; ; )
	{
	  yerrmax=.99;
	   for( ; ; )
	     {
		xtemp=x0+hstep;
		rk4_step(y,ydiff,y_old,nODE,hstep,xtemp);
	        for(i=0;i<=nODE-1;i++)
	         {
	           yerrmax=max(yerrmax,heps/ydiff[i]);
		 }
		 if(yerrmax > 1.) break;
		hstep=.9*hstep*pow(yerrmax,REDUCE);
		 heps=hstep*eps;

		// error if step size gets too low
		if(hstep<step_lolim)
		  { 
		    cout << "rk4_stepper: lower step limit reached; try lower starting " 
			 << "step size \n " ;
		    cout << " I will terminate now \n ";
		    exit(0);
		  }
	      } 
		// go further by one step
		// first check if our step size is  too small
		
		if (yerrmax>1./esmall)hstep=hstep*2.;
		
		// set upper limit for step size
		if(hstep>step_hilim){
		hstep=step_hilim;
		}
		for(i=0 ; i<=nODE-1 ; i++)
		 {
		    y_old[i]=y[i];
		    
		// store data in file rk4.dat
			out_file <<  xtemp << "  "<<y[i]<<"\n";
		  } 
		   
//		x0 += hstep;
		x0=xtemp;
		nxstep=nxstep+1;
		if(x0>xmax) 
		{
		cout << nxstep;
		  out_file.close(); // close data file
		  return ;
		}
		
	  }
	  
	  return;

}	 
