#ifndef __FUNCOES__
#define __FUNCOES__

#include <windows.h>
#include <vector>

DWORD atohex( const char * cHex );

int ParseIntList( const char * cList, std::vector<int> &lstParam );

// Cria todos os diretorios do path passado
void MakePath(const char *s);

#endif