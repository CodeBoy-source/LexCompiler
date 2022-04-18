#include <stdio.h>
#include <stdbool.h>
#include "scanner.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define SIZEARR(A) (sizeof(A) / sizeof(A[0]))


//Aquí tenemos que definir las funciones que vamos llamar de nuestro
//analizador léxico.
extern int yylex();
extern int yylineno;
extern char* yytext;

//Aquí vamos poniendo aquellas palabras reservadas que deseamos quitar para
//dar un mejor formato a nuestros prints. Intentamos ordenar según probabilidad.
//Aquí también importa el orden...Si no queremos definir varios vectores...
char* RESERVED[] = {"while","else","if","class",
	"case","float*", "int*","double*","char*","bool*","string*",
	"float**","int**","double**","char**", "int","float","double","char","auto","for"};

unsigned int SZ_RES=21;

char* FUNT[] = {"template","include","define","using","void","extern","inline",
	"cout","cin","printf","return"};

unsigned int SZ_FUNT=11;

char* DOXYGEN[] = { "author","extern","param","return"};

unsigned int SZ_DOX=4;

//Funciones extras que he definido para formatear y arreglar las expresiones
//encontradas por flex.
char *removeSpaces(char *str);
char *removeDuplicateSpaces(char * str);
int endOfMatch(char * str, char*  WHERE[],unsigned int MAX);
char * findEqual(char * str,char* WHERE[],unsigned int MAX);
char * findQuotes(char * str);
int givePosTil(char * str,char stop,unsigned int i);
void fixTabular(int tabular);
void skipChar(char *str, char skip);


/* Es básicamente un menu de traducción por medio de switches.
 * No necesita nada más que lo que devuelve nuestro analizador.
 * @author Brian Sena Simons
 */
