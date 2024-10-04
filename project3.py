from random import seed, sample

def is_sorted(lyst):
    if not isinstance(lyst, list):
        raise TypeError("Input must be a list")
    for item in lyst:
        if not isinstance(item, int):
            raise TypeError("List must contain only integers")
    return all(lyst[i] <= lyst[i + 1] for i in range(len(lyst) - 1))
    
def quicksort(lyst):
    if not isinstance(lyst, list):
        raise TypeError("Input must be a list")
        
    def _quicksort(lyst, comparisons, swaps):
        if len(lyst) <= 1:
            return lyst, comparisons, swaps
            
        pivot = lyst[len(lyst) // 2]
        left = [x for x in lyst if x < pivot]
        middle = [x for x in lyst if x == pivot]
        right = [x for x in lyst if x > pivot]
        
        sorted_left, comparisons, swaps = _quicksort(left, comparisons, swaps)
        sorted_right, comparisons, swaps = _quicksort(right, comparisons, swaps)
        
        return sorted_left + middle + sorted_right, comparisons, swaps
        
    sorted_list, comparisons, swaps = _quicksort(lyst, 0, 0)
    return sorted_list, comparisons, swaps

def selection_sort(lyst):
    if not isinstance(lyst, list):
        raise TypeError("Input must be a list")
        
    comparisons = swaps = 0
    
    for i in range(len(lyst)):
        min_index = i
        for j in range(i + 1, len(lyst)):
            comparisons += 1
            if lyst[j] < lyst[min_index]:
                min_index = j
                
        lyst[i], lyst[min_index] = lyst[min_index], lyst[i]
        swaps += 1
        
    return lyst, comparisons, swaps
    
def insertion_sort(lyst):
    if not isinstance(lyst, list):
        raise TypeError("Input must a list")
        
    comparisons = swaps = 0
    
    for i in range(1, len(lyst)):
        key = lyst[i]
        j = i - 1
        while j >= 0 and key < lyst [j]:
            comparisons += 1
            lyst[j + 1] = lyst[j]
            j -= 1
            swaps += 1
            
        lyst[j + 1] = key
        swaps += 1
        
    return lyst, comparisons, swaps
    
def mergesort(lyst):
    if not isinstance(lyst, list):
        raise TypeError("Input must be a list")
        
    def _mergesort(lyst, comparisons, swaps):
        if len(lyst) <= 1:
            return lyst, comparisons, swaps
            
        mid = len(lyst) // 2
        left, comparisons, swaps = _mergesort(lyst[:mid], comparisons, swaps)
        right, comparisons, swpas = _mergesort(lyst[mid:], comparisons, swaps)
        
        return _merge(left, right, comparisons, swaps)
        
    def _merge(left, right, comparisons, swaps):
        result = []
        i = j = 0
        
        while i < len(left) and j < len(right):
            if left[i] < right[j]:
                result.append(left[i])
                i += 1
            else:
                result.append(right[j])
                j += 1
                swaps += 1
                
            comparisons += 1
            
        result += left[i:]
        result += right[j:]
        
        return result, comparisons, swaps
        
    sorted_list, comparisons, swaps = _mergesort(lyst, 0, 0)
    return sorted_list, comparisons, swaps

def main():
    DATA_SIZE = 100000
    seed(0)
    DATA = sample(range(DATA_SIZE * 3), k=DATA_SIZE)
    test = DATA.copy() 
    
    print("Starting quicksort")
    results = quicksort(test.copy())
    print("Sorted:", is_sorted(results[0]))
    print("Comparisons:", results[1])
    print("Swaps:", results[2])

    print("\nStarting mergesort")
    results = mergesort(test.copy())
    print("Sorted:", is_sorted(results[0]))
    print("Comparisons:", results[1])
    print("Swaps:", results[2])

    print("\nStarting selection_sort")
    results = selection_sort(test.copy())
    print("Sorted:", is_sorted(results[0]))
    print("Comparisons:", results[1])
    print("Swaps:", results[2])

    print("\nStarting insertion_sort")
    results = insertion_sort(test.copy())
    print("Sorted:", is_sorted(results[0]))
    print("Comparisons:", results[1])
    print("Swaps:", results[2])
    

if __name__ == "__main__":
    main()