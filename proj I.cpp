#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
const int MAX_ACTIVE_ITEMS = 100; // maximum number of Items that can be stroed.

struct storeItems {
    string name, company, productID;
    double size;//unitsize 5 ltr or 150kg 
    string type;//gram(g), liter(ltr), meter(m), pieces(pcs), not defined(nl)
    double price;
    int amount;//quantity of item, how many of item .
};
void getRecord(storeItems activeItems[], int amount);
/*This funtion takes activeItems[] and active as its parameter
 * and it registers items from the user for the first time.
 */
void report(storeItems activeItems[], int active);
/*This function takes activeItems[] and active as its parameter
 * and displays the Items in the activeItems[][];
 */ 
void addItem(storeItems activeItems[], int& active);
/*This function takes activeItems[] and active as its parameter and 
 *It takes the name of Item to add. Then if the name of the item
 *already exists by searching it through searchItem function it just increament
 *activeItem[i].amount without creating new. 
 *If it doesn't exist this function add it to activeItems[] array.
 */
int searchItem(string name, storeItems activeItems[], int active);
/* This also activeItemss active(tem[] and active but in addition to that
 *It also have a string 'name' parameter which holds the string to be 
 *searched for.
 *This functtion retun the index of Item in the activeItems[] if the Item 
 * exists and returns -1 if the item doesn't exist.
 */
void removeItem(storeItems activeItems[], int& active);
/*This finction also activeItemss activeItems[][] and active as its parameter.
 *it removes Item from activeItems[]. It activeItemss a string value of the name 
 *of item to be removed. then by searchItem function it access the index of 
 *of item in activeItems[]. if index = -1 it means there is no element.
 ** if index is greater than -1 then the funciton replaces the activeItem[i] by
 *activeItem[i + 1]. i = index.
 */
void sellItem(storeItems activeItems[], int& active);
/*Takes activeItems and active as parameter.
 *askes user to type the name of item to be sold.(string name).
 *the int index get the index of item from searchItem function.
 *if index >= 0 or exists in activeItems then it decrease 
 *the activeItems[index].amount by amount(quantity to be sold).
 */
void save(storeItems activeItems[], int active, ofstream &out);
/*Saves items in the activeItems[] array to file called "proj1.txt"
*/
void get_file(storeItems activeItems[],int &active, ifstream &in);
/*gets items from file called in to activeItems[] but to do that first
 *determines the number of items by counting '\n'(int size) in the proj1.txt
 *then add items to activeItems.
 */
void isLow(storeItems activeItems[], int active);
/*this fuction excutes as long as there is an Item which has 
 *it's quantity(amount) below 5 and tell user that the user has 'Low quantity Items'
 */
