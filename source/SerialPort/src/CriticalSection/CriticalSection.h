
// $Id: CriticalSection.h,v 1.1 2010/08/09 21:10:56 rafael.menezes Exp $

#ifndef __CRITICAL_SECTION_H__
	#define __CRITICAL_SECTION_H__

#include <windows.h>

class CriticalSection {

	private:
	
		CRITICAL_SECTION Critical;

		CriticalSection(const CriticalSection&);
		void operator = (const CriticalSection&);

	public:

		void Enter()
		{
			EnterCriticalSection(&Critical);
		};
		
		void Leave()
		{
			LeaveCriticalSection(&Critical);
		};

		CriticalSection()
		{
			InitializeCriticalSection(&Critical);
		}

		~CriticalSection()
		{
			DeleteCriticalSection(&Critical);
		}

		class Scope
		{
			private:

				CriticalSection *p;
			
				Scope(const Scope&);
				void operator = (const Scope&);

			public:

				Scope(CriticalSection &Crit)
				{
					p = &Crit;
					p->Enter();
				}

				Scope(CriticalSection *Crit)
				{
					p = Crit;
					p->Enter();
				}

				~Scope()
				{
					p->Leave();
				}
		};
};

#endif
