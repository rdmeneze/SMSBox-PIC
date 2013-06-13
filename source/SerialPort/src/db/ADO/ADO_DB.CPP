
#include "ado_db.H"
#include "functions.h"

//------------------------------------------------------------------------------------------------------------------------

#define MIN_DATE                (-657434L)  // about year 100
#define MAX_DATE                2958465L    // about year 9999

#define LINK_FAILURE								"08S01"

// Half a second, expressed in days
#define HALF_SECOND							(1.0/172800.0)

// One-based array of days in year at month start
static const int MonthDays[13] =	{0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};

//------------------------------------------------------------------------------------------------------------------------

ado_db::ado_db()
{
	pConnection			=	NULL;
	pRecordSet			=	NULL;
	bFail						= false;
	pFields					=	NULL;    
	vtIndex.vt			= VT_I2;
  TotalRecordsets = 0;
	//[11_08_2009<]
	CommandTimeout	=	30;
	//[11_08_2009<]
}

//------------------------------------------------------------------------------------------------------------------------

ado_db::~ado_db()
{
	Close();
}

//------------------------------------------------------------------------------------------------------------------------

// Abre conexao usando o objeto ADO Microsoft
int ado_db::OpenMicrosoft(void)
{
	try 
  {

		if( pConnection == NULL )
    {
			// Cria instancia do objeto de conexao
			pConnection.CreateInstance( __uuidof( Connection ) );
		}
		
		if( pRecordSet == NULL )
    {
			// Cria instancia do objeto de record set
			pRecordSet.CreateInstance( __uuidof(Recordset) );
		}

		if( pConnection->State == adStateOpen )
    {
			// Se o objeto ja esta aberto, fecha antes de abri-lo novamente
			pConnection->Close();
		}

		//[16_04_2010<]
		// Se existir a connection string, utiliza esse parametro
		if( sConnectionString.length() > 0 )
		{
		  // Abre a conexao com o banco de dados
		  pConnection->Open(sConnectionString.c_str(), "", "", adConnectUnspecified);
    }
    else
		{
		  // Abre a conexao com o banco de dados
		  pConnection->Open(sDSN.c_str(), sUser.c_str(), sPassword.c_str(), adConnectUnspecified);

		  // Altera o banco de dados em uso
		  pConnection->DefaultDatabase = sDataBase.c_str();
    }
    //[16_04_2010>]

		//[11_08_2009<]
		// Seta o timeout de execucao de comandos
		pConnection->CommandTimeout = CommandTimeout;
		//[11_08_2009>]

		return 0;
	}
	catch( _com_error &c_error )
  {
		bFail = true;
		SetLastError( c_error );
		return -1;
	}
}

//------------------------------------------------------------------------------------------------------------------------

// Abre conexao usando o objeto ADO Oracle
int ado_db::OpenOracle(void)
{
	try {

		if( pConnection == NULL )
    {
			// Cria instancia do objeto de conexao
			pConnection.CreateInstance( __uuidof( Connection ) );
		}
		
		if( pRecordSet == NULL )
    {
			// Cria instancia do objeto de record set
			pRecordSet.CreateInstance( __uuidof(Recordset) );
		}

		if( pConnection->State == adStateOpen ){
			// Se o objeto ja esta aberto, fecha antes de abri-lo novamente
			pConnection->Close();
		}

		//[16_04_2010<]
		// Se existir a connection string, utiliza esse parametro
		if( sConnectionString.length() > 0 )
		{
			// Abre a conexao com o banco de dados
			pConnection->Open(sConnectionString.c_str(), "", "", adConnectUnspecified);
		}
		else
		{
			sConnection = "provider=OraOLEDB.Oracle;ORAPROP_PLSQLRSet=true;";
			sConnection += "Data Source=";
			sConnection += sDSN.c_str();
			sConnection += ";";   
			sConnection +="User Id=";
			sConnection += sUser.c_str();
			sConnection += ";";
			sConnection += "Password=";
			sConnection += sPassword.c_str();
			sConnection += ";";

			// Abre a conexao com o banco de dados
			pConnection->Open(sConnection.c_str(), "", "", adConnectUnspecified);
		}
		//[16_04_2010>]

		//[11_08_2009<]
		// Seta o timeout de execucao de comandos para 30 segundos
		pConnection->CommandTimeout = CommandTimeout;
		//[11_08_2009>]

		return 0;
	}
	catch( _com_error &c_error ){
		bFail = true;
		SetLastError( c_error );
		return -1;
	}
}

