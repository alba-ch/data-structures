/* Classe principal */

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

#include "TransactionManagerAVL.h"

int opcio(vector<string> options){
    int option=0;
    cout<<"\nMENÚ"<<endl;
    for(int i=0;i<options.size();i++){
        cout<<i+1<<". "<<options[i]<<endl;
    }
    cin>>option;
    // Comprova que la opció és correcta
    if(option<1 || option>options.size()){
        option = opcio(options); // Si no ho és, torna a mostrar el menú i a comprovar l'opcio introduida.
    }
    return option;
}

int main(int argc, char** argv) {
    int option = 0, n=0;
    string nomFitxer, nomQueries, data, data1="", data2="";
    TransactionManagerAVL manager;
    vector<string> options{"Carregar fitxer de transaccions", "Mostrar transaccions", "Mostrar transaccions en ordre invers",
            "Mostrar transaccions del primer instant de temps","Mostrar transaccions del darrer instant de temps","Mostrar comissió total recaptada","Mostrar comissió a partir d'una data",
            "Mostrar comissió entre dues dates","Mostrar balanç de les transaccions","Sortir"};

    do{
        option = opcio(options);
        switch(option){
            case 1: cout<<"Ruta al fitxer: "; cin>>nomFitxer;
                    try{
                        chrono::steady_clock::time_point begin = chrono::steady_clock::now();
                        manager.loadFromFile(nomFitxer);
                        chrono::steady_clock::time_point end = chrono::steady_clock::now();
                        cout << "Temps transcorregut: " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << " ms." << endl;  
                    }catch(const invalid_argument& e){
                        cout<<e.what()<<"\n"<<endl;
                    }; break;
            case 2: cout<<"\n--- Transaccions en ordre temporal ---\n"<<endl;
                    try{
                        manager.showAll();
                    }catch(const invalid_argument& e){
                        cout<<e.what()<<"\n"<<endl;
                    }; break;
            case 3: cout<<"\n--- Transaccions en ordre temporal invers ---\n"<<endl;
                    try{
                        manager.showAllReverse();
                    }catch(const invalid_argument& e){
                        cout<<e.what()<<"\n"<<endl;
                    }; break;
            case 4: cout<<"\n--- Transaccions del primer instant de temps ---\n"<<endl;
                    try{
                        manager.showNewest();
                    }catch(const invalid_argument& e){
                        cout<<e.what()<<"\n"<<endl;
                    }; break;
            case 5: cout<<"\n--- Transaccions del darrer instant de temps ---\n"<<endl;
                    try{
                        manager.showOldest();
                    }catch(const invalid_argument& e){
                        cout<<e.what()<<"\n"<<endl;
                    }; break;
            case 6: cout<<"\nComissió recaptada total: ";
                    try{
                        cout<<manager.feesInTotal()<<" €"<<endl;
                    }catch(const invalid_argument& e){
                        cout<<e.what()<<"\n"<<endl;
                    }; break;
            case 7: cout<<"\n--- Comissió recaptada a partir d'una data ---\n"<<endl;
                    cout<<"Data de la transacció: ";cin.ignore();getline(cin,data);
                    try{
                        cout<<"La comissió recaptada des de la data "<<data<<" és: "<<manager.feesSinceTime(data)<<" €"<<endl;
                    }catch(const invalid_argument& e){
                        cout<<"\n"<<e.what()<<"\n"<<endl;
                    }; break;                   
            case 8: cout<<"\n--- Comissió recaptada entre dues dates ---\n"<<endl; 
                    cout<<"Data de la primera transacció: ";cin.ignore();getline(cin,data1);
                    cout<<"Data de la segona transacció: ";getline(cin,data2);
                    try{
                        cout<<"La comissió recaptada des de "<<data1<<" fins "<<data2<<" és: ";
                        cout<<manager.feesInTimeInterval(pair<string,string>(data1,data2))<<" €"<<endl;
                    }catch(const invalid_argument& e){
                        cout<<"\n"<<e.what()<<"\n"<<endl;
                    }; break;  
            case 9: cout<<"\n--- Balanç de les transaccions ---\n"<<endl;
                    cout<<"Ruta al fitxer: "; cin>>nomQueries;
                    try{
                        cout<<"\nBalanç total sobre queries: "<<manager.calculaBalanc(nomQueries)<<" €"<<endl;
                    }catch(const invalid_argument& e){
                        cout<<e.what()<<"\n"<<endl;
                    }; break;
        }
    }while(option!=10);
     
    return 0;
}

