// g++ -o result cofactorsimple.cpp

//https://cplusplus.com/forum/beginner/25439/

#include <iostream>
using namespace std;

int cofactor(int data[][3],int x,int y)
{
    int cofactor_v;

    cofactor_v = data[(x + 1) % 3][(y + 1) % 3]
        * data[(x + 2) % 3][(y + 2) % 3]
        - data[(x + 1) % 3][(y + 2) % 3]
        * data[(x + 2) % 3][(y + 1) % 3];

    return cofactor_v;
}

int main()
{
    int matrix[3][3]={
        1,2,3,
        1,3,2,
        3,2,1};

    cout << cofactor(matrix,0,0) << endl;
    //      [3   2]
    //det ( [     ] ) = 3*1 - 2*2 = -1
    //      [2   1]

    cout << cofactor(matrix,1,1) << endl;
    //      [1   3]
    //det ( [     ] ) = 1*1 - 3*3 = -8
    //      [3   1]

    cout << cofactor(matrix,0,2) << endl;
    //      [1   3]
    //det ( [     ] ) = 1*2 - 3*3 = -7
    //      [3   2]

    cout << "\nhit enter to quit..." << endl;
    cin.get();
    return 0;
}
