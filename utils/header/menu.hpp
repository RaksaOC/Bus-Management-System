#ifndef MENU_hpp
#define MENU_hpp

#include <iostream>
#include <fstream>

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

void historyMenu(){
    cout << R"(            
                                                ╦ ╦╦╔═╗╔╦╗╔═╗╦═╗╦ ╦
                                                ╠═╣║╚═╗ ║ ║ ║╠╦╝╚╦╝
                                                ╩ ╩╩╚═╝ ╩ ╚═╝╩╚═ ╩  
    )" << endl;
}

void resTypeMenu(){
    cout << R"(        
                                  ╦═╗╔═╗╔═╗╔═╗╦═╗╦  ╦╔═╗╔╦╗╦╔═╗╔╗╔  ╔╦╗╦ ╦╔═╗╔═╗
                                  ╠╦╝║╣ ╚═╗║╣ ╠╦╝╚╗╔╝╠═╣ ║ ║║ ║║║║   ║ ╚╦╝╠═╝║╣ 
                                  ╩╚═╚═╝╚═╝╚═╝╩╚═ ╚╝ ╩ ╩ ╩ ╩╚═╝╝╚╝   ╩  ╩ ╩  ╚═╝
)" << endl;
}
void refundTypeMenu(){
    cout << R"(        
                                          ╦═╗╔═╗╔═╗╦ ╦╔╗╔╔╦╗  ╔╦╗╦ ╦╔═╗╔═╗
                                          ╠╦╝║╣ ╠╣ ║ ║║║║ ║║   ║ ╚╦╝╠═╝║╣ 
                                          ╩╚═╚═╝╚  ╚═╝╝╚╝═╩╝   ╩  ╩ ╩  ╚═╝
)" << endl; 
}
void refundMenu(){
    cout << R"(        
                                                 ╦═╗╔═╗╔═╗╦ ╦╔╗╔╔╦╗
                                                 ╠╦╝║╣ ╠╣ ║ ║║║║ ║║
                                                 ╩╚═╚═╝╚  ╚═╝╝╚╝═╩╝
)" << endl; 
}
void LoginMenu(){
    cout << R"(        
                                                  ╦  ╔═╗╔═╗  ╦╔╗╔
                                                  ║  ║ ║║ ╦  ║║║║
                                                  ╩═╝╚═╝╚═╝  ╩╝╚╝
)" << endl;
}
void signupMenu(){
    cout << R"(        
                                                ╔═╗╦╔═╗╔╗╔  ╦ ╦╔═╗
                                                ╚═╗║║ ╦║║║  ║ ║╠═╝
                                                ╚═╝╩╚═╝╝╚╝  ╚═╝╩ 
)" << endl;
}
void thankYouForTravelingWithUs(){
    cout << R"(            
                                        ╔╦╗╦ ╦╔═╗╔╗╔╦╔═  ╦ ╦╔═╗╦ ╦  ╔═╗╔═╗╦═╗     
                                         ║ ╠═╣╠═╣║║║╠╩╗  ╚╦╝║ ║║ ║  ╠╣ ║ ║╠╦╝     
                                         ╩ ╩ ╩╩ ╩╝╚╝╩ ╩   ╩ ╚═╝╚═╝  ╚  ╚═╝╩╚═     
                                    ╔╦╗╦═╗╔═╗╦  ╦╔═╗╦  ╦╔╗╔╔═╗  ╦ ╦╦╔╦╗╦ ╦  ╦ ╦╔═╗
                                     ║ ╠╦╝╠═╣╚╗╔╝║╣ ║  ║║║║║ ╦  ║║║║ ║ ╠═╣  ║ ║╚═╗
                                     ╩ ╩╚═╩ ╩ ╚╝ ╚═╝╩═╝╩╝╚╝╚═╝  ╚╩╝╩ ╩ ╩ ╩  ╚═╝╚═╝
)" << endl;
}
void seccessRefundMenu(){
    cout << R"(            
                               ╔═╗╦ ╦╔═╗╔═╗╔═╗╔═╗╔═╗╔═╗╦ ╦╦  ╦ ╦ ╦  ╦═╗╔═╗╔═╗╦ ╦╔╗╔╔╦╗╔═╗╔╦╗
                               ╚═╗║ ║║  ║  ║╣ ╚═╗╚═╗╠╣ ║ ║║  ║ ╚╦╝  ╠╦╝║╣ ╠╣ ║ ║║║║ ║║║╣  ║║
                               ╚═╝╚═╝╚═╝╚═╝╚═╝╚═╝╚═╝╚  ╚═╝╩═╝╩═╝╩   ╩╚═╚═╝╚  ╚═╝╝╚╝═╩╝╚═╝═╩╝
)" << endl;
}
void addedToWaitListMenu(){
    cout << R"(            
                                       ╔═╗╔╦╗╔╦╗╔═╗╔╦╗  ╔╦╗╔═╗  ╦ ╦╔═╗╦╔╦╗╦  ╦╔═╗╔╦╗
                                       ╠═╣ ║║ ║║║╣  ║║   ║ ║ ║  ║║║╠═╣║ ║ ║  ║╚═╗ ║ 
                                       ╩ ╩═╩╝═╩╝╚═╝═╩╝   ╩ ╚═╝  ╚╩╝╩ ╩╩ ╩ ╩═╝╩╚═╝ ╩ 
)" << endl;
}
void availableBusMenu(){
    cout << R"(            
                                        ╔═╗╦  ╦╔═╗╦╦  ╔═╗╔╗ ╦  ╔═╗  ╔╗ ╦ ╦╔═╗╔═╗╔═╗
                                        ╠═╣╚╗╔╝╠═╣║║  ╠═╣╠╩╗║  ║╣   ╠╩╗║ ║╚═╗║╣ ╚═╗
                                        ╩ ╩ ╚╝ ╩ ╩╩╩═╝╩ ╩╚═╝╩═╝╚═╝  ╚═╝╚═╝╚═╝╚═╝╚═╝
)" << endl;
}
void resMenu(){
    cout << R"(            
                                            ╦═╗╔═╗╔═╗╔═╗╦═╗╦  ╦╔═╗╔╦╗╦╔═╗╔╗╔  
                                            ╠╦╝║╣ ╚═╗║╣ ╠╦╝╚╗╔╝╠═╣ ║ ║║ ║║║║  
                                            ╩╚═╚═╝╚═╝╚═╝╩╚═ ╚╝ ╩ ╩ ╩ ╩╚═╝╝╚╝  
)" << endl;
}
void resHistoryMenu(){
    cout << R"(            
                                   ╦═╗╔═╗╔═╗╔═╗╦═╗╦  ╦╔═╗╔╦╗╦╔═╗╔╗╔  ╦ ╦╦╔═╗╔╦╗╔═╗╦═╗╦ ╦
                                   ╠╦╝║╣ ╚═╗║╣ ╠╦╝╚╗╔╝╠═╣ ║ ║║ ║║║║  ╠═╣║╚═╗ ║ ║ ║╠╦╝╚╦╝
                                   ╩╚═╚═╝╚═╝╚═╝╩╚═ ╚╝ ╩ ╩ ╩ ╩╚═╝╝╚╝  ╩ ╩╩╚═╝ ╩ ╚═╝╩╚═ ╩  
)" << endl;
}
void seatsMenu(){
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
        cout << "\033[31m0. \033[0m Exit Program\n";
        cout << "\n\033[36m1. \033[0m Log in\n";
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
        cout << "\033[36m3. \033[0m View History\n> ";
        cin >> service;
        if (cin.fail() || service < 0 || service > 3)
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