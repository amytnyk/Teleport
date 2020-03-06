#include "vm_state.hpp"
#include "utils.hpp"

namespace Teleport {
	void VM_State::set_variable(int id, var_data vd)
	{
		std::visit([&](auto&& e) {
			byte* it = &memory.data[id * bytes_for_variable];
			byte* it2 = (byte*)& e;
			for (size_t i = 0; i < bytes_for_variable; i++)
			{
				it[i] = it2[i];
			}
		}, vd);
	}

	var_data VM_State::get_variable(int id)
	{
		if (this->variables[id].type == Variable_Info::Type::t_bool) {
			return memory.get_bool(id);
		}
		else if (this->variables[id].type == Variable_Info::Type::t_char) {
			return memory.get_char(id);
		}
		else if (this->variables[id].type ==  Variable_Info::Type::t_number) {
			return memory.get_double(id);
		}
		return 0.f;
	}

	bool VM_State::is_variable_initialized(int id)
	{
		return this->variables[id].type != Variable_Info::Type::t_undefined;
	}

	bool VM_State::is_initialized() {
		return initialized;
	}

	void VM_State::init(const std::vector<byte>& vmc) {
		code_pointer = 0;
		
		memory.init();
		vm_code = vmc;
		// preprocessing
		for (; code_pointer < vm_code.size();)
		{
			size_t i = code_pointer;
			int cmd = vm_code[i];
			code_pointer += command_size.at(cmd);
			if (cmd == 0x6) { // createargs
				int count = readInt(vm_code, i + 1);
				code_pointer += count * 4;
			}
			else if (cmd == 0xA) { // createlabel
				int label_id = readInt(vm_code, i + 1);
				labels[label_id] = code_pointer;
			}
			else if (cmd > 0xA) {
				// Error
			}
		}

		code_pointer = 0;
		initialized = true;
	}
}
