%option noyywrap

%x COMMENT

%x SINGLE_COMMENT

%x STRING

%{
#include<cstdio>
#include<cstdlib>
#include<string>
#include<vector>
#include <iostream>

using namespace std;

int line_count=1;
int erro_count = 0;
int temp_line_no = 0;

char string_buf[9999];
char *string_ptr;

FILE *logout;
FILE *tokenout;

int bucket = 20;


class SymbolInfo
{
    string name;
    string type;
public:
    int index;
    int chain_idx;
    SymbolInfo *next = NULL;
    SymbolInfo(){
        name = "";
        type = "";
        index = -1;
        chain_idx = -1;
    }
    SymbolInfo(string name, string type){
        this->name = name;
        this->type = type;
    }
    void setInfo(string name, string type){
        this->name = name;
        this->type = type;
    }
    void setName(string name){
        this->name = name;
    }
    void setType(string type){
        this->type = type;
    }
    void setNext(SymbolInfo *ptr){
        this->next = ptr;
    }
    string getName(){
        return name;
    }
    string getType(){
        return type;
    }

    void printInfo(){
        cout << name << " " << type << endl;
    }

    ~SymbolInfo(){
        delete next;
    }
};

class ScopeTable
{
public:
    SymbolInfo *symbols;
    ScopeTable *parentScope = NULL;
    int scopeId;
    int bucketSpace;

    ScopeTable(int bucketSpace, int scopeId){
        symbols = new SymbolInfo[bucketSpace];
        this->bucketSpace = bucketSpace;
        this->scopeId = scopeId;
    }

    int hashFunction(string name){
        unsigned long hashValue = 5381;
        for(int i = 0; i < name.length(); i++){
            hashValue =  ((hashValue << 5) + hashValue) + name[i];
        }
        return hashValue % bucketSpace;
    }

    SymbolInfo* lookUp(string name){
        int idx;
        idx = hashFunction(name);
        if(symbols[idx].getName() == ""){
            return NULL;
        }
        else if(symbols[idx].getName() == name){
            return &symbols[idx];
        }
        else{
            SymbolInfo *temp;
            temp = symbols[idx].next;
            while(temp != NULL){
                if(temp->getName() == name){
                    return temp;
                }
                temp = temp->next;
            }
            return NULL;
        }
    }

    bool insertEntry(string name, string type){
        int idx;
        idx = hashFunction(name);

        if(lookUp(name) != NULL){
            //cout << "< " << lookUp(name)->getName() << ", " << lookUp(name)->getType() << " >" << "already exists in current ScopeTable" << endl;
            return false;
        }
        else if(symbols[idx].getName() == ""){
            symbols[idx].setInfo(name, type);
            symbols[idx].index = idx;
            symbols[idx].chain_idx = 0;
            //cout << "Inserted in ScopeTable# " << scopeId << " at position " << idx << ", 0" << endl;
            return true;
        }
        else{
            SymbolInfo *temp;
            int position = 0;
            temp = &symbols[idx];
            while(temp->next != NULL){
                //cout << "inside 2" << endl;
                temp = temp->next;
                position++;
            }
            position++;
            temp->next = new SymbolInfo(name, type);
            temp->next->index = idx;
            temp->next->chain_idx = position;
            //cout << "Inserted in ScopeTable# " << scopeId << " at position " << idx << ", " << position << endl;
            return true;
        }
        return false;
    }

    bool deleteEntry(string name){
        int idx = hashFunction(name);
        SymbolInfo *temp, *prev;
        temp = &symbols[idx];
        if(lookUp(name) == NULL){
            //cout << "Not Found\n";
            return false;
        }
        else if(temp->getName() == name){
            if(temp->next == NULL){
                temp->setInfo("", "");
                //cout << "Deleted entry at " << idx << ", 0" << " from current ScopeTable" << endl;
                return true;
            }
            else{
                temp->setInfo(temp->next->getName(), temp->next->getType());
                temp->next = temp->next->next;
                //cout << "Deleted entry at " << idx << ", 0" << " from current ScopeTable" << endl;
                return true;
            }
        }
        else{
            prev = temp;
            temp = temp->next;
            while(temp != NULL){
                if(temp->getName() == name){
                    if(temp->next == NULL){
                        prev->next = NULL;
                        return true;
                    }
                    else{
                        prev->next = temp->next;
                        return true;
                    }
                }
                temp = temp->next;
            }
        }
    }

    void printScope(){

        //cout << "ScopeTable # " << scopeId << endl;

        fprintf(logout,"ScopeTable # %d\n", scopeId);

        for(int i = 0; i < bucketSpace; i++){
            if(symbols[i].getName() == ""){
                continue;
            }
            else{
                //cout << i  << " --> ";
                fprintf(logout,"%d --> ", i);
                SymbolInfo *temp;
                temp = &symbols[i];
                while(temp != NULL){
                    //cout << "< " << temp->getName() << " , " << temp->getType() << " >  ";
                    fprintf(logout,"< %s , %s > ", temp->getName().c_str(), temp->getType().c_str());
                    temp = temp->next;
                }
                //cout << endl;
                fprintf(logout, "\n");
            }
        }
        cout << endl;
    }

    ~ScopeTable(){
        delete symbols;
    }

};

class SymbolTable
{
public:
    ScopeTable *currentScope;
    int idCount;
    int bucketSpace;

    SymbolTable(int n){
        currentScope = new ScopeTable(n, 1);
        idCount = 1;
        bucketSpace = n;
    }

    bool enterScope(){
        ScopeTable *newTable;
        idCount++;
        newTable = new ScopeTable(bucketSpace, idCount);
        newTable->parentScope = currentScope;
        currentScope = newTable;
        //cout << "New ScopeTable with id " << idCount << " created" << endl;
    }
    bool exitScope(){
        ScopeTable *temp;
        temp = currentScope;
        currentScope = currentScope->parentScope;
        delete temp;
        //cout << "ScopeTable with id " << idCount << " removed " << endl;
        idCount--;
    }

    bool insertinCurrentScope(string name, string type){
        return currentScope->insertEntry(name, type);
    }

    bool removefromCurrentScope(string name){
        return currentScope->deleteEntry(name);
    }

    SymbolInfo* lookUp(string name){
        ScopeTable *temp;
        SymbolInfo *result;
        temp = currentScope;
        while(temp != NULL){
            result = temp->lookUp(name);
            if(result != NULL){
                //cout << "Found in ScopeTable# " << temp->scopeId << " at position " << result->index << ", " << result->chain_idx << "\n\n";
                return temp->lookUp(name);
            }
            temp = temp->parentScope;
        }
        return NULL;
    }

    void printCurrrent(){
        currentScope->printScope();
    }

    void printAll(){
        ScopeTable *temp;
        temp = currentScope;
        while(temp != NULL){
            temp->printScope();
            cout << endl;
            temp = temp->parentScope;
        }
    }

    ~SymbolTable(){
        //delete currentScope;
    }
};

SymbolTable symbolTable(bucket);

/*
class SymbolInfo{
public:
	string symbol;
	string type;
	SymbolInfo(){
		symbol="";type="";
	}
	SymbolInfo(string symbol,string type){
		this->symbol=symbol;this->type=type;
	}
};
class ScopeTable{
	vector<SymbolInfo *> syminfo;
	public:
	void insert(SymbolInfo *s){
		syminfo.push_back(s);
	}
	void print(){
		for(int i=0;i<syminfo.size();i++){
			fprintf(logout,"\n%s %s\n",syminfo[i]->symbol.c_str(),syminfo[i]->type.c_str());
		}
	}
};

ScopeTable st;

*/

%}

