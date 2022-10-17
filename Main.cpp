#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>
using namespace std;
const unsigned int ALPHABET_SIZE = 26;

// trie node structure
struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];
    string Meaning;
    bool ifEnd;//true if the node is the end node
    char data;
};

struct TrieNode *getNode()// creates new node
{
    struct TrieNode *pNode =  new TrieNode;
    pNode->ifEnd = false;
    for (auto & i : pNode->children)
        i = nullptr;
    return pNode;
}
// Returns true if key presents in trie
bool search(struct TrieNode *root, string key, ofstream &cout2)
{
    struct TrieNode *tempNode = root;
    for (char i : key)
    {
        unsigned int index = i - 'a';
        if (!tempNode->children[index]){
            if(tempNode==root)
                cout2<<'"'<<"no record"<<'"'<<"\n";
            else{
                cout2<<'"'<<"incorrect Dothraki world"<<'"'<<"\n";
            }
            return false;}
        tempNode = tempNode->children[index];}
    if(tempNode->ifEnd){
        cout2<<'"'<<"The English equivalent is " << tempNode->Meaning<<'"'<<"\n";}
    else{
        cout2 << '"'<<"not enough Dothraki word"<<'"'<<"\n";}
    return (tempNode->ifEnd);}
//I used this function to search but not to print anything and using in the display function.
unsigned int search2(struct TrieNode *root, string key,string value)
{
    struct TrieNode *tempNode = root;
    for (char i : key){
        unsigned int index = i - 'a';
        if (!tempNode->children[index])
            return 0;
        tempNode = tempNode->children[index];}
    if(tempNode->ifEnd && tempNode->Meaning!=value){
        return 2;}
    else if(tempNode->ifEnd){
        return 1;}
    else{return 0;}

}

// Returns true if root hasn't any children
bool isEmpty(TrieNode* root)
{
    for (auto & i : root->children){
        if (i)
            return false;}
    return true;}


TrieNode* remove(TrieNode* root, string key,unsigned int ct , ofstream &cout2,unsigned int depth = 0)//delete a key
{
    // If tree is empty
    if (!root) {
        if(depth==1 && ct==0){
            cout2<<'"'<<"no record"<<'"'<<"\n";}
        else if(depth>1 && ct==0){
            cout2<<'"'<<"incorrect Dothraki world"<<'"'<<"\n";}
   return nullptr;
    }
    //last character of key
    if (depth == key.size()) {
        if (root->ifEnd){
            root->ifEnd = false;
            if(ct==0){
            cout2<<'"'<<key<<'"'<< " deletion is successful"<<"\n";}}
        else{
            if(ct==0){
            cout2 << '"'<<"not enough Dothraki word"<<'"'<<"\n";}}
        // If is not prefix of any other word
        if (isEmpty(root)) {
            delete (root);
            root = nullptr;}
        return root;
    }

    // If not last character
    unsigned int index = key[depth] - 'a';
    root->children[index] =
            remove(root->children[index], key, ct,cout2, depth + 1);
    // If root does not have any child and it is not end of another word.
    if (isEmpty(root) && !root->ifEnd) {
        delete (root);
        root = nullptr;}
    return root;}

void insert(struct TrieNode *root, string key,string value,int count, ofstream &cout2)
{
    unsigned int boolCheck=search2(root,key,value);
    if(boolCheck==1){
        cout2<<'"'<<key<<'"'<<" already exist"<<endl;
        return;}
    else if(boolCheck==2){
        remove(root, key,1,cout2);
        count++;
        insert(root,key,value,count,cout2);
    return;}
    struct TrieNode *tempNode = root;
    for (char i : key)
    {
        unsigned int index = i - 'a';
        if (!tempNode->children[index])
            tempNode->children[index] = getNode();
        tempNode = tempNode->children[index];
        tempNode->data=i;}
    tempNode->ifEnd = true;
    tempNode->Meaning=value;
if(count==0){
    cout2<< '"' <<key<< '"' << " was added\n"; }
else if(count==1){
    cout2<< '"' <<key<< '"' << " was updated\n";}}

