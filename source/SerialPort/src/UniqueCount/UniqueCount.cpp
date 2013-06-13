#include "UniqueCount.h"

//------------------------------------------------------------------------------------------

#define MAX_COUNT_VALUE				999999999

//------------------------------------------------------------------------------------------

long UniqueCount::lCount			=	0;
long UniqueCount::lExchange		=	0;
long UniqueCount::lComperand	=	MAX_COUNT_VALUE;
long *UniqueCount::lpDestination = &UniqueCount::lCount;

//------------------------------------------------------------------------------------------

long UniqueCount::GetUniqueCount(void)
{
  InterlockedCompareExchange( lpDestination, (LONG)lExchange, (LONG)lComperand);
	return ( InterlockedIncrement(&lCount) );
}

//------------------------------------------------------------------------------------------