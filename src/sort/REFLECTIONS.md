# Reflections on sorting

### O(n²) sorts
Of the three standard intro-to-cs sorting algorithms (bubble, selection, insertion), I find that insertion sort stands out as especially difficult to correctly implement.

I think this can be pretty easily be attributed to the fact that bubble sort and selection sort can be pretty easily translated from the high level concept to C. Swapping is the one gotcha, but it doesn't significantly affect the implementation.

Insertion sort, however, requires that extra bit of effort: manually making space for your insertion. Once the insertion position is found, a second iteration is needed to push everything out of the way to make room. Alternatively, you can work from the end of the sorted portion of the array down and push things out of the way as you go, but this makes it tempting to allow your indexes to go negative or add extra additions and subtractions on the index. The first is dangerous, the second is error prone (and also possibly dangerous). I think the thought needed makes the single iteration version of insertion sort particularly useful for learning - Even in something as simple as sorting, it's easy to shoot yourself in the foot.


