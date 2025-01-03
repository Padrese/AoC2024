import java.io.FileInputStream;
import java.io.InputStream;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.Arrays;

public class ReportsReader {
	
	/*
	Answer between 290 and 346. Should check skipping second condition validity on the dampener and going back
	to precedent states properly.
	*/
	
	public static boolean isValidReport(int[] numbers) {
		String new_state = "none";
		int prec_value = numbers[0];
		int problem_dampener = 0;
		String curr_state = new_state;
		
		for (int i = 1; i < numbers.length; ++i) {
			int curr_value = numbers[i];
			if (new_state != "none") {
				curr_state = new_state;
			}
			
			System.out.println(prec_value);
			System.out.println(curr_value);
			
			if (prec_value < curr_value) {
				new_state = "increasing";
			}
			else if (prec_value > curr_value) {
				new_state = "decreasing";
			}
			else {
				new_state = "none";
				++problem_dampener; //Equality case
				if (problem_dampener > 1) {
					return false;
				}
				continue;
			}
			
			if ((curr_state != "none" && new_state != "none" && curr_state != new_state ) || (Math.abs(curr_value-prec_value) > 3)) {
				System.out.println(new_state);
				System.out.println(curr_state);
				++problem_dampener;
				if (problem_dampener > 1) {
					return false;
				}
				continue;
			}
			
			prec_value = curr_value;
			
		}
		return true;
	}
	
	public static void main(String args[]) throws FileNotFoundException {
		
		final long startTime = System.currentTimeMillis();
		
		String path = "input/input.txt";
		InputStream file = new FileInputStream(path);
		Scanner input = new Scanner(file);
		
		long valid_reports = 0;
		
		while (input.hasNextLine()) {
            String report = input.nextLine();
            int[] numbers = Arrays.stream(report.split(" ")).mapToInt(Integer::parseInt).toArray();
            boolean isValid = isValidReport(numbers);
            System.out.println(isValid);
            if (isValid) {
            	++valid_reports;
            }
            
            int[] test = {2,2,1,0};
            isValid = isValidReport(test);
            System.out.println(isValid);
            
        }
		
        input.close();
        System.out.println("Number of valid reports: " + valid_reports);
        
        final long endTime = System.currentTimeMillis();
        System.out.println("Total execution time: " + (endTime - startTime) + " ms");
	}

}
