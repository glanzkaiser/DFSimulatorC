// g++ -o result main.cpp

#include <iostream>
using namespace std;

const int N = 4;
void cofactor(int mat[N][N], int temp[N][N], int p,int q, int n)
{
	int i = 0, j = 0;
	for (int row = 0; row < n; row++)
	{		
		for (int column = 0; column < n; column++)
		{
			if (row != p && column != q)
			{
				temp[i][j++] = mat[row][column];
				if (j == n - 1)
				{
				j = 0;
				i++;
				}
			}
		}
	}
}

int determinantOfMatrix(int mat[N][N], int dimension)
{
	int Det = 0;

	if (dimension == 1)
		return mat[0][0];

	int cofactorMat[N][N];
	int sign = 1;

	for (int firstRow = 0; firstRow < dimension; firstRow++)
	{
	cofactor(mat, cofactorMat, 0, firstRow, dimension);
	Det += sign * mat[0][firstRow] * determinantOfMatrix(cofactorMat, dimension - 1);
	sign = -sign;
	}
	return Det;
}

void display(int mat[N][N], int row, int col)
{
for (int i = 0; i < row; i++)
	{
	for (int j = 0; j < col; j++)
		cout<<mat[i][j]<<" ";	
		cout<<endl;
	}
	cout<<endl;
}

int main(){
	int mat[4][4] = {
	{ 1, 0, 3, 5},
	{ 5, 5, 6, 6},
	{ 15, 45, 60, 33},	
	{ 17, 18, 7, 9}};

	cout<<"The matrix A is "<<endl;
	display(mat,4,4);
	cout<<"Determinant of the matrix is "<<determinantOfMatrix(mat, N) << endl ;
	return 0;
}