#include "CppEditor.h"

int CppEditor::countSymbols(std::string part, bool isSingleLineComment)
{
	int count = 0;
	for (int i{ 0 }; i < part.size(); i++)
	{
		if (part.at(i) == '\n' && isSingleLineComment) return count;
		if (i == part.size() - 1) return 0;
		if (part.at(i) == '*' && part.at(i + 1) == '/' && !isSingleLineComment) return count;
		count++;
	}
	return count;
}

void CppEditor::fileRewrite()
{
		std::ofstream file(path);
		file << cppString;
		file.close();
}

CppEditor::CppEditor(std::string path)
{
	
		std::ifstream file(path);
		std::string temp;
		if (!file.is_open())
		{
			std::ofstream file(path);
			file.close();
			this->path = path;
			return;
		}
		while (file.good())
		{
		std::getline (file, temp);
			cppString += (temp + '\n');
		}
		
		file.close();
		this->path = path;
}

CppEditor::CppEditor() : CppEditor ("defaultCPP.cpp") {}

void CppEditor::deleteComments()
{
	int count;
	int begin;
	for (int i{ 0 }; i < cppString.size(); i++)
	{
		if (cppString.at(i) == '/' && cppString.at(i + 1) == '/')
		{
			count = countSymbols(cppString.substr(i, cppString.length()), true);
			std::string::iterator from = cppString.begin() + i;
			std::string::iterator to = cppString.begin() + count + i + 1;
			cppString.replace(from, to, "");
			i--;
		}
		else if (cppString.at(i) == '/' && cppString.at(i + 1) == '*')
		{
			count = countSymbols(cppString.substr(i, cppString.length()), false);
			std::string::iterator from = cppString.begin() + i;
			std::string::iterator to = cppString.begin() + count + i + 3;
			cppString.replace(from, to, "");
			i--;
		}
	}
	fileRewrite();
}

