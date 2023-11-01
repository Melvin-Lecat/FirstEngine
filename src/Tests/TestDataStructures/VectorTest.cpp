#include "VectorTest.h"

#include "DataStructures/Vector.h"

void VectorTest::run()
{
    testAddition();
}

void VectorTest::testEquality()
{
    Vector v1 = Vector(1, 2, 3);
    Vector v2 = Vector(1, 2, 3);
    assert(v1 == v2);
    cout << "Vector equality test passed" << endl;
}

void VectorTest::testAddition()
{
    Vector v1 = Vector(1, 2, 3);
    Vector v2 = Vector(4, 5, 6);
    Vector v3 = v1 + v2;
    assert(v3 == Vector(5, 7, 9));
    cout << "Vector addition test passed" << endl;
}

void VectorTest::testSubtraction()
{
}

void VectorTest::testScalarProduct()
{
}

void VectorTest::testMultiplicationByScalar()
{
}

void VectorTest::testMagnitude()
{
}

void VectorTest::testSquaredMagnitude()
{
}

void VectorTest::testDistance()
{
}

void VectorTest::testNormalized()
{
}

void VectorTest::testVectorialProduct()
{
}
