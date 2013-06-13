#ifndef __UNIQUECOUNT__
#define __UNIQUECOUNT__

#include "defs.h"

class UniqueCount
{
private:
  // Contador estatico que mantem o valor do index unico
  static long lCount;
  // Valor a ser alterado pela funcao InterlockedCompareExchange()
  static long lExchange;
  // Valor a ser comaprado pela funcao InterlockedCompareExchange()
  static long lComperand;
	// variavel para o valor final depois do incremento do index unico
	static long *lpDestination;
public:
  static LONG GetUniqueCount( );
};

#endif