//------------------------------------------------------------------------------------------------------------------------

// Abre conexao usando o objeto ADO Sybase
int ado_db::OpenSybase(void)
{
	try {

		if( pConnection == NULL ){
			// Cria instancia do objeto de conexao
			pConnection.CreateInstance( __uuidof( Connection ) );
		}
		
		if( pRecordSet == NULL ){
			// Cria instancia do objeto de record set
			pRecordSet.CreateInstance( __uuidof(Recordset) );
		}

		if( pConnection->State == adStateOpen ){
			// Se o objeto ja esta aberto, fecha antes de abri-lo novamente
			pConnection->Close();
		}

		//[16_04_2010<]
		// Se existir a connection string, utiliza esse parametro
		if( sConnectionString.length() > 0 )
		{
			// Abre a conexao com o banco de dados
			pConnection->Open(sConnectionString.c_str(), "", "", adConnectUnspecified);
		}
		else
		{
			sConnection.Format("DSN=%s;SRVR=%s;UID=%s;PWD=%s",
													sDSN.c_str(), sDataBase.c_str(), sUser.c_str(), sPassword.c_str() );

			// Abre a conexao com o banco de dados
			pConnection->Open(sConnection.c_str(), "", "", adConnectUnspecified);
		}
		//[16_04_2010>]

		//[11_08_2009<]
		// Seta o timeout de execucao de comandos para 30 segundos
		pConnection->CommandTimeout = CommandTimeout;
		//[11_08_2009>]

		return 0;
	}
	catch( _com_error &c_error ){
		bFail = true;
		SetLastError( c_error );
		return -1;
	}
}

//------------------------------------------------------------------------------------------------------------------------

//[16_04_2010<]
int ado_db::Open(	const char *ConnectionString,
									const char *DSN,
									const char *DataBase,
									const char *User,
									const char *Password,
									int type)
{
	int iRet;

	try
	{
		sConnectionString	=	ConnectionString;
		sDSN							= DSN;
		sDataBase					= DataBase;
		sUser							=	User;
		sPassword					= Password;
		sConnection				=	DSN;
		AdoType						=	type;

		switch( AdoType )
		{
			case ADO_MICROSOFT:
				// Abre uma conexao ADO com SQL Server
				iRet = OpenMicrosoft();
			break;

			case ADO_ORACLE:
				// Abre conexao com banco de dados Oracle
				iRet = OpenOracle();
			break;

			case ADO_SYBASE:
				// Abre conexao com banco de dados Sybase
				iRet = OpenSybase();
			break;
		}

    //<TITO> guarda o nome do server onde esta conectado
    bstrServerName = pConnection->GetProperties()->GetItem("Server Name")->GetValue();
    //<TITO>

		return iRet;
	}
	catch(...){
		bFail = true;
		return -1;
	}
}

//------------------------------------------------------------------------------------------------------------------------

void ado_db::Close(void)
{
	try
	{
		//[26473<]
		if( pConnection != NULL )
		{
			if(pConnection->State == adStateOpen)
			{
				pConnection->Close();
				pConnection.Release();
				pConnection = NULL;
			}
		}

		if( pRecordSet != NULL )
		{
			if(pRecordSet->State == adStateOpen)
			{
				pRecordSet->Close();
				pRecordSet.Release();
				pRecordSet = NULL;
			}
		}
		//[26473>]

		for( int i = 0; i < MAX_RECORDSETS; i++)
    {
      if( pAllRecordSet[i] != NULL )
      {
        if( pAllRecordSet[i]->State == adStateOpen)
        {
          pAllRecordSet[i]->Close();
          pAllRecordSet[i]->Release();
        }
      }
    }
	}
	catch( _com_error &c_error )
	{
		bFail = true;
		SetLastError( c_error );
	}
}

//------------------------------------------------------------------------------------------------------------------------

