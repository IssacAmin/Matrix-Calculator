#include <iostream>
#include <cmath>
#include <climits>

using namespace std;

// Functions Prototypes
bool checkDimensions1(int mat_1row, int mat_1col, int mat_2row, int mat_2col);
long Determinant(int *matrixPointers[], int matrixSize);
void multiply(int *matrixAPointer[], int *matrixBPointer[], long *resultPointer[], int matA_rows, int matA_columns, int matB_rows,int matB_columns);
void cofactor(int *matrixPointer[], long *cofactorPointer[] , int matrixSize);
void transpose(long *cofactorPointer[], long *transposePointer[], int matrixSize);
void inverse(long *transposePointer[], int *matrixB_pointer[], float *inverse_pointer[], int matrixSize);
void Division(int *matrixAPointer[], float *matrixBPointer[], long *resultPointer[], int matA_rows, int matA_columns, int matB_rows,int matB_columns);


int main()
{
     // get Matrix A dimensions and initialize 2-D array.
    cout<<"Please enter dimensions of Matrix A:"<<endl;
    int matA_rows, matA_columns;
    cin>>matA_rows;
    cin>>matA_columns;
    int MatrixA[matA_rows][matA_columns] = {};

    // declaring pointer to each row
    int *MatrixA_pointers[matA_rows] = {};
    for(int i = 0; i < matA_rows; i++)
    {
        MatrixA_pointers[i] = &MatrixA[i][0];
    }


    // get Matrix B dimensions and initialize 2-D array.
    cout<<"Please enter dimensions of Matrix B:"<<endl;
    int matB_rows, matB_columns;
    cin>>matB_rows;
    cin>>matB_columns;
    int MatrixB[matB_rows][matB_columns] = {};

    // declaring array of pointer to each row
    int *MatrixB_pointers[matB_rows] = {};
    for(int i = 0; i < matB_rows; i++)
    {
        MatrixB_pointers[i] = &MatrixB[i][0];
    }

    //get Matrix A values.
    cout<<"Please enter values of Matrix A:"<<endl;
    for(int i = 0; i < matA_rows; i++)
    {
        for(int j = 0; j < matA_columns; j++)
        {
            cin>>MatrixA[i][j];
        }
    }

    //get Matrix B values.
    cout<<"Please enter values of Matrix B:"<<endl;
    for(int i = 0; i < matB_rows; i++)
    {
        for(int j = 0; j < matB_columns; j++)
        {
            cin>>MatrixB[i][j];
        }
    }


    bool on = true;
    while(on)
    {
        int operation = 0;
        // Validate the User input or re-prompting for valid operation.
        do
        {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout<<"Please choose operation type(1: A+B, 2: A-B, 3: AxB, 4: A*inverse(B), 5: |A|, 6: |B|, 7: quit):"<<endl;
            cin>>operation;
        }while(cin.fail() || operation > 7 || operation < 1);

        // declaring the end result matrices of different Operations.
        // and initiating array of pointers for each matrix.
        int addResult[matA_rows][matA_columns] = {};
        int subtractResult[matA_rows][matA_columns] ={};

        long MultiplicationMatrix[matA_rows][matB_columns] = {};

        long *MultiplicationMatrix_pointers[matA_rows] = {};
        for(int i = 0; i < matA_rows; i++)
        {
            MultiplicationMatrix_pointers[i] = &MultiplicationMatrix[i][0];
        }

        float InverseMatrix[matB_rows][matB_columns] = {};

        float *InverseMatrix_pointers[matB_rows] = {};
        for(int i = 0; i < matB_rows; i++)
        {
            InverseMatrix_pointers[i] = &InverseMatrix[i][0];
        }

        long cofactorMatrix[matB_rows][matB_columns] = {};

        long *cofactorMatrix_pointers[matB_rows] = {};
        for(int i = 0; i < matB_rows; i++)
        {
            cofactorMatrix_pointers[i] = &cofactorMatrix[i][0];
        }

        long transposeMatrix[matB_rows][matB_columns] = {};

        long *transposeMatrix_pointers[matB_rows] = {};
        for(int i = 0; i < matB_rows; i++)
        {
            transposeMatrix_pointers[i] = &transposeMatrix[i][0];
        }

        switch(operation)
        {
            case 1:
                // Addition Operation.
                if(checkDimensions1(matA_rows,matA_columns, matB_rows, matB_columns))
                {
                    for(int i = 0; i < matA_rows; i++)
                    {
                        for(int j = 0; j < matA_columns; j++)
                        {
                            addResult[i][j] = MatrixA[i][j] + MatrixB[i][j];
                        }
                    }
                    // printing the result.
                    for(int i = 0; i < matA_rows; i++)
                    {
                        for(int j = 0; j < matA_columns; j++)
                        {
                            cout<<addResult[i][j]<<" ";
                        }
                        cout<<endl;
                    }

                }
                else
                {
                    cout<<"The operation you chose is invalid for the given matrices."<<endl;
                }

                break;
            case 2:
               if(checkDimensions1(matA_rows,matA_columns, matB_rows, matB_columns))
                {
                    for(int i = 0; i < matA_rows; i++)
                    {
                        for(int j = 0; j < matA_columns; j++)
                        {
                            subtractResult[i][j] = MatrixA[i][j] - MatrixB[i][j];
                        }
                    }

                    //printing the result.
                    for(int i = 0; i < matA_rows; i++)
                    {
                        for(int j = 0; j < matA_columns; j++)
                        {
                            cout<<subtractResult[i][j]<<" ";
                        }
                        cout<<endl;
                    }
                }
                else
                {
                    cout<<"The operation you chose is invalid for the given matrices."<<endl;
                }
                break;
            case 3:
                multiply(MatrixA_pointers, MatrixB_pointers,MultiplicationMatrix_pointers,matA_rows, matA_columns, matB_rows, matB_columns);
                break;
            case 4:
                if(matB_rows == matB_columns && Determinant(MatrixB_pointers, matB_rows) != 0)
                {
                    cofactor(MatrixB_pointers, cofactorMatrix_pointers, matB_rows);
                    transpose(cofactorMatrix_pointers, transposeMatrix_pointers, matB_rows);
                    inverse(transposeMatrix_pointers, MatrixB_pointers, InverseMatrix_pointers, matB_rows);
                    Division(MatrixA_pointers,InverseMatrix_pointers, MultiplicationMatrix_pointers, matA_rows, matA_columns, matB_rows, matB_columns);
                }
                else
                {
                    cout<<"The operation you chose is invalid for the given matrices."<<endl;
                }


                break;
            // Calculating determinant of both A & B.
            case 5:
                //checking if the matrix is square matrix.
                if(matA_rows == matA_columns && matA_rows != 0)
                {
                    long result = Determinant(MatrixA_pointers, matA_columns);
                    cout<<result<<endl;
                }
                else
                {
                    cout<<"The operation you chose is invalid for the given matrices."<<endl;
                }
                break;
            case 6:
                if(matB_rows == matB_columns && matB_rows != 0)
                {
                    long result = Determinant(MatrixB_pointers, matB_columns);
                    cout<<result<<endl;
                }
                else
                {
                    cout<<"The operation you chose is invalid for the given matrices."<<endl;
                }
                break;
            case 7:
                cout<<"Thank you!"<<endl;
                return 0;
                break;
        }
    }
}

