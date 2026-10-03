#ifndef PASSENGER_H
#define PASSENGER_H

/*
[類別關係]
基礎實體：被 Floor, Elevator, DataCollector 以聚合的方式包含(Has-a)

[設計概念]
負責記錄單一乘客的生命週期數據(體重、起終點、各階段時間)
作為系統計算「平均等待時間」與「平均搭乘時間」的最小資料單元)
*/

class Passenger{
	private:
		int id;             // 乘客唯一識別碼
		double weight;      // 乘客自身重量 (用於判斷電梯是否滿載)
		int startFloor;     // 出發樓層
		int destFloor;      // 目的樓層
		int spawnTime;      // 誕生時間 (Tick)
		int boardTime;      // 進入電梯時間 (Tick)
		int leaveTime;      // 離開電梯時間 (Tick)
		
	public:
		Passenger(int id, double w, int start, int dest, int spawn);
		
		inline int getId() const { return id;}
		inline double getWeight() const { return weight;}
		inline int getStartFloor() const { return startFloor;}
		inline int getDestFloor() const { return destFloor;}
		inline int getSpawnTime() const { return spawnTime;}
		inline int getWaitTime() const {return boardTime - spawnTime;}
		inline int getRideTime() const {return leaveTime - boardTime;}
	
		inline void setBoardTime(int t) {boardTime = t;}
		inline void setLeaveTime(int t) {leaveTime = t;}
}; 

#endif
