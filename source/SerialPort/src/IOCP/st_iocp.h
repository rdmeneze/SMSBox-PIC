
#ifndef st_iocpH
	#define st_iocpH

#include <Windows.h>
#include "StdString.h"
#include "types.h"

// Numero maximo de threads permitidas
#define	MAX_THREADS					256

class IOCP {
	public:
    static MapWordToPtr iocp;
		static int    Create(void);
    static bool   Send(int id, void * source);
		static void*  Wait(int id, int time);
    static void   Remove( int id );
};


#endif
