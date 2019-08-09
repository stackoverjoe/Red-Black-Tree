//Joe Leland
//Assignment 3
//CS202
//This module contains all of the implementations for the app class
#include "header.h"




app::app():right(NULL), left(NULL), parent(NULL), color(red), appName(NULL), history(NULL), function(NULL), recommend(false), paid(false){}


//constructor that takes all app args
app::app(char name[], char histo[], char func[], bool reco, bool pd):right(NULL), left(NULL), parent(NULL), color(red), recommend(reco), paid(pd){
    appName = new char[strlen(name) + 1];
    strcpy(appName, name);
    history = new char[strlen(histo) + 1];
    strcpy(history, histo);
    function = new char[strlen(func) + 1];
    strcpy(function, func);
}


//copy constructor
app::app(const app& be_copied){
    appName = new char[strlen(be_copied.appName) + 1];
    strcpy(appName, be_copied.appName);
    history = new char[strlen(be_copied.history) + 1];
    strcpy(history, be_copied.history);
    function = new char[strlen(be_copied.function) + 1];
    strcpy(function, be_copied.function);
    recommend = be_copied.recommend;
    paid = be_copied.paid;
    left = right = parent = NULL;//pointers set to null to avoid shallow copies
}


//deconstructor declared virtual
app::~app(){
    if(appName){
        delete[] appName;
        appName = NULL;
    }
    if(history){
        delete[] history;
        history = NULL;
    }
    if(function){
        delete[] function;
        function = NULL;
    }
}


studyApp::studyApp():schedule(NULL), time(0){}


//constructor that takes all args for self and base class, calls base class constructor
studyApp::studyApp(char sched[], int t,  char name[], char hist[], char func[], bool reco, bool pd): app(name, hist, func, reco, pd){
    schedule = new char[strlen(sched) + 1];
    strcpy(schedule, sched);
}


//virtual deconstructor 
studyApp::~studyApp(){
    if(schedule){
        delete[] schedule;
        schedule = NULL;
    }
}


gameApp::gameApp():tips(NULL), highScore(0){}


//constructor that takes all args for self and base class, calls base class constructor
gameApp::gameApp(char tip[], int high, char name[], char hist[], char func[], bool reco, bool pd):app(name, hist, func, reco, pd), highScore(high){
    tips = new char[strlen(tip) + 1];
    strcpy(tips, tip);
    highScore = high;
}


//gameApp copy constructor
gameApp::gameApp(const gameApp& be_copied):app(be_copied){
    tips = new char[strlen(be_copied.tips) + 1];
    strcpy(tips, be_copied.tips);
    highScore = be_copied.highScore;
}


//weatherApp copy constructor
weatherApp::weatherApp(const weatherApp& be_copied):app(be_copied){
    conditions = new char[strlen(be_copied.conditions) + 1];
    strcpy(conditions, be_copied.conditions);
    temp = be_copied.temp;
}


//studyApp copy constructor
studyApp::studyApp(const studyApp& be_copied):app(be_copied){
    schedule = new char[strlen(be_copied.schedule) + 1];
    strcpy(schedule, be_copied.schedule);
    time = be_copied.time;
}


//virtual deconstrucor
gameApp::~gameApp(){
    if(tips){
        delete[] tips;
        tips = NULL;
    }
    highScore = 0;
}



weatherApp::weatherApp():conditions(NULL), temp(0){}


//constructor that takes all args for self and base class, calls base class constructor
weatherApp::weatherApp(char cond[], int t, char name[], char hist[], char func[], bool reco, bool pd):app(name, hist, func, reco, pd), temp(t){
    conditions = new char[strlen(cond) + 1];
    strcpy(conditions, cond);

}


//virtual deconstructor
weatherApp::~weatherApp(){
    if(conditions){
        delete[] conditions;
        conditions = NULL;
    }
}


//write out function to write tree contents to file
void app::writeOut(app*root, ofstream& outFile){
    if(!root){
        return;
    }
    outFile << root->appName << ',' << root->history << ',' << root->function << ',';
    root->write(outFile);
    writeOut(root->left, outFile);
    writeOut(root->right, outFile);
}


//virtual write out for derived classes
void gameApp::write(ofstream& outFile){
    outFile << tips << ',' << highScore << '\n';
}


void weatherApp::write(ofstream& outFile){
    outFile << conditions << ',' << temp << '\n';
}


