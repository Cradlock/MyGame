#pragma once

#include <cstdint>
#include <stdint.h>

typedef enum sfr_event_type_e : uint32_t {
  SFRE_MEMORY_LOW,
  SFRE_INFO_LOG,
  SFRE_WARN_LOG,
  SFRE_ERROR_LOG,
  SFRE_CRITICAL_LOG
} sfr_event_type_t;


typedef struct sfr_event_ctx_s {
  sfr_event_type_t type;
  const char* sender;
  const char* message;
} sfr_event_ctx_t;


typedef void (*sfr_event_callback_t)(const sfr_event_ctx_t* event);






