#pragma once 


#include "core/boot/BootConfig.h"
#include "core/boot/BootLogger.h"
#include "core/events/Dispatcher.h"
#include "core/logger/LoggerManager.h"
#include "core/memory/FreeListS.h"
#include "core/memory/LinearS.h"
#include "core/memory/PoolS.h"
#include "core/memory/StackS.h"
#include <cstddef>
class Allocator{
private:
      EventDispatcher* m_Dispatcher = nullptr;
      BootLogger* m_BootLogger = nullptr;
      BootConfig* m_BootConfig = nullptr;    

      Logger* m_Logger = nullptr;
  
      LinearAllocator m_Linear;
      PoolAllocator m_Pool;
      StackAllocator m_Stack;
      FreeListAllocator m_FreeList;


  size_t real_memory;


public:
  Allocator() = default;
  ~Allocator();

  void init(BootConfig*,EventDispatcher*,BootLogger*);  
  

};


