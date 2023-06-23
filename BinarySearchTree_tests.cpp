// Project UID db1f506d06d84ab787baf250c265e24e

#include "BinarySearchTree.h"
#include "unit_test_framework.h"
using namespace std;
TEST(test_bst) {
    BinarySearchTree<int> tree;
    ASSERT_TRUE(tree.empty());
    tree.insert(5);
    ASSERT_FALSE(tree.empty());
    ASSERT_TRUE(tree.check_sorting_invariant());
    ASSERT_EQUAL(*tree.begin(), 5);
    tree.insert(9);
    tree.insert(3);
    ASSERT_EQUAL(*tree.max_element(), 9);
    ASSERT_EQUAL(*tree.min_element(), 3);
    tree.insert(4);
    tree.insert(2);
    tree.insert(11);
    tree.insert(6);
    ASSERT_EQUAL(tree.size(), 7);
    ASSERT_EQUAL(tree.height(), 3);
    tree.insert(12);
    cout << tree.to_string();
    ASSERT_EQUAL(*tree.max_element(), 12);
    ASSERT_EQUAL(*tree.min_element(), 2);
    ASSERT_TRUE(tree.check_sorting_invariant());
    ASSERT_EQUAL(*tree.find(3), 3);
    ASSERT_TRUE(tree.find(0) == tree.end());
    ASSERT_EQUAL(tree.size(), 8);
    ASSERT_EQUAL(tree.height(), 4);
    ASSERT_EQUAL(*tree.min_greater_than(11), 12);
    ASSERT_EQUAL(*tree.min_greater_than(4), 5);
    ASSERT_EQUAL(*tree.min_greater_than(7), 9);
    
    ostringstream oss_preorder;
    tree.traverse_preorder(oss_preorder);
    cout << "\npreorder" << endl;
    cout << oss_preorder.str() << endl << endl;
    ASSERT_TRUE(oss_preorder.str() == "5 3 2 4 9 6 11 12 ");

    ostringstream oss_inorder;
    tree.traverse_inorder(oss_inorder);
    cout << "inorder" << endl;
    cout << oss_inorder.str() << endl << endl;
    ASSERT_TRUE(oss_inorder.str() == "2 3 4 5 6 9 11 12 ");
    int arr[8] = { 2, 3, 4, 5, 6, 9, 11, 12 };
    int index = 0;
    for (BinarySearchTree<int>::Iterator itr = tree.begin(); itr != tree.end(); itr++) {
        ASSERT_EQUAL(*itr, arr[index]);
        index++;
    }

    BinarySearchTree<int> tree2;
    ASSERT_EQUAL(tree2.size(), 0);
    ASSERT_EQUAL(tree2.height(), 0);
    tree2.insert(0);
    tree2.insert(-1);
    tree2.insert(3);
    ASSERT_TRUE(tree2.check_sorting_invariant());
    ASSERT_EQUAL(tree2.size(), 3)
    tree2 = tree;
    ASSERT_EQUAL(tree2.size(), 8)
    cout << tree2.to_string();
    ostringstream oss_preorder2;
    tree2.traverse_preorder(oss_preorder2);
    cout << "\npreorder" << endl;
    cout << oss_preorder2.str() << endl << endl;
    ASSERT_TRUE(oss_preorder2.str() == "5 3 2 4 9 6 11 12 ");

    ostringstream oss_inorder2;
    tree2.traverse_inorder(oss_inorder2);
    cout << "inorder" << endl;
    cout << oss_inorder2.str() << endl << endl;
    ASSERT_TRUE(oss_inorder2.str() == "2 3 4 5 6 9 11 12 ");
}

TEST(test_bst_string) {
    BinarySearchTree<string> stree;
    string name1 = *stree.insert("Kobe");
    string name2 = *stree.insert("Aaron");
    string name3 = *stree.insert("John");
    string name4 = *stree.insert("Nancy");
    string name5 = *stree.insert("Maria");
    
    ASSERT_EQUAL(*stree.begin(), name2);
    stree.insert("Bob");
    cout << stree.to_string();
    ASSERT_EQUAL(*stree.min_greater_than("Bob"), "John");

    BinarySearchTree<int> itree;
    itree.insert(4);
    itree.insert(1);
    itree.insert(3);
    itree.insert(5);
    itree.insert(6);
    cout << itree.to_string();
    ASSERT_EQUAL(*itree.min_greater_than(2), 3);
    itree.insert(2);
    cout << itree.to_string();
    ASSERT_EQUAL(*itree.min_greater_than(1), 2);
    BinarySearchTree<int>::Iterator itr = itree.begin();
    itr++; itr++;
    *itr = 4;
    cout << itree.to_string();
    ASSERT_FALSE(itree.check_sorting_invariant());
    *itr = 10;
    ASSERT_FALSE(itree.check_sorting_invariant());
    *itr = 3;
    itr++; itr++;
    *itr = 0;
    cout << itree.to_string();
    ASSERT_FALSE(itree.check_sorting_invariant());
    *itr = 7;
    ASSERT_FALSE(itree.check_sorting_invariant());
    *itr = 5;
    itr++;
    *itr = 1;
    ASSERT_FALSE(itree.check_sorting_invariant());
}

TEST_MAIN()
