#pragma once
#include "Lock.cpp"

class altLock : public Lock{
public:
	void setAltLock(bool *arr, int N){
		this->setLock(arr, N);
	}
};