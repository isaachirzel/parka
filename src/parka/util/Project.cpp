#include "parka/util/Project.hpp"
#include "parka/file/Directory.hpp"
#include "parka/util/Result.hpp"
#include "parka/util/Path.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
    Project Project::read(const String& path)
    {
        auto srcPath = path::join(path, "src");
        auto directory = Directory::read(srcPath, path.length() + 1);
        auto name = path::getFilename(path);
        auto project = Project(std::move(name), std::move(directory));

        return project;
    }

    usize getDirectoryLinesOfCodeCount(const Directory& directory)
    {
        usize count = 0;

        for (const auto& file : directory.files())
        {
            if (file.type() == FileType::Source)
                count += file.lineCount();
        }

        for (const auto& subdirectory :directory.subdirectories())
            count += getDirectoryLinesOfCodeCount(subdirectory);

        return count;
    }

    usize Project::getLinesOfCodeCount()
    {
        return getDirectoryLinesOfCodeCount(_srcDirectory);
    }
}
