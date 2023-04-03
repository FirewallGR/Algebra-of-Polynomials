#include "SyntaxTree.h"

// ���������� ������������
template <typename T>
SyntaxTree<T>::SyntaxTree() {
    root = nullptr;
}

// ���������� �����������
template <typename T>
SyntaxTree<T>::~SyntaxTree() {
    deleteTree(root);
}

template <typename T>
void SyntaxTree<T>::create(T* source) override {

}

// ���������� ������ ��� ���������� ���� � ������
template <typename T>
void SyntaxTree<T>::insert(T obj) override {
    root = addNodeRecursive(root, data);
}

// ���������� ������ ��� ���������� �������� ��������� � ������
template <typename T>
int SyntaxTree<T>::evaluate() {
    return evaluateRecursive(root);
}

// ����������� ����� ��� ���������� ���� � ������
template <typename T>
Node* SyntaxTree<T>::addNodeRecursive(Node* current, T data) {
    if (current == nullptr) {
        return new Node(data);
    }

    if (current->left == nullptr) {
        current->left = addNodeRecursive(current->left, data);
    }
    else if (current->right == nullptr) {
        current->right = addNodeRecursive(current->right, data);
    }
    else {
        current->left = addNodeRecursive(current->left, data);
    }

    return current;
}

// ����������� ����� ��� ���������� �������� ��������� � ������
template <typename T>
int SyntaxTree<T>::evaluateRecursive(Node* current) {
    if (current == nullptr) {
        return 0;
    }

    if (current->left == nullptr && current->right == nullptr) {
        return current->data - '0';
    }

    int leftValue = evaluateRecursive(current->left);
    int rightValue = evaluateRecursive(current->right);

    if (current->data == '+') {
        return leftValue + rightValue;
    }
    else if (current->data == '-') {
        return leftValue - rightValue;
    }
    else if (current->data == '*') {
        return leftValue * rightValue;
    }
    else if (current->data == '/') {
        return leftValue / rightValue;
    }

    return 0;
}

// ����������� ����� ��� �������� ������
template <typename T>
void SyntaxTree<T>::deleteTree(Node* current) {
    if (current != nullptr) {
        deleteTree(current->left);
        deleteTree(current->right);
        delete current;
    }
}