#pragma once

struct newPare {
	double last;
	double cnt;
};

struct openLockCoord {
	int state; // ������� �� ������� ���� ������� �������
	int num; // ���������� ����� ����� � �������
};

// ���������� tick-�
struct stepXY {
	int i;
	int j;
};

struct stepPos {
	int inGroup; // ���������� ����� ��������, ������������ ��� ��������� �������� (������������ i*N+j)
	int parent; // �������� �������� �����
};