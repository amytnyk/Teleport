#pragma once
#include "utils.hpp"

namespace Teleport {
	class Memory
	{
	public:
		void init();

		void set_double(int id, double d);
		void set_char(int id, char c);
		void set_bool(int id, bool b);
		void set_data(int id, byte* bytes);
		void copy(int id1, int id2); // data1 = data2
		void swap(int id1, int id2);
		// void set_vardata(int id, var_data vd); // interface

		double get_double(int id) const;
		char get_char(int id) const;
		bool get_bool(int id) const;
		byte* get_data(int id) const;
		// var_data get_vardata(int id) const; // interface

		byte* data;
	};
}