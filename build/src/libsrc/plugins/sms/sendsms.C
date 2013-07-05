#include <iostream>
#include <stdlib.h>
#include<TweetxConfig.h>
using namespace std;

bool sendSms(std::string sEmailId,std::string &sTweetMsg)
{
  //TODO:
  //check whether the msmtp command exists ??
  //TODO:
  //Read this from config file???
  string sCommand = "msmtp -t -C ~/.msmtprc -a gmail";
  sCommand += " " + sEmailId;
  //not sure,if it works

  FILE *fd = popen(sCommand.c_str(),"w");
  if(fd == NULL)
  {
    return false;
  }
  fprintf(fd,"rcpt to:");
  fprintf(fd,sEmailId.c_str());
  fprintf(fd,"\n");
  fprintf(fd,"Subject: Tweetx Message\n");
  fprintf(fd,sTweetMsg.c_str());
//  fprintf(fd,"\r\n");
//  fprintf(fd,".");
//  fprintf(fd,"\r\n");

  pclose(fd);

}

int main()
{
  Config::Start();
  //std::string emailId = "kerneled.ami@gmail.com";
  std::string emailId = GetConfig(CP_MOBILE_NUMBER);
  std::string msg = "hey from tweetx";
  sendSms(emailId,msg);
  /*
  FILE *fd = popen("msmtp --debug soumen.banerjee@gmail.com -C ~/.msmtprc -a gmail","w");
  fprintf(fd,"Subject: Hi\n");
  fprintf(fd,"Hi from popen\n");
  fporintf(fd,"^D");
  */
  //system("cat mailme| msmtp --debug soumen.banerjee@gmail.com -C ~/.msmtprc -a gmail");
  Config::Delete();
  //std::cerr << "\nSending sms to " << emailId << std::endl;
  return 0;
}

