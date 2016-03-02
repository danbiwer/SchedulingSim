/*
  Daniel Biwer
  Homework 2, Question 3

  To compile, use g++ -std=c++0x processSimulator.cpp
*/
#include "ps.h"

int main(){
	ps Psim;

	std::cout <<  "FIFO: " << Psim.runFIFO() << std::endl;
	std::cout <<  "RR: " << Psim.runRR() << std::endl;
	//std::cout <<  Psim.runSRT() << std::endl;



	return 0;
}
