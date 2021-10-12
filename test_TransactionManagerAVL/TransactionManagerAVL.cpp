/*--- Implementació de TransactionManagerAVL ---*/

/*/ COMENTARIS /*/
/*
 * He reutilitzat codi del TransactionManager original, com que AVLTree està implementada amb template, no ha calgut fer cap canvi.
 * Cost computacional al .h
 */

#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <string> 
using namespace std;

#include "TransactionManagerAVL.h"

TransactionManagerAVL::TransactionManagerAVL(float buyingFee, float sellingFee) {
    this->buyingFee = buyingFee;
    this->sellingFee = sellingFee;
}

TransactionManagerAVL::TransactionManagerAVL(string file_path, float buyingFee, float sellingFee) {
    this->buyingFee = buyingFee;
    this->sellingFee = sellingFee;
    loadFromFile(file_path);
}

TransactionManagerAVL::TransactionManagerAVL(const TransactionManagerAVL& orig) : AVLTree<string,Transaction>(orig){
    this->buyingFee = orig.buyingFee;
    this->sellingFee = orig.sellingFee;
}

TransactionManagerAVL::~TransactionManagerAVL() {
}

/* MÈTODES VOID */

void TransactionManagerAVL::loadFromFile(string file_path){ 
    ifstream fitxer(file_path);
    string _date, line;
    int _id;
    float _amount;
    vector<string> dadesTransaccio;
    
    fitxer.ignore(256, '\n'); // Ignorem la primera línia 'date_time,client_id,amount'
    
    while(getline(fitxer,line)){
        dadesTransaccio = {};
        int temp = 0, len = line.length()-1;
        // Iterem els caràcters de cada línia del fitxer, quan troba una coma crea un substring que desa la dada en dadesTransaccio.
        for(int i = 0; i<len; i++){
            if(line[i] == ','){
                dadesTransaccio.push_back(line.substr(temp, i-temp));
                temp=i+1;
            }
        }
        dadesTransaccio.push_back(line.substr(temp, len-temp)); // Aquest últim substring conté la dada '_amount'.
        // Assignem els valors continguts en dadesTransaccio a la variable que li correspon
        _date = dadesTransaccio[0];
        _id = stoi(dadesTransaccio[1]);
        _amount = stof(dadesTransaccio[2]);
        // Creem la transacció
        Transaction* t = new Transaction(_date,_id,_amount);
        // Afegim la data de la transacció a l'arbre, o si ja existeix la data, l'afegim al values del node corresponent.
        if(isEmpty()){
            add(_date,*t);
        }else if(!has(_date)){
            add(_date,*t);
        }else{
            find(_date)->addValue(*t);
        }
    }
    fitxer.close();
}

/*Imprimeix les transaccions. Cada línia impresa tindrà l'instant de
temps i la llista de transaccions realitzades en aquell instant
(separades per comes). Les dates s'imprimiran en ordre temporal.
Demanarà quantes dates imprimir, les imprimirà, i després
demanarà quantes més se'n volen imprimir. Es repetirà el procés
fins que l'usuari indiqui un número < 1*/
void TransactionManagerAVL::showAll() const{
    if(isEmpty()){
        throw invalid_argument("L'arbre està buit.");
    }  
    int nDates=0, temp=0, var; 
    cout<<"Nombre de dates a mostrar [0 per sortir]: ";cin>>nDates;
    while(nDates>0){
        temp += nDates;
        var = temp;
        showAllAux(this->p_root,var); // Imprimim tantes dates com ha indicat l'usuari, començant per la més recent.
        cout<<endl; // Fem un salt de línia.
        cout<<"Nombre de dates a mostrar [0 per sortir]: ";cin>>nDates;
    } 
}

/*Igual que showAll() però en ordre temporal invers*/
void TransactionManagerAVL::showAllReverse() const{
    if(isEmpty()){
        throw invalid_argument("L'arbre està buit.");
    }     
    int nDates=0, temp=0, var; 
    cout<<"Nombre de dates a mostrar [0 per sortir]: ";cin>>nDates;
    while(nDates>0){
        temp += nDates;
        var = temp;
        showAllReverseAux(this->p_root,var); // Imprimim tantes dates com ha indicat l'usuari, començant per la més antiga.
        cout<<endl; // Fem un salt de línia.
        cout<<"Nombre de dates a mostrar [0 per sortir]: ";cin>>nDates;
    }
}

