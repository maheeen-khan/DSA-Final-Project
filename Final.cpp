//Stack using Linked List.
//Implement MUlti Linked List

////////////////////////////////////     RESTAURANT     /////////////////////////////////////////

#include <iostream>
#include<stdlib.h>
#include <string>
#include<conio.h>
#include<stdio.h>
#include <cstring>

using namespace std;

// Node structure for the multi-linked list
struct Node {
    int item_id;
    char name[30];
    Node* next; 
    Node* down; 
};

	Node* head = NULL;
	
// Function to insert a new element into the multi-linked list
void insert(Node* &head, int value, const char n[]) {
	
    Node* newNode = (Node*) malloc(sizeof(Node));
    
    newNode->item_id = value;
    strcpy(newNode->name, n); // Copy the string properly
    
    newNode->next = NULL;
    newNode->down = NULL;

    if (head == NULL) {
        head = newNode;
        return;
    }
    Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// Function to find a node (parent) with a given value in the main linked list
Node* findNode(Node* head, int value) {
    Node* temp = head;
    while (temp != NULL) {
        if (temp->item_id == value) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

// Function to find a child node in the sublists
Node* findNodeInSublist(Node* head, int value) {
	
    Node* temp = head;
    
    while (temp != NULL) {
    	
        Node* subCurrent = temp->down;
        
        while (subCurrent != NULL) {
            if (subCurrent->item_id == value) {
                return subCurrent;
            }
            subCurrent = subCurrent->next;
        }
        temp = temp->next;
    }
    return NULL;
}



// Function to insert a new element into the sub-list of a node
void insertIntoSubList(Node* &head, int parentValue, int value, const char name[]) {
	
    Node* parent = findNode(head, parentValue);
    
    if (parent == NULL) {
        cout << "Parent node not found." << endl;
        return;
    }

    Node* newNode = (Node*) malloc(sizeof(Node));
    
    newNode->item_id = value;
    strcpy(newNode->name, name); // Copy the string properly
    
    newNode->next = NULL;
    newNode->down = NULL;

    if (parent->down == NULL) {
        parent->down = newNode;
    }
	else {
        Node* temp = parent->down;
        
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Function to display the multi-linked list
void display(Node* head) {
	
    Node* temp = head;
    
    cout<<"\n~~~~~~~~~~~~~~~~~~~~\n";
    cout<<"\tMENU\n";
    cout<<"~~~~~~~~~~~~~~~~~~~~\n\n";
    
    while (temp != NULL) {
    	
        cout << temp->item_id << " (" << temp->name << ") -> ";
        Node* downTemp = temp->down;
        
        while (downTemp != NULL) {
            cout << downTemp->item_id << " (" << downTemp->name << ") -> ";
            downTemp = downTemp->next;
        }
        cout << "NULL\n\n" << endl;
        temp = temp->next;
    }
}

// Function to delete a node from the multi-linked list
void deleteNode(Node*& head, int value) {
	
    // If the list is empty
    if (head == NULL) {
        return;
    }

    // If the node to be deleted is the head node
    if (head->item_id == value) {
        Node* temp = head;
        head = head->next; 
        delete temp; 
        return;
    }

    // Traverse the main list to find the node to be deleted
    Node* current = head;
    Node* prev = NULL;
    
    while (current != NULL && current->item_id != value) {
        prev = current;
        current = current->next;
    }

    // not found in main list
    if (current == NULL) {
        return;
    }

    //found in the main list, remove it
    prev->next = current->next;
    delete current;
}

// Function to delete a node from a sub-list
void deleteSubNode(Node*& head, int value) {
	
    if (head == NULL) {
        return;
    }

    Node* subListHead = head;
    while (subListHead != NULL) {
    	
        Node* subCurrent = subListHead->down;
        Node* subPrev = NULL;
        
        while (subCurrent != NULL && subCurrent->item_id != value) {
            subPrev = subCurrent;
            subCurrent = subCurrent->next;
        }

        if (subCurrent == NULL) { //its mean 1 sub list completed and toDelete value could not found.
            subListHead = subListHead->next; //move to next sub list  
            continue;						//repeat above process
        }

        if (subPrev == NULL) {
            subListHead->down = subCurrent->next; //means toDelete value is head -> next : node
        } else {
            subPrev->next = subCurrent->next;
        }

        delete subCurrent;
        return; // Node deleted, exit the function
    }
}

// Function to update the value of a node in the multi-linked list
void updateNode(Node* &head, int oldValue, int newValue, const char newName[]) {
	
    if (head == NULL) {
        return;
    }

    Node* current = head;
    
    while (current != NULL) {
        if (current->item_id == oldValue) {
            current->item_id = newValue;
            strcpy(current->name, newName); // Update the name as well
            return;
        }
        current = current->next;
    }
    
    //update inner node //if don't return at above , its mean toUpdate value can't be found.
    Node* subListHead = head;
    while (subListHead != NULL) {
    	
        Node* subCurrent = subListHead->down;
        while (subCurrent != NULL) {
        	
            if (subCurrent->item_id == oldValue) {
            	
                subCurrent->item_id = newValue;
                strcpy(subCurrent->name, newName); // Update the name as well
                return; // Node updated, exit the function
            }
            
            subCurrent = subCurrent->next;
        }
        subListHead = subListHead->next; //search at another sublist because not found in this sub list.
    }

    cout << "Node with the given value not found." << endl;

}





//////////////////////////////////////////////STACK/////////////////////////////////////////////////////

struct StackNode{
	
	Node* dish;
	StackNode* back;
	
};

struct Stack {
    StackNode* top;
};

StackNode* top = NULL;

//Push Function
void push(Stack* stack, Node* dish){
	
	StackNode* temp = (StackNode*) malloc(sizeof(StackNode));
	
    temp->dish = dish;
    temp->back = stack->top;
    stack->top = temp;

}

//Pop Function
Node* pop(Stack* stack) {
	
    if (stack->top == NULL) {
        return NULL; // its mean Stack is empty
    }
    StackNode* temp = stack->top;
    
    Node* dish = temp->dish;
    stack->top = temp->back;
    
    delete temp;
    return dish;
}

//Is empty Function 
void isEmpty(StackNode* top){
	
	cout<<"\n~~~~~~~~~~~~~~~~~";
	cout<<"\nCart";
	cout<<"\n~~~~~~~~~~~~~~~~~";
	
	if(top == NULL){
		cout<<"\n\nCart is Empty.";
	}
	else{
		cout<<"\n\nCart is not Empty!";
	}
}

//Print Stack
void printStack(StackNode* top) {
	
    if (top == NULL) {
        return;
    }

    cout << "\t" << top->dish->item_id << "    : " << top->dish->name << "\n";
    printStack(top->back);
}

//Order

string cus_name;
int count = 0;

void order(Node* head, Stack* orderStack) {
	
    if (head == NULL) {
        cout << "No dishes available." << endl;
        return;
    }

    int item_value;
    cout << "Available Dishes:" << endl;
    display(head); // Assuming display function prints the list of dishes

	cout<<"\n\nEnter your Name : ";
	cin>>cus_name;
	
    cout << "\nEnter the item ID of the dish you want to order (0 for exit): ";
    cin >> item_value;

    while (item_value != 0) {
    	
        Node* dish = findNode(head, item_value);
        
        if (dish != NULL) {
            
            push(orderStack, dish);
            cout << "\nDish added to your order." << endl;
            count++;
        } 
		else {
            dish = findNodeInSublist(head, item_value);
            
            if (dish != NULL) {
                push(orderStack,dish);
                cout << "\nDish added to your Cart." << endl;
                count++;
            }
			else {
                cout << "\nDish not found." << endl;
            }
        }

        cout << "\nEnter the item ID of the dish you want to order (0 for exit): ";
        cin >> item_value;
    }

    cout << "\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << "\t  Receipt\n";
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

    cout << "\n\tItems Quantity : " << count;

    cout << "\n\n\tName  : " << cus_name;

    cout << "\n\n\tItem ID : Item \n\n";

	printStack(orderStack->top); // Use printStack to print the receipt
	
    cout << "\n\n";
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
}

//Customer function

// Initialize the orderStack
Stack* orderStack = new Stack();


void customer(){
	
orderStack->top = NULL;
    
	int cus_choice;
	int order_add_remove;

    cout<<"\t\t\t\t\t\t\t ~~~~~~~~~~~~~~~~~~";	
	cout<<"\n\t\t\t\t\t\t\t Customer Interface\n";
    cout<<"\t\t\t\t\t\t\t ~~~~~~~~~~~~~~~~~~\n";
    
    cout<<"\n\t\t\t\t\t\t  Options available for CUSTOMER : \n\n";
    
    do {
        cout << "\t\t\t\t\t\t\t1 - View Menu Card\n";
        cout << "\t\t\t\t\t\t\t2 - Order\n";
        cout << "\t\t\t\t\t\t\t3 - Check Cart\n";
        cout << "\t\t\t\t\t\t\t4 - Exit from the CUSTOMER interface\n";
        
        cout << "\nEnter your choice : ";

        cin >> cus_choice;
        
        switch(cus_choice){
        	case 1:
        		display(head);
        		break;
        	case 2:
                order(head, orderStack);

                cout << "Do you want to remove items from order? Press 1 otherwise 0 : ";
                cin >> order_add_remove;

                if (order_add_remove == 1) {
                    Node* poppedDish = pop(orderStack);
                    
                    if (poppedDish != NULL) {
                        cout << "Dish removed from your order: " << poppedDish->item_id << " (" << poppedDish->name << ")\n";
                        delete poppedDish; // Free the memory of the popped dish
                    }
					else {
                        cout << "Order is empty.\n";
                    }
                }
                break;
        	case 3:
        		isEmpty(orderStack->top);
				break;
			case 4:
				cout<<"\nEXIT";	
				break;
			default :
				cout<<"\nInvalid Choice";
		}
        
	}while(cus_choice != 4);
	
}

//admin function

void admin(){
	
			int admin_choice;
			int parentValue;
			int value;
			char name[30];
		
			cout<<"\t\t\t\t\t\t\t ~~~~~~~~~~~~~~~\n";
    		cout<<"\t\t\t\t\t\t\t Admin Interface\n";
    		cout<<"\t\t\t\t\t\t\t ~~~~~~~~~~~~~~~\n";
    
    		cout<<"\n\t\t\t\t\t\t  Options available for ADMIN : \n\n";
    
			do {
        		cout << "\t\t\t\t\t\t\t1 - Add food section\n";
        		cout << "\t\t\t\t\t\t\t2 - Add a dish (insertIntoSubList)\n";
        		cout << "\t\t\t\t\t\t\t3 - View Menu Card\n";
        		cout << "\t\t\t\t\t\t\t4 - Remove food section\n";
        		cout << "\t\t\t\t\t\t\t5 - Remove a dish (delete Sub Node)\n";
        		cout << "\t\t\t\t\t\t\t6 - Update dish\n";
        //		cout << "\t\t\t\t\t\t\t7 - update Inner Node\n";
        //		cout << "\t\t\t\t\t\t\t8 - Order\n\n";
        		
        		cout << "\t\t\t\t\t\t\t7 - Switch to Customer Interface\n";
        		cout << "\t\t\t\t\t\t\t8 - Exit from ADMIN interface\n";
        		cout << "\nEnter your choice : ";

       			cin >> admin_choice;
       			switch (admin_choice) {
            		case 1:
                		cout << "\nEnter ID to insert : ";
                		cin >> value;
                		cout << "Enter name to insert : ";
                		cin >> name;
                		insert(head, value, name);
                		break;
            		case 2:
                		cout << "Enter parent ID : ";
                		cin >> parentValue;
                		cout << "Enter ID to insert into sublist : ";
                		cin >> value;
                		cout << "Enter name to insert : ";
                		cin >> name;
                		insertIntoSubList(head, parentValue, value, name);
                		break;
            		case 3:
                		display(head);
                		break;
            		case 4:
                		cout << "Enter ID to delete : ";
                		cin >> value;
                		deleteNode(head, value);
                		break;
            		case 5:
                		cout << "Enter ID to delete subnode : ";
                		cin >> value;
                		deleteSubNode(head, value);
                		break;
            		case 6:
                		int oldValue, newValue;
                		cout << "Enter old ID to update : ";
                		cin >> oldValue;
                		cout << "Enter new ID : ";
                		cin >> newValue;
                
                		cout << "Enter name to insert : ";
                		cin >> name;
                
                		updateNode(head, oldValue, newValue, name);
                		break;
  /*          		case 7:
                		int old_value, new_value;
                		cout << "Enter old value to update at sub list : ";
                		cin >> oldValue;
               			cout << "Enter new value : ";
                		cin >> newValue;
                
						cout << "Enter name to insert : ";
                		cin >> name;
                
                		updateNode(head, oldValue, newValue, name);
                		break;
    */            		
             		case 7:
            			customer();
            			break;
            		case 8:
                		cout << "EXIT" << endl;
                		break;


           			default:
                		cout << "Invalid choice" << endl;
        }
    } while (admin_choice != 8);
    
	
}
//Main function
int main(){
	
//	Stack* orderStack = NULL; //orderrrrr
	
//	Node* head = NULL;
//    int value;
//    int choice;
//   int parentValue;
 //   char name[30];
    
    int main_choice;

	//Preparing Menu List
	
	insert(head, 99, "Fries");
	insert(head, 88, "Burger");
	insert(head, 77, "Biryani");
	insert(head, 66, "Cakes");
	
	insertIntoSubList(head, 99, 9, "Steak_Fries");
	insertIntoSubList(head, 99, 8, "Curly_Fries");
	insertIntoSubList(head, 99, 7, "Crispy_Fries");
	
	insertIntoSubList(head, 88, 6, "Hamburger");
	insertIntoSubList(head, 88, 5, "Cheese_Burger");
	insertIntoSubList(head, 88, 4, "Beef_Burger");
	
	insertIntoSubList(head, 77, 3, "Beef_Biryani");
	insertIntoSubList(head, 77, 2, "Chicken-Biryani");
	insertIntoSubList(head, 77, 1, "Sindhi_Biryani");
	
	insertIntoSubList(head, 66, 64, "Butter_Cake");
	insertIntoSubList(head, 66, 63, "Sponge_Cake");
	insertIntoSubList(head, 66, 62, "Chocolate_Cake");
	
	

	cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
	cout<<"\t\t\t\t\t\t\t   RESTAURANT\n\n";
	cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
    
    cout<<"\n\nEnter your role : \n\n";
    cout<<"1 - For Customer Interface\n";
    cout<<"2 - For Admin Interface\n";
    cout<<"3 - Exit\n";
    
    cout<<"\nEnter choice : \n";
    cin>>main_choice;
    
    switch(main_choice){
    	
    	case 1: 
    		customer();
    		break;
    		
    	case 2:
    		admin();
    		break;
    
    //end of admin interface (case 2)
    	
    	case 3: 
    		cout<<"\nEXIT\n";
    		break;
    		
    	default:
			cout<<"\nInvalid choice";	
    	
	}


    return 0;

	
}
