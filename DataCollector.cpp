#include "DataCollector.h"
#include <iostream>

void DataCollector::addFinishedPassenger(const vector<Passenger>& pList){
	for (const auto& p : pList){
		finishedPassenger.push_back(p);
	}
}

void DataCollector::printReport() const{
	if (finishedPassenger.empty()){
		cout << "[Report] 本次模擬無人搭乘電梯。\n";
		return;
	}
	
	double totalWaitTime = 0;
	double totalRideTime = 0;
	
	for (const auto& p : finishedPassenger){
		totalWaitTime += p.getWaitTime();
		totalRideTime += p.getRideTime();
	}
	
	double avgWait = totalWaitTime / finishedPassenger.size();
	double avgRide = totalRideTime / finishedPassenger.size();
	
	cout << "\n=========================\n";
	cout << "       電梯模擬系統       \n";
	cout << "==========================\n";
	cout <<	"總服務乘客數: " << finishedPassenger.size() << " 人\n"; 
	cout << "平均等待時間: " << avgWait << "秒(Tick)\n"; 
	cout << "平均搭乘時間: " << avgRide << "秒(Tick)\n"; 
	cout << "==========================\n";
}