int ado_db::Query( const char *sCommand, bool bTransaction )
{
	try {

    _RecordsetPtr pAux;
    int id = 0;
    long lngRec = 0;

		if( bFail )
		{
			// Erro, reconecta ao banco de dados
			if( AdoType == ADO_MICROSOFT ){
				// Abre uma conexao ADO normal
				OpenMicrosoft();
			}
			if( AdoType == ADO_ORACLE ){
				// Abre conexao com Oracle com ADO
				OpenOracle();
			}
		}

    CloseRecordset();

		// Habilita posisicao absoluta de cursor
		pRecordSet->CursorLocation = adUseClient;

		if(bTransaction)
			pConnection->BeginTrans();

		bFail = false;

		//[11_08_2009<]
		pConnection->CommandTimeout = CommandTimeout;
		//[11_08_2009>]

		// Executa o comando SQL
		pRecordSet->Open(sCommand, _variant_t((IDispatch *) pConnection, true), adOpenStatic, adLockOptimistic, adCmdText);

		if(bTransaction)
			pConnection->CommitTrans();

    iNumRows        = 0;
    iNumCols        = 0;
    TotalRecordsets = 0;

    //posiciona o ponteiro auxiliar no 1o recordset
    pAux = pRecordSet;

    //faz a leitura de todos os recordsets de resultado
    //e armazena na matriz de recordsets
    for(id = 0; (pAux != NULL) && (id < MAX_RECORDSETS); )
    {
      
      // Obtem um ponteiro para os campos
	  	pFields = pAux->GetFields();

      if( pFields->GetCount() > 0 )
      {
        iNumRows += pAux->RecordCount;

        // Obtem o numero de colunas
        if( iNumCols < pFields->GetCount() )
          //O numero de colunas sera o maior de todos os recordsets
  		    iNumCols = pFields->GetCount();

        pAllRecordSet[id] = pAux->Clone(adLockUnspecified);
        id++;
      }

      pAux = pAux->NextRecordset((VARIANT *)lngRec);
    }
    TotalRecordsets = id;

    /*
		// Obtem um ponteiro para os campos
		pFields = pRecordSet->GetFields();

		// Obtem o numero de colunas
		iNumCols = (int)pFields->GetCount();
    */

		if(iNumCols <= 0){

			iNumCols = 0;
			iNumRows = 0;

			if(pRecordSet->State == adStateOpen){
				pRecordSet->Close();
			}

			//return 0;
		}

		return 0;
	}
	catch( _com_error &c_error ){

		bFail = true;

		if( bTransaction ){

			try {
				pConnection->RollbackTrans();
			}
			catch( _com_error &t_error ){
				SetLastError( t_error );
			}
		}

		SetLastError( c_error );
		
    CloseRecordset();
		return -1;
	}
}

//------------------------------------------------------------------------------------------------------------------------

int ado_db::GetColCount(void)
{
	try {
		
		return iNumCols;
	}
	catch(...){
	}
  return 0;
}

//------------------------------------------------------------------------------------------------------------------------

int ado_db::GetRowCount(void)
{
	try {

		return iNumRows;
	}
	catch(...){
	}
  return 0;
}

//------------------------------------------------------------------------------------------------------------------------

char *ado_db::GetField(int Row, int Col)
{
	try {

    _RecordsetPtr pAux;
    int recCount;  
    int id;

    if( Row >= iNumRows )
      return "";

    for(id = 0 ; id < TotalRecordsets; id++)
    {

      recCount = pAllRecordSet[id]->RecordCount;

      if( Row < recCount ) // vai para o proximo recordset
        break;
     
      Row -= recCount;
    }

    if( pAllRecordSet[id] == NULL )
      return "";

    pAux = pAllRecordSet[id];
    
		// Calcula o numero de registros para mover no cursor
		int NumRegister = (Row + 1) -  pAux->AbsolutePosition;

		// Move o cursor para a posicao desejada
		pAux->Move( NumRegister );

    pFields = pAux->Fields;

    if( Col > pFields->GetCount() )
      return "";

		// Posiciona a coluna
		vtIndex.iVal = Col;

		// Obtem a propriedade do valor do campo
		propValue = pFields->GetItem(vtIndex)->Value;

		// Verifica se o dado e nulo
		if( propValue.vt == VT_NULL ){
			return "";
		}

		// Obtem o valor convertido para CStdString
		sField = (LPCSTR)(_bstr_t) pFields->GetItem(vtIndex)->GetValue();

		// Obtem o valor convertido para variant
		vtField.Clear();
		vtField = pFields->GetItem(vtIndex)->GetValue();

		// Retira os espacos a direita e a esquerda
		TrimAll(sField);

		// Obtem o tipo do campo
		FieldType = pFields->GetItem(vtIndex)->Type;		

		// Verifica o tipo do campo e faz as conversoes necessarias
		switch( FieldType ){

			case adBinary:
			break;

			case adDBTimeStamp:
				sField = DateToStr(vtField.date);
			break;

			case adBoolean:
				// O valor do campo tipo bit vem como -1 quando ele eh true, entao coloca 1 na variavel
				if( atoi( sField.c_str() ) ){
					return "1";
				}
			break;
		}

		return (char *) sField.c_str();
	}
	catch(...)
	{
		return "";
	}
}

