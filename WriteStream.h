#pragma once
#include <cstdio>
#include <fstream>
#include <tchar.h>
#include <iostream>
#include <string>
#include <cstring>
#include <Windows.h>

class WriteStreamText
{
private:
	//Приватное поле - файл
	std::ofstream f;
public:
	WriteStreamText(std::wstring filename);
	~WriteStreamText();
	HRESULT Write(std::string * buffer);
};