int main(void){

	int ntoken, vtoken;
	int tabular=0;

	int cont = 0;

	ntoken = yylex();
	while(ntoken){
		if(tabular==0 && ntoken==END)
			printf("\n");
		if(tabular>0){
			cont = 0;
			while(cont<tabular){
				printf("\t");
				cont++;
			}
		}
		//removeDuplicateSpaces(yytext);
		switch(ntoken){
			case DECNUM:
				{
					findEqual(yytext,RESERVED,SZ_RES);
					int i = givePosTil(yytext,',',0);
					char opt[25];
					if(i>0)
						sprintf(opt,"UNOS VALORES NÚMERICOS");
					else
						sprintf(opt,"UN VALOR NÚMERICO");

					printf("DECLARAMOS %s: %s\n", opt, yytext);
					break;
				}
			case DECVAR:
				{
					findEqual(yytext,RESERVED,SZ_RES);
					printf("ESTABLECEMOS QUE: %s\n",yytext);
					break;
				}
			case BOOLVAR:
				{
					findEqual(yytext,RESERVED,SZ_RES);
					int i = givePosTil(yytext,',',0);
					char opt[20];
					if(i<0)
						sprintf(opt,"EL CONDICIONAL");
					else
						sprintf(opt,"LOS CONDICIONALES");
					printf("DEFINIMOS %s: %s\n",opt,yytext);
					break;
				}
			case CHARNUM:
				{
					findEqual(yytext,RESERVED,SZ_RES);
					printf("DEFINIMOS EL CARACTER: %s\n",yytext);
					break;
				}
			case DECARR:
				{
					printf("DECLARAMOS EL VECTOR: %s\n", yytext);
					break;
				}
			case STARTARR:
				{
					printf("INICIALIZAMOS EL VECTOR: %s\n", yytext);
					break;
				}

			case DEC:
				{
					printf("ASIGNAMOS: %s\n", yytext);
					break;
				}
			case INCVAR:
				{
					int i = givePosTil(yytext,'+',0);
					if(i>0)
						printf("INCREMENTAMOS LA VARIABLE: %s\n",yytext);
					else
						printf("DECREMENTAMOS LA VARIABLE: %s\n",yytext);
					break;
				}
			case STD:
				{
					int i = givePosTil(yytext,',',0);
					char opt[20];
					if(i<0)
						sprintf(opt,"UNA ESTRUCTURA");
					else
						sprintf(opt,"UNAS ESTRUCTURAS");
					printf("NECESITAMOS %s COMO: %s\n",opt,yytext);
					break;
				}
			case STRING:
				{
					int i = givePosTil(yytext,',',0);
					char opt[5];
					if(i<0)
						sprintf(opt,"EL");
					else
						sprintf(opt,"LOS");
					findEqual(yytext,RESERVED,SZ_RES);
					printf("DEFINIMOS %s STRING: %s\n",opt,yytext);
					break;

				}
			case FOR: {
				findEqual(yytext,RESERVED,SZ_RES);
				skipChar(yytext,';');
				printf("PARA %s ", &yytext[1]);

				vtoken = yylex();
				if((vtoken > FORCON) || (vtoken < FORCONNUM))
					printf("\t[ERROR]: Expected condition here %d %s \n",vtoken, yytext);
				else{
					removeSpaces(yytext);
					printf(" MIENTRAS %s ", yytext);

				}

				vtoken = yylex();
				if((vtoken<FORINCNUM) || (vtoken>FORINC))
					printf("\t[ERROR]: Expected Step here %d %s \n",vtoken, yytext);
				else if(vtoken==FORINC){
					int i = givePosTil(yytext,'+',0);
					char opt[30];
					if(i<0){
						i = givePosTil(yytext,'-',0);
						sprintf(opt,"DISMINUIMOS");
					}
					else
						sprintf(opt,"AUMENTAMOS");

					printf("%s UNO CADA VEZ Y HACEMOS:\n",opt);
				}
				else{
					removeSpaces(yytext);
					printf(" CON UN PASO DE %s HACEMOS:\n",yytext);
				}
				break;
			}
			case CIN:
				{
					vtoken=yylex();
					if(vtoken==IN){
						skipChar(yytext,';');
						printf("PEDIMOS AL USUARIO UN VALOR PARA: %s\n",findQuotes(yytext));
					}
					else{
						printf("\t[ERROR]: Expected Step here %d %s \n",vtoken, yytext);
					}
					break;
				}
			case PRINTF:
				{
					findEqual(yytext,FUNT,SZ_FUNT);
					findQuotes(yytext);
					printf("IMPRIMIMOS:[[ %s ]]\n",yytext);
					break;
				}
			case WHILE:
				{
					findEqual(yytext,RESERVED,SZ_RES);
					printf("MIENTRAS SE CUMPLA QUE: %s\n",yytext);
					break;
				}
			case IF:
				{
					findEqual(yytext,RESERVED,SZ_RES);
					printf("EN CASO DE QUE SE CUMPLA: %s\n",yytext);
					break;
				}
			case ELSE:
				{
					printf("EN CASO CONTRARIO: \n");
					break;
				}
			case ELSEIF:
				{
					findEqual(yytext,RESERVED,SZ_RES);
					findEqual(yytext,RESERVED,SZ_RES);
					printf("SI NO, VERIFICAMOS SI: ");
					printf("%s Y HACEMOS:\n",yytext);
					break;
				}
			case FUNCTION:
				{
					printf("DEFINIMOS LA FUNCIÓN:\n");
					fixTabular(tabular);
					skipChar(yytext,'{');
					printf("%s\n",yytext);
					break;
				}
			case CLASSFUNT:
				{
					int i = givePosTil(yytext,':',0);
					int j = i;
					while(j==i){
						j = givePosTil(yytext,':',i+2);
					}
					if(j>0)
						i=j;
					if(i>0){
						removeDuplicateSpaces(yytext);
						skipChar(yytext,'{');
						printf("DEFINIMOS EL MÉTODO: %s ",&yytext[i+2]);
						yytext[i] = '\0';
						printf("DE LA CLASE %s TAL QUE:\n",yytext);
					}
					else
						printf("[ERROR]: Unable to locate class limit\n");
					break;
				}
			case CALLFUNT:
				{
					printf("LLAMAMOS A LA FUNCIÓN: \n");
					fixTabular(tabular);
					printf("%s\n",yytext);
					break;
				}
			case RETURN:
				{
					findEqual(yytext,FUNT,SZ_FUNT);
					printf("RETORNAMOS: %s \n", yytext);
					break;
				}
			case TEMPLATE:
				{
					findEqual(yytext,FUNT,SZ_FUNT);
					printf("DEFINIMOS UNA PLANTILLA: %s\n",yytext);
					break;
				}
			case CLASS:
				{
					printf("CREAMOS UNA CLASE PARA ORGANIZAR LA INFORMACIÓN:\n");
					fixTabular(tabular);
					printf("%s\n",yytext);
					break;
				}
			case CLASSDEV:
				{
					char * trim;
					char * opt;
					unsigned int i=0;
					while(yytext[i]!=':')
						i++;
					unsigned int j=0;
					while(yytext[j])
						j++;
					strncpy(trim,yytext,(i)*sizeof(char));
					findEqual(trim,FUNT,SZ_FUNT);
					printf("CREAMOS UNA CLASE %s DERIVADA DE %s PARA ORGANIZAR LA INFORMACIÓN TAL QUE:\n",trim,&yytext[i+1]);
					fixTabular(tabular);
					printf("%s\n",yytext);
					break;
				}
			case PUBLIC:
				{
					fixTabular(tabular);
					printf("LA PARTE ACCESIBLE ES: \n");
					break;
				}
			case PRIVATE:
				{
					fixTabular(tabular);
					printf("LA PARTE PRIVADA ES: \n");
					break;
				}
			case STRUCT:
				{
					printf("VAMOS A DEFINIR UNA ESTRUCTURA DE INFORMACIÓN QUE SIGUE:\n");
					fixTabular(tabular);
					printf("%s\n",yytext);
					break;
				}
			case STRUCTNAME:
				{
					skipChar(yytext,'}');
					printf("LA LLAMAREMOS: %s\n",yytext);
					break;
				}
			case ENUM:{
				printf("NECESITAMOS DEFINIR NOMBRES DE INFORMACIÓN:\n");
				fixTabular(tabular);
				printf("%s\n",yytext);
				break;
			}
			case DOSOME:
				{
					removeDuplicateSpaces(yytext);
					printf("HACEMOS LO SIGUIENTE: %s \n", yytext);
					break;
				}
			case USING:
				{
					findEqual(yytext,FUNT,SZ_FUNT);
					printf("NOS AUXILIAMOS DE: %s \n", yytext);
					break;
				}
			case INCLUDE:
				{
					findEqual(yytext,FUNT,SZ_FUNT);
					removeDuplicateSpaces(yytext);
					printf("NECESITAMOS INCLUIR: %s \n", yytext);
					break;
				}
			case DEFINE:
				{
					findEqual(yytext,FUNT,SZ_FUNT);
					removeDuplicateSpaces(yytext);
					printf("NECESITAMOS DEFINIR: %s \n", yytext);
					break;
				}
			case COMM:
				{
					//printf("EL AUTOR NOS HA DEJADO ESTE(S) COMENTARIO(S):\n");
					//fixTabular(tabular);
					printf("%s\n",yytext);
					break;
				}
			case DOX:
				{
					//printf("EL PROGRAMA TIENE EL SIGUIENTE DOXYGEN:\n");
					fixTabular(tabular);
					skipChar(yytext,'*');
					removeDuplicateSpaces(yytext);
					printf("\r#%s\n",&yytext[1]);
					vtoken = yylex();
					while(vtoken>DOX && vtoken<PRINTALL+1){
						fixTabular(tabular);
						switch(vtoken){
							case PRINTALL:
								{
									printf("* %s\n",yytext);
									break;
								}
							case DOXAUT:
								{
									findEqual(yytext,DOXYGEN,SZ_DOX);
									removeDuplicateSpaces(yytext);
									printf("* EL AUTOR ES: %s\n",yytext);
									break;
								}
							case DOXPAR:
								{
									findEqual(yytext,DOXYGEN,SZ_DOX);
									removeDuplicateSpaces(yytext);
									printf("* TENEMOS UN PARÁMETRO: %s\n",yytext);
									break;
								}
							case DOXEXT:
								{
									findEqual(yytext,DOXYGEN,SZ_DOX);
									removeDuplicateSpaces(yytext);
									printf("* NECESITAMOS A LA FUNCIÓN: %s\n",yytext);
									break;
								}
							case DOXRET:
								{
									findEqual(yytext,DOXYGEN,SZ_DOX);
									removeDuplicateSpaces(yytext);
									printf("* DEVOLVEMOS: %s\n",yytext);
									break;
								}
						}
						vtoken = yylex();
					}
					break;
				}
			case SWITCH:
				{
					printf("DEFINIMOS LAS SIGUIENTES POSIBILIDADES CON:\n");
					fixTabular(tabular);
					printf("%s\n",yytext);
					break;
				}
			case CASE:
				{
					findEqual(yytext,RESERVED,SZ_RES);
					printf("LA POSIBILIDAD %s\n",yytext);
					break;
				}
			case BREAK:
				{
					printf("REALIZAMOS UN BREAK(SALIR/PARAR)\n");
					break;
				}
			//default:printf("[WARNING] %s\n",yytext);break;
		}
		ntoken = yylex();
		tabular = 0;
		while(ntoken == TABULAR){
			tabular += 1 ;
			ntoken = yylex();
		}
		printf("\r");
	}

	printf("\n");
	return 0;
}

