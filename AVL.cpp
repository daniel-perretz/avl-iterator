#include "AVL.h"

//* C'TORS *//
AVL::AVL ()
{
  this->root_ = nullptr;
  end_node = new node(
          Apartment(std::pair<double, double>(0,0)),
          nullptr, nullptr);
}
AVL::AVL (const AVL &other){
    if(other.root_ == nullptr){
        root_ = nullptr;
    }
    else{
      root_ = copy_helper(other.root_);
}
    end_node = new node(
            Apartment(std::pair<double, double>(0,0)),
            nullptr, nullptr);
}

AVL::node* AVL:: copy_helper(node*other_root){
    node * root;
  if(other_root == nullptr){
    return nullptr;
  }
  else{
  root = new node(other_root->data_, nullptr, nullptr);
  root->left_ = copy_helper (other_root->left_);
  root->right_ = copy_helper (other_root->right_);
  }
  return root;
}
AVL::AVL (std::vector <std::pair<double, double>> coordinates) : AVL()
{
    int i = 0;
  for (auto & coordinate : coordinates)
    {
      insert(coordinate);
      i++;
    }

}


void AVL::insert (const Apartment &apartment)
{
    if(root_ == nullptr){
        root_ = new node(apartment, nullptr, nullptr);
        return;
    }
    recursive_copy (this->root_,apartment);
    update_height(root_);
    balance_tree(root_,apartment);
    root_ = balance(root_);
}
void AVL::erase (const Apartment &apartment)
{
    if(find(apartment) == end()) return;
  root_ = recursive_erase(root_,apartment);
  update_height(root_);
  balance_tree(root_,apartment);
  root_ = balance(root_);

}
AVL::node * AVL::recursive_erase(node * cur, Apartment const &apartment){

  if(cur == nullptr){ // not found, need an error?
    return cur;
  }
  if(cur->data_ < apartment){
      cur->right_ = recursive_erase(cur->right_,apartment);
  }
  else if(cur->data_ > apartment){
      cur->left_ = recursive_erase (cur->left_,apartment);
  }

  else{
    // two children
    if(cur->left_ != nullptr && cur->right_ != nullptr){
      node *suc = find_successor(cur);
      swap_nodes(cur,suc);
      cur->right_ = recursive_erase (cur->right_,apartment);
    }
    // only left child
    else if(cur->left_ != nullptr && cur->right_ == nullptr){
      swap_nodes(cur,cur->left_);
      node*temp = cur->left_;
      cur->left_ = nullptr;
      delete  temp;
    }
    // only right child
    else if( cur->left_ == nullptr && cur->right_ != nullptr){
        swap_nodes(cur,cur->right_);
        node*temp = cur->right_;
        cur->right_ = nullptr;
        delete  temp;
      }
    //a leaf
    else{
//      node*temp = cur;
//      cur = nullptr;
//      delete temp;
      delete cur;
      cur = nullptr;
    }
    }
  return cur;

}
void AVL::recursive_copy ( AVL::node *cur, const Apartment &apartment)
{

    if (cur->data_ < apartment)
    {
      if(cur->right_ == nullptr){
          cur->right_ = new node(apartment, nullptr, nullptr);
          return;
      }
     recursive_copy (cur->right_, apartment);
    }
    else
    {
        if(cur->left_ == nullptr){
            cur->left_ = new node(apartment, nullptr, nullptr);
            return;
        }
     recursive_copy (cur->left_, apartment);
    }
}


