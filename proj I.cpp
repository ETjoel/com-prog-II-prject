#include <iostream>
#include <fstream>
using namespace std;
int MAX_ACTIVE_ITEMS = 100;

struct storeItems {
    string name, company , productID;
    double size, price;
    int amount;
};
void getRecord(storeItems getItems[], int amount);
void report(storeItems activeItems[], int active);
void addItem(storeItems addItems[], int& amount);
int searchItem(string name, storeItems searchItem[], int active);
void removeItem(storeItems removeItem[], int& active);
void sellItem(storeItems removeItem[], int& active);
void save(storeItems save[], int active, ofstream &out);
int main(){
    storeItems activeItems[MAX_ACTIVE_ITEMS];
    ofstream out("proj1.txt");
    int active;
    char chooseToexit;
    int chooseNum;
    do
    {
        cout << "1. Get a record of the items in the store\n"
             << "2. Add items to the store\n"
             << "3. Removing items from the store\n"
             << "4. Sell a product\n"
             << "5. Report the status of items in the store\n"
             << "6. Save and update the status of the store\n";
        cout << "What do you want to do? please type in the number\n";
        cin >> chooseNum;
        if (chooseNum == 1)
        {
            int amount;
            cout << "How many items do you want to register\n";
            cin >> amount;
            active = amount;
            storeItems getItems[amount];
            getRecord(getItems, amount);
            for(int i = 0; i < amount; i++){
                activeItems[i] = getItems[i];
            }
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
    cout.width(10); cout << left << "Items";
    cout.width(10); cout << left << "price";
    cout.width(10); cout << left << "size";
    cout.width(10); cout << left << "amount";
    cout.width(10); cout << left << "productID";
    cout.width(10); cout << left << "company";
    cout << endl;
    for (int i = 0; i < active; i++)
    {
        cout.width(10);
        cout << left << activeItems -> name;
        cout.width(10);
        cout << left << activeItems -> price;
        cout.width(10);
        cout << left << activeItems -> size;
        cout.width(10);
        cout << left << activeItems -> amount;
        cout.width(10);
        cout << left << activeItems -> productID;
        cout.width(10);
        cout << left << activeItems -> company;
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
void addItem(storeItems getItems[], int& amount){
    string name;
    int index, add_amount;
    cout << "Enter the name of an Item\n";
    cin >> name;
    index = searchItem(name, getItems, amount);
    if(index < 0){
        getItems[++amount]. name = name;
        cout << "Enter the price : \n";
        cin >> getItems[++amount].price;
        cout << "Enter the size : \n";
        cin >> getItems[++amount].size;
        cout << "Enter the amount : \n";
        cin >> getItems[++amount]. amount;
        cout << "Enter the productID : \n";
        cin >> getItems[++amount] .productID;
        //cout << "Enter the type : \n";
        //cin >> getItems[++amount].type;
        cout << "Enter the company : \n";
        cin >> getItems[++amount] . company; 
    }
    else {
        cout << "The Item already exist. Enter amount you want to add\n";
        cin >> add_amount;
        getItems -> amount = getItems -> amount + add_amount;
    }

}
void removeItem(storeItems removeItem[], int& active){
    int to_remove;
    
    cout << "How many Items do you want to remove\n";
    cin >> to_remove;
    int Indexes[to_remove];
    string names;
    storeItems temp[active - to_remove];
    for(int i = 0; i < to_remove; i++){
        if(i == 0){
            cout << "Type the name of Item\n";
            cin >> names;
        }
        else if(i < to_remove - 1){
            cout << "Enter the other names\n";
            cin >> names;
        }
        else { 
            cout << "Enter the final name\n";
            cin >> names;
        }
        Indexes[i] = searchItem(names, removeItem, active);
        names.clear();
    }
    for(int i = 0, j = 0; i < active; i++){
        bool present = false;
        for(int j = 0; j < to_remove; j++){
            if(Indexes[j] == i){
                present = true;
            }
        }
        if(present) continue;
        else {
            temp[j++] = removeItem[i];
        }
    }
    active -= to_remove;
    for(int i = 0; i < active; i++){
        removeItem[i] = temp[i];
    }
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
                    cout << amount << " of " << sellItem[index].name << " is sold successfully :)";
                }
                sellItem[index].amount -= amount;
            }
            else if (amount > sellItem[index].amount){
                char choose;
                cout << "The store only have " << sellItem[index].amount 
                    << " amount of " << sellItem[index].name << endl;
                cout << "If you want to take it all enter 'y' or 'Y'\n";
                cin >> choose;
                if (choose == 'y' || choose == 'Y') {
                    cout << amount << " " << name << " by " << sellItem[index].company
                         << " of price " << sellItem[index].price
                         << "have been successfully sold\n";
                    sellItem[index].amount -= amount;
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
    
}
