#include "mysigslot.h"
//coded according to coding guidelines
//Design 2
class Switch
{
  public:
    //
    //
    // ....
};


class Light 
{
  public:
    //
    //
    // ...
};

//we gonna write signal/slot classes in different files
//This class only has signals
//
//
class SwitchSignal:public Switch
{
  public:
    signal0<> SignalClickedEvent;
    void EmitSignalEvent()
    {
      SignalClickedEvent();
    }
};
// This class only has definition of slots
//
//
//
class LightSlot:public Light,public has_slots<>
{
  public:
    //slot
    void OnClickedEvent()
    {
      cout << "On clicked \n";
    };
};

//this class works as interface between signal and slot classes.
class Adapter
{
  SwitchSignal swSlot;
  LightSlot lightSlot;
  public:
  void connect()
  {
    swSlot.SignalClickedEvent.connect(&lightSlot,&LightSlot::OnClickedEvent);
    swSlot.EmitSignalEvent();

  }

};
int main()
{
  Adapter adapterObj;
  adapterObj.connect();

  
  return 0;
}
