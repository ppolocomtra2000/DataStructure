#pragma once
#include <iostream>
#include <math.h>
using namespace std;

void input(int matrix[][20],int m,int n);	//Init a 2D matrix randomly
void output(int matrix[][20],int m,int n);	//Output 2D matrix
int determinant(int matrix[][20],int n);	//Return an integer number that symbols the determinant of matrix
void getCofactor(int matrix[][20], int temp[][20], int p, int q, int n);	//Make a temp array to get cofactor of original matrix
void adjoint(int matrix[][20], int adj[][20], int n);	//Make a adjoint array to get adjoint of of the original matrix by delete i row and j column
void getInverse(int matrix[][20], int n);	//Collab 2 functions above to get an Inverse matrix
void swapRow(int matrix[][20], int row1, int row2, int col);	//Swap 2 row 
int rankMatrix(int matrix[][20], int m,int n);	//return an integer number that symbols rank of matrix
void solvingLinearEquation();	//Solving an linear equation using matrix
void multiply(int matrix[][20], int temp[][20], int m,int n,int newM,int newN);	//Return a matrix that get multiplied by 2 matrix preceeded
void run();	//Run programme


