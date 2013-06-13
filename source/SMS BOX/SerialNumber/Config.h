/**
 *  Config
 *  Interface realiza��o da leitura da configura��o da aplica��o. 
 *  Autor : Rafael Dias Menezes
 *  Data  : Ago/2009
 */

#ifndef __CONFIG__
#define __CONFIG__

#include "StdString.h"

class ConfigInterface{
public:
  virtual void SetKeyName(const char * sKey)  = 0;
  virtual const char* GetKeyName(void)        = 0;
  virtual void GetValue(const char *sValue, const char *sDefaultValue, unsigned short &Value) = 0;
  virtual void GetValue(const char *sValue, const char *sDefaultValue, int &Value) = 0;
  virtual void GetValue(const char *sValue, const char *sDefaultValue, bool &Value) = 0;
  virtual void GetValue(const char *sValue, const char *sDefaultValue, char *Value) = 0;
  virtual void GetValue(const char *sValue, const char *sDefaultValue, char& Value) = 0;
  virtual void GetValue(const char *sValue, const char *sDefaultValue, CStdString &Value) = 0;
  virtual void GetValue(const char *sValue, const char *sDefaultValue) = 0;
  virtual ~ConfigInterface( void ) {};
};

#endif //~ __CONFIG__
