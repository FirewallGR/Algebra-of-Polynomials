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

// ���������� ������ ��� �������� ��������������� ������
template <typename T>
void SyntaxTree<T>::create(T* source, int size) {
    for (int i = size - 1; i > 0; i--) {
        insert(source[i]);
    }
}

// ���������� ������ ��� ���������� ���� � ������
template <typename T>
void SyntaxTree<T>::insert(T obj) {
    root = addNodeRecursive(root, obj);
}

// ���������� ������ ��� �������� ���� �� ������
template <typename T>
void SyntaxTree<T>::remove(T obj) {

}
// ���������� ������ ��� ������ �������� �� �����
template <typename T>
T SyntaxTree<T>::find(T key) {

}
// ���������� ������ ��� ���������� �������� ��������� � ������
template <typename T>
int SyntaxTree<T>::evaluate() {
    return evaluateRecursive(root);
}

// ����������� ����� ��� ���������� ���� � ������
template <typename T>
Node<T>* SyntaxTree<T>::addNodeRecursive(Node<T>* current, T data) {
    if (current == nullptr) {
        return new Node<T>(data);
    }
    if (current->getRight() == nullptr) {
        current->setRight(addNodeRecursive(current->getRight(), data));
    }
    else if (current->getLeft() == nullptr) {
        current->setLeft(addNodeRecursive(current->getLeft(), data));
    }
    else if (operationsPriority.contains(current->getRight()->getValue())) {
        current = current->getRight();
        current->setTop(root);
        current->setRight(addNodeRecursive(current->getRight(), data));
    }
    else if (operationsPriority.contains(current->getLeft()->getValue())) {
        current = current->getLeft();
        current->setTop(root);
        current->setRight(addNodeRecursive(current->getRight(), data));
    }

    return current;
}

// ����������� ����� ��� ���������� �������� ��������� � ������
template <typename T>
int SyntaxTree<T>::evaluateRecursive(Node<T>* current) {
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
void SyntaxTree<T>::deleteTree(Node<T>* current) {
    if (current != nullptr) {
        deleteTree(current->left);
        deleteTree(current->right);
        delete current;
    }
}