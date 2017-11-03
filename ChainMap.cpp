class Node 
{
        friend class HashTable;
        Node* next;
        int data;
    public:
        Node()
        {
        }
        Node(int d, Node* n)
        {
            data = d;
            next = n;
        }
        ~Node() 
        {
        }
};
class HashTable 
{
public:
    int size;
    vector<Node*>* Nodes;
    HashTable(int s)
    {
        size = s;
        Nodes = new vector<Node*>(size);
    }
    HashTable()
    {
        size = DEFAULT;
        Nodes = new vector<Node*>(size);
    }
    ~HashTable()
    {
    }
    void insert(int data)
    {
        int index = getHashByDivision(data);
        if (Nodes -> at(index) == NULL)
        {
            Nodes -> at(index) = new Node(data, NULL);
            return;
        }
        Node* p = Nodes -> at(getHashByDivision(data));
        while (p != NULL){
            if (p -> next == NULL)
            {
                p -> next = new Node(data, NULL);
                break;
            }
            p = p -> next;
        }
    }
    
    int getSize()
    {
        return size;
    }
             
    int find(int data)
    {
        for(Node*pos=Nodes -> at(getHashByDivision(data));pos;pos=pos->next)
    if(pos->data==data)
        return true;
return false;
    }
        int getHashByDivision(int key)
    {
        return (key % getSize());
    }
    void print(int start)
    {
        int lineCount = 0;
        for (int i = start; i < Nodes -> size(); i++){
            cout << i << "\t";
            Node* p = Nodes -> at(i);
            while (p != NULL){
                cout << p -> data << " ";
                p = p -> next;
            }
            cout << endl;
        }
    }
};
int main(int argc, const char* argv[]){
    int n = 10;
    //argv[1] = "10";
    //argv[2] = "10";
    int A[] = { 40, 12, 79, 35, 43, 52, 83, 66, 89, 79 };
    
    
    HashTable* hash = new HashTable(n);
    for (int i = 0; i < n; i++){
        hash -> insert(A[i]);
    }
 
    hash -> print(0);
    
 
    system("pause");
    return 0;
}
