#include "num_int.h"
#ifdef VSYS_OMP
	#include <omp.h> 
#endif

#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))


void VNNM_Integrate :: EulerIntegrate(std::vector<VNNM_System *>& ALL,double & t, double dt)
{

	int Order = 0;
	
	long unsigned int T_size = ALL.size();

		
	for(int i=0;i<T_size;i++)
	{	
		if(ALL[i]->doIntegrate)
		{
			ALL[i]->diff(t,dt,ALL[i]->State,ALL[i]->KTempState[1],Order);

		//	std::cout << ALL[i]->getSID() << '\t' << ALL[i]->Nstates << '\t' << ALL[i]->State.size() << std::endl;
			for (int j = 0; j < ALL[i]->Nstates; j++)
				ALL[i]->TempState[0][j] = ALL[i]->State[j] + dt*ALL[i]->KTempState[1][j];
		}
	}
	
	t+=dt;
	Update(ALL);
}

void VNNM_Integrate :: RK4init(int N)
{

 h_coeffs[0] = 0.5;
 h_coeffs[1] = 0.5;
 h_coeffs[2] = 1.0;
 
}

void VNNM_Integrate :: Update(std::vector<VNNM_System *>& ALL)
{
	for(int i=0;i<ALL.size();i++)
  	 for(int j=0;j<ALL[i]->Nstates;j++)
	   ALL[i]->State[j] = ALL[i]->TempState[0][j];

}

//void * thread_diff(std::vector<VNNM_System *>& ALL,double t, double dt, int Order)
//{

//	long unsigned int T_size = ALL.size();
//	
//	for(int i=0;i<T_size;i++)
//	{	
//		if(ALL[i]->doIntegrate)
//		{
//			if(Order==0)
//				ALL[i]->diff(t,dt,ALL[i]->State,ALL[i]->KTempState[1],Order);
//			else
//				ALL[i]->diff(t,dt,ALL[i]->TempState[Order],ALL[i]->KTempState[Order+1],Order);
//		}
//	}
//	return NULL;
//}

void VNNM_Integrate :: RK4Integrate(std::vector<VNNM_System *>& ALL,double &t, double dt)
{

	int Order = 0;
	
	long unsigned int T_size = ALL.size();

#ifdef VSYS_OMP
	#pragma omp parallel for
#endif

	for(int i=0;i<T_size;i++)
	{	

		if(ALL[i]->doIntegrate)
		{
			ALL[i]->diff(t,dt,ALL[i]->State,ALL[i]->KTempState[1],Order);

			for(int j=0;j<ALL[i]->Nstates;j++)
				ALL[i]->TempState[1][j] = ALL[i]->State[j] + 0.5*dt*ALL[i]->KTempState[1][j];
		}
	}

	Order++;
#ifdef VSYS_OMP
	#pragma omp parallel for
#endif
	for(int i=0;i<T_size;i++)
	{	

		if(ALL[i]->doIntegrate)
		{
			ALL[i]->diff(t+dt/2.0,dt/2.0,ALL[i]->TempState[1],ALL[i]->KTempState[2],Order);

			for(int j=0;j<ALL[i]->Nstates;j++)
				ALL[i]->TempState[2][j] = ALL[i]->State[j] + 0.5*dt*ALL[i]->KTempState[2][j];
		}
	}

	Order++;

#ifdef VSYS_OMP
	#pragma omp parallel for
#endif	
	for(int i=0;i<T_size;i++)
	{	

		if(ALL[i]->doIntegrate)
		{
			ALL[i]->diff(t+dt/2.0,dt/2.0,ALL[i]->TempState[2],ALL[i]->KTempState[3],Order);

			for(int j=0;j<ALL[i]->Nstates;j++)
				ALL[i]->TempState[3][j] = ALL[i]->State[j] + dt*ALL[i]->KTempState[3][j];
		}
	}	
	
	Order++;
#ifdef VSYS_OMP
	#pragma omp parallel for
#endif
	for(int i=0;i<T_size;i++)
	{	

		if(ALL[i]->doIntegrate)
		ALL[i]->diff(t+dt,dt,ALL[i]->TempState[3],ALL[i]->KTempState[4],Order);	
	}	
	
	
	for(int i=0;i<T_size;i++)
	 if(ALL[i]->doIntegrate)
	  for(int j=0;j<ALL[i]->Nstates;j++)
	  {
		double sumDT = ALL[i]->KTempState[1][j] + 2.0*ALL[i]->KTempState[2][j] + 2.0*ALL[i]->KTempState[3][j] + ALL[i]->KTempState[4][j];
		ALL[i]->TempState[0][j] = ALL[i]->State[j] + (dt/6.0)*sumDT;
		
	  }
		
	//return NextState;	
	t+=dt;
	Update(ALL);
}


