#include <stdio.h>
#include <Windows.h>
#include <cstdint>

#include "Matrix.h"
#include "MatrixMultiplier.h"
#include "SseMatrixMultiplier.h"
#include "VectorizedMatrixMultiplier.h"
#include "NonVectorizedMatrixMultiplier.h"
#include "MatrixUtils.h"

#define MAJOR_HEIGHT 200
#define MAJOR_WIDTH 200

#define MINOR_HEIGHT 4
#define MINOR_WIDTH 12

typedef float MatrixType;

int main() {
	LONGLONG start, end, nonVectorizedTime, vectorizedTime, sseTime;

	auto a = Matrix<MatrixType>(MAJOR_HEIGHT, MAJOR_WIDTH, MINOR_HEIGHT, MINOR_WIDTH);
	auto b = Matrix<MatrixType>(MAJOR_HEIGHT, MAJOR_WIDTH, MINOR_WIDTH, MINOR_HEIGHT);

	auto utils = new MatrixUtils<MatrixType>;

	utils->RandomizeMatrix(a);
	utils->RandomizeMatrix(b);

#pragma region  Nonvectorized
	start = GetTickCount64();
	auto nonVectorizedResult = (new NonVectorizedMatrixMultiplier<MatrixType>())->Multiply(a, b);
	end = GetTickCount();

	nonVectorizedTime = end - start;

	printf("Non vectorized time: %d milliseconds.\n", nonVectorizedTime);
#pragma endregion

#pragma region  Vectorized
	start = GetTickCount64();
	auto vectorizedResult = (new VectorizedMatrixMultiplier<MatrixType>())->Multiply(a, b);
	end = GetTickCount();

	vectorizedTime = end - start;

	printf("\nVectorized time: %d milliseconds. Diff: %d \n", vectorizedTime, nonVectorizedTime - vectorizedTime);
	printf("Vectorized equals to nonvectorized: %s.\n", utils->Equals(*nonVectorizedResult, *vectorizedResult) ? "true" : "false");
#pragma endregion

#pragma region  SSE
	start = GetTickCount64();
	auto sseResult = (new SseMatrixMultiplier<MatrixType>())->Multiply(a, b);
	end = GetTickCount();

	sseTime = end - start;

	printf("\nSse time: %d milliseconds. Diff: %d \n", sseTime, nonVectorizedTime - sseTime);
	printf("Sse equals to vectorized: %s.\n", utils->Equals(*sseResult, *vectorizedResult) ? "true" : "false" );
#pragma endregion

	system("pause");
}