#include "pch.h"
#include "Vector.h"

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