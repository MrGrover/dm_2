#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream> 
#include <cstring> 
#include <conio.h>
#include <queue>
#include <cstdlib>
#include <cstring>
#include <limits.h>
#include <iomanip>
#include <algorithm>
#include <functional>
#include <array>
#include <vector>
#include <algorithm>
#include <iterator>
#include <stdlib.h>  
#include <stdio.h>
using namespace std;

//GOVNOKOD

#define N 40
#define var 2
#define start 36
int t = 0;

class Graph
{
private:
	int** G1;
	int** G;
public:
	int result = 0;
	int* num;

	Graph()
	{
		FILE* f;
		char file[100];
		//G
		cout << "Введите файл с матрицей G: ";
		cin >> file;
		f = fopen(file, "r");
		if (f == NULL)
			cout << "Uncorrect command" << endl;
		int count = 0;

		int** x = (int**)malloc(N * sizeof(int*));
		for (int i = 0; i < N; i++) {
			x[i] = (int*)malloc(N * sizeof(int));
		}
		G = (int**)malloc(N * sizeof(int*));
		for (int i = 0; i < N; i++) {
			G[i] = (int*)malloc(N * sizeof(int));
		}
		//Считаем матрицу из файла
		while (!feof(f))
		{
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					fscanf(f, "%i", &x[i][j]);
				}
			}
		}


			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
					cout << x[i][j] << " ";
				cout << "\n";
			}
			for (int i = 0; i < N; i++)
			{
				memcpy(&G[i], &x[i], sizeof(G[0]));
			}
		cout << "Количество вершин в графе G, вариант и стартовая: " << N << " " << var << " " << start << endl;

	};


	void printPD(int d[], vector<int> p, ofstream & fout) {
		t++;
		fout << t << endl;
		fout << "D: ";
		for (int i = 0; i < N; i++) {
			if (d[i] != 5000)
				fout << d[i] << " ";
			else
				fout << "* ";
		}
		fout << endl;
		fout << "P: ";
		for (int i = 0; i < N; i++)
			fout << p[i] << " ";
		fout << endl;
	}



	void DIST()
	{

		//int d[N]; // минимальное расстояние
		//int v[N];
		//bool visited[N];
		//
		//int begin_index = start;
		//for (int i = 0; i < N; i++)
		//{
		//	d[i] = G[begin_index][i];
		//	v[i] = 1;
		//	visited[i] = false;
		//}
		//printPD(d, v);
		ofstream fout;
		fout.open("job_Var54.out");
		int big_num = 5000;//бесконечно большое число 

		int pose[N];//посещенные
		bool nepose[N];//непосещенные
		int min = 0;
		int index_min = 0;
		vector<int> parent(N, start+1);    // объявили массив родителей и сразу заполнили -1-цами в количестве row
		vector<int>temp;//для вывода пути
		for (int i = 0; i < N; ++i) { //заполняем массив посещенных бесконечно большими числами, непосещенные(временно присоед.) заполняются 0

			pose[i] = big_num;
			nepose[i] = false;
		}
		pose[start] = 0;
		//nepose[start] = true;

		printf("\n");
		//LOL KEK AVTORU 5 LET
		cout << "\n";
		for (int i = 0; i < N - 1; ++i) {
			min = big_num;

			for (int j = 0; j < N - 1; ++j) { //ТУ 
				if (!nepose[j] && pose[j] < min) {// 
					min = pose[j];//минимальное значение вершины
					index_min = j;//индекс "минимальной" вершины
				}
			}
			nepose[index_min] = true;

			for (int j = 0; j < N; ++j) {
				if (!nepose[j] && G[index_min][j] > 0 && pose[index_min] != big_num && pose[index_min] + G[index_min][j] < pose[j]) {
					pose[j] = pose[index_min] + G[index_min][j];
					parent[j] = index_min + 1;    // запоминаем род.вершину для  вершины j
				}

			}
			printPD(pose, parent, fout);
		}

		fout.close();
	}
};

int main()
{
	setlocale(LC_ALL, "Russian");
	Graph G;
	G.DIST();
	_getch();
	return 0;
}