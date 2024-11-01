#ifndef RESULT_H
#define RESULT_H

#include <stdexcept>
#include <variant>

namespace unilang {

template <typename E>
class Error {
public:
	Error(E error) :
			error(error) {}

	E getError() const {
		return error;
	}

	Error &operator=(const E &otherError) {
		error = otherError;
		return *this;
	}

private:
	E error;
};

template <typename T, typename E>
class Result {
public:
	Result(const T &value) :
			value(value) {}
	Result(T &&value) :
			value(std::move(value)) {}
	Result(const Error<E> &error) :
			value(error) {}
	Result(Error<E> &&error) :
			value(std::move(error)) {}

	Result &operator=(const T &newValue) {
		value = newValue;
		return *this;
	}

	Result &operator=(T &&newValue) {
		value = std::move(newValue);
		return *this;
	}

	Result &operator=(const Error<E> &newError) {
		value = newError;
		return *this;
	}

	Result &operator=(Error<E> &&newError) {
		value = std::move(newError);
		return *this;
	}

	bool isOk() const {
		return std::holds_alternative<T>(value);
	}

	bool isError() const {
		return std::holds_alternative<Error<E>>(value);
	}

	T unwrap() const {
		if (isError()) {
			throw std::runtime_error("Attempted to unwrap on an Error!");
		}

		return std::get<T>(value);
	}

	E err() const {
		if (isOk()) {
			throw std::runtime_error("Attempted to get an invalid Error!");
		}

		return std::get<Error<E>>(value).getError();
	}

private:
	std::variant<T, Error<E>> value;
};

}; //namespace unilang

#endif
