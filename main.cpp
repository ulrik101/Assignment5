
//used for memory leak detection. Used in Visual Studio.
/*
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#ifndef DGB_NEW
#define DBG_NEW new ( _NORMAL_BLOCK, __FILE__ , __LINE__ )

#define new DBG_NEW
#endif
#endif
*/

#include <iostream>
#include "database.h"

using namespace std;
int main()
{
  //Used to check for Memory leaks. Used in Visual Studio.
  //_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

  database db;
  const int result = db.run();
  return result;

  

}
