#ifndef PARKA_LOG_ANNOTATION_HPP
#define PARKA_LOG_ANNOTATION_HPP

#include "parka/enum/AnnotationType.hpp"
#include "parka/fs/FileSnippet.hpp"

namespace parka::log
{
    class Annotation
    {
        fs::FileSnippet _snippet;
        AnnotationType _annotationType;

    public:

        Annotation(const fs::FileSnippet& snippet, AnnotationType annotationType);
        Annotation(Annotation&&) = default;
        Annotation(const Annotation&) = default;
        Annotation& operator=(Annotation&&) = default;
        Annotation& operator=(const Annotation&) = default;

        const auto& snippet() const { return _snippet; }
        const auto& annotationType() const { return _annotationType; }
    };
}

#endif
