## Drill chapter 20
1. Define an array of ints with the ten elements { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }. 

2. Define a vector<int> with those ten elements. 

3. Define a list<int> with those ten elements. 

4. Define a second array, vector, and list, each initialized as a copy of the first array, vector, and list, respectively. 

5. Increase the value of each element in the array by 2; increase the value of each element in the vector by 3; increase the value of each element in the list by 5. 

6. Write a simple copy() operation, Click here to view code image
template<typename Iter1, typename Iter2>          // requires Input_iterator<Iter1>() && Output_iterator<Iter2>() Iter2 copy(Iter1 f1, Iter1 e1, Iter2 f2); that copies [f1,e1) to [f2,f2+(e1–f1)) and returns f2+(e1–f1) just like the standard library copy function. Note that if f1==e1 the sequence is empty, so that there is nothing to copy. 

7. Use your copy() to copy the array into the vector and to copy the list into the array. 

8. Use the standard library find() to see if the vector contains the value 3 and print out its position if it does; use find() to see if the list contains the value 27 and print out its position if it does. The “position” of the first element is 0, the position of the second element is 1, etc. Note that if find() returns the end of the sequence, the value wasn’t found. Remember to test after each step.
 
## Exercises chapter 20
1. If you haven’t already, do all Try this exercises in the chapter. 

2. Get the Jack-and-Jill example from §20.1.2 to work. Use input from a couple of small files to test it. 

3. Look at the palindrome examples (§18.7); redo the Jack-and-Jill example from §20.1.2 using that variety of techniques. 

4. Find and fix the errors in the Jack-and-Jill example from §20.3.1 by using STL techniques throughout. 

5. Define an input and an output operator (>> and <<) for vector. 

6. Write a find-and-replace operation for Documents based on §20.6.2.

7. Find the lexicographical last string in an unsorted vector<string>. 

8. Define a function that counts the number of characters in a Document. 

9. Define a program that counts the number of words in a Document. Provide two versions: one that defines word as “a whitespace-separated sequence of characters” and one that defines word as “a sequence of consecutive alphabetic characters.” For example, with the former definition, alpha.numeric and as12b are both single words, whereas with the second definition they are both two words. 

10. Define a version of the word-counting program where the user can specify the set of whitespace characters. 

11. Given a list<int> as a (by-reference) parameter, make a vector<double> and copy the elements of the list into it. Verify that the copy was complete and correct. Then print the elements sorted in order of increasing value. 

12. Complete the definition of list from §20.4.1–2 and get the high() example to run. Allocate a Link to represent one past the end. 

13. We don’t really need a “real” one-past-the-end Link for a list. Modify your solution to the previous exercise to use 0 to represent a pointer to the (nonexistent) one-past-the-end Link (list<Elem>::end()); that way, the size of an empty list can be equal to the size of a single pointer. 

14. Define a singly-linked list, slist, in the style of std::list. Which operations from list could you reasonably eliminate from slist because it doesn’t have back pointers? 

15. Define a pvector to be like a vector of pointers except that it contains pointers to objects and its destructor deletes each object. 

16. Define an ovector that is like pvector except that the [ ] and * operators return a reference to the object pointed to by an element rather than the pointer. 

17. Define an ownership_vector that hold pointers to objects like pvector but provides a mechanism for the user to decide which objects are owned by the vector (i.e., which objects are deleted by the destructor). Hint: This exercise is simple if you were awake for Chapter 13. 

18. Define a range-checked iterator for vector (a random-access iterator).

19. Define a range-checked iterator for list (a bidirectional iterator). 

20. Run a small timing experiment to compare the cost of using vector and list. You can find an explanation of how to time a program in §26.6.1. Generate N random int values in the range [0:N). As each int is generated, insert it into a vector<int> (which grows by one element each time). Keep the vector sorted; that is, a value is inserted after every previous value that is less than or equal to the new value and before every previous value that is larger than the new value. Now do the same experiment using a list<int> to hold the ints. For which N is the list faster than the vector? Try to explain your result. This experiment was first suggested by John Bentley. 