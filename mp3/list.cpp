#include <iostream>
using namespace std;
/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 *
 * @author Chase Geigle
 * @date (created) Fall 2011
 * @date (modified) Spring 2012, Fall 2012
 *
 * @author Jack Toole
 * @date (modified) Fall 2011
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List()
{
	clear();
    /// @todo Graded in MP3.1
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear()
{
	
	while(length>0){
		tail = tail-> prev;
		if(tail != NULL){
			delete tail-> next;
			tail ->next = NULL;
		}
		length--;
	}
	delete head;
	head = NULL;
    /// @todo Graded in MP3.1
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const & ndata)
{
	if(head != NULL){
		head->prev = new ListNode(ndata);
    		head->prev->next = head;
		head=head->prev;
	}
	else{
	head =new ListNode(ndata);
	tail=head; 
	}
	length++;
	/// @todo Graded in MP3.1
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack( const T & ndata )
{
	if(tail != NULL){
		tail->next = new ListNode(ndata);
		tail->next->prev = tail;
		tail = tail->next;
	}
	else{
	tail =new ListNode(ndata);
	head=tail; 
	}
	length++;
	
    /// @todo Graded in MP3.1
}


/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse()
{
    reverse(head, tail);
}


/*
a helper function for reverse
*/
template <class T>
void List<T>::bringBack(ListNode * &startPoint, ListNode * &endPoint){
	ListNode* ts = startPoint, *te = endPoint;
if(startPoint == endPoint) return;
	else{	
		startPoint = te;//->prev;
		endPoint = te->prev;
	
		if(ts->prev != NULL){
			ts->prev->next = te;
		}
		else
			head = te;

		te->prev->next = te->next;
		
		if(te->next != NULL)
			te->next->prev = te->prev;
		else
			tail = te->prev;
	
		te->prev = ts->prev;
		te->next = ts;
		ts->prev = te;				
	}
	//cout<<"startPoint is: "<<startPoint->data<<", endPoint is: "<<endPoint->data<<endl;
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
template <class T>
void List<T>::reverse(ListNode * &startPoint, ListNode * &endPoint){
	
	ListNode* ts = startPoint, *te = endPoint;
	startPoint = te;
	endPoint = ts;
	while(ts != te){
	//	cout<<"in while, start is: "<<ts->data<<", end is: "<<te->data<<endl;
		bringBack(ts,te);
	//	cout<<"after bringBack worked start is: "<<ts->data<<", end is: "<<te->data<<endl;
		ts=ts->next;
	}


    /// @todo Graded in MP3.1
}


/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth( int n )
{
	ListNode *tempStart = head, *tempEnd = head;
	while(tempEnd != NULL && tempEnd->next != NULL){
		for(int i = 1; i<n; i++){
			if(tempEnd->next!=NULL)
				tempEnd=tempEnd->next;
			else break;
		}
		reverse(tempStart, tempEnd);
		tempStart=tempEnd=tempEnd->next;
	}
    /// @todo Graded in MP3.1
}


/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall()
{
	if(head == NULL || head->next == NULL)
		return;
	ListNode *current=head, *place;
	if(current != NULL && current->next != NULL){
		current=current->next;
		place = current->next;
	}
	while(current != NULL && current->next != NULL){	
		current->prev->next = place;
		place->prev = current->prev;
		tail->next = current;
		current->next = NULL;
		current->prev = tail;
		tail=current;
		current = place->next;
		if(place!=NULL)
		place = current->next;
	}
    /// @todo Graded in MP3.1
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint)
{
    if (splitPoint > length)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode * secondHead = split(head, splitPoint);

    int oldLength = length;
    if (secondHead == head)
    {
        // current list is going to be empty
        head = NULL;
        tail = NULL;
        length = 0;
    }
    else
    {
        // set up current list
        tail = head;
        while (tail->next != NULL)
            tail = tail->next;
        length = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head = secondHead;
    ret.tail = secondHead;
    if (ret.tail != NULL)
    {
        while (ret.tail->next != NULL)
            ret.tail = ret.tail->next;
    }
    ret.length = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint)
{
	if (splitPoint < 0) return NULL; 
	ListNode* temp = start, *ret = NULL;
	for(int i = 1; i < splitPoint; i++){
		if(temp->next != NULL)
			temp = temp->next;
	}
	
	if(temp->next!= NULL)
		ret=temp->next;
	ret->prev = NULL;
	temp->next=NULL;
	return ret;

    /// @todo Graded in MP3.2
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T> & otherList)
{
    // set up the current list
    head = merge(head, otherList.head);
    tail = head;

    // make sure there is a node in the new list
    if(tail != NULL)
    {
        while (tail->next != NULL)
            tail = tail->next;
    }
    length = length + otherList.length;

    // empty out the parameter list
    otherList.head = NULL;
    otherList.tail = NULL;
    otherList.length = 0;
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
template <class T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode * second)
{
	if(first == NULL)
		return second;
	if(second == NULL)
		return first;
	ListNode * curr = first, *SECOND = second;

	while(SECOND != NULL){
		SECOND = second->next;

		while(curr->data < second->data){
			if(curr->next != NULL)
				curr = curr->next;
			else{
				curr->next = second;
				second->prev = curr;
				return first;
			}
		}
		
		if(curr->prev == NULL){
			second->prev = NULL;
			second->next = curr;
			curr->prev = second;
			first = second;
			curr = second;
			second = SECOND;
		}
		
		else{
			second->prev = curr->prev;
			curr->prev->next = second;
			second->next = curr;
			curr->prev = second;
			curr= second;
			second = SECOND;
		}
	}
return first;
    /// @todo Graded in MP3.2
  //  return NULL; // change me!
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort()
{
    if (empty())
        return;
    head = mergesort(head, length);
    tail = head;
    while (tail->next != NULL)
        tail = tail->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the rcursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode * List<T>::mergesort(ListNode * start, int chainLength)
{
		ListNode * pss = start->next;
	if(chainLength == 1) 
		return start;
	if(chainLength == 2){
		pss->prev = NULL;
		start->next = NULL;
		start= merge(start,pss);
		return start; 
		
	}

	ListNode * second = start, *end = start;
	for(int i = 0; i< chainLength/2; i++){
		end = second;
		second = second->next;
	}
	end->next = NULL;
	second->prev = NULL;
	start = mergesort(start,chainLength/2);
	second = mergesort(second,chainLength-(chainLength/2));
	return merge(start,second);
    /// @todo Graded in MP3.2
    //return NULL; // change me!
}