void studyApp::write(ofstream& outFile){
    outFile << schedule << ',' << time << '\n';
}


//overloaded = that copies the object on the left into the object on the fight. Virtual to be used with upcasting
app& app::operator= (const app& be_copied){
    if(this == &be_copied){
        return *this;
    }
    if(appName){
        delete[] appName;
        appName = NULL;
    }
    appName = new char[strlen(be_copied.appName) + 1];
    strcpy(appName, be_copied.appName);
    if(history){
        delete[] history;
        history = NULL;
    }
    history = new char[strlen(be_copied.history) + 1];
    strcpy(history, be_copied.history);
    if(function){
        delete[] function;
        function = NULL;
    }
    function = new char[strlen(be_copied.function) + 1];
    strcpy(function, be_copied.function);
    recommend = be_copied.recommend;
    paid = be_copied.paid;
    right = left = parent = NULL;
    return *this;
}


//overloaded < to compare app names
bool app::operator<(const app&obj)const{

    if(strcmp(this->appName, obj.appName) < 0){
             return true;
    }
    return false;
}


//overloaded > to compare appNames
bool app::operator>(const app&obj)const{
    
    if(strcmp(this->appName, obj.appName) > 0){
        return true;
    }
    return false;
}


bool app::operator <= (const app& obj)const{//compares two appNames with strcmp
    
    return !(strcmp(appName, obj.appName) <= 0);

}


bool app::operator >= (const app& obj)const{//compares two appNames with strcmp

    return !(strcmp(appName, obj.appName) >= 0);

}


//overloaded == to compare two app names and return true if they are the same
bool app::operator==(const app&obj)const{

    return !strcmp(appName, obj.appName);

}


//overloaded != to compare two app names and return false if they are not
bool app::operator!=(const app&obj)const{

    if(strcmp(this->appName, obj.appName)){
        return true;
    }
    return false;
}


int gameApp::operator + (const gameApp& to_add)const{
    int i = this->highScore + to_add.highScore;
    return i;
}


int weatherApp::operator + (const weatherApp& to_add)const{
    int i = this->temp + to_add.temp;
    return i;
}


int studyApp::operator + (const studyApp& to_add)const{
    int i = this->time + to_add.time;
    return i;
}


gameApp& gameApp::operator += (const gameApp& to_add){
    char *temp = new char[strlen(tips) + strlen(to_add.tips) +3];  
    sprintf(temp, "%s, %s", tips, to_add.tips);//uses the cstring library format function to insert a ',' and append the tips char * with the concatination
    if(tips){
        delete[] tips;
        tips = NULL;
    }
    strcpy(tips, temp);
    highScore+=to_add.highScore;
    delete[]temp;
    return *this;
}


studyApp& studyApp::operator += (const studyApp& to_add){
    char *temp = new char[strlen(schedule) + strlen(to_add.schedule) +3];  
    sprintf(temp, "%s, %s", schedule, to_add.schedule);//uses the cstring library format function to insert a ',' and append the schedule char * with the concatination
    if(schedule){
        delete[] schedule;
        schedule = NULL;
    }
    strcpy(schedule, temp);
    time+=to_add.time;
    delete[]temp;
    return *this;
}


weatherApp& weatherApp::operator += (const weatherApp& to_add){
    char *temp = new char[strlen(conditions) + strlen(to_add.conditions) +3];  
    sprintf(temp, "%s, %s", conditions, to_add.conditions);//uses the cstring library format function to inser t a ',' and append the conditions char * with the concatination
    if(conditions){
        delete[] conditions;
        conditions = NULL;
    }
    strcpy(conditions, temp);
    temp+=to_add.temp;
    delete[]temp;
    return *this;
}


//friend operator >> overloaded to populate objects with data
istream& operator >> (istream& in, app& obj){
    obj.populate(in);//virtual helper function call
    return in;
}


//friend operator << overloaded to display apps by calling virtual display func
ostream& operator<< (ostream& out, const app& obj){
    obj.display(out);//virtual helper function call
    return out;
}


//virtual overloaded = operator to copy an object 
gameApp& gameApp::operator = (const gameApp& be_copied){
    if(this == &be_copied){//checks for self copy
        return *this;
    }
    app::operator=(be_copied);
    if(tips){
        delete[] tips;
        tips = NULL;
    }
    tips = new char[strlen(be_copied.tips) + 1];
    strcpy(tips, be_copied.tips);
    highScore = be_copied.highScore;
    return *this;
}


