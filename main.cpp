#include <iostream>
#include <fstream>
#include <string>
#include "ArgumentManager.h"

using namespace std;

struct Node {
    string data;
    struct Node* next;
    Node(string data)
    {
        this->data = data;
        next = NULL;
    }
};

class LinkedList {
public:
    Node* head;
    LinkedList()
    {
        head = NULL;
    }

    // REVERSE LINKED LIST FUNCTION
    Node* recursiveReverse(Node* node)
    {
        if (node == NULL)
            return NULL;
        if (node->next == NULL) {
            head = node;
            return node;
        }
        Node* node1 = recursiveReverse(node->next);
        node1->next = node;
        node->next = NULL;
        return node;
    }

    void push(string data)
    {
        Node* newNode = new Node(data);
        // if linked list is empty then add new node at the beginning
        if (head == NULL)
            head = newNode;
        else
        { // if not empty then insert the node at the end of the linked list
            Node* tmp = head ;
            while(tmp->next != NULL)
            { // traversing the list
                tmp = tmp->next ;
            }
            tmp->next = newNode ;
        }
    }

    // print contents to the output file instead of the console
    // passing by reference
    void printList(ofstream& dumFile)
    {
        struct Node* temp = head;
        while (temp != NULL) {
            dumFile << temp->data << " ";
            temp = temp->next;
        }
    }
};

int main(int argc, char* argv[])
{

    LinkedList listAlpha;

    ArgumentManager arg(argc, argv);
    string inputFile = arg.get("input"); // "input3.txt"  ;
    string ouputFile = arg.get("output"); // "output3.txt" ;

    // hardcode for testing
//    string inputFile = "input1.txt";
//    string ouputFile = "output1.txt";

    ifstream ifs(inputFile);
    ofstream ofs(ouputFile);


    // read the file content
    if (ifs.is_open())
    {
        std::string line;
        while (getline(ifs, line))
        {
            istringstream ss(line);
            do
            {
                string word;
                ss >> word;
                if (!word.empty())
                {
                    listAlpha.push(word) ;
                }
            }
            while(ss) ;
        }
        ifs.close() ;
    }

    // reversing listAlpha recursively
    listAlpha.recursiveReverse(listAlpha.head);

    if (ofs.is_open())
    {
        listAlpha.printList(ofs) ;
        ofs.close() ;
    }

    // exit program
    return 0;
}