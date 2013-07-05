#include<iostream>
using namespace std;
#include "../socket.h"
#include "../httpclient.h"
using namespace NSsocket;

int main(int argc,char **argv)
{
  SocketAddress sa;
  sa.mIp = "86.51.34.35";
  sa.mPort = 8080;
  sa.mConnType = CT_PLAIN;
  Socket mySocket(sa);
  //Http::HttpClient httpclient(sa); 
  //Http::HttpMethod httpMethod;
  //httpMethod = Http::POST;
  //httpclient.setUsername("tweetxdev");
  //httpclient.setPassword("amitesh");

  //httpclient.IntializeRequest(httpMethod,"/statuses/update.json","www.twitter.com",true,"status=hi from tweetx");
  //httpclient.Start();
  mySocket.Connect();
  cout << "Connected to the Server" << endl;
  string s = "CONNECT www.twitter.com:80 HTTP/1.1\r\n";
  s += "Host: www.twitter.com\r\n";
  s += "Proxy-Connections: Keep-Alive\r\n\r\n";

  //string s = "GET /index.html HTTP/1.1\r\n\r\n";
  //cout << "Wrting to socket\n";
  cout << s << endl;
  char *df = (char *)s.c_str();
  mySocket.WriteToSocket(df,s.size());
  char output[3900];
  mySocket.ReadFromSocket(output,sizeof(output));
  cout << output;
  std::string sGoogle = "GET /statuses/public_timeline.xml HTTP/1.1\r\nHost: www.twitter.com\r\n\r\n";

  cout << sGoogle << endl;
  mySocket.WriteToSocket((char *)sGoogle.c_str(),sGoogle.size());
  char out[100000];
  bzero(out,sizeof(out));
  mySocket.ReadFromSocket(out,sizeof(out));
  cout << out;
  
  mySocket.Close();



  return 0;
}
