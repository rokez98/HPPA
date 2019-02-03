#include <stdio.h>
#include <Windows.h>
#include <cstdint>

#include "Matrix.h"
#include "MatrixMultiplier.h"
#include "SseMatrixMultiplier.h"
#include "VectorizedMatrixMultiplier.h"
#include "NonVectorizedMatrixMultiplier.h"
#include "MatrixUtils.h"

#define MAJOR_SIZE 100
#define MINOR_SIZE 64

typedef double MatrixType;

int main() {
	ULONGLONG start, end;

	auto a = Matrix<MatrixType>(MAJOR_SIZE, MINOR_SIZE);
	auto b = Matrix<MatrixType>(MAJOR_SIZE, MINOR_SIZE);

	auto utils = new MatrixUtils<MatrixType>;

	MatrixMultiplier<MatrixType>* multipliers[] = {
		new NonVectorizedMatrixMultiplier<MatrixType>(),
		new VectorizedMatrixMultiplier<MatrixType>(),
		new SseMatrixMultiplier<MatrixType>()
	};

	for (int i = 0; i < 3; i++) {
		utils->RandomizeMatrix(a);
		utils->RandomizeMatrix(b);

		start = GetTickCount64();

		auto result = multipliers[i]->Multiply(a, b);

		end = GetTickCount();

		result->~Matrix();

		printf("TIME: %d milliseconds.\n", end - start);
	}

	system("pause");
}