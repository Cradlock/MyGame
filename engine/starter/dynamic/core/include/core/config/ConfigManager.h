#pragma once



#include "core/boot/BootLogger.h"
#include "core/events/Dispatcher.h"
#include "core/logger/LoggerManager.h"
class Configer{
private:
    EventDispatcher* m_Dispatcher = nullptr;
    
    const Logger* m_Logger = nullptr;

public:
  Configer() = default;
  ~Configer() = default;
  
  void init(EventDispatcher*,const BootLogger*);


};

