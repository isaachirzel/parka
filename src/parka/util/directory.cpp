#include "parka/util/directory.hpp"
#include <cstring>
#include "parka/util/print.hpp"

#include "parka/util/string.hpp"
#include "parka/util/path.hpp"

#include <filesystem>

Directory Directory::readSubdirectory(const String& path)
{
	auto iterator = std::filesystem::directory_iterator(path);
	auto files = Array<File>();
	auto subdirectories = Array<Directory>();

	for (const auto& entry : iterator)
	{
		auto path = entry.path().string();

		if (entry.is_directory())
		{
			auto subdirectory = readSubdirectory(std::move(path));
			
			subdirectories.push(std::move(subdirectory));

			continue;
		}

		auto file = File::read(path);

		files.push(std::move(file));
	}

	auto directory = Directory(String(path), std::move(files), std::move(subdirectories));

	return directory;
}

Optional<Directory> Directory::read(const String& path)
{
	if (!std::filesystem::exists(path))
		return {};

	auto directory = readSubdirectory(path);

	return directory;
}
