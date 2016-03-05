#include <iostream>
#include <deque>
#include <random>
#include <algorithm>

struct process{
	unsigned int pid;
	unsigned int numcycles;
	unsigned int origCycles;//original number of cycles
};

struct results{
	results();
	unsigned int elapsedTime;
	int waitTime[50];
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
	int testcycles1[50];//mean 6000, SD 1000
	int testcycles2[50];//mean 6000, SD 4000
	int testcycles3[50];//mean 3000, SD 6000
	int testcycles4[50];//constant values 3000
	ps();
	results runFIFO(int *tcycles);//done
	results runFIFOmult(int *tcycles);//done
	results runRR(int *tcycles);//done
	results runRRmult(int *tcycles);//done
	results runSRT(int *tcycles);
	results runSRTmult(int *tcycles);
	results runSJF(int *tcycles);
	results runSJFmult(int *tcycles);
	results runLRT(int *tcycles);
	results runLRTmult(int *tcycles);
	void testFIFO(int *testcycles);
	void testRR(int *testcycles);
	void testSJF(int *testcycles);
	void testSRT(int *testcycles);
	void testLRT(int *testcycles);	
	void tests(int *testcycles);
	void testAll();
	void printResults(int *testcycles, results R);
};

bool compareMin(const process &a, const process &b);
bool compareMax(const process &a, const process &b);
void genNums(int *arr, int mean, int deviation);
void printArray(int *arr);
