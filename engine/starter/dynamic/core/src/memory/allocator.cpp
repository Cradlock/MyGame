
#include "core/boot/BootLogger.h"
#include "core/events/Dispatcher.h"
#include "core/memory/AllocatorManager.h"
#include "core/utils/pr.h"


void Allocator::init (
  BootConfig* cfg,EventDispatcher* disp,BootLogger* lgr
){
  

  m_Dispatcher = disp;
  m_BootLogger = lgr; 
  m_BootConfig = cfg;
  
  double m = m_BootConfig->get<double>("reservemultiplier");
  LOG_PRINT(m);  

}




Allocator::~Allocator(){

}

