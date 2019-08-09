//Joe Leland
//This module creates the redblack tree and menu to be ran by the user. All interactions with the data are called from here, to the redBlack class.
#include "header.h"




int main(){
    char choice = 'o';//control variable to switch on
    int rand();//random integer used to populate temperate in the weather app
    int grab = 0;//grab used to get return value from functions
    srand(time(NULL));//seeds rand() int
    redBlack my_tree;//redBlack tree object created

    //loop to control program, exits on q or Q
    cout << "Welcome to the app manager program!" << endl;
    while(choice != 'q' && choice != 'Q'){
        cout << "\t1. Insert a new app\n\t2. Display all apps\n\t3. Display specific app\n\t4. Update App\n\t5. Delete all apps.\n\t6. Write tree to external file.\n\t7. Display tree height.\n\tQ|q. To quit program." << endl;
        cin >> choice;
        cin.clear();
        cin.ignore(size, '\n');
        //switches on choice
        switch(choice){
            case '1':
                my_tree.insert();//calls insert function
                break;
            case '2':
                grab = my_tree.displayAll();//calls display function
                cout << "Displayed " << grab << " app(s)." << endl;
                break;
            case '3':
                my_tree.search();//calls universal search function
                break;
            case '4':
                my_tree.update();//calls update, which allows for fields to be updated and also updates history
                break;
            case '5':
                cout << "All apps deleted." << endl;
                my_tree.destroy();
                break;
            case '6':
                cout << "Writing file..\nFile: \"newFile.txt\" successfully created!" << endl;
                my_tree.writeOut();
                break;
            case '7':
                cout << "Height of tree: " << my_tree.height() << endl;
                break;
            case 'q':
            case 'Q':
                cout << "Goodbye." << endl;
                continue;//continues as to not print "invalid option" upon exit

            default:
                cout << "Invalid option." << endl;
                break;
        }
    }
    return 0;

}
