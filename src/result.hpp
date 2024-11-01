#ifndef RESULT_H
#define RESULT_H

#include <variant>

namespace unilang {
template <typename T, typename V>
class Result {
private:
	std::variant<T, V> value;
};
}; //namespace unilang

#endif
