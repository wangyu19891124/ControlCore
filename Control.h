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

int FetchParametersByIDRange(int from, int to, char** json);
int FetchParametersByIDs(int* id_array, unsigned num, char** json);
int FetchParametersByPath(const char* path, char** json);
void ModifyParameter(int id, const char* value);

int FetchSystemDataByIDRange(int from, int to, bool only_changed, char** json);
int FetchSystemDataByIDs(int* id_array, unsigned num, bool only_changed, char** json);
int FetchSystemDataByPath(const char* path, bool only_changed, char** json);
void ModifySystemData(int id, const char* value);

int FetchRecentEventLog(char** json);

void Invoke(int unit, int cmd, unsigned param1, unsigned param2);


}

// __declspec(dllexport)
#endif /* CONTROL_H_ */
