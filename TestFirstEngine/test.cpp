#include "gtest/gtest.h"
#include "../src/DataStructures/Vector.h"

using namespace std;

TEST(TestCaseName, TestName)
{
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
  
}

TEST(_VECTOR_, _ADDITION_)
{
    Vector v1 = Vector(1, 2, 3);
    Vector v2 = Vector(4, 5, 6);
    Vector v3 = v1 + v2;
    assert(v3 == Vector(5, 7, 9));
    cout << "Vector addition test passed" << endl;
}