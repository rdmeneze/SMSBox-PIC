#if !defined(__SMARTDB_)
#define __SMARTDB_

#if _MSC_VER > 1000
#pragma once
#endif

// SmartDB.h : header file
//

#define RSOPEN_SUCCESS			0
#define RSOPEN_NOLIBLOADED		1
#define RSOPEN_NOCONNECT		2
#define RSOPEN_ALREADYOPENED	3
#define RSOPEN_INVALIDQRY		4

//#define LOAD_SQLITE_DLL  

#include <StdString.h>
#include "sqlite3.h"
#include <vector>

typedef std::vector<CStdString>   CStdStringArray;
typedef std::vector<unsigned int> CUINTArray;
typedef std::vector<void*>        CVOIDArray;

/////////////////////////////////////////////////////////////////////////////
// CSmartDB thread

class CSmartDB
{
	// Attributes
	public:
		CSmartDB();           // constructor and distructor
		~CSmartDB();

	// Operations
	public:
		BOOL Connect (const char* strDBPathName, const char* strParamString = NULL);
		BOOL InitInstance();
		BOOL Close (void);
		BOOL IsConnected (void) ;
		UINT Execute (const char* strQuery, UINT * nRecEfected = NULL);
		BOOL IsLibLoaded (void) ;

		sqlite3 *db;

	// Implementation
	private:
		BOOL InitLibrary(void);

		BOOL m_bLibLoaded;
		BOOL m_bConnected;
};


/////////////////////////////////////////////////////////////////////////////
// CSmartDBRecordSet thread

class CSmartDBRecordSet //: public CWinThread
{
	// Attributes
	public:
		CSmartDBRecordSet();           // protected constructor used by dynamic creation
		virtual ~CSmartDBRecordSet();

	// Operations
	public:
		BOOL Close (void);
		UINT Open (const char* strQueryString, CSmartDB * ptrConn, LONG nRSType = NULL);
		BOOL InitInstance();

		UINT FieldsCount (void);
		const char* GetFieldName (LONG nIndex);
		INT GetFieldType (LONG nIndex);
		
		LONG RecordCount (void);
		void MoveNext (void);
		void MovePrevious (void);
		void MoveLast (void);
		void MoveFirst (void);
		BOOL IsEOF (void);

		CStdString GetColumnString (LONG nIndex);

	// Implementation
	private:
		BOOL m_bIsOpen;
		CStdStringArray strFieldsList;
		CUINTArray nFieldsType;
		CVOIDArray orsRows;
		LONG m_nFieldsCount;
		BOOL m_bIsProcessing;
		LONG m_nCurrentPage;
		LONG m_nPageCount;
		LONG m_nPageSize;
		LONG m_nCurrentRecord;
		LONG m_nRecordCount;
};

/////////////////////////////////////////////////////////////////////////////

#endif // !defined(__SMARTDB_)