//virtual overloaded = operator to copy an object 
weatherApp& weatherApp::operator = (const weatherApp& be_copied){
    if(this == &be_copied){//checks for self copy
        return *this;
    }
    app::operator=(be_copied);
    if(conditions){
        delete[] conditions;
        conditions = NULL;
    }
    conditions = new char[strlen(be_copied.conditions) + 1];
    strcpy(conditions, be_copied.conditions);
    temp = be_copied.temp;
    return *this;
}


//virtually overloaded = operator to copy an object of same type
studyApp& studyApp::operator = (const studyApp& be_copied){
    if(this == &be_copied){//check for self copy
        return *this;
    }
    app::operator=(be_copied);
    if(history){
        delete[] history;
        history = NULL;
    }
    schedule = new char[strlen(be_copied.schedule) + 1];
    strcpy(schedule, be_copied.schedule);
    time = be_copied.time;
    return *this;
}


//virtual populate function called by overloaded >> 
void app::populate(istream& in){
    //temp variables used to get string lengths
    char t = 'n';
    char tname[size];
    char thistory[size] = "";
    char tfunction[size];
    bool treco = false;
    cout << "What is the name of the app?: ";
    in.getline(tname, size, '\n');
    appName = new char[strlen(tname) + 1];
    strcpy(appName, tname);
    cout << "What does the app do?: ";
    in.getline(tfunction, size, '\n');
    function = new char[strlen(tfunction) + 1];
    strcpy(function, tfunction);
    cout << "Would you recommend this app?(y/n) ";
    in >> t;
    in.clear();
    in.ignore(size, '\n');
    if(t == 'y' || t == 'Y'){
        recommend = true;
    }
    cout << "Have you paid for this app?(y/n) ";
    in >> treco;
    in.clear();
    in.ignore(size, '\n');
    if(t == 'y' || t == 'Y'){
        paid = true;
    }
    history = new char[strlen(thistory) + 1];
    strcpy(history, thistory);

}


//virtual populate function for gameApp
void gameApp::populate(istream& in){
    app::populate(in);//calls parent function
    char special[size];
    int temp = 0;
    bool success = false;
    cout << "What tips/advice would you like to enter for this game?: ";
    in.getline(special, size, '\n');
    tips = new char[strlen(special) + 1];
    strcpy(tips, special);
    //ensures temp var is only populated with a int
    while(!success){
        try{
            cout << "What is your high score?: ";
            in >> temp;
            if(!in){
                in.clear();
                in.ignore(size, '\n');
                throw(temp);
            }
            in.clear();
            in.ignore(size, '\n');
            highScore = temp;
            success = true;
        }
        catch(int temp){
            cout << "Please only enter a number." << endl;
        }
    }
}


//virtual populate for weatherApp
void weatherApp::populate(istream& in){
    app::populate(in);//calls parent function
    char special[size];
    cout << "What observations would you like to record about the weather: ";
    in.getline(special, size, '\n');
    conditions = new char[strlen(special) + 1];
    strcpy(conditions, special);
    temp = rand()%100;//pretends to know the temp
}


//virtual populate forStudyApp
void studyApp::populate(istream& in){
    app::populate(in);//calls parent function
    char special[size];
    int temp = 0;
    bool success = false;
    //int sp = 0;
    cout << "What are the details of your study schedule?: ";
    in.getline(special, size, '\n');
    schedule = new char[strlen(special) + 1];
    strcpy(schedule, special);
    //while try protects from bad input
    while(!success){
        try{
            cout << "How Many hours have you spent studying?: ";
            in >> temp;
            if(!in){
                in.clear();
                in.ignore(size, '\n');
                throw(temp);
            }
            in.clear();
            in.ignore(size, '\n');
            time = temp;
            success = true;
        }
        catch(int temp){
            cout << "Please only enter a number." << endl;
        }
    }
}


