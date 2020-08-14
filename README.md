## NodeJS/C++ Developer Exam: *Display Manager*
by: Mar Kenneth Balba

balba.ken@gmail.com


Used Nan library to make add-on functions to Node.js "main" file.

Output:

    1. Developed a node module that exports addon functions through NAN library
    
    2. Developed a DisplayManager Class which I use to create NAN objects and call functions
    
    3. Created a function that enumerates attached displays
    
    4. Added a function that Requests the displays to sleep
    
    5. Added a function that Requests the displays to wake by simulating a mouse movement 
    
        a. Reference: https://docs.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-input
        
    6. Added a function that returns the last input time
    
        a. Done by saving the first input time during DisplayManager constructor call then subtracting current tick with it
        
    7. Added Unit tests using Jest
    
        a. Not able to test C++ part with this :(
