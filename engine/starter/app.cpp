#include "core/engine.h"
#include <sfr/common/status_codes.h>
#include "logic/hello/hello.h"
// Основной двигатель
core::Engine engine;

int main(){ 
  
  logic_hello();

  engine.Init(); 
   
  
  engine.Shutdown();  
  return 0;
}




