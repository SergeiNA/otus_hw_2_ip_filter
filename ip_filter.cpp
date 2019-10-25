
#include "filter.h"
#include <iterator>

using namespace ipflt;

int main( [[maybe_unused]]  int argc, [[maybe_unused]]  char const* argv[])
{
    try
    {
		const IP_pool ip_adrr_v = [](){
			auto ip_adrr_v = read_ip_addr();
			ip_sort(ip_adrr_v);
			return ip_adrr_v;
		}();

		std::cout << ip_adrr_v
			<< filter(ip_adrr_v, 1)
			<< filter(ip_adrr_v, 46, 70)
			<< filter_any(ip_adrr_v, 46)
			<< std::endl;

    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
