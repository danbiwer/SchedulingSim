/*
  Daniel Biwer

*/
#include "ps.h"

int main(){
	ps Psim;
	Psim.testAll();
/*
	std::cout <<  "RR (4 processors): " << Psim.runRRmult(Psim.testcycles4) << std::endl;
	std::cout <<  "RR (1 processors): " << Psim.runRR(Psim.testcycles4) << std::endl;
	std::cout <<  "FIFO (4 processors): " << Psim.runFIFOmult(Psim.testcycles4) << std::endl;
	std::cout <<  "FIFO (1 processors): " << Psim.runFIFO(Psim.testcycles4) << std::endl;
	std::cout <<  "SJF (4 processors): " << Psim.runSJFmult(Psim.testcycles4) << std::endl;
	std::cout <<  "SJF (1 processors): " << Psim.runSJF(Psim.testcycles4) << std::endl;
	std::cout <<  "SRT (1 processors): " << Psim.runSRT(Psim.testcycles4) << std::endl;
	std::cout <<  "SRT (4 processors): " << Psim.runSRTmult(Psim.testcycles4) << std::endl;
	std::cout <<  "LRT (1 processors): " << Psim.runLRT(Psim.testcycles4) << std::endl;
	std::cout <<  "LRT (4 processors): " << Psim.runLRTmult(Psim.testcycles4) << std::endl;
*/
	//std::cout << "FIFO: " << Psim.runRRmult(Psim.testcycles4) << std::endl;
	return 0;
}
