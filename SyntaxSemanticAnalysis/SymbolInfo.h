#include<cstdio>
#include<cstdlib>
#include<string>
#include<vector>
#include <iostream>

using namespace std;

class SymbolInfo
{
    string name;
    string type;
    string varType;
    string funcRetType;
public:
    int index;
    int chain_idx;
    int line_no;
    SymbolInfo *next = NULL;
    string code;
    SymbolInfo(){
        name = "";
        type = "";
        index = -1;
        chain_idx = -1;
        line_no = 0;
        code = "";
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
    void setVarType(string varType){
        this->varType = varType;
    }
    void setFuncRetType(string funcRetType){
        this->funcRetType = funcRetType;
    }
    void concatCode(string code){
        this->code = this->code + "\n" + code;
    }
    string getCode(){
        return code;
    }
    string getName(){
        return name;
    }
    string getType(){
        return type;
    }

    string getVarType(){
        return varType;
    }

    string getFuncRetType(){
        return funcRetType;
    }

    void printInfo(){
        cout << name << " " << type << endl;
    }

    ~SymbolInfo(){
        delete next;
    }
};