/*Imprimeix únicament les transaccions de l'instant de temps més recent*/
void TransactionManagerAVL::showNewest() const{
    if(isEmpty()){
        throw invalid_argument("L'arbre està buit.");
    }         
    cout<<"Data: "<<p_root->getKey()<<" || Transaccions: ";
    imprimirTransaccions(p_root->getValues());
}

/*Imprimeix únicament les transaccions de l'instant de temps més antic*/
void TransactionManagerAVL::showOldest() const{
    if(isEmpty()){
        throw invalid_argument("L'arbre està buit.");
    }
    // Creem un node 'p' per fer el recorregut cap a la dreta des de p_root i trobar el major key, que es trobarà a la dreta del tot.
    BinaryTreeNode<string,Transaction>* p = p_root;
    // A temp guardarem el valor anterior de p, per a que quan p arribi al final i sigui nullptr, tinguem el màx key.
    BinaryTreeNode<string,Transaction>* temp; 
    while(p != nullptr){
        temp = p;
        p = p->getRight();
    }

    // Imprimim la informació de temp, l'instant de temps més antic.
    cout<<"Data: "<<temp->getKey()<<" || Transaccions: ";
    imprimirTransaccions(temp->getValues());
    
    // Esborrem els nodes auxiliars del heap.
    temp = nullptr; // Ho canvio a nullptr perquè no volem que es mostri a pantalla el missatge del destructor de Transaction.
    delete temp;
    delete p;
}

/* MÈTODES AUXILIARS PER IMPRIMIR TRANSACCIONS*/

/* Imprimeix totes les transaccions d'un vector de transactions */
void TransactionManagerAVL::imprimirTransaccions(vector<Transaction> transaccions) const{
    if(transaccions.size()>1){ // Si hi ha més d'una transacció imprimeix totes
        for(int i = 0; i<transaccions.size(); i++){
            transaccions[i].print();
            cout<<", "<<endl;
        }
    }else{
        // Si només hi ha una transacció imprimim el primer valor del vector.
        transaccions[0].print(); 
        cout<<""<<endl;
    }
}

void TransactionManagerAVL::showAllAux(const BinaryTreeNode<string,Transaction>* n, int& i) const{
    // Fem un recorregut inorder, aquesta vegada a més d'imprimir els keys imprimim les seves transaccions, values.
    // Inorder -> left, root, right 
    if(i>0){
        if (n->getLeft() != nullptr){
            showAllAux(n->getLeft(),i);   
        }
    }
    if(i>0){
        i--; // Restem una unitat al comptador de nombre de dates a imprimir.
        // Imprimim la data i les transaccions.
        cout<<"Data: "<<n->getKey()<<" || Transaccions: "; 
        imprimirTransaccions(n->getValues());
    }    
    if(i>0){   
        if (n->getRight() != nullptr){
            showAllAux(n->getRight(),i);  
        }
    }
    
}

void TransactionManagerAVL::showAllReverseAux(const BinaryTreeNode<string,Transaction>* n, int& i) const{
    // Fem un recorregut inorder pero que comença per la dreta i va a l'esquerra (de major a menor key), imprimint també les transaccions.
    // Inorder -> right, root, left  (!!! estem fent un inorder al l'inrevés !!!)
    if(i>0){
        if (n->getRight() != nullptr){
            showAllReverseAux(n->getRight(),i);
        }
    }
    if(i>0){ // Imprimim de la mateixa manera que a showAllAux.
        i--; 
        cout<<"Data: "<<n->getKey()<<" || Transaccions: ";
        imprimirTransaccions(n->getValues());
    }
    if(i>0){
        if (n->getLeft() != nullptr){
            showAllReverseAux(n->getLeft(),i);
        }
    }
}

/* MÈTODES FLOAT */

