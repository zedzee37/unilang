#ifndef RESULT_H
#define RESULT_H

#include <stdexcept>
#include <variant>

namespace unilang {

class Error {
public:
	Error(std::string error) :
			error(error) {}

	std::string getError() const {
		return error;
	}

	Error &operator=(const std::string &otherError) {
		error = otherError;
		return *this;
	}

private:
	std::string error;
};

template <typename T>
class Result {
public:
	Result(const T &value) :
			value(value) {}
	Result(T &&value) :
			value(std::move(value)) {}
	Result(const Error &error) :
			value(error) {}
	Result(Error &&error) :
			value(std::move(error)) {}

	Result &operator=(const T &newValue) {
		value = newValue;
		return *this;
	}

	Result &operator=(T &&newValue) {
		value = std::move(newValue);
		return *this;
	}

	Result &operator=(const Error &newError) {
		value = newError;
		return *this;
	}

	Result &operator=(Error &&newError) {
		value = std::move(newError);
		return *this;
	}

	bool isOk() const {
		return std::holds_alternative<T>(value);
	}

	bool isError() const {
		return std::holds_alternative<Error>(value);
	}

	T unwrap() const {
		if (isError()) {
			throw std::runtime_error("Attempted to unwrap error: " + err());
		}

		return std::get<T>(value);
	}

	std::string err() const {
		if (isOk()) {
			throw std::runtime_error("Attempted to get an invalid Error!");
		}

		return std::get<Error>(value).getError();
	}

private:
	std::variant<T, Error> value;
};

}; //namespace unilang

#endif
