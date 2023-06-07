// Test code that combines all your implementation from Questions 1 to 3 in Assignment 1
// compile and run with:
//			g++ COMP8042A1Test.cpp -o COMP8042A1Test && ./COMP8042A1Test
#include <iostream>
#include <cassert>
#include <vector>
#include <string>
#include <stack>
#include "Calculator.h"
#include "Deque.h"
#include "SearchTree.h"


using namespace std;


int main() {
//    cout << "***** Part 1: expression calculation *****" << endl;
//    string expressions[] = {"2 3 + 4 5 * + =", "2 + 3 =", "( 2 + 3 ) + ( 4 * 5 ) =", "* + 1 4 * 5 2 =",
//                            "1 3 =", "1 3 + =", "@ 1 3 5 =", "1 3 5 @ =", "2 @ 4 =",
//                            "1 2 1 2 + @ 4 * 3 1 @ =", "2 2 3 ^ * 1 + 2 / ="};
//    string expected[] = {"25", "5", "25", "50", "Invalid Expression!", "4", "3", "3",
//                         "Invalid Expression!", "4", "8"};
    int i = 0;
//    for (auto& expr: expressions){
//        cout << "Evaluated expression: " << expr << " " << calculator::evaluateExpression(expr) << endl;
//        assert(calculator::evaluateExpression(expr) == expected[i]);
//        i++;
//    }
//    cout << endl << endl << "***** Part 2: Dequeue using circular array *****" << endl;
//    cout << "To understand the results of this part, please" << endl;
//    cout << "read the notes above Deque.h very carefully!" << endl;
//    cout << "************************************************" << endl;
//    Queue<int> Q(5);
//    cout << "Queue content: " << Q.print() << endl;
//    Q.enque(1);
//    Q.enque(2);
//    Q.enque(3);
//    cout << "Queue content: " << Q.print() << endl;
//    cout << "Dequeue next: " << Q.deque() << " (should be 1)" << endl;
//    cout << "Dequeue next: " << Q.deque() << " (should be 2)" << endl;
//    cout << "Dequeue next: " << Q.deque() << " (should be 3)" << endl;
//    cout << "Queue must be empty now!" << endl;
//    cout << "Dequing from the empty queue: " << Q.deque() << " (should be 0!)" << endl;
//    Q.enque(10);
//    Q.enque(20);
//    Q.enque(30);
//    Q.enque(40);
//    cout << "Added 10, 20, 30, 40 so far, queue is full so we cannot enqueue 50!" << endl;
//    Q.enque(50);
//    cout << "Queue content: " << Q.print() << endl;
//    int expectedContent[] = {30, 40, 3, 10, 20};
//    i = 0;
//    for(auto& elem : Q.debugGetArray()){
//        assert(elem == expectedContent[i]);
//        i++;
//    }
//    cout << "Dequeue next: " << Q.deque() << " (should be 10)" << endl;
//    Q.enque(100);
//    cout << "Queue content: " << Q.print() << endl;
//    cout << "Dequeue next: " << Q.deque() << " (should be 20)" << endl;
//    cout << "Dequeue next: " << Q.deque() << " (should be 30)" << endl;
//    cout << "Dequeue next: " << Q.deque() << " (should be 40)" << endl;
//    cout << "Dequeue next: " << Q.deque() << " (should be 100)" << endl;
    cout << endl << endl << "***** Part 3: Dequeue using circular array *****" << endl;
    SearchTree<int> bst;
    assert(bst.isEmpty());
    std::ostringstream os;
    bst.printTree(os);
    cout << os.str() << " (should be Empty tree)" << endl;
    bst.insert(78);
    bst.insert(12);
    bst.insert(56);
    bst.insert(34);
    bst.insert(40);
    bst.remove(56);
    bst.insert(56);
    os.str("");
    bst.printTree(os);
    cout << "Tree content: " << os.str() << endl;
    assert(!bst.isEmpty());
    int minVal = bst.findMin();
    int maxVal = bst.findMax();
    bool containsSuccess = bst.contains(12);
    bool containsFail = bst.contains(999);
    assert(minVal == 12);
    assert(maxVal == 78);
    assert(containsSuccess);
    assert(!containsFail);

    SearchTree<int> bst2(bst);
    os.str("");
    bst2.printTree(os);
    cout << "Tree2 content: " << os.str() << endl;
    SearchTree<int> bst3 = bst2;
    os.str("");
    bst3.printTree(os);
    cout << "Tree3 content: " << os.str() << endl;
    bst.makeEmpty();
    assert(bst.isEmpty());
    SearchTree<int> tree;
    tree.insert(5);
    tree.insert(10);
    tree.insert(0);
    tree.insert(1);
    tree.insert(-1);
    tree.insert(9);
    tree.insert(11);
    os.str("");
    tree.printTree(os);
    cout << "Next Tree content: " << os.str() << endl;
    tree.remove(1);
    tree.remove(5);
    tree.remove(10);
    os.str("");
    tree.printTree(os);
    cout << "Same Tree content after some removal: " << os.str() << endl;
    os.str("");
    tree.printTree(os, true);
    cout << "Same Tree content after some removal (with the removed content): " << os.str() << endl;
    tree.insert(10);
    os.str("");
    tree.printTree(os);
    cout << "Same Tree content after some removal and insertion: " << os.str() << endl;
    os.str("");
    tree.printTree(os, true);
    cout << "Same Tree content after some removal and insertion (with the removed content): " << os.str() << endl;
    return 0;
}
