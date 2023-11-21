#include "MatrixTest.h"

#include "Matrix.h"
#include "Matrix4x4.h"


void MatrixTest::testMatrixAddition()
{
    Matrix m = Matrix(Vector(1, 2, 3), Vector(4, 5, 6), Vector(7, 8, 9));
    Matrix m2 = Matrix(Vector(1, 2, 3), Vector(4, 5, 6), Vector(7, 8, 9));
    auto result = m + m2;

    // (1+1, 2+2, 3+3) = (2, 4, 6), (4+4, 5+5, 6+6) = (8, 10, 12), (7+7, 8+8, 9+9) = (14, 16, 18)
    if (result != Matrix(Vector(2, 4, 6), Vector(8, 10, 12), Vector(14, 16, 18)))
    {
        std::cout << "Error in MatrixTest::testMatrixAddition()" << std::endl;
    }
}

void MatrixTest::testMatrixSubtraction()
{
    Matrix m = Matrix(Vector(1, 2, 3), Vector(4, 5, 6), Vector(7, 8, 9));
    Matrix m2 = Matrix(Vector(1, 2, 3), Vector(4, 5, 6), Vector(7, 8, 9));
    auto result = m - m2;

    // (1-1, 2-2, 3-3) = (0, 0, 0), (4-4, 5-5, 6-6) = (0, 0, 0), (7-7, 8-8, 9-9) = (0, 0, 0)
    if (result != Matrix(Vector::zero(), Vector::zero(), Vector::zero()))
    {
        std::cout << "Error in MatrixTest::testMatrixSubtraction()" << std::endl;
    }
}

void MatrixTest::testMatrixMultiplication()
{
    Matrix m = Matrix(Vector(1, 2, 3), Vector(4, 5, 6), Vector(7, 8, 9));
    Matrix m2 = Matrix(Vector(1, 2, 3), Vector(4, 5, 6), Vector(7, 8, 9));
    auto result = m * m2;

    // (1x1+2x4+3x7, 1x2+2x5+3x8, 1x3+2x6+3x9) = (30, 36, 42), (4x1+5x4+6x7, 4x2+5x5+6x8, 4x3+5x6+6x9) = (66, 81, 96), (7x1+8x4+9x7, 7x2+8x5+9x8, 7x3+8x6+9x9) = (102, 126, 150)
    if (result != Matrix(Vector(30, 36, 42), Vector(66, 81, 96), Vector(102, 126, 150)))
    {
        std::cout << "Error in MatrixTest::testMatrixMultiplication()" << std::endl;
    }
}

void MatrixTest::testMatrixMultiplicationByVector()
{
    Matrix m = Matrix(Vector(1, 2, 3), Vector(4, 5, 6), Vector(7, 8, 9));
    auto result = m * Vector(1,2,3);

    // (1x1 + 2x2 + 3x3) = 14, (4x1 + 5x2 + 6x3) = 32, (7x1 + 8x2 + 9x3) = 50
    if (result != Vector(14,32,50))
    {
        std::cout << "Error in MatrixTest::testMatrixMultiplicationByVector()" << std::endl;
    }
}

void MatrixTest::testMatrixMultiplicationByScalar()
{
    Matrix m = Matrix(Vector(1, 2, 3), Vector(4, 5, 6), Vector(7, 8, 9));
    auto result = m * 2;

    // (1x2, 2x2, 3x2) = (2, 4, 6), (4x2, 5x2, 6x2) = (8, 10, 12), (7x2, 8x2, 9x2) = (14, 16, 18)
    if (result != Matrix(Vector(2, 4, 6), Vector(8, 10, 12), Vector(14, 16, 18)))
    {
        std::cout << "Error in MatrixTest::testMatrixMultiplicationByScalar()" << std::endl;
    }
}

void MatrixTest::testMatrixInverse()
{
    Vector v0;

    Matrix m1(Vector(1, 0, 0), Vector(0, 1, 0), Vector(0, 0, 1));
    Matrix m2(Vector(1, 2, 1), Vector(-4, 0, 2), Vector(5, 4, -2));
    Matrix m3(v0, v0, v0);
    auto result1 = m1.inverse();
    auto result2 = m2.inverse();

    auto test1_1 = result1 * m1 - m1;
    auto test1_2 = m1 * result1 - m1;
    auto test2_1 = result2 * m2 - m1;
    auto test2_2 = m2 * result2 - m1;

    float epsilon = 0.0001f;

    if ((test1_1.l1.magnitude() > epsilon) || (test1_1.l2.magnitude() > epsilon) || (test1_1.l3.magnitude() > epsilon)
        || (test1_2.l1.magnitude() > epsilon) || (test1_2.l2.magnitude() > epsilon) || (test1_2.l3.magnitude() >
            epsilon) ||
        (test2_1.l1.magnitude() > epsilon) || (test2_1.l2.magnitude() > epsilon) || (test2_1.l3.magnitude() > epsilon)
        || (test2_2.l1.magnitude() > epsilon) || (test2_2.l2.magnitude() > epsilon) || (test2_2.l3.magnitude() >
            epsilon))
    {
        std::cout << "Error in MatrixTest::testMatrixInverse()" << std::endl;
    }
    try
    {
        m3.inverse();
        // If this is printed, the test is failed
        std::cout << "Error in MatrixTest::testMatrixInverse()" << std::endl;
    }
    catch (const std::runtime_error& e)
    {
        // If we get there, the test is successful
    }
}

