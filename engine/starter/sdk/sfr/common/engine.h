#pragma once 




#include "sfr/core/Allocator.h"
typedef void* sfr_context_handle_t;


typedef void* sfr_allocator_handle_t;
typedef void* sfr_logger_handle_t;
typedef void* sfr_resource_manager_handle_t;
typedef void* sfr_config_manager_handle_t;
typedef void* sfr_tick_manaher_handle_t;



typedef struct sfr_engine_context_s {
  sfr_context_handle_t engine_instance;
  
  sfr_allocator_handle_t allocator_intance;
  sfr_logger_handle_t logger_instance;
  sfr_resource_manager_handle_t resource_manager_instance;
  sfr_config_manager_handle_t config_manager_instance;
  sfr_tick_manaher_handle_t tick_manager_instance; 

  const sfr_allocator_interface_s* allocator_interface; 

} sfr_engine_context_t;