/** end & begin */
AVL::Iterator AVL::begin ()
{
  AVL::Iterator itr (root_, end_node);

  return itr;
}
AVL::ConstIterator AVL::begin () const
{
    AVL::ConstIterator itr (root_, end_node);
  return itr;
}
AVL::ConstIterator AVL::cbegin () const
{
    AVL::ConstIterator itr (root_, end_node);
  return itr;
}
AVL::Iterator AVL::end ()
{
    AVL::Iterator itr (root_, end_node);
    itr.index = itr.data_preorder.size()-1;
    itr.cur = itr.data_preorder.data() + itr.index;
    return itr;
}
AVL::ConstIterator AVL::end () const
{
    AVL::ConstIterator end_itr (root_, end_node);
  end_itr.index =end_itr.data_preorder.size()-1;
  end_itr.cur = end_itr.data_preorder.data() + end_itr.index;
  return end_itr;
}
AVL::ConstIterator AVL::cend () const
{
    AVL::ConstIterator end_itr (root_, end_node);
    end_itr.index =end_itr.data_preorder.size()-1;
    end_itr.cur = end_itr.data_preorder.data() + end_itr.index;
    return end_itr;
}

//**    FIND    *//
AVL::Iterator AVL::find (const Apartment &data)
{
    //AVL::iterator itr(root_, end_node);

  for (auto it = this->begin(); it!=this->end() ;++it)
    {
      if(*it == data){
        return it;
      }
    }
  return end();
}
AVL::ConstIterator AVL::find (const Apartment &data) const
{
    for (auto it = this->begin(); it!=this->end() ;++it)
    {
        if(*it == data){
            return it;
        }
    }
    return end();
}



int AVL::update_height (AVL::node *cur)
{
    if (cur == nullptr) return -1;

    cur->height = std::max(update_height(cur->left_),
                           update_height(cur->right_)) +1;
    return (int) cur->height;

}
int AVL::max_height_subtree (node *height1, node* height2)
{




  if(height1 == nullptr and height2 != nullptr){
    return (int)height2->height;
  }
  if(height1 != nullptr and height2 == nullptr){
      return (int)height1->height;
    }
  else {
    if(height1->height > height2->height){
      return (int)height1->height;
    }
    return (int)height2->height;
  }
}
AVL::node* AVL::rotate_right (AVL::node *cur)
{
  node *temp = cur->left_;
  cur->left_ = temp->right_;
  temp->right_ = cur;
  cur = temp;
  tree_height (temp);
  tree_height (temp->right_);
  tree_height (temp->left_);
  return temp;
}
AVL::node* AVL::rotate_left (AVL::node *cur)
{
  node *temp = cur->right_;
  cur->right_ = temp->left_;
  temp->left_ = cur;
  cur = temp;
  tree_height(temp);
  tree_height (temp->right_);
  tree_height (temp->left_);
  return temp;
}
AVL::node *AVL::find_successor (AVL::node *cur)
{

  cur = cur->right_;
  while (cur->left_ != nullptr){
    cur = cur->left_;
  }
  return cur;
}

void AVL::swap_nodes (AVL::node *node1, AVL::node *node2)
{
  Apartment temp = node1->data_;
  node1->data_ = node2->data_;
  node2->data_= temp;

}



void AVL::Iterator::  insert_preorder
(AVL::node *root, std::vector<node *> &data)
{
  if(root == nullptr){
      return;
    }
  data.push_back (root);

  if(root->left_ != nullptr)
      insert_preorder (root->left_,data);
  if(root->right_ != nullptr)
      insert_preorder (root->right_,data);
}

void AVL::ConstIterator:: insert_preorder (
        AVL::node *root,std::vector<node *> &data)
{
  if(root == nullptr){
      return;
    }
  data.push_back (root);

  if(root->left_ != nullptr)
      insert_preorder (root->left_,data);
  if(root->right_ != nullptr)
      insert_preorder (root->right_,data);
}

//* Rules Of Three *//
AVL &AVL::operator = (const AVL &other)
{
  if(this != &other){
      copy_helper (other.root_);
  }
  return *this;
}


//** Iterator operator //
AVL::Iterator::Iterator (AVL::node *cur, AVL::node *end)
{
  insert_preorder (cur,data_preorder);
  data_preorder.push_back(end);
  this->index = 0;
  //this->cur = data_preorder[index];
  this->cur = data_preorder.data() + index;
}
AVL::Iterator &AVL::Iterator::operator++ ()
{
    index++;
    this->cur = data_preorder.data() + index;
    return *this;
}
const AVL::Iterator AVL::Iterator::operator++ (int)
{
  AVL::Iterator it = *this;
  index++;
  this->cur = data_preorder.data() + index;
  return  it;
}

