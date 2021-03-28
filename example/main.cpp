//
// Interpreter Project
// Copyright (C) 2020 by Contributors <https://github.com/Tyill/signal_connector>
//
// This code is licensed under the MIT License.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

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

  return 0;
}

