public class BST {
    
    // inner node class
    class Node{
        // member variables of Node class
        int data;
        int left;
        int right;
        
        // constructor
        Node(int data)
        {
            this.data = data;
            this.left = null;
            this.right = null;
        }
    }
    
    
    // creating an reference of Node as root
    Node node;
    
    // constructor
    BST()
    {
        this.node = null;
    }
    
    // insert function to insert in BST
    public void insert(int data)
    {
        //creating a new node 
        Node _node = new Node(data);
        
        // insert in the root if root of BST is null
        if(this.root == null)
        {
            // assign to new new node to the this.root
            this.root = _node;
        }
        else
        {
            //insert small value to the left of this.root.date, if there is data in root
            if( data < this.root.date )
            {
               // if this.root left is not null, compare the value of this.root.left is greater or smaller than data
               //   1. if this.root.left is smaller, create new node to the right of this.root.left
               //   2. if this.root.left is greater, create new node to the left of this.root.left
               if(this.root.left != null)
               {
                   // assign to ths left of this.root.left if data smaller than this.root.left
                   // else, assign to the right of this.root.left
                   if(data < this.root.left)
                   {
                       this.root.left.left = _node;
                   }
                   else
                   {
                        this.root.left.right = _node;
                   }
                   
               }
               else
               {
                   // assign to this.root.left coz this.root.left is null
                   this.root.left = _node;
               }
            }
            //insert greater value to the right of this.root.date, if there is data in root
            else
            {
               // if this.root right is not null, compare the value of this.root.right is greater or smaller than data
               //   1. if this.root.right is smaller, create new node to the right of this.root.right
               //   2. if this.root.right is greater, create new node to the left of this.root.right
               if(this.root.right != null)
               {
                   // assign to ths left of this.root.right if data smaller than this.root.right
                   // else, assign to the right of this.root.right
                   if(data < this.root.right)
                   {
                       this.root.right.left = _node;
                   }
                   else
                   {
                        this.root.right.right = _node;
                   }
                   
               }
               else
               {
                   // assign to this.root.right coz this.root.right is null
                   this.root.right = _node;
               }
            }
        }
    }
    
    public static void main(String args[]) {
        
        // creating instance of BST
        BST bst = new BST();
        bst.insert(5);
        bst.insert(4);
        bst.insert(6);
      
    }
}

