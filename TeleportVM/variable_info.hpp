#pragma once
#include <vector>
#include <string>
#include <variant>

namespace Teleport {
	typedef std::variant<double, bool, char> var_data;
	struct Variable_Info {
		enum Type {
			t_number,
			t_char,
			t_bool,
			t_undefined
		};

		Type type = Type::t_undefined;

		Variable_Info() = default;
		explicit Variable_Info(Type);
	};
}