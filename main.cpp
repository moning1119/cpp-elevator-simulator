#include <iostream>
#include "Simulator.h"
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int intValidInput(int min, int max){
	int n;
	while (true){
		cin >> n;
		if (cin.fail() || n < min || n > max){
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "輸入錯誤, 請輸入 " << min << " 到 " << max << " 之間的數字: ";
        } else {
            cin.ignore(1000, '\n');
            return n;
		}
	}
}

double doubleValidInput(double min, double max){
	double d;
	while (true){
		cin >> d;
		if (cin.fail() || d < min || d > max){
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "輸入錯誤, 請輸入 " << min << " 到 " << max << " 之間的數字: ";
        } else {
            cin.ignore(1000, '\n');
            return d;
		}
	}
}

int main(int argc, char** argv) {
	cout << "\n==================================\n";
	cout << "    多部電梯系統模擬程式(設定)    \n";
	cout << "==================================\n";
	
	cout << "輸入樓層數(ex:15, 範圍 2~100): "; 
	int numFloor = intValidInput(2, 100);
	
	cout << "輸入電梯數量(ex:4, 範圍 1~20): "; 
	int numElevator = intValidInput(1, 20);
	
	cout << "輸入電梯載重上限(kg, ex:1000.0, 範圍 100.0~5000.0): "; 
	double maxWeight = doubleValidInput(100.0, 5000.0);
	
	cout << "輸入模擬時間(秒/Tick, ex:3600, 範圍 10~86400): "; 
	int simTime = intValidInput(10, 86400);
	
	cout << "輸入每秒產生乘客的機率(ex:0.08, 範圍 0.01~1.0): "; 
	double spawnRate = doubleValidInput(0.01, 1.0);
	
	//初始化模擬並啟動時間迴圈 
	cout << "\n[System] 設定完成\n";
	Simulator sim(numFloor, numElevator, maxWeight, simTime, spawnRate);
	sim.run();
	
	cout << "模擬結束, 按Enter鍵退出程式\n"; 
	cin.get();
	return 0;
}
