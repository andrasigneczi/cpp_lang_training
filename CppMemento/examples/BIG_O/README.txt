Cracing coding interview 6th Edition, page 50

Time Compelxity
---------------
- Big 0, Big Theta, and Big Omega
    - Big O: describes an upper bound on the time.
    - Big Omega: is the equivalent concept but for lower bound.
    - Big Theta: both Omega and O, gives a tight bound on runtime.

- Best Case, Worst Case, and Expected Case


Space Complexity
----------------
Stack space in recursive calls counts, too.

Rules:
- Drop the Constants: O(2N) ==> O(N)
- Drop the Non-Dominant Terms: O(N² + N) ==> O(N²) ; O(N + log N) ==> O(N); O(5*pow(2, N) + 1000*pow(N,100)) ==> O(pow(2,N)
- Multi-Part Algorithms: Add vs. Multiply
- Amortized Time (insertion into dynamically resizing array, X + X/2 + X/4 + X/8 + X/16 + ... + 1 is roughly 2X)
- Log N Runtimes
    - Search in a balanced binary tree or binary search: O(log N)
- Recursive Runtimes> often O(pow(branches,depth))
