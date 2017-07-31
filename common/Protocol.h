#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_

#include <string>
#include <vector>
#include <stdlib.h>

enum DataType
{
	eLogin,
};

struct CommonDataStruct{
	char type;	//协议类型
	char length;//数据长度
	char* data;	//数据
	CommonDataStruct(){
		type = -1;
		length = -1;
		data = nullptr;
	}
};

class Protocol 
{
public:
	Protocol();
	~Protocol();

	static std::string createProtocol(CommonDataStruct& data);
	static void splitStr(std::string strTarget, std::vector<std::string>& vecStr);
	template<class T>
	static void analysisProtocol(const char* data, std::vector<T>& vecData){
		if (nullptr==data)
		{
			return ;
		}
		string str = data;
		std::vector<std::string> vecStr;
		Protocol::splitStr(str, vecStr);
		if (vecStr.empty())
		{
			return ;
		}
		int type = atoi(vecStr.at(0));
		switch ()
		{
		case eLogin:
			break;
		default:
			break;
		}
	}

private:

};

Protocol::Protocol()
{
}

Protocol::~Protocol()
{
}

std::string Protocol::createProtocol( CommonDataStruct& data )
{
	std::string strRet;
	char type[4];
	char length[4];
	data.length = strlen(data.data);
	sprintf_s(type, "%d,", data.type);
	sprintf_s(length, "%d,", data.length);
	strRet.append(type);
	strRet.append(length);
	strRet.append(data.data);
	return std::move(strRet);
}

void Protocol::splitStr( std::string strTarget, std::vector<std::string>& vecStr )
{
	if (strTarget.empty())
	{
		return ;
	}
	std::string strSplit = ",";
	size_t start=0;
	size_t index=strTarget.find_first_of(strSplit,0);
	while(index!=strTarget.npos)
	{
		if(start!=index)
			vecStr.push_back(strTarget.substr(start,index-start));
		start=index+1;
		index=strTarget.find_first_of(strSplit,start);
	}
	std::string strLast = strTarget.substr(start);
	if(!strLast.empty())
		vecStr.push_back(strLast);
}

#endif