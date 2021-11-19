#ifndef GRACKLE_NOTIMPLEMENTEDERROR_H
#define GRACKLE_NOTIMPLEMENTEDERROR_H

// standard library
#include <stdexcept>
#include <string>

namespace grackle
{
	class NotImplementedError : public std::exception
	{
	private:

		std::string _function_name;

	public:

		NotImplementedError(const char *function_name) :
		_function_name(function_name)
		{}

		const char *what() const noexcept 
		{
			return "This function is not implemented yet";
		} 
	};
}

#endif
