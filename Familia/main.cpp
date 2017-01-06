#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <fstream>
#include <vector>
using namespace std;

struct persoanaStruct {
    string nume;
    char genul;
    persoanaStruct *parinte1 = 0;
    persoanaStruct *parinte2 = 0;
    persoanaStruct *partener = 0;
    unsigned int nrCopii;
    persoanaStruct *copii[];
};

vector<persoanaStruct*> listaPersoane;

void adaugarePersoanaInVector(string nume){
    bool esteInVector = false;
    persoanaStruct* persoana;
    for(int i=0;i<listaPersoane.size();i++){
        if(listaPersoane[i]->nume == nume){
            esteInVector = true;
            break;
        }
    }
    if(esteInVector == false){
        persoana = new persoanaStruct;
        persoana->nume = nume;
        persoana->nrCopii = 0;
        listaPersoane.push_back(persoana);
    }
};

void adaugareGenulPersoaneiInVector(string nume,char genul){
    for(int i=0;i<listaPersoane.size();i++){
        if(listaPersoane[i]->nume == nume){
            listaPersoane[i]->genul = genul;
        }
    }
}

void adaugareaRelatieiParinteCopil(string parinte, string copil){
    int pozitiaCopil = 0;
    for(int i=0;i<listaPersoane.size();i++){
        if(listaPersoane[i]->nume == copil){
            pozitiaCopil = i;
        }
    }
    for(int i=0;i<listaPersoane.size();i++){
        if(listaPersoane[i]->nume == parinte){
            if(listaPersoane[pozitiaCopil]->parinte1 == 0){
                listaPersoane[pozitiaCopil]->parinte1 = listaPersoane[i];
            }else{
                listaPersoane[pozitiaCopil]->parinte2 = listaPersoane[i];
            }

            if(listaPersoane[i]->nrCopii == 0){
                listaPersoane[i]->nrCopii = 1;
                listaPersoane[i]->copii[0] = listaPersoane[pozitiaCopil];
            }else{
                listaPersoane[i]->nrCopii = listaPersoane[i]->nrCopii + 1;
                listaPersoane[i]->copii[listaPersoane[i]->nrCopii - 1] = listaPersoane[pozitiaCopil];
            }
        }
    }
}

void adaugareRelatiePartener(){
    for(int i=0;i<listaPersoane.size();i++){
        if((listaPersoane[i]->parinte1)&&(listaPersoane[i]->parinte2)){
            listaPersoane[i]->parinte1->partener = listaPersoane[i]->parinte2;
            listaPersoane[i]->parinte2->partener = listaPersoane[i]->parinte1;
        }
    }
}

void citireCreareArboreGenealogic(){
    string opIntrare,numeParinte,numeCopil,numePersoana,numeGenPersoana;
    char genPersoana;
    ifstream inputFile;
    inputFile.open("input2.txt",ifstream::in);
    while((getline(inputFile,opIntrare,'('))&&((opIntrare=="parent")||(opIntrare=="\nparent"))){
        if(inputFile.eof())break;
        getline(inputFile, numeParinte, ',');
        adaugarePersoanaInVector(numeParinte);
        getline(inputFile, numeCopil, ')');
        adaugarePersoanaInVector(numeCopil);
        adaugareaRelatieiParinteCopil(numeParinte,numeCopil);
    }

    inputFile.clear();
    inputFile.seekg(0,ios::beg);

    while((getline(inputFile,numeGenPersoana, '\n'))){
        if((numeGenPersoana.find("parent")!=0)&&((numeGenPersoana.find("\nparent"))!=0)){
            int length = numeGenPersoana.length();
            genPersoana = numeGenPersoana[length-1];
            numePersoana=numeGenPersoana;
            numePersoana.resize(length-2);
            adaugareGenulPersoaneiInVector(numePersoana,genPersoana);
        };
    }
    adaugareRelatiePartener();
    inputFile.close();
}

