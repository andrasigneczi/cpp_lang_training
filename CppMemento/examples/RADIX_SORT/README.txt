Radix (Bucket) sort

Runtime: O(kn)

Cracking the Coding Interview page 160

Radix sort is a sorting algorithm for integers (and some other data types) that takes advantage of the
fact that integers have a finite number of bits. In radix sort, we iterate through each digit of the number,
grouping numbers by each digit. For example, if we have an array of integers, we might first sort by the
first digit, so that the Os are grouped together. Then, we sort each of these groupings by the next digit. We
repeat this process sorting by each subsequent digit. until finally the whole array is sorted.
Unlike comparison sorting algorithms, which cannot perform better than 0 (n log (n)) in the average
case, radix sort has a runtime of O( kn), where n is the number of elements and k is the number of passes
of the sorting algorithm.

Most Significant Digit (MSD)

Least Significant Digit (LSD)