WHITESPACE [ \t\f\r\v]+ 
LETTER [a-zA-Z]
CHAR [a-zA-Z0-9 ]
DIGIT [0-9]
DIGITS [0-9]+
NEWLINE \n

%%

{WHITESPACE} 	{	}

{NEWLINE} {line_count++;}

"if"	{
			fprintf(tokenout,"<IF>");
			fprintf(logout,"Line no %d: TOKEN <IF> Lexeme %s found\n",line_count,yytext);
		}
		
"else"	{
			fprintf(tokenout,"<ELSE>");
			fprintf(logout,"Line no %d: TOKEN <ELSE> Lexeme %s found\n",line_count,yytext);
		}

"for"	{
			fprintf(tokenout,"<FOR>");
			fprintf(logout,"Line no %d: TOKEN <FOR> Lexeme %s found\n",line_count,yytext);
		}

"while"	{
			fprintf(tokenout,"<WHILE>");
			fprintf(logout,"Line no %d: TOKEN <WHILE> Lexeme %s found\n",line_count,yytext);
		}

"do"	{
			fprintf(tokenout,"<DO>");
			fprintf(logout,"Line no %d: TOKEN <DO> Lexeme %s found\n",line_count,yytext);
		}

"break"	{
			fprintf(tokenout,"<BREAK>");
			fprintf(logout,"Line no %d: TOKEN <BREAK> Lexeme %s found\n",line_count,yytext);
		}