//------------------------------------------------------------------------------------------------------------------------

void ado_db::SetLastError( _com_error &c_error )
{
	try{

		_bstr_t bstrDescription( c_error.Description() );

		sLastError = (LPCSTR) bstrDescription;

    CheckDBConnection(pConnection->Errors);
	}
	catch(...){
	}
}


//------------------------------------------------------------------------------------------------------------------------

const char *ado_db::GetLastError(void)
{
	try{
		return sLastError.c_str();
	}
	catch(...){
		return "";
	}
}

//------------------------------------------------------------------------------------------------------------------------

char *ado_db::DateToStr(DATE dtSrc)
{
	try {

		// The legal range does not actually span year 0 to 9999.
		if (dtSrc > MAX_DATE || dtSrc < MIN_DATE) // about year 100 to about 9999
			return "";

		struct tm tmDest;
		long nDays;             // Number of days since Dec. 30, 1899
		long nDaysAbsolute;     // Number of days since 1/1/0
		long nSecsInDay;        // Time in seconds since midnight
		long nMinutesInDay;     // Minutes in day

		long n400Years;         // Number of 400 year increments since 1/1/0
		long n400Century;       // Century within 400 year block (0,1,2 or 3)
		long n4Years;           // Number of 4 year increments since 1/1/0
		long n4Day;             // Day within 4 year block
								//  (0 is 1/1/yr1, 1460 is 12/31/yr4)
		long n4Yr;              // Year within 4 year block (0,1,2 or 3)
		BOOL bLeap4 = TRUE;     // TRUE if 4 year block includes leap year

		double dblDate = dtSrc; // tempory serial date

		// If a valid date, then this conversion should not overflow
		nDays = (long)dblDate;

		// Round to the second
		dblDate += ((dtSrc > 0.0) ? HALF_SECOND : -HALF_SECOND);

		nDaysAbsolute = (long)dblDate + 693959L; // Add days from 1/1/0 to 12/30/1899

		dblDate = fabs(dblDate);
		nSecsInDay = (long)((dblDate - floor(dblDate)) * 86400.);

		// Calculate the day of week (sun=1, mon=2...)
		//   -1 because 1/1/0 is Sat.  +1 because we want 1-based
		tmDest.tm_wday = (int)((nDaysAbsolute - 1) % 7L) + 1;

		// Leap years every 4 yrs except centuries not multiples of 400.
		n400Years = (long)(nDaysAbsolute / 146097L);

		// Set nDaysAbsolute to day within 400-year block
		nDaysAbsolute %= 146097L;

		// -1 because first century has extra day
		n400Century = (long)((nDaysAbsolute - 1) / 36524L);

		// Non-leap century
		if (n400Century != 0)
		{
			// Set nDaysAbsolute to day within century
			nDaysAbsolute = (nDaysAbsolute - 1) % 36524L;

			// +1 because 1st 4 year increment has 1460 days
			n4Years = (long)((nDaysAbsolute + 1) / 1461L);

			if (n4Years != 0)
				n4Day = (long)((nDaysAbsolute + 1) % 1461L);
			else
			{
				bLeap4 = FALSE;
				n4Day = (long)nDaysAbsolute;
			}
		}
		else
		{
			// Leap century - not special case!
			n4Years = (long)(nDaysAbsolute / 1461L);
			n4Day = (long)(nDaysAbsolute % 1461L);
		}

		if (bLeap4)
		{
			// -1 because first year has 366 days
			n4Yr = (n4Day - 1) / 365;

			if (n4Yr != 0)
				n4Day = (n4Day - 1) % 365;
		}
		else
		{
			n4Yr = n4Day / 365;
			n4Day %= 365;
		}

		// n4Day is now 0-based day of year. Save 1-based day of year, year number
		tmDest.tm_yday = (int)n4Day + 1;
		tmDest.tm_year = n400Years * 400 + n400Century * 100 + n4Years * 4 + n4Yr;

		// Handle leap year: before, on, and after Feb. 29.
		if (n4Yr == 0 && bLeap4)
		{
			// Leap Year
			if (n4Day == 59)
			{
				/* Feb. 29 */
				tmDest.tm_mon = 2;
				tmDest.tm_mday = 29;
				goto DoTime;
			}

			// Pretend it's not a leap year for month/day comp.
			if (n4Day >= 60)
				--n4Day;
		}

		// Make n4DaY a 1-based day of non-leap year and compute
		//  month/day for everything but Feb. 29.
		++n4Day;

		// Month number always >= n/32, so save some loop time */
		for (tmDest.tm_mon = (n4Day >> 5) + 1;
			n4Day > MonthDays[tmDest.tm_mon]; tmDest.tm_mon++);

		tmDest.tm_mday = (int)(n4Day - MonthDays[tmDest.tm_mon-1]);

	DoTime:
		if (nSecsInDay == 0)
			tmDest.tm_hour = tmDest.tm_min = tmDest.tm_sec = 0;
		else
		{
			tmDest.tm_sec = (int)nSecsInDay % 60L;
			nMinutesInDay = nSecsInDay / 60L;
			tmDest.tm_min = (int)nMinutesInDay % 60;
			tmDest.tm_hour = (int)nMinutesInDay / 60;
		}

		sprintf(sDatetime, "%04d-%02d-%02d %02d:%02d:%02d",
		
												tmDest.tm_year,
												tmDest.tm_mon,
												tmDest.tm_mday,
												tmDest.tm_hour,
												tmDest.tm_min,
												tmDest.tm_sec);

		return sDatetime;
	}
	catch(...)
	{
		return "";
	}
}

