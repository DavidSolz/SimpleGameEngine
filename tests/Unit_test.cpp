#include "gtest/gtest.h"
#include "Vectors.h"

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

    float dotProduct = v1.Dot(v2);

    float solution = 2.0f;

    ASSERT_EQ(dotProduct, solution);
}

TEST(VectorsTest, Magnitude) {

    Vector2 v1(3,4);

    float magnitude = v1.Magnitude();

    float solution = 5.0f;

    ASSERT_EQ(magnitude, solution);
}

