#ifndef GRACKLE_PREPROCESSOR_H
#define GRACKLE_PREPROCESSOR_H

#include <string>

namespace grackle
{
	class PreprocessorError
	{
	private:
		std::string _msg;
	public:
		PreprocessorError(const std::string& msg) : _msg(msg) {}
		const char *what() const noexcept { return _msg.c_str(); }
	};

	std::string preprocess(const char *src);
}


#endif
