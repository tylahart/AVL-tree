
#include <iostream>
#include <sstream>
#include <cmath>
#include <vector>
#include <cctype>
using namespace std;
#include <bits/stdc++.h>



struct Node {
public:
    Node*left = nullptr;
    Node*right = nullptr;
    string name;
    int id;
    Node(){};
    Node(string name, int id){
        this->name = name;
        this->id = id;
    };
    ~Node()= default;
};


class AVL {
private:
public:
    int node_count = 0; // total number of nodes in the tree
    int iteration = 0; // used for remove_Inorder() function
    int count = 0; //search
    Node*root = nullptr;
    //constructor
    AVL(){}
    vector<int>id_list;
    int find_height(Node*root){
        if (root == nullptr){
            return 0;
        }
        return max(find_height(root->left), find_height(root->right))+1;
    }
    bool balanced(Node*r){ //helper function to see if the tree is balanced
        if (r == nullptr){
            return true;
        }
        int l_height = find_height(r->left);
        int r_height = find_height(r->right);
        if (abs(l_height - r_height) <= 1 && balanced(r->left) && balanced(r->right)){
            return true;
        }
        return false;
    }
    Node* rotate_left(Node*t){
        Node* right_child = t->right;
        t->right = right_child->left;
        right_child->left = t;
        return right_child;
    }
    Node* rotate_right(Node*y){
        Node* left_child = y->left;
        y->left = left_child->right;
        left_child->right = y;
        return left_child;
    }
    Node* rotate_lr(Node*l){
        l->left = rotate_left(l->left);
        return rotate_right(l);
    }

    Node* rotate_rl(Node*a){
        a->right = rotate_right(a->right);
        return rotate_left(a);
    }

    Node* insert_NAME_ID(Node*r, Node*x){ //will insert node into tree based on id value
        if (r == nullptr){
            r = x;
            node_count++;
            return r;
        }
        if (r->id < x->id){
            r->right = insert_NAME_ID(r->right, x);
        }
        else{
            r->left = insert_NAME_ID(r->left, x);
        }
        if(!balanced(root)) {
            int parent_bf;
            int left_child_bf = 0;
            int right_child_bf = 0;
            parent_bf = find_height(r->left) - find_height(r->right);
            if (r->left != nullptr) {
                Node *inter = r->left;
                left_child_bf = find_height(inter->left) - find_height(inter->right);
            }
            if (r->right != nullptr) {
                Node *inter = r->right;
                right_child_bf = find_height(inter->left) - find_height(inter->right);
            }
            if (parent_bf == 2 && left_child_bf == 1) { // balancing the tree
                //right rotation
                r = rotate_right(r);
            }
            else if (parent_bf == -2 && right_child_bf == -1) {
                //left rotation
                r = rotate_left(r);
            }
            else if (parent_bf == 2 && left_child_bf == -1) {
                //left right rotation
                r = rotate_lr(r);
            }
            else if (parent_bf == -2 && right_child_bf == 1) {
                //right left rotation
                r = rotate_rl(r);
            }

        }
        return r;
    }


    Node* remove_ID(Node*root, const int& id_num){ // will remove node of a specific id from tree
        Node* node = root;
        if (id_num == node->id){
            if (node->left == nullptr && node->right == nullptr){
                delete node;
                node_count--;
                return nullptr;
            }
            else if(node->left == nullptr){
                Node*replace = node->right;
                delete node;
                node_count--;
                return replace;
            }
            else if(node->right == nullptr){
                Node*replace = node->left;
                delete node; //coverts node back to default/null
                node_count--;
                return replace;
            }
            else{
                Node* min = node->right;
                while(min->left != nullptr){
                    min = min->left;
                }
                node->id = min->id;
                node->name = min->name;
                node->right = remove_ID(node->right, node->id);
            }
        }
        else{
            if (id_num < node->id){
                node->left = remove_ID(node->left, id_num);
            }
            else if (id_num > node->id){
                node->right = remove_ID(node->right, id_num);
            }
        }
        return root;
    }

    bool search_ID(const int& id_num){ //checks to see if there is a node with specified id number
        Node* node = root;
        if (root == nullptr){
            cout << "unsuccessful" << endl;
            return false;
        }
        else{
            bool continuing = true;
            while(continuing) {
                if (id_num == node->id) {
                    cout << node->name << endl;
                    return true;
                }
                if (id_num < node->id) {
                    node = node->left;
                }
                else {
                    node = node->right;
                }
                if (node == nullptr){
                    cout << "unsuccessful" << endl;
                    continuing = false;
                    return false;
                }
            }
        }
    }

