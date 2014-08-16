#include <iostream>
#include <queue>

struct CNode {
    int Data;
    CNode* Left; // NULL, если нет.
    CNode* Right; // NULL, если нет.
};

typedef struct CNode CNode;
typedef CNode* PCNode;

void Insert(PCNode& node, int value ) {
    if( node == NULL ) {
        node = new CNode;
        node->Left = NULL;
        node->Right = NULL;
        node->Data = value;
    }
    else {
        if( node->Data > value )
            Insert(node->Left, value);
        else
            Insert( node->Right, value);
    }
}

void Delete(PCNode& node) {
    if (node == NULL) return;
    Delete(node->Left);
    Delete(node->Right);
    delete node;
}

void BFS(PCNode& root) {
    std::queue<PCNode> q;
    q.push(root);
    while( !q.empty() ) {
        PCNode node = q.front();
        q.pop();
        std::cout << node->Data <<" ";
        if (node->Left != NULL)
            q.push( node->Left);
        if (node->Right != NULL)
            q.push( node->Right );
    }
}

int main() {
    int n;
    std::cin >> n;
    PCNode Node=NULL;
    for (int i=0; i<n; i++) {
        int b;
        std::cin >> b;
        Insert(Node, b);
        }
    BFS(Node);
    Delete(Node);
} 


