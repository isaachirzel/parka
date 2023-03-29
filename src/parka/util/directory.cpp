#include "parka/util/directory.hpp"
#include <cstring>
#include "parka/util/print.hpp"

#include "parka/util/string.hpp"
#include "parka/util/path.hpp"

#include <filesystem>

Directory Directory::readSubdirectory(const String& path, usize pathOffset)
{
	auto iterator = std::filesystem::directory_iterator(path);
	auto files = Array<File>();
	auto subdirectories = Array<Directory>();

	for (const auto& entry : iterator)
	{
		auto path = entry.path().string();

		if (entry.is_directory())
		{
			auto subdirectory = readSubdirectory(std::move(path), pathOffset);
			
			subdirectories.push(std::move(subdirectory));

			continue;
		}

		auto file = File::read(path, pathOffset);

		files.push(std::move(file));
	}

	auto directory = Directory(path.substr(pathOffset), std::move(files), std::move(subdirectories));

	return directory;
}

Optional<Directory> Directory::read(const String& path, usize pathOffset)
{
	if (!std::filesystem::exists(path))
		return {};

	auto directory = readSubdirectory(path, pathOffset);

	return directory;
}
