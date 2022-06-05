# Ex6-OS
Synchronized design patterns.

## Or Cohen & Shlomi Lantser.

# Description



# Diagram of the communication :


Files on this project :

                 
## Running guide:

* Clone this repository
* Open the directory and open it in terminal


  **Question 1-3**
  
  
    - How to run:
    
      Open cmd and write `make all`
      
      Then write `./main1` to run the server.
      
      Then open another cmd and write `./client` to run the client. (Can be done several times at the same time)
       - You have 3 messages to send from each client to the server.
       - The process by which a message passes:
            1. The server receives the message and inserts it into the **first queue**.
            2. **The first active object** activates the function on the message and activates a **Caeser cipher** on it,
               Then forwards the message to the **second queue**.
            3. **The second active object** takes the message from the **second queue** and runs a function on it that **resizes the letters**,
               Then forwards the message to the **third queue**.
            4. **The third active object** takes the message from the **third queue** and **sends the new message back to the client**.

   **Question 4**
   
   **Question 5**
   
   **Question 6**


## Video of running:

 - **Question 1-3**:
 
 
 - **Question 4**:

 - **Question 5**:

 - **Question 6**

    
                 
