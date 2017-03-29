#pragma once

struct newPare {
	double last;
	double cnt;
};

struct openLockCoord {
	int state; // Ступень на которой было найдено решение
	int num; // Порядковый номер замка в ступени
};

// Координаты tick-а
struct stepXY {
	int i;
	int j;
};

struct stepPos {
	int inGroup; // Порядковый номер итерации, производимой над элементом родителя (эквивалентно i*N+j)
	int parent; // Родитель текущего замка
};