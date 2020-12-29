#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;


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
            cout << "< " << lookUp(name)->getName() << ", " << lookUp(name)->getType() << " >" << "already exists in current ScopeTable" << endl;
            return false;
        }
        else if(symbols[idx].getName() == ""){
            symbols[idx].setInfo(name, type);
            symbols[idx].index = idx;
            symbols[idx].chain_idx = 0;
            cout << "Inserted in ScopeTable# " << scopeId << " at position " << idx << ", 0" << endl;
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
            cout << "Inserted in ScopeTable# " << scopeId << " at position " << idx << ", " << position << endl;
            return true;
        }
        return false;
    }

    bool deleteEntry(string name){
        int idx = hashFunction(name);
        SymbolInfo *temp, *prev;
        temp = &symbols[idx];
        if(lookUp(name) == NULL){
            cout << "Not Found\n";
            return false;
        }
        else if(temp->getName() == name){
            if(temp->next == NULL){
                temp->setInfo("", "");
                cout << "Deleted entry at " << idx << ", 0" << " from current ScopeTable" << endl;
                return true;
            }
            else{
                temp->setInfo(temp->next->getName(), temp->next->getType());
                temp->next = temp->next->next;
                cout << "Deleted entry at " << idx << ", 0" << " from current ScopeTable" << endl;
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

        cout << "ScopeTable # " << scopeId << endl;

        for(int i = 0; i < bucketSpace; i++){
            cout << i  << " --> ";
            if(symbols[i].getName() == ""){
                cout << endl;
                continue;
            }
            else{
                SymbolInfo *temp;
                temp = &symbols[i];
                while(temp != NULL){
                    cout << "< " << temp->getName() << " : " << temp->getType() << " >  ";
                    temp = temp->next;
                }
                cout << endl;
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
        cout << "New ScopeTable with id " << idCount << " created" << endl;
    }
    bool exitScope(){
        ScopeTable *temp;
        temp = currentScope;
        currentScope = currentScope->parentScope;
        delete temp;
        cout << "ScopeTable with id " << idCount << " removed " << endl;
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
                cout << "Found in ScopeTable# " << temp->scopeId << " at position " << result->index << ", " << result->chain_idx << "\n\n";
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
        delete currentScope;
    }
};


int main()
{
    int bucket;

    string str;

    ifstream input("input.txt");

    input >> bucket;

    SymbolTable symbolTable(bucket);

    while(!input.eof()){
        input >> str;
        if(str == "I"){
            string name, type;
            input >> name;
            input >> type;

            cout << "I " << name << " " << type << "\n\n";

            symbolTable.insertinCurrentScope(name, type);
            //cout << name << endl << type;
            cout << endl;
        }
        else if(str == "L"){
            string name;
            input >> name;
            cout << "L " << name << "\n\n";

            //SymbolInfo *info = symbolTable.lookUp(name);

            if(symbolTable.lookUp(name) != NULL){
                cout << endl;
            }
            else{
                cout << "Not Found\n\n";
            }
        }
        else if(str == "P"){
            string code;
            input >> code;

            cout << "P " << code << "\n\n";

            if(code == "C") symbolTable.printCurrrent();
            else  symbolTable.printAll();

            cout << endl;

        }

        else if(str == "D"){
            string name;
            input >> name;

            cout << "D " << name << "\n\n";

            if(symbolTable.lookUp(name) != NULL){
                symbolTable.removefromCurrentScope(name);
                cout << "\n\n";
            }
            else{
                cout << "Not Found\n\n";
                cout << name << " not found\n\n";
            }
        }

        else if(str == "S"){
            cout << "S \n\n";
            symbolTable.enterScope();
            cout << endl;
        }

        else if(str == "E"){
            cout << "E \n\n";
            symbolTable.exitScope();
            cout << endl;
        }

    }


    return 0;
}
