#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
const int MAX_ACTIVE_ITEMS = 100; // maximum number of Items that can be stroed.

struct storeItems
{
    string name, company, productID;
    double size; // unitsize 5 ltr or 150kg
    string type; // gram(g), liter(ltr), meter(m), pieces(pcs), not defined(nl)
    double price;
    int amount; // quantity of item, how many of item .
};
void getRecord(storeItems activeItems[], int amount);
/*This funtion takes activeItems[] and active as its parameter
 * and it registers items from the user for the first time.
 */
void report(storeItems activeItems[], int active);
/*This function takes activeItems[] and active as its parameter
 * and displays the Items in the activeItems[][];
 */
void addItem(storeItems activeItems[], int &active);
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
void removeItem(storeItems activeItems[], int &active);
/*This finction also activeItemss activeItems[][] and active as its parameter.
 *it removes Item from activeItems[]. It activeItemss a string value of the name
 *of item to be removed. then by searchItem function it access the index of
 *of item in activeItems[]. if index = -1 it means there is no element.
 ** if index is greater than -1 then the funciton replaces the activeItem[i] by
 *activeItem[i + 1]. i = index.
 */
void sellItem(storeItems activeItems[], int &active);
/*Takes activeItems and active as parameter.
 *askes user to type the name of item to be sold.(string name).
 *the int index get the index of item from searchItem function.
 *if index >= 0 or exists in activeItems then it decrease
 *the activeItems[index].amount by amount(quantity to be sold).
 */
void save(storeItems activeItems[], int active, ofstream &out);
/*Saves items in the activeItems[] array to file called "proj1.txt"
 */
void get_file(storeItems activeItems[], int &active, ifstream &in);
/*gets items from file called in to activeItems[] but to do that first
 *determines the number of items by counting '\n'(int size) in the proj1.txt
 *then add items to activeItems.
 */
void isLow(storeItems activeItems[], int active);
/*this fuction excutes as long as there is an Item which has
 *it's quantity(amount) below 5 and tell user that the user has 'Low quantity Items'
 */
