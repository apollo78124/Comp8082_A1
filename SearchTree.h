// Starter code SearchTree - Question 3 of Assignment 1
#ifndef SEARCHTREE_H
#define SEARCHTREE_H

using namespace std;

class UnderflowException { };

template <typename Comparable>
class SearchTree {
public:
    struct BinaryNode {
        Comparable element;
        BinaryNode *left;
        BinaryNode *right;
        int height_left;
        int height_right;
        bool deleted = false;
        // You may need to add sth here!
        BinaryNode(const Comparable & theElement, BinaryNode *lt, BinaryNode *rt): element{theElement}, left{lt}, right{rt} {}
        BinaryNode( Comparable && theElement, BinaryNode *lt, BinaryNode *rt ): element{std::move(theElement)}, left{lt}, right{rt} {}
    };

    BinaryNode *root;
    int numDeleted;
    bool isAVL;
    // The isAVL flag is the only valid approach to indicate whether the tree is expected to be an AVL tree or not!
    // Please do not use any other approach.
    SearchTree(bool isAVL = false) : root{nullptr} {
        numDeleted = 0;
        isAVL = isAVL;
    }

    // Copy constructor
    SearchTree(const SearchTree & rhs) : root{nullptr} {
        numDeleted = 0;
        root = clone(rhs.root);
        isAVL = rhs.isAVL;
    }

    // Move constructor
    SearchTree(SearchTree && rhs) : root{rhs.root} {
        numDeleted = 0;
        rhs.root = nullptr;
        isAVL = rhs.isAVL;
    }

    // Destructor for the tree
    ~SearchTree() {
        makeEmpty();
    }

    // Copy assignment
    SearchTree & operator=(const SearchTree & rhs) {
        SearchTree copy = rhs;
        std::swap(*this, copy);
        return *this;
    }

    // Move assignment
    SearchTree & operator=(SearchTree && rhs) {
        std::swap(root, rhs.root);
        return *this;
    }


    // Find the smallest item in the tree.
    // Throw UnderflowException if empty.
    const Comparable & findMin() const {
        if(isEmpty())
            throw UnderflowException{};
        return findMin(root)->element;
    }

    // Find the largest item in the tree.
    // Throw UnderflowException if empty.
    const Comparable & findMax() const {
        if(isEmpty())
            throw UnderflowException{};
        return findMax(root)->element;
    }

    // Returns true if x is found in the tree.
    bool contains(const Comparable & x) const {
        return contains(x, root);
    }

    // Test if the tree is logically empty.
    // Return true if empty, false otherwise.
    bool isEmpty() const {
        return root == nullptr;
    }

    // Print the tree contents in sorted order.
    void printTree(ostream & out = cout, bool printDeleted = false) const {
        if(isEmpty())
            out << "Empty tree";
        else {
            out << "NUM DELETED = " << numDeleted << endl;
            printTree( root, out, printDeleted );
        }
    }

    // Make the tree logically empty.
    void makeEmpty() {
        makeEmpty(root);
    }

    // Insert x into the tree; duplicates are ignored.
    void insert(const Comparable & x) {
        insert(x, root);
    }

    // Insert x into the tree; duplicates are ignored.
    void insert(Comparable && x) {
        insert(std::move(x), root);
    }

    // Remove x from the tree. Nothing is done if x is not found.
    void remove(const Comparable & x) {
        remove(x, root);
    }
    /******************************** QUESTION3 - Part 2 *****************************************/
    /*********************Implement balancing functionality in the following function************/
    /**************************Start implementation for part 2 from here*************************/
    // the function which tests for the branch heights and assures the tree is
    // an AVL tree (balanced)
    void balance() {
        reportUnbalance(root);
    }

    void balance2(BinaryNode *t) {

    }

    void reportUnbalance(BinaryNode *t) {

        if(t != nullptr) {
            reportUnbalance(t->left);
            int difference = abs(tree_height(t->left) - tree_height(t->right));
            if (difference > 1) {
                balance2(t);
            }
            reportUnbalance(t->right);
        }
    }

