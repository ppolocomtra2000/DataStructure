#include "Matrix.h"


void input(int matrix[][20],int m,int n)
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			matrix[i][j] = rand() % 10 + 1;
		}
	}
}

void output(int matrix[][20],int m,int n)
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout <<matrix[i][j]<<"\t";
		}
		cout << endl;
	}
}

int determinant(int matrix[][20],int n)
{
	//using recursive method
	int Det = 0;
	//base case
	if (n == 1)
		return (matrix[0][0]);
	//base case II: Sarrus rule
	if (n == 2)
		return ((matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]));
	//the others
	for (int index = 0; index < n; index++)
	{
		//Init a smaller matrix 
		int recursiveMatrix[20][20];
		for (int i = 0; i < n; i++)
		{
			for (int j = 1; j < n; j++)
			{
				if (i < index)
					recursiveMatrix[i][j - 1] = matrix[i][j];
				else if (i > index)
					recursiveMatrix[i - 1][j - 1] = matrix[i][j];
			}
		}
		//if ((i+j) %2==0) then the multiplier would be 1, the others is -1 
		if (index % 2 == 0)
			Det += 1 * matrix[index][0] * determinant(recursiveMatrix, n - 1);
		else
			Det += (-1) * matrix[index][0] * determinant(recursiveMatrix, n - 1);
	}
	return Det;
}

void multiply(int matrix[][20],int newMatrix[][20],int m,int n,int newM,int newN)
{
	int temp[20][20];
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < newN; j++)
		{
			temp[i][j] = 0;
			for (int k = 0; k < newM; k++)
			{
				temp[i][j] += matrix[i][k] * newMatrix[k][j];
			}
		}
	}
	output(temp, m, newN);
}

void getCofactor(int matrix[][20], int temp[][20],int p,int q,int n)
{
	//get cofactor. Tieng viet goi la phan bu
	int i = 0, j = 0;
	for (int row = 0; row < n; row++)
	{
		for (int col = 0; col < n; col++)
		{
			if (row != p && col != q)
			{
				temp[i][j++] = matrix[row][col];
				if (j == n - 1)
				{
					j = 0;
					i++;
				}
			}
		}
	}
}

void adjoint(int matrix[][20], int adj[][20],int n)
{
	//Adjoint matrix.Tieng viet goi la ma tran phu hop
	if (n == 1)
	{
		adj[0][0] = 1;
		return;
	}

	int temp[20][20], num = 1;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			getCofactor(matrix, temp, i, j, n);
			if ((i + j) % 2 == 0)
				num = 1;
			else
				num = -1;
			//transpose
			adj[j][i] = num * determinant(temp, n - 1);
		}
	}
}

void getInverse(int matrix[][20], int n)
{
	//get Inverse of a matrix by using: Adj(matrix)/Det(matrix)
	float inverse[20][20];
	int det = determinant(matrix, n);
	if (det == 0)
	{
		cout << "Impossible!";
	}
	int adj[20][20];
	adjoint(matrix, adj,n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			inverse[i][j] = adj[i][j] / float(det);
	//output
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << inverse[i][j]<<"\t";
		}
		cout << endl;
	}
}

void swapRow(int matrix[][20], int row1, int row2, int col)
{
	for (int i = 0; i < col; i++)
	{
		int temp = matrix[row1][i];
		matrix[row1][i] = matrix[row2][i];
		matrix[row2][i] = temp;
	}
}

int rankMatrix(int matrix[][20], int m, int n)
{
	//by using Gauss - Jordan method
	//0<=rank<=min(m,n)
	int rank = (m > n) ? n : m;
	for (int row = 0; row < rank; row++)
	{
		//if matrix[0][0] is not 0. Then make all the element except the diagonal becomes 0 => Gauss-Jordan medthod
		if (matrix[row][row])
		{
			for (int col = 0; col < m; col++)
			{
				if (col != row)
				{
					double baseNum = (double)matrix[col][row] / matrix[row][row];
					for (int i = 0; i < rank; i++)
						matrix[col][i] -= baseNum * matrix[row][i];
				}
			}
		}
		//if matrix[0][0] is 0. Then find a row with non-zero entry and swap  with that row. But if no row with non-zero entry, then that column is all 0, then
		//swap that column with the last column  and we process that row again.
		else
		{
			bool reduce = true;
			for (int i = row + 1; i < m; i++)
			{
				if (matrix[i][row])
				{
					swapRow(matrix, row, i, rank);
					reduce = false;
					break;
				}
			}
			if (reduce)
			{
				rank--;
				for (int i = 0; i < m; i++)
					matrix[i][row] = matrix[i][rank];
			}
			row--;
		}
	}
	return rank;
}

