#ifndef SEZNAM_H_INCLUDED
#define SEZNAM_H_INCLUDED

using namespace std;

class List{

private:
    typedef struct node{
    int idOrder;
    string name;
    string coffeeType;
    double price;
    int quantity;
    node* next;
    }* nodePtr;

    nodePtr head;
    nodePtr curr;
    nodePtr temp;
    int orderCount;
public:
    enum CoffeeType {CAPUCCINO, LATTE, ESPRESSO};
    List();
    double getPrice(CoffeeType ct);
    void addOrder();
    void addOrder(CoffeeType coffee,int quantity);
    void deleteList();
    void deleteOrder();
    void deleteOrder(int delOrder);
    void editOrder();
    void editOrder(int id, CoffeeType coffee,int quantity);
    nodePtr findOrder (int id );
    CoffeeType getCoffeeType();
    string getTextForEnum(CoffeeType);
    bool isEmpty();
    bool programRunning;
    void saveList();
    void showOptions();
    void start();
};

#endif // SEZNAM_H_INCLUDED
