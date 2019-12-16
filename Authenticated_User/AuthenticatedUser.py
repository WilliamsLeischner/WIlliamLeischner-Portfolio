"""
* William S Leischner
* CS499
* 11/17/2019
* Class is for a authenticated user token that can be passed to a monitoring system which could track
* logon time, access level, password control etc... Used in this program  to hold user access and to diplay
* access information.
"""


class AuthenticatedUser:

    def __init__(self):
        self.userName = ""
        self.hashedPassword = ""
        self.userRole = ""
        
        #accessors
    def getUserName(self):
        return self.userName
   
    def getHashedPassword(self):
        return self.hashedPassword
    
    def getUserRole(self):
        return self.userRole
    
        #mutators
    
    def setUserName(self,userName):
        self.userName = userName
   
    def setHashedPassword(self,hashedPassword):
        self.hashedPassword = hashedPassword
    
    def setUserRole(self,userRole):
        self.userRole = userRole