void MatrixTest::testMatrixTranspose()
{
    Matrix m = Matrix(Vector(1, 2, 3), Vector(4, 5, 6), Vector(7, 8, 9));
    auto result = m.transpose();

    if (result != Matrix(Vector(1, 4, 7), Vector(2, 5, 8), Vector(3, 6, 9)))
    {
        std::cout << "Error in MatrixTest::testMatrixTranspose()" << std::endl;
    }
}

void MatrixTest::testMatrixDeterminant()
{
    Matrix m = Matrix(Vector(1, 2, 3), Vector(4, 5, 6), Vector(7, 8, 9));
    auto result = m.determinant();

    if (result != 0)
    {
        std::cout << "Error in MatrixTest::testMatrixDeterminant()" << std::endl;
    }
}

void MatrixTest::testMatrix4x4Addition()
{
    Matrix4x4 m = Matrix4x4(Vector(1, 2, 3, 4), Vector(5, 6, 7, 8), Vector(9, 10, 11, 12), Vector(13, 14, 15, 16));
    Matrix4x4 m2 = Matrix4x4(Vector(1, 2, 3, 4), Vector(5, 6, 7, 8), Vector(9, 10, 11, 12), Vector(13, 14, 15, 16));
    auto result = m + m2;

    // (1+1, 2+2, 3+3, 4+4) = (2, 4, 6, 8), (5+5, 6+6, 7+7, 8+8) = (10, 12, 14, 16), (9+9, 10+10, 11+11, 12+12) = (18, 20, 22, 24), (13+13, 14+14, 15+15, 16+16) = (26, 28, 30, 32)
    if (result != Matrix4x4(Vector(2, 4, 6, 8), Vector(10, 12, 14, 16), Vector(18, 20, 22, 24), Vector(26, 28, 30, 32)))
    {
        std::cout << "Error in MatrixTest::testMatrix4x4Addition()" << std::endl;
    }
}

void MatrixTest::testMatrix4x4Subtraction()
{
    Matrix4x4 m = Matrix4x4(Vector(1, 2, 3, 4), Vector(5, 6, 7, 8), Vector(9, 10, 11, 12), Vector(13, 14, 15, 16));
    Matrix4x4 m2 = Matrix4x4(Vector(1, 2, 3, 4), Vector(5, 6, 7, 8), Vector(9, 10, 11, 12), Vector(13, 14, 15, 16));
    auto result = m - m2;

    // (1-1, 2-2, 3-3, 4-4) = (0, 0, 0, 0), (5-5, 6-6, 7-7, 8-8) = (0, 0, 0, 0), (9-9, 10-10, 11-11, 12-12) = (0, 0, 0, 0), (13-13, 14-14, 15-15, 16-16) = (0, 0, 0, 0)
    if (result != Matrix4x4(Vector::zero(), Vector::zero(), Vector::zero(), Vector::zero()))
    {
        std::cout << "Error in MatrixTest::testMatrix4x4Subtraction()" << std::endl;
    }
}

void MatrixTest::testMatrix4x4Multiplication()
{
    Matrix4x4 m = Matrix4x4(Vector(1, 2, 3, 4), Vector(5, 6, 7, 8), Vector(9, 10, 11, 12), Vector(13, 14, 15, 16));
    Matrix4x4 m2 = Matrix4x4(Vector(1, 2, 3, 4), Vector(5, 6, 7, 8), Vector(9, 10, 11, 12), Vector(13, 14, 15, 16));
    auto result = m * m2;

    // (1x1+2x5+3x9+4x13, 1x2+2x6+3x10+4x14, 1x3+2x7+3x11+4x15, 1x4+2x8+3x12+4x16) = (90, 100, 110, 120), (5x1+6x5+7x9+8x13, 5x2+6x6+7x10+8x14, 5x3+6x7+7x11+8x15, 5x4+6x8+7x12+8x16) = (202, 228, 254, 280), (9x1+10x5+11x9+12x13, 9x2+10x6+11x10+12x14, 9x3+10x7+11x11+12x15, 9x4+10x8+11x12+12x16) = (314, 356, 398, 440), (13x1+14x5+15x9+16x13, 13x2+14x6+15x10+16x14, 13x3+14x7+15x11+16x15, 13x4+14x8+15x12+16x16) = (426, 484, 542, 600)
    if (result != Matrix4x4(Vector(90, 100, 110, 120), Vector(202, 228, 254, 280), Vector(314, 356, 398, 440),
                            Vector(426, 484, 542, 600)))
    {
        std::cout << "Error in MatrixTest::testMatrix4x4Multiplication()" << std::endl;
    }
}

void MatrixTest::testMatrix4x4MultiplicationByScalar()
{
    Matrix4x4 m = Matrix4x4(Vector(1, 2, 3, 4), Vector(5, 6, 7, 8), Vector(9, 10, 11, 12), Vector(13, 14, 15, 16));
    auto result = m * 2;

    // (1x2, 2x2, 3x2, 4x2) = (2, 4, 6, 8), (5x2, 6x2, 7x2, 8x2) = (10, 12, 14, 16), (9x2, 10x2, 11x2, 12x2) = (18, 20, 22, 24), (13x2, 14x2, 15x2, 16x2) = (26, 28, 30, 32)
    if (result != Matrix4x4(Vector(2, 4, 6, 8), Vector(10, 12, 14, 16), Vector(18, 20, 22, 24), Vector(26, 28, 30, 32)))
    {
        std::cout << "Error in MatrixTest::testMatrix4x4MultiplicationByScalar()" << std::endl;
    }
}
