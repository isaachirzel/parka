#include "parka/log/Annotation.hpp"

namespace parka::log
{
	Annotation::Annotation(const fs::FileSnippet& snippet, AnnotationType annotationType):
		_snippet(snippet),
		_annotationType(annotationType)
	{}
}
