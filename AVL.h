//
// Created by rotem on 07/10/2021.
//

#ifndef _AVL_H_
#define _AVL_H_
#include <vector>
#include "Apartment.h"
#include "Find.h"
//#include <algorithm>

class AVL {
 public:
  /**
   * To manage the tree nodes, we use a nested struct. This struct contains the
   * apartment corresponding to the node, the left son and the right son of the
   * node, both of them node type themselves.
   */
  struct node {

      /**
       * Constructor - It can be expanded
       * @param data the corresponding apartment object
       * @param left child
       * @param right child
       */
      node (Apartment data, node *left, node *right)
          : data_ (data), left_ (left), right_ (right)
      {
        this->height = 0;
      }
      /**
       *
       * @return the left child of this node
       */
      node *get_left () const
      {
        return left_;
      }
      /**
       *
       * @return the right child of this node
       */
      node *get_right () const
      {
        return right_;
      }
      /**
     *
     * @return the const reference apartment of this node
     */
      const Apartment &get_data () const
      {
        return data_;
      }
      Apartment data_;
      node *left_, *right_;
      size_t height;


  };
  node* rotate_right(node* cur);
  node* rotate_left(node* cur);
  node* find_successor(node*cur);
  int max_height_subtree(node *height1, node *height2);
  void recursive_copy(AVL::node *cur , Apartment const & apartment );
  node * recursive_erase(node * cur, Apartment const &apartment);
  void swap_nodes(node*node1,node *node2);
  node* copy_helper(node*other_root);
  AVL & operator=(const AVL &other);

  /**
   * Constructor. Constructs an empty AVL tree
   */
  AVL ();
  /**
   * Copy constructor
   * @param other
   */
  AVL (const AVL &other);
  /**
   * A constructor that receives a vector of a pairs. Each such pair is an
   * apartment that will inserted to the tree. Insert can be used to insert the
   * apartments a vector of a pairs
   * @param coordinates
   */
  AVL (std::vector<std::pair<double, double>> coordinates);
  /**
   *
   * @return the root node of this tree
   */
  node *get_root () const{
    return root_;
  }
  /**
   * The function inserts the new apartment into the tree so that it maintains
   * the legality of the tree.
   * @param apartment
   */
  void insert (const Apartment &apartment);
  /**
   * The function deletes the apartment from the tree (if it is in that tree)
   * so that it maintains
   * the legality of the tree.
   * @param apartment
   */
  void erase (const Apartment &apartment);
  /**
   * The class should support forward iterator. Don't forget to define the
   * iterator traits and all the actions required to support a forward iterator
   * The iterator will move in preorder.
   */
  class ConstIterator;
  class Iterator{

   public:
    friend class ConstIterator;
    node **cur;
    std::vector<node*> data_preorder;
    size_t index;
    typedef Apartment value_type;
    typedef Apartment &reference;
    typedef Apartment* pointer;
    typedef std::forward_iterator_tag iterator_category;
    typedef std::ptrdiff_t difference_type;
    void insert_preorder(node*root,std::vector<node*>&data);

    explicit Iterator(node *cur, node* end);
    Iterator &operator++();
    const Iterator operator++ (int);
    bool operator == (const Iterator &rhs) const;
    bool operator!= (const Iterator &rhs) const;
    reference operator*() const;
    pointer operator->() const;
  };
  class ConstIterator{
   public:
    std::vector<node*> data_preorder;
    size_t index;
    node **cur;
    typedef const Apartment value_type;
    typedef const Apartment &reference;
    typedef const int *pointer;
    typedef std::forward_iterator_tag iterator_category;
    typedef std::ptrdiff_t difference_type;
    void insert_preorder(node*root,std::vector<node*>&data);

    explicit ConstIterator(node *cur, node* end);
    explicit ConstIterator(const Iterator &it);
    ConstIterator &operator++();
    const ConstIterator operator++ (int);
    bool operator== (const ConstIterator &rhs) const;
    bool operator!= (const ConstIterator &rhs) const;
    Apartment operator*() const ;
    const Apartment* operator->() const;
  };

  using iterator = Iterator; // same as typedef Iterator iterator;
  using const_iterator = ConstIterator;
  iterator begin ();
  const_iterator begin () const;
  const_iterator cbegin () const;
  iterator end ();
  const_iterator end () const;
  const_iterator cend () const;
  /**
   * The function returns an iterator to the item that corresponds to the item
   * we were looking for. If there is no such member, returns end ().
   * @param data apartment to search
   * @return iterator to the item that corresponds to the item
   * we were looking for. If there is no such member, returns end ().
   */
  iterator find (const Apartment &data);
  /**
   * The function returns an iterator to the item that corresponds to the item
   * we were looking for. If there is no such member, returns end ().
   * @param data apartment to search
   * @return iterator to the item that corresponds to the item
   * we were looking for. If there is no such member, returns end ().
   */
  const_iterator find (const Apartment &data) const;
  /**
   * Insertion operator, prints the apartment in the tree in preorder
   * traversal.
   * Each apartmnet will be printed in the format: (x,y)\n
   * @param os reference to std::ostream
   * @param avl tree
   * @return os reference to std::ostream
   */
  friend std::ostream &operator<< (std::ostream &os, const AVL &avl);

  ~AVL();
  void recursive_free_destructor(node* root);
 private:
    node* end_node;
  node *root_;
  int tree_height(node*cur);
  int update_height (node *cur);
  int height_diff(AVL::node* cur);
  AVL::node* balance(AVL::node *cur);

  void balance_tree(node*cur,const Apartment &apartment);
};

#endif //_AVL_H_