//virtual update function that allows user to update fields
void app::update(char append[]){
    char choice = 'o';//variable used to get user decisions about paid and recommend
    char *temp = new char[strlen(history) + strlen(append) + 3];//creat a char * that is the size of the current history plus the amount to append + the ,
    sprintf(temp, "%s, %s", history, append);//uses the cstring library format function to inser t a ',' and append the history char * with the updates
    if(history){
        delete[] history;
        history = NULL;
    }
    //deletes old history, allocates the new required space and copys in the newly formated temp string to history
    history = new char[strlen(temp) + 1];
    strcpy(history, temp);
    delete[] temp;//delete temp memory;
    cout << "Would you recommend this app?(y/n): ";
    cin >> choice;
    cin.clear();
    cin.ignore(size, '\n');
    if(choice == 'y' || choice =='Y'){
        recommend = true;
    }
    else{
        recommend = false;
    }
    cout << "Have you purchased this app?(y/n): ";
    cin >> choice;
    cin.clear();
    cin.ignore(size, '\n');
    if(choice == 'y' || choice =='Y'){
        paid = true;
    }
    else{
        paid = false;
    }

}


//virtual gameApp update that prompts for new info and calls base class to append history and updates its fields
void gameApp::update(char append[]){
    char temp[size];
    int score = 0;
    bool success = false;
    cout << "What are the new tips? ";
    cin.getline(temp, size, '\n');
    //while try loop ensures input is of type int
    while(!success){
        try{
            cout << "What is your high score?: ";
            cin >> score;
            if(!cin){
                cin.clear();
                cin.ignore(size, '\n');
                throw(score);//throw score if cin failed
            }
            highScore = score;
            success = true;
        }
        catch(int score){
            cout << "Please only enter a number." << endl;
        }
    }
    app::update(temp);//calls base class update with char[] to append history
    if(tips){
        delete[] tips;
        tips = NULL;
    }
    tips = new char[strlen(temp) + 1];
    strcpy(tips, temp);

}


//virtual weatherApp update that prompts for new info and calls base class to append history and updates its fields
void weatherApp::update(char append[]){
    char temp[size];
    cout << "What are your new weather comments? ";
    cin.getline(temp, size, '\n');
    cout << "Updating current temperature....\n";
    this->temp = rand()%80;//pretends that it knows what the temperature outside is
    app::update(temp);//updates history with activity made
    if(conditions){
        delete[] conditions;
        conditions = NULL;
    }
    conditions = new char[strlen(temp) + 1];
    strcpy(conditions, temp);
}


//virtual studyApp update that prompts for new info and calls base class to append history and updates its fields
void studyApp::update(char append[]){
    char temp[size];
    int hours = 0;
    bool success = false;
    cout << "What are your new study schedule details? ";
    cin.getline(temp, size, '\n');
    while(!success){
        try{
            cout << "How many hours have you spent studying since your last update?: ";
            cin >> hours;
            if(!cin){
                cin.clear();
                cin.ignore(size, '\n');
                throw(hours);
            }
            cin.clear();
            cin.ignore(size, '\n');
            time= hours;
            success = true;
        }
        catch(int score){
            cout << "Please only enter a number." << endl;
        }

    }
    app::update(temp);//updates history in base class
    if(schedule){
        delete[] schedule;
        schedule = NULL;
    }
    schedule = new char[strlen(temp) + 1];
    strcpy(schedule, temp);
}


//virtual display used by overloaded << takes an ostream object as an argument
void app::display(ostream& obj)const{
    obj << "App name: " << appName << '\n'
         << "_______________________________________________" << '\n'
         << "History: " << history << '\n'
         << "What the app does: " << function << '\n'
         << "Recommendation: "; if(recommend){cout << "Yes\n";}else{cout << "No\n";}
     obj << "Paid for the app?: "; if(paid){cout << "Yes\n";}else{cout << "No\n";}

}


//virtual displays for derived classes that call base class display before displaying their own data//
void gameApp::display(ostream& obj)const{
    app::display(obj);
    obj << "Advice/tips: " << tips << '\n'
        << "High Score: " << highScore << '\n'
        << "Application Type: Game App." << endl;

}


void weatherApp::display(ostream& obj)const{
    app::display(obj);
    obj << "Conditions: " << conditions << '\n'
        << "Temp: " << temp << '\n'
        << "Application Type: Weather App." << endl;
}


void studyApp::display(ostream& obj)const{
    app::display(obj);
    obj << "Study schedule: " << schedule << '\n'
        << "Time spent studying: " << time << '\n'
        << "Application Type: Study App." << endl;

}


