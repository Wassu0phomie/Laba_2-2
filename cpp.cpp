#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <chrono>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;
struct List //описание узла списка
{
	int data; //информационное поле
	List* next; //указатель на следующий элемент
	List* prev; //указатель на предыдущий элемент
};



//**********************CREATE A LIST WITH N RANDOM ELEMENTS(0, 99)**********************
struct List* createList(unsigned lenght) {
	if (lenght == 0) return nullptr;  // if length == 0 -> the list is not created

	struct List* Current = nullptr; // Адрес очередного элемента списка
	struct List* Next = nullptr; // Адрес следующего элемента списка
    srand(time(nullptr));
	// Creates DLL starting from the LAST node
	for (int i = 0; i < lenght; ++i) {
		Current = new List;
		Current->data = rand() % 100;

		Current->next = Next;
		if (Next) Next->prev = Current;
		Next = Current;
	}
	Current->prev = nullptr;
    // Возвращаем адрес последнего созданного элемента,
    // как адрес первого элемента списка
	return Current;  // Return head

}

//**********************FREE THE MEMORY**********************
void DeleteList (List * &head){
    List *temp;
    while ( head )
    {
        temp = head->prev;
        delete head;
        head = temp;
    }
}


//**********************CREATE A LIST FROM USER INPUT**********************
struct List* createListFromInput()
{
	List* Head = nullptr;
	List* Tail = nullptr;

	int userValue = 1;

	while (userValue != 0) {
        // Create NEW Node
        List* Current = new List;
        cin >> userValue;
        if (userValue != 0) {
            Current->data = userValue;
            Current->next = nullptr;

            if (Tail) {                     // If node isn't the head, then update the pointers
                Tail->next = Current;
                Current->prev = Tail;
            } else {                        // If tail is null, then it is the first element; update the head
                Current->prev = nullptr;
                Head = Current;
            }
            Tail = Current;
        }
    }
    return Head;
}

//**********************FIND NODE BY INDEX**********************
struct List* getItemByIndex(struct List* head, unsigned position) {
	if (!head) {  //
		cout << "List is empty\n";
		return nullptr;
	}


	for (unsigned i = 0; i < position; ++i) {
		if (!head->next) {
			cout << "Index out of range\n";
			return nullptr;
		}
		head = head->next;
	}

	return head;
}

//**********************FIND NODE BY VALUE**********************
struct List* getItemByValue(struct List* head, int value) {
    if (!head) {  // Empty list check
        cout << "List is empty\n";
        return nullptr;
    }


    while (head) {
        if (head->data == value) break;

        if (!head->next) {
            cout << "Value not found\n";
            return nullptr;
        }
        head = head->next;
    }

    return head;
}



//**********************INSERT NODE AT THE SPECIFIED POSITION**********************

bool AddList(List* &head, int value, unsigned position) {

	struct List* temp = getItemByIndex(head, position);
	if (!temp){
        return false;
    }

	// Insert the new node
	List* newNode = new List;
	newNode->data = value;
	newNode->prev = temp->prev;
	newNode->next = temp;
	if (newNode->prev) newNode->prev->next = newNode;
	if (newNode->next) newNode->next->prev = newNode;
	if (position == 0) head = newNode;

	return true;
}

//**********************DELETE THE NODE WITH A SPECIFIED VALUE**********************
bool deleteItemByValue(struct List * &head, int value) {
    if (!head){               //Empty list check
        return false;
    }

    // Find the node
    struct List *temp = getItemByValue(head, value);
    if (!temp) return false;

    // Delete the node
    if ( temp->next != nullptr )
    {
        temp->next->prev = temp->prev;
    }

    if ( temp->prev != nullptr )
    {
        temp->prev->next = temp->next;
    }
    else
    {
        head = temp->next;
    }

    delete temp;
    return true;
}
//**********************DELETE THE NODE WITH A SPECIFIED INDEX**********************
bool deleteItemByIdx(struct List * &head, unsigned position) {
    if (!head) {            //Empty list check
        return false;
    }

    // Find the node
    struct List *temp = getItemByIndex(head, position);
    if (!temp) return false;

    // Delete the node
    if ( temp->next != nullptr )
    {
        temp->next->prev = temp->prev;
    }

    if ( temp->prev != nullptr )
    {
        temp->prev->next = temp->next;
    }
    else
    {
        head = temp->next;
    }

    delete temp;
    return true;
}

//**********************SWAP NODES BY SPECIFIED INDEXES**********************
bool swapByIdx(List*& head, unsigned x, unsigned y)
{

    // Edge Cases
    if (head == nullptr || head->next == nullptr
        || x == y)
        return false;
    if (x > y) swap(x, y);

    // Finding the Nodes

    List* Node1 = getItemByIndex(head, x);
    List* Node2 = getItemByIndex(head, y);

    // Swapping Node1 and Node2

    if (Node1 == head) head = Node2;

    List* temp;
    temp = Node1->next;
    Node1->next = Node2->next;
    Node2->next = temp;

    if (Node1->next != nullptr)
        Node1->next->prev = Node1;
    if (Node2->next != nullptr)
        Node2->next->prev = Node2;

    temp = Node1->prev;
    Node1->prev = Node2->prev;
    Node2->prev = temp;

    if (Node1->prev != nullptr) {
        Node1->prev->next = Node1;
    }
    if (Node2->prev != nullptr) {
        Node2->prev->next = Node2;
    }

    return true;
}

