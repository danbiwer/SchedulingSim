#include "ps.h"

bool compareMin(const process &a, const process &b){
	return a.numcycles < b.numcycles;
}

bool compareMax(const process &a, const process &b){
	return a.numcycles > b.numcycles;
}

void printArray(int *arr){
	for(int i=0; i<50; i++)
		std::cout << "p" << i << ": " << arr[i] << std::endl;
}


void genNums(int *arr, int mean, int deviation){//fills array "arr" with random numbers using normal distribution
	std::default_random_engine generator;
	std::normal_distribution<double> distribution(mean,deviation);
	for(int i=0;i<50;i++){
		while(1){
			if(((arr[i] = distribution(generator)) > 0) && arr[i] < 11000)//make sure generated number is positive
				break;
		}
	}

}

results::results(){
	for(int i=0;i<50;i++)
		waitTime[i] = 0;
}

processhandler::processhandler(){
	currentPID = 0;
	maxCycles = 11000;
	maxMem = 100;
	totalMem = 0;
	totalCycles = 0;
}

void processhandler::addProcess(unsigned int n){
	process newProcess;
	newProcess.pid = currentPID;
	unsigned int newCycles = n;
	if(newCycles > maxCycles)//if newCycles is too large, scale it back to maxCycles
		newCycles = maxCycles;
	totalCycles += newCycles;
	newProcess.numcycles = newCycles;
	newProcess.origCycles = newCycles;
	processes.push_back (newProcess);
	currentPID++;

}



void processhandler::printProcesses(){
	for(int i=0; i < processes.size(); i++){
		std::cout << "Process " << i << "- " << std::endl;
		std::cout << "\tPID: " << processes[i].pid;
		std::cout << "\tCycles: " << processes[i].numcycles << std::endl;
	}

}

void processhandler::printAverage(){//print average cycles and memory
	float averageCycles = totalCycles/currentPID;
	float averageMem = totalMem/currentPID;
	std::cout << "Mean Cycles: " << averageCycles << std::endl;
	std::cout << "Mean Memory: " << averageMem << std::endl;
}


ps::ps(){
	genNums(testcycles1,6000,1000);
	genNums(testcycles2,6000,4000);
	genNums(testcycles3,3000,6000);
	for(int i = 0; i<50;i++){
		testcycles4[i] = 3000;
	}
}

results ps::runFIFO(int *tcycles){
	
	processhandler PH;
	results R;
	unsigned int elapsedTime = 0;
	unsigned int numProcesses = 0;
	unsigned int penalty = 0;
	unsigned int pLeft = 50;
	process *p1 = NULL;
	
	while(pLeft>0){
		if(((elapsedTime % 50) == 0) && (numProcesses < 50)){
			PH.addProcess(tcycles[numProcesses]);
			numProcesses++;
		}


		if((!PH.processes.empty()) && (!p1)){
			penalty+=10;
			p1 = new process;
			*p1 = PH.processes.front();
			PH.processes.pop_front();
		}



		if(p1){
			p1->numcycles--;
			if(p1->numcycles==0){
				pLeft--;
				p1 = NULL;
			}
		}

		for(int i=0; i<PH.processes.size(); i++){//update all wait times that are in waiting queue
			R.waitTime[PH.processes[i].pid]++;
		}
		elapsedTime++;
	}
	elapsedTime+=penalty;
	R.elapsedTime = elapsedTime;
	if(p1) delete p1;

	return R;
	
}


