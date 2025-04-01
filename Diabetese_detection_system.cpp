#include <iostream>
#include <string>
using namespace std;

struct Patient {
    string name;
    int age;
    float glucose;
    float bmi;
    float bloodPressure;
    string riskLevel;
    Patient* left;
    Patient* right;

    Patient(string n, int a, float g, float b, float bp, string r)
        : name(n), age(a), glucose(g), bmi(b), bloodPressure(bp), riskLevel(r), left(nullptr), right(nullptr) {}
};

class DiabetesDetectionSystem {
private:
    Patient* root;

    Patient* insert(Patient* node, string name, int age, float glucose, float bmi, float bp, string riskLevel) {
        if (node == nullptr)
            return new Patient(name, age, glucose, bmi, bp, riskLevel);

        if (glucose < node->glucose)
            node->left = insert(node->left, name, age, glucose, bmi, bp, riskLevel);
        else
            node->right = insert(node->right, name, age, glucose, bmi, bp, riskLevel);

        return node;
    }

    void inorder(Patient* node) {
        if (node != nullptr) {
            inorder(node->left);
            cout << "Name: " << node->name << " | Age: " << node->age << " | Glucose: " << node->glucose
                 << " | BMI: " << node->bmi << " | Blood Pressure: " << node->bloodPressure
                 << " | Risk Level: " << node->riskLevel << endl;
            inorder(node->right);
        }
    }

    Patient* search(Patient* node, float glucose) {
        if (node == nullptr || node->glucose == glucose)
            return node;
        if (glucose < node->glucose)
            return search(node->left, glucose);
        return search(node->right, glucose);
    }

public:
    DiabetesDetectionSystem() : root(nullptr) {}
    void addPatient(string name, int age, float glucose, float bmi, float bp) {
        string riskLevel = "Low";
        if (glucose > 140 || bmi > 30 || bp > 130) 
            riskLevel = "High";
        else if (glucose > 100 || bmi > 25 || bp > 120)
            riskLevel = "Moderate";

        root = insert(root, name, age, glucose, bmi, bp, riskLevel);
    }
    void displayPatients() {
        if (root == nullptr) {
            cout << "No patient records available." << endl;
            return;
        }
        inorder(root);
    }
    void searchPatient(float glucose) {
        Patient* result = search(root, glucose);
        if (result)
            cout << "Patient Found: " << result->name << " | Risk Level: " << result->riskLevel << endl;
        else
            cout << "No patient found with glucose level " << glucose << endl;
    }
};
int main() {
    DiabetesDetectionSystem system;
    int choice;
    do {
        cout << "\nDiabetes Detection System" << endl;
        cout << "1. Add Patient" << endl;
        cout << "2. Display Patients" << endl;
        cout << "3. Search Patient by Glucose Level" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        
        if (choice == 1) {
            string name;
            int age;
            float glucose, bmi, bp;
            cout << "Enter Name: ";
            cin >> name;
            cout << "Enter Age: ";
            cin >> age;
            cout << "Enter Glucose Level: ";
            cin >> glucose;
            cout << "Enter BMI: ";
            cin >> bmi;
            cout << "Enter Blood Pressure: ";
            cin >> bp;
            system.addPatient(name, age, glucose, bmi, bp);
        } else if (choice == 2) {
            system.displayPatients();
        } else if (choice == 3) {
            float glucose;
            cout << "Enter Glucose Level to Search: ";
            cin >> glucose;
            system.searchPatient(glucose);
        }
    } while (choice != 4);
    return 0;
}