AVL::iterator::reference AVL::Iterator::operator* () const
{
  return (*cur)->data_;
}
AVL::Iterator::pointer AVL::Iterator::operator-> () const
{
    return &((*cur)->data_);
}
bool AVL::Iterator::operator == (const AVL::Iterator &rhs) const
{
  return *cur == *(rhs.cur);
}
bool AVL::Iterator::operator!= (const AVL::Iterator &rhs) const
{
  return *(rhs.cur) != *((*this).cur);
}


//** ConstIterator operator //

AVL::ConstIterator::ConstIterator (AVL::node *cur, AVL::node *end)
{


    insert_preorder (cur,data_preorder);
    data_preorder.push_back(end);
    this->index = 0;
    this->cur = data_preorder.data() + index;
}
AVL::ConstIterator::ConstIterator (const AVL::Iterator &it)
{
  data_preorder = it.data_preorder;
  this->index = it.index;
  cur = it.cur;
}
AVL::ConstIterator &AVL::ConstIterator::operator++ ()
{

    index++;
    this->cur = data_preorder.data() + index;
    return *this;

}
const AVL::ConstIterator AVL::ConstIterator::operator++ (int)
{
  AVL::ConstIterator it = *this;
  this->cur = data_preorder.data() + (++index);
  return  it;
}
bool AVL::ConstIterator::operator== (const AVL::ConstIterator &rhs) const
{
  return *cur == *(rhs.cur);
}
bool AVL::ConstIterator::operator!= (const AVL::ConstIterator &rhs) const
{
  return !(rhs == *this);
}
Apartment AVL::ConstIterator::operator* () const
{
//    if(cur == nullptr){
//        return;
//    }
  return (*cur)->data_;
}
const Apartment * AVL::ConstIterator::operator-> () const
{
    return &(*cur)->data_;
}


std::ostream &operator<< (std::ostream &os, const AVL &avl){
  for (auto i:avl)
    {
      os << i;
    }
  return os;
}

AVL::~AVL ()
{
  recursive_free_destructor(root_);
  delete end_node;
}
void AVL::recursive_free_destructor (AVL::node *root)
{
  if(root == nullptr){
    return;
  }
  recursive_free_destructor (root->left_);
  recursive_free_destructor (root->right_);
  delete root;

}

int AVL::tree_height(AVL::node *cur) {
    if(cur== nullptr){
        return -1;
    }
    return (int)cur->height;
}

int AVL::height_diff(AVL::node* cur){
    if (cur == nullptr) return 0;
    return tree_height(cur->left_) - tree_height(cur->right_);
}

AVL::node* AVL::balance(AVL::node *cur) {
    if (cur == nullptr) return nullptr;
    if (tree_height(cur->left_)- tree_height(cur->right_) == 2)
    {
        //left right rotate
        if (height_diff(cur->left_) < 0)
        {
            cur->left_ = rotate_left (cur->left_);
            return rotate_right (cur);
        }
        // left left
        else if (height_diff(cur->left_) >= 0)
        {
            return rotate_right (cur);
        }
    }
    else if (height_diff(cur) == -2)
    {
        // right right
        if (height_diff(cur->right_) == 1)
        {
            cur->right_ = rotate_right(cur->right_);
            return  (rotate_left(cur));
        }
        // right left
        else if (height_diff(cur->left_) <=0)
        {
            return rotate_left(cur);
        }
    }
    return cur;
}




void AVL::balance_tree(AVL::node *cur,const Apartment &apartment) {
    if(cur == nullptr){
        return;
    }
    if(cur->data_ == apartment){
        return;
    }
    if(apartment > cur->data_){
        balance_tree(cur->right_,apartment);
    }
    else if(cur->data_ > apartment){
        balance_tree(cur->left_,apartment);
    }

    cur->left_ = balance(cur->left_);
    cur->right_ = balance(cur->right_);
}


