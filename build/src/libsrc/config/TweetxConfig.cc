#include "TweetxConfig.h"
#include <stdlib.h>

Config *Config::mConfig = 0;

bool Config::ReadConfigFile()
{
  bool isRead = true;
  mConfError = CE_FILE_PRESENT;
  //
  //Running setup when File is not found or is in improper format
  //
  //
  std::fstream configFile;
  //std::cout << "Filename = " << mFilename << std::endl;
  configFile.open(mFilename.c_str());
  if(!configFile.is_open())
  {
    std::cerr << "Config file is absent\n";
    //LOG(LS_ERROR)<<"Config file is absent" << mFilename;
		char *home_path = getenv("HOME");
		std::string sHomePath = home_path;
		sHomePath += "/.tweetx";
		std::string sCommand = "mkdir ";
		sCommand += sHomePath;
		
		system(sCommand.c_str());
    mConfError = CE_FILE_NOT_PRESENT;
    isRead = false;
    //abort();
  }
  // LOG(LS_INFO) << "mConfError =" << mConfError;

  std::string sLine;
  std::string sData;
  if(mConfError == CE_FILE_PRESENT)
  {
    while(!configFile.eof())
    {
      getline(configFile,sLine);
      //std::cout << "sLine = " << sLine << std::endl;
      if(!sLine.empty())
      {
        size_t posEqual = sLine.find("=");
        if(posEqual != std::string::npos)
        {
          std::string sName,sValue;
          sName = sLine.substr(0,posEqual);
          sValue = sLine.substr(posEqual+1,sLine.size() - posEqual);

          NSCommon::TrimSpaces(sName);
          NSCommon::TrimSpaces(sValue);

          LOG(LS_INFO)<<sName<<"="<<sValue;
          configNameValueMap[sName] = sValue;
        }
        else //ignoring incorrect entries
        {
          mConfError = CE_FILE_IMPROPER_FORMAT;
          break;
          //continue;
        }
      }
    }
  }
  if(mConfError != CE_FILE_PRESENT)
  {
    configFile.close();
    RunSetup();
    configFile.open(mFilename.c_str(),std::ios::out);
    if(!configFile.is_open())
    {
      std::cerr << "Failed to open file\n";
      LOG(LS_ERROR)<<"Failed to open file " << mFilename;
      mConfError = CE_FILE_NOT_PRESENT;
      isRead = false;
      //abort();
    }
    configFile << mConfigStr.str();
    isRead = false;
  }

  configFile.close();
  return isRead;
}



void Config::RunSetup()
{

  std::string sNewLine("\n"),sEqual("=");
  char cBuff[128];
  int iBuffsize = sizeof(cBuff);
  memset(cBuff,'\0',iBuffsize);
  std::string sUsername,sPasswd;
  std::cerr << "Running Set up";
  ShowDots();
  std::cerr<<sNewLine;
  //Twitter Address
  std::cerr << "Enter Twitter username:";
  std::cin.getline(cBuff,iBuffsize);
  sUsername = cBuff;
  memset(cBuff,'\0',sizeof(cBuff));
  std::cerr << "Enter the passwd:";
  //std::cin >> sPasswd;
  std::cin.getline(cBuff,iBuffsize);
  sPasswd = cBuff;
  memset(cBuff,'\0',sizeof(cBuff));

  mConfigStr << "USERNAME" << sEqual << sUsername;
  mConfigStr << sNewLine;
  mConfigStr << "PASSWORD" << sEqual << sPasswd;
  mConfigStr << sNewLine;





  //CONNECTION TYPE
  //PORT = 80 /443 
  //SSL
  std::string sslEnabled("y");
  bool isCorrectAns = false;
  do
  {
    std::cerr << "ssl is enabled (y/n):default 'y/Y/n/N':";
    memset(cBuff,'\0',sizeof(cBuff));
    //std::cin >> sslEnabled;
    std::cin.getline(cBuff,iBuffsize);
    sslEnabled = cBuff;
    if(sslEnabled == "y" || sslEnabled == "Y" || sslEnabled == "n" || sslEnabled == "N")
      isCorrectAns = true;

  }while(!isCorrectAns);


  mConfigStr << "SSL_ENABLED" << sEqual << sslEnabled;
  mConfigStr << sNewLine;



  //Proxy information
  //HTTP_PROXY
  //HTTP_PORT
  std::string sHttpProxy,sHttpPort;
  std::cerr << "HttpProxy Address:";
  //std::cin >> sHttpProxy;
  memset(cBuff,'\0',sizeof(cBuff));
  std::cin.getline(cBuff,iBuffsize);
  sHttpProxy = cBuff;

  bool isDigit = false;
  int i = 0;
  do
  {
    if(i != 0)
      std::cerr << "Please enter numeric value\n";
    std::cerr << "Http Proxy port:";
    //std::cin >> sHttpPort;
    memset(cBuff,'\0',sizeof(cBuff));
    std::cin.getline(cBuff,iBuffsize);
    sHttpPort = cBuff;
    isDigit = NSCommon::IsDigit(sHttpPort);
    i++;
  }while(!isDigit);

  mConfigStr << "HTTP_PROXY" << sEqual << sHttpProxy;
  mConfigStr << sNewLine;
  mConfigStr << "HTTP_PROXY_PORT" << sEqual << sHttpPort;
  mConfigStr << sNewLine;

  //Proxy user name and passwd
  std::string sHPUsername,sHPPasswd;
  std::cerr << "Http proxy username:";
  //std::cin >> sHPUsername;
  memset(cBuff,'\0',sizeof(cBuff));
  std::cin.getline(cBuff,iBuffsize);
  sHPUsername = cBuff;
  std::cerr << "Http proxy password:";
  //std::cin >> sHPPasswd;
  memset(cBuff,'\0',sizeof(cBuff));
  std::cin.getline(cBuff,iBuffsize);
  sHPPasswd = cBuff;

  mConfigStr << "HTTP_PROXY_USER" << sEqual << sHPUsername;
  mConfigStr << sNewLine;
  mConfigStr << "HTTP_PORT_PASSWORD" << sEqual << sHPPasswd;
  mConfigStr << sNewLine;

  std::cerr << "Enter your mobile number:e.g.xxxx@verizon.mobile.com:";
  memset(cBuff,'\0',sizeof(cBuff));
  std::cin.getline(cBuff,iBuffsize);
  std::string sMobile = cBuff;
  mConfigStr << "MOBILE_NUMBER" << sEqual << sMobile;
  

  //LOG(LS_INFO) << "Config File = " << mConfigStr.str();


}



std::string Config::GetParam(std::string sName)
{
  std::string sValue;

  if(configNameValueMap.find(sName) != configNameValueMap.end())
    sValue = configNameValueMap[sName];
  LOG(LS_ERROR)<<sName << "=" << sValue;

  return sValue;

}

