#ifndef _VSYS_H
#define _VSYS_H

#include<vector>
#include<string>

#ifdef VSYS_APPROX
#include "fastmath.h"
#endif 
#define NUM_INT_MAX 8		//6 states + 1error + 1yscal (for adaptive rk)

#ifdef VSYS_OMP
#include<omp.h>
#endif

static std::string GetSysDir()
{

	
	#ifdef __gnu_linux__
		std::string sys_dir = "systems/";		
		std::string run_unix_cmd = "ls *.vmdl " + sys_dir + " > .syslist";		
	#elif defined __linux__
		std::string sys_dir = "systems/";
		std::string run_unix_cmd = "ls *.vmdl " + sys_dir + " > .syslist";		
	#elif defined __APPLE__ && __MACH__
		std::string sys_dir = "systems/";
		std::string run_unix_cmd = "ls *.vmdl " + sys_dir + " > .syslist";		
	#elif defined _WIN32
		std::string sys_dir = "systems\\";
		std::string run_win_cmd = "dir /b *.vmdl " + sys_dir + " > .syslist";
	#else 
		std::string sys_dir = "./";
		cout << "Other OS detected\n";
	#endif

	return sys_dir;
}


class VNNM_System
{
	protected:
	int Type;	//Parent or Child / Main System or Subsystem
	int Nparams;	//Number of Parameters to take in
	std::vector<int> dState;
	std::vector<double> Params;
	VNNM_System * Parent;			// Parent system (Parent systems will have NULL here)
	std::string sID;
	int cID;
	
	public:
	bool doIntegrate; 
	int Nstates;	//Number of States
	std::vector<double> State;
	std::vector<double> TempState[NUM_INT_MAX];
	std::vector<double> KTempState[NUM_INT_MAX];
	int SubSystemCount;			//Number of subsystems
	std::vector<VNNM_System*>SubSystems;		//Connected subsystems
	std::string Descript;	//Verbal description of system
	virtual std::string getSID()=0;
	virtual int getCID()=0;
	virtual int Info()=0;
	virtual int diff(double, double, const std::vector<double> &, std::vector<double> &, int)=0;
	virtual int operator()(double, double *,int)=0;	//t,State,dState
	virtual VNNM_System ** findSiblings(std::vector<std::string>)=0;
	virtual int SetParameters(std::vector<double>&)=0;
	virtual int SetParameter(int,double)=0;
	virtual int Init(std::string, std::vector<double>, VNNM_System * )=0;	
};

#endif