"int"	{
			fprintf(tokenout,"<INT>");
			fprintf(logout,"Line no %d: TOKEN <INT> Lexeme %s found\n",line_count,yytext);
		}

"char"	{
			fprintf(tokenout,"<CHAR>");
			fprintf(logout,"Line no %d: TOKEN <CHAR> Lexeme %s found\n",line_count,yytext);
		}

"float"	{
			fprintf(tokenout,"<FLOAT>");
			fprintf(logout,"Line no %d: TOKEN <FLOAT> Lexeme %s found\n",line_count,yytext);
		}

"double"	{
			fprintf(tokenout,"<DOUBLE>");
			fprintf(logout,"Line no %d: TOKEN <DOUBLE> Lexeme %s found\n",line_count,yytext);
		}

"void"	{
			fprintf(tokenout,"<VOID>");
			fprintf(logout,"Line no %d: TOKEN <VOID> Lexeme %s found\n",line_count,yytext);
		}

"return"	{
			fprintf(tokenout,"<RETURN>");
			fprintf(logout,"Line no %d: TOKEN <RETURN> Lexeme %s found\n",line_count,yytext);
		}

"switch"	{
			fprintf(tokenout,"<SWITCH>");
			fprintf(logout,"Line no %d: TOKEN <SWITCH> Lexeme %s found\n",line_count,yytext);
		}

"case"	{
			fprintf(tokenout,"<CASE>");
			fprintf(logout,"Line no %d: TOKEN <CASE> Lexeme %s found\n",line_count,yytext);
		}

"default"	{
			fprintf(tokenout,"<DEFAULT>");
			fprintf(logout,"Line no %d: TOKEN <DEFAULT> Lexeme %s found\n",line_count,yytext);
		}

"continue"	{
			fprintf(tokenout,"<CONTINUE>");
			fprintf(logout,"Line no %d: TOKEN <CONTINUE> Lexeme %s found\n",line_count,yytext);
		}



"+"		|

"-"		{
			fprintf(tokenout,"<ADDOP,%s>",yytext);
			fprintf(logout,"Line no %d: TOKEN <ADDOP> Lexeme %s found\n",line_count,yytext);
			//insert in symbol table and print symbol table content(only non empty buckets)
			// There is a '|' in "+"'s rule, this means match execute the action for following rule
		}

"*"		|

"/"		|

"%"		{

			fprintf(tokenout,"<MULOP,%s>",yytext);
			fprintf(logout,"Line no %d: TOKEN <MULOP> Lexeme %s found\n",line_count,yytext);

		}

"++"	|

"--"	{

			fprintf(tokenout,"<INCOP,%s>",yytext);
			fprintf(logout,"Line no %d: TOKEN <INCOP> Lexeme %s found\n",line_count,yytext);

		}

"<"		|

"<="	|

">"		|

">="	|

"=="	|

"!="	{

			fprintf(tokenout,"<RELOP,%s>",yytext);
			fprintf(logout,"Line no %d: TOKEN <RELOP> Lexeme %s found\n",line_count,yytext);

		}

"="		{

			fprintf(tokenout,"<ASSIGNOP,%s>",yytext);
			fprintf(logout,"Line no %d: TOKEN <ASSIGNOP> Lexeme %s found\n",line_count,yytext);

		}

"&&"	|

"||"	{

			fprintf(tokenout,"<LOGICOP,%s>",yytext);
			fprintf(logout,"Line no %d: TOKEN <LOGICOP> Lexeme %s found\n",line_count,yytext);

		}

"&"		|

"|"		|

"^"		|

"<<"	|

">>"	{

			fprintf(tokenout,"<BITOP,%s>",yytext);
			fprintf(logout,"Line no %d: TOKEN <BITOP> Lexeme %s found\n",line_count,yytext);

		}

"!"		{

			fprintf(tokenout,"<NOT,%s>",yytext);
			fprintf(logout,"Line no %d: TOKEN <NOT> Lexeme %s found\n",line_count,yytext);

		}

"("		{

			fprintf(tokenout,"<LPAREN,%s>",yytext);
			fprintf(logout,"Line no %d: TOKEN <LPAREN> Lexeme %s found\n",line_count,yytext);

		}

