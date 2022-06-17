#pragma once
#include "iostream"
#include "fstream"
#include <string>
class CppEditor
{
	std::string cppString;
	std::string path;
	int countSymbols(std::string part, bool isSingleLineComment);
	void fileRewrite();
public:
	CppEditor(std::string);
	CppEditor();

	void deleteComments();
};

