#include <iostream>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

class AuthSystem {
private:
    fstream file;
    const string fileName = "loginData.txt";

public:
    void signUp();
    void login();
    void forgotPassword();
};

int main() {
    AuthSystem auth;
    char choice;

    while (true) {
        cout << "\n===== AUTH SYSTEM =====";
        cout << "\n1 - Login";
        cout << "\n2 - Sign Up";
        cout << "\n3 - Forgot Password";
        cout << "\n4 - Exit";
        cout << "\nEnter your choice: ";

        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
        case '1':
            auth.login();
            break;
        case '2':
            auth.signUp();
            break;
        case '3':
            auth.forgotPassword();
            break;
        case '4':
            cout << "\nExiting program...\n";
            return 0;
        default:
            cout << "\nInvalid choice. Try again.\n";
        }
    }
}

void AuthSystem::signUp() {
    string userName, email, password;
    string storedUser, storedEmail, storedPass;
    bool exists = false;

    cout << "\n----- SIGN UP -----";
    cout << "\nEnter Username: ";
    getline(cin, userName);

    cout << "Enter Email: ";
    getline(cin, email);

    cout << "Enter Password: ";
    getline(cin, password);

    // Check if username already exists
    file.open(fileName, ios::in);
    while (getline(file, storedUser, '*') &&
           getline(file, storedEmail, '*') &&
           getline(file, storedPass)) {
        if (storedUser == userName) {
            exists = true;
            break;
        }
    }
    file.close();

    if (exists) {
        cout << "\nUsername already exists. Try a different one.\n";
        return;
    }

    // Save new user
    file.open(fileName, ios::out | ios::app);
    file << userName << "*" << email << "*" << password << endl;
    file.close();

    cout << "\nAccount created successfully!\n";
}

void AuthSystem::login() {
    string searchUser, searchPass;
    string userName, email, password;
    bool found = false;

    cout << "\n----- LOGIN -----";
    cout << "\nEnter Username: ";
    getline(cin, searchUser);

    cout << "Enter Password: ";
    getline(cin, searchPass);

    file.open(fileName, ios::in);

    while (getline(file, userName, '*') &&
           getline(file, email, '*') &&
           getline(file, password)) {

        if (userName == searchUser && password == searchPass) {
            cout << "\nLogin successful!";
            cout << "\nUsername: " << userName;
            cout << "\nEmail: " << email << endl;
            found = true;
            break;
        }
    }

    file.close();

    if (!found) {
        cout << "\nInvalid username or password.\n";
    }
}

void AuthSystem::forgotPassword() {
    string searchUser, searchEmail;
    string userName, email, password;
    bool found = false;

    cout << "\n----- FORGOT PASSWORD -----";
    cout << "\nEnter Username: ";
    getline(cin, searchUser);

    cout << "Enter Email: ";
    getline(cin, searchEmail);

    file.open(fileName, ios::in);

    while (getline(file, userName, '*') &&
           getline(file, email, '*') &&
           getline(file, password)) {

        if (userName == searchUser && email == searchEmail) {
            cout << "\nAccount verified.";
            cout << "\nYour password is: " << password << endl;
            found = true;
            break;
        }
    }

    file.close();

    if (!found) {
        cout << "\nAccount not found.\n";
    }
}
