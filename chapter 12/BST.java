import java.util.Arrays;
import java.util.Collections;

public class BST<T extends Comparable<T>> {

    private class Node {
        T key;
        Node parent;
        Node left;
        Node right;
        Node(T k) {
            key = k;
            parent = null;
            left = null;
            right = null;
        }
    }

    private Node root = null;

    public void inorder_tree_walk() {
        if(root != null) {
            inorder_tree_walk(root);
        }
    }

    private void inorder_tree_walk(Node x) {
        if(x != null) {
            inorder_tree_walk(x.left);
            System.out.print(x.key + " ");
            inorder_tree_walk(x.right);
        }
    }

    public Node tree_search(T k) {
        return tree_search(root, k);
    }

    private Node tree_search(Node x, T k) {
        if(x == null || k == x.key) {
            return x;
        }
        else if (k.compareTo(x.key) < 0) {
            return tree_search(x.left,k);
        }
        else {
            return tree_search(x.right,k);
        }
    }

    private Node tree_minimum(Node x) {
        while(x.left != null) {
            x = x.left;
        }
        return x;
    }

    private Node tree_maximum(Node x) {
        while(x.right != null) {
            x = x.right;
        }
        return x;
    }

    public void tree_insert(T k) {
        Node z = new Node(k);
        Node x = root;
        Node y = null;
        while(x!=null) {
            y = x;
            if ((z.key).compareTo(x.key) < 0) {
                x = x.left;
            } else {
                x = x.right;
            }
        }
        z.parent = y;
        if (y == null) {
            root = z;
        }
        else if ((z.key).compareTo(y.key) < 0) {
            y.left = z;
        }
        else {
            y.right = z;
        }
    }

    private Node transplant(Node u, Node v) {
        if (v != null) {
            v.parent = u.parent;
        }
        Node w = null;
        if(u.parent == null) {
            w = root;
            root = v;
        }
        else if (u == u.parent.left) {
            w = u.parent.left;
            u.parent.left = v;
        }
        else {
            w = u.parent.right;
            u.parent.right = v;
        }
        return w;
    }

    public void tree_delete(T k) {
        Node z = tree_search(k);
        if (z != null) {
            tree_delete(z);
        }
        else {
            return;
        }
    }

    private void tree_delete(Node z) {
        if(z.left == null) {
            transplant(z,z.right);
        }
        else if (z.right == null) {
            transplant(z,z.left);
        }
        else {
            Node y = tree_minimum(z.right);
            if (y.parent == z) {
                Node pz = transplant(z,z.right);
                y.left = pz.left;
                y.left.parent = y;
            }
            else {
                Node py = transplant(y,y.right);
                py.right = z.right;
                py.right.parent = py;
                Node pz = transplant(z,py);
                py.left = pz.left;
                py.left.parent = py;
            }
        }
    }

    public static void main(String[] args) {
        BST<Integer> bst = new BST<Integer>();

        Integer[] v = new Integer[100];
        for (int i = 1; i <= 100; ++i) {
            v[i - 1] = i;
        }

        System.out.println("original array");
        Collections.shuffle(Arrays.asList(v));
        for (int i = 0; i < 100; ++i) {
            System.out.print(v[i] + " ");
        }

        System.out.println();
        System.out.println("insert the nodes");
        for (int i = 0; i < 100; ++i) {
            bst.tree_insert(v[i]);
        }
        bst.inorder_tree_walk();
        System.out.println();

        System.out.println("shuffle \ndelete the nodes");

        Collections.shuffle(Arrays.asList(v));
        for (int i = 0; i < 100; ++i) {
            bst.tree_delete(v[i]);
        }
        bst.inorder_tree_walk();
        System.out.println("\ndelete complete");
    }
}
