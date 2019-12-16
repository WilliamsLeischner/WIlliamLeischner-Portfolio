package authenticationsystem;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Scanner;

/**
 *
 * William S Leischner
 * IT145
 * 08/11/2018
 */

public class AuthenticationSystem{
    
    /*
    * This function takes a string as input and then uses the MD5 hash algorythm and converts the string to a hedecimal 
    * representation and returns as a string.
    */
    public static String convertPasswordString(String inputPasswordString) throws NoSuchAlgorithmException{
		String original = inputPasswordString;
		MessageDigest md = MessageDigest.getInstance("MD5");
		md.update(original.getBytes());
		byte[] digest = md.digest();
                StringBuilder sb = new StringBuilder();
		for (byte b : digest) {
			sb.append(String.format("%02x", b & 0xff));
		}
                return sb.toString(); 
                
    }// End function convertPasswordString
    
    /*
    * This function takes a user Name and pssword and compares the entries to a credential file and returns boolean result.
    * The function uses two buffers inFS, inSS. inFS to get a line of text from the input stream of the file and inSS to hold 
    * the line of text to enable parsing with next() using whitespace as a deliminator.
    */
    
    public static boolean compareResults(String userName, String passwordHashed)throws IOException{
        String lineOfText;               // used to hold line of  text from file stream.
        String userNameToken;            // used to hold user name token parsed from inSS buffer
        String hashedStringToken;        // used to hold hashed string parsed from inSS buffer
        boolean exitCondition = false;   // used to exit while loop
        boolean resultCondition = false; // used to return value of result of comparison
        Scanner inFS;                    // used as a buffer to get line of text from file
        Scanner inSS;                    // used as buffer to hold line of text to enable parsing of the string
        FileInputStream fileByteStream;  // file stream object
        
        fileByteStream = new FileInputStream("c:\\credentials.txt"); // where I put file
        inFS = new Scanner(fileByteStream); // scanner object using file stream as input
        
       
        while(inFS.hasNext() && !exitCondition){ // continue to end of file unless exit condition true
            lineOfText = inFS.nextLine();
            inSS = new Scanner(lineOfText); // pass lineOfText to String Steam used as buffer 
            userNameToken = inSS.next(); // extract 1st token of line
            
            if(userNameToken.equals(userName)){
                hashedStringToken = inSS.next(); // extract 2nd token of line
               if(hashedStringToken.equals(passwordHashed)){
                   // user name and password match exit loop 
                   exitCondition = true;
                   resultCondition = true;
               }
               else{
                   exitCondition = true; // user names match; passwords donot match; exit loop
               } 
            }
            // user names did not match. Continue checking next name in file
        } // end while
        
    fileByteStream.close(); 
    return resultCondition;  
    
    } // end function compareResults
    
    /*
    * Function retrievs user role from file and returns it. The function uses two buffers inFS, inSS. inFS to get a line of text from 
    * the input stream of the file and inSS to hold the line of text to enable parsing with next() using whitespace as a deliminator.
    */
    public static String getRole(String userName) throws FileNotFoundException, IOException{
        String lineOfText;               // used to hold line of text from files stream buffer
        String stringToken = "";         // used to hold tokens from parsed inSS buffer 
        String userToken;                // 1st token extractec from lineOfText being the user Name
        boolean exitCondition = false;
         
        Scanner inFS;                    // used as a buffer to get line of text from file
        Scanner inSS;                    // used as buffer to hold line of text to enable parsing of the string
        FileInputStream fileByteStream;  // used for file stream object
        
        
        fileByteStream = new FileInputStream("c:\\credentials.txt"); // where I put file; open file
        inFS = new Scanner(fileByteStream);
        while(inFS.hasNext()&& !exitCondition){ //continue to end of file unless exit condition true
            lineOfText = inFS.nextLine();
            inSS = new Scanner(lineOfText); // pass lineOfText to String Steam used as buffer 
            userToken = inSS.next();        // extract 1st token of line
            if(userName.equals(userToken)){
                while(inSS.hasNext()){
                    // go to last token of line
                    stringToken = inSS.next();
                }
            }
        }// end while
        
        fileByteStream.close();
        return stringToken;
        
    } // end function getRole
    
