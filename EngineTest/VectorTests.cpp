#include "pch.h"
#include "Vector.h"
#include <numbers>
TEST(VectorTests, DefaultConstrutor)
{
	MaxrEngine::Vector2Df vectorF;
	EXPECT_EQ(0.f, vectorF.x);
	EXPECT_EQ(0.f, vectorF.y);
}

TEST(VectorTests, NonZeroConstructor)
{
	MaxrEngine::Vector2Df vectorF(-1.f, 3.f);
	EXPECT_EQ(-1.f, vectorF.x);
	EXPECT_EQ(3.f, vectorF.y);
}

TEST(VectorTests, Equal)
{
	MaxrEngine::Vector2Df vectorF1(-1.f, 3.f);
	MaxrEngine::Vector2Df vectorF2(3.f, -1.f);
	MaxrEngine::Vector2Df vectorF3(-1.f, 3.f);
	EXPECT_TRUE(vectorF1 == vectorF3);
	EXPECT_TRUE((vectorF2 == vectorF3) == false);
}

TEST(VectorTests, NotEqual)
{
	MaxrEngine::Vector2Df vectorF1(-1.f, 3.f);
	MaxrEngine::Vector2Df vectorF2(3.f, -1.f);
	MaxrEngine::Vector2Df vectorF3(-1.f, 3.f);
	EXPECT_TRUE(vectorF1 != vectorF2);
	EXPECT_TRUE((vectorF1 != vectorF3) == false);
}

TEST(VectorTests, DotProduct)
{
	MaxrEngine::Vector2Df vectorF1(-1.f, 4.f);
	MaxrEngine::Vector2Df vectorF2(-3.f, -5.f);
	float dotProduct1 = MaxrEngine::DotProduct(vectorF1, vectorF2);
	float dotProduct2 = vectorF1.DotProduct(vectorF2);
	EXPECT_EQ(dotProduct1, -17.f);
	EXPECT_EQ(dotProduct2, -17.f);
}

TEST(VectorTests, UnaryMinusOperator)
{
	MaxrEngine::Vector2Df vectorF1(-1.f, 3.f);
	MaxrEngine::Vector2Df vectorF2 = -vectorF1;
	EXPECT_EQ(vectorF2.x, 1.f);
	EXPECT_EQ(vectorF2.y, -3.f);
}

TEST(VectorTests, MinusOperator)
{
	MaxrEngine::Vector2Df vectorF1(-1.f, 4.f);
	MaxrEngine::Vector2Df vectorF2(-3.f, -5.f);
	MaxrEngine::Vector2Df vectorF3 = vectorF1 - vectorF2;
	vectorF1 -= vectorF2;
	EXPECT_EQ(vectorF3.x, 2.f);
	EXPECT_EQ(vectorF3.y, 9.f);
	EXPECT_EQ(vectorF1.x, 2.f);
	EXPECT_EQ(vectorF1.y, 9.f);
}

TEST(VectorTests, PlusOperator)
{
	MaxrEngine::Vector2Df vectorF1(-1.f, 4.f);
	MaxrEngine::Vector2Df vectorF2(-3.f, -5.f);
	MaxrEngine::Vector2Df vectorF3 = vectorF1 + vectorF2;
	vectorF1 += vectorF2;
	EXPECT_EQ(vectorF3.x, -4.f);
	EXPECT_EQ(vectorF3.y, -1.f);
	EXPECT_EQ(vectorF1.x, -4.f);
	EXPECT_EQ(vectorF1.y, -1.f);
}

TEST(VectorTests, ScalarMultiply)
{
	MaxrEngine::Vector2Df vectorF1(-1.f, 4.f);
	MaxrEngine::Vector2Df vectorF2 = vectorF1 * 2.f;
	MaxrEngine::Vector2Df vectorF3 = 3.f * vectorF1;
	vectorF1 *= -3.f;
	EXPECT_EQ(vectorF2.x, -2.f);
	EXPECT_EQ(vectorF2.y, 8.f);
	EXPECT_EQ(vectorF1.x, 3.f);
	EXPECT_EQ(vectorF1.y, -12.f);
	EXPECT_EQ(vectorF3.x, -3.f);
	EXPECT_EQ(vectorF3.y, 12.f);
}

TEST(VectorTests, HadamardMultiply)
{
	MaxrEngine::Vector2Df vectorF1(-1.f, 4.f);
	MaxrEngine::Vector2Df vectorF2(-3.f, -5.f);
	MaxrEngine::Vector2Df vectorF3 = vectorF1 * vectorF2;
	vectorF1 *= vectorF2;
	EXPECT_EQ(vectorF3.x, 3.f);
	EXPECT_EQ(vectorF3.y, -20.f);
	EXPECT_EQ(vectorF1.x, 3.f);
	EXPECT_EQ(vectorF1.y, -20.f);
}

