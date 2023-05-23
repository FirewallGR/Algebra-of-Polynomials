#ifndef LIB_AVLTREE_AVLTREE_H_
#define LIB_AVLTREE_AVLTREE_H_
#include "..\lib_Tree\Tree.h"

template <typename TKey, typename TValue>
class AVLTree : public Tree<typename TKey, typename TValue> {
private:
    int count;
    Node<TKey, TValue>* root;

    int getHeight(Node<TKey, TValue>* node);
    int getBalance(Node<TKey, TValue>* node);
    Node<TKey, TValue>* rotateRight(Node<TKey, TValue>* node);
    Node<TKey, TValue>* rotateLeft(Node<TKey, TValue>* node);
    Node<TKey, TValue>* balanceNode(Node<TKey, TValue>* node);

    Node<TKey, TValue>* insertNode(Node<TKey, TValue>* node, TKey key, TValue value);
    Node<TKey, TValue>* removeNode(Node<TKey, TValue>* node, TKey key);

    void printHelper(Node<TKey, TValue>* node, int level);

    void fillArray(Node<TKey, TValue>* node, std::vector<TTableRecord<TKey, TValue>*>& array);
public:
    AVLTree();
    ~AVLTree();

    virtual int insert(TKey key, TValue value) override;
    virtual int remove(TKey key) override;
    virtual TValue find(TKey key) override;
    void print();

    std::vector<TTableRecord<TKey, TValue>*> toArray();
};

template <typename TKey, typename TValue>
AVLTree<TKey, TValue>::AVLTree() : root(nullptr), count(0) {};

template <typename TKey, typename TValue>
AVLTree<TKey, TValue>::~AVLTree() {

}

template <typename TKey, typename TValue>
int AVLTree<TKey, TValue>::insert(TKey key, TValue value) {
    if (root == nullptr) {
        root = new Node<TKey, TValue>(key, value);
        count++;
        return 0;
    }
    else {
        Node<TKey, TValue>* result = insertNode(root, key, value);
        if (result != nullptr) {
            count++;
            root = result;
            return 0;
        }
        else {
            return -1;
        }
    }
}

template <typename TKey, typename TValue>
int AVLTree<TKey, TValue>::remove(TKey key) {
    try {
        if (root == nullptr) {
            return -1;
        }
        else {
            Node<TKey, TValue>* result = removeNode(root, key);
            if (result != nullptr) {
                count--;
                root = result;
                return 0;
            }
            else {
                return -1;
            }
        }
        throw std::out_of_range("Key not found");
    }
    catch (const std::exception& ex) {
        std::cerr << "Error:" << ex.what() << std::endl;
    }
}

template <typename TKey, typename TValue>
TValue AVLTree<TKey, TValue>::find(TKey key) {
    try {
        Node<TKey, TValue>* current = root;
        while (current != nullptr) {
            if (key == current->getKey()) {
                return current->getValue();
            }
            else if (key < current->getKey()) {
                current = current->getLeft();
            }
            else {
                current = current->getRight();
            }
        }
        throw std::out_of_range("Key not found");
    }
    catch (const std::exception& ex) {
        std::cerr << "Error:" << ex.what() << std::endl;
    }
}

template <typename TKey, typename TValue>
void AVLTree<TKey, TValue>::print() {
    printHelper(root, 0);
}

template <typename TKey, typename TValue>
int AVLTree<TKey, TValue>::getHeight(Node<TKey, TValue>* node) {
    if (node == nullptr) {
        return 0;
    }
    return std::max(getHeight(node->getLeft()), getHeight(node->getRight())) + 1;
}

template <typename TKey, typename TValue>
int AVLTree<TKey, TValue>::getBalance(Node<TKey, TValue>* node) {
    if (node == nullptr) {
        return 0;
    }
    return getHeight(node->getLeft()) - getHeight(node->getRight());
}

template <typename TKey, typename TValue>
Node<TKey, TValue>* AVLTree<TKey, TValue>::rotateRight(Node<TKey, TValue>* node) {
    Node<TKey, TValue>* newRoot = node->getLeft();
    node->setLeft(newRoot->getRight());
    newRoot->setRight(node);
    return newRoot;
}