//**********************DISPLAY THE LIST**********************
void printList(List* head) {
    if (!head) {
        cout << "List is empty\n";
        return;
    }
    List *temp = head;

    // Iterate until node is NOT NULL
    while (temp) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}
//**********************IDZ #8**********************
struct List *remove_even(List *head)
{
    while (head && (head->data % 2) == 0)
    {
        auto *p = head;
        head = head->next;
        delete p;
    }
    if (!head)
        return nullptr;

    for (auto *p = head; p->next; )
        if ((p->next->data % 2) != 0)
            p = p->next;
        else
        {
            auto *p2 = p->next;
            p->next = p2->next;
            delete p2;
        }

    return head;
}







//************************MAIN MENU************************
int main()
{
    system("chcp 65001");

	struct List* head = nullptr;
	List* ptr = head;

	int x, length;
    unsigned position;
	while(true)
	{

        cout << "\nChoose a category from below:\n";
		cout << "(1). Create the list" << endl;
        cout << "(2). Display the list" << endl;
        cout << "(3). Insert new Node" << endl;
        cout << "(4). Delete the Node (index or value)" << endl;
        cout << "(5). Swap Nodes by indexes" << endl;
        cout << "(6). Get the element" << endl;
        cout << "(7). IDZ" << endl; //IDZ #9
		cout << "(0). Exit" << endl;
		cout << "\nAction > "; cin >> x;

        if (cin.fail() || cin.get() != '\n') {
            cout << "Bad entry. Enter a NUMBER:\n";
            cin.clear();
            cin.ignore(100000, '\n');
            continue;
        }

		switch (x) {
            case 0:{
                if(head) {
                    DeleteList(head);
                }
                return 0;
            }
            case 1: {
                cout << "Choose how to create the list:\n";
                cout << "   1. Fill with random numbers from 1 to 99\n";
                cout << "   2. Fill in manually\n> ";
                int key;
                cin >> key;
                if (key != 2 && key != 1) {
                    cout << "Invalid input\n";
                    continue;
                }
                if(key == 1) {
                    cout << "Enter size of list\n>>";
                    cin >> length;

                    auto start = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
                    head = createList(length);
                    if (!head) {
                        cout << "The list is empty.\n";
                        continue;
                    }
                    auto end = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
                    cout << setw(32) << setfill('-') << "Time"<< setw(32) << setfill('-') << '\n';
                    cout << "Duration of creating list: " << end - start << "ns";
                    cout << endl <<setw(64) << setfill('-') << '\n';
                }
                else {
                    cout << "Enter value (To stop enter 0):\n";

                    auto start = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
                    head = createListFromInput();

                    if (!head) {
                        cout << "The list is empty.\n";
                        continue;
                    }
                    auto end = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
                    cout << setw(32) << setfill('-') << "Time"<< setw(32) << setfill('-') << '\n';
                    cout << "Duration of creating list: " << end - start << "ns";
                    cout << endl <<setw(64) << setfill('-') << '\n';

                }
                break;
            }
            case 2: {
                cout << setw(32) << setfill('-') << "The List"<< setw(32) << setfill('-') << '\n';
                printList(head);
                cout << setw(64) << setfill('-') << '\n';
                break;
            }
            case 3: {
                if (!head) {
                    cout << "The list is empty.\n";
                    continue;
                }
                cout << "Enter the data: \n";
                int value;
                cout << "Value > ";
                cin >> value;
                cout << "Position > ";
                cin >> position;
                auto start = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
                if(!AddList(head, value, position)) {
                    continue;
                };
                auto end = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
                cout << setw(32) << setfill('-') << "Time"<< setw(32) << setfill('-') << '\n';
                cout << "Duration of inserting node: " << end - start << "ns";
                cout << endl <<setw(64) << setfill('-') << '\n';
                break;
            }
            case 4: {
                if (!head) {
                    cout << "List is empty\n";
                    continue;
                }

                cout << "Choose how to remove the node:\n";
                cout << "   1. Index\n";
                cout << "   2. Value\n> ";
                int input;
                cin >> input;
                if (input != 1 && input != 2) {
                    cout << "Invalid input\n";
                    continue;
                }

                if (input == 1) {
                    int index;
                    cout << "Enter index:\n> ";
                    cin >> index;

                    auto start = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
                    if(!deleteItemByIdx(head, index)){
                        continue;
                    };
                    auto end = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
                    cout << setw(32) << setfill('-') << "Time"<< setw(32) << setfill('-') << '\n';
                    cout << "Duration of deleting node: " << end - start << "ns";
                    cout << endl <<setw(64) << setfill('-') << '\n';

                }
                else {
                    int value;
                    cout << "Enter value:\n>> ";
                    cin >> value;

                    auto start = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
                    if(!deleteItemByValue(head, value)){
                        continue;
                    };
                    auto end = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
                    cout << setw(32) << setfill('-') << "Time"<< setw(32) << setfill('-') << '\n';
                    cout << "Duration of deleting node: " << end - start << "ns";
                    cout << endl <<setw(64) << setfill('-') << '\n';
                }

                break;
            }
            case 5: {
                if (!head) {
                    cout << "List is empty\n";
                    continue;
                }
                cout << "Select nodes to swap:\n";
                unsigned idx1, idx2;
                cout << "Index 1 > "; cin >> idx1;
                cout << "Index 2 > "; cin >> idx2;
                auto start = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
                if(!swapByIdx(head, idx1, idx2)){
                    continue;
                };
                auto end = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
                cout << setw(32) << setfill('-') << "Time"<< setw(32) << setfill('-') << '\n';
                cout << "Duration of swapping nodes: " << end - start << "ns";
                cout << endl <<setw(64) << setfill('-') << '\n';
                break;
            }
            case 6: {
                if (!head) {
                    cout << "List is empty\n";
                    continue;
                }

                cout << "Choose how to get the element:\n";
                cout << "   1. By index\n";
                cout << "   2. By value\n>> ";
                int input;
                cin >> input;
                if (input != 2 && input != 1) {
                    cout << "Invalid input\n";
                    continue;
                }

                if (input == 1) {
                    int index;
                    cout << "<< Enter index:\n>> ";
                    cin >> index;

                    auto start = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
                    List*temp = getItemByIndex(head, index);
                    auto end = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
                    if(temp == 0){
                        cout << "Item whit index ( " << index <<" ) ...  wasn't founded" << endl;
                    }
                    else {
                        cout << "Item whit index ( " << index << " ) =  " << temp->data << endl;
                        cout << setw(32) << setfill('-') << "Time" << setw(32) << setfill('-') << '\n';
                        cout << "Duration of getting item by index: " << end - start << "ns";
                        cout << endl << setw(64) << setfill('-') << '\n';
                    }

                }
                else {
                    int value;
                    cout << "<< Enter value:\n>> ";
                    cin >> value;

                    auto start = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
                    List *temp = getItemByValue(head, value);
                    auto end = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
                    if(temp == 0) {
                        cout << "Item whit value ( " << value <<" ) ...  wasn't founded" << endl;
                    }
                    else {
                        cout << "The address of the element with value (" << value << " ) =  " << temp << endl;
                        cout << setw(32) << setfill('-') << "Time" << setw(32) << setfill('-') << '\n';
                        cout << "Duration of getting item by value: " << end - start << "ns";
                        cout << endl << setw(64) << setfill('-') << '\n';
                    }
                }
                break;
                }
                case 7: {
                    cout << "Enter size of list and array\n>>";
                    cin >> length;
                    head = createList(length);
                    if (!head) {
                        cout << "The list is empty.\n";
                        continue;
                    }

                    cout << "BEFORE DELETING: \n";
                    cout << setw(32) << setfill('-') << "The List"<< setw(32) << setfill('-') << '\n';
                    printList(head);
                    cout << setw(64) << setfill('-') << '\n';

                    srand(time(nullptr));
                    vector<int> arr(length);
                    for (int i = 0; i < length; i++)
                    {
                        arr[i] = (rand() % 100);
                    }

                    cout << setw(32) << setfill('-') << "The Array"<< setw(32) << setfill('-') << '\n';
                    std::copy(arr.begin(), arr.end(), std::ostream_iterator<int>(std::cout, " "));
                    cout << endl << setw(64) << setfill('-') << '\n';

                    cout << endl << "AFTER DELETING: \n";
                    auto start = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
                    remove_even(head);
                    auto end = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
                    cout << setw(32) << setfill('-') << "The List"<< setw(32) << setfill('-') << '\n';
                    printList(head);
                    cout << endl << "The time: " << end - start << "ns" << endl ;
                    cout << setw(64) << setfill('-') << '\n';

                    auto start2 = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
                    arr.erase(std::remove_if(arr.begin(), arr.end(), [](const int& x) {
                        return x % 2 == 0;
                    }), arr.end());
                    auto end2 = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
                    // вывод содержимого вектора в std::cout
                    cout << setw(32) << setfill('-') << "The Array"<< setw(32) << setfill('-') << '\n';
                    std::copy(arr.begin(), arr.end(), std::ostream_iterator<int>(std::cout, " "));
                    cout << endl << endl << "The time: " << end2 - start2 << "ns";
                    cout << endl << setw(64) << setfill('-') << '\n';

                    DeleteList(head);
                    arr.clear();
                    break;

                }

            default:
                cout << "\nCategory with number " << x << " does not exist." << endl;
                break;
        }

	}
}