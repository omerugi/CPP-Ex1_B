#include <iostream>
#include <string>
#include "FamilyTree.hpp"
#define COUNT 10

using namespace std;
using namespace family;

void Node::set_father(string name){
    if(name == "null"){
        father = nullptr;

    }else{
        this->father = new Node(name);

    }

}
void Node::set_mother(string name){

    if(name == "null"){
        mother = nullptr;

    }else {
        this->mother = new Node(name);
    }

};

Node* Node:: get_father(){ return this->father;};
Node* Node:: get_mother(){ return this->mother;};

string Node::relation(int grand,string name) {

    string temp=my_name;
    if((grand==0)&&(my_name==name)){
        return "me";
    }
    string ans="";
    if(father&&(*father).my_name==name){
        for (int i=0;i<grand;i++){
            if(i!=grand-1)
                ans+="great-";
            else
                ans+="grand";
        }
        ans+="father";
        return ans;
    }
    else if(mother&&(*mother).my_name==name){
        for (int i=0;i<grand;i++){
            if(i!=grand-1)
                ans+="great-";
            else
                ans+="grand";

        }
        ans+="mother";
        return ans;
    }
    if((!mother)&&(!father))
        return "unrelated";

    string relate="unrelated";

    if(father) {
        relate = this->father->relation(grand+1, name);
    }
    if(relate=="unrelated"&&mother){
        relate = this->mother->relation(grand+1, name);
    }
    return relate;

}

string Node::get_name() {
    return this->my_name;
}

Tree& Tree::addFather(string name ,string dad){

    Node* temp = find_by_name(&root,name);
    if(temp == nullptr || temp->get_father() != nullptr){
        throw runtime_error(name+" was not found");
    }
    temp->set_father(dad);

    return *this;
}

Tree& Tree::addMother(string name ,string mom){

    Node* temp = find_by_name(&root,name);
    if(temp == nullptr || temp->get_mother() != nullptr){
        throw runtime_error(name+" was not found");
    }

    temp->set_mother(mom);
    //cout<<temp->get_name();

    return *this;
};
void Tree:: display(){

    this->print2DUtil(&this->root,0);

};

void Tree::print2DUtil(Node *root, int space)
{
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    print2DUtil(root->get_mother(), space);

    // Print current node after space
    // count
    cout<<endl;
    for (int i = COUNT; i < space; i++)
        cout<<" ";
    cout<<root->get_name()<<"\n";

    // Process left child
    print2DUtil(root->get_father(), space);
}


string Tree::relation(string name){
    return this->root.relation(0,name);
};
string Tree::find(string name){

    if(name == "me"){ return this->root.get_name();}
    else if(this->root.get_father() && name == "father" ){
        return this->root.get_father()->get_name();
    } else if(this->root.get_mother() != NULL && name == "mother" ){
        return this->root.get_mother()->get_name();
    }else if(!this->root.get_father() && name == "father" ){
        throw runtime_error(name + " no have");
    }else if(this->root.get_mother() != NULL && name == "mother" ){
        throw runtime_error(name + " no have");
    }

    string a,b;
    if(this->root.get_father()){
        a = rec_find(this->root.get_father(),name);
        if(a != "x") return a;
    }
    if(this->root.get_mother()){
        b=rec_find(this->root.get_mother(),name);
        if(b != "x") return b;

    }

    throw runtime_error("The tree cannot handle the "+name +" relation");

};
void Tree::remove(string name){

    if(name == this->root.get_name()){
        throw runtime_error(name+" is root");
    }

    Node* temp = find_by_name_remove(&root,name);
    if(!temp){
        throw runtime_error(name+" not found");
    }
    rec_remove(temp);

}

string Tree::rec_find(Node* root,string name) {

    if(root == NULL){
        return "x";
    }

    if((int)name.find('-') == -1){

        if((int)name.find("father") != -1 && root->get_father()){
            return root->get_father()->get_name();
        }
        if((int)name.find("mother") != -1 && root->get_mother()){
            return root->get_mother()->get_name();
        }
        else
            return "x";
    }

    int index = name.find('-');
    index++;
    int len = name.length();

    if(rec_find(root->get_father(),name.substr(index,len)) != "x"){
        return rec_find(root->get_father(),name.substr(index,len));
    } else if(rec_find(root->get_mother(),name.substr(index,len)) != "x" ){
        return rec_find(root->get_mother(),name.substr(index,len));
    }

    return "x";
}

void Tree::rec_dis(Node *root) {

    if(root == NULL){
        return;;
    }

    string f="",m="";
    if(root->get_father()){
        f= root->get_father()->get_name();
    }
    if(root->get_mother()){
        m = root->get_mother()->get_name();
    }

    rec_dis(root->get_father());

    rec_dis(root->get_mother());

}



Node *Tree::find_by_name(Node* node, string name) {
    if(node == NULL){
        return nullptr;
    }

    if(node->get_name() == name){
        return node;
    }
    else if(node->get_father() && node->get_father()->get_name() == name){
        return node->get_father();
    }
    else if(node->get_mother() && node->get_mother()->get_name() == name){
        return node->get_mother();
    }

    Node* a = find_by_name(node->get_father(),name);
    Node* b = find_by_name(node->get_mother(),name);
    if(a) {
        return a;
    }
    if(b) {
        return b;
    }

    return nullptr;
}

void Tree::rec_remove(Node *root) {

    if(root->get_father() == nullptr && root->get_mother()== nullptr){
        delete(root);
        return;
    }

    if(root->get_father() != nullptr){
        rec_remove(root->get_father());
    }

    if(root->get_mother() != nullptr){
        rec_remove(root->get_mother());
    }

    root = nullptr;
}

Node *Tree::find_by_name_remove(Node *node, string name) {

    if(node == NULL){
        return nullptr;
    }

    if(node->get_name() == name){
        return node;
    }
    else if(node->get_father() && node->get_father()->get_name() == name){
        Node* temp = node->get_father();
        node->set_father("null");
        return temp;
    }
    else if(node->get_mother() && node->get_mother()->get_name() == name){
        Node* temp = node->get_mother();
        node->set_mother("null");
        return temp;
    }


    Node* a = find_by_name_remove(node->get_father(),name);
    Node* b = find_by_name_remove(node->get_mother(),name);
    if(a) {
        return a;
    }
    if(b) {
        return b;
    }

    return nullptr;


};

