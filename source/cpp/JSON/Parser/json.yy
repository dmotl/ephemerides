%{

#include <QtCore>

#include "CDriver.h"
#include "CIntParser.h"
#include "CLogger.h"
#include "Utils.h"
#include "CNode.h"
#include "CObject.h"
#include "CArray.h"
#include "CNullObject.h"
#include "CNumericValue.h"
#include "CTextValue.h"
#include "CLogicValue.h"
#include "CParserError.h"
#include "json_bison_output.h"

class tTerm { 
public:
	// Key (mandatory)
	QString* key;

	// Associated value (mandatory)
	JSON::CNode *value;

	tTerm() : key(NULL), value(NULL) {}
	~tTerm() { delete key; delete value; }
};

using namespace JSON;
using namespace JSON::Parser;
using tToken = JSON::Scanner::CToken;

static void yyerror(const tToken &tok, CIntParser* p, CDriver *drv, CLogger* logger, const char *msg);

static void program(const tToken &tok, CObject *map, CDriver *drv);

static CTextValue *primitiveStringValue(const tToken &tok, QString *str, CDriver *drv);
static CNumericValue *primitiveNumericValue(const tToken &tok, QString *str, CDriver *drv);
static CLogicValue *primitiveBooleanValue(const tToken &tok, bool val, CDriver *drv);
static CArray *listValue(const tToken &tok, CArray *list, CDriver *drv);
static CObject *mapValue(const tToken &tok, CObject *map, CDriver *drv);
static CNullObject *nullValue(const tToken &tok, CDriver *drv);

static CArray *addToList(const tToken &tok, CArray *list, CNode *value, CDriver *drv, bool prepend);
static CObject *addToMap(const tToken &tok, CObject *map, tTerm *term, CDriver *drv);

static tTerm *term(QString *key, CNode *value);
static QString *strCat(QString *str1, QString *str2);

%}

%union {
  QString* qstr;	
  JSON::CNode *value;
  JSON::CObject *map;
  JSON::CArray *list;
  class tTerm *term;
}

%start program
%param { const JSON::Scanner::CToken &tok }
%param { JSON::Parser::CIntParser *p }
%parse-param { JSON::Parser::CDriver *drv }
%parse-param { JSON::Parser::CLogger *logger }

%type <value> value 
%type <map> suite suite_2 object
%type <list> tuple tuple_2 array
%type <term> term
%type <qstr> string

%token <qstr> T_STR T_NUM 
%token T_NULL T_TRUE T_FALSE T_COMMA T_COLON 
%token T_BEGIN_LIST T_END_LIST T_BEGIN_OBJ T_END_OBJ 

%define api.pure full
%define api.push-pull push

%destructor { delete $$; } <*>

%% /* beginning of rules section */

/* Start non-terminal */
program	
		: object
		    { program(tok, $1, drv); }
		;

object  
        : T_BEGIN_OBJ suite T_END_OBJ
		    { $$ = mapValue(tok, $2, drv); }
		;

/* Content of an associative list, can be empty */
suite
		: %empty /* Empty */
			{ $$ = NULL; }
		| suite_2
		;

/* Content of an associative list, non-empty */
suite_2
		: term
			{ $$ = addToMap(tok,NULL,$1,drv); }
		| suite_2 T_COMMA term
		    { $$ = addToMap(tok,$1,$3,drv); }
		;

/* An item of the associative list */
term  
		: T_STR T_COLON value
			{ $$ = term($1,$3); }
		;

/* Second part of key = value pair */
value
		: string
			{ $$ = primitiveStringValue(tok,$1,drv); }
		| T_NUM
			{ $$ = primitiveNumericValue(tok,$1,drv); }
		| T_TRUE
			{ $$ = primitiveBooleanValue(tok,true,drv); }
		| T_FALSE
			{ $$ = primitiveBooleanValue(tok,false,drv); }
		| T_NULL
			{ $$ = nullValue(tok,drv); }
		| array
		    { $$ = $1; }
		| object
		    { $$ = $1; }
		;

