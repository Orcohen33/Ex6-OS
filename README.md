# Ex6-OS
Synchronized design patterns.

## Or Cohen & Shlomi Lantser.

# Description

**Question 1-3**
  - You have 3 messages to send from each client to the server.
  - The process by which a message passes:
    1. The server receives the message and inserts it into the **first queue**.
    2. **The first active object** activates the function on the message and activates a **Caeser cipher** on it,
       Then forwards the message to the **second queue**.
    3. **The second active object** takes the message from the **second queue** and runs a function on it that **resizes the letters**,
       Then forwards the message to the **third queue**.
    4. **The third active object** takes the message from the **third queue** and **sends the new message back to the client**.

**Question 4**
  1. The guard class has mutex inside as a variable and the functions `lock()` and `unlock()`
  2. When we calling to the `ptr_change()` the function initilized the Guard and the mutex is activated.
  3. in the `main()` function we created two threads and check if the guard working by changing the ptr twice.

**Question 5**
   1. The singleton class implemented by generic programming.
   2. The singleton class has 2 main functions : `get_instance()` and `destroy()`
   3. When we changing the call to `get_instance()` the mutex protecting the function from other threads
   4. in the main function we initilized file into the singelton and allocate memory into it.

**Question 6**
   1. The server uses the **reactor.cpp** to store all the clients sockets.
   2. The server always recieving messages from the clients
   3. The clients sending message to the server
   4. The server recieving the messages and sending it to every client on his data structor
   5. Every client receiving the message and prints it in the cmd.
   6. When client want to disconnect from the server he can send the command `exit` .



# Diagram of the communication :


Files on this project :


                 
## Running guide:

* Clone this repository
* Open the directory and open it in terminal
* Open cmd and write `make all`


  **Question 1-3**
  
  
    - How to run:
      
      Then write `./main1` to run the server.
      
      Then open another cmd and write `./client` to run the client. (Can be done several times at the same time)

   **Question 4**
   - How to run:
   Open cmd and write `./guard`

   
   **Question 5**
   - How to run:
   Open cmd and write `./singleton()`

   
   **Question 6**
   -How to run:
   Open cmd and write `./poll_server()`
   Open another cmd and write `./poll_client()`
   **NOTE : the server supports many clients and you can alot of clients!**
   



## Video of running:

 - **Question 1-3**:
 

https://user-images.githubusercontent.com/92351152/172062707-d1fafc74-3b49-4efe-a615-61248c08f391.mp4


 
 - **Question 4 + 5**:



https://user-images.githubusercontent.com/92504985/172064039-e9fa1b0c-8794-4795-8a3e-da4072eb79a4.mp4



 - **Question 6**:
 
https://user-images.githubusercontent.com/92504985/172064028-7e1b2ba7-f8b7-4275-bd94-9b0286a708a0.mp4


    
                 
