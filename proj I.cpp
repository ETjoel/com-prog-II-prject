#include <iostream>
#include <fstream>
using namespace std;
int MAX_ACTIVE_ITEMS = 100;

struct storeItems {
    string name, company, productID;
    double size, price;
    int amount;
};
void getRecord(storeItems getItems[], int amount);
void report(storeItems activeItems[], int active);
void addItem(storeItems addItems[], int& active);
int searchItem(string name, storeItems searchItem[], int active);
void removeItem(storeItems removeItem[], int& active);
void sellItem(storeItems removeItem[], int& active);
void save(storeItems save[], int active, ofstream &out);
void get_file(storeItems accept[],int &active, ifstream &in);
int main(){
    storeItems activeItems[MAX_ACTIVE_ITEMS];
    int active = 0;
    char chooseToexit;
    int chooseNum;
    do
    {
        cout << "1. Get a record of the items in the store\n"
             << "2. Add items to the store\n"
             << "3. Removing items from the store\n"
             << "4. Sell a product\n"
             << "5. Report the status of items in the store\n"
             << "6. Save and update the status of the store\n"
             << "7. Reload from previos excution\n";
        cout << "What do you want to do? please type in the number\n";
        cin >> chooseNum;
        if (chooseNum == 1)
        {
            int amount;
            cout << "How many items do you want to register\n";
            cin >> amount;
            if(amount > 0 && amount < (MAX_ACTIVE_ITEMS - active)) {
                active = amount;
                storeItems getItems[amount];
                getRecord(getItems, amount);
                for (int i = 0; i < amount; i++) {
                    activeItems[i] = getItems[i];
                }
            }
            else cout << "Invalid input\n";
        }
        else if (chooseNum == 2){
            addItem(activeItems, active);
        }
        else if (chooseNum == 3){
            removeItem(activeItems, active);
        }
        else if (chooseNum == 4){
            sellItem(activeItems, active);
        }
        else if (chooseNum == 5){
            report(activeItems, active);
        }
        else if (chooseNum == 6){
            ofstream out("proj1.txt");
            save(activeItems, active, out);
        }
        else if(chooseNum == 7){
            ifstream in("proj1.txt");
            get_file(activeItems, active, in);
        } 
        else cout << "Invalid input!";
        cout << endl;
        cout << "Do you want to continue with other operation?\n"
             << "press 'Y' or 'y' to do other operation other wise press any key\n";
        cin >> chooseToexit;
    } while (chooseToexit == 'Y' || chooseToexit == 'y');
    return 0;
}
void getRecord(storeItems getItems[], int amount){
    for(int i = 0; i < amount; i++){
        cout << "Enter the name of the item : \n";
        cin >> getItems[i].name;
        cout << "Enter the price : \n";
        cin >> getItems[i].price;
        cout << "Enter the size : \n";
        cin >> getItems[i].size;
        cout << "Enter the amount : \n";
        cin >> getItems[i].amount;
        cout << "Enter the productID : \n";
        cin >> getItems[i].productID;
        //cout << "Enter the type : \n";
        //cin >> getItems[i].type;
        cout << "Enter the company : \n";
        cin >> getItems[i].company; 
    }
}
void report(storeItems activeItems[], int active){
    cout << setw(10) << left << "Items";
    cout << setw(10) << left << "price";
    cout << setw(10) << left << "size";
    cout << setw(10) << left << "amount";
    cout << setw(10) << left << "productID";
    cout << setw(10) << left << "company";
    cout << endl;
    for (int i = 0; i < active; i++)
    {
        cout << setw(10) << left << activeItems[i].name;
        cout << setw(10) << left << activeItems[i].price;
        cout << setw(10) << left << activeItems[i].size;
        cout << setw(10) << left << activeItems[i].amount;
        cout << setw(10) << left << activeItems[i].productID;
        cout << setw(10) << left << activeItems[i].company;
        cout << endl;
    }
}
int searchItem(string name, storeItems searchItem[], int active){
    int index = -1;
     for(int i = 0; i < active; i++){
        if(searchItem[i].name == name){
            index = i;
        }
     }
    return index;
}
void addItem(storeItems getItems[], int& active){
    string name;
    int index, add_amount;
    cout << "Enter the name of an Item\n";
    cin >> name;
    index = searchItem(name, getItems, active);
    if(index < 0){
        getItems[active].name = name;
        cout << "Enter the price : \n";
        cin >> getItems[active].price;
        cout << "Enter the size : \n";
        cin >> getItems[active].size;
        cout << "Enter the amount : \n";
        cin >> getItems[active].amount;
        cout << "Enter the productID : \n";
        cin >> getItems[active].productID;
        cout << "Enter the company : \n";
        cin >> getItems[active].company;
        active++;
    }
    else {
        cout << "The Item already exist. Enter amount you want to add\n";
        cin >> add_amount;
        getItems[active].amount = getItems[active].amount + add_amount;
    }

}
void removeItem(storeItems removeItem[], int& active){
    string to_remove;
    int index;
    cout << "Which Item do you want to remove. Enter the name of Item.";
    cin >> to_remove;
    index = searchItem(to_remove, removeItem, active);
    if(index >= 0){
        for(int i = index; i < active; i++){
            removeItem[i] = removeItem[i + 1];
        }
        active--;
    }
    else cout << "The item you requested doesn't exist";
}
void sellItem(storeItems sellItem[], int& active){
    cout << "The item available now are listed below\n";
    report(sellItem, active);
    char choose;
    int amount;
    string name;
    do {
        cout << "continue selling\n";
        cout << "Enter name of the item\n";
        cin >> name;
        int index = searchItem(name, sellItem, active);
        if(index >= 0){
            cout << "There are " << sellItem[index].amount
                << " available. How many of them do you want to sell?\n";
            cin >> amount;
            if(amount == 0){
                cout << "The store is out of " << sellItem[index].name << endl;
            }
            else if(amount > 0 && amount <= sellItem[index].amount){
                char confirm;
                cout << "Total price " << amount << " of " << sellItem[index].name
                    << " is " << amount * sellItem[index].price << endl;
                cout << "comfirm seeling the item by pressing y or Y\n";
                cin >> confirm;
                if(confirm == 'y' || confirm == 'Y'){
                    cout << amount << " of " << sellItem[index].name 
                        << " is sold successfully :)";
                    sellItem[index].amount -= amount;
                }
            }
            else if (amount > sellItem[index].amount){
                char choose;
                cout << "The store only have " << sellItem[index].amount 
                    << " amount of " << sellItem[index].name << endl;
                cout << "If you want to take it all enter 'y' or 'Y'\n";
                cin >> choose;
                if (choose == 'y' || choose == 'Y')
                {
                    char confirm;
                    cout << "Total price " << sellItem[index].amount 
                         << " of " << sellItem[index].name
                         << " is " << sellItem[index].amount * sellItem[index].price << endl;
                    cout << "comfirm seeling the item by pressing y or Y\n";
                    cin >> confirm;
                    if (confirm == 'y' || confirm == 'Y')
                    {
                        cout << sellItem[index].amount << " of " << sellItem[index].name
                             << " is sold successfully :)";
                        sellItem[index].amount -= sellItem[index].amount;
                    }
                }
            }
            else cout << "Invalid input";
        }
        else cout << "The Item you requested is not in the store registry\n";
        cout << "press 'y' or 'Y' to continue selling\n";
        cin >> choose;
    }while(choose == 'y' || choose == 'Y');
}
void save(storeItems save[], int active, ofstream &out){
    if(!out.fail()){
        for(int i = 0; i < active; i++){
            out << setw(20) << left << save[i].name;
            out << setw(20) << left << save[i].price;
            out << setw(20) << left << save[i].size;
            out << setw(20) << left << save[i].amount;
            out << setw(20) << left << save[i].productID;
            out << setw(20) << left << save[i].company;
            out << endl;
        }
    }
    else {
        cout << "Saving failed!";
    }
}
void get_file(storeItems accept[],int &active, ifstream &in){
    char temp;
    int size = 0;
    int t = 0;
    if(!in.fail()){
        in.seekg(t, ios::beg);
        while(!in.eof()){
            in.seekg(t, ios::beg);
            in.get(temp);
            if(in.eof()) break;
            if(temp == '\n'){
                size++;
            }
            t++;
        }
        in.close();
    }
    else cout << "Reading Failed!";
    active = size;
    ifstream in2("proj1.txt");
    if (!in2.fail()) {
        for (int i = 0; i < size; i++) {
            in2 >> accept[i].name >> accept[i].price >> accept[i].size 
                >> accept[i].amount >> accept[i].productID >> accept[i].company;
        }
        in2.close();
    }
    else cout << "Reading Failed!";
}
