/* Especificació de TransactionManager */

/*/ COST COMPUTACIONAL:
 * TransactionManager: O(1)
 * TransactionManager (constructor amb paràmetres): O(1)
 * TransactionManager(constructor còpia): O(n)
 * ~TransactionManager (destructor): O(n)
 * loadFromFile: O(n) en el pitjor cas
 * showAll: O(n) en el pitjor cas
 * showAllReverse: O(n) en el pitjor cas
 * showOldest: O(n) en el pitjor cas
 * showNewest: O(n) en el pitjor cas
 * feesInTotal: O(1)
 * feesSinceTime: O(n) en el pitjor cas
 * feesInTimeInterval: O(n) en el pitjor cas
 * imprimirTransaccions: O(n) en el pitjor cas
 * showAllAux: O(n) en el pitjor cas
 * showAllReverseAux: O(n) en el pitjor cas
 * sumaTransaccions: O(n) en el pitjor cas
 * feesSinceTimeAux: O(n) en el pitjor cas
 * calculaBalanc: O(n) en el pitjor cas
/*/

#ifndef TRANSACTIONMANAGER_H
#define TRANSACTIONMANAGER_H
#include <iostream>
#include "BinarySearchTree.h"
#include "Transaction.h"
using namespace std;

class TransactionManager : protected BinarySearchTree<string, Transaction>{
public:
    TransactionManager(float buyingFee = 0.02, float sellingFee = 0.03);
    TransactionManager(string file_path, float buyingFee = 0.02, float sellingFee = 0.03);
    TransactionManager(const TransactionManager& orig);
    virtual ~TransactionManager();

    void loadFromFile(string file_path);
    void showAll() const;
    void showAllReverse() const;
    void showOldest() const;
    void showNewest() const;

    float feesInTotal() const;
    float feesSinceTime(string date) const;
    float feesInTimeInterval(pair<string,string> interval) const;
    
    /* Mètodes auxiliars */
    void imprimirTransaccions(vector<Transaction> transaccions) const;
    void showAllAux(const BinaryTreeNode<string,Transaction>* n, int& i) const;
    void showAllReverseAux(const BinaryTreeNode<string,Transaction>* n, int& i) const;
    void sumaTransaccions(vector<Transaction> transaccions, float& suma) const;
    void feesSinceTimeAux(const BinaryTreeNode<string,Transaction>* n, float& suma) const;
    float calculaBalanc(string nomFitxer);

private:
    float sellingFee;
    float buyingFee;
};

#endif /* TRANSACTIONMANAGER_H */

