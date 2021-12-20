Quick sort picks a random element as a "pivot" and then
swaps values in the array such that the elements less than pivot appear before elements greater than pivot.
This gives a "partial sort:'Then it recursively sorts the left and right sides using a similar process.

- Best Case: If all elements are equal, then quick sort will, on average, just traverse through the array once.
This is O(N). (This actually depends slightly on the implementation of quick sort. There are implementa-
tions, though, that will run very quickly on a sorted array.)

- Worst Case: What if we get really unlucky and the pivot is repeatedly the biggest element in the array?,
(Actually, this can easily happen. If the pivot is chosen to be the first element in the subarray and the
array is sorted in reverse order, we'll have this situation.) In this case, our recursion doesn't divide the
array in half and recurse on each half. It just shrinks the subarray by one element. This will degenerate
to an O(N²) runtime.

- Expected Case: Usually, though, these wonderful or terrible situations won't happen. Sure, sometimes
the pivot will be very low or very high, but it won't happen over and over again. We can expect a runtime
of O(N log N) .


Cracking the Coding Interview page 160
