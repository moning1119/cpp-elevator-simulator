#include "Floor.h"

Floor::Floor(int floorNum){
	floorNumber = floorNum;
} 

void Floor::addPassenger(const Passenger& p){
	if (p.getDestFloor() > floorNumber){
		upQueue.push_back(p);
	} else {
		downQueue.push_back(p);
	}
}

vector<Passenger>& Floor::getUpQueue(){
	return upQueue;
}

vector<Passenger>& Floor::getDownQueue(){
	return downQueue;
}
