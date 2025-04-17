#include "parka/fs/Directory.hpp"
#include "parka/log/Log.hpp"
#include "parka/util/String.hpp"

#include <cstring>
#include <filesystem>

namespace parka::fs
{
	Directory::Directory(Array<File>&& files, Array<Directory>&& subdirectories, Path&& path, u16 projectOffset):
        _files(std::move(files)),
        _subdirectories(std::move(subdirectories)),
		_path(std::move(path)),
		_projectOffset(projectOffset)
	{}

	Directory Directory::readSubdirectory(const Path& path, u16 projectOffset)
	{
		auto iterator = std::filesystem::directory_iterator(path.text());
		auto files = Array<File>();
		auto subdirectories = Array<Directory>();

		for (const auto& entry : iterator)
		{
			const auto& entryPath = entry.path();

			if (entry.is_regular_file())
			{
				auto file = File::read(entryPath, projectOffset);

				files.push(std::move(file));

			}
			else if (entry.is_directory())
			{
				auto subdirectory = readSubdirectory(std::move(entryPath), projectOffset);
				
				subdirectories.push(std::move(subdirectory));
			}
		}

		auto directory = Directory(std::move(files), std::move(subdirectories), Path(path), projectOffset);

		return directory;
	}

	static u16 getNameOffset(const String& absolutePath)
	{
		// FIXME: Fix safety where we're assuming the string doesn't end with a '/'
		for (auto i = (u16)absolutePath.size(); i-- > 0;)
		{
			if (absolutePath[i] == '/')
				return i + 1;
		}

		return 0;
	}

	String Directory::getName() const
	{
		return _path.getFilename();
	}

	Directory Directory::read(const Path& absolutePath, u16 projectOffset)
	{
		if (!std::filesystem::exists(absolutePath.text()))
			log::directoryOpenError(absolutePath.text().c_str());

		auto directory = readSubdirectory(absolutePath, projectOffset);

		return directory;
	}	

	Directory Directory::createTestSrcDirectory(const Path& projectPath)
	{
		auto absolutePath = projectPath / "src";
		auto directory = Directory({}, {}, std::move(absolutePath), 0);
		
		return directory;
	}

	void Directory::addFile(File&& file)
	{
		_files.push(std::move(file));
	}
}
