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
						T *__restrict temp2 = secondMatrix.matrix[m][n][j];

						const __m256d buff = {
							firstMatrix.matrix[m][n][i][j],
							firstMatrix.matrix[m][n][i][j],
							firstMatrix.matrix[m][n][i][j],
							firstMatrix.matrix[m][n][i][j]
						};

						for (auto k = 0; k < firstMatrix.minorSize; k += 4) {
							__m256d res = _mm256_add_pd(_mm256_mul_pd(buff, *reinterpret_cast<__m256d*>(temp2 + k)), *reinterpret_cast<__m256d*>(temp + k));
							memcpy(temp + k, &res, sizeof(res));
						}
					}
				}
			}
		}

		return resultMatrix;
	}
};