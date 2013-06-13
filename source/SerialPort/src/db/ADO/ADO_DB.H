
#ifndef ADO_DB_H
	#define ADO_DB_H

#include "sql_db.h"
#include <math.h>
#include <ole2.h>
#include "StdString.h"

#import "c:\Program Files\Common Files\System\ADO\msado15.dll" no_namespace rename("EOF", "EndOfFile")

#define MAX_RECORDSETS 100

enum ADO_TYPES {
	ADO_MICROSOFT,
	ADO_ORACLE,
	ADO_SYBASE,
};

class ado_db : public sql_db {

	private:

		// Numero de colunas do resultado
		int iNumCols;
		// Numero de linhas do resultado
		int iNumRows;
		// Tipo de ADO
		int AdoType;
    // Qtde de recordsets retornado pela consulta
    int TotalRecordsets;
		//[11_08_2009<]
		// Tempo maximo para a execucao de query em segundos
		int CommandTimeout;
		//[11_08_2009<]

    // Matriz de recordsets retornado pela pesquisa
    _RecordsetPtr pAllRecordSet[MAX_RECORDSETS];
		// Se true, indica que deve ser feita a reconexao com o banco de dados
		bool bFail;

    _bstr_t bstrServerName;

		// Auxilia na conversao de datetime para CStdString no formato yyyy-mm-dd hh:dd:ss
		char sDatetime[64];
		
		//[16_04_2010<]
		CStdString sConnectionString;
		//[16_04_2010>]
		// Data Source Name
		CStdString sDSN;
		// Nome do banco de dados
		CStdString sDataBase;
		// Nome do usuario
		CStdString sUser;
		// Senha do banco de dados
		CStdString sPassword;
		// Variavel que contem o ultimo erro
		CStdString sLastError;
		// Variavel que guarda o valor do campo atual do recotdset
		CStdString sField;
		// Variavel que guarda o valor da coluna
		CStdString ColumnName;
		// String de conexao
		CStdString sConnection;
		// Variaval para guardar a propriedade do valor do campo na verificacao de valores NULL
		_variant_t propValue;
		// Variaval indexadora para obter os nomes dos campos quando houver
		_variant_t vtIndex;
		// Varial para o campo
		_variant_t vtField;
		// Ponteiro de RecordSet
		_RecordsetPtr pRecordSet;
		// Ponteiro para os campos do record set
		FieldsPtr pFields;    
		// Variavel para guardar o tipo do campo
		DataTypeEnum FieldType;
		// Handle de resultados
		HRESULT hResult;
		// Ponteiro de conexao ADO
		_ConnectionPtr pConnection;

		// Guarda o ultimo error ocorrido no acesso ao banco de dados
		void SetLastError( _com_error &c_error );
		// Abre conexao usando o objeto ADO no banco de dados Oracle
		int OpenOracle(void);
		// Abre conexao usando o objeto ADO Microsoft
		int OpenMicrosoft(void);
		// Abre conexao usando o objeto ADO no banco de dados Sybase
		int OpenSybase(void);
    // Verifica a conexao com o BD se foi quebrada
    void CheckDBConnection(ErrorsPtr pErrors);

    // Fecha recordsets utilizados na ultima pesquisa
    void CloseRecordset(void);

	public:

		//[16_04_2010<]
		// Abre conexao com  servidor de bando de dados
		int Open(	const char *ConnectionString,
							const char *DSN,
							const char *DataBase,
							const char *User,
							const char *Password,
							int type = 0);
		//[16_04_2010>]
		// Fecha a conexao com o banco de dados
		void Close(void);
		// Retorna o numero de colunas
		int GetColCount(void);
		// Retorna o numero de colunas
		int GetRowCount(void);
		// Retorna o nome da coluna
		char *GetField(int Row, int Col);
		// Executa um comando SQL e retorna os dados e o numero de linhas e colunas
		int Query( const char *sCommand, bool bTransaction = false );
		// Retorna a ultima mensagem de erro
		const char *GetLastError(void);
		// Converte uma data para o padrao "yyyy-mm-dd hh:mm:ss"		
		char*	DateToStr(DATE dtSrc);
		// captura o nome da coluna
		const char*	GetColumnName(int Col);

		//[11_08_2009<]
		void SetCommandTimeout(int t = 30);
		//[11_08_2009>]

		// Construtor
		ado_db();
		// Destrutor
		~ado_db();
};

#endif


