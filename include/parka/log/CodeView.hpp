#ifndef PARKA_LOG_CODE_VIEW_HPP
#define PARKA_LOG_CODE_VIEW_HPP

#include "parka/file/Snippet.hpp"

namespace parka
{
	class CodeView
	{
		Snippet _snippet;
		// Optional<Snippet> _causeSnippet;
		// Optional<Snippet> _carrotSnippet;
		// Optiona<Snippet> _addSnippet;

	public:

		CodeView(const Snippet& snippet);
		CodeView(CodeView&&) = default;
		CodeView(const CodeView&) = default;

		const auto& snippet() const { return _snippet; }
	};
}

#endif
