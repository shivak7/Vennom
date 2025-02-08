// Runke Kutta with adaptive step size control
#include <iostream.h>

void rk4_step( double *y,double *ydiff,double *y_old,int nODE, 
		 double step, double x0   )

{

	void deri( int , double ,double *, double *);	// user supplied routine
							// which calculates derivative
	// setup the constants first
	
	// the coefficents for the steps in x
	double const a2=1./5. ,a3=3./10., a4=3./5., a5=1. ,a6=7./8. ;
	
	// coefficents for the y values
	double const b21=1./5. ;
	double const b31=3./40.   , b32=9./40. ;
	double const b41=3./10.   , b42=-9./10., b43=6./5. ;
	double const b51=-11./54. , b52=5./2.  , b53=-70./20. , b54=-35./27.;
	double const b61=1631./55296. , b62=175./312. , b63=575./13824. ;
	double const b64=44275./110592. , b65=253./1771. ;
	
	// coefficents for y(n-th order)
	double const c1=37./378. , c2=0. , c3=250./621., c4=125./594.,
	c5=0.,c6=512./1771. ;
	
	// coefficents for y(n+1-th order)
	double const cs1=2825./27648., cs2=0., cs3=18575./48384.,
	cs4=13525./55296. , cs5=277./14336., cs6 = 1./4. ;
	
	// the calculated values f
	double f[nODE] , f1[nODE] , f2[nODE] , f3[nODE] , f4[nODE] , f5[nODE]; 
	
	// the x value
	double x;
	double yp[nODE];
	int i;
	
	// here starts the calculation of the RK paramters
	 
	  deri(i,x,y,f);
	
	for(i=0; i<=nODE-1;i++) // 1. step
	{
	  y[i]=y_old[i]+b21*step*f[i];
	 }
	 x=x0+ a2*step;

	  deri(i,x,y,f1);

	for(i=0; i<=nODE-1;i++) //2. step
	{
	  y[i]=y_old[i]+b31*step*f[i]+b32*step*f1[i];
	 }
	 x=x0+ a3*step;

	  deri(i,x,y,f2);
	for(i=0; i<=nODE-1;i++) //3. step
	{
	  y[i]=y_old[i]+b41*step*f[i]+b42*step*f1[i]+b43*step*f2[i];
	 }
	 x=x0+ a4*step;

	  deri(i,x,y,f3);
	for(i=0; i<=nODE-1;i++) //4. step
	{
	  y[i]=y_old[i]+b51*step*f[i]+b52*step*f1[i]+b53*step*f2[i]+b54*step*f3[i];
	 }
	 x=x0+ a5*step;
	 
	  deri(i,x,y,f4);
	for(i=0; i<=nODE-1;i++) //5. step
	{
	  y[i]=y_old[i]+b61*step*f[i]+b62*step*f1[i]+b63*step*f2[i]+b64*step*f3[i]+b65*step*f4[i];
	 }
	 x=x0+ a6*step;
	 
	  deri(i,x,y,f5);
	for(i=0; i<=nODE-1;i++) //6. step
	{
	  y[i]=y_old[i]+step*(c1*f[i]+c2*f1[i]+c3*f2[i]+c4*f3[i]+c5*f4[i]+c6*f5[i]);
	  yp[i]=y_old[i]+step*(cs1*f[i]+cs2*f1[i]+cs3*f2[i]+cs4*f3[i]+cs5*f4[i]+cs6*f5[i]);
	  ydiff[i]=fabs (yp[i]-y[i]);
	 }
	 
	 return;

}
	 
	 
	 
	
	
