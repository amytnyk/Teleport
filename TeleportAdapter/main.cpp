#include <string>
#include <fstream>
#include <streambuf>
#include <algorithm>
#include <vector>
#include <iostream>
#include <map>
#include "../TeleportVM/utils.hpp"

void pushNumber(std::vector<char>& bytecode, double n) { // 16 bytes
	char* it = (char*)& n;
	for (size_t i = 0; i < 16; i++)
	{
		bytecode.push_back(it[i]);
	}
}

void pushInt(std::vector<char>& bytecode, int n) { // 4 bytes
	char* it = (char*)& n;
	for (size_t i = 0; i < 4; i++)
	{
		bytecode.push_back(it[i]);
	}
}

void pushChar(std::vector<char>& bytecode, char c) { // 1 byte
	bytecode.push_back(c);
}

void pushBool(std::vector<char>& bytecode, bool b) { // 1 byte
	bytecode.push_back(b ? 1 : 0);
}

void convert(const std::string& in_path, const std::string& out_path) {
	std::ifstream t(in_path);
	std::string str((std::istreambuf_iterator<char>(t)),
		std::istreambuf_iterator<char>());
	t.close();

	std::vector<std::string> lines;
	split(str, lines, '\n');
	std::vector<char> bytecode;

	for (size_t i = 0; i < lines.size(); i++) {
		std::vector<std::string> cmds;
		split(lines[i], cmds, ' ');
		std::string main_cmd = cmds[0];

		if (main_cmd == "setlocal") {
			pushChar(bytecode, 0x0);
			pushInt(bytecode, stoi(cmds[1]));
			if (cmds[2] == "false")
				pushNumber(bytecode, 0);
			else if (cmds[2] == "true")
				pushNumber(bytecode, 1);
			else
				pushNumber(bytecode, stod(cmds[2]));
		}
		else if (main_cmd == "copylocal") {
			pushChar(bytecode, 0x1);
			pushInt(bytecode, stoi(cmds[1]));
			pushInt(bytecode, stoi(cmds[2]));
		}
		else if (main_cmd == "swaplocal") {
			pushChar(bytecode, 0x2);
			pushInt(bytecode, stoi(cmds[1]));
			pushInt(bytecode, stoi(cmds[2]));
		}
		else if (main_cmd == "if") {
			pushChar(bytecode, 0x3);
			pushInt(bytecode, stoi(cmds[1]));
		}
		else if (main_cmd == "createlocal") {
			pushChar(bytecode, 0x4);
			pushInt(bytecode, stoi(cmds[1]));
			if (cmds[2] == "number")
				pushChar(bytecode, 0x0);
			else if (cmds[2] == "bool")
				pushChar(bytecode, 0x1);
			else if (cmds[2] == "char")
				pushChar(bytecode, 0x2);
		}
		else if (main_cmd == "goto") {
			pushChar(bytecode, 0x5);
			pushInt(bytecode, stoi(cmds[1]));
		}
		else if (main_cmd == "createargs") {
			pushChar(bytecode, 0x6);
			pushInt(bytecode, cmds.size() - 1);
			for (size_t j = 1; j < cmds.size(); j++)
			{
				pushInt(bytecode, stoi(cmds[j]));
			}
		}
		else if (main_cmd == "pushresult") {
			pushChar(bytecode, 0x7);
			pushInt(bytecode, stoi(cmds[1]));
		}
		else if (main_cmd == "call") {
			pushChar(bytecode, 0x8);
			if (cmds[1] == "sqrt")
				pushChar(bytecode, 0x0);
			else if (cmds[1] == "add")
				pushChar(bytecode, 0x1);
			else if (cmds[1] == "mult")
				pushChar(bytecode, 0x2);
			else if (cmds[1] == "div")
				pushChar(bytecode, 0x3);
			else if (cmds[1] == "sub")
				pushChar(bytecode, 0x4);
			else if (cmds[1] == "print")
				pushChar(bytecode, 0x5);
		}
		else if (main_cmd == "eval") {
			pushChar(bytecode, 0x9);
			if (cmds[1] == "less")
				pushChar(bytecode, 0x0);
			else if (cmds[1] == "bigger")
				pushChar(bytecode, 0x1);
			else if (cmds[1] == "equal")
				pushChar(bytecode, 0x2);
			else if (cmds[1] == "less_equal")
				pushChar(bytecode, 0x3);
			else if (cmds[1] == "bigger_equal")
				pushChar(bytecode, 0x4);
		}
		else if (main_cmd == "label") {
			pushChar(bytecode, 0xA);
			pushInt(bytecode, stoi(cmds[1]));
		}
		else if (main_cmd == "add") {
			pushChar(bytecode, 0xB);
			pushInt(bytecode, stoi(cmds[1]));
			pushInt(bytecode, stoi(cmds[2]));
			pushInt(bytecode, stoi(cmds[3]));
		}
		else if (main_cmd == "inc") {
			pushChar(bytecode, 0xC);
			pushInt(bytecode, stoi(cmds[1]));
			pushInt(bytecode, stoi(cmds[2]));
			pushNumber(bytecode, stod(cmds[3]));
		}
		else if (main_cmd == "sub") {
			pushChar(bytecode, 0xD);
			pushInt(bytecode, stoi(cmds[1]));
			pushInt(bytecode, stoi(cmds[2]));
			pushInt(bytecode, stoi(cmds[3]));
		}
		else if (main_cmd == "dec") {
			pushChar(bytecode, 0xE);
			pushInt(bytecode, stoi(cmds[1]));
			pushInt(bytecode, stoi(cmds[2]));
			pushNumber(bytecode, stod(cmds[3]));
		}
		else if (main_cmd == "mult") {
			pushChar(bytecode, 0xF);
			pushInt(bytecode, stoi(cmds[1]));
			pushInt(bytecode, stoi(cmds[2]));
			pushInt(bytecode, stoi(cmds[3]));
		}
		else if (main_cmd == "mulc") {
			pushChar(bytecode, 0x10);
			pushInt(bytecode, stoi(cmds[1]));
			pushInt(bytecode, stoi(cmds[2]));
			pushNumber(bytecode, stod(cmds[3]));
		}
		else if (main_cmd == "div") {
			pushChar(bytecode, 0x11);
			pushInt(bytecode, stoi(cmds[1]));
			pushInt(bytecode, stoi(cmds[2]));
			pushInt(bytecode, stoi(cmds[3]));
		}
		else if (main_cmd == "divc") {
			pushChar(bytecode, 0x12);
			pushInt(bytecode, stoi(cmds[1]));
			pushInt(bytecode, stoi(cmds[2]));
			pushNumber(bytecode, stod(cmds[3]));
		}
	}

	std::ofstream out(out_path, std::ios_base::binary);
	out.write(&bytecode[0], bytecode.size());
	out.close();
}

int main() {
	convert("code.tvma", "code.tvm");
	return 0;
}
