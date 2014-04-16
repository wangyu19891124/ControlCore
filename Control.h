/*
 * Control.h
 *
 *  Created on: 2014Äê3ÔÂ13ÈÕ
 *      Author: acm
 */

#ifndef CONTROL_H_
#define CONTROL_H_

extern "C"
{

void Initialize();
void Terminate();

void FetchParametersByIDRange(int from, int to, char** json);
void FetchParametersByIDs(int* id_array, unsigned num, char** json);
void FetchParametersByPath(const char* path, char** json);

void FetchSystemDataByIDRange(int from, int to, bool only_changed, char** json);
void FetchSystemDataByIDs(int* id_array, unsigned num, bool only_changed, char** json);
void FetchSystemDataByPath(const char* path, bool only_changed, char** json);

void FetchRecentEventLog(char** json);

void Invoke(int unit, int cmd, unsigned param1, unsigned param2);


}

// __declspec(dllexport)
#endif /* CONTROL_H_ */
