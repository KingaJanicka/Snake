
// Snake.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <stdio.h>
#include <Windows.h>
#include <chrono>
#include <thread>
#include <array>
#include <cstdlib>
#include <ctime>

int constexpr nFieldWidth = 23;
int constexpr nFieldHeight = 14;
int constexpr nScreenWidth = 80;
int constexpr nScreenHeight = 30;

bool fMoveSnake(std::array<int,322>& nFoodArray,std::array<int, 322> &nSnakeArray,int &nSnakeHeadX, int &nSnakeHeadY, int &nSnakeLenght, int dir, bool &bFruitOnField) {
	for (int x = 0; x < 23; x++) { //for (int y = 0; y < 14; y++)
		for (int y = 0; y < 14; y++) { //for (int x = 0; x < 23; x++)
			if ((nSnakeArray[y * nFieldWidth + x] == nSnakeLenght) && dir == 1) {//move left
				if (nFoodArray[y*nFieldWidth + x] != 0){
					nFoodArray[y * nFieldWidth + x] = 0;
					for (auto& a : nSnakeArray) {
						if (a != 0) {
							++a;
						}
					}
					nSnakeArray[nSnakeHeadY * nFieldWidth + nSnakeHeadX - 1] = 1;
					--nSnakeHeadX;
					nSnakeLenght++;
					bFruitOnField = false;
					return true;
				}
				else {
					nSnakeArray[y * nFieldWidth + x] = 0;
					for (auto& a : nSnakeArray) {
						if (a != 0) {
							++a;
						}
					}
					nSnakeArray[nSnakeHeadY * nFieldWidth + nSnakeHeadX - 1] = 1;
					--nSnakeHeadX;
					return true;
				}
			}

			
			if ((nSnakeArray[y * nFieldWidth + x] == nSnakeLenght) && dir == 0) {//move right
				if (nFoodArray[y*nFieldWidth + x] != 0) {
					nFoodArray[y * nFieldWidth + x] = 0;
					for (auto& a : nSnakeArray) {
						if (a != 0) {
							++a;
						}
					}
					nSnakeArray[nSnakeHeadY * nFieldWidth + nSnakeHeadX + 1] = 1;
					++nSnakeHeadX;
					nSnakeLenght++;
					bFruitOnField = false;
					return true;
				}
				else {
					nSnakeArray[y * nFieldWidth + x] = 0;
					for (auto& a : nSnakeArray) {
						if (a != 0) {
							++a;
						}
					}
					nSnakeArray[nSnakeHeadY * nFieldWidth + nSnakeHeadX + 1] = 1;
					++nSnakeHeadX;
					return true;
				}
			}
			if ((nSnakeArray[y * nFieldWidth + x] == nSnakeLenght) && dir == 3) {//move up
				if (nFoodArray[y*nFieldWidth + x] != 0) {
					nFoodArray[y * nFieldWidth + x] = 0;
					for (auto& a : nSnakeArray) {
						if (a != 0) {
							++a;
						}
					}
					nSnakeArray[(nSnakeHeadY - 1) * nFieldWidth + nSnakeHeadX] = 1;
					--nSnakeHeadY;
					nSnakeLenght++;
					bFruitOnField = false;
					return true;
				}
				else {
					nSnakeArray[y * nFieldWidth + x] = 0;
					for (auto& a : nSnakeArray) {
						if (a != 0) {
							++a;
						}
					}
					nSnakeArray[(nSnakeHeadY - 1) * nFieldWidth + nSnakeHeadX] = 1;
					--nSnakeHeadY;
					return true;
				}
			}
			
			if ((nSnakeArray[y * nFieldWidth + x] == nSnakeLenght) && dir == 2) {//move down
				if (nFoodArray[y*nFieldWidth + x] != 0) {
					nFoodArray[y * nFieldWidth + x] = 0;
					for (auto& a : nSnakeArray) {
						if (a != 0) {
							++a;
						}
					}
					nSnakeArray[(nSnakeHeadY + 1) * nFieldWidth + nSnakeHeadX] = 1;
					++nSnakeHeadY;
					nSnakeLenght++;
					bFruitOnField = false;
					return true;
				}
				else {
					nSnakeArray[y * nFieldWidth + x] = 0;
					for (auto& a : nSnakeArray) {
						if (a != 0) {
							++a;
						}
					}
					nSnakeArray[(nSnakeHeadY + 1) * nFieldWidth + nSnakeHeadX] = 1;
					++nSnakeHeadY;
					return true;
				}
			}
			
		}
	}
	return false;
}
bool fDoesSnakeHitWall (std::array<int, 322>& nSnakeArray, int& nSnakeHeadX, int& nSnakeHeadY, int dir) {
	if (dir == 1) { //left
		if (nSnakeHeadX == 1) {
			return true;
		}
		return false;
	}
	if (dir == 0) {//right
		if (nSnakeHeadX == 22) {
			return true;
		}
		return false;
	}
	if (dir == 3) { //up
		if (nSnakeHeadY == 1) {
			return true;
		}
		return false;
	}
	if (dir == 2) {//down
		if (nSnakeHeadY == 13) {
			return true;
		}
		return false;
	}
};
bool fDoesSnakeEatItself(std::array<int, 322>& nSnakeArray, int& nSnakeHeadX, int& nSnakeHeadY, int dir) {
	if (dir == 1) { //left 
		if (nSnakeArray[nSnakeHeadY * nFieldWidth + nSnakeHeadX - 1] > 0) {
			return true;
		}
		else return false;
	}
	if (dir == 0) { //right
		if (nSnakeArray[nSnakeHeadY * nFieldWidth + nSnakeHeadX + 1] > 0) {
			return true;
		}
		else return false;
	}
	if (dir == 3) { //up
		if (nSnakeArray[(nSnakeHeadY - 1) * nFieldWidth + nSnakeHeadX] > 0) {
			return true;
		}
		else return false;
	}

	if (dir == 2) { //down
		if (nSnakeArray[(nSnakeHeadY + 1) * nFieldWidth + nSnakeHeadX] > 0) {
			return true;
		}
		else return false;
	}

}
bool fPlaceFruit(std::array<int, 322>& nFoodArray, std::array<int,322> &nSnakeArray) {
	int FruitX = std::rand() % 21 + 1;
	int FruitY = std::rand() % 12 + 1;
	if (nSnakeArray[FruitY * nFieldWidth + FruitX] == 0) {
		nFoodArray[FruitY * nFieldWidth + FruitX] = 1;
		return true;
	}
	else {
		fPlaceFruit(nFoodArray, nSnakeArray);
	}
}
bool fFruitOnField(std::array<int, 322>& nFoodArray, std::array<int, 322>& nSnakeArray) {
	for (int x = 1; x < nFieldWidth - 1; ++x) {
		for (int y = 1; y < nFieldHeight - 1; ++y) {
			if (nSnakeArray[y * nFieldWidth + x] == 0 && nFoodArray[y * nFieldWidth + x] != 0) {
				return true;
			}
		}
	}
	return false;
}
int main()
{
	std::srand(std::time(0));
	// Create Screen Buffer
	wchar_t* screen = new wchar_t[nScreenWidth * nScreenHeight];
	for (int i = 0; i < nScreenWidth * nScreenHeight; i++) screen[i] = L' ';
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;

	std::array<wchar_t, 322> pField;// Create play field buffer
	for (int x = 0; x < nFieldWidth; x++) // Board Boundary
		for (int y = 0; y < nFieldHeight; y++)
			pField[y * nFieldWidth + x] = (x == 0 || x == nFieldWidth - 1 || y == nFieldHeight - 1 || y == 0) ? '.' : ' ';

	bool bKey[4];
	bool bGameOver = false;
	bool bSnakeMoved = false;
	bool bFruitOnField = false;
	bool bPlaceFruit = false;
	int dir = 1;
	int nSnakeHeadX = 10;
	int nSnakeHeadY = 7;
	int nSnakeLenght = 3;
	std::array<int, 322> nSnakeArray;
	std::array<int, 322> nFoodArray;
	nFoodArray.fill(0);
	nSnakeArray.fill(0);
	//Putting Snake into Snake array
	nSnakeArray[nSnakeHeadY * nFieldWidth + nSnakeHeadX] = 1;
	nSnakeArray[nSnakeHeadY * nFieldWidth + nSnakeHeadX + 1] = 2;
	nSnakeArray[nSnakeHeadY * nFieldWidth + nSnakeHeadX + 2] = 3;
	

	while (!bGameOver) { // main game loop


		// Timing =======================
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		// Input ========================
		for (int k = 0; k < 4; k++)								// R   L   D U
			bKey[k] = (0x8000 & GetAsyncKeyState((unsigned char)("\x27\x25\x28\x26"[k]))) != 0;
		for (int n = 0; n < 4; ++n) { //determine current key pressed
			if (bKey[n]) {
				dir = n;
			}
		}
		bFruitOnField = fFruitOnField(nFoodArray, nSnakeArray); // Check if we have fruit to eat
		if (!bFruitOnField) { //if we don't have fruit to eat place it
			bPlaceFruit = fPlaceFruit(nFoodArray, nSnakeArray);
		}

		//Snake Moving functions
		if (dir == 0) { //right
			bGameOver = fDoesSnakeEatItself(nSnakeArray, nSnakeHeadX, nSnakeHeadY, dir) || 
				fDoesSnakeHitWall(nSnakeArray, nSnakeHeadX, nSnakeHeadY, dir);
			bSnakeMoved = fMoveSnake(nFoodArray, nSnakeArray, nSnakeHeadX, nSnakeHeadY, nSnakeLenght, dir, bFruitOnField);
		}

		if (dir == 1) { //left
			bGameOver = fDoesSnakeEatItself(nSnakeArray, nSnakeHeadX, nSnakeHeadY, dir) || 
				fDoesSnakeHitWall(nSnakeArray, nSnakeHeadX, nSnakeHeadY, dir);
			bSnakeMoved = fMoveSnake(nFoodArray, nSnakeArray, nSnakeHeadX, nSnakeHeadY, nSnakeLenght, dir, bFruitOnField);
		}

		if (dir == 2) { //bottom
			bGameOver = fDoesSnakeEatItself(nSnakeArray, nSnakeHeadX, nSnakeHeadY, dir) || 
				fDoesSnakeHitWall(nSnakeArray, nSnakeHeadX, nSnakeHeadY, dir);
			bSnakeMoved = fMoveSnake(nFoodArray, nSnakeArray, nSnakeHeadX, nSnakeHeadY, nSnakeLenght, dir, bFruitOnField);
		}
		if (dir == 3) { //
			bGameOver = fDoesSnakeEatItself(nSnakeArray, nSnakeHeadX, nSnakeHeadY, dir) || 
				fDoesSnakeHitWall(nSnakeArray, nSnakeHeadX, nSnakeHeadY, dir);
			bSnakeMoved = fMoveSnake(nFoodArray, nSnakeArray, nSnakeHeadX, nSnakeHeadY, nSnakeLenght, dir, bFruitOnField);
		}

		//inclde function that will make snake move automiaticly based on previous key if nothing is pressed



		// Display ======================
		//Move Snake into pField array
		for (int x = 1; x < nFieldWidth - 1; ++x) 
			for (int y = 1; y < nFieldHeight - 1; ++y)
					pField[y * nFieldWidth + x] = L" Xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"[nSnakeArray[y * nFieldWidth + x]];
		//Move Food into pField array
		for (int x = 1; x < nFieldWidth - 1; ++x) {
			for (int y = 1; y < nFieldHeight - 1; ++y) {
				if (nFoodArray[y * nFieldWidth + x] != 0) {
					pField[y * nFieldWidth + x] = L" f"[nFoodArray[y * nFieldWidth + x]];
				}
			}
		}
		for (int x = 0; x < nFieldWidth; x++)
			for (int y = 0; y < nFieldHeight; y++)
				screen[(y + 2) * nScreenWidth + (x + 2)] = pField[y * nFieldWidth + x];



		// Display Frame
		WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
	

	}
	CloseHandle(hConsole);
	std::cout << "Game Over!!" << std::endl;
	system("pause");
	return 0;
};
