# Reflections on sorting

## O(n<sup>2</sup>) sorts
Of the three standard intro-to-cs sorting algorithms (bubble, selection, insertion), I find that insertion sort stands out as especially difficult to correctly implement.

I think this can be pretty easily be attributed to the fact that bubble sort and selection sort can be pretty easily translated from the high level concept to C. Swapping is the one gotcha, but it doesn't significantly affect the implementation.

Insertion sort, however, requires that extra bit of effort: manually making space for your insertion. Once the insertion position is found, a second iteration is needed to push everything out of the way to make room. Alternatively, you can work from the end of the sorted portion of the array down and push things out of the way as you go, but this makes it tempting to allow your indexes to go negative or add extra additions and subtractions on the index. The first is dangerous, the second is error prone (and also possibly dangerous). I think the thought needed makes the single iteration version of insertion sort particularly useful for learning - Even in something as simple as sorting, it's easy to shoot yourself in the foot.

# Results

## Random Arrays
![Time to sort shuffled arrays](shuffled.png)

As expected, bubble sort, insertion sort, and selection sort all show an n<sup>2</sup> curve. Bubble sort being significantly more expensive because bubble sort has to perform p<sub>1</sub>*(n-i) swaps to sort each element where n is the length of the array, i is the number of elements that have been already sorted, and p<sub>1</sub> is some likelihood of requiring a swap. 

Surprisingly mergesort, which should be nlog(n) looks awfully similar to insertion sort. This is explained by my poor merge implementation. Since I wanted to do an in-place merge, the merge step degrades to a slighly optimized insertion sort.

Quick Sort is so fast that it is not pictured. At 30,000 elements, it was still only ~15ms.

## Presorted arrays
![Time to sort presorted array](presorted.png)

On presorted arrays, nearly every sort takes less time than my resolution - with the notable exception of selection sort which is nearly unaffected. This can be explained pretty easy:
Bubble Sort - simply iterates through the array, sees that no element needs to be stopped, and terminates. An O(n) operation.
Insertion Sort - looks for the insertion point, but breaks after 1 comparison having already found the insertion point - the current position
Merge Sort - As mentioned, my merge sort implementation is nearly identical to insertion sort
Quick Sort - Works exactly the same, but was so fast in general that it doesn't fit on this graph.
Selection Sort - In order to select the correct element, selection sort still needs to scan from i to the end of the array, which means it retains it's O(n<sup>2</sup>) performance

## Inverse Sorted Arrays
![Time to sort inverse sorted arrays](inversesorted.png)

Analysis to come