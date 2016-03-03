#include "ps.h"

bool compareMin(const process &a, const process &b){
	return a.numcycles < b.numcycles;
}

bool compareMax(const process &a, const process &b){
	return a.numcycles > b.numcycles;
}

processhandler::processhandler(){
	currentPID = 0;
	maxCycles = 11000;
	maxMem = 100;
	totalMem = 0;
	totalCycles = 0;
}

void processhandler::addProcess(unsigned int n){
	currentPID++;
	process newProcess;
	newProcess.pid = currentPID;
	unsigned int newCycles = n;
	if(newCycles > maxCycles)//if newCycles is too large, scale it back to maxCycles
		newCycles = maxCycles;
	totalCycles += newCycles;
	newProcess.numcycles = newCycles;
	newProcess.origCycles = newCycles;
	processes.push_back (newProcess);

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




unsigned int ps::runFIFO(){
	
	processhandler PH;
	unsigned int elapsedTime = 0;
	unsigned int numProcesses = 0;
	unsigned int penalty = 0;
	process *current;
	//std::cout << std::flush;
	do{
		if(((elapsedTime % 50) == 0) && (numProcesses < 50)){
			//std::cout << "adding at " << elapsedTime << std::endl;
			PH.addProcess(3000);
			numProcesses++;
		}
		current = &PH.processes.front();
		current->numcycles--;
		if(current->numcycles == 0){
			PH.processes.pop_front();
			penalty+=10;
		}
		elapsedTime++;
	}while((!PH.processes.empty()));
	//std::cout << "done" << std::endl;
	elapsedTime+=penalty;
	return elapsedTime;
	
	//return 0;
}


unsigned int ps::runFIFOmult(){
	
	processhandler PH;
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
			PH.addProcess(3000);
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

		elapsedTime++;
	}
	elapsedTime+=penalty;
	if(p1) delete p1;
	if(p2) delete p1;
	if(p3) delete p1;
	if(p4) delete p1;
	//PH.printProcesses();
	return elapsedTime;

}

unsigned int ps::runRR(){
	
	processhandler PH;
	unsigned int elapsedTime = 0;
	unsigned int numProcesses = 0;
	unsigned int penalty = 0;
	unsigned int pLeft = 50;
	process *p1 = NULL;
	
	while(pLeft>0){

		if(((elapsedTime % 50) == 0) && (numProcesses < 50)){
			PH.addProcess(3000);
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



		elapsedTime++;
	}
	elapsedTime+=penalty;
	if(p1) delete p1;
	PH.printProcesses();

	return elapsedTime;

}


unsigned int ps::runRRmult(){
	
	processhandler PH;
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
			PH.addProcess(3000);
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


		elapsedTime++;
	}
	elapsedTime+=penalty;
	if(p1) delete p1;
	if(p2) delete p2;
	if(p3) delete p3;
	if(p4) delete p4;
	PH.printProcesses();

	return elapsedTime;

}


unsigned int ps::runSJF(){
	
	processhandler PH;
	unsigned int elapsedTime = 0;
	unsigned int numProcesses = 0;
	unsigned int penalty = 0;
	unsigned int pLeft = 50;
	process *p1 = NULL;
	std::sort(PH.processes.begin(), PH.processes.end(),compareMin);
	
	while(pLeft>0){

		if(((elapsedTime % 50) == 0) && (numProcesses < 50)){
			PH.addProcess(3000);
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



		elapsedTime++;
	}
	elapsedTime+=penalty;
	if(p1) delete p1;

	return elapsedTime;

}

unsigned int ps::runSJFmult(){
	
	processhandler PH;
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
			PH.addProcess(3000);
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



		elapsedTime++;
	}
	elapsedTime+=penalty;
	if(p1) delete p1;
	if(p2) delete p2;
	if(p3) delete p3;
	if(p4) delete p4;
	//PH.printProcesses();
	return elapsedTime;

}



unsigned int ps::runSRT(){
	
	processhandler PH;
	unsigned int elapsedTime = 0;
	unsigned int numProcesses = 0;
	unsigned int penalty = 0;
	unsigned int pLeft = 50;
	process *p1 = NULL;
	unsigned int p1Last = 0;
	std::sort(PH.processes.begin(), PH.processes.end(),compareMin);
	
	while(pLeft>0){

		if(((elapsedTime % 50) == 0) && (numProcesses < 50)){
			PH.addProcess(3000);
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



		elapsedTime++;
	}
	elapsedTime+=penalty;
	if(p1) delete p1;
	PH.printProcesses();
	return elapsedTime;

}

unsigned int ps::runSRTmult(){
	
	processhandler PH;
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
			PH.addProcess(3000);
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



		elapsedTime++;
	}
	elapsedTime+=penalty;
	if(p1) delete p1;
	if(p2) delete p2;
	if(p3) delete p3;
	if(p4) delete p4;
	PH.printProcesses();
	return elapsedTime;

}