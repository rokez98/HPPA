#pragma once

#include "MatrixMultiplier.h"

template <typename T> class VectorizedMatrixMultiplier : public MatrixMultiplier<T> {
	void mul(Matrix<T>& firstMatrix, Matrix<T>& secondMatrix, Matrix<T>* resultMatrix, int m, int n, int l) {
		for (auto i = 0; i < firstMatrix.minorHeight; i++) {
			T *__restrict temp = resultMatrix->matrix[m][n][i];

			for (auto j = 0; j < secondMatrix.minorWidth; j++) {
				T *__restrict temp2 = secondMatrix.matrix[l][n][j];

				for (auto k = 0; k < secondMatrix.minorWidth; k++) {
					temp[k] += firstMatrix.matrix[m][l][i][j] * temp2[k];
				}
			}
		}
	}

public:
	Matrix<T>* Multiply(Matrix<T>& firstMatrix, Matrix<T>& secondMatrix) override {
		Matrix<T>* resultMatrix = new Matrix<T>(firstMatrix.majorHeight, secondMatrix.majorWidth, firstMatrix.minorHeight, secondMatrix.minorWidth);

		for (auto m = 0; m < firstMatrix.majorHeight; m++) {
			for (auto n = 0; n < secondMatrix.majorWidth; n++) {
				for (auto l = 0; l < firstMatrix.majorWidth; l++) {
					mul(firstMatrix, secondMatrix, resultMatrix, m, n, l);
				}
			}
		}

		return resultMatrix;
	}
};