#ifndef FLOOR_H
#define FLOOR_H
#include <vector>
#include "Passenger.h"
using namespace std;

/*
[類別關係]
聚合關係: 包含零到多個Passenger實體(Has-a)。

[設計概念]
模擬真實大樓樓層的等候區。將等待中的乘客依據「想上樓」或「想下樓」
拆分為兩個獨立的佇列(Queue)，方便電梯抵達時依據當前行進方向進行載客。
*/ 

class Floor{
	private:
		int floorNumber;
		vector<Passenger> upQueue;
		vector<Passenger> downQueue;
		
	public:	
		Floor(int floorNum = 1);
		
		//依據乘客的目的地，將其分發至對應方向的等待列
		void addPassenger(const Passenger& p);
		
		//檢查該樓層特定方向是否有人按鈕等候
		inline bool hasUpPassenger() const { return !upQueue.empty();}
		inline bool hasDownPassenger() const { return !downQueue.empty();}
		
		//取得參考(提供給Elevator進行載客操作)
		vector<Passenger>& getUpQueue();
		vector<Passenger>& getDownQueue();
}; 

#endif
