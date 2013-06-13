#ifndef __TYPES__
#define __TYPES__

#include <windows.h>
#include <map>
#include <string>
#include <vector>
#include <list>

// map types
typedef std::map< void* , void* >         MapPtrToPtr;
typedef std::map< void* , WORD  >         MapPtrToWord;
typedef std::map< WORD , void*  >         MapWordToPtr;
typedef std::map< DWORD , void*  >        MapDWordToPtr;
typedef std::map< std::string , void* >   MapStringToPtr;
typedef std::map< void* , std::string >   MapPtrToString;
typedef std::map< void* , DWORD  >        MapPtrToDWord;
typedef std::map< DWORD , DWORD  >        MapDWordToDWord;
typedef std::map< std::string , WORD  >   MapStringToWord;
typedef std::map< WORD , std::string  >   MapWordToString;
typedef std::map< std::string , DWORD  >  MapStringToDWord;
typedef std::map< DWORD , std::string  >  MapDWordToString;
typedef std::map< std::string , std::string  >  MapStringToString;

// vector types
typedef std::vector< std::string >        VectorString;
typedef std::vector< DWORD >              VectorDWord;
typedef std::vector< void* >              VectorPtr;

// list types
typedef std::list<std::string> LstString;

#endif