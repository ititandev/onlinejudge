#include "sort.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;
int N=-1;
double *arr;
void swap(double& a, double& b)
{
	double tmp=a;
	a=b;
	b=tmp;
}
void Input(fstream& f)
{
	string str;
	getline(f,str);
	N=stoi(str);
	arr=new double[N];
	getline(f,str);
	stringstream ss(str);
	for(int i=0;i<N;++i)
	{
		ss>>arr[i];
	}
}
void Output(fstream& f)
{
	for(int i=0;i<N;++i)
	{
		f<<setw(8)<<setprecision(4)<<arr[i];
		if((i+1)%5==0) f<<endl;
	}
}
void sort()
{
	int i, j;
	double temp;
	for (i = 1; i < N; i++)
	{
		j = i - 1;
		temp = arr[i];
		while(arr[j] > temp && j >= 0)
		{
			arr[j+1] = arr[j];
			j--;
		}
		arr[j+1] = temp;
	}
}
