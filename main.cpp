#include "iostream"
#include "conio.h"
#include "vector"
//#define UnitTest

struct openLockCoord {
	int state; // Ступень на которой было найдено решение
	int num; // Порядковый номер замка в ступени
};

class lockCoord {
public:
	int state; // Ступень на которой было найдено решение
	int num; // Порядковый номер замка в ступени
};

struct stepPos {
	int inGroup; // Порядковый номер итерации, производимой над элементом родителя (эквивалентно i*N+j)
	int parent; // Родитель текущего замка
};

// Координаты tick-а
struct stepXY {
	int i;
	int j;
};

class Lock {
protected:
	std::vector <std::vector <bool>> lck;
	int N;
public:
	Lock(bool *arr, int N){
		setLock(arr, N);
	};

	void print(){
		for(int i=0; i<N; i++){
			for(int j=0; j<N; j++)
				std::cout << lck[i][j] << " ";
			std::cout << "\n";
		}
	};

	void setLock(bool *arr, int N){
		lck.clear();
		for(int i=0; i<N; i++){
			std::vector <bool> tLck;
			for(int j=0; j<N; j++)
				tLck.push_back(arr[i*N+j]);
			lck.push_back(tLck);
		}
		this->N = N;
	}

	bool isEqual(const Lock &ll){
		bool res = true;
		if(ll.N == this->N){
			for(int i=0; i<this->N; i++)
				for(int j=0; j<this->N; j++)
					if(ll.lck[i][j] != this->lck[i][j])
						res=false;
		}
		else res=false;

		return res;
	}

	//Щелкаем переключатель
	void tick(int w, int h){
		for(int i=0; i<this->N; i++){
			this->lck[h][i] = !this->lck[h][i];
			if(h != i)
				this->lck[i][w] = !this->lck[i][w];
		}
	}

	bool lockIsOpen(){
		int cntTrue = 0;
		int cntFalse = 0;
		for(int i=0; i<N; i++)
			for(int j=0; j<N; j++){
				if(this->lck[i][j]) cntTrue++;
				else cntFalse++;
			}

		bool result = (cntTrue == N*N || cntFalse == N*N)? true : false;
		return result;
	}

	int getN(){
		return this->N;
	}

	void copyLock(Lock* lck){
		int nN = lck->N;
		bool* arr = (bool*) malloc(nN*nN*sizeof(bool));

		for(int i=0; i<nN; i++)
			for(int j=0; j<nN; j++)
				arr[i*nN+j] = lck->lck[i][j];

		this->setLock(arr, nN);
		free(arr);
	}

	Lock(){};
};

class altLock : public Lock{
public:
	void setAltLock(bool *arr, int N){
		this->setLock(arr, N);
	}
};

class Test {
private:
	bool lockIsEqual(){
		const int N=3;
		bool arr1[N*N]={1,0,1, 0,1,0, 1,0,1};
		bool arr2[N*N]={1,0,1, 0,1,0, 1,0,1};
		Lock* lck1 = new Lock(arr1, N);
		altLock* lck2 = new altLock();
		lck2->setAltLock(arr2, N);
		return lck1->isEqual(*lck2);
	}

	bool lockIsNotEqual(){
		const int N=3;
		bool arr1[N*N]={1,1,1, 1,1,1, 1,1,1};
		bool arr2[N*N]={1,0,1, 0,1,0, 1,0,1};
		Lock* lck1 = new Lock(arr1, N);
		altLock* lck2 = new altLock();
		lck2->setAltLock(arr2, N);
		return lck1->isEqual(*lck2);
	}

	bool tickIsEqual(){
		const int N=3;
		bool arr1[N*N]={1,1,1, 1,1,1, 1,1,1};
		bool arr2[N*N]={0,0,0, 0,1,1, 0,1,1};
		Lock* lck1 = new Lock(arr1, N);
		lck1->tick(0,0);
		altLock* lck2 = new altLock();
		lck2->setAltLock(arr2, N);
		return lck1->isEqual(*lck2);
	}

	bool tickIsNotEqual(){
		const int N=3;
		bool arr1[N*N]={1,1,1, 1,1,1, 1,1,1};
		bool arr2[N*N]={1,0,0, 0,1,1, 0,1,1};
		Lock* lck1 = new Lock(arr1, N);
		lck1->tick(0,0);
		altLock* lck2 = new altLock();
		lck2->setAltLock(arr2, N);
		return lck1->isEqual(*lck2);
	}

