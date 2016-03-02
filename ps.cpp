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

unsigned int ps::runRR(){
	processhandler PH;
	unsigned int elapsedTime = 0;
	unsigned int penalty = 0;//context switch penalty;
	unsigned int numProcesses = 0;
	unsigned int pLeft = 50;
	process *current;
	while(pLeft>0){
		if(((elapsedTime % 50) == 0) && (numProcesses < 50)){
			PH.addProcess(3000);
			numProcesses++;
			if(numProcesses>1){//get next process
				if(current->pid == 50)
					current = &PH.processes.front();
				else
					current++;
				while(current->numcycles == 0){
					if(current->pid == 50)
						current = &PH.processes.front();
					else
						current++;
				}
			}
			penalty+=10;
		}
		if(numProcesses==1)//initialize current
			current = &PH.processes.front();
		current->numcycles--;
		if(current->numcycles == 0){
			pLeft--;
			if(pLeft == 0) break;
			penalty+=10;
			if(current->pid == 50)
				current = &PH.processes.front();
			else
				current++;
			while(current->numcycles == 0){
				if(current->pid == 50)
					current = &PH.processes.front();
				else
					current++;
			}
		}
		elapsedTime++;
	}
	elapsedTime+=penalty;
	return elapsedTime;

}

unsigned int ps::runFIFOmult(){
	
	processhandler PH;
	unsigned int elapsedTime = 0;
	unsigned int numProcesses = 0;
	unsigned int penalty = 0;
	process *current1;
	process *current2;
	process *current3;
	process *current4;
	//std::cout << std::flush;
	do{
		if(((elapsedTime % 50) == 0) && (numProcesses < 50)){
			//std::cout << "adding at " << elapsedTime << std::endl;
			PH.addProcess(3000);
			numProcesses++;
		}
		current1 = &PH.processes.front();
		current1->numcycles--;
		if(current1->numcycles == 0){
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
