#include "variable_info.hpp"
#include <variant>

namespace Teleport {
	Variable_Info::Variable_Info(Type type) {
		this->type = type;
	}
}