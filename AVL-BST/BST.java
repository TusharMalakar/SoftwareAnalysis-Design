import java.util.*;

public class BST {
    
    // inner node class
    class Node
    {
        // member variables of Node class
    	int data;
    	Node left;
    	Node right;
        
        // constructor: assign data and make left and right pointers null 
        Node(int data)
        {
            this.data = data;
            this.left = null;
            this.right = null;
        }
    }
    
    
    // creating an reference of Node as root
    Node root;
    // constructor : create a empty node in BST
    BST()
    {
        this.root = null;
    }
    
    // store path of bst-value
	Vector<Integer> pathVector = new Vector<Integer>();
    
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
            if( data < this.root.data )
            {
               // if this.root left is not null, compare the value of this.root.left is greater or smaller than data
               //   1. if this.root.left is smaller, create new node to the right of this.root.left
               //   2. if this.root.left is greater, create new node to the left of this.root.left
               if(this.root.left != null)
               {
                   // assign to the left of this.root.left if data smaller than this.root.left
                   // else, assign to the right of this.root.left
                   if(data < this.root.left.data)
                   {
                	   this.root.left = _node;
                   }
                   else
                   {
                	   this.root.left = _node;
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
                   // assign to the left of this.root.right if data smaller than this.root.right
                   // else, assign to the right of this.root.right
                   if(data < this.root.right.data)
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
    
    
    public Node search(Node root, int data) 
    { 
        // Base Cases: root is null or key is present at root 
        if (root==null || root.data==data)
        {
        	return root; 
        }
        else
        {
        	// add path to pathVector
        	pathVector.add(root.data);
        	// data is greater than root's data 
            if (root.data > data) 
            {	
                return search(root.left, data);
            }
            else
            {
            	// data is less than root's data 
                return search(root.right, data); 
            }  	  
        }  
    }
    
    public String printPath(Vector<Integer> path)
    {
    	String valPath = "";
    	if( !path.isEmpty() )
    	{
    		for(int i=0; i<path.size(); i++)
    		{
    			valPath += path.get(i).toString();
    			valPath += " -> ";
    		}
    	}
    	return valPath;
    }
    
    public static void main(String args[]) {
        
        // creating instance of BST
        BST bst = new BST();
        bst.insert(5);
        bst.insert(4);
        bst.insert(6);
        bst.insert(8);
       
        //search and print path of 8 
        int searchVal = 8;
        bst.search(bst.root, searchVal); 
        String path = bst.printPath(bst.pathVector);
        System.out.println(path+searchVal);
    }
}
