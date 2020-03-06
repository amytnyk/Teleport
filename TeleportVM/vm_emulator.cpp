#include <iostream>
#include <sstream>
#include <iomanip>
#include "vm_emulator.hpp"


namespace Teleport {
	void VM_Emulator::start_emulating(VM_State& state) {
		std::vector<int> args;
		int result = -1;

		std::cout.precision(8);
		std::cout << std::fixed;

		bool exec_next_cmd = true;
		for (; state.code_pointer < state.vm_code.size();)
		{
			size_t i = state.code_pointer;
			int cmd = state.vm_code[i];
			state.code_pointer += state.command_size.at(cmd);
			if (cmd == 0x6) { // createargs
				int count = readInt(state.vm_code, i + 1);
				state.code_pointer += count * 4;
			}
			if (exec_next_cmd) {
				if (cmd == 0x0) { // setlocal
					int id = readInt(state.vm_code, i + 1);
					state.memory.set_data(id, &state.vm_code[i + 5]);
				}
				else if (cmd == 0x1) { // copylocal
					int id1 = readInt(state.vm_code, i + 1);
					int id2 = readInt(state.vm_code, i + 5);
					state.memory.copy(id1, id2);
				}
				else if (cmd == 0x2) { // swaplocal
					int id1 = readInt(state.vm_code, i + 1);
					int id2 = readInt(state.vm_code, i + 5);
					state.memory.swap(id1, id2);
				}
				else if (cmd == 0x3) { // if
					int id = readInt(state.vm_code, i + 1);
					if (!state.memory.get_bool(id))
						exec_next_cmd = false;
				}
				else if (cmd == 0x4) { // createlocal
					int id = readInt(state.vm_code, i + 1);
					int type = state.vm_code[i + 5];
					if (type == 0x0) { // number
						state.variables[id].type = Variable_Info::Type::t_number;
					}
					else if (type == 0x1) { // bool
						state.variables[id].type = Variable_Info::Type::t_bool;
					}
					else if (type == 0x2) { // char
						state.variables[id].type = Variable_Info::Type::t_char;
					}
				}
				else if (cmd == 0x5) { // goto
					int label_id = readInt(state.vm_code, i + 1);
					state.code_pointer = state.labels.at(label_id);
					continue;
				}
				else if (cmd == 0x6) { // createargs
					size_t count = readInt(state.vm_code, i + 1);
					args.clear();
					for (size_t j = 0; j < count; j++)
					{
						int id = readInt(state.vm_code, i + 5 + j * 4);
						args.push_back(id);
					}
				}
				else if (cmd == 0x7) { // pushresult
					int id = readInt(state.vm_code, i + 1);
					result = id;
				}
				else if (cmd == 0x8) { // call
					int function = state.vm_code[i + 1];


					if (function == 0x0) { // sqrt
						double d = state.memory.get_double(args[0]);
						state.memory.set_double(result, sqrt(d));
					}
					else if (function == 0x1) { // add
						double r = state.memory.get_double(args[0]) + state.memory.get_double(args[1]);
						state.memory.set_double(result, r);
					}
					else if (function == 0x2) { // mult
						double r = state.memory.get_double(args[0]) * state.memory.get_double(args[1]);
						state.memory.set_double(result, r);
					}
					else if (function == 0x3) { // div
						double r = state.memory.get_double(args[0]) / state.memory.get_double(args[1]);
						state.memory.set_double(result, r);
					}
					else if (function == 0x4) { // sub
						double r = state.memory.get_double(args[0]) - state.memory.get_double(args[1]);
						state.memory.set_double(result, r);
					}
					else if (function == 0x5) { // print
						auto type = state.variables[args[0]].type;

						std::ostringstream stream;
						stream << std::fixed;
						stream << std::setprecision(8);
						if (type == Variable_Info::Type::t_number)
							stream << state.memory.get_double(args[0]);
						if (type == Variable_Info::Type::t_char)
							stream << state.memory.get_char(args[0]);
						if (type == Variable_Info::Type::t_bool)
							stream << (state.memory.get_bool(args[0]) ? "true" : "false");
						std::cout << stream.str() << std::endl;
					}
				}
				else if (cmd == 0x9) { // eval
					int comparator = state.vm_code[i + 1];

					int comp = -1;
					if (state.variables[args[0]].type == state.variables[args[1]].type) {
						if (state.variables[args[0]].type == Variable_Info::Type::t_number) {
							if (state.memory.get_double(args[0]) < state.memory.get_double(args[1]))
								comp = 0;
							else if (state.memory.get_double(args[0]) == state.memory.get_double(args[1]))
								comp = 1;
							else
								comp = 2;
						}
						else if (state.variables[args[0]].type == Variable_Info::Type::t_char) {
							if (state.memory.get_char(args[0]) < state.memory.get_char(args[1]))
								comp = 0;
							else if (state.memory.get_char(args[0]) == state.memory.get_char(args[1]))
								comp = 1;
							else
								comp = 2;
						}
						else if (state.variables[args[0]].type == Variable_Info::Type::t_bool) {
							if (state.memory.get_bool(args[0]) < state.memory.get_bool(args[1]))
								comp = 0;
							else if (state.memory.get_bool(args[0]) == state.memory.get_bool(args[1]))
								comp = 1;
							else
								comp = 2;
						}
					}

					bool res = false;
					if (comparator == 0x0) { // less
						res = comp == 0;
					}
					else if (comparator == 0x1) { // bigger
						res = comp == 2;
					}
					else if (comparator == 0x2) { // equal
						res = comp == 1;
					}
					else if (comparator == 0x3) { // less_equal
						res = comp == 1 || comp == 0;
					}
					else if (comparator == 0x4) { // bigger_equal
						res = comp == 2 || comp == 1;
					}

					state.memory.set_bool(result, res);
				}
			}
			else {
				exec_next_cmd = true;
			}
		}
		std::cout << "Finished" << std::endl;
		system("pause");
	}
}