#pragma once

template <typename T> class Matrix {
public:
	T**** matrix; 

	int majorSize;
	int minorSize;
	
	Matrix(int majorSize, int minorSize) {
		this->majorSize = majorSize;
		this->minorSize = minorSize;

		this->matrix = new T***[majorSize];
		for (int i = 0; i < majorSize; i++) {
			this->matrix[i] = new T**[majorSize];
			for (int j = 0; j < majorSize; j++) {
				this->matrix[i][j] = new T*[minorSize];
				for (int k = 0; k < minorSize; k++) {
					this->matrix[i][j][k] = new T[minorSize];
				}
			}
		}
	}

	~Matrix() {
		for (auto i = 0; i < majorSize; i++) {
			for (auto j = 0; j < majorSize; j++) {
				for (auto k = 0; k < minorSize; k++) {
					delete[] matrix[i][j][k];
				}
				delete[] matrix[i][j];
			}
			delete[] matrix[i];
		}
		delete[] matrix;
	}
};