/* Calcula el benefici total */
float TransactionManagerAVL::feesInTotal() const{
    float total;
    // Cridem al auxiliar per fer un recorregut inorder des del root i anar calculant l'impost total.
    feesSinceTimeAux(p_root,total);
    return total;
}

/* Calcula el benefici des d'una data */
float TransactionManagerAVL::feesSinceTime(string date) const{
    if(!has(date)){
        throw invalid_argument("No hi ha cap transacció en aquest període de temps."); 
    }
    BinaryTreeNode<string,Transaction>* p = find(date);
    float total;
    // Cridem al auxiliar per fer recorregut inorder des de el node amb el key introduït per anar calculant l'impost total.
    feesSinceTimeAux(p,total);
    return total;
}

/* Calcula el benefici entre dues dates */
float TransactionManagerAVL::feesInTimeInterval(pair<string,string> interval) const{
    if(!has(interval.first) || !has(interval.second)){
        throw invalid_argument("No hi ha cap transacció en aquest període de temps."); 
    }
    float total1, total2, totalN2 = 0; // Variables on guardarem els totals
    BinaryTreeNode<string,Transaction>* n1 = find(interval.first); // Trobem el primer node
    BinaryTreeNode<string,Transaction>* n2 = find(interval.second); // Trobem el segon node
    
    // Calculem la suma total des de n1 fins al final per després fer la diferència amb la de n2. (total1)
    feesSinceTimeAux(n1,total1); 
    // Calculem la suma total des de n2 fins al final per després fer la diferència amb la de n2. (total2) 
    feesSinceTimeAux(n2,total2); 
    // Calculem la suma del node particular n2 per sumar-la a la total i que no se'ns elimini al fer la diferència.    
    sumaTransaccions(n2->getValues(),totalN2); 
    
    return abs(total1-total2+totalN2); // Retornem la diferència.
}

/* MÈTODES AUXILIARS PER CALCULAR BENEFICIS */

/* Fa la suma dels impostos d'un vector amb transaccions */
void TransactionManagerAVL::sumaTransaccions(vector<Transaction> transaccions, float& suma) const{
    float amount = 0;
    // Si tenim més d'una transacció, calcula l'impost i l'afegeix a la suma total de cada una.
    if(transaccions.size()>1){ 
        for(int i = 0; i<transaccions.size(); i++){
            amount = transaccions[i].getQuantitat();
            suma += amount<0 ? abs(amount)*buyingFee : amount*sellingFee;
        }
    }else{
        // Si només té una transacció, suma al total l'impost d'aquesta única transacció.
        amount = transaccions[0].getQuantitat();
        suma += amount<0 ? abs(amount)*buyingFee : amount*sellingFee;
    }
}

/* Fa un recorregut inorder des d'un node per anar sumant transaccions i trobar un total */
void TransactionManagerAVL::feesSinceTimeAux(const BinaryTreeNode<string,Transaction>* n, float& suma) const{ 
    // Fem un recorregut inorder des del node rebut per paràmetre sumant les transaccions per trobar l'impost total.
    if (n->getLeft() != nullptr){
        feesSinceTimeAux(n->getLeft(),suma); // Sumem a l'esquerra del node.
    }  
    
    // Sumem les transaccions (la suma total es va guardant a 'suma', un alias que retornem al mètode principal).
    sumaTransaccions(n->getValues(),suma); 
    
    if (n->getRight() != nullptr){
        feesSinceTimeAux(n->getRight(),suma); // Sumem a la dreta del node.
    }
}

/* MÈTODE PER CALCULAR EL BALANÇ */

/* Calcula la suma de les transaccions de les dates d'un fitxer trobades a la llista de transaccions */
float TransactionManagerAVL::calculaBalanc(string nomFitxer){
    ifstream fitxer(nomFitxer);
    string line;
    float balanc = 0;
    while(getline(fitxer,line)){ 
        if(has(line)){ // Si la data existeix a l'arbre, suma les transaccions del node a balanç.
            float suma = 0;
            sumaTransaccions(find(line)->getValues(),suma);
            balanc += suma;
        }
    }
    fitxer.close();
    return balanc;
}