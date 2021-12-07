# Connector

A lightweight "signals and slots".
One header only.

## Example of use

```cpp
#include "../include/connector.h"

using namespace std;

int main(int argc, char* argv[])
{  
  /// One type of usage ////////////////////////////////////////////

  class MyObject : public Connector {
  public:
    MyObject() : Connector() { }
  };

  MyObject obj;

  obj.connect(1, std::function<void(int,int,int)>([](int a, int b, int c) {
      int res = a + b + c;
  }));
    
  int a = 1;
  int b = 2;
  int c = 3;

  obj.emit(1, a, b, c);


  /// Two type of usage ////////////////////////////////////////////

  Connector conr;

  conr.connect(1, std::function<void(int, int, int)>([](int a, int b, int c) {
    int res = a + b + c;
  }));
    
  conr.emit(1, a, b, c);
  

  conr.connect(2, std::function<void(int&, int)>([](int& a, int b) {
    a = b;
  }));

  conr.emit<int&, int>(2, a, b);

  return 0;
}
```

### License
Licensed under an [MIT-2.0]-[license](LICENSE).
