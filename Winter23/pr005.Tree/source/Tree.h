

class Tree {
public:
    class Node {
    private:
        int value;
        Node* parent;
        Node* l;
        Node* r;

    public:

        Node(Node* parent, int value);

        int getValue();
        Node* getParent();
        Node* getL();
        Node* getR();

        void addL(int value);
        void addR(int value);

        void setL(Node* newL);
        void setR(Node* newR);
        void setParent(Node* newParent);
        
        void swap(Node* b);
    };

    Tree();

    void add(int value);
    Node* search(int value);
    bool remove(int value);

private:

    Node* root;

    void add(Node* node, int value);
    Node* search(Node* node, int value);
    Node* next(Node* node);
    void remove(Node* ptr);
    bool remove(Node* node, int value);
};
