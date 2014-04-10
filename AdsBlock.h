/*
 * AdsBlock.h
 *
 *  Created on: 2014Äê4ÔÂ9ÈÕ
 *      Author: Administrator
 */

#ifndef ADSBLOCK_H_
#define ADSBLOCK_H_

#include "TcAdsDef.h"
#include "TcAdsAPI.h"


#define BUFFER_SIZE 4*1024


class AdsBlock
{
public:
	AdsBlock(int id, const std::string& name, const std::string& fun_name, const std::string& ip,
			unsigned short port, unsigned short read_start,	unsigned short read_end,
			unsigned short write_start, unsigned short write_end);
	~AdsBlock();

	void Initialize();
	void Terminate();
	void Sync();
	void Write(unsigned long long value, unsigned io_offset, unsigned bit_offset, unsigned bits);
	unsigned long long Read(unsigned io_offset, unsigned bit_offset, unsigned bits);

private:
	void convert_address(const std::string& str, unsigned short port);

private:
	int m_id;
	std::string m_name;
	std::string m_var_name;
	unsigned short m_read_start;
	unsigned short m_read_end;
	unsigned short m_write_start;
	unsigned short m_write_end;

	boost::mutex m_mtx;
	unsigned char m_buffer[BUFFER_SIZE];
	std::vector<unsigned char> m_comm_buf;
	AmsAddr m_addr;
	unsigned long m_handle;
};


#endif /* ADSBLOCK_H_ */
