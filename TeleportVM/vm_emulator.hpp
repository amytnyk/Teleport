#pragma once
#include <vector>
#include <string>
#include "vm_state.hpp"

namespace Teleport {
	class VM_Emulator {
	public:
		void start_emulating(VM_State&);
	};
}