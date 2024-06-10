#include "parka/file/File.hpp"
#include "parka/log/Log.hpp"
#include "parka/util/Path.hpp"
#include "parka/util/String.hpp"

#include <cstring>

// TODO: Cross platform
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

namespace parka
{
	File::File(String&& path, String&& text):
		_path(std::move(path)),
		_text(std::move(text)),
		_type(getType(_path))
	{}

	static String readFileText(const String& filePath)
	{
		auto fd = open(filePath.c_str(), O_RDONLY);

		if (fd == -1)
			log::fatal("Failed to open file `$`.", filePath);

		struct stat sb;

		if (fstat(fd, &sb) == -1)
			log::fatal("Failed to get information for file `$`.", filePath);

		auto length = sb.st_size;
		auto* ptr = mmap(nullptr, length, PROT_READ, MAP_SHARED, fd, 0);

		if (ptr == (void*)-1)
			log::fatal("Failed to read data for file `$`.", filePath);


		auto text = String((char*)ptr, length);

		munmap(ptr, length);
		close(fd);

		return text;
	}

	bool writeFileText(const char *filepath, const String& content)
	{
		FILE *file = fopen(filepath, "w");

		if (!file)
		{
			log::error("Failed to open file '$' for writing.", filepath);
			return false;
		}

		usize bytesWritten = fwrite(content.c_str(), sizeof(char), content.length(), file);

		fclose(file);

		if (bytesWritten != content.length())
		{
			log::error("Failed to write content to file '$'.", filepath);
			return false;
		}

		return true;
	}

	FileType File::getType(const String& filepath)
	{
		// TODO: Optimize and safety
		assert(!filepath.empty() && "Empty filepath");

		const char *lastPoint = nullptr;
		const char *end = &filepath[0];

		while (*end)
		{
			if (*end == '.')
				lastPoint = end;

			end += 1;
		}

		if (lastPoint == nullptr || end - lastPoint == 1)
			return FileType::Regular;
		
		const char *extension = lastPoint + 1;

		if (!strcmp(extension, "pk"))
			return FileType::Source;

		if (!strcmp(extension, "json"))
			return FileType::Json;

		return FileType::Regular;
	}

	File File::read(const String& directoryPath, const String& filename)
	{
		// TODO: Optimize
		auto path = path::join(directoryPath, filename);
		auto text = readFileText(path);
		auto file = File(std::move(path), std::move(text));

		return file;
	}

	File File::read(const String& path, usize pathOffset)
	{
		auto text = readFileText(path);
		auto file = File(path.substr(pathOffset), std::move(text));

		return file;
	}

	File File::from(const String& name, const String& text)
	{
		auto file = File(String(name), String(text));

		return file;
	}

	String File::substr(const usize index, const usize length) const
	{
		assert(index <= _text.length());
		assert(index + length <= _text.length());

		return _text.substr(index, length);
	}
}
