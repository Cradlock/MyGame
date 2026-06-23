#pragma once


#include "core/events/Dispatcher.h"
#include "core/logger/LoggerManager.h"
class RSM{

private:
    EventDispatcher* m_Dispatcher = nullptr;

    const Logger* m_Logger = nullptr;
public:
  RSM() = default;
  ~RSM() = default;
  
  void init(EventDispatcher*);



};
