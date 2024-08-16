#include "parka/fs/Project.hpp"
#include "parka/fs/Directory.hpp"

namespace parka::fs
{
    Project::Project(String&& name, Directory&& srcDirectory):
        _name(std::move(name)),
        _srcDirectory(std::move(srcDirectory))
    {}

    Project Project::read(const Path& path)
    {
        auto srcPath = path / "src";
        auto directory = Directory::read(srcPath, path.size() + 1);
        auto name = path::getFilename(path);
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

    Project Project::createTestProject(String&& name, String&& mainSrc)
    {
        auto absolutePath = createTestAbsolutePath(name);
        auto relativePathOffset = absolutePath.length() - 3;
        auto srcDirectory = Directory::createTestSrcDirectory(std::move(absolutePath), relativePathOffset, std::move(mainSrc));
        auto project = Project(std::move(name), std::move(srcDirectory));

        return project;
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
            if (file.type() == FileType::Source)
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
