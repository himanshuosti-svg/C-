#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class Contact {
private:
    string name, phone, email, address;

public:
    Contact(string n="", string p="", string e="", string a="") {
        name = n; phone = p; email = e; address = a;
    }

    string getName() { return name; }
    string getPhone() { return phone; }
    string getEmail() { return email; }
    string getAddress() { return address; }

    void display() {
        cout << "Name: " << name
             << "\nPhone: " << phone
             << "\nEmail: " << email
             << "\nAddress: " << address << endl;
    }

    // Save contact in file
    void saveToFile(ofstream &out) {
        out << name << "|" << phone << "|" << email << "|" << address << "\n";
    }

    // Load contact from file line
    static Contact fromString(string line) {
        string n, p, e, a;
        size_t pos = 0;

        pos = line.find("|"); n = line.substr(0, pos); line.erase(0, pos+1);
        pos = line.find("|"); p = line.substr(0, pos); line.erase(0, pos+1);
        pos = line.find("|"); e = line.substr(0, pos); line.erase(0, pos+1);
        a = line;
        return Contact(n, p, e, a);
    }
};

class PhoneDiary {
private:
    vector<Contact> contacts;
    string filename = "contacts.txt";

public:
    PhoneDiary() { loadFromFile(); }
    ~PhoneDiary() { saveToFile(); }

    void addContact(Contact c) {
        contacts.push_back(c);
        saveToFile();
    }

    void viewContacts() {
        if (contacts.empty()) {
            cout << "No contacts saved yet!\n";
            return;
        }
        for (size_t i = 0; i < contacts.size(); i++) {
            cout << "\nContact " << i+1 << ":\n";
            contacts[i].display();
        }
    }

    void searchContact(string name) {
        bool found = false;
        for (auto &c : contacts) {
            if (c.getName() == name) {
                c.display();
                found = true;
                break;
            }
        }
        if (!found) cout << "Contact not found!" << endl;
    }

    void deleteContact(string name) {
        for (size_t i = 0; i < contacts.size(); i++) {
            if (contacts[i].getName() == name) {
                contacts.erase(contacts.begin() + i);
                cout << "Contact deleted.\n";
                saveToFile();
                return;
            }
        }
        cout << "Contact not found!\n";
    }

    void saveToFile() {
        ofstream out(filename);
        for (auto &c : contacts) {
            c.saveToFile(out);
        }
        out.close();
    }

    void loadFromFile() {
        ifstream in(filename);
        string line;
        while (getline(in, line)) {
            if (!line.empty()) {
                contacts.push_back(Contact::fromString(line));
            }
        }
        in.close();
    }
};

int main() {
    PhoneDiary diary;
    int choice;
    string name, phone, email, address;

    do {
        cout << "\n--- PHONE DIARY ---";
        cout << "\n1. Add Contact\n2. View All\n3. Search\n4. Delete\n5. Exit\nChoice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            cout << "Enter Name: "; getline(cin, name);
            cout << "Enter Phone: "; getline(cin, phone);
            cout << "Enter Email: "; getline(cin, email);
            cout << "Enter Address: "; getline(cin, address);
            Contact c(name, phone, email, address);
            diary.addContact(c);
        } else if (choice == 2) {
            diary.viewContacts();
        } else if (choice == 3) {
            cout << "Enter Name to Search: "; getline(cin, name);
            diary.searchContact(name);
        } else if (choice == 4) {
            cout << "Enter Name to Delete: "; getline(cin, name);
            diary.deleteContact(name);
        }

    } while (choice != 5);

    return 0;
}
