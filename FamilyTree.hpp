//
// Created by omerugi on 04/04/2020.
//

#include <iostream>
#include <string>


using namespace std;

namespace family{

    class Node{
        string my_name;
        Node *father,*mother;
    public:

        Node(string &name) : my_name(name), father(nullptr),mother(nullptr) {};
        string get_name();
        void set_father(string name);
        void set_mother(string name);
        Node* get_father();
        Node* get_mother();
        string relation(int grand,string name);

    };

    class Tree{
    private:
        Node root;

    public:

        Tree(string name): root(name){};
        Tree& addFather(string name ,string dad);
        Tree& addMother(string name ,string dad);
        void display();
        void print2DUtil(Node *root, int space);
        string relation(string name);
        string find(string name);
        void remove(string name);
        string rec_find(Node* root,string basicString);

        void rec_dis(Node *pNode);

        Node *find_by_name(Node* node, string basicString);

        void rec_remove(Node *pNode);

        Node *find_by_name_remove(Node *pNode, string basicString);
    };
}



