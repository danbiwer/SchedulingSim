#include <iostream>
#include <deque>
#include <random>
#include <algorithm>

struct process{
	unsigned int pid;
	unsigned int numcycles;
	unsigned int origCycles;//original number of cycles
};

struct processhandler{
	unsigned int currentPID;
	unsigned int maxCycles;
	unsigned int maxMem;
	unsigned int totalCycles;
	unsigned int totalMem;
	std::deque<process> processes;
	processhandler();
	void addProcess(unsigned int n);
	void printProcesses();
	void printAverage();
	process *findMin();
};

struct ps{
	unsigned int runFIFO();//done
	unsigned int runFIFOmult();//done
	unsigned int runRR();//done
	unsigned int runRRmult();//done
	unsigned int runSRT();
	unsigned int runSRTmult();
	unsigned int runSJF();
	unsigned int runSJFmult();
	unsigned int runLRT();
	unsigned int runLRTmult();
};

bool compareMin(const process &a, const process &b);
bool compareMax(const process &a, const process &b);