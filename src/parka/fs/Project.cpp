#include "parka/fs/Project.hpp"
#include "parka/fs/Directory.hpp"
#include "parka/util/PathUtils.hpp"
#include "parka/fs/Path.hpp"

namespace parka::fs
{
    Project::Project(String&& name, Directory&& srcDirectory):
        _name(std::move(name)),
        _srcDirectory(std::move(srcDirectory))
    {}

    Project Project::read(const fs::Path& path)
    {
        auto srcPath = path / "src";
        auto directory = Directory::read(srcPath, 0);
        auto name = path.getFilename();
        auto project = Project(std::move(name), std::move(directory));

        return project;
    }

    static String createTestAbsolutePath(const String& projectName)
	{
		auto absolutePath = String(":memory:/");

		absolutePath += projectName;
		absolutePath += "/src";

		return absolutePath;
	}

    usize getSourceLineCount(const File& file)
    {
        usize count = 1;

        for (usize i = 0; i < file.length(); ++i)
        {
            if (file[i] == '\n')
                count += 1;
        }

        return count;
    }

    usize getDirectoryLinesOfCodeCount(const Directory& directory)
    {
        usize count = 0;

        for (const auto& file : directory.files())
        {
            if (file.type() == FileType::ParkaSource)
                count += getSourceLineCount(file);
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
