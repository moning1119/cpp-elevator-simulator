#ifndef DISPATCHER_H
#define DISPATCHER_H
#include <vector>
#include "Elevator.h"
using namespace std;

/*
[類別關係]
依賴關係: 依賴 Elevator 類別來分配任務 (Uses-a)。
 (本身不擁有電梯，僅負責將大廳的請求指派給最合適的電梯實體)
 
[設計概念]
實作Cost-Based Dispatch(代價計算指派)演算法。
負責接收來自各樓層的乘車請求，計算所有電梯的服務代價並將任務指派給代價最低(最快抵達)的電梯。
 */ 

class Dispatcher{
	public:
		//依據請求樓層和方向, 從電梯陣列中挑選最佳並寫入任務 
		void assignRequest(int requestFloor, Direction requestDir, vector<Elevator>& elevator);
};

#endif
