# signal-connector

A lightweight "signals and slots" like in Qt.
One header only.

## Example of use

```cpp
#include "../include/signal_connector.h"

using namespace std;

int main(int argc, char* argv[])
{  
  /// One type of usage ////////////////////////////////////////////

  class MyObject : public SignalConnector {
  public:
    MyObject() : SignalConnector() { }
  };

  MyObject obj;

  obj.connectSlot(1, std::function<void(int,int,int)>([](int a, int b, int c) {
      int res = a + b + c;
  }));
    
  int a = 1;
  int b = 2;
  int c = 3;

  obj.emitSignal(1, a, b, c);


  /// Two type of usage ////////////////////////////////////////////

  SignalConnector conr;

  conr.connectSlot(1, std::function<void(int, int, int)>([](int a, int b, int c) {
    int res = a + b + c;
  }));
    
  conr.emitSignal(1, a, b, c);
  

  conr.connectSlot(2, std::function<void(int&, int)>([](int& a, int b) {
    a = b;
  }));

  conr.emitSignal<int&, int>(2, a, b);

  return 0;
}
```

### License
Licensed under an [MIT-2.0]-[license](LICENSE).
