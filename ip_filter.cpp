
#include "filter.h"
#include <iterator>

using namespace ipflt;

int main(int argc, char const *argv[])
{
    try
    {
		auto ip_adrr_v = read_ip_addr();
		ip_sort(ip_adrr_v);

		auto ip_adrr_v_1 = filter(ip_adrr_v, 1);
		auto ip_adrr_v_46_70 = filter(ip_adrr_v, 46, 70);
		auto ip_adrr_v_any_46 = filter_any(ip_adrr_v, 46);

		ip_adrr_v.reserve(ip_adrr_v.size() + ip_adrr_v_1.size() 
			+ ip_adrr_v_46_70.size() + ip_adrr_v_any_46.size());

		ip_adrr_v.insert(end(ip_adrr_v),
			std::make_move_iterator(begin(ip_adrr_v_1)),
			std::make_move_iterator(end(ip_adrr_v_1)));


		ip_adrr_v.insert(end(ip_adrr_v),
			std::make_move_iterator(begin(ip_adrr_v_46_70)),
			std::make_move_iterator(end(ip_adrr_v_46_70)));

		ip_adrr_v.insert(end(ip_adrr_v),
			std::make_move_iterator(begin(ip_adrr_v_any_46)),
			std::make_move_iterator(end(ip_adrr_v_any_46)));

		output(ip_adrr_v);

    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