results ps::runFIFOmult(int *tcycles){
	
	processhandler PH;
	results R;
	unsigned int elapsedTime = 0;
	unsigned int numProcesses = 0;
	unsigned int penalty = 0;
	unsigned int pLeft = 50;
	process *p1 = NULL;
	process *p2 = NULL;
	process *p3 = NULL;
	process *p4 = NULL;
	
	while(pLeft>0){
		if(((elapsedTime % 50) == 0) && (numProcesses < 50)){
			PH.addProcess(tcycles[numProcesses]);
			numProcesses++;
		}

		if((!PH.processes.empty()) && (!p1)){
			penalty+=10;
			p1 = new process;
			*p1 = PH.processes.front();
			PH.processes.pop_front();
		}

		if((!PH.processes.empty()) && (!p2)){
			penalty+=10;
			p2 = new process;
			*p2 = PH.processes.front();
			PH.processes.pop_front();
		}

		if((!PH.processes.empty()) && (!p3)){
			penalty+=10;
			p3 = new process;
			*p3 = PH.processes.front();
			PH.processes.pop_front();
		}

		if((!PH.processes.empty()) && (!p4)){
			penalty+=10;
			p4 = new process;
			*p4 = PH.processes.front();
			PH.processes.pop_front();
		}

		if(p1){
			p1->numcycles--;
			if(p1->numcycles==0){
				pLeft--;
				p1 = NULL;
			}
		}

		if(p2){
			p2->numcycles--;
			if(p2->numcycles==0){
				pLeft--;
				p2 = NULL;
			}
		}

		if(p3){
			p3->numcycles--;
			if(p3->numcycles==0){
				pLeft--;
				p3 = NULL;
			}
		}

		if(p4){
			p4->numcycles--;
			if(p4->numcycles==0){
				pLeft--;
				p4 = NULL;
			}
		}
		for(int i=0; i<PH.processes.size(); i++){//update all wait times that are in waiting queue
			R.waitTime[PH.processes[i].pid]++;
		}
		elapsedTime++;
	}
	elapsedTime+=penalty;
	R.elapsedTime = elapsedTime;
	if(p1) delete p1;
	if(p2) delete p1;
	if(p3) delete p1;
	if(p4) delete p1;
	return R;
}

results ps::runRR(int *tcycles){
	
	processhandler PH;
	results R;
	unsigned int elapsedTime = 0;
	unsigned int numProcesses = 0;
	unsigned int penalty = 0;
	unsigned int pLeft = 50;
	process *p1 = NULL;
	
	while(pLeft>0){

		if(((elapsedTime % 50) == 0) && (numProcesses < 50)){
			PH.addProcess(tcycles[numProcesses]);
			numProcesses++;
		}

		if((!PH.processes.empty()) && (!p1)){
			penalty+=10;
			p1 = new process;
			*p1 = PH.processes.front();
			PH.processes.pop_front();
		}


		if(p1){
			p1->numcycles--;
			if(p1->numcycles==0){
				pLeft--;
				p1 = NULL;
			}
			else if(((p1->origCycles - p1->numcycles) % 50) == 0){
				PH.processes.push_back(*p1);
				p1 = NULL;
			}
		}


		for(int i=0; i<PH.processes.size(); i++){//update all wait times that are in waiting queue
			R.waitTime[PH.processes[i].pid]++;
		}
		elapsedTime++;
	}
	elapsedTime+=penalty;
	R.elapsedTime = elapsedTime;
	if(p1) delete p1;
	//PH.printProcesses();
	return R;
}


results ps::runRRmult(int *tcycles){
	
	processhandler PH;
	results R;
	unsigned int elapsedTime = 0;
	unsigned int numProcesses = 0;
	unsigned int penalty = 0;
	unsigned int pLeft = 50;
	process *p1 = NULL;
	process *p2 = NULL;
	process *p3 = NULL;
	process *p4 = NULL;
	
	while(pLeft>0){

		if(((elapsedTime % 50) == 0) && (numProcesses < 50)){
			PH.addProcess(tcycles[numProcesses]);
			numProcesses++;
		}

		if((!PH.processes.empty()) && (!p1)){
			penalty+=10;
			p1 = new process;
			*p1 = PH.processes.front();
			PH.processes.pop_front();
		}

		if((!PH.processes.empty()) && (!p2)){
			penalty+=10;
			p2 = new process;
			*p2 = PH.processes.front();
			PH.processes.pop_front();
		}

		if((!PH.processes.empty()) && (!p3)){
			penalty+=10;
			p3 = new process;
			*p3 = PH.processes.front();
			PH.processes.pop_front();
		}

		if((!PH.processes.empty()) && (!p4)){
			penalty+=10;
			p4 = new process;
			*p4 = PH.processes.front();
			PH.processes.pop_front();
		}

		if(p1){
			p1->numcycles--;
			if(p1->numcycles==0){
				pLeft--;
				p1 = NULL;
			}
			else if(((p1->origCycles - p1->numcycles) % 50) == 0){
				PH.processes.push_back(*p1);
				p1 = NULL;
			}
		}

		if(p2){
			p2->numcycles--;
			if(p2->numcycles==0){
				pLeft--;
				p2 = NULL;
			}
			else if(((p2->origCycles - p2->numcycles) % 50) == 0){
				PH.processes.push_back(*p2);
				p2 = NULL;
			}
		}

		if(p3){
			p3->numcycles--;
			if(p3->numcycles==0){
				pLeft--;
				p3 = NULL;
			}
			else if(((p3->origCycles - p3->numcycles) % 50) == 0){
				PH.processes.push_back(*p3);
				p3 = NULL;
			}
		}

		if(p4){
			p4->numcycles--;
			if(p4->numcycles==0){
				pLeft--;
				p4 = NULL;
			}
			else if(((p4->origCycles - p4->numcycles) % 50) == 0){
				PH.processes.push_back(*p4);
				p4 = NULL;
			}
		}

		for(int i=0; i<PH.processes.size(); i++){//update all wait times that are in waiting queue
			R.waitTime[PH.processes[i].pid]++;
		}
		elapsedTime++;
	}
	elapsedTime+=penalty;
	R.elapsedTime = elapsedTime;
	if(p1) delete p1;
	if(p2) delete p2;
	if(p3) delete p3;
	if(p4) delete p4;
	//PH.printProcesses();
	return R;
}


