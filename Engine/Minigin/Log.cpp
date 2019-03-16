#include "MiniginPCH.h"

#include "Log.h"
#include <ctime>
#include <io.h>
#include <fcntl.h>

HANDLE dae::Logger::m_ConsoleHandle = nullptr;
char dae::Logger::m_BreakBitField = LogLevel::Error;

std::basic_streambuf<char>::int_type dae::DebugStreambuf::overflow(int_type c)
{
	if (c != EOF)
	{
		char buf[] = {static_cast<char>(c), '\0'};
		OutputDebugStringA(buf);
	}
	return c;
}

dae::Logger::Logger()
{
	default_stream = std::cout.rdbuf(&dbgstream);
}

dae::Logger::~Logger()
{
	std::cout.rdbuf(default_stream);
}

void dae::Logger::LogWarning(const std::wstring& msg, bool includeTimeStamp)
{
	Log(LogLevel::Warning, msg, includeTimeStamp);
}


void dae::Logger::Log(LogLevel level, const std::wstring& msg, bool includeTimeStamp)
{
	std::wstringstream stream;

	if (includeTimeStamp)
	{
		SYSTEMTIME st;
		GetSystemTime(&st);
		stream << L"[" << st.wYear << L"-" << st.wMonth << L"-" << st.wDay << L" - ";
		stream << st.wHour << L":" << st.wMinute << L":" << st.wSecond << L":" << st.wMilliseconds << L"]";
	}

	switch (level)
	{
	case LogLevel::Info:
		SetConsoleTextAttribute(m_ConsoleHandle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		stream << L"[INFO]    ";
		break;
	case LogLevel::Warning:
		SetConsoleTextAttribute(m_ConsoleHandle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
		stream << L"[WARNING] ";
		break;
	case LogLevel::Error:
		SetConsoleTextAttribute(m_ConsoleHandle, FOREGROUND_INTENSITY | FOREGROUND_RED);
		stream << L"[ERROR]   ";
		break;
	case LogLevel::FixMe:
		SetConsoleTextAttribute(m_ConsoleHandle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
		stream << L"[FIX-ME]   ";
		break;
	}

	stream << msg;
	stream << L"\n";

	//if error, break
	if (level == LogLevel::Error)
	{
		MessageBox(0, " ", "ERROR", 0);
	}

}