/* String (string concatenation) */
string
		: T_STR
			{ $$ = $1; }
		| string T_STR
			{ $$ = strCat($1, $2); }
		;

array 
        : T_BEGIN_LIST tuple T_END_LIST
			{ $$ = listValue(tok,$2,drv); }
		;

/* Content of an ordered list, can be empty */
tuple
		: %empty /* Empty */
			{ $$ = NULL; }
		| tuple_2
		;

/* Content of an ordered list, non-empty */
tuple_2
		: value 
			{ $$ = addToList(tok,NULL,$1,drv,false); }
		| tuple_2 T_COMMA value
			{ $$ = addToList(tok,$1,$3,drv,false); }
		;

%%

//
// Error reporting
//
static void yyerror(const tToken &tok, CIntParser* p, CDriver *drv, CLogger* logger, const char *s)
{
	if (strcmp(s, "syntax error") == 0) {
		logger->log(CParserSyntaxError(p, tok));
	}
	else if (strcmp(s, "memory exhausted") == 0) {
		logger->log(CParserMemoryError(p, tok));
	}
}


//
// Typecast to custom value or create a new list 
//
static CArray *listValue(const tToken &tok, CArray *list, CDriver* drv)
{
	return (list ? list : drv->list(tok));
}


//
// Typecast to custom value or create a new map
//
static CObject *mapValue(const tToken &tok, CObject *map, CDriver* drv)
{
	return (map ? map : drv->map(tok));
}


//
// Create a null value (a special "undefined" value)
//
static CNullObject *nullValue(const tToken &tok, CDriver* drv)
{
	return drv->null(tok);
}


//
// Make a primitive value (string value)
//
static CTextValue *primitiveStringValue(const tToken &tok, QString *str, CDriver* drv)
{
	if (str) {
		CTextValue* retval = drv->primitiveStringValue(tok, *str);
		delete str;
		return retval;
    }
	return NULL;
}


//
// Make a primitive value (numeric value)
//
static CNumericValue *primitiveNumericValue(const tToken &tok, QString *str, CDriver* drv)
{
	if (str) {
		CNumericValue* retval = drv->primitiveNumericValue(tok, *str);
		delete str;
		return retval;
    }
	return NULL;
}


//
// Make a primitive value (logic value)
//
static CLogicValue *primitiveBooleanValue(const tToken &tok, bool val, CDriver* drv)
{
	return drv->primitiveBooleanValue(tok, val);
}


//
// Add to value list
//
static CArray *addToList(const tToken &tok, CArray *list, CNode *arg, CDriver *drv, bool prepend)
{
	if (arg) {
		list = listValue(tok, list, drv);
		if (list) {
			if (!prepend)
				list->append(arg);
			else
				list->prepend(arg);
		}
		else
			delete arg;
	}
	return list;
}


//
// Add to value list
//
static CObject *addToMap(const tToken &tok, CObject *map, tTerm *term, CDriver *drv)
{
	if (term && term->key) {
		map = mapValue(tok, map, drv);
		if (map) {
			map->insert(*term->key, term->value);
			term->value = NULL;
		}
	}
	delete term;
	return map;
}


//
// Create a key, value pair (term is one item in a dictionary)
//
static tTerm *term(QString *key, CNode *value)
{
	if (key && value) {
		tTerm *retval = new tTerm();
		retval->key = key;
		retval->value = value;
		return retval;
	}
	else {
		delete key;
		delete value;
		return NULL;
	}
}


//
// Concatenate two strings
//
static QString *strCat(QString *str1, QString *str2)
{
	if (!str1)
		return str2;
	if (!str2)
		return str1;

	QString *retval = new QString(*str1 + *str2);
	delete str1;
	delete str2;
	return retval;
}


//
// Set top-level object
//
static void program(const tToken &tok, CObject *map, CDriver *drv)
{
	drv->setContents(tok, map);
}
