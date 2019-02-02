#include <stdio.h>
#include <Windows.h>
#include <cstdint>

#include "Matrix.h"
#include "MatrixMultiplier.h"
#include "SseMatrixMultiplier.h"
#include "VectorizedMatrixMultiplier.h"
#include "NonVectorizedMatrixMultiplier.h"

#define MAJOR_SIZE 100
#define MINOR_SIZE 80

int main() {
	auto a = new Matrix<double>(MAJOR_SIZE, MINOR_SIZE);
	auto b = new Matrix<double>(MAJOR_SIZE, MINOR_SIZE);

	MatrixMultiplier<double>* multipliers[] = {
		new NonVectorizedMatrixMultiplier<double>(),
		new VectorizedMatrixMultiplier<double>(),
		new SseMatrixMultiplier<double>(),
	};

	for (int i = 0; i < 3; i++) {
		int start = GetTickCount();

		multipliers[i]->Multiply(*a, *b);
		
		int end = GetTickCount();
		
		printf("TIME: %d milliseconds.\n", end - start);
	}

	system("pause");
}