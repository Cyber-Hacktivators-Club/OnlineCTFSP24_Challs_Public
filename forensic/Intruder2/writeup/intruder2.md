# Intruder 2 - Forensics Challenge  

## Challenge Description  
Who needs persistence when clueless employees keep granting access?  

This time, the attacker did more than just leave a message.  

An employee unknowingly clicked a link for an **Omnitrix giveaway**, downloading what seemed like a harmless **PDF file** but was actually a backdoor. Upon opening it, the attacker gained access to the machine.  

A carefully placed script allowed the attacker to **download malicious SUS files**, enabling keylogging and system compromise.  
The attacker then **injected** malicious files into **legitimate software**, ensuring their continuous execution.  

The **employee responsible was executed**.  

Our forensics team stopped the attack and gathered information, but they couldn't fully assess the damage.  
Maybe you can.  

## Objectives: Find the Following Information  

1. **Through which port did the attacker maintain remote access?**  
2. **Which malicious file, disguised as a PDF, did the employee download?**  
3. **Which reverse_tcp file communicated with the attacker?**  
4. **Which shell script did the attacker use to transfer malicious libraries?**  
5. **Which sneaky DLL file did the attacker drop among Zoom files?**  
6. **What is the parent PID of the process that created the file where the keystrokes were saved?**  
7. **Which legitimate process was used to run the keylogger?**  
8. **A file in the same directory as the keylogger was used to inject malicious DLLs into processes. What is its full path?**  

---  

## **Writeup: How to Solve the Challenge**  

### 1️⃣ Find the Port Used for Remote Access  
- Apply a **Network filter** in **Procmon**.  
- Identify **two connections** to internal network IPs.  
- Look for **192.168.64.142** and note the **port number** used.  

### 2️⃣ Identify the Malicious PDF File  
- Apply a **File Changes filter** in **Procmon**.  
- Find an **.exe file with a PDF icon**.  
- Note its **full name and path**.  

### 3️⃣ Find the Reverse_TCP File  
- Use the **Network filter** again.  
- Filter by **IP: 192.168.64.142** to see which **process is using it**.  

### 4️⃣ Locate the Shell Script Used for Malware Transfer  
- Follow **timestamps** from the **malicious PDF execution**.  
- Identify files dropped by the PDF.  
- One of them will be a **PowerShell script**.  

### 5️⃣ Find the sneaky DLL Dropped in Zoom Files  
- Apply a **Path filter**: `"path contains Zoom"`.  
- Look at the earliest file modifications.  
- The name will make it **obvious**.  

### 6️⃣ Find the Parent PID of the Keystroke Log File  
- Locate the **keystroke log file**.  
- Check the **creation timestamp**.  
- Identify the **Parent PID** of the process that created it.  

### 7️⃣ Identify the Legitimate Process Running the Keylogger  
- Find the **logger’s location**.  
- Check which **legitimate process** is executing it.  

### 8️⃣ Find the Injector File for Malicious DLLs  
- **Filter by the keylogger’s directory**.  
- Find the **injector file**.  
- Note its **full path**.  

---  

### 🏆 **Mission: Complete**