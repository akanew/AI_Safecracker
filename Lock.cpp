#pragma once
#include "iostream"
#include "conio.h"
#include "vector"

class Lock {
protected:
	std::vector <std::vector <bool>> lck;
	int N;
public:
	Lock(bool *arr, int N){
		setLock(arr, N);
	};

	// Печать замка
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

	//Сравнение замка в классе с внешним замком
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

	//Замок открыт?
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

	//Получть размерность массива замка (используется в классе дочернего замка)
	int getN(){
		return this->N;
	}

	//Копировать данные внешнего замка в замок класса
	void copyLock(Lock* lck){
		int nN = lck->N;
		bool* arr = (bool*) malloc(nN*nN*sizeof(bool));

		for(int i=0; i<nN; i++)
			for(int j=0; j<nN; j++)
				arr[i*nN+j] = lck->lck[i][j];

		this->setLock(arr, nN);
		free(arr);
	}

	//Конструктор по умолчанию
	Lock(){};
};