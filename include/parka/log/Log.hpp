#ifndef PARKA_ERROR_ERROR_LOG_HPP
#define PARKA_ERROR_ERROR_LOG_HPP

namespace parka
{
	struct Log
	{
	private:

		static void addEntry(Entry&& entry);

	public:

		template <typename ...Arg>
		static void addNote(const char *fmt, Arg const&... args)
		{
			addEntry(Entry(format(fmt, args...)));
		}

		// static void addNote(Token& token, const char *format);
		// static void addWarning(const char *format);
		// static void addWarning(Token& token, const char *format);
		// static void addError(const char *format);
		// static void addError(Token& token, const char *format);
	};
}

#endif
