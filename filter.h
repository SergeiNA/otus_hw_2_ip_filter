#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include <algorithm>
#include <array>

namespace ipflt {
	const size_t IP_ADDR_SZ = 4;
	using Byte = std::uint16_t;
	using IP_addr = std::array<Byte, IP_ADDR_SZ>;
	using IP_pool = std::vector<IP_addr>;
	using IP_addr_raw = std::vector<std::string>;
	using IP_pool_c_itr = IP_pool::const_iterator;

	template <typename It>
	class Range {
	public:
		Range(It begin, It end) : begin_(begin), end_(end) {}
		It begin() const { return begin_; }
		It end() const { return end_; }

	private:
		It begin_;
		It end_;
	};


	IP_addr_raw split(const std::string& str, char d);

	IP_addr get_ip_addr(IP_addr_raw ip_addr_raw);

	IP_pool read_ip_addr(std::istream& is = std::cin);

	[[deprecated("use operator << ")]]
	void output(const IP_pool& ip_pool, std::ostream& os = std::cout);

	std::ostream& operator << (std::ostream& os, const IP_pool& ip_pool);
	std::istream& operator >> (std::istream& is, IP_pool& ip_pool);

	void ip_sort(IP_pool& ip_pool);

	IP_pool filter_any(const IP_pool& ip_pool, Byte byte);

	template<typename... Args>
	void setBoundary(IP_addr& lb, Args... args) {
		size_t i = 0;
		(void(lb[i++] = args), ...);
	}

	template<typename... Args>
	IP_pool filter(const IP_pool& ip_pool, Args... args) {
		if (ip_pool.empty())
			return {};
		auto arg_sz = sizeof...(args);
		if (arg_sz > IP_ADDR_SZ)
			throw std::runtime_error("filter: to many args");

		IP_addr lb_addr{ 255,255,255,255 };
		IP_addr ub_addr{ 0,0,0,0 };

		setBoundary(lb_addr, args...);
		setBoundary(ub_addr, args...);

		auto lower_b = std::lower_bound(begin(ip_pool), end(ip_pool), lb_addr,
			[](const IP_addr& ip_addr, const IP_addr& val) {return ip_addr > val; });

		auto upper_b = std::upper_bound(lower_b, end(ip_pool), ub_addr,
			[](const IP_addr& val, const IP_addr& ip_addr) {return val > ip_addr; });

		return { lower_b ,upper_b };

	}


}