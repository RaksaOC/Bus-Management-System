#ifndef MENU_hpp
#define MENU_hpp

#include <iostream>
#include <thread>
#include <chrono>

#define invalidInputMessage "\n[⚠] \033[31mError: Invalid Input\033[0m\n\n";
#define invalidPasswordMessage "\n[⚠] \033[31mError: Invalid Password\033[0m\n\n";
#define invalidEmailFormatMessage "\n[⚠] \033[31mError: Invalid Password\033[0m\n\n";
#define openFileFailMessage "\n[⚠] \033[31mError: Cannot open\033[0m\n\n";
#define invalidNameMessage "\n[⚠] \033[31mError: Invalid Name Format\033[0m\n\n";
#define invalidNameFormatMessage "\n[⚠] \033[31mError: Invalid Name Format, Name Cannot Contain numbers\033[0m\n\n";
#define invalidAgeMessage "\n[⚠] \033[31mError: Invalid Age\033[0m\n\n";
#define incorrectEmailMessage "\n[⚠] \033[31mError: Incorrect Email\033[0m\n\n";
#define incorrectPasswordMessage "\n[⚠] \033[31mError: Incorrect Password\033[0m\n\n";
#define seatUnavailableMessage "\n[⚠] \033[31mError: Seat Unavailable\033[0m\n\n";
#define invalidDestinationMessage "\n[⚠] \033[31mError: Invalid Destination\033[0m\n\n";
#define tooYoungMessage "\n[⚠] \033[31mError: Invalid User Must Be Older Than 13 Years Old\033[0m\n\n";
#define tooOldMessage "\n[⚠] \033[31mError: User Is Too Old\033[0m\n\n";
#define invalidFilePath "\n[⚠] \033[31mError: Failed To Open file, Path: \033[0m\n\n";
#define takenEmail "\n[⚠] \033[31mError: Email Is Taken \033[0m\n\n";
#define passwordTooLong "\n[⚠] \033[31mError: Password Must Be Longer Than 6 Characters \033[0m\n\n";

using namespace std;

void simpleBusLoading()
{
    const int duration = 1;     // Duration of the loading animation in seconds
    const int delay = 40;       // Delay between each frame in milliseconds
    const int maxPosition = 50; // Max space for the bus to move across

    std::string track = "_________________________"; // Track with underscores
    std::string bus = "🚌";
    std::cout << "\033[36m\nLoading...\n\n\033[0m"; // Display the loading message
    cout << track << endl
         << endl;

    for (int i = 0; i < duration * 1000 / delay; ++i)
    {
        // Replace all characters before the bus with '#' to leave a full trail
        std::string currentTrack = track;
        for (int j = 0; j < i % maxPosition; ++j)
        {
            currentTrack[j] = '#'; // Fill the route passed with #
        }

        // Move the bus across the track
        std::cout << "\r" << currentTrack.substr(0, i % maxPosition) << bus << currentTrack.substr(i % maxPosition + 1) << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
    cout << endl
         << track;
    std::cout << "\n\n";
}

void printLuxaryBus()
{
    cout << "\033[36m\t\t\t\t\t                             __\n"
            "\t\t\t\t\t    .-----------------------'  |\n"
            "\t\t\t\t\t   /| _ .---. .---. .---. .---.|\n"
            "\t\t\t\t\t   |j||||___| |___| |___| |___||\n"
            "\t\t\t\t\t   |=|||=======================|\n"
            "\t\t\t\t\t   [_|j||(O)\\__________||(O)__]\033[0m"
         << endl;
    cout << "\n\n";
}

void historyMenu()
{
    cout << R"(            
                                                ╦ ╦╦╔═╗╔╦╗╔═╗╦═╗╦ ╦
                                                ╠═╣║╚═╗ ║ ║ ║╠╦╝╚╦╝
                                                ╩ ╩╩╚═╝ ╩ ╚═╝╩╚═ ╩  
    )" << endl;
}

