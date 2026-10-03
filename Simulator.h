#ifndef SIMULATOR_H
#define SIMULATOR_H
#include <vector>
#include <random>
#include "Floor.h"
#include "Elevator.h"
#include "Dispatcher.h"
#include "DataCollector.h"
using namespace std;

class Simulator{
	private:
		int totalFloor;
		int totalElevator;
		int totalTick;
		double spawnRate;
		int passengerCounter;
	
		vector<Floor> floors;
		vector<Elevator> elevators;
		Dispatcher dispatcher;
		DataCollector collector;
		mt19937 rng;
		
	public:
		Simulator(int floor, int elevator, double maxWeight, int tick, double spawnRate);
		void run();
}; 

#endif
