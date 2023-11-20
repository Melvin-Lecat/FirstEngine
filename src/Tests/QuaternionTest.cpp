#include "QuaternionTest.h"

#include "Quaternion.h"


void QuaternionTest::testQuaternionAddition()
{
    Quaternion q1 = Quaternion(1, 2, 3, 4);
    Quaternion q2 = Quaternion(5, 6, 7, 8);
    auto result = q1 + q2;

    // (1+5, 2+6, 3+7, 4+8) = (6, 8, 10, 12)
    if (result != Quaternion(6, 8, 10, 12))
    {
        std::cout << "Error in QuaternionTest::testQuaternionAddition()" << std::endl;
    }
}

void QuaternionTest::testQuaternionMultiplication()
{
    Quaternion q1 = Quaternion(1, 2, 3, 4);
    Quaternion q2 = Quaternion(5, 6, 7, 8);
    auto result = q1 * q2;

    // (1*5-2*6-3*7-4*8, 1*6+2*5+3*8-4*7, 1*7-2*8+3*5+4*6, 1*8+2*7-3*6+4*5) = (-60, 12, 30, 24)
    if (result != Quaternion(-60, 12, 30, 24))
    {
        std::cout << "Error in QuaternionTest::testQuaternionMultiplication()" << std::endl;
    }
}

void QuaternionTest::testQuaternionMultiplicationByScalar()
{
    Quaternion q1 = Quaternion(1, 2, 3, 4);
    auto result = q1 * 2;

    // (1*2, 2*2, 3*2, 4*2) = (2, 4, 6, 8)
    if (result != Quaternion(2, 4, 6, 8))
    {
        std::cout << "Error in QuaternionTest::testQuaternionMultiplicationByScalar()" << std::endl;
    }
}

void QuaternionTest::testQuaternionDivision()
{
    Quaternion q1 = Quaternion(1, 2, 3, 4);
    auto result = q1 / 2;

    if (result != Quaternion(0.5, 1, 1.5, 2))
    {
        std::cout << "Error in QuaternionTest::testQuaternionDivision()" << std::endl;
    }
    try
    {
        auto resultErr = q1 / 0;
        // If this is printed, the test is failed
        std::cout << "Error in QuaternionTest::testQuaternionDivision()" << std::endl;
    }
    catch (invalid_argument e)
    {
        // If we get here, the test is successful
    }
}

void QuaternionTest::testQuaternionDifference()
{
    Quaternion q1 = Quaternion(1, 2, 3, 4);
    Quaternion q2 = Quaternion(5, 6, 7, 8);
    auto result = q1.difference(q2);

    // Result calculated on line
    if (result != Quaternion(70, -8, 0, -16))
    {
        std::cout << "Error in QuaternionTest::testQuaternionDifference()" << std::endl;
    }
}

void QuaternionTest::testQuaternionNormalize()
{
    Quaternion q1 = Quaternion(1, 0, 0, 0);
    auto result = q1.normalize();

    if (result != Quaternion(1, 0, 0, 0))
    {
        std::cout << "Error in QuaternionTest::testQuaternionNormalize()" << std::endl;
    }
}

void QuaternionTest::testQuaternionInverse()
{
    Quaternion q1 = Quaternion(1, 0, 0, 0);
    auto result = q1.inverse();

    if (result != Quaternion(1, 0, 0, 0))
    {
        std::cout << "Error in QuaternionTest::testQuaternionInverse()" << std::endl;
    }
}

void QuaternionTest::testQuaternionScalarProduct()
{
    Quaternion q1 = Quaternion(1, 2, 3, 4);
    Quaternion q2 = Quaternion(5, 6, 7, 8);
    auto result = q1.scalarProduct(q2);

    // 1*5+2*6+3*7+4*8 = 70
    if (result != 70)
    {
        std::cout << "Error in QuaternionTest::testQuaternionScalarProduct()" << std::endl;
    }
}

void QuaternionTest::testQuaternionApplyRotation()
{
    Quaternion q1 = Quaternion(1, 0, 0, 0);
    Vector v1 = Vector(1, 0, 0);
    Quaternion q2 = Quaternion(0, 1, 0, 0);
    auto result = q1.applyRotation(v1, q2);

    if (result != Vector(1, 0, 0))
    {
        std::cout << "Error in QuaternionTest::testQuaternionApplyRotation()" << std::endl;
    }
}

void QuaternionTest::testQuaternionToMatrix()
{
    Quaternion q = Quaternion(1, 2, 3, 4);
    auto result = q.quatToMat();
    // Calculated manually
    Matrix expected = Matrix(Vector(-49, 20,10), Vector(4, -39, 28), Vector(22, 20, -25));

    if (result != expected)
    {
        std::cout << "Error in QuaternionTest::testQuaternionToMatrix()" << std::endl;
    }
}
