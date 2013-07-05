#ifndef TWEETX_CONFIG_H
#define TWEETX_CONFIG_H

#include <iostream>
#include <stdlib.h>
#include <map>
#include <string>
#include<fstream>
#include<sstream>
#include "src/libsrc/common/StringManip.h"
#include "src/libsrc/log/log.h"
#include<string.h>
#include "ConfigEnum.h"
#define GetConfig(name) Config::mConfig->GetParam(GetConfigParam(name))


/*!
 *
 *
 *
 */
enum ConfError
{
  CE_FILE_PRESENT,
  CE_FILE_NOT_PRESENT,
  CE_FILE_IMPROPER_FORMAT
};

const char * const GetConfigParam(ConfigParam);
class Config
{
  std::map<std::string,std::string> configNameValueMap;
  std::string mFilename; //!< this is absolute path
  ConfError mConfError;
  void RunSetup();
  std::stringstream mConfigStr;
  //TODO:
  //remove it later
  //
  void ShowDots()
  {
    for(int dotCount = 0;dotCount <6;++dotCount)
    {
      std::cerr<<".";
      //sleep(1); //use usleep later
    }
    
  }
  Config(std::string file):mFilename(file),mConfError(CE_FILE_PRESENT)
  {
  }
	
  public:
  static Config *mConfig;
  static void Start()
  {
		std::string config_path;
		char *home_path = getenv("HOME");
		if(home_path != NULL)
			config_path = home_path;
		else
			config_path = "./";

		config_path += "/.tweetx/config";
    if(mConfig == 0)
      mConfig = new Config(config_path);
    bool isReadFile = mConfig->ReadConfigFile();
    //After running setup, run read Config again
    if(!isReadFile)
      mConfig->ReadConfigFile();
  }
  bool ReadConfigFile();
  std::string GetParam(std::string sName);
  ~Config()
  {
    LOG(LS_INFO) << "Hello"; 
  }
  static void Delete()
  {
    if(mConfig!=NULL)
    delete mConfig;
  }

};

//Config *Config::mConfig = 0;
//TODO:
//should take config file from configure.ac macro
//std::stringstream Config::mConfigStr;



#endif