/* Esta función como su nombre indica es para quitar espacios en blanco
 * @author Brian Sena Simons
 * @param str cadena a editar
 * @return devuelve la misma cadena
 * En realidad el returno no es necesario ya que pasamos las cosas por
 * referencia pero me pareció buena idea en algún momento y lo dejé así.
*/
char *removeSpaces(char *str){
	int i=0, j=0;
	while(str[i]){
		if(str[i]!=' ')
		str[j++] = str[i];
			i++;
	}
	str[j]='\0';
	return str;
}

/* Una variación de nuestra función de quitar espacios en blanco,
 * Solo que ahora solamente lo haremos si es un espacio duplicado.
 * @author Brian Sena Simons
 * @param str cadena a editar.
 * @return la cadena editada
 * Otra vez, no era necesario...
*/
char *removeDuplicateSpaces(char * str){
	int i=0, j=0;
	if(str[i]){
		while(str[i+1]){
			if(str[i]==' ' && str[i+1]==' ')
				i++;
			else
				str[j++] = str[i];
			i++;
		}
		str[j++]=str[i];
		str[j]='\0';
	}
	return str;
}

/* Función que escribe una tarde noche para encontrar cadenas.
 * @author Brian Sena Simons
 * @param str cadena donde buscar.
 * @return valor númerico de la posición dónde terminamos el match.
 * Obviamente no funciona si Lo que deseamos quitar no está al principio
 * de la cadena, pero no era necesario cambiar eso ya que normalmente
 * lo usaremos para quitar la parte inicial. Aunque de cualquier modo ç
 * podríamos cambiar para pasar dos valores por referencia que sean
 * inicio y fin del match y así quitarnos de problemas.
*/
int endOfMatch(char * str,char* WHERE[],unsigned int MAX){
	int i=0, j=0, n=0, match = -1;
	while(n<MAX) {
		while(str[i]){
			if(str[i]==WHERE[n][j]){
				j++;
				if(WHERE[n][j]=='\0'){
					match = 1;
					break;
				}
			}
			else{
				j=0;
			}
			i++;
		}
		n++;
		if(match==1)
		break;
		else{
			i=0;
			j=0;
		}
	}
	if(match==1)
		return ++i;
	else
		return -1;
}

