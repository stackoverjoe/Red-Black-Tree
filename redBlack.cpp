//Joe Leland
//Assignment 3
//CS202
//This module contains all of the implementation of the redBlack class
#include "header.h"

redBlack::redBlack(){
    root = NULL;
    ifstream inFile;//create an ifstream object for file reading
    //temp variables for creating objects
    int type = 0;
    char tname[size];
    char thistory[size];
    char tfunction[size];
    bool treco = false;
    bool tpaid = false;
    char tspecial[size];
    int tspec = 0;
    app * grab = NULL;
    inFile.open("appData.csv");//opens appData.csv file for readinf
    while(!inFile.eof()){//grabs all data from text file, line by line, and loads objects
        inFile >> type;
        inFile.clear();
        inFile.ignore(size, ',');
        inFile.getline(tname, size, ',');
        inFile.getline(thistory, size, ',');
        inFile.getline(tfunction, size, ',');
        inFile >> treco; 
        inFile.clear();
        inFile.ignore(size, ',');
        inFile >> tpaid;
        inFile.clear();
        inFile.ignore(size, ',');
        inFile.getline(tspecial, size, ',');
        inFile >> tspec;
        inFile.clear();
        inFile.ignore(size, '\n');
        //type dictated as first field in file determines the nature of the app
        if(type == 1){
            app* temp = new gameApp(tspecial, tspec, tname, thistory, tfunction, treco, tpaid);
            grab = root->insert(root, temp);
        }
        else if(type == 2){          
            app* temp = new weatherApp(tspecial, tspec, tname, thistory, tfunction, treco, tpaid);
            grab = root->insert(root, temp);
        }
        else{
            app* temp = new studyApp(tspecial, tspec, tname, thistory, tfunction, treco, tpaid);
            grab = root->insert(root, temp);
        }
        if(grab){
            //if insert ever returns a non null pointer, it is the new root
            root = grab;
        }
        inFile.peek();//peek for eof
            
    }
    inFile.close();//close file
}


//destructor calls destroy function to delete tree
redBlack::~redBlack(){
    root->destroy(root);//deletes entire tree
    root = NULL;
}


//redBlack copy constructor calls upon a recursive function that copys all of the contents of the tree into a new one
redBlack::redBlack(const redBlack& be_copied){
    root = NULL;
    app *root2 = be_copied.root;
    root->copy(root, be_copied.root, root2);
}


//function to write out the contents of the tree into a .txt file
void redBlack::writeOut(){
    ofstream outFile;
    outFile.open("newFile.txt");
    root->writeOut(root, outFile);//calls to recursive function to write into the file
    outFile.close();
}


//search function takes a key word and calls app traverse function with key as arg
void redBlack::search(){
    char key[size];
    app* flag = NULL;//flag used to produce argument required for traverse method
    app *grab = NULL;//grab collects return value from app traverse method
    cout << "What app would you like to search for?\n(Provide a keyword and if any matches exists in the app name, history, or functionality, it will display the app): ";
    cin.getline(key, size, '\n');
    cout << '\n';
    grab = root->traverse(root, key, flag);
    //if grab is not null, the object was found and will be displayed
    if(grab){
        cout << (*grab) << endl;
    }
    else{
        cout << "No matches for the keyword: " << key << " were found." << endl;
    }
}


//Allows user to update the fields of a desired application
//this will also append their history information with their actions
void redBlack::update(){
    char key[size];
    app *grab = NULL;
    cout << "What app would you like to update?: ";
    cin.getline(key, size, '\n');
    cout << endl;
    grab = root->traverse(root, key, grab);//uses travers function to get the desired pointer
    if(grab){
        cout << "Updating: \n";
        cout << (*grab) << '\n';
        grab->update(key);
        cout << "Successfully updated app!\n" << endl;
    }
    else{
        cout << "No apps found with the keyword: " << key << "." << endl;
    }

}


//insert function prompts user for what type of app they would like to create and calls app class insert to add to the tree
void redBlack::insert(){
    app* grab = NULL;
    int type = 0;
    bool success = false;
    while(!success){
        try{
            cout << "What kind of app would you like to add?\n\t1.Gaming App\n\t2.Weather app\n\t3.Study app" << endl;
            cin >> type;
            if(!cin || type > 3 || type < 1){
                cin.clear();
                cin.ignore(size, '\n');
                throw(type);
            }
            cin.clear();
            cin.ignore(size, '\n');
            success = true;
        }
        catch(int type){
            cout << "Please select a number 1-3." << endl;
        }

    }
    //based on type of app they would like, an object is created and populated with the overloaded >> operator
    if(type == 1){
        app *temp1 = new gameApp;
        cin >> (*temp1);
        grab = root->insert(root, temp1);
    }
    else if(type == 2){
        app *temp = new weatherApp;
        cin >> (*temp);
        grab = root->insert(root, temp);
    }
    if(type == 3){
        app *temp = new studyApp;
        cin >> (*temp);
        grab = root->insert(root, temp);
    }
    if(grab){
        root = grab;//if grab is not NULL, it is the new root of the tree
    }
}


//display all calls app class displayAll
int redBlack::displayAll(){
    if(!root){
        return 0;
    }
    return root->displayAll(root);
}


//height calls app class height
int redBlack::height(){
    return root->height(root);

}

void redBlack::destroy(){
    root->destroy(root);
}






