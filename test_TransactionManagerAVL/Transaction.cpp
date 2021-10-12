/*--- Implementació de Transaction ---*/

/*/ Cost computacional al .h /*/

#include "Transaction.h"

Transaction::Transaction(){
    this->temps = "";
    this->client_id  = 0;
    this->amount = 0.; 
}

Transaction::Transaction(string& t, int& id, float& q){
    this->temps = t;
    this->client_id  = id;
    this->amount = q;  
}

Transaction::Transaction(const Transaction& orig){
    this->temps = orig.temps;
    this->client_id  = orig.client_id ;
    this->amount = orig.amount;  
    
}

Transaction::~Transaction(){
}

/* Mètode print */

const void Transaction::print() const{
    cout<<"("<<temps<<", " <<client_id <<", "<<amount<<")";
}

/* Getters */

const string& Transaction::getTemps() const{
    return this->temps;
}
const int& Transaction::getID() const{
    return this->client_id ;
}
const float& Transaction::getQuantitat() const{
    return this->amount;
}

/* Setters */

void Transaction::setTemps(string& t){
    this->temps = t;
}
void Transaction::setID(int& t){
    this->client_id = t;
}
void Transaction::setQuantitat(float& t){
    this->amount = t;
}