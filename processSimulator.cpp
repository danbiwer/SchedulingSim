/*
  Daniel Biwer
  Homework 2, Question 3

  To compile, use g++ -std=c++0x processSimulator.cpp
*/
#include "ps.h"

int main(){
	ps Psim;

	std::cout <<  "RR (4 processors): " << Psim.runRRmult() << std::endl;
	std::cout <<  "RR (1 processors): " << Psim.runRR() << std::endl;
	std::cout <<  "FIFO (4 processors): " << Psim.runFIFOmult() << std::endl;
	std::cout <<  "FIFO (1 processors): " << Psim.runFIFO() << std::endl;
	std::cout <<  "SJF (4 processors): " << Psim.runSJFmult() << std::endl;
	std::cout <<  "SJF (1 processors): " << Psim.runSJF() << std::endl;
	return 0;
}
