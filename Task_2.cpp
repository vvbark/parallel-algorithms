#include <iostream>
#include <string.h>
#include <omp.h>
#include <cstdlib>
#include <time.h>
#include <vector>
#include <bits/stdc++.h>

using namespace std; 

vector <vector <int>> generateMatrix(int sizeOfMatrix) {
	
	vector <vector <int>> matrix (sizeOfMatrix);
	
	for (int i = 0; i < sizeOfMatrix; i++) {
		for (int j = 0; j < sizeOfMatrix; j++)
			matrix[i].push_back(rand());
	}
	
	return matrix;
}

void displayMatrix(vector<vector<int>> *matrix) {
	
	int N = (*matrix).size();
	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			printf("|%d|", (*matrix)[i][j]);
		cout << endl;
	}
}

vector <vector <int>> multiplyMatrices_ijk(vector<vector<int>> *matrix1, vector<vector<int>> *matrix2, int n) {
	vector <vector <int>> matrixMultiplied((*matrix1).size(), vector<int>((*matrix1)[0].size()));
	
	int N = matrixMultiplied.size();
	
	clock_t t = clock();
	
#pragma omp parallel for num_threads(n) collapse(3) 
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			for (int k = 0; k < N; k++)
				#pragma omp atomic
				matrixMultiplied[i][j] += (*matrix1)[i][k] * (*matrix2)[k][j];

	t = clock() - t;
	printf("\nTime ijk loops is %d \n", t );
	
	return matrixMultiplied;
}

vector <vector <int>> multiplyMatrices_ikj(vector<vector<int>> *matrix1, vector<vector<int>> *matrix2, int n) {
	vector <vector <int>> matrixMultiplied((*matrix1).size(), vector<int>((*matrix1)[0].size()));
	
	int N = matrixMultiplied.size();
	
	clock_t t = clock();
	
#pragma omp parallel for num_threads(n) collapse(3)
	for (int i = 0; i < N; i++)
		for (int k = 0; k < N; k++)
			for (int j = 0; j < N; j++)
				#pragma omp atomic
				matrixMultiplied[i][j] += (*matrix1)[i][k] * (*matrix2)[k][j];

	t = clock() - t;
	printf("\nTime ikj loops is %d \n", t);
	
	return matrixMultiplied;
}

vector <vector <int>> multiplyMatrices_jki(vector<vector<int>> *matrix1, vector<vector<int>> *matrix2, int n) {
	vector <vector <int>> matrixMultiplied((*matrix1).size(), vector<int>((*matrix1)[0].size()));
	
	int N = matrixMultiplied.size();
	
	clock_t t = clock();
	
#pragma omp parallel for num_threads(n) collapse(3) 
	for (int j = 0; j < N; j++)
		for (int k = 0; k < N; k++)
			for (int i = 0; i < N; i++)
				#pragma omp atomic
				matrixMultiplied[i][j] += (*matrix1)[i][k] * (*matrix2)[k][j];

			
	t = clock() - t;
	printf("\nTime jki loops is %d \n", t);
	
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
	
	vector <vector <int>> matrix1 = generateMatrix(sizeOfMatrix), 
							matrix2 = generateMatrix(sizeOfMatrix); 
		
	// display small matrix
	//displayMatrix(&matrix1);
	//cout << endl;
	//isplayMatrix(&matrix2);
	
	vector <vector <int>> matrix (sizeOfMatrix, vector<int>(sizeOfMatrix));
	
	printf("\nijk | n | Time, s | Eff\n");
	printf("---------------------------------");
	for (int n = 1; n <= 10; n++) {
		printf("\nCase of %d threads", n);
		matrix = multiplyMatrices_ijk(&matrix1, &matrix2, n);
	}
	//printf("\nResult of matrix multiplication: \n");
	//displayMatrix(&matrix);
	
	for (int n = 1; n <= 10; n++) {
		printf("\nCase of %d threads", n);
		matrix = multiplyMatrices_ikj(&matrix1, &matrix2, n);
	}
	//printf("\nResult of matrix multiplication: \n");
	//displayMatrix(&matrix);
	
	for (int n = 1; n <= 10; n++) {
		printf("\nCase of %d threads", n);
		matrix = multiplyMatrices_jki(&matrix1, &matrix2, n);
	}
	//printf("\nResult of matrix multiplication: \n");
	//displayMatrix(&matrix);

	return 0;
}
