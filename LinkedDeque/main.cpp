/* Classe principal */

#include <cstdlib>
#include <iostream>
#include <vector>
#include "LinkedDeque.h"

using namespace std;

// Aquest mètode mostra el menú i retorna la opció escollida si aquesta és correcte.
int opcio(vector<string> options){
    int option=0;
    cout<<"Hola, que vols fer?"<<endl;
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

// Demana el nom, saluda i demana una opció mostrades per un menú.
int main() {
    int option = 0, n=0;
    LinkedDeque<int> deque;
    cout<<"Estructura creada"<<endl;
    vector<string> options{"Inserir element al davant de la cua", "Inserir element al darrera de la cua", "Treure element pel davant de la cua",
            "Treure element pel darrera de la cua","Consultar el primer element","Consultar el darrer element","Imprimir tot el contingut de l’ArrayDeque","Sortir"};
            
    do{
        option = opcio(options);
        switch(option){
            case 1: cout<<"\nElement a inserir: ";cin>>n;deque.enqueueFront(n);n=0; break;
            case 2: cout<<"\nElement a inserir: ";cin>>n;deque.enqueueBack(n);n=0;break;
            case 3: try{deque.dequeueFront();}catch(const invalid_argument& e){cout<<e.what()<<"\n"<<endl;};break;
            case 4: try{deque.dequeueBack();}catch(const invalid_argument& e){cout<<e.what()<<"\n"<<endl;};break;
            case 5: try{
                        int front = deque.getFront();
                        cout<<"\nPrimer element: "<<front<<"\n"<<endl;
                    }catch(const invalid_argument& e){
                        cout<<e.what()<<"\n"<<endl;// S'ha produit una excepció (el deque està buit)
                    };break;
            case 6: try{
                        int rear = deque.getBack();
                        cout<<"\nÚltim element: "<<rear<<"\n"<<endl;
                    }catch(const invalid_argument& e){
                        cout<<e.what()<<"\n"<<endl;// S'ha produit una excepció (el deque està buit)
                    };break;
            case 7: try{cout<<"\nDeque: ";deque.print();}catch(const invalid_argument& e){cout<<e.what()<<"\n"<<endl;};break;
        }
    }while(option!=8);
    
    return 0;
}

