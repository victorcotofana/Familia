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
    vector<persoanaStruct*> copii;
};

struct relatiaSiGradul{
    string relatiaGenealogica;
    string gradDeRudenie;
};

string toString(int a) {
    string res = "";
    if (a == 0) res = "0";
    while (a>0) {
        res = (char)(a % 10 + '0') + res;
        a/=10;
    }
    return res;
}

relatiaSiGradul relatiaGenealogica(string codRelatiaGenealogica, persoanaStruct* aDouaPersoana){
    relatiaSiGradul relatiaSiGradul;
    relatiaSiGradul.relatiaGenealogica = "Neidentificat";
    relatiaSiGradul.gradDeRudenie = "Neidentificat";
    if( codRelatiaGenealogica.size() == 1){
        if ( codRelatiaGenealogica == "A" ){
            if( aDouaPersoana->genul == 'M') {
                relatiaSiGradul.relatiaGenealogica = "Tata";
                relatiaSiGradul.gradDeRudenie = "Gr.I";
            }else{
                relatiaSiGradul.relatiaGenealogica = "Mama";
                relatiaSiGradul.gradDeRudenie = "Gr.I";
            };
        }else
        if ( codRelatiaGenealogica == "B" ){
            if ( aDouaPersoana->genul == 'M'){
                relatiaSiGradul.relatiaGenealogica = "Fiu";
                relatiaSiGradul.gradDeRudenie = "Gr.I";
            }else{
                relatiaSiGradul.relatiaGenealogica = "Fiica";
                relatiaSiGradul.gradDeRudenie = "Gr.I";
            }
        }else
        if ( codRelatiaGenealogica == "C" ){
            if ( aDouaPersoana->genul == 'M'){
                relatiaSiGradul.relatiaGenealogica = "Sot";
                relatiaSiGradul.gradDeRudenie = "Gr.I";
            }else{
                relatiaSiGradul.relatiaGenealogica = "Sotie";
                relatiaSiGradul.gradDeRudenie = "Gr.I";
            }
        }
    }

    if( codRelatiaGenealogica.size() == 2){
        if ( codRelatiaGenealogica == "AA" ){
            if (aDouaPersoana->genul == 'M'){
                relatiaSiGradul.relatiaGenealogica = "Bunic";
                relatiaSiGradul.gradDeRudenie = "Gr.II";
            }else{
                relatiaSiGradul.relatiaGenealogica = "Bunica";
                relatiaSiGradul.gradDeRudenie = "Gr.II";
            }
        }else
        if ( codRelatiaGenealogica == "AB" ){
            if (aDouaPersoana->genul == 'M'){
                relatiaSiGradul.relatiaGenealogica = "Frate";
                relatiaSiGradul.gradDeRudenie = "Gr.II";
            }else{
                relatiaSiGradul.relatiaGenealogica = "Sora";
                relatiaSiGradul.gradDeRudenie = "Gr.II";
            }
        }else
        if ( codRelatiaGenealogica == "BB" ){
            if (aDouaPersoana->genul == 'M'){
                relatiaSiGradul.relatiaGenealogica = "Nepot";
                relatiaSiGradul.gradDeRudenie = "Gr.II";
            }else{
                relatiaSiGradul.relatiaGenealogica = "Nepoata";
                relatiaSiGradul.gradDeRudenie = "Gr.II";
            }
        }else
        if ( codRelatiaGenealogica == "BC" ){
            if (aDouaPersoana->genul == 'M'){
                relatiaSiGradul.relatiaGenealogica = "Ginere";
                relatiaSiGradul.gradDeRudenie = "Gr.I";
            }else{
                relatiaSiGradul.relatiaGenealogica = "Nora";
                relatiaSiGradul.gradDeRudenie = "Gr.I";
            }
        }else
        if ( codRelatiaGenealogica == "CA" ){
            if (aDouaPersoana->genul == 'M'){
                relatiaSiGradul.relatiaGenealogica = "Socru";
                relatiaSiGradul.gradDeRudenie = "Gr.I";
            }else{
                relatiaSiGradul.relatiaGenealogica = "Soacra";
                relatiaSiGradul.gradDeRudenie = "Gr.I";
            }
        }
    }

    if( codRelatiaGenealogica.size() == 3){
        if ( codRelatiaGenealogica == "AAA" ){
            if (aDouaPersoana->genul == 'M'){
                relatiaSiGradul.relatiaGenealogica = "Strabunic";
                relatiaSiGradul.gradDeRudenie = "Gr.III";
            }else{
                relatiaSiGradul.relatiaGenealogica = "Strabunica";
                relatiaSiGradul.gradDeRudenie = "Gr.III";
            }
        }else
        if ( codRelatiaGenealogica == "AAB" ){
            if (aDouaPersoana->genul == 'M'){
                relatiaSiGradul.relatiaGenealogica = "Unchi";
                relatiaSiGradul.gradDeRudenie = "Gr.III";
            }else{
                relatiaSiGradul.relatiaGenealogica = "Matusa";
                relatiaSiGradul.gradDeRudenie = "Gr.III";
            }
        }else
        if ( codRelatiaGenealogica == "ABB" ){
            if (aDouaPersoana->genul == 'M'){
                relatiaSiGradul.relatiaGenealogica = "Nepot (de pe frati)";
                relatiaSiGradul.gradDeRudenie = "Gr.III";
            }else{
                relatiaSiGradul.relatiaGenealogica = "Nepoata (de pe frati)";
                relatiaSiGradul.gradDeRudenie = "Gr.III";
            }
        }else
        if ( codRelatiaGenealogica == "CAB" ){
            if (aDouaPersoana->genul == 'M'){
                relatiaSiGradul.relatiaGenealogica = "Cumnat (de la partener)";
                relatiaSiGradul.gradDeRudenie = "Gr.II";
            }else{
                relatiaSiGradul.relatiaGenealogica = "Cumnata (de la partener)";
                relatiaSiGradul.gradDeRudenie = "Gr.II";
            }
        }else
        if ( codRelatiaGenealogica == "ABC" ){
            if (aDouaPersoana->genul == 'M'){
                relatiaSiGradul.relatiaGenealogica = "Cumnat (de la frati/surori)";
                relatiaSiGradul.gradDeRudenie = "Gr.II";
            }else{
                relatiaSiGradul.relatiaGenealogica = "Cumnata (de la frati/surori)";
                relatiaSiGradul.gradDeRudenie = "Gr.II";
            }
        }else
        if ( codRelatiaGenealogica == "BBB" ){
            if (aDouaPersoana->genul == 'M'){
                relatiaSiGradul.relatiaGenealogica = "Stranepot";
                relatiaSiGradul.gradDeRudenie = "Gr.III";
            }else{
                relatiaSiGradul.relatiaGenealogica = "Stranepoata";
                relatiaSiGradul.gradDeRudenie = "Gr.III";
            }
        }else
        if ( codRelatiaGenealogica == "CBC" ){
            if (aDouaPersoana->genul == 'M'){
                relatiaSiGradul.relatiaGenealogica = "Ginere";
                relatiaSiGradul.gradDeRudenie = "Gr.I";
            }else{
                relatiaSiGradul.relatiaGenealogica = "Nora";
                relatiaSiGradul.gradDeRudenie = "Gr.I";
            }
        }else
        if ( codRelatiaGenealogica == "CAC" ){
            if (aDouaPersoana->genul == 'M'){
                relatiaSiGradul.relatiaGenealogica = "Socru";
                relatiaSiGradul.gradDeRudenie = "Gr.I";
            }else{
                relatiaSiGradul.relatiaGenealogica = "Soacra";
                relatiaSiGradul.gradDeRudenie = "Gr.I";
            }
        }
    };

    if( codRelatiaGenealogica.size() == 4){
        if ( codRelatiaGenealogica == "AAAA" ){
            if (aDouaPersoana->genul == 'M'){
                relatiaSiGradul.relatiaGenealogica = "Stra-strabunic";
                relatiaSiGradul.gradDeRudenie = "Gr.IV";
            }else{
                relatiaSiGradul.relatiaGenealogica = "Stra-strabunica";
                relatiaSiGradul.gradDeRudenie = "Gr.IV";
            }
        }else
        if ( codRelatiaGenealogica == "AABB" ){
            if (aDouaPersoana->genul == 'M'){
                relatiaSiGradul.relatiaGenealogica = "Verisor";
                relatiaSiGradul.gradDeRudenie = "Gr.IV";
            }else{
                relatiaSiGradul.relatiaGenealogica = "Verisoara";
                relatiaSiGradul.gradDeRudenie = "Gr.IV";
            }
        }else
        if ( codRelatiaGenealogica == "BBBB" ){
            if (aDouaPersoana->genul == 'M'){
                relatiaSiGradul.relatiaGenealogica = "Stra-stranepot";
                relatiaSiGradul.gradDeRudenie = "Gr.IV";
            }else{
                relatiaSiGradul.relatiaGenealogica = "Stra-stranepot";
                relatiaSiGradul.gradDeRudenie = "Gr.IV";
            }
        }
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
                relatiaSiGradul.relatiaGenealogica = relatiaGenealogicaTemp;
                relatiaSiGradul.gradDeRudenie = "Gr." + toString(countLitera);
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
                relatiaSiGradul.relatiaGenealogica = relatiaGenealogicaTemp;
                relatiaSiGradul.gradDeRudenie = "Gr." + toString(countLitera);
            }
        }
    }

    return relatiaSiGradul;
}


#endif
