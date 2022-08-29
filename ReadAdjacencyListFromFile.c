/* 
Author: Yigit Bora Cagiran
Read Adjacency List From a File
With this algorithm, we can read a .txt file and reach it with singly linked list.
In the .txt file: left nodes means main nodes, the nodes which on their right side means their adjacent nodes.
Please take a look at to the png file to understand better the structure.
*/

#include <stdio.h>
#include <stdlib.h>

struct node{
    char nodeName; //Node name
    struct node *nextNode; //It points to the next adjacent node
    int mainNode; //In the adjacency list, if a node is; one of the main nodes -> 1, one of the main node's adjacent nodes -> 0 
    struct node *nextMainNode; //It points to the next main node
};

FILE *file;
struct node *firstNode=NULL;
struct node *nodeIter=NULL;
struct node *mainNodeIter=NULL;
int control=0;

void BuildingAdjacencyList(){ //Read the characters in the .txt file and add them to singly linked list
    char readCharacter=fgetc(file);
    char previousCharacter='\n';  // If this variable doesn't start with '\n', algorithm can't make the first node to a main node
    while(!feof(file)){ //Until to read all the characters in the file
        if(readCharacter!='\n'&&readCharacter!=' '&&previousCharacter=='\n'){ //Main Nodes
            if(control==0){ //First Main Node
                nodeIter->mainNode=1; 
                nodeIter->nodeName=readCharacter; 
                mainNodeIter=nodeIter;
                firstNode=mainNodeIter;
                control=1;
            }
            else{ 
                mainNodeIter->nextMainNode=(struct node*)malloc(sizeof(struct node)); //Other Main Nodes
                nodeIter=mainNodeIter->nextMainNode; 
                nodeIter->mainNode=1;
                nodeIter->nodeName=readCharacter;
                mainNodeIter=nodeIter;
            }
            mainNodeIter->nextMainNode=NULL;
        }
        else if(readCharacter!='\n'&&readCharacter!=' '&&previousCharacter!='\n'){ //Adjacent Nodes
            nodeIter->nextNode=(struct node*)malloc(sizeof(struct node));  
            nodeIter=nodeIter->nextNode;
            nodeIter->nodeName=readCharacter;
            nodeIter->mainNode=0; 
            nodeIter->nextNode=NULL;
        } 
        previousCharacter=readCharacter;
        readCharacter=fgetc(file);
    }
}

void PrintingAdjacencyList(){ //Print the structure
    mainNodeIter=firstNode;
    nodeIter=mainNodeIter;
    while(mainNodeIter!=NULL){ //Do it until the all rows are travelled.
        while(nodeIter!=NULL){  //Travel between adjacent nodes in the first main node's row, when the row is complete, go to the next main node's row.
            if(nodeIter->mainNode==1){ //Main node...
                printf("%c->", nodeIter->nodeName);
            }
            else{ //Adjacent node...
                printf("%c-", nodeIter->nodeName);
            }
            nodeIter=nodeIter->nextNode; 
        }
        printf("NULL\n");
        mainNodeIter=mainNodeIter->nextMainNode;
        nodeIter=mainNodeIter;
    }
}

int main(){
    file=fopen("adjacency_list.txt", "r"); //Open the file for only reading
    if(file==NULL){
        printf("File is Empty!");
    }
    else{
        printf("Adjacency List:\n");
        firstNode=(struct node*)malloc(sizeof(struct node));
        nodeIter=(struct node*)malloc(sizeof(struct node));
        mainNodeIter=(struct node*)malloc(sizeof(struct node));
        nodeIter=firstNode;
        mainNodeIter=firstNode;
        BuildingAdjacencyList();
        PrintingAdjacencyList();
    }   
    fclose(file); //Close the file.
    free(firstNode);
    free(nodeIter);
    free(mainNodeIter);
    free(mainNodeIter);
    return 0;
}