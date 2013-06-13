#include <conio.h>
#include "Semaphore.h"



void main( void )
{
  DWORD dwMaxCount = 5;

  Semaphore sem( 5, 5 );

//  Semaphore::Scope scope( sem );

  
  for ( int i = 0; i < 10; i++ )
  {
    sem.Wait();
  }


}