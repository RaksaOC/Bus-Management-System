#include <iostream>
using namespace std;

void clearInput()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// int logInOrSignUp()
// {
//     int authChoice;
//     do
//     {
//         cout << "\n\n\t\t\t  USER AUTHENTICATION\n";
//         cout << "1. Log in\n";
//         cout << "2. Sign Up\n";
//         cout << "Enter (1/2): ";
//         cin >> authChoice;
//         if (cin.fail() || authChoice < 1 || authChoice > 2)
//         {
//             cout << "\nPlease enter again...\n\n";
//             clearInput();
//         }
//         else
//         {
//             break;
//         }
//     } while (1);
//     return authChoice;
// }



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
