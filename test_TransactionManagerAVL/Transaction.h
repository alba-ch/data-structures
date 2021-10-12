/* Especificació de Transaction */

/*/ COST COMPUTACIONAL:
 * Transaction: O(1)
 * Transaction (amb paràmetres): O(1)
 * Transaction (constructor còpia): O(1)
 * ~Transaction (destructor): O(1)
 * getTemps: O(1)
 * getID: O(1)
 * getQuantitat: O(1)
 * setTemps: O(1)
 * setID: O(1)
 * setQuantitat: O(1)
 * print: O(1)
*/

#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <iostream>
using namespace std;

class Transaction {
public:
    Transaction();
    Transaction(string&, int&, float&);
    Transaction(const Transaction& orig);
    virtual ~Transaction();
    const float feesInTotal() const;
    /* Getters*/
    const string& getTemps() const;
    const int& getID() const;
    const float& getQuantitat() const;
    /* Setters */
    void setTemps(string&);
    void setID(int&);
    void setQuantitat(float&);
    /* Print */
    const void print() const;
    
private:
    string temps;
    int client_id;
    float amount;
};

#endif /* TRANSACTION_H */
