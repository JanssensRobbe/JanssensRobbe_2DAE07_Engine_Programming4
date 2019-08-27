#pragma once
#include <streambuf>

namespace dae
{
	enum LogLevel
	{
		Info = 0x1,
		Warning = 0x2,
		Error = 0x4,
		FixMe = 0x8
	};

	class DebugStreambuf : public std::streambuf 
	{
	public:
		int_type overflow(int_type c) override;
	};

	// This class redirects the output of std::cout to the visual studio debug stream
	// https://gist.github.com/takashyx/937f3a794ad36cd98ec3
	class Logger 
	{
		DebugStreambuf dbgstream;
		std::streambuf *default_stream{};

	public:
		Logger();
		~Logger();

		Logger(const Logger &) = delete;
		Logger(Logger &&) = delete;
		Logger & operator= (const Logger &) = delete;
		Logger & operator= (const Logger &&) = delete;
	
		static void Log(LogLevel level, const std::wstring& msg, bool includeTimeStamp = false);
		static void LogWarning(const std::wstring& msg, bool includeTimeStamp = false);
	private:
		static HANDLE m_ConsoleHandle;
		static char m_BreakBitField;
	};

#ifdef _DEBUG
#ifdef _MSC_VER
	Logger c2v;
#endif
#endif
}
