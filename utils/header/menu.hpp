#ifndef MENU_hpp
#define MENU_hpp

#include <iostream>
#include <fstream>
#include<limits>

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
        if (cin.fail() ||  authChoice < 1  ||authChoice > 2)
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

int serviceMenu()
{
    int service;
    do
    {
        cout << "\n\n\t\t\t    SERVICE SELECTION\n\n";
        cout << "0. Exit Program\n";
        cout << "1. Booking\n";
        cout << "2. Refund\n";
        cout << "3. View History\n> ";
        cin >> service;
        if (cin.fail() || service < 0 || service > 3)
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

int bookingTypeMenu() // choose single or bulk booking
{
    int typeOfBooking;
    do
    {
        cout << "\n\n\t\t\t    BOOKING TYPE\n\n";
        cout << "0. Back to bus type selection menu\n";
        cout << "1. Book one ticket\n";
        cout << "2. Book multiple tickets\n";
        cout << "Enter your desired booking (1/2): ";
        cin >> typeOfBooking;
        if (cin.fail() || typeOfBooking < 0 || typeOfBooking > 2)
        {
            clearInput();
            cout << "\nPlease enter again...\n\n";
        }
        else
        {
            break;
        }
    } while (1);
    return typeOfBooking;
}

int adminActionsMenu()
{
    int choice;
    do
    {
        cout << "\n\t\t\tADMIN ACTIONS\n\n";
        cout << "0. Back\n";
        cout << "1. Add Admin\n";
        cout << "2. Add Bus\n";
        cout << "3. Change Bus Settings\n";
        cout << "4. See all Users\n";
        cout << "Enter your choice: ";
        cin >> choice;
        if (cin.fail() || choice < 0 || choice > 4)
        {
            clearInput();
            cout << "\nPlease enter again...\n\n";
        }
        else
        {
            break;
        }
    } while (1);
    return choice;
}

void printBusManagementSystem()
{
    cout << "\n\n\n\n";
    cout << "                     __  _   _ __   \n"
            "                    | __ )| | | / ___|  \n"
            "                    |  _ \\| | | \\___ \\  \n"
            "                    | |_) | |_| |___) | \n"
            "                    |____/ \\___/|____/  \n"
         << endl;
    cout << " __  ___ __  ___ __     _  ___ _ _  _   _ \n"
            "|  _ \\| ____/ ___|| ____|  _ \\ \\   / / \\|_   _|_ _/ _ \\| \\ | |\n"
            "| |_) |  _| \\___ \\|  _| | |_) \\ \\ / / _ \\ | |  | | | | |  \\| |\n"
            "|  _ <| |___ _) | |___|  _ < \\ V / _ \\| |  | | |_| | |\\  |\n"
            "|_| \\_\\_____|____/|_____|_| \\_\\ \\_/_/   \\_\\_| |___\\___/|_| \\_|\n"
         << endl;
    cout << "            __   __ _ _    \n"
            "           / ___\\ \\ / / ___|_   _| ____|  \\/  |\n"
            "           \\___ \\ V /\\___ \\ | | |  _| | |\\/| |\n"
            "            ___)  |  ___)  | | |___| |  | |\n"
            "           |____/ |_| |____/ |_| |_____|_|  |_|\n"
         << endl;
}
void printStandardBus()
{
    cout << " _________________________________\n"
            "|,----.,----.,----.,----.,----.,--.\\\n"
            "||                    ||   \\\\\n"
            "|`----'`----'`----'`----'`----||----`.\\\n"
            "[                       |   - ||- __||( |\n"
            "[  ,--.                 |____ ||.--.  ||\n"
            "=-(( `))---------------------(( `))==\n"
            "   `--'                       `--'  \n"
         << endl;
}
void printLuxaryBus()
{
    cout << "                         __\n"
            " .-----------------------'  |\n"
            "/| _ .---. .---. .---. .---.|\n"
            "|j||||___| |___| |___| |___||\n"
            "|=|||=======================|\n"
            "[_|j||(O)\\__________||(O)__]"
         << endl;
}
void printDoubleDeckerBus()
{
    cout << "   .---------------------------.\n"
            "  /,--..---..---..---..---..--. `.\n"
            " //___||___||___||___||___||___\\_|\n"
            "[j__ ######################## [_|\n"
            "   \\============================|\n"
            " .==|  |\"\"\"||\"\"\"||\"\"\"||\"\"\"| |\"\"\"||\n"
            "/=====\"---\"---\"---\"---\"=|  =||\n"
            "|____    []*          ____  | ==||\n"
            "   //  \\\\               //  \\\\ |===||\n"
            "   \"\\__/\"---------------\"\\__/-+---+'\n"
         << endl;
}

void printThanks()
{
    cout << "\n\n";
    cout << "    _ _   _    _    _   _ _      _  _   _ \n"
            "   |_   _| | | |  / \\  | \\ | | |/ / \\ \\ / / _ \\| | | |\n"
            "     | | | |_| | / _ \\ |  \\| | ' /   \\ V / | | | | | |\n"
            "     | | |  _  |/ ___ \\| |\\  | . \\    | || |_| | |_| |\n"
            "     |_| |_| |_/_/   \\_\\_| \\_|_|\\_\\   |_| \\___/ \\___/"
         << endl;
    cout << " _ _  __    __   _   _  _  ___ _   _  ____ \n"
            "|  _/ _ \\|  _ \\  |  ) / _ \\ / _ \\| |/ /_ _| \\ | |/ ___|\n"
            "| |_ | | | | |_) | |  _ \\| | | | | | | ' / | ||  \\| | |  _ \n"
            "|  _|| |_| |  _ <  | |_) | |_| | |_| | . \\ | || |\\  | |_| |\n"
            "|_|   \\___/|_| \\_\\ |____/ \\___/ \\___/|_|\\_\\___|_| \\_|\\____|\n"
         << endl;
    cout << "             ___ _ _   _   _   _ ____    _ \n"
            "     \\ \\      / /_ _|_   _| | | | | | | / ___|  | |\n"
            "      \\ \\ /\\ / / | |  | | | |_| | | | | \\___ \\  | |\n"
            "       \\ V  V /  | |  | | |  _  | | |_| |___) | |_|\n"
            "        \\_/\\_/  |___| |_| |_| |_|  \\___/|____/  (_)\n"
         << endl;
}

void printThanksRefund()
{
    cout << " __  _   _  __ __ ___ __ __  _ _   _ _     _  __   __\n"
            "/ ___|| | | |/ ___/ ___| ____/ ___/ ___||  ___| | | | |   | | \\ \\ / /\n"
            "\\___ \\| | | | |  | |   |  _| \\___ \\___ \\| |_  | | | | |   | |  \\ V / \n"
            " _) | |_| | |__| |___| |_ ___) |__) |  _| | |_| | |___| |___| |  \n"
            "|____/ \\___/ \\____\\____|_____|____/____/|_|    \\___/|_____|_____|_|  \n"
         << endl;
    cout << "       __  ___ _ _   _ _   _ __  ___ ____    _ \n"
            "      |  _ \\| ____|  ___| | | | \\ | |  _ \\| ____|  _ \\  | |\n"
            "      | |_) |  _| | |_  | | | |  \\| | | | |  _| | | | | | |\n"
            "      |  _ <| |___|  _| | |_| | |\\  | |_| | |___| |_| | |_|\n"
            "      |_| \\_\\_____|_|    \\___/|_| \\_|____/|_____|____/  (_)\n"
         << endl;
}

#endif