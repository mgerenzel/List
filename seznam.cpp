#include <cstdlib>
#include <iostream>
#include "seznam.h"
#include <string>
#include <stdexcept>
#include <fstream>
using namespace std;

List::List(){
    head = NULL;
    curr = NULL;
    temp = NULL;
    orderCount = 1;
}

void List::showOptions(){
    cout << "Choose one of the options!" << endl;
    cout << "0: Adding new order" << endl;
    cout << "1: Deleting an order" << endl;
    cout << "2: Editing the order" << endl;
    cout << "3: Quit" << endl;
}

void List::addOrder(){
    try{
        int quantity;
        List::CoffeeType coffeeType = getCoffeeType();
        cout << "Enter quantity" << endl;
        cin>> quantity;
        addOrder(coffeeType, quantity);
    } catch( const std::invalid_argument& e ) {
        cout << "Invalid choice" << endl;
    }
}

void List::addOrder(CoffeeType coffee, int quantity){
    nodePtr n = new node;
    n->next = NULL;
    n->idOrder = orderCount++;
    n->coffeeType = getTextForEnum(coffee);
    n->price = getPrice(coffee)* quantity;
    n->quantity = quantity;
    if(head != NULL){
       curr = head;
       while(curr->next!= NULL){
          curr = curr->next;
       }
       curr->next=n;
    }else{
       head = n;
    }
}

void List::deleteOrder(){
    if(!isEmpty()){
        int delOrder;
        cout<< "please type the id order to delete"<< endl;
        cin >> delOrder;
        deleteOrder(delOrder);
    } else {
        cout << "Order list is empty!" << endl;
    }
}

void List::deleteOrder(int delOrder){
    orderCount -= 1;
    nodePtr delPtr = NULL;
    temp = head;
    curr = head;
    while (curr->next != NULL && curr->idOrder != delOrder){
        temp = curr;
        curr = curr->next;
    }
    if(curr->idOrder == delOrder){
        delPtr = curr;
        curr = curr->next;
        temp -> next = curr;
        if(head == delPtr){
            head = delPtr->next;
        }
        delete delPtr;
        cout<<"\n The order number " << delOrder << " was taken :)  \n"<< endl;
    }else{
        cout<< delOrder<< " was not in the list" <<endl;
        delete delPtr;
    }
}

string List::getTextForEnum(CoffeeType ct){
   switch(ct)
  {
  case CAPUCCINO:
    return "Cappuccino";
  case LATTE:
    return "Latte";
  case ESPRESSO:
    return "Espresso" ;
  default:
    return "Not recognized..";
  }
}

void List::saveList(){
    curr = head;
    ofstream file("oreders.txt");
    if(file.is_open()){
        cout<<"the file is associated"<<endl;
    } else {
        cout<< "There is a problem with file associating process" <<endl;
    }
    if (head==NULL){
        file << "Order list is empty" << endl;
    }
    file << "Id   Quantity       Name            Price" << endl;
    while(curr!= NULL){
        file << curr->idOrder << "        " << curr->quantity << "          " <<
        curr->coffeeType <<"           " << curr->price << " CZK" << endl;
        curr=curr->next;
    }
      file<< "--------------------------------------------------" << endl;
      file.close();
}

void List::editOrder(){
    if(!isEmpty()){
        int id;
        int quantity;
        cout<<" Please enter the id to edit"<<endl;
        cin >> id;
        try{
            cout<< "please choose coffee type "<< endl;
            List::CoffeeType coffee = getCoffeeType();
            cout<< "please enter the quantity"<< endl;
            cin >> quantity;
            editOrder(id, coffee, quantity);
        } catch( const std::invalid_argument& e ) {
            cout << "Invalid choice" << endl;
        }
    } else {
        cout << "Order list is empty!" << endl;
    }
}

void List::editOrder(int id, CoffeeType coffee,int quantity){
    curr = findOrder(id);
    if(curr == NULL){
        cout << "Invalid choice" << endl;
    }else{
        curr->coffeeType = getTextForEnum(coffee);
        curr->quantity = quantity;
        curr->price = getPrice(coffee)*quantity;
    }
}

bool List::isEmpty(){
    if(head == NULL)
        return true;
    return false;
}

List::nodePtr List::findOrder(int id){
    nodePtr findPtr = NULL;
    if(!isEmpty()){
        curr = head;
        while (curr->next!=NULL &&curr ->idOrder != id){
            curr = curr->next;
        }
        if(curr->idOrder == id){
            findPtr = curr;
        }
    }
    return findPtr;
}

void List::deleteList(){
    orderCount = 1;
    while(head!=NULL){
        curr = head;
        head = head->next;
        delete curr;
    }
}

double List::getPrice(CoffeeType ct)
{
  switch(ct){
    case CAPUCCINO:
        return 50;

    case ESPRESSO:
        return 40;

    case LATTE:
        return 60;
    }
}

List::CoffeeType List::getCoffeeType(){
    int coffeeChoice;
    List::CoffeeType coffeeType;
    cout << " Please enter the coffee type"<< endl;
    cout << "0: Capuccino" << endl;
    cout << "1: Espresso" << endl;
    cout << "2: Latte" << endl;
    cin>> coffeeChoice;
    switch(coffeeChoice){
       case 0:{
           coffeeType = List::CAPUCCINO;
           break;
       }
       case 1:{
           coffeeType = List::ESPRESSO;
           break;
       }
       case 2:{
           coffeeType = List::LATTE;
           break;
       }
       default:
           throw std::invalid_argument("Invalid choice");
    }
    return coffeeType;
}

void List::start(){
    int choice;
    bool programRunning = true;
    while (programRunning){
        showOptions();
        cin >> choice;
        switch (choice){
            case 0: {
                addOrder();
                saveList();
                break;
            }
            case 1: {
                deleteOrder();
                saveList();
                break;
            }
            case 2: {
                editOrder();
                saveList();
                break;
            }
             case 3: {
                programRunning = false;
                cout << "Good bye" << endl;
                break;
            }
            default: {
                cout << "Choice is not valid. Try again please" << endl;
                break;
            }
        }
    }
}