void resTypeMenu()
{
    cout << R"(        
                                  ╦═╗╔═╗╔═╗╔═╗╦═╗╦  ╦╔═╗╔╦╗╦╔═╗╔╗╔  ╔╦╗╦ ╦╔═╗╔═╗
                                  ╠╦╝║╣ ╚═╗║╣ ╠╦╝╚╗╔╝╠═╣ ║ ║║ ║║║║   ║ ╚╦╝╠═╝║╣ 
                                  ╩╚═╚═╝╚═╝╚═╝╩╚═ ╚╝ ╩ ╩ ╩ ╩╚═╝╝╚╝   ╩  ╩ ╩  ╚═╝
)" << endl;
}
void refundTypeMenu()
{
    cout << R"(        
                                          ╦═╗╔═╗╔═╗╦ ╦╔╗╔╔╦╗  ╔╦╗╦ ╦╔═╗╔═╗
                                          ╠╦╝║╣ ╠╣ ║ ║║║║ ║║   ║ ╚╦╝╠═╝║╣ 
                                          ╩╚═╚═╝╚  ╚═╝╝╚╝═╩╝   ╩  ╩ ╩  ╚═╝
)" << endl;
}
void refundMenu()
{
    cout << R"(        
                                                 ╦═╗╔═╗╔═╗╦ ╦╔╗╔╔╦╗
                                                 ╠╦╝║╣ ╠╣ ║ ║║║║ ║║
                                                 ╩╚═╚═╝╚  ╚═╝╝╚╝═╩╝
)" << endl;
}
void LoginMenu()
{
    cout << R"(        
                                                  ╦  ╔═╗╔═╗  ╦╔╗╔
                                                  ║  ║ ║║ ╦  ║║║║
                                                  ╩═╝╚═╝╚═╝  ╩╝╚╝
)" << endl;
}
void signupMenu()
{
    cout << R"(        
                                                ╔═╗╦╔═╗╔╗╔  ╦ ╦╔═╗
                                                ╚═╗║║ ╦║║║  ║ ║╠═╝
                                                ╚═╝╩╚═╝╝╚╝  ╚═╝╩ 
)" << endl;
}
void thankYouForTravelingWithUs()
{
    cout << R"(            
                                        ╔╦╗╦ ╦╔═╗╔╗╔╦╔═  ╦ ╦╔═╗╦ ╦  ╔═╗╔═╗╦═╗     
                                         ║ ╠═╣╠═╣║║║╠╩╗  ╚╦╝║ ║║ ║  ╠╣ ║ ║╠╦╝     
                                         ╩ ╩ ╩╩ ╩╝╚╝╩ ╩   ╩ ╚═╝╚═╝  ╚  ╚═╝╩╚═     
                                    ╔╦╗╦═╗╔═╗╦  ╦╔═╗╦  ╦╔╗╔╔═╗  ╦ ╦╦╔╦╗╦ ╦  ╦ ╦╔═╗
                                     ║ ╠╦╝╠═╣╚╗╔╝║╣ ║  ║║║║║ ╦  ║║║║ ║ ╠═╣  ║ ║╚═╗
                                     ╩ ╩╚═╩ ╩ ╚╝ ╚═╝╩═╝╩╝╚╝╚═╝  ╚╩╝╩ ╩ ╩ ╩  ╚═╝╚═╝
)" << endl;
}
void seccessRefundMenu()
{
    cout << R"(            
                               ╔═╗╦ ╦╔═╗╔═╗╔═╗╔═╗╔═╗╔═╗╦ ╦╦  ╦ ╦ ╦  ╦═╗╔═╗╔═╗╦ ╦╔╗╔╔╦╗╔═╗╔╦╗
                               ╚═╗║ ║║  ║  ║╣ ╚═╗╚═╗╠╣ ║ ║║  ║ ╚╦╝  ╠╦╝║╣ ╠╣ ║ ║║║║ ║║║╣  ║║
                               ╚═╝╚═╝╚═╝╚═╝╚═╝╚═╝╚═╝╚  ╚═╝╩═╝╩═╝╩   ╩╚═╚═╝╚  ╚═╝╝╚╝═╩╝╚═╝═╩╝
)" << endl;
}
void addedToWaitListMenu()
{
    cout << R"(            
                                       ╔═╗╔╦╗╔╦╗╔═╗╔╦╗  ╔╦╗╔═╗  ╦ ╦╔═╗╦╔╦╗╦  ╦╔═╗╔╦╗
                                       ╠═╣ ║║ ║║║╣  ║║   ║ ║ ║  ║║║╠═╣║ ║ ║  ║╚═╗ ║ 
                                       ╩ ╩═╩╝═╩╝╚═╝═╩╝   ╩ ╚═╝  ╚╩╝╩ ╩╩ ╩ ╩═╝╩╚═╝ ╩ 
)" << endl;
}
void availableBusMenu()
{
    cout << R"(            
                                        ╔═╗╦  ╦╔═╗╦╦  ╔═╗╔╗ ╦  ╔═╗  ╔╗ ╦ ╦╔═╗╔═╗╔═╗
                                        ╠═╣╚╗╔╝╠═╣║║  ╠═╣╠╩╗║  ║╣   ╠╩╗║ ║╚═╗║╣ ╚═╗
                                        ╩ ╩ ╚╝ ╩ ╩╩╩═╝╩ ╩╚═╝╩═╝╚═╝  ╚═╝╚═╝╚═╝╚═╝╚═╝
)" << endl;
}
void resMenu()
{
    cout << R"(            
                                            ╦═╗╔═╗╔═╗╔═╗╦═╗╦  ╦╔═╗╔╦╗╦╔═╗╔╗╔  
                                            ╠╦╝║╣ ╚═╗║╣ ╠╦╝╚╗╔╝╠═╣ ║ ║║ ║║║║  
                                            ╩╚═╚═╝╚═╝╚═╝╩╚═ ╚╝ ╩ ╩ ╩ ╩╚═╝╝╚╝  
)" << endl;
}
void resHistoryMenu()
{
    cout << R"(            
                                   ╦═╗╔═╗╔═╗╔═╗╦═╗╦  ╦╔═╗╔╦╗╦╔═╗╔╗╔  ╦ ╦╦╔═╗╔╦╗╔═╗╦═╗╦ ╦
                                   ╠╦╝║╣ ╚═╗║╣ ╠╦╝╚╗╔╝╠═╣ ║ ║║ ║║║║  ╠═╣║╚═╗ ║ ║ ║╠╦╝╚╦╝
                                   ╩╚═╚═╝╚═╝╚═╝╩╚═ ╚╝ ╩ ╩ ╩ ╩╚═╝╝╚╝  ╩ ╩╩╚═╝ ╩ ╚═╝╩╚═ ╩  
)" << endl;
}
void seatsMenu()
{
    cout << R"(            
                                                    ╔═╗╔═╗╔═╗╔╦╗╔═╗
                                                    ╚═╗║╣ ╠═╣ ║ ╚═╗
                                                    ╚═╝╚═╝╩ ╩ ╩ ╚═╝
)" << endl;
}

