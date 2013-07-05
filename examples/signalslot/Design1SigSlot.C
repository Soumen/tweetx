#include "mysigslot.h"
//coded according to coding guidelines
//Design 1
class Switch
{
  public:
    signal0<> SignalClickedEvent;
    void pressedClicked()
    {
      SignalClickedEvent();
    }
};

class Light :public has_slots<>
{
  public:
  void OnClickedEvent()
  {
    cout << "Clicked Event fired\n";
  }

  public:
  Light()
  {
  }
};

class Adapter
{
  Switch switchObj;
  Light lightObj;
  public:
    void connect()
    {
      //conncet
      switchObj.SignalClickedEvent.connect(&lightObj,&Light::OnClickedEvent);
      //emit the signal
      switchObj.pressedClicked();
    }
};
int main()
{
  Adapter adapterObj;
  adapterObj.connect();

  
  return 0;
}
