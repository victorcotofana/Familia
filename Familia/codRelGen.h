#include <string.h>
#include <string>
#include <iostream>
#ifndef CODRELGEN_H_INCLUDED
#define CODRELGEN_H_INCLUDED
using namespace std;

struct persoanaStruct {
    string nume;
    char genul;
    persoanaStruct *parinte1 = 0;
    persoanaStruct *parinte2 = 0;
    persoanaStruct *partener = 0;
    unsigned int nrCopii = 0;
    persoanaStruct *copii[];
};


string relatiaGenealogica(string codRelatiaGenealogica, persoanaStruct* aDouaPersoana){
    string relatiaGenealogica = "Neidentificata" ;
    if( codRelatiaGenealogica.size() == 1){
        if ( codRelatiaGenealogica == "A" ){
            if( aDouaPersoana->genul == 'M') {
                relatiaGenealogica = "Tata";
            }else{
                relatiaGenealogica = "Mama";
            };
        }else
        if ( codRelatiaGenealogica == "B" ){
            if ( aDouaPersoana->genul == 'M'){
                relatiaGenealogica = "Fiu";
            }else{
                relatiaGenealogica = "Fiica";
            }
        }else
        if ( codRelatiaGenealogica == "C" ){
            if ( aDouaPersoana->genul == 'M'){
                relatiaGenealogica = "Sot";
            }else{
                relatiaGenealogica = "Sotie";
            }
        }else relatiaGenealogica = "Neidentificata";
    }

    if( codRelatiaGenealogica.size() == 2){
        if ( codRelatiaGenealogica == "AA" ){
            if (aDouaPersoana->genul == 'M'){
                relatiaGenealogica = "Bunic";
            }else{
                relatiaGenealogica = "Bunica";
            }
        }else
        if ( codRelatiaGenealogica == "AB" ){
            if (aDouaPersoana->genul == 'M'){
                relatiaGenealogica = "Frate";
            }else{
                relatiaGenealogica = "Sora";
            }
        }else
        if ( codRelatiaGenealogica == "BB" ){
            if (aDouaPersoana->genul == 'M'){
                relatiaGenealogica = "Nepot";
            }else{
                relatiaGenealogica = "Nepoata";
            }
        }else
        if ( codRelatiaGenealogica == "BC" ){
            if (aDouaPersoana->genul == 'M'){
                relatiaGenealogica = "Ginere";
            }else{
                relatiaGenealogica = "Nora";
            }
        }else
        if ( codRelatiaGenealogica == "CA" ){
            if (aDouaPersoana->genul == 'M'){
                relatiaGenealogica = "Socru";
            }else{
                relatiaGenealogica = "Soacra";
            }
        }else relatiaGenealogica = "Neidentificata";
    }

    if( codRelatiaGenealogica.size() == 3){
        if ( codRelatiaGenealogica == "AAA" ){
            if (aDouaPersoana->genul == 'M'){
                relatiaGenealogica = "Strabunic";
            }else{
                relatiaGenealogica = "Strabunica";
            }
        }else
        if ( codRelatiaGenealogica == "AAB" ){
            if (aDouaPersoana->genul == 'M'){
                relatiaGenealogica = "Unchi";
            }else{
                relatiaGenealogica = "Matusa";
            }
        }else
        if ( codRelatiaGenealogica == "ABB" ){
            if (aDouaPersoana->genul == 'M'){
                relatiaGenealogica = "Nepot(de pe frati)";
            }else{
                relatiaGenealogica = "Nepoata(de pe frati)";
            }
        }else
        if ( codRelatiaGenealogica == "CAB" ){
            if (aDouaPersoana->genul == 'M'){
                relatiaGenealogica = "Cumnat(de la partener)";
            }else{
                relatiaGenealogica = "Cumnata(de la partener)";
            }
        }else
        if ( codRelatiaGenealogica == "ABC" ){
            if (aDouaPersoana->genul == 'M'){
                relatiaGenealogica = "Cumnat(de la frati/surori)";
            }else{
                relatiaGenealogica = "Cumnata(de la frati/surori)";
            }
        }else
        if ( codRelatiaGenealogica == "BBB" ){
            if (aDouaPersoana->genul == 'M'){
                relatiaGenealogica = "Stranepot";
            }else{
                relatiaGenealogica = "Stranepoata";
            }
        }else
        relatiaGenealogica = "Neidentificata";
    };

    if( codRelatiaGenealogica.size() == 4){
        if ( codRelatiaGenealogica == "AAAA" ){
            if (aDouaPersoana->genul == 'M'){
                relatiaGenealogica = "Stra-strabunic";
            }else{
                relatiaGenealogica = "Stra-strabunica";
            }
        }else
        if ( codRelatiaGenealogica == "AABB" ){
            if (aDouaPersoana->genul == 'M'){
                relatiaGenealogica = "Var";
            }else{
                relatiaGenealogica = "Verisoara";
            }
        }else
        if ( codRelatiaGenealogica == "BBBB" ){
            if (aDouaPersoana->genul == 'M'){
                relatiaGenealogica = "Stra-stranepot";
            }else{
                relatiaGenealogica = "Stra-stranepot";
            }
        }else relatiaGenealogica = "Neidentificata";
    }
    //  Stra -stra -stra -stra bunic AA AA AA
    if( codRelatiaGenealogica.size() > 4){
        if( codRelatiaGenealogica.find("AAAA") == 0 ){
            string relatiaGenealogicaTemp = "Stra";
            int countLitera = 0;
            for(int i=0; i < codRelatiaGenealogica.size(); i++){
                if( codRelatiaGenealogica[i] == 'A' ){
                    countLitera++;
                }
            };
            for(int j=0; j < countLitera-3; j++){
                relatiaGenealogicaTemp+="-stra";
            };
            if( aDouaPersoana->genul == 'M'){
                relatiaGenealogicaTemp+="bunic";
            }else{
                relatiaGenealogicaTemp+="bunica";
            }
            if( countLitera == codRelatiaGenealogica.size() ){
                relatiaGenealogica = relatiaGenealogicaTemp;
            }
        }else
        if( codRelatiaGenealogica.find("BBBB") == 0 ){
            string relatiaGenealogicaTemp = "Stra";
            int countLitera = 0;
            for(int i=0; i < codRelatiaGenealogica.size(); i++){
                if( codRelatiaGenealogica[i] == 'B' ){
                    countLitera++;
                }
            };
            for(int j=0; j < countLitera-3; j++){
                relatiaGenealogicaTemp+="-stra";
            };
            if( aDouaPersoana->genul == 'M'){
                relatiaGenealogicaTemp+="nepot";
            }else{
                relatiaGenealogicaTemp+="nepoata";
            }
            if( countLitera == codRelatiaGenealogica.size() ){
                relatiaGenealogica = relatiaGenealogicaTemp;
            }
        }else relatiaGenealogica = "Neidentificata";
    }

    return relatiaGenealogica;
}


#endif
