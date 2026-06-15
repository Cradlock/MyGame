#pragma once 




#include "sfr/core/resources/Interface.h"
#include "sfr/core/resources/results.h"
#include <cstddef>
#include <cstdint>


typedef struct sfr_istream_vtbl_s {
  
  ResUsedBytes (*read)(sfr_istream_t* self,void* buffer,size_t size);

  ResUsedBytes (*write)(sfr_istream_t* self, const void* buffer, size_t size);

  ResOffsetBytes (*seek)(sfr_istream_t* self, int64_t offset, int origin);

  ResSize (*tell)(sfr_istream_t* self);

  ResSize (*size)(sfr_istream_t* self);

  ResValid   (*is_valid)(sfr_istream_t* self);

  void   (*close)(sfr_istream_t* self);

} sfr_istream_vtbl_t;


// [Поток данных]
typedef struct sfr_istream_s {
  const sfr_istream_vtbl_t* vptr; 
} sfr_istream_t;



