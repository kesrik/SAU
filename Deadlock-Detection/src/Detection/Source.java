package Detection;

import java.util.Scanner;

public class Source {

	public static void print1DMatrix(int[] matrix) {
		for (int i = 0; i < matrix.length; i++) {
			System.out.printf("%d ", matrix[i]);
		}
		System.out.println();
	}

	public static boolean isRowZero(int[][] array, int index) {
		for (int i = 0; i < array[0].length; i++) {
			if (array[index][i] != 0) {
				return false;
			}
		}
		return true;
	}

	public static boolean isAllTrue(boolean[] array) {
		for (int i = 0; i < array.length; i++) {
			if (!array[i]) 
				return false;
		}
		return true;
	}

	public static boolean isEnough(int[][] req, int[] wrk, int index) {
		for (int i = 0; i < wrk.length; i++) {
			if (req[index][i] > wrk[i]) 
				return false;
		}
		return true;
	}

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		System.out.println("Enter the number of processes: ");
		int processCount = sc.nextInt();

		System.out.println("Enter the number of resource types: ");
		int resourceTypes = sc.nextInt();

		int[] work = new int[resourceTypes];
		int[] available = new int[resourceTypes];

		int[] executionOrder = new int[processCount];

		boolean[] finished = new boolean[processCount];

		int[][] request = new int[processCount][resourceTypes];
		int[][] allocation = new int[processCount][resourceTypes];
		
		System.out.printf("\nEnter %d numbers for the available matrix (You can enter the numbers as \n\"45 65 23...\" ", resourceTypes);
		for (int i = 0; i< resourceTypes;i++)
			available[i] = sc.nextInt();

		for (int i = 0; i < resourceTypes; i++) 
			work[i] = available[i];

		System.out.printf(
				"\nEnter %d numbers for the allocation matrix (You can enter the numbers as \n\"45 65 23 ...\n 42 28 53 ...\n 68 25 31 ...\")\n\n",
				resourceTypes * processCount);
		for (int i = 0; i < processCount; i++) {
			for (int j = 0; j < resourceTypes; j++)
				allocation[i][j] = sc.nextInt();
		}

		System.out.printf(
				"Enter %d numbers for the request matrix (You can enter the numbers as \n\"45 65 23 ...\n 42 28 53 ...\n 68 25 31 ...\")\n\n",
				resourceTypes * processCount);
		for (int i = 0; i < processCount; i++) {
			for (int j = 0; j < resourceTypes; j++) 
				request[i][j] = sc.nextInt();
		}

		for (int i = 0; i < processCount; i++) {
			if (isRowZero(allocation, i))
				finished[i] = true;
			else
				finished[i] = false;
		}

		int counter = 0;
		int order = 0;
		while (true) {
			if (counter > Math.pow(processCount, 2))
				break;

			for (int i = 0; i < processCount; i++) {
				if (finished[i])
					continue;
				if (isEnough(request, work, i)) {
					for (int j = 0; j < resourceTypes; j++)
						work[j] += allocation[i][j];
					executionOrder[order] = i;
					finished[i] = true;
					order++;
				} else
					finished[i] = false;
			}
			if (isAllTrue(finished))
				break;
			counter++;
		}

		if (isAllTrue(finished))
			System.out.println("not deadlock\n");
		else
			System.out.println("deadlock\n");

		System.out.print("work: ");
		print1DMatrix(work);

		System.out.print("available: ");
		print1DMatrix(available);
		
		if (isAllTrue(finished)) {
			System.out.print("execution order: ");
			print1DMatrix(executionOrder);
		}
		else {
			for (int i = 0; i< processCount;i++) {
				if (!finished[i])
					System.out.printf("%d. process deadlock\n", i);
			}
		}

		sc.close();
	}

}
