#ifndef __TCP_IOCP__
#define __TCP_IOCP__

//#include "st_iocp.h"
#include "StdString.h"
#include "defs.h"

class TCP_IOCP{

	public:

		// Evento
		WORD Event;
		// Id da aplicacao
		WORD IdApp;
		// Tipo da aplicacao
		WORD TypeApp;
		// Dados vindos do pacote TCP_IP
		CStdString sData;

		void operator=(TCP_IOCP &st_iocp)
		{
			this->Event			=	st_iocp.Event;
			this->IdApp			=	st_iocp.IdApp;
			this->TypeApp		=	st_iocp.TypeApp;
			this->sData			=	st_iocp.sData.c_str();
		}

		void operator=(int)
		{
			Event			=	0;
			IdApp			=	0;
			TypeApp		=	0;
			sData.erase();
		}

};


#endif //~ __TCP_IOCP__