//------------------------------------------------------------------------------------------------------------------------

void ado_db::CloseRecordset(void)
{
  try
	{
 	  // Fecha o recordset se ele estiver aberto
	  if(pRecordSet->State == adStateOpen)
		{
  		pRecordSet->Close();
	  }

    /*
    for( int i = 0; i < MAX_RECORDSETS; i++)
    {
      if( pAllRecordSet[i] == NULL )
        break;

      if( pAllRecordSet[i]->State == adStateOpen)
      {
        pAllRecordSet[i]->Close();
      }
    }
    */
	}
	catch( _com_error &c_error ){

		bFail = true;
	
		SetLastError( c_error );
	}
}

//------------------------------------------------------------------------------------------------------------------------

void ado_db::CheckDBConnection(ErrorsPtr pErrors)
{
  ErrorPtr  pErr = NULL;
  CStdString errorMsg, strConnection, adoErrorMsg;

  try
  {
    long nCount = pErrors->Count;

    adoErrorMsg = "";
    for(long i = 0; i < nCount; i++)
    {
      pErr = pErrors->GetItem(i);

      if( _stricmp( (LPCSTR)pErr->SQLState, LINK_FAILURE) == 0)
      {
        adoErrorMsg += pErr->Description;

        errorMsg.Format("Database connection error \r\n"
                        "DSN: %s \r\n"
                        "DB Server: %s \r\n"
                        "Error Description: \r\n"
                        "%s", 
                        sDSN.c_str(), 
                        (LPCSTR)bstrServerName,
                        adoErrorMsg.GetBuffer(0));
      }
      adoErrorMsg += pErr->Description;
    }
  }
	catch(...)
	{
	}
}

//------------------------------------------------------------------------------------------------------------------------

const char *ado_db::GetColumnName(int Col)
{
	try {

		Col--;

		if( Col < 0 || Col > iNumCols ){
			return "";
		}

		vtIndex.iVal = Col;

		ColumnName = (LPSTR)pFields->GetItem( vtIndex )->GetName();

		return (char *)ColumnName.c_str();
	}
	catch(...)
	{
		return " ";
	}
}

//------------------------------------------------------------------------------------------------------------------------

//[11_08_2009<]
void ado_db::SetCommandTimeout(int t)
{
	if( t >= 30 )
		CommandTimeout = t;
	else
		CommandTimeout = 30;
}
//[11_08_2009>]

//------------------------------------------------------------------------------------------------------------------------
