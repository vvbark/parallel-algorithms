#include <iostream>
#include <string.h>
#include <omp.h>
#include <cstdlib>
#include <time.h>
#include <vector>
#include <bits/stdc++.h>

using namespace std; 

vector <vector <float>> generateMatrix(float sizeOfMatrix) {
	
	vector <vector <float>> matrix (sizeOfMatrix);
	
	for (int i = 0; i < sizeOfMatrix; i++) {
		for (int j = 0; j < sizeOfMatrix; j++)
			matrix[i].push_back(rand() / RAND_MAX);
	}
	
	return matrix;
}

void displayMatrix(vector <vector <float>> matrix) {
	
	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix[i].size(); j++)
			printf("|%d|", matrix[i][j]);
		cout << endl;
	}
}

vector <vector <float>> multiplyMatrices(vector<vector<float>> *matrix1, 
										 vector<vector<float>> *matrix2) {
	vector <vector <float>> matrixMultiplied((*matrix1).size(), 
							vector<float>((*matrix1)[0].size()));
	
	
	return matrixMultiplied;
}

int main(int argc, char *argv[]) {	

	unsigned long long sizeOfMatrix = 0;
	
	if (argc > 1)
	{
		sizeOfMatrix = atoll(argv[1]);
		printf("Size of matrix is: %d\n", sizeOfMatrix);
	} 
	else
	{
		printf("Not arguments\n");
		return 0;
	}
	
	vector <vector <float>> matrix1 = generateMatrix(sizeOfMatrix), 
							matrix2 = generateMatrix(sizeOfMatrix); 
	
	cout << matrix1[0][0] << endl;
	
	// display small matrix
	displayMatrix(matrix1);
	cout << endl;
	displayMatrix(matrix2);
	
	return 0;
}
