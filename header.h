//Joe Leland
//Sources: https://www.geeksforgeeks.org/red-black-tree-set-2-insert/, https://www.cs.auckland.ac.nz/software/AlgAnim/red_black.html, http://staff.ustc.edu.cn/~csli/graduate/algorithms/book6/chap14.htm
//https://en.wikipedia.org/wiki/Red%E2%80%93black_tree
//This module contains all class definitions and prototypes. App is the indirect abstract base class for weatherApp, gameApp, and studyApp. An additional class, named redBlack, manages a red-black tree to store all of the data.
//The program starts by creating a redBlack object and loading in some apps from a txt file, into the tree. The fields from the app were produced by the website mockaroo and are mosstly meaningless. The program can be used to manage
//the apps by updating them, adding new ones, and displaying them all. A singular deletion function was not required for the red-black tree. When ever an app is updated, the updated char string is appened to the history char *, 
//seperated by a ',' to show all previous actions. All searches are done by getting a desired key word from the user (not case sensitive) and returning that app to the caller if it is a match.

#include <iostream>
#include <cstring>
#include <ctime>
#include <fstream>
#include <cctype>
using namespace std;
const int size = 500;//const global size used for temp char strings
enum{black, red};//enum for red black, black = 0, red = 1 by default


class app{
    public:
        app();
        virtual ~app();//virtual default constructor
        app(char[], char[], char[], bool, bool);//constructor that takes char[] appName, char[] history, char[] function, bool recommend, bool paid
        app(const app&);//copy constructor
        app* traverse(app*, char key[], app*&);//universal search function that returns the pointer of the desired node
        app* insert(app*&, app*&to_add);//insert function that returns a pointer IF that pointer is to be the new root of the redBlack class
        app* fixViolation(app*&);//recursive function to correct violations that occur when inserting nodes, returns pointer if redBlack head needs to be updated
        app* shiftRight(app*&);//function to shift sub tree right, returns pointer to be recursed on by fixViolations function
        app* shiftLeft(app*&);//function to shift sub tree left, returns pointer to be recursed on by fixViolations function
        bool keyword(char*, char[]);//recursive function to search for keyword matches in a cstring, starts at first character of array and calls keyword2, returns true if substring matches
        bool keyword2(char*, char[], int, int&);//recurses through the substring key[] length amount of times, returning true if every character in that length matches
        void destroy(app*&);//deletes the entire tree
        int displayAll(app*root);//displays everything
        int height(app*);//function that returns the height of the tree
        void copy(app*&dest, app*source, app*&);//a function used to copy a red-black tree, redBlack class copyconstructor calls this
        virtual void display(ostream&)const;//virtual display called by the overloaded << operator
        virtual void update(char[]);//virtual function used to update application information, takes a char[] to append the history
        void writeOut(app*, ofstream&);//recursive function to write to an external file
        virtual void write(ofstream&) =0;//pure virtual function to have derived classes write their content to file
        virtual void populate(istream&);//virtual helper function called by the overloaded >> operator that populates the object with data
        bool operator < (const app&)const;//compares two appNames with strcmp
        bool operator > (const app&)const;//compares two appNames with strcmp
        bool operator <= (const app&)const;//compares two appNames with strcmp
        bool operator >= (const app&)const;//compares two appNames with strcmp
        bool operator == (const app&)const;//compares two appNames and returns true is they are the same
        bool operator != (const app&)const;//returns false if appNames are not the same
        virtual app& operator = (const app&);//virtual function that copies app object
        friend ostream& operator<< (ostream&, const app&);//overloaded << displays app objects
        friend istream& operator>> (istream&, app&);//overloaded >> to populate objects

    protected:
        app* right;//left, right, parent pointer to make these act ass the nodes of the tree
        app* left;
        app* parent;
        bool color;//color flag to check for violations in the red black tree
        char * appName;//name of the app
        char * history;//app history
        char * function;//what the app does
        bool recommend;//would the app be recommended
        bool paid;//have you paid for the app
};


//gameApp derived from app
class gameApp:public app{
    public:
        gameApp();
        gameApp(char[], int, char[], char[], char[], bool, bool);//constructor that takes char[]tips, highschore, and all apps args.
        gameApp(const gameApp&);//copy constructor
        ~gameApp();//virtual destructor
        void populate(istream&);
        void display(ostream&)const;//virtual display used by << operator
        void update(char[]);//virtual update, updates information, and appends history
        void write(ofstream&);//virtual file write function
        gameApp& operator = (const gameApp&);//virtual overloaded =
        int operator + (const gameApp&)const;//operator to add highiscores between two apps, residule value is an int
        gameApp& operator += (const gameApp&);//operator to sum two game objects highschores and assign it to the object on the left

    private:
        char *tips;//tips to store tips and advice regarding the game
        int highScore;

};


//weatherApp derived from app
class weatherApp:public app{
    public:
        weatherApp();
        weatherApp(char[], int, char[], char[], char[], bool, bool);//constructor takes char[]conditions, int temp, and all app args 
        weatherApp(const weatherApp&);//copy constructor
        ~weatherApp();//virtual destructor
        void populate(istream&);
        void display(ostream&)const;//virtual display used by overloaded <<
        void update(char[]);//virtual update, updates information, and appends history
        void write(ofstream&);//virtual file write function
        weatherApp& operator = (const weatherApp&);//virtual overloaded = operator
        int operator + (const weatherApp&)const;//operator to add weatherapps together, residule value is their summed temps
        weatherApp& operator += (const weatherApp&);//adds the temps and assigns that value to the weather object on the left

    private:
        char * conditions;//weather conditions/information
        int temp;//temp

};


//studyApp derived from app
class studyApp:public app{
    public:
        studyApp();
        studyApp(char[], int,  char[], char[], char[], bool, bool);//constructor that takes char[] schedule, int time and all other app fields as args
        studyApp(const studyApp&);//copy constructor
        ~studyApp();//virtual destructor
        void populate(istream&);
        void display(ostream&)const;//virtual display used by overloaded <<
        void update(char[]);//virtual update, appends history
        void write(ofstream&);//virtual file write function
        studyApp& operator = (const studyApp&);//virtual overloaded = operator
        int operator + (const studyApp&)const;//oeprator to sum two study apps hours, residule value is an int
        studyApp& operator += (const studyApp&);//sum two apps hours and assigns it to the study objec ton the left

    private:
        char * schedule;//study schedule information
        int time;//time spen studying
};


//class that manages a red-black, self balancing tree
class redBlack{
    public:
        redBlack();//constructor reads in from file and populates the tree with 15 apps.
        ~redBlack();//destructor writes file out and deallocates all memory in the tree
        redBlack(const redBlack&);
        void insert();//insert function prompts user with required information and calls app class insert
        int displayAll();//displayAll calls app class display all
        void update();//update prompts user for required info and then updates the field of app object
        void search();//search allows for user to search for any app using a keyword from any field of that app
        void destroy();//calls app class destroy to delete all nodes in the tree
        int height();//functio to call app class height and return the max depth of the tree.
        void writeOut();//functio to write out tree contents to file

    private:
        app* root;

};