bool isLeafNode(struct TrieNode* root) //to check if node is leaf
{return root->ifEnd;}

vector<unsigned int> way;
vector<char> vect;
vector<char> vect2;
unsigned int level2;
unsigned int hasRoot(struct TrieNode* root,char str[],unsigned int level, unsigned int SpaceTimes,unsigned int count, ofstream &cout2){
    for (int i = 0; i < 26; i++) {
        if (root->children[i]) {
                way.push_back(i);
            count++;}}
    if(count>1) {
            if(level2!=level){
             vect.push_back(root->data);
            for (unsigned int j = 0; j < SpaceTimes; j++)
                cout2 << " ";
            cout2 << "-";
            for (char i: vect) {
                cout2 << i;
                vect2.push_back(i);}
            if (root->ifEnd) {
                cout2 << "(" << root->Meaning << ")";}
             way.clear();
             cout2 << endl;}
        SpaceTimes+=4;
             level2=level;
        return SpaceTimes;}

    else if(count==1){
        vect.push_back(root->data);
        count=0;
        for(char i:vect){
            vect2.push_back(i);}
        if(!way.empty()){
           for(unsigned int i : way){
                 if (root->children[i]) {
            hasRoot(root->children[i],str,level+1,SpaceTimes,count,cout2);
            vect.clear();}}
            way.clear();}}
    else if(count==0){
        way.clear();}
    return SpaceTimes;}

void display(struct TrieNode* root, char str[], unsigned int level , ofstream &cout2,unsigned int SpaceTimes=0) {

    // If node leaf, it is end of string
    if (isLeafNode(root)) {
        str[level] = '\0';
        for(unsigned int j=0; j<SpaceTimes; j++)
            cout2<<" ";
        cout2 <<"-"<< str << "("<<root->Meaning<<")"<<endl;}
    int i;
    for (i = 0; i < 26; i++) {
        //if child isn't NULL , function calls itself recursively
        if (root->children[i]) {
            SpaceTimes=hasRoot(root->children[i],str,level,SpaceTimes,0,cout2);
            str[level] = i + 'a';
            display(root->children[i], str, level + 1,cout2,SpaceTimes);
            if(level==0){
                SpaceTimes=0;
                vect.clear();}}}}

int main(__attribute__((unused)) int argc, char* argv[]) {
    struct TrieNode *root = getNode();
    size_t pos;
    string delimiter ;
    vector<string> inputVector;
    ifstream inputS;
    ofstream cout2(argv[2],ofstream::out);
    inputS.open(argv[1]);
    for (string input; getline(inputS, input);) {
        inputVector.push_back(input);}
    for(string s:inputVector){
    if(s=="list"){
        int level = 0;
        char str[26];
        vect.clear();
       display(root, str, level,cout2);}
    else{
       string line = s.substr(0,6);
       if(line=="insert"){
           string DothrakiWord;
           string Meaning;
           delimiter = ",";
            s=s.erase(0,7);
            s=s.erase(s.length()-1);
           string character;
           string character2;
           pos = s.find(delimiter);
           character = s.substr(0, pos);
            s=s.erase(0,character.length()+1);
           DothrakiWord=character;
           Meaning=s;
           insert(root, DothrakiWord, Meaning,0,cout2);}
       else if(line == "delete"){
        string TheWordWillbeDeleted;
        s.erase(0,7);
        TheWordWillbeDeleted=s.substr(0,s.length()-1);
        remove(root, TheWordWillbeDeleted,0,cout2);}
       else if(line=="search"){
           string TheWordWillbeSearched;
           s.erase(0,7);
           TheWordWillbeSearched=s.substr(0,s.length()-1);
           search(root, TheWordWillbeSearched,cout2);}}

    }}



