#ifndef sort_h
#define sort_h
#include <fstream>
using namespace std;
extern int N;
extern double* arr;
void swap(double& a, double& b);
void Input(fstream& fin);
void Output(fstream& fout);
void sort();
#endif
