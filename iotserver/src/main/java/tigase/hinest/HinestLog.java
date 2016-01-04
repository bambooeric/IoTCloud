package tigase.hinest;

public class HinestLog {
	
	public static Boolean debug = true;
	
	public static void debug(String str){
		if(debug){
			System.out.println(str);
		}	
	}

}