void userAuthMenu()
{
    cout << R"(
                                  ╦ ╦╔═╗╔═╗╦═╗  ╔═╗╦ ╦╔╦╗╦ ╦╔═╗╔╗╔╦╗╦╔═╗╔═╗╔╦╗╦╔═╗╔╗╔
                                  ║ ║╚═╗║╣ ╠╦╝  ╠═╣║ ║ ║ ╠═╣║╣ ║║║║ ║║  ╠═╣ ║ ║║ ║║║║
                                  ╚═╝╚═╝╚═╝╩╚═  ╩ ╩╚═╝ ╩ ╩ ╩╚═╝╝╚╝╩ ╩╚═╝╩ ╩ ╩ ╩╚═╝╝╚╝
    )";
}

void clearInput()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int logInOrSignUpMenu()
{
    userAuthMenu();
    int authChoice;
    do
    {
        cout << "\n\033[31m0. \033[0m Exit Program\n";
        cout << "\033[36m1. \033[0m Log in\n";
        cout << "\033[36m2. \033[0m Sign Up\n\n> ";
        cin >> authChoice;
        if (cin.fail() || authChoice < 0 || authChoice > 2)
        {
            cout << invalidInputMessage;
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
        cout << R"(
                                                ╔═╗╔═╗╦═╗╦  ╦╦╔═╗╔═╗╔═╗
                                                ╚═╗║╣ ╠╦╝╚╗╔╝║║  ║╣ ╚═╗
                                                ╚═╝╚═╝╩╚═ ╚╝ ╩╚═╝╚═╝╚═╝
    )";
        cout << endl;
        cout << "\033[36m1. \033[0m Booking\n";
        cout << "\033[36m2. \033[0m Refund\n";
        cout << "\033[36m3. \033[0m View History\n\n> ";
        cin >> service;
        if (cin.fail() || service < 1 || service > 3)
        {
            clearInput();
            cout << invalidInputMessage;
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
        cout << "\033[31m0. \033[0m Back to bus type selection menu\n";
        cout << "\033[36m1. \033[0m Book one ticket\n";
        cout << "\033[36m2. \033[0m Book multiple tickets\n\n> ";
        cin >> typeOfBooking;
        if (cin.fail() || typeOfBooking < 0 || typeOfBooking > 2)
        {
            clearInput();
            cout << invalidInputMessage;
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
        cout << "\n\n";
        cout << R"(
                                  ╔═╗╔╦╗╔╦╗╦╔╗╔  ╔═╗╔═╗╔╦╗╦╔═╗╔╗╔╔═╗
                                  ╠═╣ ║║║║║║║║║  ╠═╣║   ║ ║║ ║║║║╚═╗
                                  ╩ ╩═╩╝╩ ╩╩╝╚╝  ╩ ╩╚═╝ ╩ ╩╚═╝╝╚╝╚═╝
    )";
        cout << "0. Back\n";
        cout << "1. Add Admin\n";
        cout << "2. Add Bus\n";
        cout << "3. View Buses\n";
        cout << "4. View Users\n";
        cout << "5. Delete User\n";
        cout << "6. Delete Bus\n";
        cout << "Enter your choice: ";
        cin >> choice;
        if (cin.fail() || choice < 0 || choice > 6)
        {
            clearInput();
            cout << invalidInputMessage;
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
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    cout << R"(
██████╗ ██╗   ██╗███████╗    ███╗   ███╗ █████╗ ███╗   ██╗ █████╗  ██████╗ ███████╗███╗   ███╗███████╗███╗   ██╗████████╗    
██╔══██╗██║   ██║██╔════╝    ████╗ ████║██╔══██╗████╗  ██║██╔══██╗██╔════╝ ██╔════╝████╗ ████║██╔════╝████╗  ██║╚══██╔══╝    
██████╔╝██║   ██║███████╗    ██╔████╔██║███████║██╔██╗ ██║███████║██║  ███╗█████╗  ██╔████╔██║█████╗  ██╔██╗ ██║   ██║       
██╔══██╗██║   ██║╚════██║    ██║╚██╔╝██║██╔══██║██║╚██╗██║██╔══██║██║   ██║██╔══╝  ██║╚██╔╝██║██╔══╝  ██║╚██╗██║   ██║       
██████╔╝╚██████╔╝███████║    ██║ ╚═╝ ██║██║  ██║██║ ╚████║██║  ██║╚██████╔╝███████╗██║ ╚═╝ ██║███████╗██║ ╚████║   ██║       
╚═════╝  ╚═════╝ ╚══════╝    ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝ ╚═════╝ ╚══════╝╚═╝     ╚═╝╚══════╝╚═╝  ╚═══╝   ╚═╝       
                                                                                                                             
                                 ███████╗██╗   ██╗███████╗████████╗███████╗███╗   ███╗                        
                                 ██╔════╝╚██╗ ██╔╝██╔════╝╚══██╔══╝██╔════╝████╗ ████║                        
                                 ███████╗ ╚████╔╝ ███████╗   ██║   █████╗  ██╔████╔██║                        
                                 ╚════██║  ╚██╔╝  ╚════██║   ██║   ██╔══╝  ██║╚██╔╝██║                        
                                 ███████║   ██║   ███████║   ██║   ███████╗██║ ╚═╝ ██║                        
                                 ╚══════╝   ╚═╝   ╚══════╝   ╚═╝   ╚══════╝╚═╝     ╚═╝                        
                                                                                                                             
    )";
    printLuxaryBus();
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

// void printThanks()
// {
//     cout << "\n\n";
//     cout << "    _____ _   _    _    _   _ _  __ __   _____  _   _ \n"
//             "   |_   _| | | |  / \\  | \\ | | |/ / \\ \\ / / _ \\| | | |\n"
//             "     | | | |_| | / _ \\ |  \\| | ' /   \\ V / | | | | | |\n"
//             "     | | |  _  |/ ___ \\| |\\  | . \\    | || |_| | |_| |\n"
//             "     |_| |_| |_/_/   \\_\\_| \\_|_|\\_\\   |_| \\___/ \\___/"
//          << endl;
//     cout << " _____ ___  ____    ____   ___   ___  _  _____ _   _  ____ \n"
//             "|  ___/ _ \\|  _ \\  | __ ) / _ \\ / _ \\| |/ /_ _| \\ | |/ ___|\n"
//             "| |_ | | | | |_) | |  _ \\| | | | | | | ' / | ||  \\| | |  _ \n"
//             "|  _|| |_| |  _ <  | |_) | |_| | |_| | . \\ | || |\\  | |_| |\n"
//             "|_|   \\___/|_| \\_\\ |____/ \\___/ \\___/|_|\\_\\___|_| \\_|\\____|\n"
//          << endl;
//     cout << "     __        _____ _____ _   _   _   _ ____    _ \n"
//             "     \\ \\      / /_ _|_   _| | | | | | | / ___|  | |\n"
//             "      \\ \\ /\\ / / | |  | | | |_| | | | | \\___ \\  | |\n"
//             "       \\ V  V /  | |  | | |  _  | | |_| |___) | |_|\n"
//             "        \\_/\\_/  |___| |_| |_| |_|  \\___/|____/  (_)\n"
//          << endl;
// }

// void printThanksRefund()
// {
//     cout << " ____  _   _  ____ ____ _____ ____ ____  _____ _   _ _     _  __   __\n"
//             "/ ___|| | | |/ ___/ ___| ____/ ___/ ___||  ___| | | | |   | | \\ \\ / /\n"
//             "\\___ \\| | | | |  | |   |  _| \\___ \\___ \\| |_  | | | | |   | |  \\ V / \n"
//             " ___) | |_| | |__| |___| |___ ___) |__) |  _| | |_| | |___| |___| |  \n"
//             "|____/ \\___/ \\____\\____|_____|____/____/|_|    \\___/|_____|_____|_|  \n"
//          << endl;
//     cout << "       ____  _____ _____ _   _ _   _ ____  _____ ____    _ \n"
//             "      |  _ \\| ____|  ___| | | | \\ | |  _ \\| ____|  _ \\  | |\n"
//             "      | |_) |  _| | |_  | | | |  \\| | | | |  _| | | | | | |\n"
//             "      |  _ <| |___|  _| | |_| | |\\  | |_| | |___| |_| | |_|\n"
//             "      |_| \\_\\_____|_|    \\___/|_| \\_|____/|_____|____/  (_)\n"
//          << endl;
// }

#endif