#include <string>
#include <fstream>
#include <streambuf>
#include <algorithm>
#include <vector>
#include <iostream>
#include <map>
#include "vm_emulator.hpp"

void emulate(const std::string& path) {
	std::ifstream file(path, std::ios::binary | std::ios::ate);
	std::streamsize size = file.tellg();
	file.seekg(0, std::ios::beg);

	std::vector<char> buffer(size);
	file.read(buffer.data(), size);
	file.close();

	Teleport::VM_Emulator vme;
	Teleport::VM_State vms;
	vms.init(buffer);
	vme.start_emulating(vms);
}

int main() {
	emulate("code.tvm");
	return 0;
}
