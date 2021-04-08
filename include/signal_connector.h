//
// Signal-connector Project
// Copyright (C) 2020 by Contributors <https://github.com/Tyill/signal-connector>
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

#pragma once

#include <vector>
#include <map>
#include <functional>
#include <mutex>
#include <memory>

class SignalConnector {

public: 
  SignalConnector() = default;
  ~SignalConnector() = default;

  typedef int SignalType;

  template<typename... Args>
  void connectSlot(SignalType stype, std::function<void(Args...)> func)
  {
    std::lock_guard<std::mutex> lck(m_mtx);
    m_slots[stype].push_back(std::make_unique<SlotFunctor<Args...>>(func));
  }

  void disconnectSlot(SignalType stype)
  {
    std::lock_guard<std::mutex> lck(m_mtx);
    if (m_slots.find(stype) != m_slots.end()) 
      m_slots[stype].clear();
  }

  template<typename... Args>
  bool emitSignal(SignalType stype, Args... args)
  {
    std::lock_guard<std::mutex> lck(m_mtx);
    bool ok = false;
    if (m_slots.find(stype) != m_slots.end()) {
      ok = true;
      for (auto& af : m_slots[stype]) {
        auto f = dynamic_cast<SlotFunctor<Args...>*>(af.get());
        if (f) {
          f->m_func(args...);
        }
        else
          ok = false;
      }
    }
    return ok;
  }

private:
  class AbstractFunctor {
  public: virtual ~AbstractFunctor() {}
  };
  template<typename ...Args>
  class SlotFunctor : public AbstractFunctor {
  public:
    SlotFunctor(std::function<void(Args...)> func) :
      AbstractFunctor(), m_func(func){}
       
    std::function<void(Args...)> m_func;
  };

private:
  std::map<SignalType, std::vector<std::unique_ptr<AbstractFunctor>>> m_slots;
  std::mutex m_mtx;
};