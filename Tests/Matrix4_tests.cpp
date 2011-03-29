#define BOOST_TEST_MODULE Math Tests
#include <boost/test/unit_test.hpp>

#include <Math/Matrix4.h>

BOOST_AUTO_TEST_SUITE(Matrix4TestSuite)

struct MatrixFixture
{
	Matrix4 a;
	Matrix4 b;
	Matrix4 c;

	MatrixFixture()
	{
		a = Matrix4(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);
		b = Matrix4(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);
		c = Matrix4(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16);
	}
};

BOOST_FIXTURE_TEST_CASE(equal_test, MatrixFixture)
{
	BOOST_CHECK(a == b);
}

BOOST_FIXTURE_TEST_CASE(not_equal_test, MatrixFixture)
{
	BOOST_CHECK(a != c);
}

BOOST_AUTO_TEST_CASE(identity_test)
{
	BOOST_CHECK(Matrix4::Identity() == Matrix4(1,0,0,0,
											   0,1,0,0,
											   0,0,1,0,
											   0,0,0,1));
}

BOOST_AUTO_TEST_CASE(zero_test)
{
	BOOST_CHECK(Matrix4::Zero() == Matrix4());
}

BOOST_FIXTURE_TEST_CASE(access1_test, MatrixFixture)
{
	BOOST_CHECK_EQUAL(c(0,0), 1);
}

BOOST_FIXTURE_TEST_CASE(access2_test, MatrixFixture)
{
	BOOST_CHECK_EQUAL(c[0][0], 1);
}

BOOST_FIXTURE_TEST_CASE(multiplication_test, MatrixFixture)
{
	BOOST_CHECK(a * c == Matrix4(1,0,0,0,
								 0,1,0,0,
								 0,0,1,0,
								 0,0,0,1));
}

BOOST_AUTO_TEST_SUITE_END()
