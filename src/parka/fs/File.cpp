#include "parka/fs/File.hpp"
#include "parka/log/Log.hpp"
#include "parka/util/String.hpp"

#include <cstring>

#ifdef _WIN32

#include <windows.h>

#else

#include <fcntl.h>
#include <fileapi.h>
#include <handleapi.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#endif

namespace parka::fs
{
	File::File(String&& text, const Path& path, u8 projectOffset, FileType fileType):
		_text(std::move(text)),
		_path(path),
		_projectOffset(projectOffset),
		_type(fileType)
	{}

	static String readFileText(const Path& filePath)
	{
		// TODO: More specific errors

		const auto* path = filePath.text().c_str();

		#ifdef _WIN32

		auto* fileHandle = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		if (fileHandle == INVALID_HANDLE_VALUE)
			log::fileOpenError(path);
		
		auto fileSize = GetFileSize(fileHandle, NULL);

		if (fileSize == INVALID_FILE_SIZE)
			log::fileStatError(path);


		DWORD bytesRead;
		auto text = String(fileSize, '\0');
		auto result = ReadFile(fileHandle, &text[0], fileSize, &bytesRead, NULL);

		if (!result)
			log::fileReadError(path);

		if (bytesRead != fileSize)
			text.resize(bytesRead);

		return text;
		
		#else

		auto fd = open(path, O_RDONLY);

		if (fd == -1)
			log::fileOpenError(path);

		struct stat sb;

		if (fstat(fd, &sb) == -1)
			log::fileStatError(path);

		auto length = sb.st_size;
		auto* ptr = mmap(nullptr, length, PROT_READ, MAP_SHARED, fd, 0);

		if (ptr == (void*)-1)
			log::fileReadError(path);

		auto text = String((char*)ptr, length);

		munmap(ptr, length);
		close(fd);

		return text;

		#endif
	}

	static void writeFileText(const char *filePath, const String& content)
	{
		FILE *file = fopen(filePath, "w");

		if (!file)
			log::fileOpenError(filePath);

		usize bytesWritten = fwrite(content.c_str(), sizeof(char), content.length(), file);

		fclose(file);

		if (bytesWritten != content.length())
			log::fileWriteError(filePath);
	}

	FileType File::getFileType(const Path& filePath)
	{
		// TODO: Optimize and safety
		auto extension = filePath.extension();

		if (extension == "pk")
			return FileType::ParkaSource;

		if (extension == "json")
			return FileType::Json;

		return FileType::Other;
	}

	File File::read(const Path& path, u16 projectOffset)
	{
		auto text = readFileText(path);
		auto fileType = getFileType(path);
		auto file = File(std::move(text), path, projectOffset, fileType);

		return file;
	}

	File File::createTestMainSrcFile(const Path& directoryPath, u16 projectOffset, String&& src)
	{
		auto file = File(std::move(src), directoryPath / "main.pk", projectOffset, FileType::ParkaSource);

		return file;
	}

	void File::write()
	{
		return writeFileText(_path.text().c_str(), _text);
	}

	String File::getRelativePath() const
	{
		throw std::runtime_error("getRelativePath not implemented.");
		// return _path.substr(_relativePathOffset);
	}
}
