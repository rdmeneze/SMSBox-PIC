#include "funcoes.h"
#include <string.h>
#include "StdString.h"
#include <windows.h>
#include <direct.h>


//---------------------------------------------------------------------------------------------

DWORD atohex( const char * cHex ){
  DWORD dwRet = 0;
  unsigned char bLen;
  unsigned char i;
  char cVal;


  bLen = (unsigned char)strlen( cHex );
  i = bLen;

  for ( ; i ; i--){
    if ( (cHex[ i - 1 ] >= '0') && (cHex[ i - 1 ] <= '9') ){
      cVal = cHex[ i - 1 ] - '0';
    }
    else if ( (cHex[ i - 1 ] >= 'A') && (cHex[ i - 1 ] <= 'F') ){
      cVal = cHex[ i - 1 ] - 'A' + 10;
    }
    else if ( (cHex[ i - 1 ] >= 'a') && (cHex[ i - 1 ] <= 'f') ){
      cVal = cHex[ i - 1 ] - 'a' + 10;
    }
    else{
      break;
    }
    
    dwRet += (cVal << (4 * (bLen - i)));
  }

  return dwRet;
}

//---------------------------------------------------------------------------------------------

int ParseIntList( const char * cList, std::vector<int> &lstParam )
{
  CStdString sList;
  CStdString sSubList;
  CStdString sAux;
  int i, j;
  int iRIni; 
  int iRFim;
  int iRangeIndexI;
  const CStdString sTotem(";,");
  // pode separar por ;,- . [,;] identificam um campo

  lstParam.clear();
  sList = cList;

  i = 0;
  j = 0;

  do
  {
    i = sList.find_first_of( (LPCSTR)sTotem, j );
    if ( i == std::string::npos )
    {
      i = sList.GetLength();
      if ( j >= i )
      {
        break;
      }
    }

    sSubList = sList.substr( j, i-j );

    if ( sSubList.find( '-' ) != std::string::npos )
    {
      iRangeIndexI = sSubList.find( '-' );
      if ( iRangeIndexI == 0 || iRangeIndexI == sSubList.GetLength() )
      {
        lstParam.clear();
        return -1;
      }

      iRIni = atoi( (LPCSTR)sSubList );
      iRFim = atoi( sSubList.substr( iRangeIndexI + 1, sSubList.GetLength() ).c_str() );
      
      DWORD dwTmp;

      if ( iRIni > iRFim )
      {
        dwTmp = iRFim;
        iRFim = iRIni;
        iRIni = dwTmp;
      }

      for ( ; iRIni <= iRFim; iRIni++ )
      {
        lstParam.push_back( iRIni );
      }

    }
    else
    {
      lstParam.push_back( atoi( (LPCSTR)sSubList ) );
    }

    j = i+1;
  }while(true);

  unique( lstParam.begin(), lstParam.end() );
  return 0;
}

//---------------------------------------------------------------------------------------------

void MakePath(const char *s)
{
	//[25664<]
	char sPath[ _MAX_PATH + 512 ];
	//[25664>]
	char *p;

	try {

		strcpy(sPath, s);

		p = strchr(sPath, '\\' );
		
		while( p ){				
			p[0] = 0;
			_mkdir( sPath );
			p[0] = '\\';
			p = strchr( p+1, '\\' );		
		};

		_mkdir( sPath );
	}
	catch(...){
	}
}

//---------------------------------------------------------------------------------------------