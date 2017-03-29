#pragma once
#include "vector"
#include "Lock.cpp"
#include "structures.cpp"

class reverseSafecracker {
public:
	

	//получить последовательность действий для успешного вскрытия замка
	std::vector <stepPos> getReverseCrackPath(int state, int num, int N){
		stepPos sp;
		int inGroup = -1;
		int parent = -1;
		std::vector <stepPos> spl;	
		sp.inGroup = num % (N*N);
		sp.parent = num/(N*N);
		spl.push_back(sp);
		int runPoint = state;
		while(runPoint >= 2){
			int pr = spl[spl.size()-1].parent;
			inGroup = spl[spl.size()-1].parent % (N*N);
			parent = spl[spl.size()-1].parent/(N*N);
			sp.inGroup=inGroup;
			sp.parent=parent;
			spl.push_back(sp);
			runPoint--;
		}
		return spl;
	};

	std::vector <stepXY> getCoordinateReverseCrack(std::vector <stepPos> spl, int N){
		stepXY sxy;
		bool isFound = false;
		std::vector <stepXY> sxyl;
		for(int t=0; t<spl.size(); t++){
			isFound=false;
			for(int i=0; i<N; i++){
				for(int j=0; j<N; j++)
					if(i*N+j == spl[t].inGroup){
						sxy.i=i;
						sxy.j=j;
						sxyl.push_back(sxy);
						isFound=true;
						break;
					}
				if(isFound) break;
			}
		}
		return sxyl;
	};	

	std::vector <stepXY> reduceEqualsCoordinates(Lock* tmp, std::vector <stepXY> sxyl){
		Lock* postTmp = new Lock(); // временный замок после "текущего элемента"
		std::vector <stepXY> sxyll; // Сокращенный путь координат тиков позиций следования в дереве возможных вариантов
		for(int y=0; y<sxyl.size(); y++){
			tmp->tick(sxyl[y].j,sxyl[y].i);
			if(y+2 < sxyl.size()){
				postTmp->tick(sxyl[y+2].j,sxyl[y+2].i);
				if(tmp->isEqual(*postTmp) == false){
					sxyll.push_back(sxyl[y]);
				}
			}
		}
		return sxyll;
	}

};