//insert functionc alled by red black with the app to be inserted as an arg: to_add. 
app* app::insert(app*&root, app*&to_add){
    char temp[size];//temp used for converting first letter to capital so that the tree stays sorted regardless of app name starting with an uppercase letter or not
    char t;//character used in temp string so that all first letters are measure to be capital for consistent alphabetical insertion
    if(!root){
        app *temp = NULL;//temp is used to catch the return value of fixViolation. If that return value is not null, then it is the new root and returned to the red black tree
        root = to_add;//assumes ownership of the memory
        temp = fixViolation(root);//calls fixViolation on new addition
        to_add = NULL;//severs other ownerships and ensures memory is only pointed to by one location
        return temp;//return temp pointer to caller, if not null, root will be updated
    }
    strcpy(temp, to_add->appName);
    t = toupper(temp[0]);//return the uppper case equivilent of the name to be added, compare this string to find correct place to add the object 
    temp[0] = t;
    if((*to_add) == (*root)){
        cout << "No duplicates allowed." << endl;//rejects duplicate apps
        return NULL;
    }
    //update root as we go
    if(strcmp(temp, root->appName)<0){
        to_add->parent = root;//update passed in objects parent as we recurse
        insert(root->left, to_add);
    }
    else{
        to_add->parent = root;
        insert(root->right, to_add);
    }
}


//recursive violation fix for a red-black balanced tree, this starts by correcting the violation at the node, and then bubbling up to see if any other violations were created, after fixing the previous
app* app::fixViolation(app*& check){
    //first base case is if check has a null parent, then it is the new root and it's color is switched to black, and it it is returned back to caller
    if(!check->parent){
        check->color = black;
        return check;
    }
    //second base case is that the parent color is black and there is no violation
    if(check->parent->color == black){
        return NULL;
    }
    app *grand = check->parent->parent;//temp pointer to watch grand parent node
    app *grab = check->parent;//temp pointer set to current objects parent
    if(grand){
        //first if block handles the cases where our parent is a right child of its parent
        if(grand->right == check->parent){
            app *uncle = grand->left;//"uncle" pointer, which in this case will always be the grand parents left child
            //if uncle is red then we make uncle and parent black, and switch grandparent to red. we then return grandparent so that the function can check that it is not breaking the rules from there up
            if(uncle && uncle->color == red){
                uncle->color = black;
                check->parent->color = black;
                grand->color = red;
                return fixViolation(grand);
            }
            else{//else then uncle is black and we need to rotate (null pointers are treated as black
                //we are in the scope of having a right oriented parent from grandparent, so if we are on the left of our parent (not a straight line) we must first rotate to straighten out
                //with a right rotation on our parent. The "grab" variable will be updated with the new "root" of our mini tree after rotation
                if(check->parent->left==check){
                    grab = shiftRight(grab);   
                }
                //the colors of grab and gran parent our swapped, grab is either checks parent or check depending on if a previous rotation happened
                bool grabcolor = grab->color;
                bool grandcolor = grand->color;
                grab->color = grandcolor;
                grand->color = grabcolor;
                grab = shiftLeft(grand);//grandparent is shifted left and grab will become the "root" of the shifted section of the tree. this is the value that is returned to search for further violations
                return fixViolation(grab);

            }

        }
        //if checks parent is the left child of its parent then we do the same logic but mirrored
        if(grand->left == check->parent){
            app *uncle = grand->right;
            if(uncle && uncle->color == red){
                uncle->color = black;
                check->parent->color = black;
                grand->color = red;
                return fixViolation(grand);
            }
            else{
                if(check->parent->right==check){
                    grab = shiftLeft(grab);
                }
                bool grabcolor = grab->color;
                bool grandcolor = grand->color;
                grab->color = grandcolor;
                grand->color = grabcolor;
                grab = shiftRight(grand);
                return fixViolation(grab);
            }
        }

    }
}


//shiftRight function that rotates a tree or sub-tree to the right
//this function is always called with either a parent node or grandparent, thus "temp" will always be an exsisting node
app* app::shiftRight(app*& move){
    app *temp = move->left;//temp set to the left of the node we are shifting
    move->left = temp->right;//the node we are shifting to the right will adopt temps right if it has one
    //if move has adopted a subtree, that objects parent is updated to point to move
    if(move->left){
        move->left->parent = move;
    }
    //temp will be shifted up to the right and be at the top of this rotation when we are done. it's parent will become the object we are moving parent
    temp->parent = move->parent;
    //temp->right = move;
    if(move->parent == NULL){
        temp->right = move;
        move->parent = temp;
        return temp;
        //then temp will become the new root of the tree
    }
    //checks the relationship of the object we are moving with its parent, so we know which pointer to update on temp
    else if (move == move->parent->left){
        move->parent->left = temp;
    }
    else{
        move->parent->right = temp;
    }
    temp->right = move;//set temps right to point to its new right (the node we moved)
    move->parent = temp;//move is shifted down and now its parent becomes temp
    return temp;//returns temp to caller, this value will be recursed on
}


