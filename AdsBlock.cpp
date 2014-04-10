/*
 * AdsBlock.cpp
 *
 *  Created on: 2014Äê4ÔÂ9ÈÕ
 *      Author: Administrator
 */

#include <sstream>
#include <algorithm>

#include "boost/regex.hpp"

#include "AdsBlock.h"

static unsigned long long bits_mask[64] =
{
		0x1,
		0x3,
		0x7,
		0xF,
		0x1F,
		0x3F,
		0x7F,
		0xFF,
		0x1FF,
		0x3FF,
		0x7FF,
		0xFFF,
		0x1FFF,
		0x3FFF,
		0x7FFF,
		0xFFFF,
		0x1FFFF,
		0x3FFFF,
		0x7FFFF,
		0xFFFFF,
		0x1FFFFF,
		0x3FFFFF,
		0x7FFFFF,
		0xFFFFFF,
		0x1FFFFFF,
		0x3FFFFFF,
		0x7FFFFFF,
		0xFFFFFFF,
		0x1FFFFFFF,
		0x3FFFFFFF,
		0x7FFFFFFF,
		0xFFFFFFFF,
		0x1FFFFFFFF,
		0x3FFFFFFFF,
		0x7FFFFFFFF,
		0xFFFFFFFFF,
		0x1FFFFFFFFF,
		0x3FFFFFFFFF,
		0x7FFFFFFFFF,
		0xFFFFFFFFFF,
		0x1FFFFFFFFFF,
		0x3FFFFFFFFFF,
		0x7FFFFFFFFFF,
		0xFFFFFFFFFFF,
		0x1FFFFFFFFFFF,
		0x3FFFFFFFFFFF,
		0x7FFFFFFFFFFF,
		0xFFFFFFFFFFFF,
		0x1FFFFFFFFFFFF,
		0x3FFFFFFFFFFFF,
		0x7FFFFFFFFFFFF,
		0xFFFFFFFFFFFFF,
		0x1FFFFFFFFFFFFF,
		0x3FFFFFFFFFFFFF,
		0x7FFFFFFFFFFFFF,
		0xFFFFFFFFFFFFFF,
		0x1FFFFFFFFFFFFFF,
		0x3FFFFFFFFFFFFFF,
		0x7FFFFFFFFFFFFFF,
		0xFFFFFFFFFFFFFFF,
		0x1FFFFFFFFFFFFFFF,
		0x3FFFFFFFFFFFFFFF,
		0x7FFFFFFFFFFFFFFF,
		0xFFFFFFFFFFFFFFFF
};

AdsBlock::AdsBlock(int id, const std::string& name, const std::string& var_name, const std::string& ip,
		unsigned short port, unsigned short read_start, unsigned short read_end,
		unsigned short write_start, unsigned short write_end) :
		m_id(id), m_name(name), m_var_name(var_name), m_read_start(read_start),
		m_read_end(read_end), m_write_start(write_start), m_write_end(write_end), m_handle(0)
{
	if(read_end<read_start || write_end<write_start)
	{
		std::stringstream ss;
		ss<<"Ads configuration is incorrect in block id="<<id;
		throw ss.str();
	}
	convert_address(ip, port);
	unsigned long block_size = (m_read_end - m_read_start) + (m_write_end - m_write_start);
	m_comm_buf.resize(block_size, 0);
}

AdsBlock::~AdsBlock()
{
}

void AdsBlock::Initialize()
{
	long rtv = AdsSyncReadWriteReq(&m_addr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(m_handle), &m_handle,
			m_var_name.length(), &(*(m_var_name.begin())));
	if(rtv)
	{
		std::stringstream ss;
		ss<<"Failed to get handle of block ["<<m_id<<", "<<m_name<<"].";
		throw ss.str();
	}

	unsigned long read_size = (m_read_end - m_read_start) + (m_write_end - m_write_start);
	rtv = AdsSyncReadReq(&m_addr, ADSIGRP_SYM_VALBYHND, m_handle, read_size, m_buffer);
	if(rtv)
	{
		std::stringstream ss;
		ss<<"Block ["<<m_id<<", "<<m_name<<"] initialize failed.";
		throw ss.str();
	}
}

void AdsBlock::Terminate()
{

}

void AdsBlock::Sync()
{
	unsigned long block_size = (m_read_end - m_read_start) + (m_write_end - m_write_start);
	long rtv = AdsSyncReadReq(&m_addr, ADSIGRP_SYM_VALBYHND, m_handle, block_size, &(*(m_comm_buf.begin())));
	if(rtv)
	{
		//write log
	}

	{
		boost::mutex::scoped_lock lock(m_mtx);
		std::copy(m_comm_buf.begin()+m_read_start, m_comm_buf.begin()+m_read_end, m_buffer+m_read_start);
		std::copy(m_buffer+m_write_start, m_buffer+m_write_end, m_comm_buf.begin()+m_write_start);
	}

	long rtv = AdsSyncWriteReq(&m_addr, ADSIGRP_SYM_VALBYHND, m_handle, block_size, &(*(m_comm_buf.begin())));
	if(rtv)
	{
		//write log
	}
}

void AdsBlock::Write(unsigned long long value, unsigned byte_offset,
		unsigned bit_offset, unsigned bits)
{
	unsigned long long mask = (bits_mask[bits-1]<<bit_offset);
	value <<= bit_offset;
	value &= mask;
	{
		unsigned long long rtv;
		boost::mutex::scoped_lock lock(m_mtx);
		memcpy_s(&rtv, m_buffer+byte_offset, sizeof(unsigned long long));
		rtv &= ~mask;
		rtv |= value;
		memcpy_s(m_buffer+byte_offset, &rtv, sizeof(unsigned long long));
	}
}

unsigned long long AdsBlock::Read(unsigned byte_offset, unsigned bit_offset,
		unsigned bits)
{
	unsigned long long rtv;
	{
		boost::mutex::scoped_lock lock(m_mtx);
		memcpy_s(&rtv, m_buffer+byte_offset, sizeof(unsigned long long));
	}

	rtv >>= bit_offset;
	rtv &= bits_mask[bits-1];

	return rtv;
}

void AdsBlock::convert_address(const std::string& ip, unsigned short port)
{
	boost::regex reg("^(\\d{1,3})\\.(\\d{1,3})\\.(\\d{1,3})\\.(\\d{1,3})\\.(\\d{1,3})\\.(\\d{1,3})$");
	boost::cmatch mat;
	bool r = boost::regex_match(ip.c_str(), mat, reg);
	if(r)
	{
		int i=0;
		for (auto itor = mat.begin(); itor != mat.end(); ++itor)
		{
			m_addr.netId[i++] = boost::lexical_cast<unsigned short>(*itor);
		}
		m_addr.port = port;
	}
	else
	{
		std::stringstream ss;
		ss<<"IP address ("<<ip<<") can't be parsed for block ["<<m_id<<", "<<m_name<<"].";
		throw ss.str();
	}
}