void VNNM_Integrate :: RKCK(std::vector<VNNM_System *>& ALL,double t, double dt)
{

	static double a2=0.2,a3=0.3,a4=0.6,a5=1.0,a6=0.875,b21=0.2,
	b31=3.0/40.0,b32=9.0/40.0,b41=0.3,b42 = -0.9,b43=1.2,
	b51 = -11.0/54.0, b52=2.5,b53 = -70.0/27.0,b54=35.0/27.0,
	b61=1631.0/55296.0,b62=175.0/512.0,b63=575.0/13824.0,
	b64=44275.0/110592.0,b65=253.0/4096.0,c1=37.0/378.0,
	c3=250.0/621.0,c4=125.0/594.0,c6=512.0/1771.0,
	dc5 = -277.00/14336.0;
	double dc1=c1-2825.0/27648.0,dc3=c3-18575.0/48384.0,
	dc4=c4-13525.0/55296.0,dc6=c6-0.25;
	
	int Order = 0;
	
	long unsigned int T_size = ALL.size();
#ifdef VSYS_OMP
	#pragma omp parallel for
#endif
	for(int i=0;i<T_size;i++)
	{	
		if(ALL[i]->doIntegrate)
		{
			
			ALL[i]->diff(t,dt,ALL[i]->State,ALL[i]->KTempState[1],Order);

			for(int j=0;j<ALL[i]->Nstates;j++)
				ALL[i]->TempState[1][j] = ALL[i]->State[j] + b21*dt*ALL[i]->KTempState[1][j];
		}
	}
	
	Order++;

#ifdef VSYS_OMP
	#pragma omp parallel for
#endif
	for(int i=0;i<T_size;i++)
	{	
		
		if(ALL[i]->doIntegrate)
		{
			ALL[i]->diff(t+dt*a2,dt*a2,ALL[i]->TempState[1],ALL[i]->KTempState[2],Order);

			for(int j=0;j<ALL[i]->Nstates;j++)
				ALL[i]->TempState[2][j] = ALL[i]->State[j] + dt*(b31*ALL[i]->KTempState[1][j] + b32*ALL[i]->KTempState[2][j]);
		}
	}
	
	
	Order++;

#ifdef VSYS_OMP
	#pragma omp parallel for
#endif	
	for(int i=0;i<T_size;i++)
	{	
		if(ALL[i]->doIntegrate)
		{
			ALL[i]->diff(t+dt*a3,dt*a3,ALL[i]->TempState[2],ALL[i]->KTempState[3],Order);

			for(int j=0;j<ALL[i]->Nstates;j++)
				ALL[i]->TempState[3][j] = ALL[i]->State[j] + dt*(b41*ALL[i]->KTempState[1][j] + b42*ALL[i]->KTempState[2][j] + b43*ALL[i]->KTempState[3][j]);
			
		}
	}
	
	
	Order++;

#ifdef VSYS_OMP
	#pragma omp parallel for
#endif	
	for(int i=0;i<T_size;i++)
	{	
		if(ALL[i]->doIntegrate)
		{
			ALL[i]->diff(t+dt*a4,dt*a4,ALL[i]->TempState[3],ALL[i]->KTempState[4],Order);

			for(int j=0;j<ALL[i]->Nstates;j++)
				ALL[i]->TempState[4][j] = ALL[i]->State[j] + dt*(b51*ALL[i]->KTempState[1][j] + b52*ALL[i]->KTempState[2][j] + b53*ALL[i]->KTempState[3][j] + b54*ALL[i]->KTempState[4][j]);
			
		}
	}	

	
	Order++;

#ifdef VSYS_OMP
	#pragma omp parallel for
#endif	
	for(int i=0;i<T_size;i++)
	{	
		if(ALL[i]->doIntegrate)
		{
			ALL[i]->diff(t+dt*a5,dt*a5,ALL[i]->TempState[4],ALL[i]->KTempState[5],Order);

			for(int j=0;j<ALL[i]->Nstates;j++)
				ALL[i]->TempState[5][j] = ALL[i]->State[j] + dt*(b61*ALL[i]->KTempState[1][j] + b62*ALL[i]->KTempState[2][j] + b63*ALL[i]->KTempState[3][j] + b64*ALL[i]->KTempState[4][j] + b65*ALL[i]->KTempState[5][j]);
			
		}
	}
	
	Order++;

#ifdef VSYS_OMP
	#pragma omp parallel for
#endif	
	for(int i=0;i<T_size;i++)
	{	
		if(ALL[i]->doIntegrate)
		{
			ALL[i]->diff(t+dt*a6,dt*a6,ALL[i]->TempState[5],ALL[i]->KTempState[6],Order);

			for(int j=0;j<ALL[i]->Nstates;j++)
			{
				ALL[i]->TempState[0][j] = ALL[i]->State[j] + dt*(c1*ALL[i]->KTempState[1][j] + c3*ALL[i]->KTempState[3][j] + c4*ALL[i]->KTempState[4][j] + c6*ALL[i]->KTempState[6][j]);
				
				//Compute error
				
				ALL[i]->TempState[6][j] = dt*(dc1*ALL[i]->KTempState[1][j] + dc3*ALL[i]->KTempState[3][j] + dc4*ALL[i]->KTempState[4][j] + dc5*ALL[i]->KTempState[5][j] + dc6*ALL[i]->KTempState[6][j]);
			
			}
				
			
		}
	}
	
}