void sort(storeItems activeItems[], int active, char c);
void swap(storeItems activeItems[], int active);
string itemType(char c)
{
    if (c == 'g')
        return "gm";
    else if (c == 'l')
        return "ltr";
    else if (c == 'm')
        return "m";
    else if (c == 'p')
        return "pcs";
    else
        return "nl";
}
bool is_digit(string temp)
{
    bool b = true;
    for (int i = 0; i < temp.length(); i++)
    {
        if (!isdigit(temp[i]))
            b = false;
    }
    return b;
}
bool is_float(string temp)
{
    bool b = true;
    for (int i = 0; i < temp.length(); i++)
    {
        if (!(isdigit(temp[i]) || temp[i] == '.'))
            b = false;
    }
    return b;
}
int main()
{
    storeItems activeItems[MAX_ACTIVE_ITEMS];
    int active = 0;
    char chooseToexit;
    string chooseNum;
    do
    {
        cout << "1. Register new items in the inventory\n"
             << "2. Add items to the inventory\n"
             << "3. Removing items from the inventory.\n"
             << "4. Sell a product.\n"
             << "5. Display the current status of the inventory.\n"
             << "6. View low stock items\n"
             << "7. load the inventory data from a file\n"
             << "8. save the inventory data to a file\n";
        cout << "What do you want to do? please type in the number\n";
        cin >> chooseNum;
        if (is_digit(chooseNum))
        {
            if (stoi(chooseNum) == 1)
            {
                string amount;
                do
                {
                    cout << "How many items do you want to register\n";
                    cin >> amount;
                    if (is_digit(amount))
                    {
                        if (stoi(amount) > 0 && stoi(amount) <= (MAX_ACTIVE_ITEMS))
                        {
                            active = stoi(amount);
                            getRecord(activeItems, stoi(amount));
                        }
                    }
                    else
                        cout << "Please enter a proper input\n";
                } while (!(is_digit(amount) && (stoi(amount) > 0 && stoi(amount) <= MAX_ACTIVE_ITEMS)));
            }
            else if (stoi(chooseNum) == 2)
            {
                addItem(activeItems, active);
            }
            else if (stoi(chooseNum) == 3)
            {
                removeItem(activeItems, active);
            }
            else if (stoi(chooseNum) == 4)
            {
                sellItem(activeItems, active);
            }
            else if (stoi(chooseNum) == 5)
            {
                char sortType;
                do{
                   cout << "In what order do you want to get report.\n";
                   cout << "For name order enter 'n', For Quantity order enter 'q'\n";
                   cin >> sortType;
                   if(!(sortType == 'n' || sortType == 'q'))
                        cout << "please enter valid input";
                }while(!(sortType == 'n' || sortType == 'q'));
                sort(activeItems, active, sortType);
                report(activeItems, active);
            }
            else if (stoi(chooseNum) == 6)
            {
                isLow(activeItems, active);
            }
            else if (stoi(chooseNum) == 7)
            {
                ifstream in("proj1.txt");
                get_file(activeItems, active, in);
            }
            else if (stoi(chooseNum) == 8)
            {
                ofstream out("proj1.txt");
                save(activeItems, active, out);
            }
            else
                cout << "please enter from the given choice!\n";
        }
        else
            cout << "Please input a valid input\n";
        cout << endl;
        cout << "Do you want to continue with other operation?\n"
             << "press 'Y' or 'y' to do other operation other wise press any key\n";
        cin >> chooseToexit;
    } while (chooseToexit == 'Y' || chooseToexit == 'y');
    return 0;
}
void getRecord(storeItems activeItems[], int amount)
{
    string s;
    for (int i = 0; i < amount; i++)
    {
        char choosetype;
        cout << "Enter the name :\n";
        cin >> activeItems[i].name;
        do
        {
            cout << "Enter the price : \n";
            cin >> s;
            if (!is_float(s))
                cout << "please enter a valid input";
        } while (!is_float(s));
        activeItems[i].price = stod(s);
        s.clear();
        do
        {
            cout << "Enter the unitsize : \n";
            cin >> s;
            if (!is_digit(s))
                cout << "Please enter the proper input\n";
        } while (!is_digit(s));
        activeItems[i].size = stoi(s);
        s.clear();
        do
        {
            cout << "if the item is measured mass type 'g'\n"
                 << "if item is measured length type 'm'\n"
                 << "if item is measured volume type 'l'\n"
                 << "if item is counted type 'p'\n"
                 << "if the item does't have a known unit of measurement type 'n'\n";
            cin >> choosetype;
            if (!(choosetype == 'g' || choosetype == 'm' || choosetype == 'l' || choosetype == 'p' || choosetype == 'n'))
                cout << "please enter the proper input\n";
        } while (!(choosetype == 'g' || choosetype == 'm' || choosetype == 'l' || choosetype == 'p' || choosetype == 'n'));
        activeItems[i].type = itemType(choosetype);
        do
        {
            cout << "How many " << activeItems[i].name << " are you storing : \n";
            cin >> s;
            if (!is_digit(s))
                cout << "please enter a proper input";
        } while (!is_digit(s));
        activeItems[i].amount = stoi(s);
        cout << "Enter the productID : \n";
        cin >> activeItems[i].productID;
        cout << "Enter the company : \n";
        cin >> activeItems[i].company;
    }
}
void report(storeItems activeItems[], int active)
{
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
int searchItem(string name, storeItems activeItems[], int active)
{
    int index = -1;
    for (int i = 0; i < active; i++)
    {
        if (activeItems[i].name == name)
        {
            index = i;
        }
    }
    return index;
}
void addItem(storeItems activeItems[], int &active)
{
    string name;
    int index, add_amount;
    cout << "Enter the name of an Item\n";
    cin >> name;
    index = searchItem(name, activeItems, active);

    if (index < 0)
    {
        string s;
        char choosetype;
        activeItems[active].name = name;
        do
        {
            cout << "Enter the price : \n";
            cin >> s;
            if (!is_float(s))
                cout << "please enter a valid input";
        } while (!is_float(s));
        activeItems[active].price = stod(s);
        s.clear();
        do
        {
            cout << "Enter the unitsize : \n";
            cin >> s;
            if (!is_digit(s))
                cout << "Please enter the proper input\n";
        } while (!is_digit(s));
        activeItems[active].size = stoi(s);
        s.clear();
        do
        {
            cout << "if the item is measured mass type 'g'\n"
                 << "if item is measured length type 'm'\n"
                 << "if item is measured volume type 'l'\n"
                 << "if item is counted type 'p'\n"
                 << "if the item does't have a known unit of measurement type 'n'\n";
            cin >> choosetype;
            if (!(choosetype == 'g' || choosetype == 'm' || choosetype == 'l' || choosetype == 'p' || choosetype == 'n'))
                cout << "please enter the proper input\n";
        } while (!(choosetype == 'g' || choosetype == 'm' || choosetype == 'l' || choosetype == 'p' || choosetype == 'n'));
        activeItems[active].type = itemType(choosetype);
        do
        {
            cout << "How many " << activeItems[active].name << " are you storing : \n";
            cin >> s;
            if (!is_digit(s))
                cout << "please enter a proper input";
        } while (!is_digit(s));
        activeItems[active].amount = stoi(s);
        cout << "Enter the productID : \n";
        cin >> activeItems[active].productID;
        cout << "Enter the company : \n";
        cin >> activeItems[active].company;
        active++;
    }
    else
    {
        cout << "The Item already exist. Enter quatity you want to add\n";
        cin >> add_amount;
        activeItems[index].amount = activeItems[index].amount + add_amount;
    }
}
void removeItem(storeItems activeItems[], int &active)
{
    string to_remove;
    int index;
    cout << "Which Item do you want to remove. Enter the name of Item.\n";
    cin >> to_remove;
    index = searchItem(to_remove, activeItems, active);
    if (index >= 0)
    {
        cout << activeItems[index].name << " have been successfully removed.\n";
        for (int i = index; i < active; i++)
        {
            activeItems[i] = activeItems[i + 1];
        }
        active--;
    }
    else
        cout << "The item you requested doesn't exist";
}
void sellItem(storeItems sellItem[], int &active)
{
    cout << "The item available now are listed below\n";
    report(sellItem, active);
    char choose;
    string amount;
    string name;
    do
    {
        cout << "continue selling\n";
        cout << "Enter name of the item\n";
        cin >> name;
        int index = searchItem(name, sellItem, active);
        if (index >= 0)
        {
            do
            {
                cout << "There are " << sellItem[index].amount
                     << " available. How many of them do you want to sell?\n";
                cin >> amount;
                if (!is_digit(amount))
                    cout << "please enter a proper input";
            } while (!is_digit(amount));
            if (sellItem[index].amount == 0)
            {
                cout << "The store is out of " << sellItem[index].name << endl;
            }
            else if (stoi(amount) > 0 && stoi(amount) <= sellItem[index].amount)
            {
                char confirm;
                cout << "Total price " << stoi(amount) << " of " << sellItem[index].name
                     << " is " << stoi(amount) * sellItem[index].price << endl;
                cout << "comfirm seeling the item by pressing y or Y\n";
                cin >> confirm;
                if (confirm == 'y' || confirm == 'Y')
                {
                    cout << stoi(amount) << " of " << sellItem[index].name
                         << " is sold successfully :)\n";
                    sellItem[index].amount -= stoi(amount);
                }
            }
            else if (stoi(amount) > sellItem[index].amount)
            {
                char choose;
                cout << "The store only have " << sellItem[index].amount
                     << " amount of " << sellItem[index].name << endl;
                cout << "If you want to sell it all enter 'y' or 'Y'\n";
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
            else
                cout << "Invalid input";
        }
        else
            cout << "The Item you requested is not in the store registry\n";
        cout << "press 'y' or 'Y' to continue selling\n";
        cin >> choose;
    } while (choose == 'y' || choose == 'Y');
}
void save(storeItems activeItems[], int active, ofstream &out)
{
    if (!out.fail())
    {
        for (int i = 0; i < active; i++)
        {
            out << setw(15) << left << activeItems[i].name;
            out << setw(15) << left << activeItems[i].price;
            out << setw(5) << left << activeItems[i].size;
            out << setw(10) << left << activeItems[i].type;
            out << setw(15) << left << activeItems[i].amount;
            out << setw(15) << left << activeItems[i].productID;
            out << setw(15) << left << activeItems[i].company;
            out << endl;
        }
        cout << "Savint to the file is successfull\n";
    }
    else
    {
        cout << "Saving failed!\n";
    }
    out.close();
}
void get_file(storeItems activeItems[], int &active, ifstream &in)
{
    char temp;
    int size = 0;
    if (!in.fail())
    {
        while (!in.eof())
        {
            in.get(temp);
            if (in.eof())
                break;
            if (temp == '\n')
            {
                size++;
            }
        }
        in.close();
    }
    else
        cout << "Reading Failed!\n";
    active = size;
    ifstream in2("proj1.txt");
    if (!in2.fail())
    {
        for (int i = 0; i < size; i++)
        {
            in2 >> activeItems[i].name >> activeItems[i].price >> activeItems[i].size >> activeItems[i].type >> activeItems[i].amount >> activeItems[i].productID >> activeItems[i].company;
        }
        in2.close();
        cout << "The item is successfully loaded\n";
    }
    else
        cout << "Reading Failed!";
}
void isLow(storeItems activeItems[], int active)
{
    int treshold = 5;
    int count = 0;
    for (int i = 0; i < active; i++)
    {
        if (activeItems[i].amount < treshold)
        {
            count++;
        }
    }
    if (count > 0)
    {
        int lowIndex[count];
        for (int i = 0, j = 0; i < active; i++)
        {
            if (activeItems[i].amount < treshold)
            {
                lowIndex[j] = i;
                j++;
            }
        }
        cout << setw(10) << right;
        for (int i = 0; i < 30; i++)
        {
            cout << "-";
        }
        cout << endl;
        cout << setw(30) << right << "Low Quantity Items" << endl;
        cout << setw(10) << right;
        for (int i = 0; i < 30; i++)
        {
            cout << "-";
        }
        cout << endl;
        for (int i = 1; i <= count; i++)
        {
            int t = lowIndex[i - 1];
            cout << i << ". " << activeItems[t].name
                 << "    Quantity " << activeItems[t].amount << endl;
        }
    }
    else
        cout << "There are no low stack items in the inventory\n";
}
void swap(storeItems& item1, storeItems& item2){
    storeItems temp = item1;
    item1 = item2;
    item2 = temp;
}
void sort(storeItems activeItems[], int active, char c)
{
    int least;
    if (c == 'n')
    {
        for (int i = 0; i < active - 1; i++)
        {
            least = i;
            for (int j = i + 1; j < active; j++)
            {
                if (activeItems[least].name > activeItems[j].name)
                    least = j;
            }
            swap(activeItems[least], activeItems[i]);
        }
    }
    else if (c == 'q')
        for (int i = 0; i < active - 1; i++)
        {
            least = i;
            for (int j = i + 1; j < active; j++)
            {
                if (activeItems[least].amount < activeItems[j].amount)
                    least = j;
            }
            swap(activeItems[least], activeItems[i]);
        }
}
