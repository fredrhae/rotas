// test_rotas.cpp : Defines the entry point for the console application.
//

#include "gtest/gtest.h"

TEST(testValidacao, validacaoTrivial)
{
	EXPECT_EQ(1000, 10*10*10);
}