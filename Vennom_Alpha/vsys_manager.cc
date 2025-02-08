#include "vsys_manager.h"
#include "algo_utils.h"
#include <fstream>
#include <iostream>
#include <string>
#include <iterator>
#include <sstream>

static std::string DumpSystemsToFile()
{

	
	#ifdef __gnu_linux__
		std::string sys_dir = "systems/";		
		std::string run_unix_cmd = "ls " + sys_dir + " > .syslist";		
		system(run_unix_cmd.c_str());
	#elif defined __linux__
		std::string sys_dir = "systems/";
		std::string run_unix_cmd = "ls " + sys_dir + " > .syslist";		
		system(run_unix_cmd.c_str());
	#elif defined __APPLE__ && __MACH__
		std::string sys_dir = "systems/";
		std::string run_unix_cmd = "ls " + sys_dir + " > .syslist";		
		system(run_unix_cmd.c_str());
	#elif defined _WIN32
		std::string sys_dir = "systems\\";
		std::string run_win_cmd = "dir /b " + sys_dir + " > .syslist";
		system(run_win_cmd.c_str());
	#else 
		std::string sys_dir = "./";
		cout << "Other OS detected\n";
	#endif

	return sys_dir;
}


VNNM_Manager :: VNNM_Manager()
{
	nsys = 0;
	usys = 0;
	t=0;
	dt=0.01;
	Max_Time = 1;
	RecordFlag = false;
	std::string sys_dir = DumpSystemsToFile();
	

	std::fstream f(".syslist",std::ios::in);
	std::vector<std::string> sys_files;
	if(!f.fail())
	{
		while(!f.eof())
		{
			std::string fn;
			f >> fn;
			if(!f.eof())
			   if((fn!="Parameters")&&(fn!="parameters")&&(fn!="Params")&&(fn!="params"))
				{
					//std::cout << fn << std::endl;
					sys_files.push_back(fn);
				}
		}
	}
	f.close();
	
	
	Solver.RK4init(4);	//HAVE TO CHANGE!!!
	
	for(int i=0;i<sys_files.size();i++)
	{
		std::string fn_path = sys_dir + sys_files[i]; 
		std::fstream g(fn_path.c_str(),std::ios::in);
		//std::cout << "Loading " << fn_path << " ..." << std::endl; 
		std::string str_id;
		g >> str_id;

		int cl_id=0;
		g >> cl_id;
		
		fID.insert(std::pair<int,std::string>(nsys,fn_path));
		csID.insert(std::pair<int,int>(nsys,cl_id));
		sID.insert(std::pair<std::string,int>(str_id,nsys++));
	
		g.close();
	}

}

VNNM_Manager :: ~VNNM_Manager()
{
	for(int i=0;i<usys;i++)
	  for(int j=0;j<Main_Sys[i].size();j++)
		delete Main_Sys[i][j];
}


int VNNM_Manager :: CheckAndAdd(int ClassID, VNNM_System * vptr)
{
	// Check if classID exists in map, if not add .
	// Then update Main_sys accordingly
	std::map<int,int>::iterator it;
	it = uList.find(ClassID);
	
	if(it!=uList.end())
	{
		Main_Sys[it->second].push_back(vptr);
		All_Sys.push_back(vptr);
	}
	else
	{
		uList.insert(std::pair<int,int>(ClassID,usys));
		Main_Sys[usys++].push_back(vptr);
		All_Sys.push_back(vptr);
	}	

	return 0;
}

int VNNM_Manager :: Create_Synapse(std::string Nname, int from, int to, double gsyn)
{
	std::map<std::string,int>::iterator it;
	it = sID.find(Nname);	
	
	int max_n = (from>=to)?from:to; 	//find the max index
	if ((max_n+1) > Main_Sys[0].size())	// This constrains network to a single neuron class
	{
		std::cout << "Synapse connection request beyond Network size.\n";
		exit(-1); 
	}
	
	if(it!=sID.end())	//If synapse type exists
	{
		int Nref = it->second;
		std::string fname = fID.find(Nref)->second;
		std::fstream f(fname.c_str(),std::ios::in);

		std::vector<double> A;	
		
		std::string nid;
		int cid;
		
		f >> nid >> cid;
		
		VNNM_System * ptr;
		
		switch(cid)
		{
			case DT_SYNAPSE:
			{
				VNNM_synapse_system * s_ptr = new VNNM_synapse_system;
				s_ptr->Init(fname,A,Main_Sys[0][to]);		//Connect to post-synaptic neuron
				s_ptr->connectFrom(Main_Sys[0][from]);		//Connect to pre-synaptic neuron
				s_ptr->SetParameter(0,gsyn);			//Assign synaptic strength
				ptr = s_ptr;
				break;
			}
			default: std::cout << "Mismatched synapse class id: " << cid << "\n"; exit(-1);
		}
		
		CheckAndAdd(cid, ptr);
		
	}
	else
	{
		std::cout << "Cannot find synapse system: " << Nname << std::endl; 
		exit(-1);	
	
	}
	
	return 0;
}

