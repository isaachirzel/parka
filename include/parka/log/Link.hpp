#ifndef PARKA_LOG_LINK_HPP
#define PARKA_LOG_LINK_HPP


#include "parka/util/String.hpp"
#include <ostream>
namespace parka
{
	class Link
	{
		String _url;
		String _text;

	public:

		Link(String&& url, String&& text) :
		_url(std::move(url)),
		_text(std::move(text))
		{}
		Link(Link&&) = default;
		Link(const Link&) = default;

		const auto& url() const { return _url; }
		const auto& text() const { return _text; }

		friend std::ostream& operator<<(std::ostream& out, const Link& link);
	};
}

#endif