string itemType(char c){
    if(c == 'g') return "gm";
    else if(c == 'l') return "ltr";
    else if(c == 'm') return "m";
    else if(c == 'p') return "pcs";
    else return "nl";
}
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
        else cout << "Invalid input!\n";
        isLow(activeItems, active);
        cout << endl;
        cout << "Do you want to continue with other operation?\n"
             << "press 'Y' or 'y' to do other operation other wise press any key\n";
        cin >> chooseToexit;
    } while (chooseToexit == 'Y' || chooseToexit == 'y');
    return 0;
}
void getRecord(storeItems activeItems[], int amount){
    for(int i = 0; i < amount; i++){
        char choosetype;
        cout << "Enter the name :\n";
        cin >> activeItems[i].name;
        cout << "Enter the price : \n";
        cin >> activeItems[i].price;
        cout << "Enter the unitsize : \n";
        cin >> activeItems[i].size;
        cout << "if the item is measured mass type 'g'\n" 
                << "if item is measured length type 'm'\n"
                <<"if item is measured volume type 'l'\n"
                <<"if item is counted type 'p'\n"
                <<"if the item does't have a known unit of measurement type 'n'"
                << endl;
        cin >> choosetype;
        activeItems[i].type = itemType(choosetype);
        cout << "How many " << activeItems[i].name << " are you storing : \n";
        cin >> activeItems[i].amount;
        cout << "Enter the productID : \n";
        cin >> activeItems[i].productID;
        cout << "Enter the company : \n";
        cin >> activeItems[i].company;
    }
}
void report(storeItems activeItems[], int active){
    cout << setw(15) << left << "Items";
    cout << setw(15) << left << "price";
    cout << setw(15) << left << "unitsize";
    cout << setw(15) << left << "Quantity";
    cout << setw(15) << left << "productID";
    cout << setw(15) << left << "company";
    cout << endl;
    for (int i = 0; i < active; i++)
    {
        cout << setw(15) << left << activeItems[i].name;
        cout << setw(15) << left << activeItems[i].price;
        cout << setw(5) << left << activeItems[i].size;
        cout << setw(10) << left << activeItems[i].type;
        cout << setw(15) << left << activeItems[i].amount;
        cout << setw(15) << left << activeItems[i].productID;
        cout << setw(15) << left << activeItems[i].company;
        cout << endl;
    }
}
int searchItem(string name, storeItems activeItems[], int active){
    int index = -1;
     for(int i = 0; i < active; i++){
        if(activeItems[i].name == name){
            index = i;
        }
     }
    return index;
}
void addItem(storeItems activeItems[], int& active){
    string name;
    int index, add_amount;
    cout << "Enter the name of an Item\n";
    cin >> name;
    index = searchItem(name, activeItems, active);
    if(index < 0){
        char choosetype;
        activeItems[active].name = name;
        cout << "Enter the price : \n";
        cin >> activeItems[active].price;
        cout << "Enter the size : \n";
        cin >> activeItems[active].size;
        cout << "if the item is measured mass type 'g'\n" 
                << "if item is measured length type 'm'\n"
                <<"if item is measured volume type 'l'\n"
                <<"if item is counted type 'p'\n"
                <<"if the item does't have a known unit of measurement type 'n'"
                << endl;
        cin >> choosetype;
        activeItems[active].type = itemType(choosetype);
        cout << "How many " << activeItems[active].name << " are you storing : \n";
        cin >> activeItems[active].amount;
        cout << "Enter the productID : \n";
        cin >> activeItems[active].productID;
        cout << "Enter the company : \n";
        cin >> activeItems[active].company;
        active++;
    }
    else {
        cout << "The Item already exist. Enter amount you want to add\n";
        cin >> add_amount;
        activeItems[active].amount = activeItems[active].amount + add_amount;
    }

}
void removeItem(storeItems activeItems[], int& active){
    string to_remove;
    int index;
    cout << "Which Item do you want to remove. Enter the name of Item.\n";
    cin >> to_remove;
    index = searchItem(to_remove, activeItems, active);
    if(index >= 0){
        for(int i = index; i < active; i++){
            activeItems[i] = activeItems[i + 1];
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
                        << " is sold successfully :)\n";
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
                             << " is sold successfully :)\n";
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
void save(storeItems activeItems[], int active, ofstream &out){
    if(!out.fail()){
        for(int i = 0; i < active; i++){
            out << setw(10) << left << activeItems[i].name;
            out << setw(10) << left << activeItems[i].price;
            out << setw(5) << left << activeItems[i].size;
            out << setw(5) << left << activeItems[i].type;
            out << setw(10) << left << activeItems[i].amount;
            out << setw(10) << left << activeItems[i].productID;
            out << setw(10) << left << activeItems[i].company;
            out << endl;
        }
    }
    else {
        cout << "Saving failed!";
    }
}
void get_file(storeItems activeItems[],int &active, ifstream &in){
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
    else cout << "Reading Failed!\n";
    active = size;
    ifstream in2("proj1.txt");
    if (!in2.fail()) {
        for (int i = 0; i < size; i++) {
            in2 >> activeItems[i].name >> activeItems[i].price >> activeItems[i].size 
                >> activeItems[i].type >> activeItems[i].amount >> activeItems[i].productID 
                >> activeItems[i].company;
        }
        in2.close();
    }
    else cout << "Reading Failed!";
}
void isLow(storeItems activeItems[], int active){
    int treshold = 5;
    int count = 0;
    for(int i = 0; i < active; i++){
        if(activeItems[i].amount < treshold){
            count++;
        }
    }
    if(count > 0){
        int lowIndex[count];
        for (int i = 0, j = 0; i < active; i++) {
            if (activeItems[i].amount < treshold) {
                lowIndex[j++] = i;
            }
        }
        cout << setw(10) << right;
        for (int i = 0; i < 30; i++) {
            cout << "-";
        }
        cout << endl;
        cout << setw(30) << right << "Low Quantity Items" << endl;
        cout << setw(10) << right;
        for (int i = 0; i < 30; i++) {
            cout << "-";
        }
        cout << endl;
        for (int i = 1; i <= count; i++) {
            int t = lowIndex[i - 1];
            cout << i << ". " << activeItems[t].name
                 << "    Quantity " << activeItems[t].amount << endl;
        }
    }
}
