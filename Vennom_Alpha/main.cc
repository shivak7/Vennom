#include "vsys_manager.h"
#include <iostream>

#ifdef __gnu_linux__
#include <sys/time.h>
#endif

#ifdef _WIN32
#include <Windows.h>
#endif

/*

WARNING: This code is a disaster. Consider rewriting. The findSiblings called by a sibling through a parent can be premature before other sibling channels are even defined
Due to this, unexpected behavior or crashes may occur. 

*/
using namespace std;

int main()
{

#ifdef _WIN32
	LARGE_INTEGER StartingTime, EndingTime, ElapsedMicroseconds;
	LARGE_INTEGER Frequency;

	QueryPerformanceFrequency(&Frequency);
	QueryPerformanceCounter(&StartingTime);
#elif defined __gnu_linux__
	struct timeval start, end;
	gettimeofday(&start, NULL);
#endif
	
	VNNM_Manager Prime;
#ifdef VSYS_OMP 
	int numCPU = omp_get_num_procs();
	std::cout << "Available cores (OpenMP): " << numCPU << std::endl;
#endif
	
//	Prime.Create_HHNeuron("ML_CTX",1);
//	Prime.Record_Config("single.rec");

	Prime.Build_Network("BG_CTX_loop.net");
	Prime.Record_Config("BG_CTX.rec");
//	Prime.Build_Network("small.net");
//	Prime.Record_Config("small0.rec");

//	Prime.Build_Network("test.net");
//	Prime.Record_Config("output.rec");

	Prime.Set_Timer(0.05, 6000);
	Prime.RunSystem();

#ifdef _WIN32
	QueryPerformanceCounter(&EndingTime);
	ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;
	ElapsedMicroseconds.QuadPart *= 1000000;
	ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;
	double delta = double(ElapsedMicroseconds.QuadPart)/1000000;
#elif defined __gnu_linux__
	gettimeofday(&end, NULL);
	double delta = ((end.tv_sec  - start.tv_sec) * 1000000u + 
    end.tv_usec - start.tv_usec) / 1.e6;
#endif

	  std::cout<<"Time taken : " << delta << std::endl;
	  
#ifdef _WIN32
	system("pause");
#endif // _WIN32

	return 0;
}
