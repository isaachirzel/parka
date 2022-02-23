#include <warbler/lexicon/token.hpp>

namespace warbler::lexicon
{
	using source::File;
	using source::Location;
	using source::Text;

	
	Token::Token(const File& file, const Location& location, TokenType type) :
	_file(file),
	_location(location),
	_type(type)
	{}	

	
}
