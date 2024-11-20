#include <iostream>
#include <fstream>
using namespace std;

void clearInput()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int logInOrSignUpMenu()
{
    int authChoice;
    do
    {
        cout << "\n\n\t\t\t  USER AUTHENTICATION\n";
        cout << "1. Log in\n";
        cout << "2. Sign Up\n";
        cout << "Enter (1/2): ";
        cin >> authChoice;
        if (cin.fail() || authChoice < 1 || authChoice > 2)
        {
            cout << "\nPlease enter again...\n\n";
            clearInput();
        }
        else
        {
            break;
        }
    } while (1);
    return authChoice;
}

int logIn()
{
    string contents, email, passWord;
    int int_personalID;
    int foundEmail = 1;
    int foundPass = 1;
    int isGoingBack = 2;
    cout << "\n\n\t\t\t       LOGGING IN\n\n";
    int i = 0;
    do
    {
        if (i > 1)
        {
            do
            {
                cout << "Do you want to sign up instead?\n";
                cout << "1. Yes\n";
                cout << "2. No\n";
                cout << "(1/2) : ";
                cin >> isGoingBack;
                if (cin.fail() || isGoingBack < 1 || isGoingBack > 2)
                {
                    clearInput();
                    cout << "\nPlease enter again...\n\n";
                }
                else
                {
                    break;
                }
            } while (1);
        }
        ifstream readContents("Info.txt"); // the need to open the file is so that the pointer position in the file is reset
        if (!readContents.is_open())
        {
            cerr << "Error opening Info.txt";
        }
        if (isGoingBack == 2) // not going back
        {
            cout << "EMAIL: ";
            cin >> email;
            while (getline(readContents, contents))
            {
                if (contents == "# User Section")
                {
                    getline(readContents, contents);
                    foundEmail = 1;
                    if (contents == email)
                    {
                        foundEmail = 0;
                        break;
                    }
                }
            }
            if (foundEmail == 1)
            {
                cout << "\nPlease enter a valid Email...\n\n";
                i++; // if wrong more than 2 times then ask if they wanna sign up instead
            }
            else
            {
                break; // foundEmail == 0
            }
        }
        else // is going back
        {
            isGoingBack = 1;
            return 0;
        }
        readContents.close();
    } while (1);
    if (isGoingBack == 2 && foundEmail == 0) // not going back and email was found
    {
        do
        {
            cout << "PASSWORD: ";
            cin >> passWord;
            ifstream readContents("Info.txt");
            if (!readContents.is_open())
            {
                cerr << "Error opening Info.txt";
            }
            while (getline(readContents, contents))
            {
                foundPass = 1;
                if (contents == email)
                {
                    getline(readContents, contents); // read the line after email
                    if (contents == passWord)
                    {
                        foundPass = 0;
                        break;
                    }
                }
            }
            if (foundPass == 1)
            {
                cout << "\nPlease enter the correct password...\n\n";
            }
            else
            {
                cout << "\nSuccessfully logged in, proceeding to service selection menu...\n\n";
                break;
            }
            readContents.close();
        } while (1);
    }

    string contentCheck;
    ifstream readCredentials("Info.txt");
    if (!readCredentials.is_open())
    {
        cerr << "Error opening file\n";
    }

    while (getline(readCredentials, contentCheck))
    {
        if (contentCheck == "# User Section")
        {
            getline(readCredentials, contentCheck);
            if (contentCheck == email)
            {
                getline(readCredentials, contentCheck);
                if (contentCheck == passWord)
                {
                    getline(readCredentials, contentCheck);
                    int_personalID = stoi(contentCheck);
                    break;
                }
            }
        }
    }
    readCredentials.close();

    return int_personalID;
}

