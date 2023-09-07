/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */


template <class T>
List<T>::List() { 
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}


/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  //replace NULL with head_
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(NULL);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  ListNode * tempnode = head_;
  ListNode * nodeholder = tempnode;
  //use while statement to delete every node in memory (tempnode != NULL)
  while (tempnode != NULL) {
    nodeholder = nodeholder -> next;
    delete tempnode;
    tempnode = nodeholder;
  }
  //once completely done, delete temporary holders as well and set length to 0
  tempnode = NULL;
  nodeholder = NULL;
  length_= 0;
  /// @todo Graded in MP3.1
}



/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  if (head_ == NULL) {
    head_ = newNode;
    tail_ = newNode;
    newNode -> next = NULL;
    newNode -> prev = NULL;
  }
  else {
    newNode -> next = head_;
    newNode -> prev = NULL;
    head_ -> prev = newNode;
    head_ = newNode;
  }
  //increment length
  length_++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
ListNode * NewNode = new ListNode(ndata);
  //same as insert front but use tail_ not head_
  if(tail_ == NULL){
    tail_ = NewNode;
    head_ = NewNode;
    tail_ -> next = NULL;
    tail_ -> prev = NULL;
  }
  else {
    tail_ -> next = NewNode;
    NewNode -> next = NULL;
    NewNode -> prev = tail_;
    tail_ = NewNode;
  }
  //increment length
  length_++;
  /// @todo Graded in MP3.1
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  for (int i = 0; i < splitPoint; i ++) {
        start = start -> next;
    }
    ListNode* prev = start -> prev;
    start -> prev = NULL;
    prev -> next = NULL;
    return start;
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the last 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
  // @todo Graded in MP3.1
  ListNode * one = head_;
  ListNode * two = head_ -> next;
  ListNode * three = two -> next;
  ListNode * temp;
  int n;
  if (length_ % 3 == 0) {
    n = length_/3;
  } 
  else {
    n = (int)(length_/3);
  }
  if (n < 1) {
    return;
  }
  for (int i = 0; i < n; i++) {
    if (i != 0) {
      one = temp -> next;
      two = temp -> next -> next;
      three = temp -> next -> next -> next;
      if (three -> next == nullptr) {
        one -> next = nullptr;
      } 
      else {
        one -> next = three -> next;
      }
      three -> next = one;
      one -> prev = three;
      two -> prev = temp;
      temp -> next = two;
      temp = one;
    }
    else {
      one -> next = three -> next;
      three -> next = one;
      one -> prev = three;
      two -> prev = nullptr;
      head_ = two;
      temp = one;
    }
  }
}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  if (startPoint == endPoint || startPoint == NULL || endPoint == NULL) {
    return;
  }
  ListNode * tempnode;
  ListNode * currnode = startPoint;
  ListNode * initial_prev = startPoint -> prev;
  ListNode * new_end = endPoint -> next;
  ListNode * original_start = startPoint;
  ListNode * original_end = endPoint;

  while (currnode != new_end) {
    tempnode = currnode -> prev;
    currnode -> prev = currnode -> next;
    currnode -> next = tempnode;
    currnode = currnode -> prev;
  }  

  original_end -> prev = initial_prev;
  original_start -> next = new_end;

  if (initial_prev != NULL) {
    initial_prev -> next = original_end;
  } 

  if (new_end != NULL) {
    new_end -> prev = original_start;
  }

  startPoint = original_end;
  endPoint = original_start;

  if (head_ == original_start) {
    head_ = original_end;
  }
  if (tail_ == original_end) {
    tail_ = original_start; 
  }
  /// @todo Graded in MP3.2
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  if (n >= length_) {
    reverse(head_, tail_);
    return;
  }
  if (n <= 1) {
    return;
  }
  int b;
  if (length_ % n > 0) {
    b = length_ / n + 1;
  } 
  if (length_ % n == 0) {
    b = length_ / n;
  }

  for (int i = 1; i < b + 1; i++) {
    ListNode * tempnode_end = head_;
    ListNode * tempnode_start = head_;
    for (int j = 0; j < i * n - 1; j++) {
      if (tempnode_end -> next != NULL) {
        tempnode_end = tempnode_end -> next;
      }
    }
    for (int m = 0; m < (i-1) * n; m++) {
        tempnode_start = tempnode_start -> next;
    }
    reverse(tempnode_start, tempnode_end);
  }
  /// @todo Graded in MP3.2
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    head_ = merge(head_, otherList.head_);
    tail_ = head_;
    if (tail_ != NULL) {
        while (tail_ -> next != NULL)
            tail_ = tail_ -> next;
    }
    length_ = length_ + otherList.length_;
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  if (first == NULL) {
    return second;
  }
  if (second == NULL) {
    return first;
  }
  if (second == NULL && first == NULL) {
    return NULL;
  }
  ListNode * head;
  if (first -> data < second -> data) {
    head = first;
    first = first -> next;
  } else {
    head = second;
    second = second -> next;
  }
  ListNode * currnode = head;
  while (first != NULL && second != NULL) {
    if (first -> data < second -> data) {
      currnode -> next = first;
      first -> prev = currnode;
      currnode = first;
      first = first -> next;
    } else {
      currnode -> next = second;
      second -> prev = currnode;
      currnode = second;
      second = second -> next;
    }
  }

  if (first == NULL && second != NULL) {
    currnode -> next = second;
    second -> prev = currnode;
  }
  if (second == NULL && first != NULL) {
    currnode -> next = first;
    first -> prev = currnode;
  }
  return head;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if (chainLength <= 1) {
    return start;
  } 
  else {
    //recursive strategy
    ListNode * middle = split(start, chainLength/2);
    ListNode * left = mergesort(start, chainLength/2);
    ListNode * right = mergesort(middle, chainLength - chainLength/2);
    return merge(left, right);
  }
}
