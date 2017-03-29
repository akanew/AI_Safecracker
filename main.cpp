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

	Lock* lck1 = new Lock(arr1, N); // �������� �����
	Lock* tmp = new Lock(); // ��������� ����� "�������� ��������"
	Safecracker* sf = new Safecracker();
	reverseSafecracker* rSf = new reverseSafecracker();
	openLockCoord crd; // ������� ��������� �������� � ������ ��������� ���������
	bool openLockIsFound = false; // �������� ������� ������?
	bool openLockIsNotFound = false; // �������� ������� �� ������?
	int lastLevel=LAST_LEVEL; // �������� ������� ����������� ������ ������
	int finLevel = lastLevel-1; // ������ ��������� ������ � ������ ������
	std::vector <stepPos> spl; // ���� ������� ���������� � ������ ��������� ���������
	std::vector <stepXY> sxyl; // ���� ��������� ����� ������� ���������� � ������ ��������� ���������

	// ��������� ��������� ������ ��������� ���������
	std::vector <newPare> allData;
	allData = sf->getTreeLevelsSituations(lastLevel, N);

	while(!openLockIsFound && !openLockIsNotFound){
		//������� �� ��������� ������� � ������ ��������� ���������
		if(allData[finLevel].last == allData[finLevel].cnt)
			finLevel++;

		// � ������ ���������� ��� ������ ��������� ������
		if(finLevel == lastLevel){
			openLockIsNotFound=true; // �������� ����� �� ������!
			break;
		}

		// �������� ���� �� ������ ��������� �� "�������� ��������"
		// "������� �������" ������������ �������� � ������: ������� - finLevel; � �������� ���������� - allData[finLevel].last.
		spl.clear();
		spl = rSf->getReverseCrackPath(finLevel, allData[finLevel].last, N);
		sxyl.clear();
		sxyl = rSf->getCoordinateReverseCrack(spl,N);

		// �������� ����� � "������� ���������" � ������ ���������
		tmp->copyLock(lck1);
		for(int y=sxyl.size()-1; y>=0; y--){
			tmp->tick(sxyl[y].j,sxyl[y].i);
		}

		// ����� ������?
		if(tmp->lockIsOpen()){
			crd.state = finLevel;
			crd.num = allData[finLevel].last;
			openLockIsFound=true; // ������������ ���� �������� �����
		}

		// ��������� � ���������� �������� �� "�������" ������
		allData[finLevel].last++;
		
	}

	if (openLockIsNotFound){// ����� �� ������
		printf("Open lock was not found!");
	}
	else {// ���������� �������� ������������������ ������� ��� ������

		// �������� ������������������ �������� ������
		spl.clear();
		spl = rSf->getReverseCrackPath(crd.state, crd.num, N);
		// �������� ���������� tick-��, ����������� �� ������ ��������
		sxyl.clear();
		sxyl = rSf->getCoordinateReverseCrack(spl,N);

		// ��������� ��������� ���� �����
		std::vector <stepXY> sxyll; // ���� ��������� ����� ������� ���������� � ������ ��������� ���������
		tmp->copyLock(lck1); // �������� �����
		sxyll = rSf->reduceEqualsCoordinates(tmp, sxyl);

		// �������� � �������� ����� � "������� ���������" � ������ ���������		
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