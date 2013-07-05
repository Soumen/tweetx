#include<iostream>
using namespace std;
#include "../socket.h"
using namespace NSsocket;

int main(int argc,char **argv)
{
  SocketAddress sa;
  sa.mHost = "www.twitter.com";
  sa.mPort = 443;
  sa.mConnType = CT_TLSV1;
  Socket mySocket(sa);
  mySocket.Connect();
  string s = "GET /statuses/public_timeline.xml HTTP/1.0\r\n\r\n";
  //string s = "GET /index.html HTTP/1.1\r\n\r\n";
  cout << "Wrting to socket\n";
  char *df = (char *)s.c_str();
  mySocket.WriteToSocket(df,s.size());
  char output[100000];
  mySocket.ReadFromSocket(output,sizeof(output));

  mySocket.Close();

  cout << output;

  return 0;
}
