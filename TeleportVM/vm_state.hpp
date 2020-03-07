#pragma once
#include <vector>
#include <map>
#include <variant>
#include "memory.hpp"
#include "variable_info.hpp"

namespace Teleport {
	class VM_State {
	private:
		bool initialized = false;
	public:
		VM_State() = default;
		void set_variable(int id, var_data data);
		var_data get_variable(int id);
		bool is_variable_initialized(int id);
		bool is_initialized();
		void init(const std::vector<byte>&);
		const std::map<int, int> command_size = { { 0x0, 21 },  { 0x1, 9 }, { 0x2, 9 }, { 0x3, 5 }, { 0x4, 6 }, { 0x5, 5 }, { 0x6, 5 }, { 0x7, 5 }, { 0x08, 2 }, { 0x9, 2 }, { 0xA, 5 }, { 0xB, 13 }, { 0xC, 25 }, { 0xD, 13 }, { 0xE, 25 }, { 0xF, 13 }, { 0x10, 25 }, { 0x11, 13 }, { 0x12, 25 } };

		std::vector<byte> vm_code;
		Memory memory;
		std::vector<Variable_Info> variables{ variables_max };
		std::map<int, int> labels;
		size_t code_pointer = 0;
	};
}