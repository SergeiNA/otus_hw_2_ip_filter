#include "filter.h"


namespace ipflt {
	const size_t IP_ADDR_SZ = 4;

	IP_addr_raw split(const std::string& str, char d)
	{
		IP_addr_raw r;

		std::string::size_type start = 0;
		std::string::size_type stop = str.find_first_of(d);
		while (stop != std::string::npos)
		{
			r.emplace_back(str.substr(start, stop - start));

			start = stop + 1;
			stop = str.find_first_of(d, start);
		}

		r.emplace_back(str.substr(start));

		return r;
	}

	IP_addr get_ip_addr(IP_addr_raw ip_addr_raw) {
		IP_addr ip_addr(4);
		std::transform(begin(ip_addr_raw), end(ip_addr_raw), begin(ip_addr),
			[](std::string s)->size_t {
				return std::stoi(s);
			});
		return ip_addr; // NRVO ???
	}

	void ip_sort(IP_pool& ip_pool) {
		std::sort(ip_pool.begin(), ip_pool.end(), std::greater<IP_addr>());
	}


	IP_pool read_ip_addr(std::istream& is) {
		IP_pool ip_pool;

		for (std::string line; std::getline(is, line);)
		{
			IP_addr_raw v = split(line, '\t');
			ip_pool.emplace_back(get_ip_addr(split(v.at(0), '.')));
		}
		return ip_pool; // NRVO ???
	}


	void output(const IP_pool& ip_pool, std::ostream& os) {
		for (const auto& ip : ip_pool) {
			bool first = true;
			for (const auto& ip_part : ip) {

				if (first) {
					first = false;
					os << ip_part;
					continue;
				}
				os << '.' << ip_part;

			}
			os << std::endl;
		}

	}

	IP_pool filter_any(const IP_pool& ip_pool, Byte byte) {
		if (ip_pool.empty())
			return {};

		IP_pool result;
		std::copy_if(begin(ip_pool), end(ip_pool), std::back_inserter(result),
			[&byte](const IP_addr& ip_addr) {
				return std::count(begin(ip_addr), end(ip_addr), byte) > 0;
			});
		return result;
	}


}