int VNNM_Manager :: Create_HHNeuron(std::string Nname, int Nnumber)
{

	std::map<std::string,int>::iterator it;
	it = sID.find(Nname);	
	
	if(it!=sID.end())	//If neuron type exists
	{
		int Nref = it->second;
		
		std::string fname = fID.find(Nref)->second;
		
		std::fstream f(fname.c_str(),std::ios::in);
		
		std::string nid;
		int cid;
		int nIntegrate;
		int tStates;
		int tSubSystemCount;
		
		f >> nid >> cid;
		f >> nIntegrate;
		f >> tStates;
		
		f >> tSubSystemCount;
		
		std::vector<std::string> parts;
		
		for(int i=0;i<tSubSystemCount;i++)
		{
			std::string dummy;
			f >> dummy;
			parts.push_back(dummy);
		}
		
		
		for(int i=0;i<Nnumber;i++)
		{
			VNNM_System * ptr = new VNNM_HHcell_system;
			CheckAndAdd(cid, ptr);
			ptr->SubSystemCount = tSubSystemCount;
			ptr->SubSystems.resize(tSubSystemCount);
			//ptr->SubSystems = new VNNM_System * [tSubSystemCount];
			std::vector<double> A;
			
			for(int j=0;j<tSubSystemCount;j++)
			{
				std::cout << "Connecting: " << parts[j] << std::endl;
				it = sID.find(parts[j]);
				if(it==sID.end()) 
				{
					std::cout << "Cannot find subsystem: " << parts[j] << std::endl; 
					exit(-1);	
				}
				
				int sys_no = it->second;	//Get system number
				std::string fpath = fID.find(sys_no)->second;	// Get file for system
				int subclass_id = csID.find(sys_no)->second;	//Get class for system

				switch(subclass_id)	// Initialize subsystem with relevant derived class datatype
				{
					case VSYS_RC_IONS: ptr->SubSystems[j] = new VNNM_ions_system; break;
					case VSYS_STATE_IONS: ptr->SubSystems[j] = new VNNM_ions_system2; break;
					case VSYS_DT_CaT: ptr->SubSystems[j] = new VNNM_ions_DT_CaT; break;
					case VSYS_DT_sAHP: ptr->SubSystems[j] = new VNNM_ions_DT_sAHP; break;
					case VSYS_CUSTOM: ptr->SubSystems[j] = new VNNM_custom; break;
					case VSYS_REDUCED: ptr->SubSystems[j] = new VNNM_ions_reduced; break;
					default: std::cout << "Unknown subsystem id:" << subclass_id << std::endl; exit(-1);
				}

			}

			for (int j = 0; j < tSubSystemCount; j++)
			{
				it = sID.find(parts[j]);
				if (it == sID.end())
				{
					std::cout << "Cannot find subsystem: " << parts[j] << std::endl;
					exit(-1);
				}

				int sys_no = it->second;	//Get system number
				std::string fpath = fID.find(sys_no)->second;	// Get file for system
				int subclass_id = csID.find(sys_no)->second;	//Get class for system

				int scid = ptr->SubSystems[j]->Init(fpath, A, ptr);	// Initialize Neuron's subsystems

				//if (subclass_id == VSYS_REDUCED)
				//	std::cout << "Got here...\n";
				//std::cout << "SCID: " << scid << std::endl;
				//if(scid==5)
				//	ptr->SubSystems[j]->Info();

				CheckAndAdd(scid, ptr->SubSystems[j]);
			}
			
			std::cout << "\nDebugging 2!...\n\n";
			ptr->Init(fname,A,NULL);	//Initialize Neuron
			
		
		}
		f.close();
	}
	else
	{
		std::cout << "Cannot find neuron system: " << Nname << std::endl; 
		exit(-1);
	}
	return 0;
}				