results ps::runSJF(int *tcycles){
	
	processhandler PH;
	results R;
	unsigned int elapsedTime = 0;
	unsigned int numProcesses = 0;
	unsigned int penalty = 0;
	unsigned int pLeft = 50;
	process *p1 = NULL;
	std::sort(PH.processes.begin(), PH.processes.end(),compareMin);
	
	while(pLeft>0){

		if(((elapsedTime % 50) == 0) && (numProcesses < 50)){
			PH.addProcess(tcycles[numProcesses]);
			numProcesses++;
			std::sort(PH.processes.begin(), PH.processes.end(),compareMin);
		}

		if((!PH.processes.empty()) && (!p1)){
			penalty+=10;
			p1 = new process;
			*p1 = PH.processes.front();
			PH.processes.pop_front();
		}


		if(p1){
			p1->numcycles--;
			if(p1->numcycles==0){
				pLeft--;
				p1 = NULL;
			}
		}


		for(int i=0; i<PH.processes.size(); i++){//update all wait times that are in waiting queue
			R.waitTime[PH.processes[i].pid]++;
		}
		elapsedTime++;
	}
	elapsedTime+=penalty;
	R.elapsedTime = elapsedTime;
	if(p1) delete p1;
	return R;
}

results ps::runSJFmult(int *tcycles){
	
	processhandler PH;
	results R;
	unsigned int elapsedTime = 0;
	unsigned int numProcesses = 0;
	unsigned int penalty = 0;
	unsigned int pLeft = 50;
	process *p1 = NULL;
	process *p2 = NULL;
	process *p3 = NULL;
	process *p4 = NULL;
	std::sort(PH.processes.begin(), PH.processes.end(),compareMin);
	
	while(pLeft>0){

		if(((elapsedTime % 50) == 0) && (numProcesses < 50)){
			PH.addProcess(tcycles[numProcesses]);
			numProcesses++;
			std::sort(PH.processes.begin(), PH.processes.end(),compareMin);
		}

		if((!PH.processes.empty()) && (!p1)){
			penalty+=10;
			p1 = new process;
			*p1 = PH.processes.front();
			PH.processes.pop_front();
		}
		if((!PH.processes.empty()) && (!p2)){
			penalty+=10;
			p2 = new process;
			*p2 = PH.processes.front();
			PH.processes.pop_front();
		}
		if((!PH.processes.empty()) && (!p3)){
			penalty+=10;
			p3 = new process;
			*p3 = PH.processes.front();
			PH.processes.pop_front();
		}
		if((!PH.processes.empty()) && (!p4)){
			penalty+=10;
			p4 = new process;
			*p4 = PH.processes.front();
			PH.processes.pop_front();
		}


		if(p1){
			p1->numcycles--;
			if(p1->numcycles==0){
				pLeft--;
				p1 = NULL;
			}
		}

		if(p2){
			p2->numcycles--;
			if(p2->numcycles==0){
				pLeft--;
				p2 = NULL;
			}
		}

		if(p3){
			p3->numcycles--;
			if(p3->numcycles==0){
				pLeft--;
				p3 = NULL;
			}
		}
		
		if(p4){
			p4->numcycles--;
			if(p4->numcycles==0){
				pLeft--;
				p4 = NULL;
			}
		}


		for(int i=0; i<PH.processes.size(); i++){//update all wait times that are in waiting queue
			R.waitTime[PH.processes[i].pid]++;
		}
		elapsedTime++;
	}
	elapsedTime+=penalty;
	R.elapsedTime = elapsedTime;
	if(p1) delete p1;
	if(p2) delete p2;
	if(p3) delete p3;
	if(p4) delete p4;
	return R;
}



