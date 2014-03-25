/*
 * ConfigFile.cpp
 *
 *  Created on: 2014Äê3ÔÂ25ÈÕ
 *      Author: acm
 */

#include <sstream>

#include "boost/property_tree/json_parser.hpp"

#include "ConfigFile.h"
#include "Utility.h"

ConfigFile::ConfigFile(const std::string& name)
{
	using namespace boost::property_tree;

	try
	{
		m_filename = config_fullname(name);
		json_parser::read_json(m_filename, m_pt);
	}
	catch (...)
	{
	}
}

ConfigFile::~ConfigFile()
{
	save_to_file();
	m_pt.clear();
}

std::string ConfigFile::ToString(const std::string& path)
{
	using namespace boost::property_tree;
	ptree pt = m_pt.get_child(path);

	std::stringstream ss;
	json_parser::write_json(ss, pt);

	return ss.str();
}

void ConfigFile::save_to_file()
{
	using namespace boost::property_tree;
	json_parser::write_json(m_filename, m_pt);
}