")"		{

			fprintf(tokenout,"<RPAREN,%s>",yytext);
			fprintf(logout,"Line no %d: TOKEN <RPAREN> Lexeme %s found\n",line_count,yytext);

		}

"{"		{

			fprintf(tokenout,"<LCURL,%s>",yytext);
			fprintf(logout,"Line no %d: TOKEN <LCURL> Lexeme %s found\n",line_count,yytext);

		}

"}"		{

			fprintf(tokenout,"<RCURL,%s>",yytext);
			fprintf(logout,"Line no %d: TOKEN <RCURL> Lexeme %s found\n",line_count,yytext);

		}

"["		{

			fprintf(tokenout,"<LTHIRD,%s>",yytext);
			fprintf(logout,"Line no %d: TOKEN <LTHIRD> Lexeme %s found\n",line_count,yytext);

		}																					
		
"]"		{

			fprintf(tokenout,"<RTHIRD,%s>",yytext);
			fprintf(logout,"Line no %d: TOKEN <RTHIRD> Lexeme %s found\n",line_count,yytext);

		}

","		{

			fprintf(tokenout,"<COMMA,%s>",yytext);
			fprintf(logout,"Line no %d: TOKEN <COMMA> Lexeme %s found\n",line_count,yytext);

		}

";"		{

			fprintf(tokenout,"<SEMICOLON,%s>",yytext);
			fprintf(logout,"Line no %d: TOKEN <SEMICOLON> Lexeme %s found\n",line_count,yytext);

		}

[_a-zA-Z][_a-zA-Z0-9]*		{

			fprintf(tokenout,"<ID,%s>",yytext);
			fprintf(logout,"Line no %d: TOKEN <ID> Lexeme %s found\n",line_count,yytext);
			symbolTable.insertinCurrentScope(yytext, "ID");
			symbolTable.printCurrrent();

		}						

{DIGIT}+ 	{
				fprintf(tokenout,"<CONST_INT,%s>",yytext);
				fprintf(logout,"Line no %d: TOKEN <CONST_INT> Lexeme %s found\n",line_count,yytext);
				symbolTable.insertinCurrentScope(yytext, "CONST_INT");
				symbolTable.printCurrrent();
				//insert in symbol table and print symbol table content(only non empty buckets)
				//SymbolInfo *si=new SymbolInfo(string(yytext),"CONST_INT");
				//st.insert(si);
			}

{DIGIT}*\.{DIGIT}+(E[+-]?{DIGIT}+)?				{

			fprintf(tokenout,"<CONST_FLOAT,%s>",yytext);
			fprintf(logout,"Line no %d: TOKEN <CONST_FLOAT> Lexeme %s found\n",line_count,yytext);
			symbolTable.insertinCurrentScope(yytext, "CONST_FLOAT");
			symbolTable.printCurrrent();

		}	
			

'[a-zA-Z0-9]'		{

			fprintf(tokenout,"<CONST_CHAR,%c>",yytext[1]);
			fprintf(logout,"Line no %d: TOKEN <CONST_CHAR> Lexeme %s found\n",line_count,yytext);
			symbolTable.insertinCurrentScope(yytext, "CONST_CHAR");
			symbolTable.printCurrrent();

		}

'\\[tvaraf0bn]'		{

			fprintf(tokenout,"<CONST_CHAR,%c%c>",yytext[1],yytext[2]);
			fprintf(logout,"Line no %d: TOKEN <CONST_CHAR> Lexeme %s found\n",line_count,yytext);
			symbolTable.insertinCurrentScope(yytext, "CONST_CHAR");
			symbolTable.printCurrrent();

		}

"/*"			{

			temp_line_no = line_count;

			string_ptr = string_buf;

			*string_ptr++ = '/';
			*string_ptr++ = '*';

			BEGIN(COMMENT);

		}

<COMMENT>[^*\n]*		{

			char *yptr = yytext;

			while(*yptr){

				*string_ptr++ = *yptr++;

			}

		}

<COMMENT>"*"+[^*/\n]*		{

			char *yptr = yytext;

			while(*yptr){

				*string_ptr++ = *yptr++;

			}

		}		

<COMMENT>"*"+"/"		{

				BEGIN(INITIAL);

				char *yptr = yytext;

				while(*yptr){

					*string_ptr++ = *yptr++;

				}
				
				*string_ptr = '\0';

				fprintf(logout,"Line no %d: TOKEN <COMMENT> %s found\n",temp_line_no,string_buf);

		}

<COMMENT>\n 		{

			*string_ptr++ = '\n';
			line_count++;

		}

