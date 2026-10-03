#ifndef ELEVATOR_H
#define ELEVATOR_H
#include "Passenger.h"
#include <vector>
#include <set>
using namespace std;

enum Direction{
	IDLE, UP, DOWN
}; 

/*
[類別關係]
組合關係: 內部車廂裝載零到多個Passenger(Has-a)。
依賴關係: 被Dispatcher呼叫以計算代價(Uses-a)。
 
[設計概念]
實作LOOK演算法, 負責管理自身的移動狀態、載重限制，並處理乘客的上下車邏輯與車廂門安全延遲機制。
 */

class Elevator{
	private:
		int id;
		int currentFloor;
		int doorTimer;
		Direction currentDir;
		double maxWeight;
		double currentWeight;
		vector<Passenger> passengerInside; 	// 車廂內的乘客清單
		set<int> stopRequest;				// 預計停靠的樓層清單(LOOK演算法用)
		
		
	public:
		Elevator(int id, double maxW, int startFloor = 1);
		 
		inline int getId() const { return id;}
		inline int getCurrentFloor() const { return currentFloor;}
		inline Direction getDirection() const { return currentDir;}
		inline bool canLoad(double weight) const {return (currentWeight + weight) <= maxWeight;}
		inline int getDoorTimer() const { return doorTimer;}
		inline void decreaseDoorTimer() {
			if (doorTimer > 0)
				doorTimer--;	
		}
		inline void resetDoorTimer(){
			doorTimer = 5;
		}
		
		void addStopRequest(int floor);
		void move();
		void checkDirection();
		
		//處理樓層的上下客並回傳抵達目的地的乘客清單 
		vector<Passenger> processFloor(vector<Passenger>& waitingQueue, int currentTime);
		
		//提供給Dispatcher的評分函式 
		int calculateCost(int requestFloor, Direction requestDir) const; 
};

#endif
