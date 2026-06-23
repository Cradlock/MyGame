
#include "core/events/Dispatcher.h"
#include "sfr/common/events.h"
#include <cassert>



void EventDispatcher::init(){
  m_Storage.reserve(32);
}



void EventDispatcher::subscribe(
  sfr_event_type_t type, sfr_event_callback_t callback 
){
  if(!callback) return;

  m_Storage[type].push_back(callback);
}


void EventDispatcher::broadcast(const sfr_event_ctx_t* event){
  assert(event != nullptr);
  
  auto it = m_Storage.find(event->type);
  if(it != m_Storage.end()){
    for(auto callback : it->second){
      callback(event);
    }
  }

}
