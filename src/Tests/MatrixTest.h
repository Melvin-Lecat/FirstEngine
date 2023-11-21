#pragma once

class MatrixTest
{
public:

    // Matrix 3x3 tests
    static void testMatrixAddition();
    static void testMatrixSubtraction();
    static void testMatrixMultiplication();
    static void testMatrixMultiplicationByVector();
    static void testMatrixMultiplicationByScalar();
    static void testMatrixInverse();
    static void testMatrixTranspose();
    static void testMatrixDeterminant();

    // Matrix 4x4 tests
    static void testMatrix4x4Addition();
    static void testMatrix4x4Subtraction();
    static void testMatrix4x4Multiplication();
    static void testMatrix4x4MultiplicationByScalar();
};
