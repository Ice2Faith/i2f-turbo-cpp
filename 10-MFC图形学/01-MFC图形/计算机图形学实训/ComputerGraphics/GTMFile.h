#ifndef _GTMFILE_H_
#define _GTMFILE_H_
#include"GData.h"
class GTMData
{
public:
	GTMData();
	~GTMData();
	GTMData(char * fileName);
	bool loadTMFile(char * fileName);
	bool saveTMFile(char * fileName);
	bool isLoadFile();
	GD3DataGroup data;
private:
	bool isLoad;
};

#endif // _GTMFILE_H_
