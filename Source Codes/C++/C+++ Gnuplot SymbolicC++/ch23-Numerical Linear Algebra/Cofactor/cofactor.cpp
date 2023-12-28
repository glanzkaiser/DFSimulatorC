// g++ -o result cofactor.cpp

#include<iostream>

using namespace std;
void ind_val_out(int mat[][3]);
void ind_val_in(int mat[][3]);
int cofactor(int data[][3],int x,int y);

class matrix_3x3
{ 
	public:
	void in_value(void)
	{
		ind_val_in(data);
	};
	const void out_value(void)
	{
		ind_val_out(data);
	}
	const int getdet(void)
	{
		return det(data);
	}

	private:
	int data[3][3];

	int det(int data[][3])
	{
		int determinant;
		int x,y,z;
		x=data[0][1]*cofactor(data,0,1);
		y=data[0][2]*cofactor(data,0,2);
		z=data[0][3]*cofactor(data,0,3);
		determinant=x+y+z;
		return determinant;
	}
};

void ind_val_out(int mat[][3])
{
	int x(0),y(0),z(0);
	abc:
		cout<<mat[x][y]<<" ";
		cout<<mat[x][y+1]<<" ";
		cout<<mat[x][y+2]<<"\n";
		z++;
	if (z<3)
	{
		x++;
		goto abc;
	}
}

void ind_val_in(int mat[][3])
{
	int x(0),y(0),z(0);
	abc:
		cin>>mat[x][y];
		cin>>mat[x][y+1];
		cin>>mat[x][y+2];
		z++;
	if (z<3)
	{
		x++;
		goto abc;
	}
}

int cofactor(int data[][3],int x,int y)
{
	int cofactor_v;

	cofactor_v = data[(x + 1) % 3][(y + 1) % 3]
	* data[(x + 2) % 3][(y + 2) % 3]
	- data[(x + 1) % 3][(y + 2) % 3]
	* data[(x + 2) % 3][(y + 1) % 3];

	//fix the sign, according to x+y
	int sign=(x+y)%2;
	sign*=-2;
	sign++;

	cofactor_v*=sign;
	if ((x+y)%2==1) 
	{
		cofactor_v*=-1;
	}
	return cofactor_v;
}

int det(int data[][3])
{
	int determinant;
	int x,y,z;
	x=data[0][0]*cofactor(data,0,0);
	y=data[0][1]*cofactor(data,0,1);
	z=data[0][2]*cofactor(data,0,2);
	determinant=x+y+z;
	return determinant;
}

const int N = 3;
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

int main()
{
	//int M[3][3] = {0};
	int r=0, c=0;// cofactor of M
	char repeat = 'n';// user queried to repeat for another case
	
	int M[3][3]={
        1,1,3,
        2,3,2,
        3,2,1};

	do// allows repeat runs and keeps window open so results can be seen
	{
		cout<<"The matrix A is "<<endl;
		display(M,3,3);
		cout << endl;
		cout<<"Enter row for cofactor: ";
		cin >> r;
		cout<<"Enter col for cofactor: ";
		cin >> c;
		cout << "The cofactor is: " << cofactor( M, r, c ) << endl;
		cout << "the determinant is: " << det(M)<< endl;
		cout << endl << "repeat (y/n)? " << flush;
		cin >> repeat;
	}
	while( repeat=='y');
	return 0;
}