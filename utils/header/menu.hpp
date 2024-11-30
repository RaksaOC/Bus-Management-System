#ifndef MENU_hpp
#define MENU_hpp

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

int serviceMenu()
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

void printStandardBus()
{
    cout << " _________________________________\n"
            "|,----.,----.,----.,----.,----.,--.\\\n"
            "||    ||    ||    ||    ||    ||   \\\\\n"
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
    cout << "    _____ _   _    _    _   _ _  __ __   _____  _   _ \n"
            "   |_   _| | | |  / \\  | \\ | | |/ / \\ \\ / / _ \\| | | |\n"
            "     | | | |_| | / _ \\ |  \\| | ' /   \\ V / | | | | | |\n"
            "     | | |  _  |/ ___ \\| |\\  | . \\    | || |_| | |_| |\n"
            "     |_| |_| |_/_/   \\_\\_| \\_|_|\\_\\   |_| \\___/ \\___/"
         << endl;
    cout << " _____ ___  ____    ____   ___   ___  _  _____ _   _  ____ \n"
            "|  ___/ _ \\|  _ \\  | __ ) / _ \\ / _ \\| |/ /_ _| \\ | |/ ___|\n"
            "| |_ | | | | |_) | |  _ \\| | | | | | | ' / | ||  \\| | |  _ \n"
            "|  _|| |_| |  _ <  | |_) | |_| | |_| | . \\ | || |\\  | |_| |\n"
            "|_|   \\___/|_| \\_\\ |____/ \\___/ \\___/|_|\\_\\___|_| \\_|\\____|\n"
         << endl;
    cout << "     __        _____ _____ _   _   _   _ ____    _ \n"
            "     \\ \\      / /_ _|_   _| | | | | | | / ___|  | |\n"
            "      \\ \\ /\\ / / | |  | | | |_| | | | | \\___ \\  | |\n"
            "       \\ V  V /  | |  | | |  _  | | |_| |___) | |_|\n"
            "        \\_/\\_/  |___| |_| |_| |_|  \\___/|____/  (_)\n"
         << endl;
}

void printThanksRefund()
{
    cout << " ____  _   _  ____ ____ _____ ____ ____  _____ _   _ _     _  __   __\n"
            "/ ___|| | | |/ ___/ ___| ____/ ___/ ___||  ___| | | | |   | | \\ \\ / /\n"
            "\\___ \\| | | | |  | |   |  _| \\___ \\___ \\| |_  | | | | |   | |  \\ V / \n"
            " ___) | |_| | |__| |___| |___ ___) |__) |  _| | |_| | |___| |___| |  \n"
            "|____/ \\___/ \\____\\____|_____|____/____/|_|    \\___/|_____|_____|_|  \n"
         << endl;
    cout << "       ____  _____ _____ _   _ _   _ ____  _____ ____    _ \n"
            "      |  _ \\| ____|  ___| | | | \\ | |  _ \\| ____|  _ \\  | |\n"
            "      | |_) |  _| | |_  | | | |  \\| | | | |  _| | | | | | |\n"
            "      |  _ <| |___|  _| | |_| | |\\  | |_| | |___| |_| | |_|\n"
            "      |_| \\_\\_____|_|    \\___/|_| \\_|____/|_____|____/  (_)\n"
         << endl;
}

#endif