/* scanner for a Generating Pseudo-like Code-language */
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scanner.h"
%}
/* SECCIÓN DE DEFINCIONES */
DIGITO					[0-9]
FLOTANTE				{ESPACIO}*[0-9]+([.][0-9]*)?{ESPACIO}*
LETRA					([a-zA-Z]|"á"|"ó"|"í"|"é"|"ú")
ESPACIO					[" "]
INI_COMENTARIO			["/*"]
FIN_COMENTARIO			["*/"]
GUIONES					[-_]
CHAR_COMA				{ESPACIO}*[","]{ESPACIO}*
CHAR_PUNTO				{ESPACIO}*["."]{ESPACIO}*
CHAR_PUNTOYCOMA			{ESPACIO}*[";"]{ESPACIO}*
QUOTES					{ESPACIO}*["]{ESPACIO}*
OP_SUMA					{ESPACIO}*"+"{ESPACIO}*
OP_RESTA				{ESPACIO}*"-"{ESPACIO}*
OP_MULT					{ESPACIO}*"*"{ESPACIO}*
OP_DIV					{ESPACIO}*"/"{ESPACIO}*
OP_IGUAL				{ESPACIO}*"="{ESPACIO}*
OP_MAYOR				{ESPACIO}*">"{ESPACIO}*
OP_MENOR				{ESPACIO}*"<"{ESPACIO}*
OP_MAYOR_IGUAL			{ESPACIO}*">="{ESPACIO}*
OP_MENOR_IGUAL			{ESPACIO}*"<="{ESPACIO}*
OP_COMP					{ESPACIO}*"=="{ESPACIO}*
OP_NEGACION				{ESPACIO}*"!"{ESPACIO}*
OP_DISTINTO				{ESPACIO}*"!="{ESPACIO}*

OP_DOS_PUNTOS			{ESPACIO}*":"{ESPACIO}*

LLAVE_A					{ESPACIO}*"{"{ESPACIO}*
LLAVE_C					{ESPACIO}*"}"{ESPACIO}*
PARENTESIS_A			{ESPACIO}*"("{ESPACIO}*
PARENTESIS_C			{ESPACIO}*")"{ESPACIO}*
SQUARE_A				{ESPACIO}*"["{ESPACIO}*
SQUARE_C				{ESPACIO}*"]"{ESPACIO}*
FIN_SENTENCIA			{ESPACIO}*";"{ESPACIO}*

IF						{ESPACIO}*"if"{ESPACIO}*
ELSE					{ESPACIO}*"else"{ESPACIO}*{LLAVE_A}?
ELSIF					{ESPACIO}*"else"{ESPACIO}*"if"{ESPACIO}*
CONST					{ESPACIO}*"const"|"static"{ESPACIO}*
NUMERIC					{ESPACIO}*("extern")?{ESPACIO}*("const"|"short"|"long"|"unsigned")?{ESPACIO}*("float"|"int"|"double"){ESPACIO}*
CHARTYPE				{ESPACIO}*("const"|"extern")?{ESPACIO}*"char"{ESPACIO}*
BOOLTYPE				{ESPACIO}*("const"|"extern")?{ESPACIO}*"bool"{ESPACIO}*
VECTOR					{ESPACIO}*"vector"{ESPACIO}*
STRING					{ESPACIO}*("const"|"extern")?{ESPACIO}*"string"{ESPACIO}*
FOR						{ESPACIO}*"for"{ESPACIO}*
WHILE					{ESPACIO}*"while"{ESPACIO}*
VOID					{ESPACIO}*"void"{ESPACIO}*

SIGNO					({OP_SUMA}|{OP_RESTA})

OP_ARITM	{ESPACIO}*({OP_SUMA}|{OP_RESTA}|{OP_DIV}|{OP_MULT}|"%"){ESPACIO}*
OP_LOGICA	{ESPACIO}*({OP_NEGACION}|{OP_COMP}|{OP_MAYOR}|{OP_MENOR}|{OP_MAYOR_IGUAL}|{OP_MENOR_IGUAL}|{OP_DISTINTO}){ESPACIO}*
OP_INC		{ESPACIO}*("++"|"--"){ESPACIO}*
OP_INCNUM	{ESPACIO}*("+="|"-="|"/="|"*="){ESPACIO}*

INCVAR		{ESPACIO}*({VARNAMES}{OP_INC}|{OP_INC}{VARNAMES}){ESPACIO}*{CHAR_PUNTOYCOMA}

FORDEFNUM	{PARENTESIS_A}{NUMERIC}[^!"#$%&?¿º;]+{OP_IGUAL}[^!"#$%&?¿º;]+{CHAR_PUNTOYCOMA}
FORDEF		{PARENTESIS_A}[^!"#$%&?¿º;]+{OP_IGUAL}[^!"#$%&?¿º;]+{CHAR_PUNTOYCOMA}
FORCON		([^"#$%&?¿º=;])+{OP_LOGICA}([^"#$%&?¿º;])+({CONCATENATE}?([^"#$%&?¿º;])+)*
FORINC		{CHAR_PUNTOYCOMA}({OP_INC}[^!"#$%&?¿º;]+|[^!"#$%&?¿º;]+{OP_INC}){PARENTESIS_C}{LLAVE_A}?
FORINCNUM   [^!"#$%&?¿º;]+{OP_INCNUM}[^!"#$%&?¿º;]+{PARENTESIS_C}{LLAVE_A}?
PRINTF		"printf"|"std::"?"cout"|{VARNAMES}"<<"

CHARVARTYPE			[']({LETRA}|{DIGITO}|{PUNCTUACTION})[']

PUNCTUACTION		{ESPACIO}*([!*'();:@&=+$,/?%#_.~]|"-"|"["|"]"){ESPACIO}*
COUT				{VARNAMES}*({OP_LOGICA}|{OP_ARITM})?{VARNAMES}*

OUT					{ESPACIO}*"<<"{ESPACIO}*
IN					{ESPACIO}*">>"{ESPACIO}*

INPUT				(({IN}(.)*)+|{PARENTESIS_A}["]((.)\n)*["]{PARENTESIS_C})

CONCATENATE			{ESPACIO}*("||"|"&&"){ESPACIO}*

STRINGPARENTESIS	[^;]*{CHAR_PUNTOYCOMA}
WHILEPARENTESIS		{PARENTESIS_A}([^;{}]*{CONCATENATE}?)+{PARENTESIS_C}

VARNAMES 			{ESPACIO}*{GUIONES}*{LETRA}+({GUIONES}|{LETRA}|{DIGITO})*{ESPACIO}*
VAR					{VARNAMES}(("->"|"."|"::"){VARNAMES}|([^;{}=]*))*

DECNUM				{NUMERIC}{OP_MULT}*({VARNAMES}({OP_IGUAL}({SIGNO}?{FLOTANTE}))?{CHAR_COMA}?)+{CHAR_PUNTOYCOMA}
DECVAR				{NUMERIC}{OP_MULT}*{VARNAMES}{OP_IGUAL}{VAR}{CHAR_PUNTOYCOMA}

STDTYPE				{ESPACIO}*({VECTOR}|"stack"|"queue"|"priority_queue"|"pair"|"map"){ESPACIO}*
STRINGTYPE			{STRING}({VARNAMES}({OP_IGUAL}({VAR}|["]((.)\n)*["]))?{CHAR_COMA}?)+{CHAR_PUNTOYCOMA}

DECSTD				{STDTYPE}{OP_MENOR}[^;{}]*{OP_MAYOR}({VARNAMES}({OP_IGUAL}{VAR})?{CHAR_COMA}?)+{CHAR_PUNTOYCOMA}

BOOLVAR				({BOOLTYPE}){OP_MULT}*({VARNAMES}({OP_IGUAL}{VAR}*)?{CHAR_COMA}?)+{CHAR_PUNTOYCOMA}

INITARR				({BOOLTYPE}|{NUMERIC}|{CHARTYPE}){OP_MULT}*
DECARR				{INITARR}{VARNAMES}({SQUARE_A}({DIGITO}*|{VARNAMES})?{SQUARE_C})+({OP_IGUAL}{VAR})?{CHAR_PUNTOYCOMA}
STARTARR			{INITARR}{VARNAMES}({SQUARE_A}({DIGITO}*|{VARNAMES})?{SQUARE_C})+{OP_IGUAL}{LLAVE_A}([^;(){}[\]]*{CHAR_COMA}?[\n]?)*{LLAVE_C}{CHAR_PUNTOYCOMA}

NEW					{ESPACIO}*"new"{ESPACIO}*
DEC					({VAR}|{VARNAMES})({OP_IGUAL}|{OP_INCNUM})(({SIGNO}?{FLOTANTE}|{VAR}|{VARNAMES}){CHAR_COMA}?)+{CHAR_PUNTOYCOMA}+
CHARNUM				({CHARTYPE}){OP_MULT}*{VARNAMES}({OP_IGUAL}{CHARVARTYPE})?{CHAR_PUNTOYCOMA}

RETURN				{ESPACIO}*"return"{ESPACIO}*[^;{}]*{CHAR_PUNTOYCOMA}?

DEFS				({BOOLTYPE}|{NUMERIC}|{CHARTYPE}|{STRING})({OP_MULT})*

SWITCH				{ESPACIO}*"switch"{ESPACIO}*{PARENTESIS_A}[^;(){}]*{PARENTESIS_C}{LLAVE_A}?
CASE				{ESPACIO}*("case"|"default"){ESPACIO}*({VARNAMES}|{FLOTANTE})":"

STRUCT				{ESPACIO}*"struct"{ESPACIO}*{VARNAMES}[\n]?{LLAVE_A}
STRUCTNAME			{LLAVE_C}{VARNAMES}{CHAR_PUNTOYCOMA}
CLASS				{ESPACIO}*"class"{ESPACIO}*{VARNAMES}
CLASSDEV			{ESPACIO}*"class"{ESPACIO}*{VARNAMES}{ESPACIO}*":"{ESPACIO}{VARNAMES}
ENUM				{ESPACIO}*"enum"{ESPACIO}*{VARNAMES}{LLAVE_A}([^;(){}[\]]*\n)*{LLAVE_C}{CHAR_PUNTOYCOMA}

EXTRA				({ESPACIO}*("inline"|"extern"){ESPACIO}*)?
INITFUNT			{EXTRA}({VOID}|{DEFS}|"ostream"|"istream"|{CONST})
OPERATOR			{ESPACIO}*"operator"{ESPACIO}*
FUNT				{INITFUNT}([^;(){}:=<![\]]+|[^;(){}:=<![\]]+{OPERATOR}[^;{}]+){PARENTESIS_A}[^;(){}]*{PARENTESIS_C}{CONST}?({LLAVE_A}|{CHAR_PUNTOYCOMA})?
CLASSFUNT			[^;(){}=<>![\]\n]+"::"[^;{}]+{LLAVE_A}
CALLFUNT			{VARNAMES}?{VARNAMES}{PARENTESIS_A}[^;{}]*{PARENTESIS_C}{CHAR_PUNTOYCOMA}

R_CLOSURE			({PARENTESIS_C}|{SQUARE_C})
L_CLOSURE			({SQUARE_A}|{PARENTESIS_A})
DOSOME				({OP_MULT}|("."|"->"|"::"|"<"|">"|" ")|{VARNAMES}|{L_CLOSURE}(([^;{}]*|['](.)+[']){CHAR_COMA}?)*{R_CLOSURE})*(({OP_IGUAL}|{OP_INCNUM})[^;{}]+)?{CHAR_PUNTOYCOMA}

%s COMMENT
%s FORTYPE
%s WAITINGNAME
%s CLASSDEF
%s DEF_FUN

%%
{SWITCH}										return SWITCH;
{CASE}											return CASE;

{ESPACIO}*"template"{OP_MENOR}[^;]{OP_MAYOR}	return TEMPLATE;

{STRUCT}										{ BEGIN(WAITINGNAME); return STRUCT;}
<WAITINGNAME>{STRUCTNAME}						{ BEGIN(INITIAL); return STRUCTNAME;}
{ENUM}											return ENUM;
{CLASS}											{ BEGIN(CLASSDEF); return CLASS; }
{CLASSDEV}										{ BEGIN(CLASSDEF); return CLASSDEV;}
<CLASSDEF>{ESPACIO}*"public:"{ESPACIO}*			return PUBLIC;
<CLASSDEF>{ESPACIO}*"private:"{ESPACIO}*		return PRIVATE;
{ESPACIO}*"#include"{ESPACIO}*(.)*				return INCLUDE;
{ESPACIO}*"#define"{ESPACIO}*(.)*				return DEFINE;
{ESPACIO}*"using"{ESPACIO}*(.)*					return USING;
{ESPACIO}*"std::"?"cin"{ESPACIO}*				return CIN;
{PRINTF}{STRINGPARENTESIS}						return PRINTF;
{ESPACIO}*"break"{ESPACIO}*{CHAR_PUNTOYCOMA}	return BREAK;

({ESPACIO}*"//"{ESPACIO}*(.)*)					return COMM;

{ESPACIO}*"/"{OP_MULT}{ESPACIO}*[^@]*{OP_MULT}"/"	{ return COMM; }

{ESPACIO}*"/"{OP_MULT}{ESPACIO}*([^@\n]-[*/])*	{ BEGIN(COMMENT);return DOX;}
<COMMENT>{OP_MULT}+"@author"(.)*				return DOXAUT;
<COMMENT>{OP_MULT}+"@param"(.)*					return DOXPAR;
<COMMENT>{OP_MULT}+"@return"(.)*				return DOXRET;
<COMMENT>{OP_MULT}+"@extern"(.)*				return DOXEXT;

<COMMENT>[^/@\n]*								{ return PRINTALL; }

([\t]*)?{OP_MULT}+"/"							{ BEGIN(INITIAL);printf("# FIN DE COMENTARIO\n"); return END;}

{DECNUM}										return DECNUM;
{DECVAR}										return DECVAR;

{DECARR}										return DECARR;
{STARTARR}										return STARTARR;

{DECSTD}										return STD;
{STRINGTYPE}									return STRING;

{BOOLVAR}										return BOOLVAR;

{CHARNUM}										return CHARNUM;

{IF}{WHILEPARENTESIS}							{ return IF; }
{ELSE}											return ELSE;
{ELSIF}{WHILEPARENTESIS}						{ return ELSEIF;}

{WHILE}{WHILEPARENTESIS}						{ return WHILE;}

{INPUT}											return IN;

{FOR}{FORDEF}									{ BEGIN(FORTYPE); return FOR;}
{FOR}{FORDEFNUM}								{ BEGIN(FORTYPE); return FOR;}
<FORTYPE>{FORCON}								return FORCON;
<FORTYPE>{FORINC}								{ BEGIN(INITIAL); return FORINC;}
<FORTYPE>{FORINCNUM}							{ BEGIN(INITIAL); return FORINCNUM;}

<INITIAL,DEF_FUN>{CALLFUNT}						return CALLFUNT;
<INITIAL,CLASSDEF>{FUNT}						{ BEGIN(DEF_FUN); return FUNCTION;}
<INITIAL>{CLASSFUNT}							{ BEGIN(DEF_FUN); return CLASSFUNT;}
{RETURN}										{ BEGIN(INITIAL); return RETURN; }

<INITIAL,CLASSDEF>{DEC}							return DEC;

{INCVAR}										return INCVAR;
<INITIAL,CLASSDEF>{DOSOME}						return DOSOME;

(([\t]|{ESPACIO})*{LLAVE_A}[\n]?|^{ESPACIO}?{LLAVE_A})	return START;
(([\t]|{ESPACIO})*{LLAVE_C}[\n]?){CHAR_PUNTOYCOMA}?		{ BEGIN(INITIAL); return END;}

[\t]											return TABULAR;

<INITIAL,CLASSDEF>^(?:[\t ]*(?:\r?\n|\r))+		printf("\n");

[ \n]|[\n]|[\b]									;

[;]												;

.												BEGIN(INITIAL);

%%

int yywrap(void){
	return 1;
}
