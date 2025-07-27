#include <iostream>

// 트리의 각 노드를 나타내는 구조체 정의
struct Node {
    int data; // 노드에 저장될 데이터
    Node* left; // 왼쪽 자식 노드를 가리키는 포인터
    Node* right; // 오른쪽 자식 노드를 가리키는 포인터

    // 생성자: 새로운 노드를 생성할 때 데이터를 초기화하고 자식 포인터는 NULL로 설정
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

/*
 * 1
 * / \
 * 2   3
 * / \
 * 4   5
 *
 * 위와 같은 구조의 트리를 생성하고 순회합니다.
 */

// 전위 순회 함수 (루트 -> 왼쪽 -> 오른쪽)
void preorderTraversal(Node* root) {
    if (root == nullptr) return;
    std::cout << root->data << " "; // 현재 노드 방문
    preorderTraversal(root->left);  // 왼쪽 서브트리 순회
    preorderTraversal(root->right); // 오른쪽 서브트리 순회
}

// 중위 순회 함수 (왼쪽 -> 루트 -> 오른쪽)
void inorderTraversal(Node* root) {
    if (root == nullptr) return;
    inorderTraversal(root->left);  // 왼쪽 서브트리 순회
    std::cout << root->data << " "; // 현재 노드 방문
    inorderTraversal(root->right); // 오른쪽 서브트리 순회
}

// 후위 순회 함수 (왼쪽 -> 오른쪽 -> 루트)
void postorderTraversal(Node* root) {
    if (root == nullptr) return;
    postorderTraversal(root->left);  // 왼쪽 서브트리 순회
    postorderTraversal(root->right); // 오른쪽 서브트리 순회
    std::cout << root->data << " "; // 현재 노드 방문
}


int main() {
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);

    std::cout << "전위 순회 (Pre-order): ";
    preorderTraversal(root);
    std::cout << std::endl;

    std::cout << "중위 순회 (In-order): ";
    inorderTraversal(root);
    std::cout << std::endl;

    std::cout << "후위 순회 (Post-order): ";
    postorderTraversal(root);
    std::cout << std::endl;
    
    // 실제로는 후위 순회를 이용해 안전하게 모든 노드를 삭제하는 함수를 만드는 것이 좋습니다.
    delete root->left->left;
    delete root->left->right;
    delete root->left;
    delete root->right;
    delete root;

    return 0;
}