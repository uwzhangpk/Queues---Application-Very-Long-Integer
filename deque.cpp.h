template <class Object>
Deque<Object>::Deque( ) {                          // the constructor
  front = back = NULL;
}

template <class Object>
Deque<Object>::Deque( const Deque &rhs ) {         // the copy constructor
  front = back = NULL;
  *this = rhs;
}

template <class Object>
Deque<Object>::~Deque( ) {                         // the destructor
  clear( );
}

template <class Object>
bool Deque<Object>::isEmpty( ) const {             // check if a deque is empty
  return front == NULL;
}

template <class Object>
int Deque<Object>::size( ) const {                 // retrieves # deque nodes
  int i = 0;
  for ( DequeNode *ptr = front; ptr != NULL; ptr = ptr->next ) // traverse que
    ++i;

  return i;
}

template <class Object>
const Object &Deque<Object>::getFront( ) const {   // retrieve the front node
  if ( isEmpty( ) )
    throw "empty queue";
  return front->item;
}

template <class Object>
const Object &Deque<Object>::getBack( ) const {    // retrieve the back node
  if ( isEmpty( ) )
    throw "empty queue";
  return back->item;
}

template <class Object>
void Deque<Object>::clear( ) {          // clean up all entries.
  while ( !isEmpty( ) )                 // dequeue till the queue gets empty.
    removeFront( );
}

template <class Object>
void Deque<Object>::addFront( const Object &obj ) {// add a new node to  front
  // add a new node to the front
	DequeNode* tmp = new DequeNode;
	tmp->item = obj;
	tmp->prev = NULL;
	tmp->next = NULL;

	if (isEmpty()) {
		front = tmp;
		back = tmp;
	}
	else {	
		tmp->next = front;
		front->prev = tmp;
		front = tmp;
		
	}

}

template <class Object>
void Deque<Object>::addBack( const Object &obj ) { // add a new node to back
  // add a new node to the back
	DequeNode* tmp = new DequeNode;
	tmp->item = obj;
	tmp->next = NULL;
	tmp->prev = NULL;

	if (isEmpty()) {
		front = tmp;
		back = tmp;
	}
	else {
		tmp->prev = back;
		back->next = tmp;
		back = tmp;

	}
}

template <class Object>
Object Deque<Object>::removeFront( ) {  // remove the front node
  // remove the front node
	Object frontItem = getFront();
	DequeNode *tmp = front;
	if (front == back) {
		
		front = NULL;
		back = NULL;
		
	}
	else {
		
		
		front = front->next;
		
		delete tmp;
		
		
	}
	return frontItem;

}

template <class Object>
Object Deque<Object>::removeBack( ) {   // remove the back node
  // remove the back node
	Object backItem = getBack();
	DequeNode *tmp = back;
	if (front == back) {
		
		front = NULL;
		back = NULL;
		
	}
	else {
		
		
		back = back->prev;
		
		delete tmp;
		

		
	}
	return backItem;
}

template <class Object>
const Deque<Object> &Deque<Object>::operator=( const Deque &rhs ) { // assign
  if ( this != &rhs ) { // avoid self assignment
    clear( );
    for ( DequeNode *rptr = rhs.front; rptr != NULL; rptr = rptr->next )
      addBack( rptr->item );
  }
  return *this;
}


