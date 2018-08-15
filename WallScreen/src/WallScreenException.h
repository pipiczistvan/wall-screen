#pragma once

#include <string>
#include <stdexcept>

class WallScreenException : public std::runtime_error
{
public:
	WallScreenException(const std::string &message) : std::runtime_error(message) {}
};
