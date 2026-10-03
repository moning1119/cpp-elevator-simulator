#include "Simulator.h"
#include <iostream>
#include <ctime>

Simulator::Simulator(int f, int e, double maxWeight, int tick, double rate){
	totalFloor = f;
	totalElevator = e;
	totalTick = tick;
	spawnRate = rate;
	passengerCounter = 0;	
	
	for (int i = 1; i <= totalFloor; ++i){
		floors.push_back(Floor(i));
	}
	for (int i = 1; i <= totalElevator; ++i){
		elevators.push_back(Elevator(i, maxWeight));
	}
	
	rng.seed(time(nullptr));
} 

void Simulator::run(){
	cout << "\n ---開始電梯模擬(總時長: " << totalTick << "秒)\n";
	
	uniform_real_distribution<double> probDist(0.0, 1.0);
	uniform_int_distribution<int> floorDist(1, totalFloor);
	normal_distribution<double> weightDist(65.0, 15.0);
	
	for (int time = 1; time <= totalTick; ++time){
		if (probDist(rng) <= spawnRate){
			int numPassenger;
			double eventProb = probDist(rng);
			
			if (eventProb < 0.05) {
				uniform_int_distribution<int> massiveBatch(15, 30);
				numPassenger = massiveBatch(rng);
			} else if (eventProb < 0.20) {
				uniform_int_distribution<int> midBatch(5, 12);
				numPassenger = midBatch(rng);
			} else {
				uniform_int_distribution<int> normalBatch(1, 4);
				numPassenger = normalBatch(rng);
			}
			
			for (int i = 0; i < numPassenger; ++i){
				int startFloor, destFloor;
				double behaviorProb = probDist(rng);
				
				if (behaviorProb < 0.35) {
					startFloor = 1;
					destFloor = floorDist(rng);
					if (destFloor == 1) destFloor = (totalFloor > 1) ? 2 : 1; 
				} else if (behaviorProb < 0.70) {
					startFloor = floorDist(rng);
					if (startFloor == 1) startFloor = (totalFloor > 1) ? 2 : 1;
					destFloor = 1;
				} else {
					startFloor = floorDist(rng);
					destFloor = floorDist(rng);
					while (startFloor == destFloor) destFloor = floorDist(rng);
				}
				
				double weight = weightDist(rng);
				if (weight < 20.0){
					weight = 20.0;
				}		 
				passengerCounter++;
				
				Passenger newPassenger(passengerCounter, weight, startFloor, destFloor, time);
				floors[startFloor - 1].addPassenger(newPassenger);
				
				if (destFloor > startFloor){
					dispatcher.assignRequest(startFloor, UP, elevators);
				} else {
					dispatcher.assignRequest(startFloor, DOWN, elevators);
				} 
			} 
		} 
		
		for (auto& elevator : elevators){
			if (elevator.getDoorTimer() > 0){
				elevator.decreaseDoorTimer();
				continue;
			}
			
			int currFloor = elevator.getCurrentFloor();
			Floor& thisFloor = floors[currFloor - 1];
			
			vector<Passenger> finished;
			if (elevator.getDirection() == UP || elevator.getDirection() == IDLE){
				finished = elevator.processFloor(thisFloor.getUpQueue(), time);
			} else if (elevator.getDirection() == DOWN){
				finished = elevator.processFloor(thisFloor.getDownQueue(), time);			
			}
			
			if (!finished.empty()){
				collector.addFinishedPassenger(finished);
			}
			
			elevator.checkDirection();
			elevator.move();
		}
	}
	cout << "---模擬結束---\n";
	collector.printReport(); 
}









