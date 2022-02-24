#include "GameUtils.h"

#include <locale>

std::string GameUtils::WString2String(std::wstring wstrSrc)
{
	std::string strLocale = setlocale(LC_ALL, "");
	const wchar_t* wchSrc = wstrSrc.c_str();
	size_t nDestSize = wcslen(wchSrc) + 1;
	char* chDest = new char[nDestSize];
	wcstombs_s(nullptr, chDest, nDestSize, wchSrc, _TRUNCATE);
	std::string strResult = chDest;
	delete[] chDest;
	setlocale(LC_ALL, strLocale.c_str());
	return strResult;
}