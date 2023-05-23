#ifndef LIB_AVLTREETABLE_AVLTREETABLE_H_
#define LIB_AVLTREETABLE_AVLTREETABLE_H_
#include "../../Functional/lib_AVLTree/AVLTree.h"
#include "../lib_Table/Table.h"

template <typename TKey, typename TValue>
class AVLTreeTable : public Table<TKey, TValue> {
	AVLTree<TKey, TValue> tree;
public:
	virtual int insert(TKey key, TValue value);
	virtual int remove(TKey key);
	virtual TValue find(TKey key);
	virtual void print();

	std::vector<TTableRecord<TKey, TValue>*> toArray();
};

template <typename TKey, typename TValue>
int AVLTreeTable<TKey, TValue>::insert(TKey key, TValue value) {
	tree.insert(key, value);
	return 0;
}

template <typename TKey, typename TValue>
int AVLTreeTable<TKey, TValue>::remove(TKey key) {
	tree.remove(key);
	return 0;
}

template <typename TKey, typename TValue>
TValue AVLTreeTable<TKey, TValue>::find(TKey key) {
	return tree.find(key);
}

template <typename TKey, typename TValue>
void AVLTreeTable<TKey, TValue>::print() {
	std::cout << "AVL Tree Table" << std::endl;
	tree.print();
}

template <typename TKey, typename TValue>
std::vector<TTableRecord<TKey, TValue>*> AVLTreeTable<TKey, TValue>::toArray() {
	return tree.toArray();
}

#endif // !LIB_AVLTREETABLE_AVLTREETABLE_H_