// function Implementations

// checking dimensions for additions and subtractions only.
bool checkDimensions1(int mat_1row, int mat_1col, int mat_2row, int mat_2col)
{
    if(mat_1row == mat_2row && mat_1col == mat_2col)
        return true;
    else
        return false;
}

long Determinant(int *matrixPointers[], int matrixSize)
{
        long result= 0;
    int tmpMatrix[matrixSize - 1][matrixSize - 1];

    int *tmpMatrixPointers[matrixSize - 1] = {};
        for(int i = 0; i < matrixSize - 1; i++)
        {
            tmpMatrixPointers[i] = &tmpMatrix[i][0];
        }


    // Terminal cases for recursion.
    if (matrixSize == 1)
        return matrixPointers[0][0];
    else if (matrixSize == 2)
        return ((matrixPointers[0][0] * matrixPointers[1][1]) - (matrixPointers[1][0] * matrixPointers[0][1]));

    // getting tmpMatrix for recursion.
    else
    {
        int sign = 1;
        for(int i = 0; i < matrixSize; i++)
        {
            int tmpX = 0;
            for(int j = 1; j < matrixSize; j++)
            {
                int tmpY = 0;
                int k = 0;
                while(k < matrixSize)
                {
                    //skipping current row.
                    if(k == i)
                    {
                        k += 1;
                        continue;
                    }
                    else
                    {
                        tmpMatrix[tmpX][tmpY] = matrixPointers[j][k];
                        tmpY += 1;
                        k += 1;
                    }
                }
                tmpX += 1;
            }
            //recursion process.
            result += (sign * matrixPointers[0][i] * Determinant(tmpMatrixPointers, matrixSize - 1));
            //transversing sign.
            sign = sign * -1;
        }
    }

        return result;
}

