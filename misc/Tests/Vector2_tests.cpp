#include <boost/test/unit_test.hpp>
#include <Math/Vector2.h>

BOOST_AUTO_TEST_SUITE(Vector2TestSuite)

struct Vector2Fixture
{
	Vector2 a;
	Vector2 b;

	Vector2Fixture()
	{
		a = Vector2(1, 2);
		b = Vector2(2, 4);
	}
};

BOOST_FIXTURE_TEST_CASE(equal_test, Vector2Fixture)
{
	BOOST_CHECK(a == Vector2(1,2));
}

BOOST_FIXTURE_TEST_CASE(not_equal_test, Vector2Fixture)
{
	BOOST_CHECK(a != b);
}

BOOST_FIXTURE_TEST_CASE(access_test, Vector2Fixture)
{
	BOOST_CHECK_EQUAL(a.GetX(), 1);
	BOOST_CHECK_EQUAL(a.GetY(), 2);
	BOOST_CHECK_EQUAL(b.GetX(), 2);
	BOOST_CHECK_EQUAL(b.GetY(), 4);
}

BOOST_FIXTURE_TEST_CASE(component_assign_test, Vector2Fixture)
{
	a.SetX(2);
	a.SetY(3);
	b.SetX(4);
	b.SetY(5);

	BOOST_CHECK_EQUAL(a.GetX(), 2);
	BOOST_CHECK_EQUAL(a.GetY(), 3);
	BOOST_CHECK_EQUAL(b.GetX(), 4);
	BOOST_CHECK_EQUAL(b.GetY(), 5);
}

BOOST_FIXTURE_TEST_CASE(assign_test, Vector2Fixture)
{
	Vector2 x;
	x = a;
	BOOST_CHECK(x == a);
}

BOOST_FIXTURE_TEST_CASE(multiplication_test, Vector2Fixture)
{
	BOOST_CHECK(a * 2 == Vector2(2, 4));
}

BOOST_FIXTURE_TEST_CASE(division_test, Vector2Fixture)
{
	BOOST_CHECK(b / 2 == Vector2(1, 2));
}

BOOST_FIXTURE_TEST_CASE(multiplication2_test, Vector2Fixture)
{
	a *= 2;
	BOOST_CHECK(a == Vector2(2, 4));
}

BOOST_FIXTURE_TEST_CASE(division2_test, Vector2Fixture)
{
	b /= 2;
	BOOST_CHECK(b == Vector2(1, 2));
}

BOOST_FIXTURE_TEST_CASE(addition_test, Vector2Fixture)
{
	BOOST_CHECK(a + b == Vector2(3, 6));
}

BOOST_FIXTURE_TEST_CASE(subtraction_test, Vector2Fixture)
{
	BOOST_CHECK(a - b == Vector2(-1, -2));
}

BOOST_FIXTURE_TEST_CASE(addition2_test, Vector2Fixture)
{
	a += b;
	BOOST_CHECK(a == Vector2(3, 6));
}

BOOST_FIXTURE_TEST_CASE(subtraction2_test, Vector2Fixture)
{
	a -= b;
	BOOST_CHECK(a == Vector2(-1, -2));
}

BOOST_FIXTURE_TEST_CASE(magnitude_test, Vector2Fixture)
{
	BOOST_CHECK_CLOSE_FRACTION(b.Magnitude(), 4.47f, 0.05f);
}

BOOST_FIXTURE_TEST_CASE(normalize_test, Vector2Fixture)
{
	float mag = b.Magnitude();
	Vector2 normed = b / mag;

	BOOST_CHECK(b.Normalize() == normed);
}

/*BOOST_FIXTURE_TEST_CASE(dorproduct_test, Vector2Fixture)
{
	BOOST_CHECK_CLOSE_FRACTION(b.ScalarProduct(a),  );
}*/

BOOST_AUTO_TEST_SUITE_END()
