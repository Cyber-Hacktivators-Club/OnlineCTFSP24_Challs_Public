# Intruder  

## Challenge Description  
An attacker managed to intrude our local network and send suspicious links to most of our employees. One of them clicked it and downloaded a suspicious file and even ran it.
The file happened to contain a malicious exe,this granted the attacker acces to out system.
The attacker only left a message in a file and made changes to ensure persistence.
We managed to get a hold of the attackers activities, Your job is to find out. 
Where was the malicious executable stored(Dir name) ?
In which file did the attacker leave his message? And what is the parent PID of that process
What is the name of the modification he made to ensure persistence and on for what file?

 

## Steps to Solve:  

1. **Where was the malicious executable stored(Dir name) ?**  
   - Open the given file in `Procmon`.  
   - Apply the **File Modification** filter to track changes and identify the path of the malicious `.exe` file.  

2. **In which file did the attacker leave his message?**  
   - Scroll through the logs until you find a file named `Thr33_arms.txt`.  
   - This file appears to follow a **Ben 10**-themed naming convention and is likely created by the attacker.  
   - Check its **Properties** to retrieve the **Parent Process ID (PID)**.  

3. **What is the name of the modification he made to ensure persistence and on for what file?**  
   - The attacker has hidden an entry in the **Run** folder in the **Windows Registry** to maintain persistence.  
   - Apply a **Registry filter** in `Procmon` to locate an entry related to the malicious file.  

4. **Complete the Challenge**  
   - Once you find the registry entry, you have successfully uncovered the persistence mechanism used by the attacker.  



## Answer Key
### Where was the malicious executable stored (Dir name)?
**Answer:** `ProgramData`

### In which file did the attacker leave his message?
**Answer:** `Thr33_arms.txt`

### What is the parent PID of the process where the attacker leaves a message?
**Answer:** `3364`

### What is the name of the modification he made to ensure persistence?
**Answer:** `Omnitr1x`

### The persistence modification is made for what file?
**Answer:** `ben14.exe`


---

## Answer Key
### Through which port did the attacker maintain remote access?
**Answer:** `5539`

### Which malicious file, disguised as a PDF, did the employee download?
**Answer:** `someoneHEHE.exe`

### Which reverse_tcp file communicated with the attacker?
**Answer:** `badla.exe`

### Which shell script did the attacker use to transfer malicious libraries?
**Answer:** `intruude.ps1`

### Which sneaky DLL file did the attacker drop among Zoom files?
**Answer:** `sn34ky.dll`

### What is the parent PID of the process that created the file where the keystrokes were saved?
**Answer:** `2868`

### Which legitimate process was used to run the keylogger?
**Answer:** `notepad.exe`

### A file in the same directory as the keylogger was used to inject malicious DLLs into processes, what is its full path?
**Answer:** `C:\Windows\Logs\sys_inj.exe`