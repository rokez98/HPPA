#pragma once

template <typename T> class Matrix {
public:
	T**** matrix; 

	const int majorHeight;
	const int majorWidth;
	const int minorHeight;
	const int minorWidth;
	
	Matrix(int majorHeight, int majorWidth, int minorHeight, int minorWidth) 
		: majorHeight(majorHeight), majorWidth(majorWidth), minorHeight(minorHeight), minorWidth(minorWidth) {
		this->matrix = new T***[majorHeight];
		for (int i = 0; i < majorHeight; i++) {
			this->matrix[i] = new T**[majorWidth];
			for (int j = 0; j < majorWidth; j++) {
				this->matrix[i][j] = new T*[minorHeight];
				for (int k = 0; k < minorHeight; k++) {
					this->matrix[i][j][k] = new T[minorWidth];
					for (int m = 0; m < minorWidth; m++) {
						matrix[i][j][k][m] = 0;
					}
				}
			}
		}
	}

	~Matrix() {
		for (auto i = 0; i < majorHeight; i++) {
			for (auto j = 0; j < majorWidth; j++) {
				for (auto k = 0; k < minorHeight; k++) {
					delete[] matrix[i][j][k];
				}
				delete[] matrix[i][j];
			}
			delete[] matrix[i];
		}
		delete[] matrix;
	}
};