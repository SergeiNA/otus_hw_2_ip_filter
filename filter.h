#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include <algorithm>

namespace ipflt {

	using Byte = unsigned short;
	using IP_pool = std::vector<std::vector<Byte>>;
	using IP_addr = std::vector<Byte>;
	using IP_addr_raw = std::vector<std::string>;
	using IP_pool_cr_itr = IP_pool::const_reverse_iterator;

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

	void output(const IP_pool& ip_pool, std::ostream& os = std::cout);

	void ip_sort(IP_pool& ip_pool);

	IP_pool filter_any(const IP_pool& ip_pool, Byte byte);

	template <class...Args>
	Range<IP_pool_cr_itr> filter_(Range<IP_pool_cr_itr>  ip_cr_range, [[maybe_unused]] size_t pos, [[maybe_unused]] Args... args) {
		return ip_cr_range;
	}


	template <class Head, class...Args>

	Range<IP_pool_cr_itr> filter_(Range<IP_pool_cr_itr>  ip_cr_range, size_t pos, Head b, Args... args) {

		auto new_ip_rbegin = std::lower_bound(begin(ip_cr_range), end(ip_cr_range), b,
			[&pos](const IP_addr& ip_addr, Byte val) {return ip_addr.at(pos) < val; });

		auto new_ip_rend = std::upper_bound(new_ip_rbegin, end(ip_cr_range), b,
			[&pos](Byte val, const IP_addr& ip_addr) {return val < ip_addr.at(pos); });

		return filter_({ new_ip_rbegin, new_ip_rend }, ++pos, args...);
	}


	template <class...Args>
	IP_pool filter(const IP_pool& ip_pool, Args... args) {
		if (ip_pool.empty())
			return {};
		if (sizeof...(args) > ip_pool.at(0).size())
			throw std::runtime_error("filter: to many args");

		auto ip_cr_range = filter_({ ip_pool.crbegin(), ip_pool.crend() }, 0, args...);
		return { ip_cr_range.end().base(), ip_cr_range.begin().base() };

	}




}