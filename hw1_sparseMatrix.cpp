#include <iostream>
using namespace std;
class matrix {
public:
    void SetEntry(int i, int j, int v);
    int GetEntry(int i, int j); // this is already defined for you.
    int CountNonZero();
    void GetSparseRep();
    int* SparseRow, * SparseCol, * SparseVal;

private:
    int m[3][5];
};
void matrix::SetEntry(int i, int j, int v) {
    m[i][j] = v;
    // assign value v to the row i and column j of matrix "m"
}
int matrix::GetEntry(int i, int j) {
    // this function returns matrix entry at row i and column j
    return m[i][j];
}
int matrix::CountNonZero() {
    int count{0};

    for(int row = 0; row < 3; ++row){
        for(int col = 0; col < 5; ++col){
            if(m[row][col] != 0) {
                ++count;
            }
        }
    }
    return count;
}
void matrix::GetSparseRep() {

    // ------------------------------------------------------
    // generate a sparse representation of matrix "m"
    // ------------------------------------------------------
    // assign results to (SparseRow, SparseCol, SparseVal)
    // use SparseRow to hold row indices
    // use SparseCol to hold column indices
    // use SparseVal to hold entry values
    //
    // For example, if the first non-zero element we find is m[a][b],
    // then SparseRow[0]=a, SparseCol[0]=b, SparseVale[0]=m[a][b].
    // If the second non-zero element we find is m[c][d], then
    // SparseRow[1]=a, SparseCol[1]=b, SparseVale[1]=m[a][b]
    //
    // parts of the code is given to you, please build on them.
    // you can add lines both inside and outside the loop.
    // --------------------------------------------------------
    int size = CountNonZero();
    SparseRow = new int [size];
    SparseCol = new int [size];
    SparseVal = new int [size];

    int index {0};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 5; j++) {
            if (m[i][j] != 0) {
                SparseRow[index] = i;
                SparseCol[index] = j;
                SparseVal[index] = m[i][j];
                ++index;
            }
        }
    }
}
int main()
{
    // The main function is given to you.
    // It first declares a matrix object "x",
    // then inputs the matrix values,
    // then generates the sparse representation
    // of the matrix and finally outputs it.
    // You do not need to modify this function.
    // And please do not modify it or Grade scope
    // may not recognize the format of your input/output.
    matrix x;

    int temp, mode;
    cin >> mode; // this controls what to test
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 5; j++) {
            cin >> temp;
            x.SetEntry(i, j, temp);
        }
    }
    switch (mode) {

        case 1: // test if inputs are correctly assigned

            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 5; j++) {
                    cout << x.GetEntry(i, j) << endl;
                }
            }
            break;

        case 2: // test if CountNonZero() is correct
            cout << x.CountNonZero() << endl;
            break;
        case 3: // test if GetSparseRep() is correct
            x.GetSparseRep();
            for (int i = 0; i < x.CountNonZero(); i++) {
                cout << x.SparseRow[i] << ' ' << x.SparseCol[i] << ' ' <<
                     x.SparseVal[i] << endl;
            }
            break;
    }
    return 0;
}