results ps::runSRT(int *tcycles){
	
	processhandler PH;
	results R;
	unsigned int elapsedTime = 0;
	unsigned int numProcesses = 0;
	unsigned int penalty = 0;
	unsigned int pLeft = 50;
	process *p1 = NULL;
	unsigned int p1Last = 0;
	std::sort(PH.processes.begin(), PH.processes.end(),compareMin);
	
	while(pLeft>0){

		if(((elapsedTime % 50) == 0) && (numProcesses < 50)){
			PH.addProcess(tcycles[numProcesses]);
			numProcesses++;
			if(p1){
				PH.processes.push_back(*p1);
				p1Last = p1->pid;
				p1 = NULL;
			}
			std::sort(PH.processes.begin(), PH.processes.end(),compareMin);
		}

		if((!PH.processes.empty()) && (!p1)){
			p1 = new process;
			*p1 = PH.processes.front();
			PH.processes.pop_front();
			if(p1Last != p1->pid){
				penalty+=10;
			}
		}


		if(p1){
			p1->numcycles--;
			if(p1->numcycles==0){
				pLeft--;
				p1 = NULL;
			}
		}

		for(int i=0; i<PH.processes.size(); i++){//update all wait times that are in waiting queue
			R.waitTime[PH.processes[i].pid]++;
		}

		elapsedTime++;
	}
	elapsedTime+=penalty;
	R.elapsedTime = elapsedTime;
	if(p1) delete p1;
	return R;
}

results ps::runSRTmult(int *tcycles){
	
	processhandler PH;
	results R;
	unsigned int elapsedTime = 0;
	unsigned int numProcesses = 0;
	unsigned int penalty = 0;
	unsigned int pLeft = 50;
	process *p1 = NULL;
	process *p2 = NULL;
	process *p3 = NULL;
	process *p4 = NULL;
	unsigned int p1Last = 0;
	unsigned int p2Last = 0;
	unsigned int p3Last = 0;
	unsigned int p4Last = 0;
	std::sort(PH.processes.begin(), PH.processes.end(),compareMin);
	
	while(pLeft>0){

		if(((elapsedTime % 50) == 0) && (numProcesses < 50)){
			PH.addProcess(tcycles[numProcesses]);
			numProcesses++;
			if(p1){
				PH.processes.push_back(*p1);
				p1Last = p1->pid;
				p1 = NULL;
			}
			if(p2){
				PH.processes.push_back(*p2);
				p2Last = p2->pid;
				p2 = NULL;
			}
			if(p3){
				PH.processes.push_back(*p3);
				p3Last = p3->pid;
				p3 = NULL;
			}
			if(p4){
				PH.processes.push_back(*p4);
				p4Last = p4->pid;
				p4 = NULL;
			}
			std::sort(PH.processes.begin(), PH.processes.end(),compareMin);
		}

		if((!PH.processes.empty()) && (!p1)){
			p1 = new process;
			*p1 = PH.processes.front();
			PH.processes.pop_front();
			if(p1Last != p1->pid){
				penalty+=10;
			}
		}

		if((!PH.processes.empty()) && (!p2)){
			p2 = new process;
			*p2 = PH.processes.front();
			PH.processes.pop_front();
			if(p2Last != p2->pid){
				penalty+=10;
			}
		}

		if((!PH.processes.empty()) && (!p3)){
			p3 = new process;
			*p3 = PH.processes.front();
			PH.processes.pop_front();
			if(p3Last != p3->pid){
				penalty+=10;
			}
		}

		if((!PH.processes.empty()) && (!p4)){
			p4 = new process;
			*p4 = PH.processes.front();
			PH.processes.pop_front();
			if(p4Last != p4->pid){
				penalty+=10;
			}
		}


		if(p1){
			p1->numcycles--;
			if(p1->numcycles==0){
				pLeft--;
				p1 = NULL;
			}
		}

		if(p2){
			p2->numcycles--;
			if(p2->numcycles==0){
				pLeft--;
				p2 = NULL;
			}
		}

		if(p3){
			p3->numcycles--;
			if(p3->numcycles==0){
				pLeft--;
				p3 = NULL;
			}
		}
		
		if(p4){
			p4->numcycles--;
			if(p4->numcycles==0){
				pLeft--;
				p4 = NULL;
			}
		}

		for(int i=0; i<PH.processes.size(); i++){//update all wait times that are in waiting queue
			R.waitTime[PH.processes[i].pid]++;
		}

		elapsedTime++;
	}
	elapsedTime+=penalty;
	if(p1) delete p1;
	if(p2) delete p2;
	if(p3) delete p3;
	if(p4) delete p4;
	return R;
}


