import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Random;

public class SortingTest
{
	public static void main(String args[])
	{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

		try
		{
			boolean isRandom = false;	// 입력받은 배열이 난수인가 아닌가?
			int[] value;	// 입력 받을 숫자들의 배열
			String nums = br.readLine();	// 첫 줄을 입력 받음
			if (nums.charAt(0) == 'r')
			{
				// 난수일 경우
				isRandom = true;	// 난수임을 표시

				String[] nums_arg = nums.split(" ");

				int numsize = Integer.parseInt(nums_arg[1]);	// 총 갯수
				int rminimum = Integer.parseInt(nums_arg[2]);	// 최소값
				int rmaximum = Integer.parseInt(nums_arg[3]);	// 최대값

				Random rand = new Random();	// 난수 인스턴스를 생성한다.

				value = new int[numsize];	// 배열을 생성한다.
				for (int i = 0; i < value.length; i++)	// 각각의 배열에 난수를 생성하여 대입
					value[i] = rand.nextInt(rmaximum - rminimum + 1) + rminimum;
			}
			else
			{
				// 난수가 아닐 경우
				int numsize = Integer.parseInt(nums);

				value = new int[numsize];	// 배열을 생성한다.
				for (int i = 0; i < value.length; i++)	// 한줄씩 입력받아 배열원소로 대입
					value[i] = Integer.parseInt(br.readLine());
			}

			// 숫자 입력을 다 받았으므로 정렬 방법을 받아 그에 맞는 정렬을 수행한다.
			while (true)
			{
				int[] newvalue = (int[])value.clone();	// 원래 값의 보호를 위해 복사본을 생성한다.

				String command = br.readLine();

				long t = System.currentTimeMillis();
				switch (command.charAt(0))
				{
					case 'B':	// Bubble Sort
						newvalue = DoBubbleSort(newvalue);
						break;
					case 'I':	// Insertion Sort
						newvalue = DoInsertionSort(newvalue);
						break;
					case 'H':	// Heap Sort
						newvalue = DoHeapSort(newvalue);
						break;
					case 'M':	// Merge Sort
						newvalue = DoMergeSort(newvalue);
						break;
					case 'Q':	// Quick Sort
						newvalue = DoQuickSort(newvalue);
						break;
					case 'R':	// Radix Sort
						newvalue = DoRadixSort(newvalue);
						break;
					case 'X':
						return;	// 프로그램을 종료한다.
					default:
						throw new IOException("잘못된 정렬 방법을 입력했습니다.");
				}
				if (isRandom)
				{
					// 난수일 경우 수행시간을 출력한다.
					System.out.println((System.currentTimeMillis() - t) + " ms");
				}
				else
				{
					// 난수가 아닐 경우 정렬된 결과값을 출력한다.
					for (int i = 0; i < newvalue.length; i++)
					{
						System.out.println(newvalue[i]);
					}
				}

			}
		}
		catch (IOException e)
		{
			System.out.println("입력이 잘못되었습니다. 오류 : " + e.toString());
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
    //bubble : 직접 구현하였습니다.
	private static int[] DoBubbleSort(int[] value) {
        for(int i = 0 ; i < value.length ; i++) {
            for(int j = 0 ; j < value.length - (i+1) ; j++) {
                if(value[j] > value[j + 1]) {
                    int tmp = value[j+1];
                    value[j+1] = value[j];
                    value[j] = tmp; //swap value[j] <-> value[j+1]
                }
            }
        }
		return (value);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
    //insetion : copy from <wikipedia> 참고하였습니다.
    private static int[] DoInsertionSort(int[] value) {
        for(int i = 1 ; i < value.length ; i++) {
            int j = i - 1; // assumption : 0~(i-1) is sorted already
            int temporal = value[i];
            while(j >= 0) {
                if(temporal < value[j]) {
                    value[j+1] = value[j]; // move one block
                    j--;
                }
                else //find the proper location
                    break;
            }
            value[j + 1] = temporal;
        }
		return (value);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
    //heap : copy from <관계 중심의 사고법 : 쉽게 배우는 알고리즘(문병로 교수님 저)> 참고하였습니다.
    private static void heapify(int[] arr, int k, int n) { //k is root node
	    int left, right, larger;
	    if(k != 0) {
            left = 2 * k + 1; //left child of root
            right = 2 * k + 2; //right child of root
        }
        else {
	        left = 1;
	        right = 2;
        }

        //find larger child and compare with root
        if (right <= n - 1) { //exists right child -> compare right vs left for larger one
            if (arr[left] > arr[right])
                larger = left;
            else
                larger = right;
        }
        else if (left <= n - 1) { // only left child
            larger = left;
        }
        else
            return; // root has no child -> already heap

        if (arr[larger] > arr[k]) { //if root is smaller
            int temp = arr[k];
            arr[k] = arr[larger];
            arr[larger] = temp; //swap root and largest child
            heapify(arr, larger, n); //recursive call
        }
    }

    private static void buildheap (int[] arr, int n) {
	    for(int i = n/2 ; i >= 0 ; i--) {
	        heapify(arr,i, n);
        }
    }
	private static int[] DoHeapSort(int[] value)
	{
        buildheap(value, value.length); //make heap

        for(int i = value.length - 1 ; i >= 1 ; i--) {
            int temp = value[i];
            value[i] = value[0];
            value[0] = temp; //swap value[i](leaf) <-> value[0](root)
            heapify(value, 0, i ); // heapify value[0~(i-1)]
        }
		return (value);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
    //merge : 직접 구현하였습니다.
    private static int[] merge(int[] arr1, int[] arr2) {
	    int i = 0;
	    int j = 0;
	    int k = 0;
	    int l1 = arr1.length;
	    int l2 = arr2.length;
	    int[] merged = new int[l1 + l2];
	    while(i < l1 && j < l2) { //fill by order
	        if(arr1[i] < arr2[j])
	            merged[k++] = arr1[i++];
	        else
	            merged[k++] = arr2[j++];
        }
        while(i < l1) //fill the remain
            merged[k++] = arr1[i++];
	    while(j < l2) //fill the remain
            merged[k++] = arr2[j++];
	    return merged;
    }

	private static int[] DoMergeSort(int[] value)
	{
        int l = value.length;
        int m = l/2;
        int[] arr1 = new int[m];
        int[] arr2 = new int[l - m];
        for(int i = 0 ; i < m ; i ++) {
            arr1[i] = value[i];
        }
        for(int j = 0 ; j < (l - m) ; j++) {
            arr2[j] = value[j + m];
        }
        if(value.length != 1) {
            arr1 = DoMergeSort(arr1);
            arr2 = DoMergeSort(arr2);
            value = merge(arr1, arr2);
        }
		return (value);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
    //Quick : 강의 자료를 참고하였습니다.
    private static int partition(int[] arr, int start, int last) {
        if(last > start) { //if length > 1
            int pivot = arr[last]; //last element is pivot
            int locapivot = last;
            for (int i = last - 1 ; i >= start ; i--) {
                if (arr[i] > pivot) {
                    locapivot--;
                    int temp = arr[i];
                    arr[i] = arr[locapivot];
                    arr[locapivot] = temp; //a[i] <-> a[locapivot]
                }
            } //now locapivot - 1 < pivot, locapivot >= pivot ==> pivotloca = rank of a[last]
            int temp = arr[last];
            arr[last] = arr[locapivot];
            arr[locapivot] = temp;//a[locapivot] <-> a[last]
            return locapivot;
            }
	    return last; //if length = 1
    }
    private static void QuickSort(int[] arr, int first, int last) {
	    int pivotloca = partition(arr, first , last);
	    if(last > first) { // if length > 1
	        QuickSort(arr, first, pivotloca - 1);
	        QuickSort(arr, pivotloca + 1, last);
        }
    }
	private static int[] DoQuickSort(int[] value)
	{
        QuickSort(value, 0 , value.length - 1);
		return (value);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
    //radix : copy from "관계 중심의 사고법 : 쉽게 배우는 알고리즘(문병로 교수님 저)" & geeksforgeeks 참고하였습니다.
    private static void eachdigit(int[] arr, int mod) { //implement by count sort
	    int[] store = new int[10]; // 0~9 for mod 10
	    int[] temp = new int[arr.length];
	    for(int i = 0 ; i < 10 ; i++) { // save the count of each digit in list of length 10
            store[i] = 0;
        }
	    for(int i = 0 ; i < arr.length ; i++) { //count of element for each digit
            store[(arr[i] / mod) % 10]++;
        }
        for(int i = 1 ; i < 10 ; i++) { //cumsum of element that digit is <= i -> rank of digit i
	        store[i] = store[i] + store[i-1];
        }
        for(int i = arr.length-1 ; i >= 0 ; i--) {
	        temp[store[arr[i] / mod % 10] - 1] = arr[i]; //store contains cumsum which is smaller = rank -> directs to location in sorted array
            store[arr[i] / mod % 10]--;
        }
        for(int i = 0 ; i < arr.length ; i++) { //copy to original array
	        arr[i] = temp[i];
        }
    }

	private static int[] DoRadixSort(int[] value)
	{
        int[] negatemp = new int[value.length];
        int[] positemp = new int[value.length];
        int j = 0;
        int k = 0;
        int negcnt = 0; //num of -
        int posicnt = 0; // num of + or 0
        int maxloca = 0; //location for maximum
        int minloca = 0; //location for minimum

        for(int i = 0 ; i < value.length ; i++) {
            if(value[i] < 0) {
                negcnt++;
                negatemp[j++] = -(value[i]+1); //convert neg to pos : to use radix. but as neg and posi are asymmetric -> + 1
            }
            else {
                posicnt++;
                positemp[k++] = value[i];
            }
            if(value[i] > value[maxloca])
                maxloca = i;
            if(value[i] < value[minloca])
                minloca = i;
        }

        int[] negaonly = new int[negcnt];
        for(int i = 0 ; i < negcnt ; i++) {
            negaonly[i] = negatemp[i]; // converted num
        }
        int[] posionly = new int[posicnt];
        for(int i = 0 ; i < posicnt ; i++) {
            posionly[i] = positemp[i];
        }

        int max = value[maxloca];

        int min = -(value[minloca]+1); // prevent case of overflow

        int d = 1;
        if(negcnt != 0) { //exists negative num
            while(min / d > 0) { //digit of min value
                eachdigit(negaonly, d);
                d = d * 10;
            }
        }

        d = 1; //reset
        if(posicnt != 0) { //exists positive num
            while(max / d > 0) { //digit of max value
                eachdigit(posionly, d);
                d = d * 10;
            }
        }

        int l = 0;

        for (int i = negcnt - 1 ; i >= 0; i--) // for neg num : reversed order should be implemented
            value[l++] = -negaonly[i] - 1; //fix to original number
        for (int i = 0; i < posicnt ; i++) //for posi num : same order
            value[l++] = posionly[i];

		return (value);
	}
}