int VNNM_Manager :: Build_Network(std::string netfile)
{
	
	std::fstream f(netfile.c_str(),std::ios::in);
	std::string nid;
	int cid;
	std::vector<std::string> SynapseList;
	std::vector<int> cumsumNeuron;  
	std::string ConnMatFile;	//Connectivity matrix file
	int Neuron_Types = 0;
	int SumNeuron = 0;
	
	f >> nid >> cid >> Neuron_Types;
	
	for(int i=0;i<Neuron_Types;i++)
	{
		std::string syn;
		f >> syn;
		SynapseList.push_back(syn);
	}

	//std::cout << "\nDebugging!...\n\n";
	std::cout << "\nNeuron types: " << Neuron_Types << "...\n\n";

	for(int i=0;i<Neuron_Types;i++)
	{
		std::string neu;
		int count;
		f >> neu >> count;
		SumNeuron+=count;
		cumsumNeuron.push_back(SumNeuron);
		Create_HHNeuron(neu,count);	//Create 'count' number of 'neu' neurons 
		
	}
	std::cout << "\nReached!...\n\n";

	f >> ConnMatFile;
	f.close();
	std::fstream g(ConnMatFile.c_str(),std::ios::in);
	std::vector<double> ConnMat;
	while(!g.eof())
	{
		double d;
		g >> d;
		if(!g.eof())
			ConnMat.push_back(d);
	}
	g.close();
	if(ConnMat.size()==SumNeuron*SumNeuron)
		std::cout << "Connectivity matrix size verified. \n";
	
	/* Build synaptic connectivity now */
	
	
	for(int i=0;i<ConnMat.size();i++)
	{
		if(ConnMat[i]>0)	//connection exists
		{
			int from = i/SumNeuron;
			int to = i%SumNeuron; 
			bool chkFlag = true;
			for(int j=0;((j<cumsumNeuron.size())&&(chkFlag==true));j++)
			{
				if(from<cumsumNeuron[j])
				{
					Create_Synapse(SynapseList[j], from, to, ConnMat[i]);
					std::cout << "Connecting from: " << from << "\t to \t" << to << '\t' << SynapseList[j] << std::endl; 
					chkFlag = false;	//found from type, stop checking anymore
				}
			}
		}
		
	}
	
	
	
	return 0;
}

int VNNM_Manager :: FindClassID(std::string search)
{
	std::map<std::string,int>::iterator it;
	it = sID.find(search);
		
	if(it==sID.end()) 
	{
		std::cout << "Cannot identify system for recording: " << search << std::endl; 
		exit(-1);	
	}
		
	int sys_no = it->second;	//Get system number
	int subclass_id = csID.find(sys_no)->second;	//Get class for system
	return subclass_id;

}

int VNNM_Manager :: Record_Config(std::string cfgfile)
{

	RecordFlag = true;
	
	std::fstream f(cfgfile.c_str(),std::ios::in);
	
	std::string thisLine;
	
	f >> thisLine;
	TRecStates = 0;
	
	if(thisLine=="VNNM_RECORD")
	{
		f >> outFile;	//Store filename for output
		std::cout << "Valid signature for output record configuration.\n";
		
		 	std::vector<std::string> Linetokens;
    			while (!f.eof()) 
    			{
    				std::string item;
    				if(std::getline(f,item))
        				Linetokens.push_back(item);
        		}	
			f.close();        		
        		Linetokens.erase(Linetokens.begin());
        	
        	for(int i=0;i<Linetokens.size();i++)
        	{
        		int tokenCount = 0;
        		
        		std::cout << i+1 << ".)" << Linetokens[i] << std::endl;
        		std::stringstream ss;
        		ss << Linetokens[i];
        		std::vector<std::string> Tokens;
        		std::string split;
        		while(getline(ss,split,' '))
        			Tokens.push_back(split);

			int subclass_id = FindClassID(Tokens[tokenCount]);
			
			RecordSystem tSys;	//Temporary record system variable.
			tSys.sID = Tokens[tokenCount++];
			tSys.cID = subclass_id;
			
			if(Tokens[tokenCount]=="SYSTEM")
			{
			  tSys.isState = false;
			  tokenCount++;
			}
			else if (Tokens[tokenCount]=="STATE")
			{  
				tSys.isState = true;
				tokenCount++;
				tSys.state_number = atoi(Tokens[tokenCount++].c_str());
			}
			else
			{ std:: cout << Tokens[tokenCount] << "\t is neither \"STATE\" nor \"SYSTEM\" record! \n"; exit(-1);}
			
        		
        	for(int j=0;j<usys;j++)		//Hunt down correct class
        		 if(Main_Sys[j][0]->getCID()==tSys.cID)
        		 	{tSys.cID_idx = j; break;}
        		 	
        	if(Tokens[tokenCount]=="ALL")
			  for(int j = 0; j < Main_Sys[tSys.cID_idx].size();j++)	//Traverse down the correct Main_sys vector
			  {
			  	if(tSys.sID==Main_Sys[tSys.cID_idx][j]->getSID()) //If correct match,
			  		tSys.msys_idx.push_back(j);
			  }
			else
			{
				int ncount = 0;			//count the number of rec systems/states
				std::vector<int> sys_num;
				while(tokenCount<Tokens.size())		// Extract remaining system indices in current line 
					sys_num.push_back(atoi(Tokens[tokenCount++].c_str()));
				
				for(int j = 0; j < Main_Sys[tSys.cID_idx].size();j++)	//Traverse down the correct Main_sys vector
			  	{
			  		if(tSys.sID==Main_Sys[tSys.cID_idx][j]->getSID()) //If correct match,
			  		{
			  		   ncount++;
			  		   for(int k=0;k<sys_num.size();k++)
			  		   {
			  		   	if(sys_num[k]==ncount-1)
			  				{tSys.msys_idx.push_back(j); break;}
			  		   }
			  		}
			  	}	
			
			}
			
			TRecStates += tSys.msys_idx.size();
        		sysRec.push_back(tSys);
        	}
	}
	
	f.close();	
	return 0;	
}