	bool lockIsOpenOne(){
		const int N=3;
		bool arr1[N*N]={1,1,1, 1,1,1, 1,1,1};
		bool arr2[N*N]={1,1,1, 1,1,1, 1,1,1};
		Lock* lck1 = new Lock(arr1, N);
		bool isOpen = lck1->lockIsOpen();
		altLock* lck2 = new altLock();
		lck2->setAltLock(arr2, N);
		bool cmpLokcsIsOpen = lck1->isEqual(*lck2);
		return (cmpLokcsIsOpen & isOpen);
	}

	bool lockIsOpenNull(){
		const int N=3;
		bool arr1[N*N]={0,0,0, 0,0,0, 0,0,0};
		bool arr2[N*N]={0,0,0, 0,0,0, 0,0,0};
		Lock* lck1 = new Lock(arr1, N);
		bool isOpen = lck1->lockIsOpen();
		altLock* lck2 = new altLock();
		lck2->setAltLock(arr2, N);
		bool cmpLokcsIsOpen = lck1->isEqual(*lck2);
		return (cmpLokcsIsOpen & isOpen);
	}

	bool lockIsNotOpen(){
		const int N=3;
		bool arr1[N*N]={1,0,0, 0,0,0, 0,0,0};
		bool arr2[N*N]={1,0,0, 0,0,0, 0,0,0};
		Lock* lck1 = new Lock(arr1, N);
		bool isOpen = lck1->lockIsOpen();
		altLock* lck2 = new altLock();
		lck2->setAltLock(arr2, N);
		bool cmpLokcsIsOpen = lck1->isEqual(*lck2);
		return (cmpLokcsIsOpen & isOpen);
	}

	bool locksCompare(bool* arr1, bool* arr2, const int N){
		Lock* lck1 = new Lock(arr1, N);
		lck1->tick(0,0);
		altLock* lck2 = new altLock();
		lck2->setAltLock(arr2, N);
		return lck1->isEqual(*lck2);
	}
public:
	std::string lockIsOpenCorrect(){
		if(!lockIsOpenOne())return "\"lock is open for 1\"";
		if(!lockIsOpenNull())return "\"lock is open for 0\"";
		if(lockIsNotOpen())return "\"lock is not open\"";
		return "";
	}

	std::string tickIsCorrect(){
		if(!this->tickIsEqual()) return "\"lock is equal\"";
		if(this->tickIsNotEqual()) return "\"lock is not equal\"";
		return "";
	}
	std::string createLock(){
		if(!this->lockIsEqual()) return "\"lock is equal\"";
		if(this->lockIsNotEqual()) return "\"lock is not equal\"";
		return "";
	}

	std::string checkAllTest(){
		std::string result = "Error in group test ";
		if(this->createLock().compare("") != 0) return result += "\"create lock\" in test ";
		if(this->tickIsCorrect().compare("") != 0) return result += "\"tick's lock\" in test ";
		if(this->lockIsOpenCorrect().compare("") != 0) return result += "\"open lock\" in test ";
		if(result.compare("Error in group test ") == 0) return "All test is success";
	}
};

class Safecracker {
public:
	std::vector <Lock> getAllLockState(Lock* lck){
		std::vector <Lock> states;
		for(int i=0; i<lck->getN(); i++)
			for(int j=0; j<lck->getN(); j++){
				Lock* tmp = new Lock();
				tmp->copyLock(lck);
				tmp->tick(i,j);				
				states.push_back(*tmp);
			}
		return states;
	}

	int checkVektorToLockIsOpen(std::vector <Lock> lcks){
		for(int i=0; i<lcks.size(); i++){
			if(lcks[i].lockIsOpen()) return i;
		}
		return -1;
	}
};

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
};

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

class newPare {
public:
		double last;
		double cnt;
	};

lockCoord getParent(int state, int pos, int N){
	lockCoord* lc = new lockCoord();
	int ost = (pos%(N*N) == 0)? 0 : 1;
	lc->num=(pos/(N*N))+ost-1;
	lc->state=state-1;
	return *lc;
}

