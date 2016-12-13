#include "config.h"
#include "base.h"
#include "ctext.h"

#include <stdio.h>
#include <string>
#include <stdio.h>

ConfigManager& ConfigManager::getInstance()
{
	
	static ConfigManager instance;
	return instance;
}

int ConfigManager::loadConfigFile()
{
	std::string url = CONFIG_PATH;
	CRAWLER_INFO_LOG("Loading config file...");
	FILE* file;
	file = fopen(url.c_str(), "r");
	if(NULL == file)
	{
		CRAWLER_DEBUG_LOG("Loading config file failed, check for path: %s", url.c_str());
	}
	fseek(file, 0L, SEEK_SET);
	char buf[MAX_LINE_LENGTH];
	char* str = NULL;
	while(feof(file))
	{
		str = fgets(buf,MAX_LINE_LENGTH, file);
		if(NULL == str)
		{
			CRAWLER_DEBUG_LOG("Read config file error.");
		}
		CText text(str);
		text.removeSpace();

		char* p = str;
		while('\0' != *str)
		{
			if('=' == *str)
			{
				break;
			}
			str++;
		}
		if('=' == *str)
		{
			*str = '\0';
			str++;
			std::string key(p);
			std::string value(str);
			m_options.insert(std::pair<std::string,std::string>(key, value));	
		}
		else
		{
			CRAWLER_DEBUG_LOG("Config format error.");
			return ERROR;
		}
	}

	fclose(file);
	return SUCCESS;
}

int ConfigManager::findOption(std::string option, std::string& value)
{
	std::map<std::string,std::string>::iterator it;
	it = m_options.find(option);
	if(it == m_options.end())
	{
		CRAWLER_DEBUG_LOG("Can't find option \"%s\" ", option.c_str());
		return ERROR;
	}
	value = (std::string)it->second;
	return SUCCESS;
}