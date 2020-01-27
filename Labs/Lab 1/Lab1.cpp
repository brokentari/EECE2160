#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using std::cout;
using std::cin;
using std::endl;

double *array;
int count;
int size;

void Initialize() {
	count = 0;
	size = 2;
	array = new double[size];
}

void Finalize(){
	delete[] array;
}

void Grow(){ 
	int new_size = size * 2;
	double *new_array = new double[new_size];

	for(int i = 0; i < size; i++){
		new_array[i] = array[i];
	}
	
	Finalize();
	array = new_array;
	cout << "Vector grown" << endl;
	cout << "Previous capacity: " << size << " elements" << endl;
	cout << "New capacity: "<< new_size << " elements" << endl;
	size = new_size;
}

void AddElement(){
	if(size == count){
		Grow();
	}
	double new_element;
	cout << "Enter the new element: _" << endl;
	cin >> new_element;
	array[count] = new_element;
	count++;
}

void RemoveElement(){
	if(count>0){
		array[count-1] = 0;
		count--;
	}
	else cout << "The array is already empty" << endl;
}

void InsertElement(){
	int index;
	double new_element;
	cout <<"Enter the index of the new element: _" << endl;
	cin >> index;
	cout << "Enter the new element: _" << endl;
	cin >> new_element;

	if(size=count){
		Grow();
	}

	for(int i = count-1; i >= index; i--){
		array[i + 1] = array[i];	
	}

	array[index] = new_element;
	count++;
}

void Shrink(){
	double *new_array = new double[count];

	for(int i=0; i < count; i++){
		array[i] = new_array[i];
	}

	size = count;
	array = new_array;
}	

void PrintVector(){
	for(int i = 0; i < size; i++){
		cout << array[i] << " ";
	}
	cout << endl;
}

int main(){
	Initialize();
	int input;
	while (true){
		cout << "Main Menu:" << endl;
		cout << "1. List vector's contents" << endl;
		cout << "2. Append element at the end" << endl;
		cout << "3. Remove last element" << endl;
		cout << "4. Insert one element" << endl;
		cout << "5. Exit" << endl;
		cout << "Select an Option: _ " << endl;
		cin >> input;
		switch (input){
			case 1:
				cout<<"List vector's contents"<<endl;
				PrintVector();
				break;
			case 2:
				cout<<"Append element at the end"<<endl;
				AddElement();
				break;
			case 3:
				cout<<"Remove last element"<<endl;
				RemoveElement();
				break;
			case 4:
				cout<<"Insert one element"<<endl;
				InsertElement();
				break;
			case 5:
				return(0);
				break;
			default: 
				cout<<"Error: Invalid number"<<endl;
		}
	}
}
