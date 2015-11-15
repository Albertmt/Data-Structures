#include <iostream>

using namespace std;
/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 *  stacks and queues portion of the lab.
 */

/**
 * Sums items in a stack.
 * @param s A stack holding values to sum.
 * @return The sum of all the elements in the stack, leaving the original
 *  stack in the same state (unchanged).
 *
 * @note You may modify the stack as long as you restore it to its original
 *  values.
 * @note You may use only two local variables of type T in your function.
 *  Note that this function is templatized on the stack's type, so stacks of
 *  objects overloading the + operator can be summed.
 * @note We are using the Standard Template Library (STL) stack in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint Think recursively!
 */
template <typename T>
T QuackFun::sum(stack<T> & s)
{
	if (s.empty()) return T(0);
	T a = s.top(), total = T(0);
	s.pop();
	total = a + sum(s);
	s.push(a);
	return total;	


    // Your code here
    //return T(); // stub return value (0 for primitive types). Change this!
                // Note: T() is the default value for objects, and 0 for
                // primitive types
}

/**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 * @param q A queue of items to be scrambled
 *
 * @note Any "leftover" numbers should be handled as if their block was complete.
 * @note We are using the Standard Template Library (STL) queue in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint You'll want to make a local stack variable.
 */
template <typename T>
void QuackFun::scramble(queue<T> & q)
{
    stack<T> s;
	T a;
	int size = (int)q.size(), blockSize = 1;
	for(int i = 1; (i * (i-1))/2 <= size; i++){
		(i*(i+1)/2 <= size)?blockSize=i:blockSize = size -(i*(i - 1))/2; 
		if (i%2 == 1){
			for(int j = 0; j < blockSize; j++){
				a = q.front();
				q.pop();
				q.push(a);
			}
		}
		else{
			for(int j = 0; j < blockSize; j++){
				s.push(q.front());
				q.pop();
			}
			for(int j = 0; j < blockSize; j++){
				q.push(s.top());
				s.pop();
			}		
		}
	}
	
    // optional: queue<T> q2;

    // Your code here
}

/**
 * @return true if the parameter stack and queue contain only elements of exactly
 *  the same values in exactly the same order; false, otherwise.
 *
 * @note You may assume the stack and queue contain the same number of items!
 * @note There are restrictions for writing this function.
 * - Your function may not use any loops
 * - In your function you may only declare ONE local boolean variable to use in your return statement,
 *      and you may only declare TWO local variables of parametrized type T to use however you wish.
 *   No other local variables can be used.
 * - After execution of verifySame, the stack and queue must be unchanged. Be sure to comment your code VERY well.
 */
template <typename T>
bool QuackFun::verifySame(stack<T> & s, queue<T> & q)
{
	
    bool retval = true; // optional
    T temp1; // rename me
    T temp2; // rename :)
/*
 *  I am allowing verifySame() to compare a 
 *  stack and a queue of different sizes too.
 */
	if(s.size() == 1){
/*
 *  In this case the return value is true if
 *  the only element in the stack coincides 
 *  with the last element of the queue.
 *  Moreover, the last element in the queue 
 *  comes out in front.
 */
		retval = (s.top() == q.front());
		temp2 = q.front();
		q.push(q.front());
		q.pop();
	}
/*
 *  Here is the recursive step, which will be performed
 *  as many times as the size of the stack is. Here we also
 *  take care of bringing s and q to their original state.
 */
	else{
		temp1 = s.top();
		s.pop();
		retval = verifySame(s,q);
		temp2 = q.front();
		q.pop();
		q.push(temp2);
		retval = retval && (temp1 == temp2);
		s.push(temp1);
	}
	return retval;
}

