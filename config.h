#ifndef _CONFIG_
#define _CONFIG_

#include <string>
#include <map>

class ConfigManager
{
public:
	static ConfigManager& getInstance();
	int loadConfigFile();
	int findOption(std::string option, std::string& value);
	
private:
	ConfigManager(){}
	~ConfigManager(){}
	
	static std::map<std::string,std::string> m_options;

};

#define CONFIGMN() ConfigManager::getInstance()

#endif
