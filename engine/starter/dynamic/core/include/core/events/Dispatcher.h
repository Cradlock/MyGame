#pragma once

#include "sfr/common/events.h"
#include <unordered_map>
#include <vector>
class EventDispatcher{
 
public:
  EventDispatcher() = default;
  ~EventDispatcher() = default; 

  void init();

  void subscribe(sfr_event_type_t type, sfr_event_callback_t callback);
  
  void broadcast(const sfr_event_ctx_t* event);

private:
  std::unordered_map<
    sfr_event_type_t, 
    std::vector<sfr_event_callback_t>> m_Storage;

};
