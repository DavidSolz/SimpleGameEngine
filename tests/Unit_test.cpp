#include "gtest/gtest.h"
#include "Vector2.h"

TEST(VectorsTest, Addition) {

    Vector2 v1(1,1);
    Vector2 v2(0,1);

    Vector2 sum = v1+v2;

    Vector2 solution(1,2);

    ASSERT_EQ(sum==solution, true);
}

TEST(VectorsTest, Substraction) {

    Vector2 v1(1,1);
    Vector2 v2(0,1);

    Vector2 sum = v1-v2;

    Vector2 solution(1,0);

    ASSERT_EQ(sum==solution, true);
}

TEST(VectorsTest, Dot_Product) {

    Vector2 v1(1,1);
    Vector2 v2(1,1);

    float dotProduct = Vector2::Dot(v1,v2);

    float solution = 2.0f;

    ASSERT_EQ(dotProduct, solution);
}

TEST(VectorsTest, Magnitude) {

    Vector2 v1(3,4);

    float magnitude = v1.Magnitude();

    float solution = 5.0f;

    ASSERT_EQ(magnitude, solution);
}

TEST(VectorsTest, LengthComparison) {

    Vector2 v1(3,4);

    Vector2 v2(4,3);

    ASSERT_EQ(v1.sqrMagnitude(), v2.sqrMagnitude());
}

TEST(VectorsTest, LinearInterpolation) {

    Vector2 v1(0,0);

    Vector2 v2(0,1);

    Vector2 v3 = Vector2::Lerp(v1,v2,0.5f);

    Vector2 solution(0, 0.5f);

    ASSERT_TRUE(v3==solution);
}


