#pragma once
#include "vector"
#include "Lock.cpp"
#include "structures.cpp"

class Safecracker {
public:	
	//Формирование массива количества элементов на каждом уровне
	std::vector <newPare> getTreeLevelsSituations(int lastLevel, int N){
		std::vector <newPare> allData;
		for(int i=0; i<lastLevel; i++){
			newPare* tmp = new newPare();
			tmp->last=0;
			tmp->cnt=pow(N*N,i);
			allData.push_back(*tmp);
			delete tmp;
		}
		allData[0].last=1;

		return allData;
	}

	stepXY getCoordFromNum(int num, int N){
		stepXY res;
		res.i=-1, res.j = -1;

		for(int i=0; i<N; i++)
			for(int j=0; j<N; j++)
				if(i*N+j == num){
					res.i = i;
					res.j = j;
					return res;
				}
		return res;
	}

	openLockCoord getParent(int state, int pos, int N){
		openLockCoord* lc = new openLockCoord();
		int ost = (pos%(N*N) == 0)? 0 : 1;
		lc->num=(pos/(N*N))+ost-1;
		lc->state=state-1;
		return *lc;
	}
};