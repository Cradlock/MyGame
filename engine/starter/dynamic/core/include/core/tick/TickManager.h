#pragma once


#include "core/events/Dispatcher.h"
#include "core/logger/LoggerManager.h"
class Ticker{

private:
    EventDispatcher* m_Dispatcher = nullptr;

    Logger* m_Logger = nullptr;
public:
  Ticker() = default;
  ~Ticker() = default;
  
  void init(EventDispatcher*);


};
