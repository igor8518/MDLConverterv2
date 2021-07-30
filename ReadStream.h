#pragma once

#include <cstdio>
#include <fstream>
#include <tchar.h>
#include <iostream>
#include <string>
#include <cstring>
#include <Windows.h>

class ReadStream
{
private:
	//��������� ���� - ����
	
public:
	std::ifstream f;
	std::ifstream* GetStream();
	ReadStream(std::wstring filename);
	~ReadStream();
	HRESULT Read(PVOID64 buffer, INT64 seek, INT64 count);
};

class ReadStreamText
{
private:
	//��������� ���� - ����
	std::ifstream f;
public:
	ReadStreamText(std::wstring filename);
	~ReadStreamText();
	HRESULT Read(std::string * buffer, INT64 line);
};

