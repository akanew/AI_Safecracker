#include "iostream"
#include "conio.h"
#include "vector"
#include "Lock.cpp"
#include "Test.cpp"
#include "Safecracker.cpp"
#include "reverseSafecracker.cpp"
#include "structures.cpp"
#define LAST_LEVEL 5
//#define UnitTest
//#define Main_Exercise
#define Test_Level_2
//#define Test_Level_3
//#define Test_Level_4
//#define Test_Level_5

int main(int* argc, char** argv) {
#ifdef UnitTest
	printf("--------\n");
	printf("Result of test: ");
	Test* tt = new Test();
	std::string result = tt->checkAllTest();
	printf("%s\n",result.c_str());
	printf("--------\n\n");
#endif
#ifdef Test_Level_2
	const int N=4;
	bool arr1[N*N]={0,0,0,0, 0,1,1,1, 0,1,1,1, 0,1,1,1};
#endif 
#ifdef Test_Level_3
	const int N=4;
	bool arr1[N*N]={1,1,1,1, 0,0,1,1, 0,0,1,1, 0,0,1,1};
#endif
#ifdef Test_Level_4
	const int N=4;
	bool arr1[N*N]={0,0,0,0, 0,0,0,1, 0,0,0,1, 0,0,0,1};
#endif
#ifdef Test_Level_5
	const int N=4;
	bool arr1[N*N]={1,1,1,1, 0,0,0,0, 0,0,0,0, 0,0,0,0,};
#endif
#ifdef Main_Exercise
	const int N=4;
	bool arr1[N*N]={0,1,1,1, 1,0,1,1, 0,1,1,0, 0,1,0,0};
#endif

	Lock* lck1 = new Lock(arr1, N); // »сходный замок
	Lock* tmp = new Lock(); // временный замок "текущего элемента"
	Safecracker* sf = new Safecracker();
	reverseSafecracker* rSf = new reverseSafecracker();
	openLockCoord crd; // ѕозици€ конечного элемента в дереве возможных вариантов
	bool openLockIsFound = false; // конечный элемент найден?
	bool openLockIsNotFound = false; // конечный элемент не найден?
	int lastLevel=LAST_LEVEL; //  онечный уровень ограничени€ дерева поиска
	int finLevel = lastLevel-1; // »ндекс конечного уровн€ в дереве поиска
	std::vector <stepPos> spl; // ѕуть позиций следовани€ в дереве возможных вариантов
	std::vector <stepXY> sxyl; // ѕуть координат тиков позиций следовани€ в дереве возможных вариантов

	// ѕолучение структуры дерева возможных вариантов
	std::vector <newPare> allData;
	allData = sf->getTreeLevelsSituations(lastLevel, N);

	while(!openLockIsFound && !openLockIsNotFound){
		//ѕереход на следующий уровень в дереве возможных вариантов
		if(allData[finLevel].last == allData[finLevel].cnt)
			finLevel++;

		// ¬ случае достижени€ при поиске конечного уровн€
		if(finLevel == lastLevel){
			openLockIsNotFound=true; //  онечный замок не найден!
			break;
		}

		// ѕолучить путь из дерева вариантов до "текущего элемента"
		// "текущий элемент" определ€етс€ позицией в дереве: уровнем - finLevel; и позицией следовани€ - allData[finLevel].last.
		spl.clear();
		spl = rSf->getReverseCrackPath(finLevel, allData[finLevel].last, N);
		sxyl.clear();
		sxyl = rSf->getCoordinateReverseCrack(spl,N);

		// ѕолучаем замок с "текущим элементом" в дереве вариантов
		tmp->copyLock(lck1);
		for(int y=sxyl.size()-1; y>=0; y--){
			tmp->tick(sxyl[y].j,sxyl[y].i);
		}

		// «амок открыт?
		if(tmp->lockIsOpen()){
			crd.state = finLevel;
			crd.num = allData[finLevel].last;
			openLockIsFound=true; // констатируем факт открыти€ замка
		}

		// ѕереходим к следующему элементу на "текущем" уровне
		allData[finLevel].last++;
		
	}

	if (openLockIsNotFound){// «амок не найден
		printf("Open lock was not found!");
	}
	else {// ¬озвращаем обратную последовательность позиций дл€ взлома

		// ѕолучить последовательность итераций взлома
		spl.clear();
		spl = rSf->getReverseCrackPath(crd.state, crd.num, N);
		// ѕолучить координаты tick-ов, выполненных на каждой итерации
		sxyl.clear();
		sxyl = rSf->getCoordinateReverseCrack(spl,N);

		// »сключить повторные тики замка
		std::vector <stepXY> sxyll; // ѕуть координат тиков позиций следовани€ в дереве возможных вариантов
		tmp->copyLock(lck1); // »сходный замок
		sxyll = rSf->reduceEqualsCoordinates(tmp, sxyl);

		// ѕолучаем и печатаем замок с "текущим элементом" в дереве вариантов		
		tmp->copyLock(lck1);
		std::cout << "========\n";
		for(int y=sxyll.size()-1; y>=0; y--){
			tmp->tick(sxyll[y].j,sxyll[y].i);
			std::cout << "i=" << sxyll[y].i << "; j=" << sxyll[y].j << ";\n--------\n";
			tmp->print();
			std::cout << "========\n";
		}
	}

	getch();
	return 0;
}