    /*
    * Function display a authenticated users role file. Function restrievs user role and appends the name
    * to the filePathName producing complete name and path of the user role file. Function uses a file stream 
    * scanner object to retrieve a line of text from file and displays line line by line until end of file. 
    */
    
    public static void displayOutput(AuthenticatedUser userToken) throws FileNotFoundException{
        String filePathName ="c:\\";
        String userRole = userToken.getUserRole();  // retrieve user role
        String lineOfText;                          // used to hold line of text from file
        
        Scanner inFS;                    // used as a buffer to get line of text from file
        FileInputStream fileByteStream;  // used for file stream object
        
        filePathName = filePathName.concat(userRole); // appennd to end of filePathName
        filePathName = filePathName.concat(".txt");   // add extension to file name
        fileByteStream = new FileInputStream(filePathName);  // open file using a file stream object
        inFS = new Scanner(fileByteStream);                  // create scanner object used as buffer 
        
        System.out.println();
        while(inFS.hasNext()){                        // continue to end of file
            lineOfText = inFS.nextLine();             //get line of text from buffer
            System.out.println(lineOfText);
        }
    } // end function displayOutput
    
    
    /**
     * @param args the command  line arguments
     * @throws java.security.NoSuchAlgorithmException
     * @throws java.io.IOException
     */
    public static void main(String[] args) throws NoSuchAlgorithmException, IOException{
        
        // Create objects
        Scanner scrnInput = new Scanner(System.in);  // object to get input from user using standard in
        
        
        String userName;                             // used to hold userName
        String userPassword;                         // used to hold user password
        String passwordHashed;                       // used to hold converted hashed password
        String clearLineBuffer;                      // used to hold rest of line of current line of text
        AuthenticatedUser userToken = null;          // authenticated users holds attributes of user
        
        int userAttempts = 0;                        // how many failed attempts to authenticate
        char exitCondition = ' ';                    // to exit while loop 
        
        
       while(exitCondition != 'q'&& userAttempts<3){    // loop unitil user enter q to quit or fails 3 login attemps
                                                        // or user enters a vailid user name and password
           System.out.print("Enter User Name or 'q' to quit: ");
           userName = scrnInput.next();
           if(userName.length() == 1 && userName.charAt(0)=='q'){ // user wants to exit
              exitCondition = 'q';
              System.out.println();
              System.out.println("Exiting");
           }
          else{
             System.out.print("Enter password or 'q' to quit: ");
             clearLineBuffer =scrnInput.nextLine(); // clear current buffer to get to next line
             userPassword = scrnInput.nextLine();
             if(userPassword.length()== 1 && userPassword.charAt(0) == 'q'){ // user wants to exit
                exitCondition = 'q';
                System.out.println();
                System.out.println("Exiting");
             }
             else{
                passwordHashed = convertPasswordString(userPassword);
                if(compareResults(userName,passwordHashed)){
                   // vaild username and password create authenticated user token
                   // for a monitoring user system
                   userToken = new AuthenticatedUser();
                   userToken.setUserName(userName);
                   userToken.setHashedPassword(passwordHashed);
                   userToken.setUserRole(getRole(userName));
                   exitCondition = 'q';
                   displayOutput(userToken);
                }
                else{                       // user name or password do not match
                    System.out.println();
                    System.out.println("User Name or Password error:");
                    System.out.println();
                    userAttempts += 1;
                }
             } // end else
             
              
               
          } // end else
             // check for which exit condition exisits
          if(exitCondition != 'q'&& userAttempts == 3){
              System.out.println("Exceeded login attempts. Exiting");
          }
              
       } // end while
    } // end main
} // end AuthenticationSystem
