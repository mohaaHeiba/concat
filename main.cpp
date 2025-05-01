#include <iostream>
#include <string>

using namespace std;

class Contact {
public:
    string name;
    string phone_number;
    string email;

    Contact() {}
    Contact(string name, string phone_number, string email) {
        this->name = name;
        this->phone_number = phone_number;
        this->email = email;
    }
};

class Node {
public:
    Contact contact;
    Node* next;

    Node(Contact contact) : contact(contact), next(nullptr) {}
};

class ContactManager {
private:
    Node* stack_top;

public:
    ContactManager() : stack_top(nullptr) {}

    ~ContactManager() {
        while (stack_top != nullptr) {
            Node* temp = stack_top;
            stack_top = stack_top->next;
            delete temp;
        }
    }

    void addContact(string name, string phone_number, string email) {
        Contact newContact(name, phone_number, email);
        Node* newNode = new Node(newContact);

        newNode->next = stack_top;
        stack_top = newNode;

        cout << "Contact added successfully: " << name << " (" << phone_number << ", " << email << ")" << endl;
    }

    void searchContact(string search_query) {
        bool found = false;
        cout << "Search result for \"" << search_query << "\":" << endl;
        Node* current = stack_top;

        while (current != nullptr) {
            if (current->contact.name.find(search_query) != string::npos) {
                cout << "Contact found: " << current->contact.name << " (" << current->contact.phone_number << ", " << current->contact.email << ")" << endl;
                found = true;
            }
            current = current->next;
        }

        if (!found) {
            cout << "No matching contacts found." << endl;
        }
    }

    void deleteContact(string name) {
        Node* current = stack_top;
        Node* previous = nullptr;
        bool found = false;

        while (current != nullptr) {
            if (current->contact.name == name) {
                if (previous == nullptr) {
                    stack_top = current->next;
                } else {
                    previous->next = current->next;
                }

                delete current;
                cout << "Contact deleted successfully: " << name << endl;
                found = true;
                break;
            }

            previous = current;
            current = current->next;
        }

        if (!found) {
            cout << "Contact not found." << endl;
        }
    }
};

int main() {
    ContactManager contactManager;
    int choice;
    string name, phone_number, email, search_query;

    while (true) {
        cout << "\nContact Manager Menu:\n";
        cout << "1. Add Contact\n";
        cout << "2. Search Contact\n";
        cout << "3. Delete Contact\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter phone number: ";
                getline(cin, phone_number);
                cout << "Enter email: ";
                getline(cin, email);
                contactManager.addContact(name, phone_number, email);
                break;

            case 2:
                cout << "Enter name to search: ";
                cin.ignore();
                getline(cin, search_query);
                contactManager.searchContact(search_query);
                break;

            case 3:
                cout << "Enter name to delete: ";
                cin.ignore();
                getline(cin, name);
                contactManager.deleteContact(name);
                break;

            case 4:
                cout << "Exiting the program.\n";
                return 0;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
