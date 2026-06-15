#pragma once 

#include <cstdint>
#include <stdint.h>
#include <sfr/common/status_codes.h>


// Интерфейс для работы с ресурсами 
typedef struct sfr_resource_s {
  void* data;  
  const uint32_t type; 

} sfr_resource_t;




typedef struct sfr_istream_s sfr_istream_t;


// Список функций для каждого ресурса
typedef struct sfr_resource_vtable_s {
  // Загрузка
  sfr_result_code_t (*load)(sfr_resource_t* res,sfr_istream_t* istr,sfr_resource_t** out);
  // Создание 
  sfr_result_code_t (*create)(sfr_istream_t* istr,sfr_resource_t** out);
  // Сохранение
  sfr_result_code_t (*save)(sfr_resource_t* res,sfr_istream_t* istr);
  // Освобождение 
  void (*release)(sfr_resource_t* res);

} sfr_resource_vtable_t;

// Функция-фабрика ресурсов 
typedef sfr_resource_t* (*sfr_resource_creator_fn)(const char* path);





