#include <glm/ext/scalar_relational.hpp>
#include <glm/gtc/ulp.hpp>
#include <cmath>

static int test_equal_epsilon()
{
#	if GLM_CONFIG_CONSTEXP == GLM_ENABLE
		static_assert(glm::equal(1.01f, 1.02f, 0.1f), "GLM: Failed constexpr");
		static_assert(!glm::equal(1.01f, 1.02f, 0.001f), "GLM: Failed constexpr");
#	endif
	
	int Error = 0;

	Error += glm::equal(1.01f, 1.02f, 0.1f) ? 0 : 1;
	Error += !glm::equal(1.01f, 1.02f, 0.001f) ? 0 : 1;

	return Error;
}

static int test_notEqual_epsilon()
{
#	if GLM_CONFIG_CONSTEXP == GLM_ENABLE
		static_assert(glm::notEqual(1.01f, 1.02f, 0.001f), "GLM: Failed constexpr");
		static_assert(!glm::notEqual(1.01f, 1.02f, 0.1f), "GLM: Failed constexpr");
#	endif
	
	int Error = 0;

	Error += glm::notEqual(1.01f, 1.02f, 0.001f) ? 0 : 1;
	Error += !glm::notEqual(1.01f, 1.02f, 0.1f) ? 0 : 1;

	return Error;
}

static int test_equal_ulps()
{
	int Error = 0;
	
	float const ULP1Plus = glm::next_float(1.0f);
	Error += glm::equal(1.0f, ULP1Plus, 1) ? 0 : 1;

	float const ULP2Plus = glm::next_float(ULP1Plus);
	Error += !glm::equal(1.0f, ULP2Plus, 1) ? 0 : 1;
	
	float const ULP1Minus = glm::prev_float(1.0f);
	Error += glm::equal(1.0f, ULP1Minus, 1) ? 0 : 1;

	float const ULP2Minus = glm::prev_float(ULP1Minus);
	Error += !glm::equal(1.0f, ULP2Minus, 1) ? 0 : 1;
	
	return Error;
}

static int test_notEqual_ulps()
{
	int Error = 0;
	
	float const ULP1Plus = glm::next_float(1.0f);
	Error += !glm::notEqual(1.0f, ULP1Plus, 1) ? 0 : 1;
	
	float const ULP2Plus = glm::next_float(ULP1Plus);
	Error += glm::notEqual(1.0f, ULP2Plus, 1) ? 0 : 1;
	
	float const ULP1Minus = glm::prev_float(1.0f);
	Error += !glm::notEqual(1.0f, ULP1Minus, 1) ? 0 : 1;
	
	float const ULP2Minus = glm::prev_float(ULP1Minus);
	Error += glm::notEqual(1.0f, ULP2Minus, 1) ? 0 : 1;
	
	return Error;
}

int main()
{
	int Error = 0;

	Error += test_equal_epsilon();
	Error += test_notEqual_epsilon();

	Error += test_equal_ulps();
	Error += test_notEqual_ulps();

	return Error;
}