//just like the right shift but mirrored
app* app::shiftLeft(app*& move){
    app *temp = move->right;
    move->right = temp->left;
    if(move->right){
        move->right->parent = move;
    }
    //temp->left = move;
    temp->parent = move->parent;
    if(move->parent == NULL){
        temp->left = move;
        move->parent = temp;
        return temp; //then temp will become the new root
    }
    else if(move->parent->left == move){
        move->parent->left = temp;
    }
    else{
        move->parent->right = temp;
    }
    temp->left = move;
    move->parent = temp;
    return temp;
    
}


//function to delete every node in the tree
void app::destroy(app*& root){
    if(!root){
        return;
    }
    destroy(root->left);
    destroy(root->right);
    delete root;
    root = NULL;
}


//universal traversal function that will return a pointer if the desired keyword is found within the c-strings: appName, function, or history
app* app::traverse(app*root, char key[], app*& flag){
    bool check = false;//check used to check the success of a keyword search
    if(!root){
        return NULL;
    }
    char*temp = NULL;
    temp = root->appName;
    check = keyword(temp, key);//calls keyword function in the appName field and looks for a match
    temp = NULL;
    if(check){
        flag = root;
        return flag;//flag reference pointer used as arg to deal with behavior involving an additional iteration after the return statement. 
    }
    temp = root->history;
    check = keyword(temp, key);//checks history field for keyword match within cstring
    temp = NULL;
    if(check){
        flag = root;
        return flag;
    }
    temp = root->function;
    check = keyword(temp, key);//checks function field for keyword match
    temp = NULL;
    if(check){
        flag = root;
        return flag;
    }
    if(flag){
        return flag;//returns desired pointer to caller to be operated on
    }
    traverse(root->left, key, flag);
    traverse(root->right, key, flag);
}


//first keyword recursive function that checks the keyword starting at each character in a cstring, if the key is longer than the string==false
bool app::keyword(char* parse, char key[]){
    bool check = false;//check used to grab value of second search function
    if(strlen(key) > strlen(parse)){
            return false;
    }
    int i = 0;
    check = keyword2(parse, key, strlen(key), i);//keyword2 looks for a match within strings
    if(check){
        return 1;//if check is true success is reported back to caller
    }
    return keyword(++parse, key);//advances the string to be searched by one and then looks for a match again (looking for the match within every word)

}


//keyword to iterates -length of key- amount of times. If every character in that timespan matches, it returns true
bool app::keyword2(char* parse, char key[],int length, int& i){
    if(i == length){
        return true;//length of key was achieved without returning false, search is true
    }
    if(toupper(parse[i]) == toupper(key[i])){
        //compares each element upto length starting at parse[0] to upper makes the comparison not case sensitive
        ++i;
        return keyword2(parse, key, length, i);
    }
    return false;//as soon as a char is false, return
}


//displays all apps
int app::displayAll(app*root){
    int total = 0;
    if(!root){
        return 0;
    }
    ++total;
    total += displayAll(root->left);
    cout << (*root) << endl;//overloaded <<
    total += displayAll(root->right);
    return total;
}


//returns the height of the tree
int app::height(app*root){
    if(!root){
        return 0;
    }
    int l = height(root->left);
    int r = height(root->right);
    if(l > r){
        return(l + 1);
    }
    else{
        return(r + 1);
    }
}


//this function is called by the redblack copy constructor
void app::copy(app*&dest, app* source, app*&root){
    if(!source){
        return;
    }
    //RTTI used to make the correct node for the copied red-black tree
    gameApp *try1 = dynamic_cast<gameApp*>(source);
    weatherApp *try2 = dynamic_cast<weatherApp*>(source);
    studyApp *try3 = dynamic_cast<studyApp*>(source);
    if(try1){
        dest = new gameApp(*try1);
    }
    if(try2){
        dest = new weatherApp(*try2);
    }
    if(try3){
        dest = new studyApp(*try3);
    }
    dest->insert(root, dest);//calls insert to correctly link up parent pointers for new tree 
    copy(dest->left, source->left, root);
    copy(dest->right, source->right, root);
}