void VNNM_Integrate :: RKQS(std::vector<VNNM_System *>& ALL,double &t, double dt, double& dt_next, double eps)
{
	
	bool succeed = false;
	double errmax = 0;
	double htemp = 0;
	long unsigned int T_size = ALL.size();
	
	while(!succeed)
	{
		RKCK( ALL, t, dt);
		errmax = 0;
		for(int i=0;i<T_size;i++)
		{
			if(ALL[i]->doIntegrate)
			{
				
				for(int j=0;j<ALL[i]->Nstates;j++)
				{	errmax = MAX(errmax,std::abs(ALL[i]->TempState[6][j] / ALL[i]->TempState[7][j]));
					//std::cout << "Adaptive RK : " << ALL[i]->TempState[6][j] << '\t' << ALL[i]->TempState[7][j] << std::endl;
				}								
			}
			
		}			
		
		errmax /= eps;
		
		if(errmax <= 1.0)
		{
			succeed = true;
			continue;
		}
		
		htemp = SAFETY*dt*pow(errmax,PSHRNK);
		
		dt=(dt >= 0.0 ? MAX(htemp,0.1*dt) : MIN(htemp,0.1*dt));
		if(t + dt == t)
		{
			std::cout << "Error! Adaptive RK stepsize underflow error: " << dt << std::endl;
			exit(-1); 
		}		
	}	

	if(errmax > ERRCON) dt_next = SAFETY*dt*pow(errmax,PGROW);
	else dt_next = 5.0*dt;
	t = t + dt;
	Update(ALL);
	
}


void VNNM_Integrate :: RKAdaptive(std::vector<VNNM_System *>& ALL,double &t, double dt, double Tstart, double Tend, double dt_min)
{
	
	int Order = 0;
	long unsigned int T_size = ALL.size();
	double eps = 0.001;
	
#ifdef VSYS_OMP
	#pragma omp parallel for
#endif		
		
		for(int i=0;i<T_size;i++)
		{	
			if(ALL[i]->doIntegrate)
			{
				for(int j=0;j<ALL[i]->Nstates;j++)
				{
					ALL[i]->diff(t,dt,ALL[i]->State,ALL[i]->KTempState[0],Order);
					ALL[i]->TempState[7][j] = std::abs(ALL[i]->State[j]) + std::abs(ALL[i]->KTempState[0][j]*dt) + TINY;
				}

			}
		}
		
		if((t + dt - Tend)*(t+dt - Tstart) > 0)
			dt = Tend - t;				//overshoot case
		
		double dt2 = dt;
		double dt_next=0;
		RKQS(ALL,t, dt, dt_next, eps);
		if((t-Tend)*(Tend - Tstart) >= 0)
			return;
		
		if(abs(dt_next <= dt_min))
			{
				std::cout << "Error! Step size too small for adaptive RK. \n";
				exit(-1);
			}
		dt = dt_next;
		
}