int main(int* argc, char** argv) {
	//const int N=2;
	//bool arr1[N*N]={0,1,0,1};
	//const int N=3;
	//bool arr1[N*N]={1,1,0,0,1,1,1,0,1};
	//const int N=4;
	//bool arr1[N*N]={0,0,0,0, 1,1,0,0, 1,1,0,0, 1,1,0,0};
	//bool arr1[N*N]={1,1,1,1, 1,1,1,0, 1,1,1,0, 1,1,1,0};
	//bool arr1[N*N]={0,0,0,0, 1,1,1,1, 1,1,1,1, 1,1,1,1};
	const int N=4;
	bool arr1[N*N]={0,1,1,1, 1,0,1,1, 0,1,1,0, 0,1,0,0};
	Lock* lck1 = new Lock(arr1, N);

	Safecracker* sf = new Safecracker();
	openLockCoord crd;
	bool openLockIsFound = false;
	int lastLevel=7;	

	std::vector <newPare> allData;
	for(int i=0; i<lastLevel; i++){
		newPare* tmp = new newPare();
		tmp->last=0;
		tmp->cnt=pow(N*N,i);
		allData.push_back(*tmp);
		delete tmp;
	}
	allData[0].last=1;

	int finLevel = 6;
	bool openLockIsNotFound = false;
	reverseSafecracker* rSf = new reverseSafecracker();
	std::vector <stepPos> spl;
	std::vector <stepXY> sxyl;
	Lock* tmp = new Lock();

	while(!openLockIsFound && !openLockIsNotFound){
		//std::cout<<"---  ---\n";
		if(allData[finLevel].last == allData[finLevel].cnt)
			finLevel++;

		if(finLevel == lastLevel){
			openLockIsNotFound=true;
			break;
		}

		spl.clear();
		spl = rSf->getReverseCrackPath(finLevel, allData[finLevel].last, N);
		sxyl.clear();
		sxyl = rSf->getCoordinateReverseCrack(spl,N);

		tmp->copyLock(lck1);
		for(int y=sxyl.size()-1; y>=0; y--){
			tmp->tick(sxyl[y].j,sxyl[y].i);
			//std::cout<<"level "<<sxyl.size()-y<<'\n';
			//tmp->print();
		}

		if(tmp->lockIsOpen()){
			crd.state = finLevel;
			crd.num = allData[finLevel].last;
			openLockIsFound=true;
		}

		//std::cout<<"--- ite:" << (int)allData[finLevel].last << " ---\n\n";
		allData[finLevel].last++;
		
	}

	openLockIsNotFound;

	// Возвращаем обратную последовательность позиций для взлома
	//reverseSafecracker* rSf = new reverseSafecracker();
	// Получить последовательность итераций взлома
	//std::vector <stepPos> spl;
	spl.clear();
	spl = rSf->getReverseCrackPath(crd.state, crd.num, N);
	// Получить координаты tick-ов, выполненных на каждой итерации
	//std::vector <stepXY> sxyl;
	sxyl.clear();
	sxyl = rSf->getCoordinateReverseCrack(spl,N);

	//Вывод последовательности достижения результата
	//lck1->print();
	/*std::cout << "========\n\n";
	for(int t=0; t<spl.size(); t++){
		std::cout << "i=" << sxyl[t].i << "; j=" << sxyl[t].j << ";\n--------\n";
		if(t!=(spl.size()-1)) server[t+1][spl[t].inGroup-1].print();
		else {
			Lock* tmp = new Lock(server[t][spl[t-1].inGroup-1]);
			tmp->tick(sxyl[t].i,sxyl[t].j);
			tmp->print();
		}
		std::cout << "========\n\n";
	}*/
	//_CrtDumpMemoryLeaks();
	getch();
	return 0;
}

