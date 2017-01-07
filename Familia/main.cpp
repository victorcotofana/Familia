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

string relatiaGenealogica(vector<persoanaStruct*> ramuraCompleta);

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

bool gasireaRamureiAnComun(persoanaStruct *ancestor, vector<persoanaStruct*> &ramura, string numePersoana){
    if (ancestor == 0) return false;
    ramura.push_back(ancestor);
    if (ancestor->nume == numePersoana) return true;
    if (ancestor->nrCopii != 0){
        for(int i=0; i < ancestor->nrCopii; i++){
            if (gasireaRamureiAnComun(ancestor->copii[i],ramura,numePersoana)){
                return true;
                break;
            }
        };
    }
    ramura.pop_back();
    return false;
}

string gasireaAncestruluiComunRude(string primaPersoana, string aDouaPersoana){
    vector<persoanaStruct*> ramura1, ramura2, ramuriConcatinate;
    string ancestorComun;
    for(int i=0; i < listaPersoane.size(); i++){
        if((listaPersoane[i]->parinte1 == 0) && (listaPersoane[i]->parinte2 == 0)){
            if(!gasireaRamureiAnComun(listaPersoane[i], ramura1, primaPersoana) || !gasireaRamureiAnComun(listaPersoane[i], ramura2, aDouaPersoana)){
                ramura1.clear();
                ramura2.clear();
                continue;
            }
            int j;
            for(j = 0; j < ramura1.size() && j < ramura2.size(); j++ ){
                if(ramura1[j] != ramura2[j]) break;
            }
            ancestorComun = ramura1[j-1]->nume;

            for(int k=0; k < j-1; k++){
                if(ramura1[0]->nume == ramura2[0]->nume){
                ramura1.erase(ramura1.begin());
                ramura2.erase(ramura2.begin());
                }
            }
            cout << "Ramura 1: ";
            for(int i=0; i < ramura1.size(); i++){
                cout << ramura1[i]->nume << ' ';
            }
            cout << endl;
            cout << "Ramura 2: ";
            for(int i=0; i < ramura2.size(); i++){
                cout << ramura2[i]->nume << ' ';
            }
            cout << endl;

            for(int i=ramura1.size()-1; i >= 0; i--){
                ramuriConcatinate.push_back(ramura1[i]);
            }
            for(int i=1; i < ramura2.size(); i++){
                ramuriConcatinate.push_back(ramura2[i]);
            }
            cout << "Ramura Completa: ";
            for(int i=0; i < ramuriConcatinate.size();i++){
                cout << ramuriConcatinate[i]->nume << ' ';
            }
            cout << endl;
            cout << "THE CODE : " << relatiaGenealogica(ramuriConcatinate) << endl;
            return ancestorComun;
        }
    }
}

bool gasireaRamureiAnComunAfini(persoanaStruct *rudaAfinaComuna,bool vineAfin, string numeExclusPartener , string numeExclusCopil, vector<persoanaStruct*> &ramura, string numePersoana){
    if (rudaAfinaComuna == 0) return false;
    ramura.push_back(rudaAfinaComuna);
    if (rudaAfinaComuna->nume == numePersoana) return true;

    if ((rudaAfinaComuna->partener != 0)&&(rudaAfinaComuna->partener->nume != numeExclusPartener)){
        if (gasireaRamureiAnComunAfini(rudaAfinaComuna->partener, 1, rudaAfinaComuna->nume, "", ramura, numePersoana)){
            return true;
        }
    }

    if(vineAfin == 1){
        if((rudaAfinaComuna->parinte1 != 0 )&&(rudaAfinaComuna->parinte2 != 0)){
            if (gasireaRamureiAnComunAfini(rudaAfinaComuna->parinte1, 1, rudaAfinaComuna->parinte2->nume, rudaAfinaComuna->nume, ramura ,numePersoana)){
                return true;
            }
            if (gasireaRamureiAnComunAfini(rudaAfinaComuna->parinte2, 1, rudaAfinaComuna->parinte1->nume, rudaAfinaComuna->nume, ramura ,numePersoana)){
                return true;
            }
        }
        if((rudaAfinaComuna->partener->parinte1 != 0 )&&(rudaAfinaComuna->partener->parinte2 == 0)){
            if(gasireaRamureiAnComunAfini(rudaAfinaComuna->parinte1, 1, "", rudaAfinaComuna->nume, ramura, numePersoana)){
                return true;
            }
        }
        if((rudaAfinaComuna->parinte1 == 0 )&&(rudaAfinaComuna->parinte2 != 0)){
            if(gasireaRamureiAnComunAfini(rudaAfinaComuna->parinte2, 1, rudaAfinaComuna->parinte1->nume, rudaAfinaComuna->nume, ramura, numePersoana)){
                return true;
            }
        }
    }

    if (rudaAfinaComuna->nrCopii != 0){
        for(int i=0; i < rudaAfinaComuna->nrCopii; i++){
            if (rudaAfinaComuna->copii[i]->nume != numeExclusCopil){
                if (gasireaRamureiAnComunAfini(rudaAfinaComuna->copii[i], 0, "", "", ramura, numePersoana)){
                    return true;
                    break;
                }
            }
        };
    }

    ramura.pop_back();
    return false;
}

