#include<cstdio>
#include<cstdlib>
#include<string>
#include<vector>
#include <iostream>

using namespace std;

extern FILE *fp2;

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

        fprintf(fp2,"ScopeTable # %d\n", scopeId);

        for(int i = 0; i < bucketSpace; i++){
            if(symbols[i].getName() == ""){
                continue;
            }
            else{
                //cout << i  << " --> ";
                fprintf(fp2,"%d --> ", i);
                SymbolInfo *temp;
                temp = &symbols[i];
                while(temp != NULL){
                    //cout << "< " << temp->getName() << " , " << temp->getType() << " >  ";
                    fprintf(fp2,"< %s , %s > ", temp->getName().c_str(), temp->getType().c_str());
                    temp = temp->next;
                }
                //cout << endl;
                fprintf(fp2, "\n");
            }
        }
        //cout << endl;
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
        //fprintf(fp2, "New ScopeTable with id %d created \n", idCount);
    }
    bool exitScope(){
        ScopeTable *temp;
        temp = currentScope;
        currentScope = currentScope->parentScope;
        temp = 0;
        delete temp;
        //cout << "ScopeTable with id " << idCount << " removed " << endl;
        //idCount--;
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
            //cout << endl;
            temp = temp->parentScope;
        }
    }

    ~SymbolTable(){
        //delete currentScope;
    }
};