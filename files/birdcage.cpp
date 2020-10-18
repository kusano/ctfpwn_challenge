//  g++ birdcage.cpp -o birdcage -std=c++17 -no-pie
#include <iostream>
#include <string>
#include <typeinfo>
#include <unistd.h>
using namespace std;

void setup()
{
    alarm(60);
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}

struct Bird {
    string name() {return typeid(*this).name();};
    virtual void sing() = 0;
    virtual ~Bird() = default;
};

struct Cock: Bird {
    void sing() override {cout<<"Cock-a-doodle-doo!"<<endl;}
};

struct Owl: Bird {
    void sing() override {cout<<"Hoot! Hoot!"<<endl;}
};

class Parrot: public Bird {
    string memory;
public:
    Parrot() {
        cout<<"Talk to: ";
        cin>>memory.data();
    }
    void sing() override {cout<<memory.c_str()<<endl;}
};

Bird *cage[4];

void capture() {
    int index;
    string name;
    cin>>index>>name;
    if (index<0 || 4<=index)
        return;
    if (cage[index]!=nullptr)
        delete cage[index];
    Bird *bird = nullptr;
    if (name=="cock")   bird = new Cock();
    if (name=="owl")    bird = new Owl();
    if (name=="parrot") bird = new Parrot();
    cage[index] = bird;
}

void sing() {
    int index;
    cin>>index;
    if (index<0 || 4<=index)
        return;
    if (cage[index]!=nullptr)
        cage[index]->sing();
}

void release() {
    int index;
    cin>>index;
    if (index<0 || 4<=index)
        return;
    delete cage[index];
    cage[index] = nullptr;
}

void list() {
    for (int i=0; i<4; i++) {
        cout<<i<<": ";
        if (cage[i]!=nullptr)
            cout<<cage[i]->name();
        cout<<endl;
    }
}

int main()
{
    setup();

    cout<<"Birdcage"<<endl;
    cout<<"  capture <index> cock|owl|parrot"<<endl;
    cout<<"  sing <index>"<<endl;
    cout<<"  release <index>"<<endl;
    cout<<"  list"<<endl;
    cout<<"  exit"<<endl;

    while (true) {
        cout<<"> ";
        string cmd;
        cin>>cmd;
        if (cmd=="capture") capture();
        if (cmd=="sing")    sing();
        if (cmd=="release") release();
        if (cmd=="list")    list();
        if (cmd=="exit")    break;
    }
}
