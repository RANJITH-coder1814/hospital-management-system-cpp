#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

class Patient {
public:
    int id;
    char name[50];
    int age;
    char disease[50];

    void add() {
        cout << "Enter Patient ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Name: ";
        cin.getline(name, 50);
        cout << "Enter Age: ";
        cin >> age;
        cin.ignore();
        cout << "Enter Disease: ";
        cin.getline(disease, 50);
    }

    void display() {
        cout << setw(5) << id
             << setw(15) << name
             << setw(10) << age
             << setw(20) << disease << endl;
    }
};

void addPatient() {
    Patient p;
    ofstream file("patients.dat", ios::binary | ios::app);
    p.add();
    file.write((char*)&p, sizeof(p));
    file.close();
    cout << "Patient added successfully!\n";
}

void viewPatients() {
    Patient p;
    ifstream file("patients.dat", ios::binary);
    cout << "\nID   Name           Age     Disease\n";
    cout << "------------------------------------------\n";
    while (file.read((char*)&p, sizeof(p))) {
        p.display();
    }
    file.close();
}

void searchPatient() {
    int id;
    Patient p;
    bool found = false;
    cout << "Enter Patient ID to search: ";
    cin >> id;

    ifstream file("patients.dat", ios::binary);
    while (file.read((char*)&p, sizeof(p))) {
        if (p.id == id) {
            cout << "\nPatient Found:\n";
            cout << "ID: " << p.id << "\nName: " << p.name
                 << "\nAge: " << p.age
                 << "\nDisease: " << p.disease << endl;
            found = true;
            break;
        }
    }
    file.close();
    if (!found) cout << "Patient not found!\n";
}

int main() {
    int choice;
    do {
        cout << "\n==============================";
        cout << "\n   HOSPITAL MANAGEMENT SYSTEM";
        cout << "\n==============================";
        cout << "\n1. Add Patient";
        cout << "\n2. View Patients";
        cout << "\n3. Search Patient";
        cout << "\n4. Exit";
        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: addPatient(); break;
        case 2: viewPatients(); break;
        case 3: searchPatient(); break;
        case 4: cout << "Exiting system...\n"; break;
        default: cout << "Invalid choice!\n";
        }
    } while (choice != 4);

    return 0;
}
