/*
adjacency list
____            ____    ____    ____
|node|    ----> |list|->|    |->|    |
|____|          |node|  |____|  |____|
____            ____    ____    ____
|    |    ----> |    |->|    |->|    |
|____|          |____|  |____|  |____|
____            ____    ____    ____
|    |    ----> |    |->|    |->|    |
|____|          |____|  |____|  |____|
____            ____    ____    ____
|    |    ----> |    |->|    |->|    |
|____|          |____|  |____|  |____|

*/
#include <stdio.h>
#include <stdlib.h>

typedef struct list_node{
    int index_of_item;
    struct list_node *next;
}list_node;

typedef struct node{
    int data;
    list_node *head;
}node;

typedef struct graph{
    int number_of_vertices;
    node heads[];
}graph;


node * new_node(int data){
    node *z;
    z = malloc(sizeof(node));
    z->data = data;
    z->head = NULL; 
}

list_node *new_list_node(int item_index){
    list_node *z;
    z = malloc(sizeof(list_node));
    z->index_of_item = item_index;
    z->next = NULL;
    return z;
}

graph * new_graph(int number_of_vertices){
    graph *g = malloc(sizeof(graph) * number_of_vertices * sizeof(node));
    g->number_of_vertices = number_of_vertices;
    
    int i;
    for(i=0;i<number_of_vertices;i++){
        node *z = new_node(-1);
        g->heads[i] = *z;
    }
    return g;
}


void add_node_to_graph(graph *g, int data){
    node *z = new_node(data);
    int i;
    for(i=0;i<g->number_of_vertices;i++){
        if(g->heads[i].data < 0){
            g->heads[i] = *z;
            break;
        }
    }
}

void add_edge(graph *g, int source, int dest){
    int i,j;
    for(i=0;i<g->number_of_vertices;i++){
        if(g->heads[i].data == source){
            int dest_index;
            
            for(j=0; j< g->number_of_vertices;j++){
                if(g->heads[j].data == dest){
                    dest_index = j;
                    break;
                }
            }
            
            list_node *n = new_list_node(dest_index);
            if(g->heads[i].head == NULL){
                g->heads[i].head = n;
            }
            else{
                list_node *temp;
                temp = g->heads[i].head;
                while(temp->next != NULL){
                    temp = temp->next;
                }
                temp->next = n;
            }
        break;
        }
    }
    
    //if graph is undirected 
    for(i=0; i<g->number_of_vertices; i++) {
        if(g->heads[i].data == dest) {
            int source_index;
            for(j=0;j<g->number_of_vertices;j++){
                if(g->heads[j].data == source){
                    source_index = j;
                    break;
                }
            }
            list_node *n = new_list_node(source_index);
            if(g->heads[i].head == NULL){
                g->heads[i].head = n;
            }
            else{
                list_node *temp;
                temp = g->heads[i].head;
                while(temp->next != NULL){
                    temp = temp->next;
                }
                temp->next = n;
            }
            break;
        }
}
}
void print_graph(graph *g){
    int i;
    for(i=0;i<g->number_of_vertices;i++){
        list_node *tmp;
        tmp = g->heads[i].head;
        printf("%d \t", g->heads[i].data);
        while(tmp != NULL){
            printf("%d \t", g->heads[tmp->index_of_item].data);
            tmp = tmp->next;
        }
        printf("\n");
    }
}

int main(){
    graph *g = new_graph(4);
    add_node_to_graph(g, 1);
    add_node_to_graph(g, 2);
    add_node_to_graph(g, 3);
    add_node_to_graph(g, 4);
    
    add_edge(g, 1,2);
    add_edge(g, 1,3);
    add_edge(g, 2,4);
    add_edge(g, 3,2);
    
    print_graph(g);
}