results ps::runLRT(int *tcycles){
	
	processhandler PH;
	results R;
	unsigned int elapsedTime = 0;
	unsigned int numProcesses = 0;
	unsigned int penalty = 0;
	unsigned int pLeft = 50;
	process *p1 = NULL;
	unsigned int p1Last = 0;
	std::sort(PH.processes.begin(), PH.processes.end(),compareMin);
	
	while(pLeft>0){

		if(((elapsedTime % 50) == 0) && (numProcesses < 50)){
			PH.addProcess(tcycles[numProcesses]);
			numProcesses++;
		}

		if(p1){
				PH.processes.push_back(*p1);
				p1Last = p1->pid;
				p1 = NULL;
		}

		std::sort(PH.processes.begin(), PH.processes.end(),compareMax);

		if((!PH.processes.empty()) && (!p1)){
			p1 = new process;
			*p1 = PH.processes.front();
			PH.processes.pop_front();
			if(p1Last != p1->pid){
				penalty+=10;
			}
		}


		if(p1){
			p1->numcycles--;
			if(p1->numcycles==0){
				pLeft--;
				p1 = NULL;
			}
		}


		for(int i=0; i<PH.processes.size(); i++){//update all wait times that are in waiting queue
			R.waitTime[PH.processes[i].pid]++;
		}
		elapsedTime++;
	}
	elapsedTime+=penalty;
	R.elapsedTime = elapsedTime;
	if(p1) delete p1;
	return R;
}


results ps::runLRTmult(int *tcycles){
	
	processhandler PH;
	results R;
	unsigned int elapsedTime = 0;
	unsigned int numProcesses = 0;
	unsigned int penalty = 0;
	unsigned int pLeft = 50;
	process *p1 = NULL;
	process *p2 = NULL;
	process *p3 = NULL;
	process *p4 = NULL;
	unsigned int p1Last = 0;
	unsigned int p2Last = 0;
	unsigned int p3Last = 0;
	unsigned int p4Last = 0;
	std::sort(PH.processes.begin(), PH.processes.end(),compareMin);
	
	while(pLeft>0){

		if(((elapsedTime % 50) == 0) && (numProcesses < 50)){
			PH.addProcess(tcycles[numProcesses]);
			numProcesses++;
		}
		if(p1){
			PH.processes.push_back(*p1);
			p1Last = p1->pid;
			p1 = NULL;
		}
		if(p2){
			PH.processes.push_back(*p2);
			p2Last = p2->pid;
			p2 = NULL;
		}
		if(p3){
			PH.processes.push_back(*p3);
			p3Last = p3->pid;
			p3 = NULL;
		}
		if(p4){
			PH.processes.push_back(*p4);
			p4Last = p4->pid;
			p4 = NULL;
		}
		std::sort(PH.processes.begin(), PH.processes.end(),compareMax);

		if((!PH.processes.empty()) && (!p1)){
			p1 = new process;
			*p1 = PH.processes.front();
			PH.processes.pop_front();
			if(p1Last != p1->pid){
				penalty+=10;
			}
		}

		if((!PH.processes.empty()) && (!p2)){
			p2 = new process;
			*p2 = PH.processes.front();
			PH.processes.pop_front();
			if(p2Last != p2->pid){
				penalty+=10;
			}
		}

		if((!PH.processes.empty()) && (!p3)){
			p3 = new process;
			*p3 = PH.processes.front();
			PH.processes.pop_front();
			if(p3Last != p3->pid){
				penalty+=10;
			}
		}

		if((!PH.processes.empty()) && (!p4)){
			p4 = new process;
			*p4 = PH.processes.front();
			PH.processes.pop_front();
			if(p4Last != p4->pid){
				penalty+=10;
			}
		}


		if(p1){
			p1->numcycles--;
			if(p1->numcycles==0){
				pLeft--;
				p1 = NULL;
			}
		}

		if(p2){
			p2->numcycles--;
			if(p2->numcycles==0){
				pLeft--;
				p2 = NULL;
			}
		}

		if(p3){
			p3->numcycles--;
			if(p3->numcycles==0){
				pLeft--;
				p3 = NULL;
			}
		}
		
		if(p4){
			p4->numcycles--;
			if(p4->numcycles==0){
				pLeft--;
				p4 = NULL;
			}
		}

		for(int i=0; i<PH.processes.size(); i++){//update all wait times that are in waiting queue
			R.waitTime[PH.processes[i].pid]++;
		}

		elapsedTime++;
	}
	elapsedTime+=penalty;
	R.elapsedTime = elapsedTime;
	if(p1) delete p1;
	if(p2) delete p2;
	if(p3) delete p3;
	if(p4) delete p4;
	return R;

}

