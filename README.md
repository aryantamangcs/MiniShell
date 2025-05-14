# MiniShell (A minimalist shell built from scratch)

Driven by desire to master Linux internals and sharpen my C skills, I built the **minimalist shell** from scratch.
As a daily linux user, my curiosity led me to **go beyond using just commands** to recreate them throught raw system calls and truly understands what happens under the hood.

## Installation (Only for Linux and Unix)
 1. git clone https://github.com/aryantamangcs/MiniShell.git 
 2. cd MiniShell && make
 3. export PATH="$PATH:."
 4. mini-shell

### Available Commands
1. **ls** (listing the files and folders in current directory)

2. **ls -l -a** (listing the hidden files and folders with more metadata about files) -- stat systemcall wasn't used so only limited metadata are presented

3. **whoami** (current user of the session)

4. **echo output** (echoes the output to the standard output)
   
6. **cd <directory_name>** (changes the current directory to the specified directory)

7. **pwd** (prints the current directory to the standard output)

8. **cat <file_name>** (displays the content of the file)

9. **clear** (clears the screen)

    
#### Screenshots
![ls](https://github.com/user-attachments/assets/9300bc33-e1db-4b52-83e5-01ec0431726f)
![ls-l](https://github.com/user-attachments/assets/96551cc7-d9bc-43f9-a1ac-6e3928e75d54)
![ls-a](https://github.com/user-attachments/assets/07e18b4f-9043-46d9-93ba-bf53dfcb4e8c)
![pwd](https://github.com/user-attachments/assets/8d388cbd-8cf3-4c04-8cd1-0ae25c6a1940)
![cd](https://github.com/user-attachments/assets/2475003a-37d3-42d1-99f5-6656420b57a6)
![cat](https://github.com/user-attachments/assets/b16e17fb-206f-4a62-a702-67e2657e2070)

#### Working Mechanism

1. **ls**

  ls command invokes the opendir() systemcall with an argument of current path. In success, opendir returns the pointer to
  the directory stream. Then we read the entries of the pointed directory stream in a loop using readdir systemcall and displayed it's name

  Similarly with ls -l option/flag we displayed it's inode number, size in bytes and other metadata
  
2. **whoami**

  When whoami is invoked we find the current uid of the invoking process. And we know /etc/passwd contains the information
  where the uid and it's corresponding name is mapped together. We read from the /etc/passwd using read() syscall and find the corresponding name mapped to the uid and displayed it on the 
  standard output 
  
3. **echo**

  we simply write the message to the standard output with fd 1 using write systemcall
  
4. **cat <file_name>**

  we dynamically allocated the memory to the buffer then read the contents of the file, if the size of contents of the file exceeds the
  allocated memory then we reallocated the memory to the buffer without losing it's previous content using realloc() and then write to the standard output
  the file contents.
    
