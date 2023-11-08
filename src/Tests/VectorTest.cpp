#include "VectorTest.h"

void VectorTest::testScalarProduct()
{
    Vector v1 = Vector(1, 2, 3);
    Vector v2 = Vector(4, 5, 6);
    auto result = v1 * v2;
    
    Vector v3 = Vector(1, 1, 1);
    Vector v4 = Vector(0, 0, 0);
    auto resultNull = v3 * v4;
    
    // 1x4+2x5+3x6 = 32
    if (result != 32 || resultNull != 0)
    {
        std::cout << "Error in VectorTest::testScalarProduct()" << std::endl;
    }
}

void VectorTest::testVectorialProduct()
{
    Vector v1 = Vector(1, 2, 3);
    Vector v2 = Vector(4, 5, 6);
    auto result = v1.vectorialProduct(v2);
    
    Vector v3 = v1;
    auto resultNull = v1.vectorialProduct(v3);
    
    // (2x6-3x5, 3x4-1x6, 1x5-2x4) = (-3, 6, -3)
    if (result != Vector(-3, 6, -3) || resultNull != Vector::zero())
    {
        std::cout << "Error in VectorTest::testVectorialProduct()" << std::endl;
    }
}

void VectorTest::testProjection()
{
    Vector v1 = Vector(1, 0, 0);
    Vector v2 = Vector(4, 5, 6);
    auto result = v2.projection(v1);

    if (result != Vector(4, 0, 0))
    {
        std::cout << "Error in VectorTest::testProjection()" << std::endl;
    }
}
