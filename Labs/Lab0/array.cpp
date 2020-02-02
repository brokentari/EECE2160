#include <iostream>
#include<cstdlib>
#include<algorithm>
using namespace std;

void PrintArray(int v[], int size){
	for(int i=0; i<size; i++){
		cout<<v[i]<<endl;
	}
}

void RandomArray(int v[], int size){
	for(int i=0; i<size; i++){
		v[i]=(rand()%99)+1;
	}
}

void SortArray(int v[], int size){
	int i, j, min;
	for(i=0; i<size-1; i++){
		min=i;
		for(j=i+1; j<size; j++){
			if(v[j]<v[min]){
				min=j;
			}
		}
		if (min != i){
			swap(v[i], v[min]);
		}
	}
}
int main(){
	int array[10];
	int arr_length = sizeof(array)/sizeof(array[0]);
	RandomArray(array, arr_length);
	PrintArray(array, arr_length);
	cout<<"Sorted array:"<<endl;
	SortArray(array, arr_length);
	PrintArray(array, arr_length);
} 