void ps::testFIFO(int *testcycles){
	std::cout << "FIFO (1 PROCESSOR)" << std::endl;
	printResults(testcycles,runFIFO(testcycles));
	std::cout << std::endl;
	std::cout << "FIFO (4 PROCESSORS)" << std::endl;
	printResults(testcycles,runFIFOmult(testcycles));
	std::cout << std::endl;
}

void ps::testRR(int *testcycles){
	std::cout << "RR (1 PROCESSOR)" << std::endl;
	printResults(testcycles,runRR(testcycles));
	std::cout << std::endl;
	std::cout << "RR (4 PROCESSORS)" << std::endl;
	printResults(testcycles,runRRmult(testcycles));
	std::cout << std::endl;
}

void ps::testSRT(int *testcycles){
	std::cout << "SRT (1 PROCESSOR)" << std::endl;
	printResults(testcycles,runSRT(testcycles));
	std::cout << std::endl;
	std::cout << "SRT (4 PROCESSORS)" << std::endl;
	printResults(testcycles,runSRTmult(testcycles));
	std::cout << std::endl;
}

void ps::testSJF(int *testcycles){
	std::cout << "SJF (1 PROCESSOR)" << std::endl;
	printResults(testcycles,runSJF(testcycles));
	std::cout << std::endl;
	std::cout << "SJF (4 PROCESSORS)" << std::endl;
	printResults(testcycles,runSJFmult(testcycles));
	std::cout << std::endl;
}

void ps::testLRT(int *testcycles){
	std::cout << "LRT (1 PROCESSOR)" << std::endl;
	printResults(testcycles,runLRT(testcycles));
	std::cout << std::endl;
	std::cout << "LRT (4 PROCESSORS)" << std::endl;
	printResults(testcycles,runLRTmult(testcycles));
	std::cout << std::endl;
}

void ps::tests(int *testcycles){
	testFIFO(testcycles);
	testRR(testcycles);
	testSJF(testcycles);
	testSRT(testcycles);
	testLRT(testcycles);
}

void ps::testAll(){
	std::cout << "Normal Distribution w/ Mean of 6000, Standard Deviation of 1000" << std::endl;
	tests(testcycles1);
	std::cout << "------------------------\n" << std::endl;
	std::cout << "Normal Distribution w/ Mean of 6000, Standard Deviation of 4000" << std::endl;
	tests(testcycles2);
	std::cout << "------------------------\n" << std::endl;
	std::cout << "Normal Distribution w/ Mean of 3000, Standard Deviation of 6000" << std::endl;
	tests(testcycles3);
	std::cout << "------------------------\n" << std::endl;
	std::cout << "All Values 3000 cycles" << std::endl;
	tests(testcycles4);
}

void ps::printResults(int *testcycles, results R){
	int avgWaitTime = 0;
	std::cout << "Process\tCycles\tWait Time" << std::endl;
	for(int i=0; i < 50; i++){
		std::cout << "p" << i << ":\t" << testcycles[i] << "\t" << R.waitTime[i] << std::endl;
		avgWaitTime+=R.waitTime[i];
	}
	avgWaitTime = avgWaitTime/50;
	std::cout << "Total Elapsed Time:\t" << R.elapsedTime << std::endl;
	std::cout << "Average Wait Time:\t" << avgWaitTime << std::endl;
}
