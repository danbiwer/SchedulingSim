#include "ps.h"

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


unsigned int ps::runSRT(){
	processhandler PH;
	unsigned int min;
	unsigned int elapsedTime = 0;
	unsigned int penalty = 0;//context switch penalty;
	unsigned int numProcesses;
	unsigned int pLeft = 50;
	unsigned int lastpid;
	process *it;
	PH.addProcess(3000);
	it = &PH.processes.front();
	lastpid = it->pid;
	numProcesses++;
	std::cout << std::flush;
	while(1){
		//elapsedTime++;

		if((elapsedTime % 50 == 0) && (elapsedTime > 0)){
			if(numProcesses < 50){//add new process
				PH.addProcess(3000);
				numProcesses++;
				if( !(it = PH.findMin()) ){
					break;
				}
				if(it->pid != lastpid){
					penalty+=10;
					lastpid = it->pid;
				}
			}
		}



		it->numcycles -= 1;
		if(it->numcycles==0){
			if( !(it = PH.findMin()) ){
					break;
				}
			if(it->pid != lastpid){
					penalty+=10;
					lastpid = it->pid;
				}
		}


		elapsedTime++;
	}
	elapsedTime += penalty;
	return elapsedTime;

}

process * processhandler::findMin(){
	unsigned int min = 0;
	process *temp, *minProcess;
	minProcess=NULL;
	for(int i = 0; i<processes.size(); i++){
		temp = &processes[i];
		if(temp->numcycles > 0){
			if((min==0) || (temp->numcycles < min)){
				min = temp->numcycles;
				minProcess = temp;
			}
		}
	}
	return minProcess;
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


		if(p1){
			p1->numcycles--;
			if(p1->numcycles==0){
				pLeft--;
				p1 = NULL;
			}
			else if(((p1->origCycles - p1->numcycles) % 50) == 0){//problem here
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
			else if(((p1->origCycles - p1->numcycles) % 50) == 0){//problem here
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
			else if(((p2->origCycles - p2->numcycles) % 50) == 0){//problem here
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
			else if(((p3->origCycles - p3->numcycles) % 50) == 0){//problem here
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
			else if(((p4->origCycles - p4->numcycles) % 50) == 0){//problem here
				PH.processes.push_back(*p4);
				p4 = NULL;
			}
		}


		elapsedTime++;
	}
	elapsedTime+=penalty;
	if(p1) delete p1;
	PH.printProcesses();

	return elapsedTime;

}