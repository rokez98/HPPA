#pragma once

#include "Matrix.h"
#include "time.h"

template <typename T>
class MatrixUtils {
public:
	void RandomizeMatrix(Matrix<T>& matrix) {
		srand((unsigned)time(NULL));

		for (int i = 0; i < matrix.majorHeight; i++) {
			for (int j = 0; j < matrix.majorWidth; j++) {
				for (int k = 0; k < matrix.minorHeight; k++) {
					for (int m = 0; m < matrix.minorWidth; m++) {
						matrix.matrix[i][j][k][m] = (T)(rand() % 100);
					}
				}
			}
		}
	}

	bool Equals(Matrix<T>& matrix, Matrix<T>& secondMatrix) {
		for (int i = 0; i < matrix.majorHeight; i++) {
			for (int j = 0; j < matrix.majorWidth; j++) {
				for (int k = 0; k < matrix.minorHeight; k++) {
					for (int m = 0; m < matrix.minorWidth; m++) {
						if (matrix.matrix[i][j][k][m] != secondMatrix.matrix[i][j][k][m]) {
							return false;
						}
					}
				}
			}
		}
		
		return true;
	}
};