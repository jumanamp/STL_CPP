/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby,
C#, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>

using namespace std;

//#define USE_VECTOR
#define USE_LIST

class guest{
public:
    guest(){};
    ~guest(){};
    void set_gender(string name){
        char start = name.c_str()[0];// not the c_str()
        if (start == 'i' or start == 'B' or start == 'm' or start == 'M') {
            gender = "Boy";
        }
        else{
            gender = "Girl";
        }
    }
    string gender;
    string name;
    int age;
};

#ifdef USE_VECTOR
    typedef vector<guest> guest_data;
#elif defined USE_LIST
    typedef list<guest> guest_data;
#endif

void read_guest_file(guest_data& data) {
    ifstream in_file("guest.txt");
    string line;
    if (in_file.is_open()){
        guest tmp; // locally used, we are ok with it being destroyed once function exists. so statically initialized
        while (getline(in_file, line)) {
            tmp.name = line;
            getline(in_file, line);
            tmp.gender =  line;
            getline(in_file, line);
            tmp.age = stoi(line);
            data.push_back(tmp);
        }
        in_file.close();
    }
    else {
        cout << "file not opened properly" << endl;
    }
}

void print_guests(guest_data& data){
    // use iterator, note iterator returns pointer
    auto it = data.begin();
    while(it != data.end()) { // < can be used only for vector because it can
                              // randm=only accessed, fails for list, so !=
        cout << "Name: " << it->name <<endl;
        cout << "Gender: " << it->gender <<endl;
        cout << "Age: " << it->age<<endl;
        it++; // it + =1 fails for list as not randomly accessible.
    }

    cout<<"end of data" << endl;
}

void print_guest(guest& data){
    cout << "Name: " << data.name <<endl;
    cout << "Gender: " << data.gender <<endl;
    cout << "Age: " << data.age<<endl;
}

bool get_guest(guest_data& data, int index, guest& sel){
    // cant use[] operator as size is not known.
    auto it = data.begin();
    for(int i=0; i<index; i++, it++) {//Note the iterator increment, also ,
        if(it == data.end())
            return false;
    }
    sel = *it; // sel is object location, so value of pointer.
    return true;
}

bool remove_guest(guest_data& data, int index){
    auto it = data.begin();
    for(int i=0; i<index; i++, it++) {
        if(it == data.end())
            return false;
    }
    data.erase(it); // note erase function
    return true;
}

float get_av_age(guest_data& data, float& av_age){
    auto it = data.begin();
    av_age = 0.0;
    for(guest g: data)//look at the iterator style like in python
        av_age+=g.age;
    av_age= av_age/data.size();//can use size directly
    return av_age;
}

int main()
{
    printf("Beginning test");
    guest_data guests; // other solution is dynamically allocate with new
                       // if new used then memory stays until freed.
                       // Then functions called can take pointer variable.
                       // If pointers then values accessed by ->
    read_guest_file(guests);
    // Print guest at index 1
    guest sel_guest;
    bool get = get_guest(guests,0, sel_guest);
    if (get){
        cout << "Printing found guest 1"<<endl;
        print_guest(sel_guest);
    }
    else{
        cout << "False"<<endl;
    }
    //Remove guest at index 1
    print_guests(guests);
    bool rem = remove_guest(guests,0);
    cout << "Printing after removing guest 1"<<endl;
    print_guests(guests);
    float av_age = get_av_age(guests, av_age);
    cout << "Average Age: "<<av_age<<endl;
    return 0;
}
