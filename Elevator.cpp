#include "Elevator.h"
#include <cmath>
#include <algorithm>

Elevator::Elevator(int id, double maxW, int startFloor){
	this->id = id;
	this->maxWeight = maxW;
	this->currentFloor = startFloor;
	this->currentDir = IDLE;
	this->currentWeight = 0.0;
	this->doorTimer = 0;
}

//接收新任務並喚醒電梯 
void Elevator::addStopRequest(int floor){
	stopRequest.insert(floor);
	if (currentDir == IDLE){
		currentDir = (floor > currentFloor) ? UP : DOWN;
	}
}

void Elevator::move(){
	if (currentDir == UP){
		currentFloor++;
	} else if (currentDir == DOWN){
		currentFloor--;
	}
}


//實作LOOK演算法, 檢查當前方向是否還有未完成任務 
void Elevator::checkDirection(){
	if (stopRequest.empty()){
		currentDir = IDLE;
		return;
	}
	
	bool furtherRequest = false;
	if (currentDir == UP){
		//檢查上方還有無停靠需求 
		for (int f : stopRequest){
			if (f > currentFloor){
				furtherRequest = true;
				break;
			}
		}
		if (!furtherRequest){
			currentDir = DOWN; //上方無需求, 轉向向下 
		}
	} else if (currentDir == DOWN){
		//檢查下方還有無停靠需求 
		for (int f : stopRequest){
			if (f < currentFloor){
				furtherRequest = true;
				break;
			}
		}
		if (!furtherRequest){
			currentDir = UP; //下方無需求, 轉向向上 
		}
	}
} 

//處理乘客進出並控制電梯門安全機制 
vector<Passenger> Elevator::processFloor(vector<Passenger>& waitingQueue, int currentTime){
	vector<Passenger> finishedPassenger;
	bool actionHappen = false; //紀錄本樓層是否有人上車 
	
	//處理離開電梯 
	for (auto it = passengerInside.begin(); it != passengerInside.end();){
		if (it->getDestFloor() == currentFloor){
			it->setLeaveTime(currentTime);
			finishedPassenger.push_back(*it);
			currentWeight -= it->getWeight();
			it = passengerInside.erase(it);
			actionHappen = true;
		} else {
			++it;
		}
	}
	stopRequest.erase(currentFloor); //清除本層停靠需求 
	
	//處理進入電梯(檢查載重限制) 
	for (auto it = waitingQueue.begin(); it != waitingQueue.end();){
		if (canLoad(it->getWeight())){
			it->setBoardTime(currentTime);
			currentWeight += it->getWeight();
			addStopRequest(it->getDestFloor()); //將新進入乘客目的地加入停靠清單 
			passengerInside.push_back(*it);
			it = waitingQueue.erase(it);
			actionHappen = true;
		} else {
			++it; //超過載重, 留在原地等候 
		}
	}
	
	//有人進出, 觸發電梯門延遲關閉 
	if (actionHappen){
		resetDoorTimer();
	}
	
	return finishedPassenger;
}

//計算電梯前往服務該需求的代價(越低越好) 
int Elevator::calculateCost(int reqFloor, Direction reqDir) const {
	int distance = abs(reqFloor - currentFloor);
	
	//閒置直接計算距離
	if (currentDir == IDLE){
		return distance;  
	}
	
	//方向相同且乘客在前方(順路代價較低) 
	if (currentDir == UP && reqDir == UP && reqFloor >= currentFloor){
		return distance;  
	}
	if (currentDir == DOWN && reqDir == DOWN && reqFloor <= currentFloor){
		return distance;
	}
	
	//方向相反或已錯過(不順路代價較高, 加上懲罰值) 
	return distance + 100;
}





















