
#include "filter.h"
#include <iterator>

using namespace ipflt;

int main(int argc, char const *argv[])
{
    try
    {
		const IP_pool ip_adrr_v = [](){
			auto ip_adrr_v = read_ip_addr();
			ip_sort(ip_adrr_v);
			return move(ip_adrr_v);
		}();

		output(ip_adrr_v);
		output(filter(ip_adrr_v, 1));
		output(filter(ip_adrr_v, 46, 70));
		output(filter_any(ip_adrr_v, 46));

    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
