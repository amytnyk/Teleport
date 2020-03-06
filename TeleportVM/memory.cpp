#include "memory.hpp"
#include <variant>
#include <typeinfo>

namespace Teleport {
	void Memory::init() {
		data = new byte[variables_max * bytes_for_variable];
		for (size_t i = 0; i < variables_max * bytes_for_variable; i++)
		{
			data[i] = 0;
		}
	}
	void Memory::set_double(int id, double d) {
		byte* it = &data[id * bytes_for_variable];
		byte* it2 = (byte*)& d;
		for (size_t i = 0; i < bytes_for_variable; i++)
		{
			it[i] = it2[i];
		}
	}
	/*void Memory::set_vardata(int id, var_data d) {
		std::visit([&](auto&& e) { 
			byte* it = &data[id * bytes_for_variable];
			byte* it2 = (byte*)& e;
			for (size_t i = 0; i < bytes_for_variable; i++)
			{
				it[i] = it2[i];
			}
		}, d);
	}*/

	void Memory::set_data(int id, byte* bytes) {
		byte* it = &data[id * bytes_for_variable];
		for (size_t i = 0; i < bytes_for_variable; i++)
		{
			it[i] = bytes[i];
		}
	}
	void Memory::copy(int id1, int id2) {
		byte* it1 = &data[id1 * bytes_for_variable];
		byte* it2 = &data[id2 * bytes_for_variable];
		for (size_t i = 0; i < bytes_for_variable; i++)
		{
			it1[i] = it2[i];
		}
	}
	void Memory::swap(int id1, int id2) {
		byte* it1 = &data[id1 * bytes_for_variable];
		byte* it2 = &data[id2 * bytes_for_variable];
		for (size_t i = 0; i < bytes_for_variable; i++)
		{
			std::swap(it1[i], it2[i]);
		}
	}
	void Memory::set_char(int id, char c) {
		byte* it = &data[id * bytes_for_variable];
		it[0] = c;
	}
	void Memory::set_bool(int id, bool b) {
		byte* it = &data[id * bytes_for_variable];
		it[0] = b;
	}
	double Memory::get_double(int id) const {
		double d;
		const byte* it = &data[id * bytes_for_variable];
		byte* it2 = (byte*)& d;
		for (size_t i = 0; i < 8; i++) // bytes_for_variable
		{
			it2[i] = it[i];
		}
		return d;
	}
	byte* Memory::get_data(int id) const {
		return &data[id * bytes_for_variable];
	}
	char Memory::get_char(int id) const {
		const byte* it = &data[id * bytes_for_variable];
		return it[0];
	}
	bool Memory::get_bool(int id) const {
		const byte* it = &data[id * bytes_for_variable];
		return it[0];
	}
}