// Первая версия кода - не оптимизированная по памяти
/*
#include "iostream"
#include "conio.h"
#include "vector"
//#define UnitTest

struct openLockCoord {
	int state; // Ступень на которой было найдено решение
	int num; // Порядковый номер замка в ступени
};

struct stepPos {
	int inGroup; // Порядковый номер итерации, производимой над элементом родителя (эквивалентно i*N+j)
	int parent; // Родитель текущего замка
};

// Координаты tick-а
struct stepXY {
	int i;
	int j;
};

class Lock {
protected:
	std::vector <std::vector <bool>> lck;
	int N;
public:
	Lock(bool *arr, int N){
		setLock(arr, N);
	};

	void print(){
		for(int i=0; i<N; i++){
			for(int j=0; j<N; j++)
				std::cout << lck[i][j] << " ";
			std::cout << "\n";
		}
	};

	void setLock(bool *arr, int N){
		for(int i=0; i<N; i++){
			std::vector <bool> tLck;
			for(int j=0; j<N; j++)
				tLck.push_back(arr[i*N+j]);
			lck.push_back(tLck);
		}
		this->N = N;
	}

	bool isEqual(const Lock &ll){
		bool res = true;
		if(ll.N == this->N){
			for(int i=0; i<this->N; i++)
				for(int j=0; j<this->N; j++)
					if(ll.lck[i][j] != this->lck[i][j])
						res=false;
		}
		else res=false;

		return res;
	}

	//Щелкаем переключатель
	void tick(int w, int h){
		for(int i=0; i<this->N; i++){
			this->lck[h][i] = !this->lck[h][i];
			if(h != i)
				this->lck[i][w] = !this->lck[i][w];
		}
	}

	bool lockIsOpen(){
		int cntTrue = 0;
		int cntFalse = 0;
		for(int i=0; i<N; i++)
			for(int j=0; j<N; j++){
				if(this->lck[i][j]) cntTrue++;
				else cntFalse++;
			}

		bool result = (cntTrue == N*N || cntFalse == N*N)? true : false;
		return result;
	}

	int getN(){
		return this->N;
	}

	void copyLock(Lock* lck){
		int nN = lck->N;
		bool* arr = (bool*) malloc(nN*nN*sizeof(bool));

		for(int i=0; i<nN; i++)
			for(int j=0; j<nN; j++)
				arr[i*nN+j] = lck->lck[i][j];

		this->setLock(arr, nN);
	}

	Lock(){};
};

class altLock : public Lock{
public:
	void setAltLock(bool *arr, int N){
		this->setLock(arr, N);
	}
};

class Test {
private:
	bool lockIsEqual(){
		const int N=3;
		bool arr1[N*N]={1,0,1, 0,1,0, 1,0,1};
		bool arr2[N*N]={1,0,1, 0,1,0, 1,0,1};
		Lock* lck1 = new Lock(arr1, N);
		altLock* lck2 = new altLock();
		lck2->setAltLock(arr2, N);
		return lck1->isEqual(*lck2);
	}

	bool lockIsNotEqual(){
		const int N=3;
		bool arr1[N*N]={1,1,1, 1,1,1, 1,1,1};
		bool arr2[N*N]={1,0,1, 0,1,0, 1,0,1};
		Lock* lck1 = new Lock(arr1, N);
		altLock* lck2 = new altLock();
		lck2->setAltLock(arr2, N);
		return lck1->isEqual(*lck2);
	}

	bool tickIsEqual(){
		const int N=3;
		bool arr1[N*N]={1,1,1, 1,1,1, 1,1,1};
		bool arr2[N*N]={0,0,0, 0,1,1, 0,1,1};
		Lock* lck1 = new Lock(arr1, N);
		lck1->tick(0,0);
		altLock* lck2 = new altLock();
		lck2->setAltLock(arr2, N);
		return lck1->isEqual(*lck2);
	}

	bool tickIsNotEqual(){
		const int N=3;
		bool arr1[N*N]={1,1,1, 1,1,1, 1,1,1};
		bool arr2[N*N]={1,0,0, 0,1,1, 0,1,1};
		Lock* lck1 = new Lock(arr1, N);
		lck1->tick(0,0);
		altLock* lck2 = new altLock();
		lck2->setAltLock(arr2, N);
		return lck1->isEqual(*lck2);
	}

	bool lockIsOpenOne(){
		const int N=3;
		bool arr1[N*N]={1,1,1, 1,1,1, 1,1,1};
		bool arr2[N*N]={1,1,1, 1,1,1, 1,1,1};
		Lock* lck1 = new Lock(arr1, N);
		bool isOpen = lck1->lockIsOpen();
		altLock* lck2 = new altLock();
		lck2->setAltLock(arr2, N);
		bool cmpLokcsIsOpen = lck1->isEqual(*lck2);
		return (cmpLokcsIsOpen & isOpen);
	}

	bool lockIsOpenNull(){
		const int N=3;
		bool arr1[N*N]={0,0,0, 0,0,0, 0,0,0};
		bool arr2[N*N]={0,0,0, 0,0,0, 0,0,0};
		Lock* lck1 = new Lock(arr1, N);
		bool isOpen = lck1->lockIsOpen();
		altLock* lck2 = new altLock();
		lck2->setAltLock(arr2, N);
		bool cmpLokcsIsOpen = lck1->isEqual(*lck2);
		return (cmpLokcsIsOpen & isOpen);
	}

	bool lockIsNotOpen(){
		const int N=3;
		bool arr1[N*N]={1,0,0, 0,0,0, 0,0,0};
		bool arr2[N*N]={1,0,0, 0,0,0, 0,0,0};
		Lock* lck1 = new Lock(arr1, N);
		bool isOpen = lck1->lockIsOpen();
		altLock* lck2 = new altLock();
		lck2->setAltLock(arr2, N);
		bool cmpLokcsIsOpen = lck1->isEqual(*lck2);
		return (cmpLokcsIsOpen & isOpen);
	}

	bool locksCompare(bool* arr1, bool* arr2, const int N){
		Lock* lck1 = new Lock(arr1, N);
		lck1->tick(0,0);
		altLock* lck2 = new altLock();
		lck2->setAltLock(arr2, N);
		return lck1->isEqual(*lck2);
	}
public:
	std::string lockIsOpenCorrect(){
		if(!lockIsOpenOne())return "\"lock is open for 1\"";
		if(!lockIsOpenNull())return "\"lock is open for 0\"";
		if(lockIsNotOpen())return "\"lock is not open\"";
		return "";
	}

	std::string tickIsCorrect(){
		if(!this->tickIsEqual()) return "\"lock is equal\"";
		if(this->tickIsNotEqual()) return "\"lock is not equal\"";
		return "";
	}
	std::string createLock(){
		if(!this->lockIsEqual()) return "\"lock is equal\"";
		if(this->lockIsNotEqual()) return "\"lock is not equal\"";
		return "";
	}

	std::string checkAllTest(){
		std::string result = "Error in group test ";
		if(this->createLock().compare("") != 0) return result += "\"create lock\" in test ";
		if(this->tickIsCorrect().compare("") != 0) return result += "\"tick's lock\" in test ";
		if(this->lockIsOpenCorrect().compare("") != 0) return result += "\"open lock\" in test ";
		if(result.compare("Error in group test ") == 0) return "All test is success";
	}
};

class Safecracker {
public:
	std::vector <Lock> getAllLockState(Lock* lck){
		std::vector <Lock> states;
		for(int i=0; i<lck->getN(); i++)
			for(int j=0; j<lck->getN(); j++){
				Lock* tmp = new Lock();
				tmp->copyLock(lck);
				tmp->tick(i,j);				
				states.push_back(*tmp);
			}
		return states;
	}

	int checkVektorToLockIsOpen(std::vector <Lock> lcks){
		for(int i=0; i<lcks.size(); i++){
			if(lcks[i].lockIsOpen()) return i;
		}
		return -1;
	}
};

class reverseSafecracker {
public:
	//получить последовательность действий для успешного вскрытия замка
	std::vector <stepPos> getReverseCrackPath(int state, int num, int N){
		stepPos sp;
		int inGroup = -1;
		int parent = -1;
		std::vector <stepPos> spl;	
		sp.inGroup = (num+1 % (N*N) == 0) ? (N*N) : ((num+1) % (N*N));
		sp.parent = (num+1 % (N*N) == 0) ? ((num+1)/(N*N)) : ((num+1)/(N*N))+1;
		spl.push_back(sp);
		int runPoint = state;
		while(runPoint >= 2){
			inGroup = (spl[spl.size()-1].parent % (N*N) == 0) ? (N*N) : spl[spl.size()-1].parent % (N*N);
			parent = (spl[spl.size()-1].parent % (N*N) == 0) ? (spl[spl.size()-1].parent/(N*N)) : (spl[spl.size()-1].parent/(N*N))+1;
			sp.inGroup=inGroup;
			sp.parent=parent;
			spl.push_back(sp);
			runPoint--;
		}
		return spl;
	};

	std::vector <stepXY> getCoordinateReverseCrack(std::vector <stepPos> spl, int N){
		stepXY sxy;
		std::vector <stepXY> sxyl;
		for(int t=0; t<spl.size(); t++){
			for(int i=0; i<N; i++)
				for(int j=0; j<N; j++)
					if(i*N+j == spl[t].inGroup-1){
						sxy.i=j;
						sxy.j=i;
						sxyl.push_back(sxy);
					}
		}
		return sxyl;
	};
};

int main(int* argc, char** argv) {
#ifdef UnitTest
	Test* tt = new Test();
	std::string res = tt->checkAllTest();
	std::cout << res.c_str() << "\n\n";
#endif

	//const int N=2;
	//bool arr1[N*N]={0,1,0,1};
	//const int N=3;
	//bool arr1[N*N]={1,1,0,0,1,1,1,0,1};
	const int N=4;
	bool arr1[N*N]={0,1,1,0, 1,1,0,1, 1,0,1,1, 0,1,1,0};
	Lock* lck1 = new Lock(arr1, N);

	std::vector <std::vector <Lock>> server;
	std::vector <Lock> tmp;
	tmp.push_back(*lck1);
	server.push_back(tmp);
	Safecracker* sf = new Safecracker();
	openLockCoord crd;
	bool openLockIsFound = false;
	// Подбираем вариант взлома замка
	while(!openLockIsFound){
		for(int i=0; i<server.size(); i++){
			crd.state=i+1;
			int step=0;
			std::vector <Lock> states;
			for(int j=0; j<server[i].size(); j++){
				std::vector <Lock> state;
				state = sf->getAllLockState(&server[i][j]);
				int lockIdInGroup = sf->checkVektorToLockIsOpen(state);
				if(lockIdInGroup == -1) {
					step+=(N*N);
					for(int t=0; t<state.size(); t++)
						states.push_back(state[t]);
				}
				else {
					step+=lockIdInGroup;
					for(int t=0; t<state.size(); t++)
						states.push_back(state[t]);
					crd.num = step;
					openLockIsFound=true;
					break;
				}
			}
			server.push_back(states);
			if(openLockIsFound) break;
		}
	}

	// Возвращаем обратную последовательность позиций для взлома
	reverseSafecracker* rSf = new reverseSafecracker();
	// Получить последовательность итераций взлома
	std::vector <stepPos> spl;
	spl = rSf->getReverseCrackPath(crd.state, crd.num, N);
	// Получить координаты tick-ов, выполненных на каждой итерации
	std::vector <stepXY> sxyl;
	sxyl = rSf->getCoordinateReverseCrack(spl,N);

	//Вывод последовательности достижения результата
	lck1->print();
	std::cout << "========\n\n";
	for(int t=0; t<spl.size(); t++){
		std::cout << "i=" << sxyl[t].i << "; j=" << sxyl[t].j << ";\n--------\n";
		if(t!=(spl.size()-1)) server[t+1][spl[t].inGroup-1].print();
		else {
			Lock* tmp = new Lock(server[t][spl[t-1].inGroup-1]);
			tmp->tick(sxyl[t].i,sxyl[t].j);
			tmp->print();
		}
		std::cout << "========\n\n";
	}

	getch();
	return 0;
}
*/

