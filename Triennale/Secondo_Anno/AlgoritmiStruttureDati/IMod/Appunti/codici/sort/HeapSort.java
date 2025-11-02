public class HeapSort {
	
	private int[] myArr;
	
	HeapSort(int[] myArr){
		heapify(myArr);
		heapSort(myArr);
		this.myArr = myArr;
	}
    
    private static void fixHeap(int[] myArr, int arrLen, int index) {
        int maxVal = index;
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        if (leftChild < arrLen && myArr[leftChild] > myArr[maxVal]) {
            maxVal = leftChild;
	        }
        if (rightChild < arrLen && myArr[rightChild] > myArr[maxVal]) {
            maxVal = rightChild;
        }
        if (maxVal != index) {
            // Swap values;
            int quickCopy = myArr[index];
            myArr[index] = myArr[maxVal];
            myArr[maxVal] = quickCopy;
            fixHeap(myArr, arrLen, maxVal);
        }
    }

    
    private static void heapify(int[] myArr) {
        int arrLen = myArr.length;
        int parents = arrLen / 2 - 1;
        // Iterates bottom-up, (I don't need the lheapSort
        for (int i = parents; i >= 0; i--) {
            fixHeap(myArr, arrLen, i);
        }
    }
	
	private static void heapify_recursive(int[] myArr, int pos){
		int leftChild = 2 * pos + 1;
		int rightChild = 2 * pos + 2;
		int myArrLen = myArr.length;
		if(leftChild < myArrLen && rightChild < myArrLen){
			heapify_recursive(myArr, pos);
			heapify_recursive(myArr, pos);
			fixHeap(myArr, myArrLen, pos);
		}
	}

    
    private static void heapSort(int[] heapArr) {
        int quickCopy;
        int fixedLength = heapArr.length;
        for (int i = fixedLength - 1; i > 0; i--) {
            quickCopy = heapArr[0];
            heapArr[0] = heapArr[i];
            heapArr[i] = quickCopy;
            fixHeap(heapArr, fixedLength, i);
        }
    }

    
    public int[] computeArr() {
    	return this.myArr;    	
    }
    
    
    // Testing
    public static void main(String[] args) {
    		int[] myArr = {3,64,21,12,5,89,43,1,765,23,643,11,323,97,10};
    		HeapSort heapsort = new HeapSort(myArr);
    		myArr = heapsort.computeArr();
    		for(int i : myArr) {
    			System.out.printf("%d\t", i);
    		}
    }
}

