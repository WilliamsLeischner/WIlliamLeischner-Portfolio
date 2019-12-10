
package authenticationsystem;

/**
 *
 * William S Leischner
 * IT145
 * 08/13/2018
 */
/*
* Class is for a authenticated user token that can be passed to a monitoring system which could track
* logon time, access level, password control etc... Used in this program  to hold user access and to diplay
* access information.
*/
public class AuthenticatedUser {
    // fields
    private String userName;
    private String hashedPassword;             // holds a hashed password
    private String userRole;                   // hold access level
    
    // default constructor  
    public AuthenticatedUser(){
        this.userName = "";
        this.hashedPassword = "";
        this.userRole = "";
    }
    
    //accessors
    public String getUserName(){
        return userName;
    }
    public String getHashedPassword(){
        return hashedPassword;
    }
    public String getUserRole(){
        return userRole;
    }
    
    // mutators 
    public void setUserName(String userName){
        this.userName = userName;
    }
    public void setHashedPassword(String hashedPassword){
        this.hashedPassword = hashedPassword;
    }
    public void setUserRole(String userRole){
        this.userRole = userRole;
    }
}// end class AuthenticatedUser
