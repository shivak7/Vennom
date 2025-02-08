#include "vsys_ions.h"
#include "vsys_ions2.h"
#include "vsys_ions_DT_CaT.h"
#include "vsys_hh_cell.h"
#include "vsys_ions_DT_sAHP.h"
#include "vsys_synapse.h"
#include "vsys_ions_reduced.h"
#include "vsys_custom.h"
#include "num_int.h"
#include <vector>
#include <string>
#include <map>
#include <cstdlib>

class RecordSystem
{
	public:
	std::string sID;
	int cID;
	int cID_idx;	//cID mainsys index
	std::vector<int> msys_idx; //Mainsys index vector
	bool isState;	//True = state, false = system.
	int state_number; //If a state, choose state number
};

class VNNM_Manager
{
	double Max_Time;
	double dt;
	double t;
	std::vector<double> TempState;		//Temporary state after integration
	std::vector<VNNM_System *> All_Sys;	//All systems lined up for easy integration
	std::vector<VNNM_System *> Main_Sys[100];		//Main VENNOM system database of all objects (Max 100 varieties)
	std::map<std::string,int> sID;		//String IDs
	std::map<int, std::string> fID;		//File path IDs
	std::map<int, int> uList;		//Unique Sys list
	std::map<int, int> csID;		//ClassIDs for all systems
	std::vector< std::vector<int> > RecordList;
	int usys;				//Number of unique system types
	VNNM_Integrate Solver;			
	std::vector<RecordSystem> sysRec;	//Record systems or states
	bool RecordFlag;
	public:
	int nsys;				//Number of systems
	int TRecStates;				//Total number of recorded states
	std::vector <double> sysOut;		//Output vector
	std::vector <double> sysOut2;		//Output vector2
	std::string outFile;			//output filename
	VNNM_Manager();
	~VNNM_Manager();
	int Set_Timer(double dt, double T);
	int FindClassID(std::string);
	int Build_Network(std::string);
	int Record_Config(std::string);
	int Record_Network();
	int Format_Output(std::vector<double>&,int);
	int Create_Synapse(std::string, int,int, double);
	int Create_HHNeuron(std::string, int);
	int CheckAndAdd(int, VNNM_System *);
	int RunSystem();
	int RunAdaptive();
};