// multiplication operation.
void multiply(int *matrixAPointer[], int *matrixBPointer[], long *resultPointer[], int matA_rows, int matA_columns, int matB_rows,int matB_columns)
{
    //checking if the dimensions are valid for multiplication.
    if(matA_columns != matB_rows)
        cout<<"The operation you chose is invalid for the given matrices."<<endl;
    else
    {
        for(int k = 0; k < matB_columns;k++)
        {
            for(int i = 0; i < matA_rows; i++)
            {
                long element = 0;
                for(int j = 0; j < matA_columns; j++)
                {
                    element = element + matrixAPointer[i][j] * matrixBPointer[j][k];
                }
                //cout<<element<<" ";
                resultPointer[i][k] = element;
            }
        }

        // printing the result matrix.
        for(int i = 0; i < matA_rows; i++)
        {
            for(int j = 0; j < matB_columns;j++)
            {

                cout<<resultPointer[i][j]<<" ";
            }
            cout<<endl;
        }
    }
}

void cofactor(int *matrixPointer[], long *cofactorPointer[] , int matrixSize)
{

    long element = 0;
    int tmpMatrix[matrixSize - 1][matrixSize - 1];

    // getting tmpMatrix to calculate determinant.

    for(int i = 0; i < matrixSize; i++)
    {
        for(int j = 0; j < matrixSize; j++)
        {
            int tmpX = 0;
            for(int k = 0; k < matrixSize; k++)
            {
                int tmpY = 0;
                if (k == i)
                    continue;
                for(int l = 0; l < matrixSize; l++)
                {
                    if(l == j)
                        continue;
                    tmpMatrix[tmpX][tmpY] = matrixPointer[k][l];
                    tmpY++;
                }
                tmpX++;
            }
            int *tmpMatrixPointer[matrixSize - 1] = {};
            for(int i = 0; i < matrixSize - 1; i++)
            {
               tmpMatrixPointer[i] = &tmpMatrix[i][0];
            }

            element = Determinant(tmpMatrixPointer, matrixSize - 1);
            //cout<<element<<" ";
            if( (i + j) % 2 == 0 )
                cofactorPointer[i][j] = element;
            else
                cofactorPointer[i][j] = -element;
        }
    }
}

//transposing the cofactor
void transpose(long *cofactorPointer[], long *transposePointer[], int matrixSize)
{
         for(int i  = 0; i < matrixSize; i++)
            {
                for (int j = 0; j < matrixSize ; j++)
                {

                    transposePointer[j][i] = cofactorPointer[i][j];
                }
            }
}

// multiplying transpose with 1 / determinant.
void inverse(long *transposePointer[], int *matrixB_pointer[], float *inverse_pointer[], int matrixSize)
{
    float constant = 1.0 / (float)Determinant(matrixB_pointer, matrixSize);

    for(int i = 0; i < matrixSize; i++)
    {
        for (int j = 0; j < matrixSize; j++)
        {
            inverse_pointer[i][j] = (float) transposePointer[i][j] * constant;
        }
    }
}

void Division(int *matrixAPointer[], float *matrixBPointer[], long *resultPointer[], int matA_rows, int matA_columns, int matB_rows,int matB_columns)
{
    //checking if the dimensions are valid for multiplication.
    if(matA_columns != matB_rows)
        cout<<"The operation you chose is invalid for the given matrices."<<endl;
    else
    {
        int counter = 0;
        for(int k = 0; k < matB_columns;k++)
        {
            for(int i = 0; i < matA_rows; i++)
            {
                float element = 0;
                for(int j = 0; j < matA_columns; j++)
                {
                    element = element + (float)matrixAPointer[i][j] * matrixBPointer[j][counter];
                }
                //cout<<element<<" ";
                if(round(element) != -0)
                {
                    resultPointer[i][k] = round(element);
                }
                else
                    resultPointer[i][k] = 0;

            }
            counter++;
        }

        // printing the result matrix.
        for(int i = 0; i < matA_rows; i++)
        {
            for(int j = 0; j < matB_columns;j++)
            {

                cout<<resultPointer[i][j]<<" ";
            }
            cout<<endl;
        }
    }
}
