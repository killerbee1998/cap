#ifndef HANDLE
#define HANDLE

#include <string>
#include <map>
#include <vector>
#include <functional>
#include <iostream>

#include "zero.h"
#include "one.h"
#include "two.h"

typedef std::vector<std::string> args;

class handler{
 private:

std::map<std::string, std::function<bool(args)>> table;

 public:

handler();
   
void handle(std::string c,args a);

};

#endif