// Вторая версия кода - оптимизированная по памяти
/*
#include "iostream"
#include "conio.h"
#include "vector"
//#define UnitTest

struct openLockCoord {
	int state; // Ступень на которой было найдено решение
	int num; // Порядковый номер замка в ступени
};

struct stepPos {
	int inGroup; // Порядковый номер итерации, производимой над элементом родителя (эквивалентно i*N+j)
	int parent; // Родитель текущего замка
};

// Координаты tick-а
struct stepXY {
	int i;
	int j;
};

class Lock {
protected:
	std::vector <std::vector <bool>> lck;
	int N;
public:
	Lock(bool *arr, int N){
		setLock(arr, N);
	};

	void print(){
		for(int i=0; i<N; i++){
			for(int j=0; j<N; j++)
				std::cout << lck[i][j] << " ";
			std::cout << "\n";
		}
	};

	void setLock(bool *arr, int N){
		for(int i=0; i<N; i++){
			std::vector <bool> tLck;
			for(int j=0; j<N; j++)
				tLck.push_back(arr[i*N+j]);
			lck.push_back(tLck);
		}
		this->N = N;
	}

	bool isEqual(const Lock &ll){
		bool res = true;
		if(ll.N == this->N){
			for(int i=0; i<this->N; i++)
				for(int j=0; j<this->N; j++)
					if(ll.lck[i][j] != this->lck[i][j])
						res=false;
		}
		else res=false;

		return res;
	}

	//Щелкаем переключатель
	void tick(int w, int h){
		for(int i=0; i<this->N; i++){
			this->lck[h][i] = !this->lck[h][i];
			if(h != i)
				this->lck[i][w] = !this->lck[i][w];
		}
	}

	bool lockIsOpen(){
		int cntTrue = 0;
		int cntFalse = 0;
		for(int i=0; i<N; i++)
			for(int j=0; j<N; j++){
				if(this->lck[i][j]) cntTrue++;
				else cntFalse++;
			}

		bool result = (cntTrue == N*N || cntFalse == N*N)? true : false;
		return result;
	}

	int getN(){
		return this->N;
	}

	void copyLock(Lock* lck){
		int nN = lck->N;
		bool* arr = (bool*) malloc(nN*nN*sizeof(bool));

		for(int i=0; i<nN; i++)
			for(int j=0; j<nN; j++)
				arr[i*nN+j] = lck->lck[i][j];

		this->setLock(arr, nN);
	}

	Lock(){};
};

class altLock : public Lock{
public:
	void setAltLock(bool *arr, int N){
		this->setLock(arr, N);
	}
};

class Test {
private:
	bool lockIsEqual(){
		const int N=3;
		bool arr1[N*N]={1,0,1, 0,1,0, 1,0,1};
		bool arr2[N*N]={1,0,1, 0,1,0, 1,0,1};
		Lock* lck1 = new Lock(arr1, N);
		altLock* lck2 = new altLock();
		lck2->setAltLock(arr2, N);
		return lck1->isEqual(*lck2);
	}

	bool lockIsNotEqual(){
		const int N=3;
		bool arr1[N*N]={1,1,1, 1,1,1, 1,1,1};
		bool arr2[N*N]={1,0,1, 0,1,0, 1,0,1};
		Lock* lck1 = new Lock(arr1, N);
		altLock* lck2 = new altLock();
		lck2->setAltLock(arr2, N);
		return lck1->isEqual(*lck2);
	}

	bool tickIsEqual(){
		const int N=3;
		bool arr1[N*N]={1,1,1, 1,1,1, 1,1,1};
		bool arr2[N*N]={0,0,0, 0,1,1, 0,1,1};
		Lock* lck1 = new Lock(arr1, N);
		lck1->tick(0,0);
		altLock* lck2 = new altLock();
		lck2->setAltLock(arr2, N);
		return lck1->isEqual(*lck2);
	}

	bool tickIsNotEqual(){
		const int N=3;
		bool arr1[N*N]={1,1,1, 1,1,1, 1,1,1};
		bool arr2[N*N]={1,0,0, 0,1,1, 0,1,1};
		Lock* lck1 = new Lock(arr1, N);
		lck1->tick(0,0);
		altLock* lck2 = new altLock();
		lck2->setAltLock(arr2, N);
		return lck1->isEqual(*lck2);
	}

	bool lockIsOpenOne(){
		const int N=3;
		bool arr1[N*N]={1,1,1, 1,1,1, 1,1,1};
		bool arr2[N*N]={1,1,1, 1,1,1, 1,1,1};
		Lock* lck1 = new Lock(arr1, N);
		bool isOpen = lck1->lockIsOpen();
		altLock* lck2 = new altLock();
		lck2->setAltLock(arr2, N);
		bool cmpLokcsIsOpen = lck1->isEqual(*lck2);
		return (cmpLokcsIsOpen & isOpen);
	}

	bool lockIsOpenNull(){
		const int N=3;
		bool arr1[N*N]={0,0,0, 0,0,0, 0,0,0};
		bool arr2[N*N]={0,0,0, 0,0,0, 0,0,0};
		Lock* lck1 = new Lock(arr1, N);
		bool isOpen = lck1->lockIsOpen();
		altLock* lck2 = new altLock();
		lck2->setAltLock(arr2, N);
		bool cmpLokcsIsOpen = lck1->isEqual(*lck2);
		return (cmpLokcsIsOpen & isOpen);
	}

	bool lockIsNotOpen(){
		const int N=3;
		bool arr1[N*N]={1,0,0, 0,0,0, 0,0,0};
		bool arr2[N*N]={1,0,0, 0,0,0, 0,0,0};
		Lock* lck1 = new Lock(arr1, N);
		bool isOpen = lck1->lockIsOpen();
		altLock* lck2 = new altLock();
		lck2->setAltLock(arr2, N);
		bool cmpLokcsIsOpen = lck1->isEqual(*lck2);
		return (cmpLokcsIsOpen & isOpen);
	}

	bool locksCompare(bool* arr1, bool* arr2, const int N){
		Lock* lck1 = new Lock(arr1, N);
		lck1->tick(0,0);
		altLock* lck2 = new altLock();
		lck2->setAltLock(arr2, N);
		return lck1->isEqual(*lck2);
	}
public:
	std::string lockIsOpenCorrect(){
		if(!lockIsOpenOne())return "\"lock is open for 1\"";
		if(!lockIsOpenNull())return "\"lock is open for 0\"";
		if(lockIsNotOpen())return "\"lock is not open\"";
		return "";
	}

	std::string tickIsCorrect(){
		if(!this->tickIsEqual()) return "\"lock is equal\"";
		if(this->tickIsNotEqual()) return "\"lock is not equal\"";
		return "";
	}
	std::string createLock(){
		if(!this->lockIsEqual()) return "\"lock is equal\"";
		if(this->lockIsNotEqual()) return "\"lock is not equal\"";
		return "";
	}

	std::string checkAllTest(){
		std::string result = "Error in group test ";
		if(this->createLock().compare("") != 0) return result += "\"create lock\" in test ";
		if(this->tickIsCorrect().compare("") != 0) return result += "\"tick's lock\" in test ";
		if(this->lockIsOpenCorrect().compare("") != 0) return result += "\"open lock\" in test ";
		if(result.compare("Error in group test ") == 0) return "All test is success";
	}
};

class Safecracker {
public:
	std::vector <Lock> getAllLockState(Lock* lck){
		std::vector <Lock> states;
		for(int i=0; i<lck->getN(); i++)
			for(int j=0; j<lck->getN(); j++){
				Lock* tmp = new Lock();
				tmp->copyLock(lck);
				tmp->tick(i,j);				
				states.push_back(*tmp);
			}
		return states;
	}

	int checkVektorToLockIsOpen(std::vector <Lock> lcks){
		for(int i=0; i<lcks.size(); i++){
			if(lcks[i].lockIsOpen()) return i;
		}
		return -1;
	}
};

class reverseSafecracker {
public:
	//получить последовательность действий для успешного вскрытия замка
	std::vector <stepPos> getReverseCrackPath(int state, int num, int N){
		stepPos sp;
		int inGroup = -1;
		int parent = -1;
		std::vector <stepPos> spl;	
		sp.inGroup = (num+1 % (N*N) == 0) ? (N*N) : ((num+1) % (N*N));
		sp.parent = (num+1 % (N*N) == 0) ? ((num+1)/(N*N)) : ((num+1)/(N*N))+1;
		spl.push_back(sp);
		int runPoint = state;
		while(runPoint >= 2){
			inGroup = (spl[spl.size()-1].parent % (N*N) == 0) ? (N*N) : spl[spl.size()-1].parent % (N*N);
			parent = (spl[spl.size()-1].parent % (N*N) == 0) ? (spl[spl.size()-1].parent/(N*N)) : (spl[spl.size()-1].parent/(N*N))+1;
			sp.inGroup=inGroup;
			sp.parent=parent;
			spl.push_back(sp);
			runPoint--;
		}
		return spl;
	};

	std::vector <stepXY> getCoordinateReverseCrack(std::vector <stepPos> spl, int N){
		stepXY sxy;
		std::vector <stepXY> sxyl;
		for(int t=0; t<spl.size(); t++){
			for(int i=0; i<N; i++)
				for(int j=0; j<N; j++)
					if(i*N+j == spl[t].inGroup-1){
						sxy.i=j;
						sxy.j=i;
						sxyl.push_back(sxy);
					}
		}
		return sxyl;
	};
};

int main(int* argc, char** argv) {
#ifdef UnitTest
	Test* tt = new Test();
	std::string res = tt->checkAllTest();
	std::cout << res.c_str() << "\n\n";
#endif

	//const int N=2;
	//bool arr1[N*N]={0,1,0,1};
	//const int N=3;
	//bool arr1[N*N]={1,1,0,0,1,1,1,0,1};
	//const int N=4;
	//bool arr1[N*N]={0,1,1,0, 1,1,0,1, 1,0,1,1, 0,1,1,0};

	const int N=4;
	bool arr1[N*N]={0,1,1,1, 1,0,1,1, 0,1,1,0, 0,1,0,0};
	Lock* lck1 = new Lock(arr1, N);

	Safecracker* sf = new Safecracker();
	openLockCoord crd;
	bool openLockIsFound = false;

	int state=0;
	int step=0;
	std::vector <Lock> parentStates;
	parentStates.push_back(*lck1);
	// Подбираем вариант взлома замка
	while(!openLockIsFound){
		int i=state;
		crd.state=i+1;
		std::vector <Lock> childStates;
		for(int j=0; j<parentStates.size(); j++){
			std::vector <Lock> state;
			state = sf->getAllLockState(&parentStates[j]);
			int lockIdInGroup = sf->checkVektorToLockIsOpen(state);
			if(lockIdInGroup == -1) {
				step+=(N*N);
				for(int t=0; t<state.size(); t++)
					childStates.push_back(state[t]);
			}
			else {
				step+=lockIdInGroup;
				for(int t=0; t<state.size(); t++)
					childStates.push_back(state[t]);
				crd.num = step;
				openLockIsFound=true;
				break;
			}
		}

		parentStates.clear();
		for(int t=0; t<childStates.size(); t++)
			parentStates.push_back(childStates[t]);
		step=0;
		state++;

		if(openLockIsFound) break;
	}

	// Возвращаем обратную последовательность позиций для взлома
	reverseSafecracker* rSf = new reverseSafecracker();
	// Получить последовательность итераций взлома
	std::vector <stepPos> spl;
	spl = rSf->getReverseCrackPath(crd.state, crd.num, N);
	// Получить координаты tick-ов, выполненных на каждой итерации
	std::vector <stepXY> sxyl;
	sxyl = rSf->getCoordinateReverseCrack(spl,N);

	//Вывод последовательности достижения результата
	lck1->print();
	std::cout << "========\n\n";
	for(int t=0; t<spl.size(); t++){
		std::cout << "i=" << sxyl[t].i << "; j=" << sxyl[t].j << ";\n--------\n";
		if(t!=(spl.size()-1)) server[t+1][spl[t].inGroup-1].print();
		else {
			Lock* tmp = new Lock(server[t][spl[t-1].inGroup-1]);
			tmp->tick(sxyl[t].i,sxyl[t].j);
			tmp->print();
		}
		std::cout << "========\n\n";
	}

	getch();
	return 0;
}
*/