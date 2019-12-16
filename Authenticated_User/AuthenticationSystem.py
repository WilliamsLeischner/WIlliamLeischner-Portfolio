import hashlib
import os

import AuthenticatedUser

"""
 * William S Leischner
 * IT145
 * 08/11/2018
"""

FILE_PATH = 'C:'
CREDENTIAL_FILE_PATH = 'c:\\credentials.txt'


class AuthenticationSystem:

    @staticmethod
    def convertPasswordString(inputPasswordString):
        """
        This function takes a string as input and then uses the MD5 hash algorythm and converts the string to a hedecimal representation and returns as a string.
        :param inputPasswordString:
        :return:
        """
        m = hashlib.md5()
        m.update(inputPasswordString.encode("utf-8"))
        return m.hexdigest()

    @staticmethod
    def compareResults(userName, passwordHashed):
        """
        This function takes a user Name and pssword and compares the entries to a credential file and returns boolean result.
        The function uses two buffers inFS, inSS. inFS to get a line of text from the input stream of the file and inSS to hold
        the line of text to enable parsing with next() using whitespace as a deliminator.
        :param userName:
        :param passwordHashed:
        :return:
        """
        with open(CREDENTIAL_FILE_PATH) as f:
            lines = f.readlines()
        lines = [x.strip() for x in lines]
        for line in lines:
            items = line.split('\t')
            if userName == items[0] and items[1] == passwordHashed:
                return True
        return False

    @staticmethod
    def getRole(userName):
        """
        Function retrievs user role from file and returns it. The function uses two buffers inFS, inSS. inFS to get a line of text from
        the input stream of the file and inSS to hold the line of text to enable parsing with next() using whitespace as a deliminator.
        :return:
        """
        with open(CREDENTIAL_FILE_PATH) as f:
            lines = f.readlines()
        lines = [x.strip() for x in lines]
        for line in lines:
            items = line.split('\t')
            if userName == items[0]:
                return items[-1]
        return ""

    @staticmethod
    def displayOutput(userToken):
        filePathName = "{0}{1}{2}.txt".format(FILE_PATH, os.path.sep, userToken.getUserRole())
        if not os.path.exists(filePathName):
            print("{0} not exists".format(filePathName))
            return
        with open(filePathName) as f:
            lines = f.readlines()
        lines = [x.strip() for x in lines]
        for line in lines:
            print(line)


def main():
    exitCondition = ''
    userAttempts = 0
    while exitCondition != 'q' and userAttempts < 3:
        userName = input("Enter User Name or 'q' to quit: ")
        if len(userName) == 1 and userName[0] == 'q':
            exitCondition = 'q'
            print("\nExiting")
        else:
            userPassword = input("Enter password or 'q' to quit: ")
            if len(userPassword) == 1 and userPassword[0] == 'q':
                exitCondition = 'q'
                print("\nExiting")
            else:
                passwordHashed = AuthenticationSystem.convertPasswordString(userPassword)
                if AuthenticationSystem.compareResults(userName, passwordHashed):
                    userToken = AuthenticatedUser.AuthenticatedUser()
                    userToken.setUserName(userName)
                    userToken.setHashedPassword(passwordHashed)
                    userToken.setUserRole(AuthenticationSystem.getRole(userName))
                    exitCondition = 'q'
                    AuthenticationSystem.displayOutput(userToken)
                else:
                    print("\nUser Name or Password error:\n")
                    userAttempts += 1
        if exitCondition != 'q' and userAttempts == 3:
            print("Exceeded login attempts. Exiting")


if __name__ == "__main__":
    main()
