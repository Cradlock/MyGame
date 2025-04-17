#ifndef ITEMSDB_H
#define ITEMSDB_H

#include "links.h"


extern unordered_map<int,function<void()>> ItemsLambdaDB;

extern void init_items_lambdas();

#endif