TEST(VectorTests, Angle)
{
	MaxrEngine::Vector2Df vectorF1(1.f, 0.f);
	MaxrEngine::Vector2Df vectorF2(0.f, 1.f);
	MaxrEngine::Vector2Df vectorF3(1.f, 1.f);
	MaxrEngine::Vector2Df vectorF4(1.f, std::numbers::sqrt3_v<float>);
	MaxrEngine::Vector2Df vectorF5(-1.f, 0.f);
	EXPECT_FLOAT_EQ(MaxrEngine::Angle(vectorF1, vectorF1), 0.f);
	EXPECT_FLOAT_EQ(MaxrEngine::Angle(vectorF1, vectorF2), std::numbers::pi_v<float> / 2.f);
	EXPECT_FLOAT_EQ(MaxrEngine::Angle(vectorF1, vectorF3), std::numbers::pi_v<float> / 4.f);
	EXPECT_FLOAT_EQ(MaxrEngine::Angle(vectorF3, vectorF2), std::numbers::pi_v<float> / 4.f);
	EXPECT_FLOAT_EQ(MaxrEngine::Angle(vectorF1, vectorF4), std::numbers::pi_v<float> / 3.f);
	EXPECT_FLOAT_EQ(MaxrEngine::Angle(vectorF2, vectorF4), std::numbers::pi_v<float> / 6.f);
	EXPECT_FLOAT_EQ(MaxrEngine::Angle(vectorF1, vectorF5), std::numbers::pi_v<float>);
}
TEST(VectorTests, AngleDegree)
{
	MaxrEngine::Vector2Df vectorF1(1.f, 0.f);
	MaxrEngine::Vector2Df vectorF2(0.f, 1.f);
	MaxrEngine::Vector2Df vectorF3(1.f, 1.f);
	MaxrEngine::Vector2Df vectorF4(1.f, std::numbers::sqrt3_v<float>);
	MaxrEngine::Vector2Df vectorF5(-1.f, 0.f);
	EXPECT_FLOAT_EQ(MaxrEngine::AngleDegree(vectorF1, vectorF1), 0.f);
	EXPECT_FLOAT_EQ(MaxrEngine::AngleDegree(vectorF1, vectorF2), 90.f);
	EXPECT_FLOAT_EQ(MaxrEngine::AngleDegree(vectorF1, vectorF3), 45.f);
	EXPECT_FLOAT_EQ(MaxrEngine::AngleDegree(vectorF3, vectorF2), 45.f);
	EXPECT_FLOAT_EQ(MaxrEngine::AngleDegree(vectorF1, vectorF4), 60.f);
	EXPECT_FLOAT_EQ(MaxrEngine::AngleDegree(vectorF2, vectorF4), 30.f);
	EXPECT_FLOAT_EQ(MaxrEngine::AngleDegree(vectorF1, vectorF5), 180.f);
}
TEST(VectorTests, Normalize)
{
	MaxrEngine::Vector2Df vectorF1(1.f, 0.f);
	EXPECT_TRUE(MaxrEngine::Normalized(vectorF1) == vectorF1);
	MaxrEngine::Vector2Df vectorF2(10.f, 0.f);
	EXPECT_TRUE(MaxrEngine::Normalized(vectorF2) == vectorF1);
	MaxrEngine::Vector2Df vectorF3(-std::numbers::sqrt2_v<float> / 2.f, std::numbers::sqrt2_v<float> / 2.f);
	MaxrEngine::Vector2Df normalizedF3 = MaxrEngine::Normalized(vectorF3);
	EXPECT_FLOAT_EQ(vectorF3.x, normalizedF3.x);
	EXPECT_FLOAT_EQ(vectorF3.y, normalizedF3.y);
	MaxrEngine::Vector2Df vectorF4(-5.f, 5.f);
	MaxrEngine::Vector2Df normalizedF4 = MaxrEngine::Normalized(vectorF4);
	EXPECT_FLOAT_EQ(vectorF3.x, normalizedF4.x);
	EXPECT_FLOAT_EQ(vectorF3.y, normalizedF4.y);
	MaxrEngine::Vector2Df vectorF5(0.5f, -std::numbers::sqrt3_v<float> / 2.f);
	MaxrEngine::Vector2Df vectorF6(1.f, -std::numbers::sqrt3_v<float>);
	MaxrEngine::Vector2Df normalizedF6 = MaxrEngine::Normalized(vectorF6);
	EXPECT_FLOAT_EQ(vectorF5.x, normalizedF6.x);
	EXPECT_FLOAT_EQ(vectorF5.y, normalizedF6.y);
	MaxrEngine::Vector2Df zeroVector;
	MaxrEngine::Vector2Df normalizedZeroVector = MaxrEngine::Normalized(zeroVector);
	EXPECT_FLOAT_EQ(zeroVector.x, normalizedZeroVector.x);
	EXPECT_FLOAT_EQ(zeroVector.y, normalizedZeroVector.y);
}