#ifndef _VSYS_CUSTOM
#define _VSYS_CUSTOM

#include <vector>
#include "vsys.h"

#ifdef __gnu_linux__
#include <dlfcn.h>
#elif defined _WIN32
#include <Windows.h>
#include <tchar.h>
typedef int(__cdecl *MYPROC)(LPWSTR);

std::wstring static s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

#endif

#define VSYS_CUSTOM 100

/*


	dX/dt = phi_X [(X_inf(V) - X)/tau_X(V)]
	
	X_inf(V) = 1/{1 + exp[-(V-theta_X)/sigma_X]} - K OR optional 1/[1 + exp(-theta_X/sigma_X)]
	
	tau_X(V) = theta_0X + theta1X/{1 + exp[-(V-theta_t_X)/sigma_t_X]}


*/
typedef int (*DFPTR) (int, double, double, const std::vector<double> & Params, const std::vector<double> & curr_state, std::vector<double> & diff_state, std::vector<int> & dstate, int Order, VNNM_System *);

typedef int (*AFPTR) (int, double, double *, const std::vector<double> & Params, const std::vector<double> & curr_state, std::vector<int> & dstate, int Order, VNNM_System *);

class VNNM_custom : public VNNM_System
{
	protected:
	int dum;
	public:
#ifdef _WIN32
	HINSTANCE hinstLib;
	~VNNM_custom(){FreeLibrary(hinstLib);}
#else
	void *lib_handle;
	~VNNM_custom(){dlclose(lib_handle);}
#endif
	VNNM_custom(){Parent=NULL;}			//Default Constructor 
	int Init(std::string,std::vector<double>, VNNM_System * );			// Alternative Initializer
	std::string getSID(){return sID;}
	int getCID(){return cID;}
	int Info() { return 0;}
	int SetParameters(std::vector<double>&);
	int SetParameter(int,double);
	VNNM_System ** findSiblings(std::vector<std::string>){ return NULL; };
	int diff(double, double, const std::vector<double> & curr_state, std::vector<double> & diff_state, int Order);
	int operator()(double, double *,int Order);
	
	DFPTR diff_fn;
	AFPTR main_fn;

};

#endif