    int tree_height(BinaryNode* root) {
        // Get the height of the tree
        if (!root)
            return 0;
        else {
            // Find the height of both subtrees and use the larger one
            int left_height = tree_height(root->left);
            int right_height = tree_height(root->right);
            if (left_height >= right_height)
                return left_height + 1;
            else
                return right_height + 1;
        }
    }
    /**************************End the implementation for part 2 in here*************************/
    /****************All the required functions for part 2 must be placed above this line*******/
    /*******************************************************************************************/
private:
    /*
        Internal methods to insert into a subtree.
        x is the item to insert.
        t is the node that roots the subtree.
        Set the new root of the subtree.
     */
    void insert(const Comparable & x, BinaryNode * & t) {
        if(t == nullptr)
            t = new BinaryNode{x, nullptr, nullptr};
        else if(x < t->element)
            insert(x, t->left);
        else if(t->element < x)
            insert(x, t->right);
        else if (t->element == x && t->deleted) {
            t->deleted = false;
        } else  {
            return ;// Duplicate; do nothing
        }
    }

    void insert(Comparable && x, BinaryNode * & t) {
        if(t == nullptr)
            t = new BinaryNode{std::move(x), nullptr, nullptr};
        else if(x < t->element)
            insert(std::move(x), t->left);
        else if(t->element < x)
            insert(std::move(x), t->right);
        else if (t->element == x && t->deleted) {
            t->deleted = false;
        } else  {
            return ;// Duplicate; do nothing
        }
    }

    /*
        Internal method to remove from a subtree.
        x is the item to remove.
        t is the node that roots the subtree.
        Set the new root of the subtree.
     */
    void remove(const Comparable & x, BinaryNode * & t) {
        if(t == nullptr)
            return;   // Item not found; do nothing
        if(x < t->element)
            remove(x, t->left);
        else if(t->element < x)
            remove(x, t->right);
        else if(t->element == x) { // Two children
            t->deleted = true;
            numDeleted++;
        }
    }

    // Internal method to print a subtree rooted at t in sorted order.
    BinaryNode * findMin(BinaryNode *t) const {
        if(t != nullptr) {
            BinaryNode * result = findMin(t->left);
            if (result != nullptr) {
                return result;
            }
            if (t->deleted == false) {
                return t;
            }
            result = findMin(t->right);
            if (result != nullptr) {
                return result;
            }
        } else {
            return NULL;
        }
    }

    /*
        Internal method to find the largest item in a subtree t.
        Return node containing the largest item.
     */
    BinaryNode * findMax(BinaryNode *t) const {
        if(t != nullptr) {
            BinaryNode * result = findMax(t->right);
            if (result != nullptr) {
                return result;
            }
            if (t->deleted == false) {
                return t;
            }
            result = findMax(t->left);
            if (result != nullptr) {
                return result;
            }
        } else {
            return NULL;
        }
    }

    /*
        Internal method to test if an item is in a subtree.
        x is item to search for.
        t is the node that roots the subtree.
     */
    bool contains(const Comparable & x, BinaryNode *t) const {
        if(t == nullptr)
            return false;
        else if(x < t->element)
            return contains(x, t->left);
        else if(t->element < x)
            return contains(x, t->right);
        else
            return true;    // Match
    }

    void makeEmpty(BinaryNode * & t) {
        if(t != nullptr) {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        t = nullptr;
    }

    // Internal method to print a subtree rooted at t in sorted order.
    void printTree(BinaryNode *t, ostream & out, bool printDeleted = false) const {
        if(t != nullptr) {
            printTree(t->left, out, printDeleted);
            if (t->deleted == false) {
                out << t->element << endl;
            } else {
                if (printDeleted) {
                    out << "{" << t->element << "}" << endl;
                }
            }
            printTree(t->right, out, printDeleted);
        }
    }

    // Internal method to clone subtree.
    BinaryNode * clone( BinaryNode *t ) const {
        if(t == nullptr)
            return nullptr;
        else
            return new BinaryNode{t->element, clone(t->left), clone(t->right)};
    }
};

#endif //SEARCHTREE_H