void solvingLinearEquation()
{
	int newN;
	/*cout.precision(4);
	cout.setf(ios::fixed);*/
	//Init equation
	cout << "Number of equation:" << endl;
	cin >> newN;
	float x[5];
	float matrix[20][20];
	for (int i = 0; i < newN; i++)
		for (int j = 0; j <= newN; j++)
			matrix[i][j] = rand() % 10 + 1;
	//Partion
	//Picking the largest entry number in that row and swap in the first.
	for (int i = 0; i < newN; i++)
	{
		for (int k = i + 1; k < newN; k++)
		{
			if (abs(matrix[i][i]) < abs(matrix[k][i]))
			{
				for (int j = 0; j <= newN; j++)
				{
					double temp = matrix[i][j];
					matrix[i][j] = matrix[k][j];
					matrix[k][j] = temp;
				}
			}
		}
	}
	cout << "The matrix after Pivotisation:" << endl;
	for (int i = 0; i < newN; i++)            //print the new matrix
	{
		for (int j = 0; j <= newN; j++)
			cout << matrix[i][j] << "\t";
		cout << "\n";
	}
	//Gauss elimination
	for (int row = 0; row < newN-1; row++)
	{
		for (int col = row+1; col < newN; col++)
		{
			double multiply = (double)matrix[col][row] / matrix[row][row];
			for (int i = 0; i <= newN; i++)
				matrix[col][i] -= multiply * matrix[row][i];
		}
	}
	cout << "\n\nThe matrix after gauss-elimination is as follows:\n";
	for (int i = 0; i < newN; i++)            //print the new matrix
	{
		for (int j = 0; j <= newN; j++)
			cout << matrix[i][j] << "\t";
		cout << "\n";
	}
	//Finding X by changing method
	for (int i = newN - 1; i >= 0; i--)
	{
		x[i] = matrix[i][newN];
		for (int j = i + 1; j < newN; j++)
			if (j != i)
				x[i] -= matrix[i][j] * x[j];
		x[i] = x[i] / matrix[i][i];
	}
	cout << "\nThe values of the variables are as follows:\n";
	for (int i = 0; i < newN; i++)
		cout << x[i] << endl;            // Print the values of x, y,z,....    
}

void run() {
	int matrix[20][20], m, n;
	int newMatrix[20][20], newM, newN;
	int choice;
	while (1) {
		cout << "=============" << endl;
		cout << "Matrix:" << endl;
		cout << "1.Finding determinant of matrix" << endl;
		cout << "2.Finding inverse of matrix" << endl;
		cout << "3. Finding multiply matrix of 2 matrix " << endl;
		cout << "4.Finding rank of matrix" << endl;
		cout << "5.Solving linear equation" << endl;
		cout << "6.Exit" << endl;
		cout << "================" << endl;
		cout << "Your choice:" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			cout << "Input row:" << endl;
			cin >> m;
			cout << "Input column:" << endl;
			cin >> n;
			input(matrix, m, n); 
			cout << "Your matrix:" << endl;
			output(matrix, m, n);
			if (m == n)
				cout << "Determinant:" << determinant(matrix, n) << endl;
			else
			{
				cout << "Not exist determinant cause Row not equal to Column." << endl;
				break;
			}
			break;
		}
		case 2:
		{
			cout << "Input row:" << endl;
			cin >> m;
			cout << "Input column:" << endl;
			cin >> n;
			input(matrix, m, n);
			cout << "Your matrix before get inversed:" << endl;
			output(matrix, m, n);
			if (m != n)
			{
				cout << "Not exist inversed matrix cause row not equal to col." << endl;
				break;
			}
			else
			{
				cout << "Your matrix after get inversed:" << endl;
				getInverse(matrix,n);
			}
			break;
		}
		case 3:
		{
			cout << "Enter your first matrix:" << endl;
			cout << "Input row:" << endl;
			cin >> m;
			cout << "Input column:" << endl;
			cin >> n;
			input(matrix, m, n);
			cout << "Your 1st matrix:" << endl;
			output(matrix, m, n);
			cout << "Enter your second matrix:" << endl;
			cout << "Input new 2nd row:" << endl;
			cin >> newM;
			cout << "Input new 2nd column:" << endl;
			cin >> newN;
			input(newMatrix, newM, newN);
			cout << "Your 2nd matrix:" << endl;
			output(newMatrix, newM, newN);
			if (n == newM) {
				cout << "==============" << endl;
				cout << "Multiply Matrix:" << endl;
				multiply(matrix, newMatrix, m, n, newM, newN);
			}
			else
			{
				cout << "Not exist multiply matrix cause 1st column not equal to 2nd row!" << endl;
				break;
			}
			break;
		}
		case 4:
		{
			cout << "Input row:" << endl;
			cin >> m;
			cout << "Input column:" << endl;
			cin >> n;
			input(matrix, m, n);
			cout << "Your matrix:" << endl;
			output(matrix, m, n);
			cout << "Rank of matrix: " << rankMatrix(matrix, m, n)<<endl;
			cout << "Detailed matrix:" << endl;
			output(matrix, m, n);
			break;
		}
		case 5:
		{
			solvingLinearEquation();
			break;
		}
		case 6:
			exit(0);
		}
	}
}