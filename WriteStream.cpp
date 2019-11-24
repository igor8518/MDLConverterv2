#include "WriteStream.h"



WriteStreamText::WriteStreamText(std::wstring filename)
{
	f.open(filename);
	if (!f.is_open())
		std::wcout << "Файл не открыт";
}


WriteStreamText::~WriteStreamText()
{
	if (f.is_open())
		f.close();
}

HRESULT WriteStreamText::Write(std::string* buffer)
{
	if (!f.is_open())
		return -1;
	try
	{
		f << *buffer;

		//*buffer = std::string(str);
	}
	catch (...)
	{
		std::wcout << "ERROR";
	}
	//return buffer;
	return NOERROR;
}
