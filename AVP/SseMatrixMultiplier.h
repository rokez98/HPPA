#pragma once

#include "MatrixMultiplier.h"

#include <Windows.h>

#include "immintrin.h"

template <typename T> class SseMatrixMultiplier : public MatrixMultiplier<T> {
public:
	Matrix<T>* Multiply(Matrix<T>& firstMatrix, Matrix<T>& secondMatrix) override {
		Matrix<T>* resultMatrix = new Matrix<T>(firstMatrix.majorSize, firstMatrix.minorSize);

		for (auto m = 0; m < firstMatrix.majorSize; m++) {
			for (auto n = 0; n < secondMatrix.majorSize; n++) {
				for (auto i = 0; i < firstMatrix.minorSize; i++) {
					T *__restrict temp = resultMatrix->matrix[m][n][i];

					for (auto j = 0; j < secondMatrix.minorSize; j++) {
						T temp1 = firstMatrix.matrix[m][n][i][j];
						T *__restrict temp2 = secondMatrix.matrix[m][n][j];

						const __m256d buff = { temp1, temp1, temp1, temp1 };

						__m256d res = _mm256_add_pd(_mm256_mul_pd(buff, *reinterpret_cast<__m256d*>(temp2 + 0)), *reinterpret_cast<__m256d*>(temp + 0));
						memcpy(temp + 0, &res, sizeof(res));
						__m256d res1 = _mm256_add_pd(_mm256_mul_pd(buff, *reinterpret_cast<__m256d*>(temp2 + 4)), *reinterpret_cast<__m256d*>(temp + 4));
						memcpy(temp + 4, &res1, sizeof(res1));
					}
				}
			}
		}

		return resultMatrix;
	}
};