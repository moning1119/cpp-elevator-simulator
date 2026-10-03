#ifndef DATACOLLECTOR_H
#define DATACOLLECTOR_H
#include <vector>
#include "Passenger.h"
using namespace std;

/*
[類別關係]
聚合關係: 收集並儲存所有已完成的Passenger (Has-a)。

[設計概念]
負責在模擬過程中妥善保存所有已經下車的乘客資料，
並在模擬結束時，統一計算平均等待時間與平均搭乘時間，產出最終報告。
*/

class DataCollector{
	private:
		vector<Passenger> finishedPassenger;
	
	public: 
		void addFinishedPassenger(const vector<Passenger>& pList);
		void printReport() const;
};
#endif
