#pragma once 


#include "sfr/common/status_codes.h"
#include "sfr/core/resources/Interface.h"
#include "sfr/core/resources/states.h"
#include <cstddef>
#include <cstdint>





// [Оболочка ресурса]
typedef struct ResResource {
  sfr_result_code_t code;
  sfr_resource_t* resource;
} ReqResource;



// [Оболочка Json узла]
typedef struct ResJsonNode {
  sfr_result_code_t code;

} ReqJsonNode;

// [Оболочка used bytes]
typedef struct ResUsedBytes {
  sfr_result_code_t code;
  size_t size;
} ResUsedBytes;

// [Оболочка Bytes offset]
typedef struct ResOffsetBytes {
  sfr_result_code_t code; 
  int offset;
} ResOffsetBytes; 

// [Оболочка is_valid]
typedef struct ResValid {
  sfr_result_code_t code;
} ResValid;

// [Оболчка размера]
typedef struct ResSize {
  sfr_result_code_t code;
  int64_t size;
} ResSize;


// [Оболочка IStream]
typedef struct ResStream {
  sfr_result_code_t code;
  sfr_istream_t* stream;
} ResStream;




