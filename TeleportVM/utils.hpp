#pragma once
#include <vector>
#include <string>
#include "config.hpp"

static void split(const std::string& str, std::vector<std::string>& cont, char delim = '\n')
{
	std::size_t current, previous = 0;
	current = str.find(delim);
	while (current != std::string::npos) {
		cont.push_back(str.substr(previous, current - previous));
		previous = current + 1;
		current = str.find(delim, previous);
	}
	cont.push_back(str.substr(previous, current - previous));
}

static int readInt(const std::vector<Teleport::byte>& bytecode, int pos) {
	int r;
	const Teleport::byte* it = &bytecode[pos];
	Teleport::byte* it2 = (Teleport::byte*)& r;
	for (size_t i = 0; i < 4; i++)
	{
		it2[i] = it[i];
	}
	return r;
}

static double readDouble(const std::vector<Teleport::byte>& bytecode, int pos) {
	double r;
	const Teleport::byte* it = &bytecode[pos];
	Teleport::byte* it2 = (Teleport::byte*) & r;
	for (size_t i = 0; i < 8; i++)
	{
		it2[i] = it[i];
	}
	return r;
}