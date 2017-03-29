#pragma once
#include "Lock.cpp"
#include "altLock.cpp"

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
protected:
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
		if(this->createLock().compare("") != 0) 
			result = "Error in group test \"create lock\" in test ";
		if(this->tickIsCorrect().compare("") != 0) 
			result = "Error in group test \"tick's lock\" in test ";
		if(this->lockIsOpenCorrect().compare("") != 0) 
			result = "Error in group test \"open lock\" in test ";
		if(result.compare("Error in group test ") == 0) 
			result = "All test is success";
		return result;
	}
};
