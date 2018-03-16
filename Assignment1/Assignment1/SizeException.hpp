#pragma once
#include <exception>

class SizeException : public std::exception {
	virtual const char* what() const noexcept {
		return "Sizes for two matrices are not compatible";
	}
};