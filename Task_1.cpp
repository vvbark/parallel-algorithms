#include <iostream>
#include <string.h>
#include <omp.h>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <bits/stdc++.h>

using namespace std; 

int maximumValue(vector <int> arr) {
	
	time_t startTime, delta;
	int max_element = 0;
	
	cout << "\n\nn  |  time, s\n----------" << endl;
	
	for (int n = 1; n <= 10; n++) {
		startTime = time(NULL);
		
#pragma omp parallel for shared(max_element, arr) num_threads(n) 
		for (int i = 0; i < arr.size(); i++)
			#pragma omp critical 
			{
				if (arr[i] > max_element)
					max_element = arr[i];
			}
		delta = time(NULL) - startTime;
		cout << n << "  |  " << delta << endl;
	}
	
	return max_element;
}

vector <int> generateVector(int sizeOfArray) {
	
	vector <int> arr(0);
	
	for (int i = 0; i < sizeOfArray; i++) 
		arr.push_back(rand() * 100);
	
	return arr;
}

int main(int argc, char *argv[]) {	

	unsigned long long sizeOfArray = 0;
	cout << argc << endl;
	
	if (argc > 1)
	{
		sizeOfArray = atoll(argv[1]);
		cout << "The size of array is " << sizeOfArray << endl;
	} 
	else
	{
		cout << "Not arguments" << endl;
		return 0;
	}
	
	srand(time(0));
	
	vector <int> arr (sizeOfArray);
	generate(arr.begin(), arr.end(), rand);
	
	//for (int i = 0; i < arr.size(); i++)
	//	cout << arr[i] << " ";
	
	int max_value = maximumValue(arr);
	
	cout << "\nMaximum value is " << max_value << endl;
	return 0;
}