    void search_NAME(Node* node,const string& name_check){
        if (root == nullptr){
            cout << "unsuccessful" << endl;
            return;
        }
        if (node == nullptr){
            return;
        }
        if (name_check == node->name){
            cout << node->id << endl;
            count++;
        }
        iteration++;
        if (iteration == node_count && count == 0){ // checks to see if the end of tree has been reach and if name wasn't found once
            cout << "unsuccessful" << endl;
            iteration = 0;
            count = 0;
        }
        search_NAME(node->left, name_check);
        search_NAME(node->right, name_check);
    }
    string all_words;
    void actually_print(string finish){
        finish = finish.substr(0, finish.size()-2);
        cout << finish << endl;
        all_words = "";
    }
    void printInorder(Node*r){
        if (r == nullptr){
            return;
        }
        printInorder(r->left);
        all_words.append(r->name);
        all_words.append(", ");
        printInorder(r->right);
    }

    void printPreorder(Node*r){
        if (r == nullptr){
            return;
        }
        all_words.append(r->name);
        all_words.append(", ");
        printPreorder(r->left);
        printPreorder(r->right);
    }

    void printPostorder(Node*r){
        if (r == nullptr){
            return;
        }
        printPostorder(r->left);
        printPostorder(r->right);
        all_words.append(r->name);
        all_words.append(", ");
    }

    void printLevelCount(Node*root){ //uses root height to print the number of levels
        if (root == nullptr){
            cout << "0" << endl;
        }
        else{
            cout << find_height(root) << endl;
        }
    }
    vector<int>to_remove;
    void removeInorder(Node*r, const int N){
        if (r == nullptr){
            return;
        }
        removeInorder(r->left, N);
        if(iteration == N){
            to_remove.push_back(r->id);
            return;
        }
        iteration++;
        removeInorder(r->right, N);
    }

    bool existing(int ID){
        for (int check : id_list){
            if (check == ID){
                return true;
            }
        }
        return false;
    }
};

bool all_characters(string name){ // checks to see if the name is only characters and spaces
    for (char l : name){
        if(!isalpha(l) && !isspace(l)){
            return false;
        }
    }
    return true;
}

int main() {

    AVL avl;

    int num;
    //command format: "insert NAME ID"
    string num_lines;
    getline(cin, num_lines);
    num = stoi(num_lines);

    for (int i = 0; i < num;  i++){
        string line;
        getline(cin, line);
        istringstream in(line);
        string cmd;
        in >> cmd;
        if (cmd == "insert"){
            string buffer;
            getline(in, buffer, '"'); // creates buffer between the command and name string, the quotation mark
            string name;
            getline(in, name, '"');
            char id[8];
            in >> id;
            int ID = stoi(id);
            if (all_characters(name) && (log10(ID) >= 7 && log10(ID) < 8) && !avl.existing(ID)){
                cout << "successful" << endl;
                avl.id_list.push_back(ID);
                Node* person = new Node(name, ID);
                avl.root = avl.insert_NAME_ID(avl.root, person);
            }
            else if (id[0] == '0'){
                id[0] = '1';
                ID = stoi(id);
                if (all_characters(name) && (log10(ID) >= 7 && log10(ID) < 8) && !avl.existing(ID)){
                    id[0] = '0';
                    ID = stoi(id);
                    cout << "successful" << endl;
                    avl.id_list.push_back(ID);
                    Node* person = new Node(name, ID);
                    avl.root = avl.insert_NAME_ID(avl.root, person);
                }
            }
            else{
                cout << "unsuccessful" << endl;
                continue;
            }
        }
        else if (cmd == "remove"){
            int ID;
            in >> ID;
            if (!avl.existing(ID)){
                cout << "unsuccessful" << endl;
                continue;
            }
            else{
                cout << "successful" << endl;
                avl.remove_ID(avl.root, ID);
            }
        }
        else if (cmd == "search"){
            char unknown[8];
            in >> unknown;
            if (isdigit(unknown[0])){ //checks to see if we are dealing with an id number or name
                string newnum = reinterpret_cast<const char *>(unknown);
                int id_search = stoi(newnum);
                avl.search_ID(id_search);
            }
            else{
                string newword = reinterpret_cast<const char *>(unknown);
                newword = newword.substr(1, newword.size() - 2);
                avl.count = 0;
                avl.search_NAME(avl.root, newword);
            }
        }
        else if (cmd == "printInorder"){
            avl.all_words = "";
            avl.printInorder(avl.root);
            avl.actually_print(avl.all_words);
            avl.all_words = "";
        }
        else if (cmd == "printPreorder"){
            avl.printPreorder(avl.root);
            avl.actually_print(avl.all_words);
            avl.all_words = "";
        }
        else if (cmd == "printPostorder"){
            avl.printPostorder(avl.root);
            avl.actually_print(avl.all_words);
            avl.all_words = "";
        }
        else if (cmd == "printLevelCount"){
            avl.printLevelCount(avl.root);
        }
        else if (cmd == "removeInorder"){
            int node_remove;
            in >> node_remove;
            if (node_remove > avl.node_count-1){
                cout << "unsuccessful" << endl;
            }
            else{
                avl.removeInorder(avl.root, node_remove);
                avl.remove_ID(avl.root, avl.to_remove[0]);
                cout << "successful" << endl;
            }
            avl.iteration = 0;
            avl.to_remove.clear();
        }
        else{
            cout << "unsuccessful" << endl; //in case a command was said that does not exist
        }

    }



    return 0;
}