/* Esta es la función que quita palabras reservadas.
 * @author Brian Sena Simons
 * @param str cadena a editar
 * @extern endOfMatch(str);
 * @return la cadena editada
*/
char * findEqual(char * str, char* WHERE[],unsigned int MAX){
	int beg = endOfMatch(str,WHERE,MAX);
	if(beg<0){
		return str;
	}
	int i =	0;
	while(str[beg] && str[i]){
		str[i] = str[beg];
		beg++;
		i++;
	}
	str[i]='\0';
	return str;
}

/* Básicamente está función es para limpiar los cout del código.
 * Juntando todo en un mismo string.
 * @author Brian Sena Simons
 * @param str cadena a editar
 * @return cadena editada
*/
char * findQuotes(char * str){
	unsigned int i = 0,j = 0;
	bool quotes = false;
	while(str[i+1]){
		if(str[i]=='"'||str[i]==')'||str[i]=='(')
			quotes = !quotes;

		if(!quotes&&((str[i]=='<' && str[i+1]=='<')||(str[i]=='>'&&str[i+1]=='>'))){
			str[j++]=' ';
			i++;
		}
		else{
			str[j]=str[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
	return str;
}

/* Función que me indica dónde se encuentra la primera aparación de
 * un carácter dado
 * @author Brian Sena Simons
 * @param str cadena donde buscar
 * @param stop carácter que nos indica salida.
 * @return posición dónde se encontró ó -1;
*/
int givePosTil(char * str,char stop,unsigned int i){
	unsigned int j=0;
	while(str[i]){
		if(str[i]==stop){
			j=1;
			break;
		}
		i++;
	}
	if(j==1)
		return i;
	else
		return -1;
}

/* Función para arreglar la tabulación.
 * @author Brian Sena Simons
 * @param tabular número de veces que hay que tabular
*/
void fixTabular(int tabular){
	unsigned int cont = 0;
	while(cont<tabular){
		printf("\t");
		cont++;
	}

}

/* Función para ignorar caractéres raros o no-deseados;
* @author Brian Sena Simons.
* @param str cadena a modificar
* @param skip caractér a ignorar
* Utiliza parámetros por referencia por lo que no es necesario
* devolver nada.
*/
void skipChar(char *str, char skip){
	unsigned int i=0,j=0;
	while(str[i]){
		if(str[i]==skip)
			i++;
		else
			str[j++]=str[i++];
	}
	str[j]='\0';
}
