#pragma once 


#include <sfr/core/resources/Interface.h>
#include "sfr/core/resources/states.h"
#include "core/services/resources/in/resource.h"


class Task{
  public:
    Task();
    Task(ResourceTaskType,ResourceInternal*);
    
    ResourceTaskType getType();
    ResourceInternal* getData();
  private:
    ResourceInternal* data;
    ResourceTaskType type;
};


