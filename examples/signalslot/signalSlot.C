#include "../../src/include/sigslot.h"
#include <iostream>
using namespace std;
using namespace sigslot;

class Switch
{
  public:
    signal0<> Clicked; //signal
};

//single thread
class Light : public has_slots<>
{
  public:
    void turnOn() { cout <<"Turn On\n";}

};
int main()
{
  Switch sw1;
  Light l1;
  //connect signal and slot 2gether
  sw1.Clicked.connect(&l1,&Light::turnOn);
  //emit the signal
  // 2ways 
  // sw1.Clicked();
  //Or
  sw1.Clicked.emit(); //emit the signal

  return 0;
}
