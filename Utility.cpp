/*
 * utility.cpp
 *
 *  Created on: 2014Äê3ÔÂ20ÈÕ
 *      Author: acm
 */

//#include <locale>
//#include <codecvt>

#include "boost/filesystem.hpp"


std::string wstring_to_utf8(const std::wstring& src)
{
//	std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
//
//	return conv.to_bytes(src);
	std::string str;
	for(const wchar_t& chr : src)
	{
		str.push_back(chr);
	}

	return str;
}

std::string recipe_fullname(const std::string& recipe_name)
{
	std::string path = "./recipe/" + recipe_name + ".rcp";

	std::wstring wfullpath = boost::filesystem::system_complete(path).native();

	return wstring_to_utf8(wfullpath);
}

std::string config_fullname(const std::string& config_name)
{
	std::string path = "./config/" + config_name + ".json";

	std::wstring wfullpath = boost::filesystem::system_complete(path).native();

	return wstring_to_utf8(wfullpath);
}

//std::wstring utf8_to_wstring(const std::string& src)
//{
//	std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
//
//	return conv.from_bytes(src);
//}