string gasireaAncestruluiComunRudeAfine(string primaPersoana, string aDouaPersoana){
    vector<persoanaStruct*> ramura1,ramura2,ramuriConcatinate;
    string ancestorComun ;
    for(int i=0; i < listaPersoane.size(); i++){
        if((listaPersoane[i]->parinte1 == 0) && (listaPersoane[i]->parinte2 == 0)){
            if(!gasireaRamureiAnComunAfini(listaPersoane[i],0,"","", ramura1, primaPersoana) || !gasireaRamureiAnComunAfini(listaPersoane[i],0,"","", ramura2, aDouaPersoana)){
                ramura1.clear();
                ramura2.clear();
                continue;
            }
        };
        int j;
        for(j = 0; j < ramura1.size() && j < ramura2.size(); j++ ){
            if(ramura1[j] != ramura2[j]) break;
        }
        ancestorComun = ramura1[j-1]->nume;
        for(int k=0; k < j-1; k++){
            if(ramura1[0] == ramura2[0]){
            ramura1.erase(ramura1.begin());
            ramura2.erase(ramura2.begin());
            }
        }
        cout << "Ramura 1: ";
        for(int i=0; i < ramura1.size(); i++){
            cout << ramura1[i]->nume << ' ';
        }
        cout << endl;
        cout << "Ramura 2: ";
        for(int i=0; i < ramura2.size(); i++){
            cout << ramura2[i]->nume << ' ';
        }
        cout << endl;
        for(int i=ramura1.size()-1; i >= 0; i--){
            ramuriConcatinate.push_back(ramura1[i]);
        }
        for(int i=1; i < ramura2.size(); i++){
            ramuriConcatinate.push_back(ramura2[i]);
        }
        cout << "Ramura Completa: ";
        for(int i=0; i < ramuriConcatinate.size();i++){
            cout << ramuriConcatinate[i]->nume << ' ';
        }
        cout << endl;

        cout << "THE CODE : " << relatiaGenealogica(ramuriConcatinate) << endl;
        return ancestorComun;
    }
}

string relatiaGenealogica(vector<persoanaStruct*> ramuraCompleta){
    string relatiaGenealogica;
    for(int i=0; i < ramuraCompleta.size()-1 ; i++){
        if (ramuraCompleta[i]->parinte1 == ramuraCompleta[i+1] ){
            relatiaGenealogica += 'A';
        }
        if (ramuraCompleta[i]->parinte2 == ramuraCompleta[i+1]){
            relatiaGenealogica += 'A';
        }
        if (ramuraCompleta[i]->nrCopii != 0){
            for(int j=0; j < ramuraCompleta[i]->nrCopii; j++ ){
                if(ramuraCompleta[i]->copii[j]->nume == ramuraCompleta[i+1]->nume){
                    relatiaGenealogica += 'B';
                    break;
                }
            }
        }
        if (ramuraCompleta[i]->partener == ramuraCompleta[i+1]){
            relatiaGenealogica += 'C';
        }
    };
    return relatiaGenealogica;
}

int main()
{
    //freopen("output2.txt","w",stdout);
    citireCreareArboreGenealogic();
    afisareListaPersoane();

    bool estePrimaPersoana = false , esteADouaPersoana = false;
    string primaPersoana, aDouaPersoana;
    cout << "Prima persoana : " ;
    cin >> primaPersoana;
    cout << "A doua persoana: " ;
    cin >> aDouaPersoana;
    estePrimaPersoana = gasireaUneiPersoane(primaPersoana);
    esteADouaPersoana = gasireaUneiPersoane(aDouaPersoana);
    if(estePrimaPersoana && esteADouaPersoana){
        string ancestrulComun = gasireaAncestruluiComunRude(primaPersoana,aDouaPersoana);
        if( ancestrulComun != "\0"){
            cout << primaPersoana << " si " << aDouaPersoana << " sunt Rude de singe." << endl;
            cout << "Ancestrul Comun: " << ancestrulComun << endl;
        }else{
            string ancestrulComunAfin = gasireaAncestruluiComunRudeAfine(primaPersoana,aDouaPersoana);
            cout << primaPersoana << " si " << aDouaPersoana << " sunt Rude prin alianta." << endl;
            cout << "Ruda Comuna : " << ancestrulComunAfin << endl;
        }
    }else{
        if (estePrimaPersoana == 0){
            cout << primaPersoana << " nu este in arborele genealogic introdus." << endl;
        }
        if (esteADouaPersoana ==0){
            cout << aDouaPersoana << " nu este in arborele genealogic introdus." << endl;
        }
    }

}
