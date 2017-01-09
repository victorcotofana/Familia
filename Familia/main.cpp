#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <fstream>
#include <vector>
#include "codRelGen.h"
using namespace std;

struct relatieDouaPers{
    string primaPersoana;
    string aDouaPersoana;
    string tipLegatura;
    vector<persoanaStruct*> ramuraCompleta;
    string ancestorComun;
    string codRelatie;
    string relatia;
    string gradulDeRudenie;
} ;

vector<persoanaStruct*> listaPersoane;

string codRelatiaGenealogica(vector<persoanaStruct*> ramuraCompleta);

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
    for(int i=0; i < listaPersoane.size(); i++){
        if(listaPersoane[i]->nume == copil){
            pozitiaCopil = i;
        }
    }
    for(int i=0; i < listaPersoane.size() ;i++){
        if(listaPersoane[i]->nume == parinte){
            if(listaPersoane[pozitiaCopil]->parinte1 == 0){
                listaPersoane[pozitiaCopil]->parinte1 = listaPersoane[i];
            }else{
                listaPersoane[pozitiaCopil]->parinte2 = listaPersoane[i];
            };
            listaPersoane[i]->copii.push_back(listaPersoane[pozitiaCopil]);
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
            numePersoana = numeGenPersoana;
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

        if(listaPersoane[i]->copii.size() != 0){
            outputFile << "Nr. Copii : " << listaPersoane[i]->copii.size() << endl;

            for(int j=0;j<listaPersoane[i]->copii.size(); j++){
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
    if (ancestor->copii.size() != 0){
        for(int i=0; i < ancestor->copii.size(); i++){
            if (gasireaRamureiAnComun(ancestor->copii[i],ramura,numePersoana)){
                return true;
                break;
            }
        };
    }
    ramura.pop_back();
    return false;
}

relatieDouaPers gasireaAncestruluiComunRude(string primaPersoana, string aDouaPersoana){
    relatieDouaPers relatieDouaRude;
    vector<persoanaStruct*> ramura1, ramura2, ramuriConcatinate;
    relatieDouaRude.primaPersoana = primaPersoana;
    relatieDouaRude.aDouaPersoana = aDouaPersoana;
    relatieDouaRude.tipLegatura = "Rude de singe";
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
            relatieDouaRude.ancestorComun = ramura1[j-1]->nume;

            for(int k=0; k < j-1; k++){
                if(ramura1[0]->nume == ramura2[0]->nume){
                ramura1.erase(ramura1.begin());
                ramura2.erase(ramura2.begin());
                }
            }
            /*
            cout << "Ramura " << primaPersoana << " -> " << relatieDouaRude.ancestorComun << " : " ;
            for(int i=0; i < ramura1.size(); i++){
                cout << ramura1[i]->nume << ' ';
            }
            cout << endl;
            cout << "Ramura " << aDouaPersoana << " -> " << relatieDouaRude.ancestorComun << " : ";
            for(int i=0; i < ramura2.size(); i++){
                cout << ramura2[i]->nume << ' ';
            }
            cout << endl;
            */
            for(int i=ramura1.size()-1; i >= 0; i--){
                ramuriConcatinate.push_back(ramura1[i]);
            }
            for(int i=1; i < ramura2.size(); i++){
                ramuriConcatinate.push_back(ramura2[i]);
            }
            relatieDouaRude.ramuraCompleta = ramuriConcatinate;

            string codulRelatieiGenealogice = codRelatiaGenealogica(ramuriConcatinate);
            relatieDouaRude.codRelatie = codulRelatieiGenealogice;

            persoanaStruct* aDouaPersoanaPointer;
            for(int i=0; i < listaPersoane.size(); i++){
                if(listaPersoane[i]->nume == aDouaPersoana){
                    aDouaPersoanaPointer = listaPersoane[i];
                }
            };

            relatiaSiGradul relatiaGen = relatiaGenealogica(codulRelatieiGenealogice, aDouaPersoanaPointer);
            relatieDouaRude.relatia = relatiaGen.relatiaGenealogica;
            relatieDouaRude.gradulDeRudenie = relatiaGen.gradDeRudenie;

            return relatieDouaRude;
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

    if (rudaAfinaComuna->copii.size() != 0){
        for(int i=0; i < rudaAfinaComuna->copii.size(); i++){
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

relatieDouaPers gasireaAncestruluiComunRudeAfine(string primaPersoana, string aDouaPersoana){
    relatieDouaPers relatieDouaAfine;
    vector<persoanaStruct*> ramura1,ramura2,ramuriConcatinate;
    relatieDouaAfine.primaPersoana = primaPersoana;
    relatieDouaAfine.aDouaPersoana = aDouaPersoana;
    relatieDouaAfine.tipLegatura = "Rude afine";
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

        relatieDouaAfine.ancestorComun = ramura1[j-1]->nume;

        for(int k=0; k < j-1; k++){
            if(ramura1[0] == ramura2[0]){
            ramura1.erase(ramura1.begin());
            ramura2.erase(ramura2.begin());
            }
        }
        /*
        cout << "Ramura " << primaPersoana << " -> " << relatieDouaAfine.ancestorComun << " : ";
        for(int i=0; i < ramura1.size(); i++){
            cout << ramura1[i]->nume << ' ';
        }
        cout << endl;
        cout << "Ramura " << aDouaPersoana << " -> " << relatieDouaAfine.ancestorComun << " : ";
        for(int i=0; i < ramura2.size(); i++){
            cout << ramura2[i]->nume << ' ';
        }
        cout << endl;
        */
        for(int i=ramura1.size()-1; i >= 0; i--){
            ramuriConcatinate.push_back(ramura1[i]);
        }
        for(int i=1; i < ramura2.size(); i++){
            ramuriConcatinate.push_back(ramura2[i]);
        }
        //&&( ramuriConcatinate[i-1]->partener == ramuriConcatinate[i])
        for(int i=1; i < ramuriConcatinate.size()-1; i++){
                ramuriConcatinate.erase(ramuriConcatinate.begin()+i);
            }
        }


        relatieDouaAfine.ramuraCompleta = ramuriConcatinate;

        string codulRelatieiGenealogice = codRelatiaGenealogica(ramuriConcatinate);
        relatieDouaAfine.codRelatie = codulRelatieiGenealogice;

        persoanaStruct* aDouaPersoanaPointer;
        for(int i=0; i < listaPersoane.size(); i++){
            if(listaPersoane[i]->nume == aDouaPersoana){
                aDouaPersoanaPointer = listaPersoane[i];
            }
        }

        relatiaSiGradul relatiaGen = relatiaGenealogica(codulRelatieiGenealogice, aDouaPersoanaPointer);
        relatieDouaAfine.relatia = relatiaGen.relatiaGenealogica;
        relatieDouaAfine.gradulDeRudenie = relatiaGen.gradDeRudenie;

        return relatieDouaAfine;
    }
}

string codRelatiaGenealogica(vector<persoanaStruct*> ramuraCompleta){
    string relatiaGenealogica;
    for(int i=0; i < ramuraCompleta.size()-1 ; i++){
        if (ramuraCompleta[i]->parinte1 == ramuraCompleta[i+1] ){
            relatiaGenealogica += 'A';
        }
        if (ramuraCompleta[i]->parinte2 == ramuraCompleta[i+1]){
            relatiaGenealogica += 'A';
        }
        if (ramuraCompleta[i]->copii.size() != 0){
            for(int j=0; j < ramuraCompleta[i]->copii.size(); j++ ){
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
        relatieDouaPers relatiaDintrePersoane = gasireaAncestruluiComunRude(primaPersoana,aDouaPersoana);
        if( relatiaDintrePersoane.ancestorComun!= "\0"){
            cout << "Forma de Rudenie : " << relatiaDintrePersoane.tipLegatura << endl;
            cout << "Stramosul Comun  : " << relatiaDintrePersoane.ancestorComun << endl;
            cout << "Ramura Completa  : ";
            for(int i=0; i < relatiaDintrePersoane.ramuraCompleta.size(); i++){
                cout << relatiaDintrePersoane.ramuraCompleta[i]->nume << ' ';
            }
            cout << endl;
            cout << "Codul Relatiei   : " << relatiaDintrePersoane.codRelatie << endl;
            cout << "Gradul de rudenie: " << relatiaDintrePersoane.gradulDeRudenie << endl;
            cout << "Relatie          : " << relatiaDintrePersoane.relatia << endl;
        }else{
            relatieDouaPers relatieAfina = gasireaAncestruluiComunRudeAfine(primaPersoana,aDouaPersoana);
            cout << "Forma de Rudenie : " << relatieAfina.tipLegatura << endl;
            cout << "Ruda Comuna      : " << relatieAfina.ancestorComun << endl;
            cout << "Ramura Completa  : ";
            for(int i=0; i < relatieAfina.ramuraCompleta.size(); i++){
                cout << relatieAfina.ramuraCompleta[i]->nume << ' ';
            }
            cout << endl;
            cout << "Codul Relatiei   : " << relatieAfina.codRelatie << endl;
            cout << "Gradul de rudenie: " << relatieAfina.gradulDeRudenie << endl;
            cout << "Relatie          : " << relatieAfina.relatia << endl;
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