int VNNM_Manager :: Set_Timer(double step, double T)
{
	dt = step;
	Max_Time = T;
	return 0;
}

int VNNM_Manager :: Record_Network()
{

	sysOut.push_back(t);	//First store time
	for(int i=0;i<sysRec.size();i++)
	{
		for(int j=0; j<sysRec[i].msys_idx.size();j++)
		{
			int x = sysRec[i].cID_idx;
			int y = sysRec[i].msys_idx[j];
			int sn = sysRec[i].state_number;
			if(sysRec[i].isState)
			{
				if(sn < Main_Sys[x][y]->Nstates)
					sysOut.push_back(Main_Sys[x][y]->State[sn]);
				else
				{
					std::cout << "Requested state value greater than available for: " << Main_Sys[x][y]->getSID();	exit(-1);
				}
			}
			else
			{
				double V=0;
				(*Main_Sys[x][y])(t,&V,0);
				sysOut.push_back(V);
			}	
		}
	}

	return 0;
}

int VNNM_Manager :: Format_Output(std::vector<double> &Out, int columns)
{
	std::fstream f(outFile.c_str(),std::ios::out);
	int count = 0;
	
	for(int i=0;i<(Out.size()/(columns));i++)
	{
		for(int j=0;j<columns;j++)
		{
			f << Out[j + (columns)*i] << '\t';		
		}
		f << std::endl;
	}
	
	f.close();
	return 0;
}

int VNNM_Manager :: RunAdaptive()
{

	double dt_min = 0.0;
	long int Tsize = Max_Time/dt;
	std::vector<int> reg_idx;			//Array Index needed for regularization of adaptive output
	reg_idx.reserve(Tsize + 1);
	double t_thresh = dt;
	int nstp = 0;
	reg_idx.push_back(nstp);
	while(t<Max_Time)
	{
		if(RecordFlag)
			Record_Network();
			
		Solver.RKAdaptive(All_Sys,t, dt, 0, Max_Time, dt_min);
		
		if(t>=t_thresh)
		{
			reg_idx.push_back(nstp+1);
			t_thresh+=dt;
		}
		nstp++;
	}
	
	if(RecordFlag)
		Record_Network();
	
	//reg_idx.push_back(nstp);
	
	if(RecordFlag)
	{
		std::vector <double> Derivs;
		SplineDeriv(sysOut, Derivs, TRecStates+1);
		Spline(sysOut, Derivs, reg_idx, sysOut2, TRecStates+1, dt);
	}
	if(RecordFlag)
		Format_Output(sysOut2,TRecStates+1);	
	
	//for(int i=0;i<reg_idx.size();i++)
	//	std::cout << sysOut[0 + (TRecStates+1)*reg_idx[i]] << '\t' << reg_idx[i] << std::endl;
	
	return 0;
}

/*
int VNNM_Manager :: RegularizeOutput()
{
	for(int i=0;i<sysRec.size();i++)
		Tstates+=sysRec[i].msys_idx.size();
	
	

}
*/
int VNNM_Manager :: RunSystem()
{

	long int Tsize = Max_Time/dt;
	long int Tstates = 0;
	for(int i=0;i<sysRec.size();i++)
		Tstates+=sysRec[i].msys_idx.size();
		
	sysOut.reserve((Tstates+1)*(Tsize+1));
	sysOut2.reserve((Tstates+1)*(Tsize+1));
	
	RunAdaptive();
		
//	while(t<Max_Time)
//	{
////	
////		
//		if(RecordFlag)
//			Record_Network();
////		//Solver.EulerIntegrate(All_Sys,t,dt);
//		Solver.RK4Integrate(All_Sys,t,dt);
//////		Solver.Update(All_Sys);
//////		t+=dt;
//	}

//	if(RecordFlag)
//		Format_Output(sysOut,TRecStates+1);	

	return 0;
}
