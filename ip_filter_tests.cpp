#define BOOST_TEST_MODULE ip_filter_test_module

#include "filter.h"

#include <boost/test/unit_test.hpp>
#include <sstream>

using namespace ipflt;

BOOST_AUTO_TEST_SUITE(ip_filter_test_suite)

BOOST_AUTO_TEST_CASE(input_test)
{
	std::string intput_1(
		R"(1.1.0.0	111	0
2.2.1.0	123 33
3.3.3.3	234 1
1.0.1.0	23 0
)");
	std::istringstream iss(intput_1);

	IP_pool ver_ip_pool = { {1,1,0,0},  {2,2,1,0},  {3,3,3,3},  {1,0,1,0} };

	BOOST_CHECK(ver_ip_pool == read_ip_addr(iss));
}

BOOST_AUTO_TEST_CASE(output_test)
{
	std::string output_1(
		R"(1.1.0.0
2.2.1.0
3.3.3.3
1.0.1.0
)");
	std::ostringstream oss;
	IP_pool ver_ip_pool = { {1,1,0,0},  {2,2,1,0},  {3,3,3,3},  {1,0,1,0} };

	oss << ver_ip_pool;
	ASSERT_EQUAL(output_1, oss.str());

	BOOST_CHECK(output_1 == oss.str());
}

BOOST_AUTO_TEST_CASE(sort_test) {
	IP_pool t_ip_pool_1 = { {0,1,169,0},  {1,2,230,0},  {10,1,240,0},  {10,2,124,0} };
	IP_pool ver_ip_pool_1 = { {10,2,124,0},  {10,1,240,0},  {1,2,230,0},  {0,1,169,0} };
	ip_sort(t_ip_pool_1);
	BOOST_CHECK(ver_ip_pool_1 == t_ip_pool_1);

	IP_pool t_ip_pool_2 = { {70,157,169,0},  {250,211,230,0},  {255,211,240,0},  {9,157,124,0} };
	IP_pool ver_ip_pool_2 = { {255,211,240,0},  {250,211,230,0},  {70,157,169,0},  {9,157,124,0} };
	ip_sort(t_ip_pool_2);
	BOOST_CHECK(ver_ip_pool_2 == t_ip_pool_2);
}

BOOST_AUTO_TEST_CASE(filter_test) {
	IP_pool init_ip_pool = { {10,2,250,0},  {10,2,230,0},{10,1,240,0},{10,1,230,0},{10,1,0,1},  {1,2,230,0},  {0,1,169,0} };
	IP_pool ip_pool_10 = { {10,2,250,0},  {10,2,230,0},{10,1,240,0},{10,1,230,0},{10,1,0,1} };

	IP_pool ip_pool_1 = { {1,2,230,0} };

	IP_pool ip_pool_10_2 = { {10,2,250,0},  {10,2,230,0} };

	IP_pool ip_pool_10_1 = { {10,1,240,0},{10,1,230,0},{10,1,0,1} };

	BOOST_CHECK(ip_pool_10 == filter(init_ip_pool, 10));
	BOOST_CHECK(ip_pool_1 == filter(init_ip_pool, 1));


	BOOST_CHECK(ip_pool_10_2 == filter(init_ip_pool, 10, 2));
	BOOST_CHECK(ip_pool_10_1 == filter(init_ip_pool, 10, 1));

	BOOST_CHECK(ip_pool_10 == filter(init_ip_pool, 10));
	BOOST_CHECK(ip_pool_1 == filter(init_ip_pool, 1));
}

BOOST_AUTO_TEST_CASE(filter_any_test) {
	IP_pool init_ip_pool = { {10,2,250,0},  {10,2,230,0},{10,1,240,0},{10,1,230,0},{10,1,0,1},  {1,2,230,0},  {0,1,169,0} };
	IP_pool ip_pool_any_1 = { {10,1,240,0},{10,1,230,0},{10,1,0,1},  {1,2,230,0},  {0,1,169,0} };
	IP_pool ip_pool_any_230 = { {10,2,230,0},{10,1,230,0},{1,2,230,0} };;
	BOOST_CHECK(ip_pool_any_1 == filter_any(init_ip_pool, 1));
	BOOST_CHECK(ip_pool_any_230 == filter_any(init_ip_pool, 230));
}


BOOST_AUTO_TEST_SUITE_END()