#pragma once

#include "MatrixMultiplier.h"

#include <stdlib.h>

template <typename T> class NonVectorizedMatrixMultiplier : public MatrixMultiplier<T> {
public:
	Matrix<T>* Multiply(Matrix<T>& firstMatrix, Matrix<T>& secondMatrix) override {
		Matrix<T>* resultMatrix = new Matrix<T>(firstMatrix.majorSize, firstMatrix.minorSize);

		for (auto m = 0; m < firstMatrix.majorSize; m++) {
			for (auto n = 0; n < secondMatrix.majorSize; n++) {
				for (auto i = 0; i < firstMatrix.minorSize; i++) {
					T *__restrict temp = resultMatrix->matrix[m][n][i];
					for (auto j = 0; j < secondMatrix.minorSize; j++) {
						T *__restrict temp2 = secondMatrix.matrix[m][n][j];

#pragma loop(no_vector) 
						for (auto k = 0; k < firstMatrix.minorSize; k++) {
							temp[k] += firstMatrix.matrix[m][n][i][j] * temp2[k];
						}
					}
				}
			}
		}


		return resultMatrix;
	}
};