template <typename TKey, typename TValue>
Node<TKey, TValue>* AVLTree<TKey, TValue>::rotateLeft(Node<TKey, TValue>* node) {
    Node<TKey, TValue>* newRoot = node->getRight();
    node->setRight(newRoot->getLeft());
    newRoot->setLeft(node);
    return newRoot;
}

template <typename TKey, typename TValue>
Node<TKey, TValue>* AVLTree<TKey, TValue>::balanceNode(Node<TKey, TValue>* node) {
    int balance = getBalance(node);
    if (balance > 1) {
        if (getBalance(node->getLeft()) < 0) {
            node->setLeft(rotateLeft(node->getLeft()));
        }
        return rotateRight(node);
    }
    else if (balance < -1) {
        if (getBalance(node->getRight()) > 0) {
            node->setRight(rotateRight(node->getRight()));
        }
        return rotateLeft(node);
    }
    return node;
}

template <typename TKey, typename TValue>
Node<TKey, TValue>* AVLTree<TKey, TValue>::insertNode(Node<TKey, TValue>* node, TKey key, TValue value) {
    if (node == nullptr) {
        return new Node<TKey, TValue>(key, value);
    }
    if (key < node->getKey()) {
        node->setLeft(insertNode(node->getLeft(), key, value));
    }
    else if (key > node->getKey()) {
        node->setRight(insertNode(node->getRight(), key, value));
    }
    else {
        node->setValue(value);
    }
    return balanceNode(node);
}

template <typename TKey, typename TValue>
Node<TKey, TValue>* AVLTree<TKey, TValue>::removeNode(Node<TKey, TValue>* node, TKey key) {
    if (node == nullptr) {
        return nullptr;
    }

    if (key < node->getKey()) {
        node->setLeft(removeNode(node->getLeft(), key));
    }
    else if (key > node->getKey()) {
        node->setRight(removeNode(node->getRight(), key));
    }
    else {
        if (node->getLeft() == nullptr || node->getRight() == nullptr) {
            Node<TKey, TValue>* temp = node->getLeft() ? node->getLeft() : node->getRight();

            if (temp == nullptr) {
                temp = node;
                node = nullptr;
            }
            else {
                *node = *temp;
            }

            delete temp;
        }
        else {
            Node<TKey, TValue>* temp = node->getRight();
            while (temp->getLeft() != nullptr) {
                temp = temp->getLeft();
            }

            node->setKey(temp->getKey());
            node->setValue(temp->getValue());

            node->setRight(removeNode(node->getRight(), temp->getKey()));
        }
    }

    if (node == nullptr) {
        return node;
    }

    node = balanceNode(node);
    return node;
}

template <typename TKey, typename TValue>
void AVLTree<TKey, TValue>::printHelper(Node<TKey, TValue>* node, int level) {
    if (node == nullptr) {
        return;
    }
    printHelper(node->getRight(), level + 1);
    for (int i = 0; i < level; i++) {
        std::cout << "  ";
    }
    if constexpr (std::is_same_v<TValue, Polynom>) {
        std::cout << node->getKey() << " : " << node->getValue().toString() << std::endl;
    }
    else {
        std::cout << node->getKey() << " : " << node->getValue() << std::endl;
    }
    printHelper(node->getLeft(), level + 1);
}

template <typename TKey, typename TValue>
std::vector<TTableRecord<TKey, TValue>*> AVLTree<TKey, TValue>::toArray() {
    std::vector<TTableRecord<TKey, TValue>*> array;
    fillArray(root, array);
    return array;
}

template <typename TKey, typename TValue>
void AVLTree<TKey, TValue>::fillArray(Node<TKey, TValue>* node, std::vector<TTableRecord<TKey, TValue>*>& array) {
    if (node == nullptr) {
        return;
    }

    fillArray(node->getLeft(), array);
    array.push_back(new TTableRecord<TKey, TValue>(node->getKey(), node->getValue()));
    fillArray(node->getRight(), array);
}

#endif // !LIB_AVLTREE_AVLTREE_H_