int signUp()
{
    string email, passWord1, passWord2, contents;
    int isEmailTaken = 1;
    int isGoingBack = 2;

    cout << "\n\n\t\t\t CREATING ACCOUNT\n\n";
    int i = 0;

    do
    {
        if (i > 1)
        {
            do
            {
                cout << "Do you want to log in instead?\n";
                cout << "1. Yes\n";
                cout << "2. No\n";
                cout << "(1/2) : ";
                cin >> isGoingBack;
                if (cin.fail() || isGoingBack < 1 || isGoingBack > 2)
                {
                    clearInput();
                    cout << "\nPlease enter again...\n\n";
                }
                else
                {
                    break;
                }
            } while (1);
        }

        if (isGoingBack == 2)
        {
            cout << "ENTER EMAIL: ";
            cin >> email;
            ifstream readCredentials("Info.txt");
            isEmailTaken = 1;
            while (getline(readCredentials, contents))
            {
                if (contents == email)
                {
                    cout << "\nEmail is already taken, please select log in or use another email...\n\n";
                    isEmailTaken = 0;
                    i++;
                    break;
                }
            }
            readCredentials.close();
        }
        else
        {
            isGoingBack = 1;
            return 0;
        }

        if (isEmailTaken == 1)
        {
            break;
        }
    } while (1);

    if (isGoingBack == 2 && isEmailTaken == 1)
    {
        do
        {
            cout << "ENTER PASSWORD: ";
            cin >> passWord1;
            cout << "RE-ENTER PASSWORD: ";
            cin >> passWord2;
            if (passWord1 != passWord2)
            {
                cout << "\nPlease confirm your password correctly...\n\n";
            }
            else
            {
                break;
            }
        } while (1);
        cout << "\nAccount successfully created, Proceeding to service selection menu...\n\n";
    }

    int highestID = 0;
    ifstream readCredentials("Info.txt");

    if (!readCredentials.is_open())
    {
        cerr << "Error opening file\n";
    }

    while (getline(readCredentials, contents))
    {
        if (contents == "# User Section")
        {
            getline(readCredentials, contents); // Skip email
            getline(readCredentials, contents); // Skip password
            getline(readCredentials, contents); // Read ID
            int currentID = stoi(contents);
            if (currentID > highestID)
            {
                highestID = currentID;
            }
        }
    }
    readCredentials.close();
    int newID = highestID + 1;
    ofstream writeCredentials("Info.txt", ios::app);
    writeCredentials << "\n# User Section\n";
    writeCredentials << email << "\n"
                     << passWord1 << "\n"
                     << newID << "\n";
    writeCredentials.close();

    return newID;
}

int startMenu()
{
    int service;
    do
    {
        cout << "\n\n\t\t\t    SERVICE SELECTION\n\n";
        cout << "0. Exit Program\n";
        cout << "1. Booking\n";
        cout << "2. Refund\n";
        cout << "Enter service (1/2): ";
        cin >> service;
        if (cin.fail() || service < 0 || service > 2)
        {
            cout << "\nPlease enter again...\n\n";
            clearInput();
        }
        else
        {
            break;
        }
    } while (1);
    return service;
}

void printBusManagementSystem()
{
    cout << "\n\n\n\n";
    cout << "                     ____  _   _ ____   \n"
            "                    | __ )| | | / ___|  \n"
            "                    |  _ \\| | | \\___ \\  \n"
            "                    | |_) | |_| |___) | \n"
            "                    |____/ \\___/|____/  \n"
         << endl;
    cout << " ____  _____ ____  _____ ______     ___  _____ ___ ___  _   _ \n"
            "|  _ \\| ____/ ___|| ____|  _ \\ \\   / / \\|_   _|_ _/ _ \\| \\ | |\n"
            "| |_) |  _| \\___ \\|  _| | |_) \\ \\ / / _ \\ | |  | | | | |  \\| |\n"
            "|  _ <| |___ ___) | |___|  _ < \\ V / ___ \\| |  | | |_| | |\\  |\n"
            "|_| \\_\\_____|____/|_____|_| \\_\\ \\_/_/   \\_\\_| |___\\___/|_| \\_|\n"
         << endl;
    cout << "            ______   ______ _____ _____ __  __ \n"
            "           / ___\\ \\ / / ___|_   _| ____|  \\/  |\n"
            "           \\___ \\ V /\\___ \\ | | |  _| | |\\/| |\n"
            "            ___) || |  ___) || | | |___| |  | |\n"
            "           |____/ |_| |____/ |_| |_____|_|  |_|\n"
         << endl;
}
