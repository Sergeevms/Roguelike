#include "pch.h"

#include "Matrix2D.h"

constexpr float EPS = 1e-7f;
TEST(MatrixTest, DefaultConstructor) {
    MaxrEngine::Matrix2D matrix;
    auto& m = matrix.GetMatrix();
    EXPECT_EQ(m[0][0], 1.f);
    EXPECT_EQ(m[0][1], 0.0F);
    EXPECT_EQ(m[0][2], 0.0F);
    EXPECT_EQ(m[1][0], 0.0F);
    EXPECT_EQ(m[1][1], 1.f);
    EXPECT_EQ(m[1][2], 0.0F);
    EXPECT_EQ(m[2][0], 0.0F);
    EXPECT_EQ(m[2][1], 0.0F);
    EXPECT_EQ(m[2][2], 1.f);
}

TEST(MatrixTest, ValuesConstructor) {
    MaxrEngine::Matrix2D matrix =
        MaxrEngine::Matrix2D(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f);
    auto& m = matrix.GetMatrix();
    EXPECT_EQ(m[0][0], 1.f);
    EXPECT_EQ(m[0][1], 2.f);
    EXPECT_EQ(m[0][2], 3.f);
    EXPECT_EQ(m[1][0], 4.f);
    EXPECT_EQ(m[1][1], 5.f);
    EXPECT_EQ(m[1][2], 6.f);
    EXPECT_EQ(m[2][0], 7.f);
    EXPECT_EQ(m[2][1], 8.f);
    EXPECT_EQ(m[2][2], 9.f);
}

TEST(MatrixTest, MultiplyOperator) {
    MaxrEngine::Matrix2D matrix1 =
        MaxrEngine::Matrix2D(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f);
    MaxrEngine::Matrix2D matrix2 = MaxrEngine::Matrix2D(
        -50.0F, 49.f, 48.f, 47.f, 46.f, -45.f, 44.f, -43.f, 42.f);
    auto matrix = matrix1 * matrix2;
    auto& m = matrix.GetMatrix();
    EXPECT_EQ(m[0][0], 176.f);
    EXPECT_EQ(m[0][1], 12.f);
    EXPECT_EQ(m[0][2], 84.f);
    EXPECT_EQ(m[1][0], 299.f);
    EXPECT_EQ(m[1][1], 168.f);
    EXPECT_EQ(m[1][2], 219.f);
    EXPECT_EQ(m[2][0], 422.f);
    EXPECT_EQ(m[2][1], 324.f);
    EXPECT_EQ(m[2][2], 354.f);
}

TEST(MatrixTest, TransformConstructor) {
    MaxrEngine::Vector2Df zeroVector;
    MaxrEngine::Matrix2D matrix =
        MaxrEngine::Matrix2D(zeroVector, 0.0F, zeroVector);
    auto& nullTransform = matrix.GetMatrix();
    EXPECT_EQ(nullTransform[0][0], 0.0F);
    EXPECT_EQ(nullTransform[0][1], 0.0F);
    EXPECT_EQ(nullTransform[0][2], 0.0F);
    EXPECT_EQ(nullTransform[1][0], 0.0F);
    EXPECT_EQ(nullTransform[1][1], 0.0F);
    EXPECT_EQ(nullTransform[1][2], 0.0F);
    EXPECT_EQ(nullTransform[2][0], 0.0F);
    EXPECT_EQ(nullTransform[2][1], 0.0F);
    EXPECT_EQ(nullTransform[2][2], 1.f);

    matrix = MaxrEngine::Matrix2D({1, 3}, 0.0F, zeroVector);
    auto& positionTransform = matrix.GetMatrix();
    EXPECT_EQ(positionTransform[0][0], 0.0F);
    EXPECT_EQ(positionTransform[0][1], 0.0F);
    EXPECT_EQ(positionTransform[0][2], 1.f);
    EXPECT_EQ(positionTransform[1][0], 0.0F);
    EXPECT_EQ(positionTransform[1][1], 0.0F);
    EXPECT_EQ(positionTransform[1][2], 3.f);
    EXPECT_EQ(positionTransform[2][0], 0.0F);
    EXPECT_EQ(positionTransform[2][1], 0.0F);
    EXPECT_EQ(positionTransform[2][2], 1.f);

    MaxrEngine::Vector2Df oneVector = MaxrEngine::Vector2Df(1.f, 1.f);

    matrix = MaxrEngine::Matrix2D(zeroVector, 90.0F, oneVector);
    auto& angleTransform = matrix.GetMatrix();
    EXPECT_NEAR(angleTransform[0][0], 0.0F, EPS);
    EXPECT_NEAR(angleTransform[0][1], 1.f, EPS);
    EXPECT_NEAR(angleTransform[0][2], 0.0F, EPS);
    EXPECT_NEAR(angleTransform[1][0], -1.f, EPS);
    EXPECT_NEAR(angleTransform[1][1], 0.0F, EPS);
    EXPECT_NEAR(angleTransform[1][2], 0.0F, EPS);
    EXPECT_NEAR(angleTransform[2][0], 0.0F, EPS);
    EXPECT_NEAR(angleTransform[2][1], 0.0F, EPS);
    EXPECT_NEAR(angleTransform[2][2], 1.f, EPS);

    matrix = MaxrEngine::Matrix2D(zeroVector, 0.0F, {2.f, 3.f});
    auto& scaleTransform = matrix.GetMatrix();
    EXPECT_EQ(scaleTransform[0][0], 2.f);
    EXPECT_EQ(scaleTransform[0][1], 0.0F);
    EXPECT_EQ(scaleTransform[0][2], 0.0F);
    EXPECT_EQ(scaleTransform[1][0], 0.0F);
    EXPECT_EQ(scaleTransform[1][1], 3.f);
    EXPECT_EQ(scaleTransform[1][2], 0.0F);
    EXPECT_EQ(scaleTransform[2][0], 0.0F);
    EXPECT_EQ(scaleTransform[2][1], 0.0F);
    EXPECT_EQ(scaleTransform[2][2], 1.f);
}

TEST(MatrixTest, Inversed) {
    MaxrEngine::Matrix2D identytiMatrix;
    auto& identyti = identytiMatrix.GetMatrix();
    auto& reverseIdentyti = identytiMatrix.GetInversed().GetMatrix();
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            EXPECT_EQ(identyti[i][j], reverseIdentyti[i][j]);
        }
    }

    MaxrEngine::Matrix2D someMatrix = MaxrEngine::Matrix2D(
        7.f, 3.f, 10.0F, 37.f, -30.0F, 2.f, 2.f, 19.f, -23.f);

    auto& multiplyResult = (someMatrix * someMatrix.GetInversed()).GetMatrix();

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            EXPECT_NEAR(identyti[i][j], multiplyResult[i][j], EPS);
        }
    }
}