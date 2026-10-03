#include "Dispatcher.h"
#include <climits>

//找過所有電梯, 找出代價最低的電梯並指派 
void Dispatcher::assignRequest(int requestFloor, Direction requestDir, vector<Elevator>& elevator){
	int bestElevatorIndex = -1;
	int minCost = INT_MAX; //初始化為無限大 
	
	//評估每部電梯的適合度 
	for (size_t i = 0; i < elevator.size(); ++i){
		int cost = elevator[i].calculateCost(requestFloor, requestDir);
		if (cost < minCost){
			minCost = cost;
			bestElevatorIndex = i; //紀錄目前找到最佳的電梯 
		}
	}
	
	//指派電梯 
	if (bestElevatorIndex != -1){
		elevator[bestElevatorIndex].addStopRequest(requestFloor);
	}
}