void afisareListaPersoane(){
    ofstream outputFile;
    outputFile.open("output2.txt",ifstream::out);

    outputFile << "Lista persoane:" << endl;
    for(int i=0;i<listaPersoane.size();i++){
        outputFile << "Persoana  " << i+1 << " : " << endl;
        outputFile << "Nume    : " << listaPersoane[i]->nume <<endl;
        outputFile << "Genul   : " << listaPersoane[i]->genul << endl;
        if(listaPersoane[i]->parinte1 != 0){
            outputFile << "Parinte1: " << listaPersoane[i]->parinte1->nume <<endl;
        };
        if(listaPersoane[i]->parinte2 != 0){
            outputFile << "Parinte2: " << listaPersoane[i]->parinte2->nume <<endl;
        };
        if(listaPersoane[i]->partener != 0){
            outputFile << "Partener: " << listaPersoane[i]->partener->nume << endl;
        }

        if(listaPersoane[i]->nrCopii != 0){
            outputFile << "Nr. Copii : " << listaPersoane[i]->nrCopii << endl;

            for(int j=0;j<listaPersoane[i]->nrCopii;j++){
                if(listaPersoane[i]->copii[j]!=0){
                    outputFile << "Copil " << j+1 << " : " << listaPersoane[i]->copii[j]->nume << endl;
                }
            }

        };
        outputFile << endl;
    };
    outputFile.close();
}

bool gasireaUneiPersoane(string numePersoana){
    bool gasit = false;
    for(int i=0;i<listaPersoane.size();i++){
        if(listaPersoane[i]->nume == numePersoana){
            gasit = true;
        }
    }
    return gasit;
}

bool gasireaRamureiAnComun(persoanaStruct *ancestor, vector<string> &ramura, string numePersoana){
    if (ancestor == 0) return false;
    ramura.push_back(ancestor->nume);
    if (ancestor->nume == numePersoana) return true;
    if (ancestor->nrCopii != 0){
        for(int i=0; i < ancestor->nrCopii; i++){
            if (gasireaRamureiAnComun(ancestor->copii[i],ramura,numePersoana)){
                return true;
                break;
            }
        };
    }
    /*
    if (ancestor->partener != 0){
        cout << "Ancestor Partener" << endl;
        if(gasireaRamureiAnComun(ancestor->partener,ramura,numePersoana)){
            return true;
        }else return false;
    }
    */
    if(!ramura.empty()){
        ramura.pop_back();
    }
    return false;
}

string gasireaAncestruluiComun(string primaPersoana, string aDouaPersoana){
    vector<string> ramura1,ramura2;
    string ancestorComun;
    for(int i=0; i < listaPersoane.size(); i++){
        if((listaPersoane[i]->parinte1 == 0) && (listaPersoane[i]->parinte2 == 0)){
            if(!gasireaRamureiAnComun(listaPersoane[i], ramura1, primaPersoana) || !gasireaRamureiAnComun(listaPersoane[i], ramura2, aDouaPersoana)){
                //return "\0";
                ramura1.clear();
                ramura2.clear();
                continue;
            }
            int j;
            for(j = 0; j < ramura1.size() && j < ramura2.size(); j++ ){
                if(ramura1[j] != ramura2[j]) break;
            }
            ancestorComun = ramura1[j-1];
            for(int k=0; k < j-1; k++){
                if(ramura1[0] == ramura2[0]){
                ramura1.erase(ramura1.begin());
                ramura2.erase(ramura2.begin());
                }
            }
            cout << "Ramura 1: ";
            for(int i=0; i < ramura1.size(); i++){
                cout << ramura1[i] << ' ';
            }
            cout << endl;
            cout << "Ramura 2: ";
            for(int i=0; i < ramura2.size(); i++){
                cout << ramura2[i] << ' ';
            }
            cout << endl;
            return ancestorComun;
        }
    }
}


int main()
{
    //freopen("output2.txt","w",stdout);
    citireCreareArboreGenealogic();
    afisareListaPersoane();

    string primaPersoana, aDouaPersoana;
    cin >> primaPersoana;
    cin >> aDouaPersoana;
    cout << "Prima Persoana : " << primaPersoana << endl;
    cout << "A Doua Persoana: " << aDouaPersoana << endl;
    cout << "Este prima persoana?  " << gasireaUneiPersoane(primaPersoana) << endl;
    cout << "Este a doua persoana? " << gasireaUneiPersoane(aDouaPersoana) << endl;
    if(gasireaUneiPersoane(primaPersoana)&&gasireaUneiPersoane(aDouaPersoana)){
        cout << "Ancestrul Comun: " << gasireaAncestruluiComun(primaPersoana,aDouaPersoana) << endl;
    };
}
