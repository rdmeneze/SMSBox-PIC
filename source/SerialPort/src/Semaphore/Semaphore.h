
// $Id: Semaphore.h,v 1.1 2010/08/10 22:48:05 rafael.menezes Exp $

#ifndef __SEMAPHORE_H__
#define __SEMAPHORE_H__

#include <windows.h>

class Semaphore {

	private:
	
		HANDLE hSemaphore;

		Semaphore(const Semaphore&);
		void operator = (const Semaphore&);

	public:

    void Wait( )
    {
      WaitForSingleObject( hSemaphore, INFINITE );
    }

    BYTE Release( )
    {
      DWORD dwRet;

      dwRet = ReleaseSemaphore( hSemaphore,  // handle to semaphore
                                1,            // increase count by one
                                NULL) ;       // not interested in previous count

      return (BYTE)dwRet;
    }


		Semaphore(DWORD dwMaxCount) throw( ... )
		{
      hSemaphore = NULL;
      hSemaphore = CreateSemaphore( 
                        NULL,             // default security attributes
                        dwMaxCount,       // initial count
                        dwMaxCount,       // maximum count
                        NULL);            // unnamed semaphore

      if ( hSemaphore == NULL )
      {
        throw( ::GetLastError() );
      }
		}

		Semaphore(DWORD dwInitialCount, DWORD dwMaxCount) throw( ... )
		{
      hSemaphore = CreateSemaphore( 
                        NULL,             // default security attributes
                        dwInitialCount,   // initial count
                        dwMaxCount,       // maximum count
                        NULL);            // unnamed semaphore

      if ( hSemaphore == NULL )
      {
        throw( ::GetLastError() );
      }

		}

		~Semaphore()
		{
			CloseHandle(hSemaphore);
		}

		class Scope
		{
			private:

				Semaphore *p;
			
				Scope(const Scope&);
				void operator = (const Scope&);

			public:

				Scope(Semaphore &sem)
				{
					p = &sem;
					p->Wait();
				}

				Scope(Semaphore *sem)
				{
					p = sem;
					p->Wait();
				}

				~Scope()
				{
					p->Release();
				}
		};
};

#endif