<COMMENT><<EOF>>		{

			fprintf(logout,"Error at line no %d: Unterminated comment %s\n",temp_line_no,string_buf);
			erro_count++;
			return 0;
		}		

"//"			{
	
			string_ptr = string_buf;

			temp_line_no = line_count;
			
			*string_ptr++ = '/';
			*string_ptr++ = '/';

			BEGIN(SINGLE_COMMENT);

		}

<SINGLE_COMMENT>[^\\\n]+ 	{

			char *yptr = yytext;

			while(*yptr){

				*string_ptr++ = *yptr++;

			}

		}

<SINGLE_COMMENT>\\\n  	{

			char *yptr = yytext;

			while(*yptr){

				*string_ptr++ = *yptr++;

			}

			line_count++;

		}

<SINGLE_COMMENT>\n 			{

			BEGIN(INITIAL);

			*string_ptr++ = '\0';

			fprintf(logout,"Line no %d: TOKEN <COMMENT> %s found\n",temp_line_no,string_buf);

			line_count++;


		}
	

<SINGLE_COMMENT><<EOF>>		{

			fprintf(logout,"Line no %d: TOKEN <COMMENT> %s found\n",temp_line_no,string_buf);

			return 0;
		}								

\" 				{
	
			BEGIN(STRING);
			string_ptr = string_buf;

		}

<STRING>\"		{

			BEGIN(INITIAL);
			*string_ptr = '\0';
			fprintf(tokenout,"<STRING,%s>",string_buf);
			fprintf(logout,"Line no %d: TOKEN <STRING> Lexeme %s found\n",line_count,string_buf);


		}

<STRING>\n		{

			*string_ptr = '\0';
			fprintf(logout,"Error at line no %d: Unterminated String %s\n",line_count,string_buf);
			line_count++;
			BEGIN(INITIAL);

	}

<STRING>\\n 	{

		*string_ptr++ = '\n';

}

<STRING>\\t 	{

		*string_ptr++ = '\t';

}

<STRING>\\r 	{

		*string_ptr++ = '\r';

}

<STRING>\\b 	{

		*string_ptr++ = '\b';

}

<STRING>\\f 	{

		*string_ptr++ = '\f';

}

<STRING>\\(.|\n) 	{

		*string_ptr++ = yytext[1];

}					

<STRING>[^\\\n\"]+ 	{

		char *yptr = yytext;

		while(*yptr){

			*string_ptr++ = *yptr++;

		}


}

{DIGITS}*((\.)+{DIGITS}+)+(E(\.)*[+-]?(\.)*{DIGITS})?(\.)*{DIGITS}*		{

			fprintf(logout,"Error at line no %d: Too many decimal point %s\n",line_count,yytext);
			erro_count++;

		}

{DIGITS}+(E(\.)*[+-]?(\.)*{DIGITS})?(\.)*{DIGITS}*		{

			fprintf(logout,"Error at line no %d: Ill formed number %s\n",line_count,yytext);
			erro_count++;

		}		

{DIGITS}{LETTER}+	|

{DIGITS}[_a-zA-Z]+{DIGIT}*	{

			fprintf(logout,"Error at line no %d: Invalid prefix on ID or invalid suffix on Number %s\n",line_count,yytext);
			erro_count++;

		}

'{CHAR}+{CHAR}+'			{

			fprintf(logout,"Error at line no %d: Multi character constant error %s\n",line_count,yytext);
			erro_count++;

		}

'({CHAR}*)?	|

'\\'		{

			fprintf(logout,"Error at line no %d: Unterminated character %s\n",line_count,yytext);
			erro_count++;

		}

''			{

			fprintf(logout,"Error at line no %d: Empty character constant error %s\n",line_count,yytext);
			erro_count++;

		}





%%

int main(int argc,char *argv[]){
	
	if(argc!=2){
		printf("Please provide input file name and try again\n");
		return 0;
	}
	
	FILE *fin=fopen(argv[1],"r");
	if(fin==NULL){
		printf("Cannot open specified file\n");
		return 0;
	}
	
	logout= fopen("log.txt","w");
	tokenout= fopen("token.txt","w");

	yyin= fin;
	yylex();
	//st.print();
	symbolTable.printCurrrent();
	fprintf(logout,"Total Lines %d \n",line_count);
	fprintf(logout,"Total Errors %d \n",erro_count);
	fclose(yyin);
	fclose(tokenout);
	fclose(logout);
	return 0;
}
