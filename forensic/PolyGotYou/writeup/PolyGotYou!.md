### **Challenge Name:** PolyGotYou!

**Category:** Forensic / Steganography  
**Difficulty:** Intermediate  
**Value:** 100 points  

#### **Description:**

Some files wear masks, but this one takes it to another level. Unravel its true identity and claim your prize!  
This challenge involves a polyglot file that masquerades as a PDF but also holds another secret in the form of a PNG image. Inside the PDF, you'll find the first half of the flag. But to uncover the second half, you need to dive deeper into the file's true form as a PNG. Editing the file at the binary (hex) level and then converting it to an image will reveal the hidden half of the flag.

#### **Flag Format:**

**Flag:**  
`CHC{Wh4t_Even_1s_Th1s_F1le?!}`  

**Hint:** The PDF holds half of the flag, but the rest is hidden in the polyglot structure. Modify the file and reveal the complete flag!

---

### **Steps to Solve:**

1. **Inspect the file:**  
   Begin by opening the provided file with a PDF viewer. You'll see part of the flag displayed in the text. This is your starting point!

2. **Analyze the file as a polyglot:**  
   The file is not just a PDF. It is also a PNG file embedded within the PDF structure. To reveal the other half of the flag, you'll need to examine the file as a PNG.

3. **Extract the PNG part:**  
   Open the file in a hex editor. You'll notice that the file starts with the standard PDF header (`%PDF`) but also contains the PNG signature (`\x89\x50\x4E\x47\x0D\x0A\x1A\x0A`) further down the file.  
   
   Locate the PNG header and footer in the hex view. The PNG data is embedded within the PDF, and you'll need to isolate it.

4. **Edit the hex and extract the PNG:**  
   Using the hex editor, delete everything before the PNG header and everything after the PNG footer. The result should leave you with just the PNG data.

5. **Save the extracted PNG:**  
   Save the edited data to a new file with a `.png` extension.

6. **View the PNG:**  
   Open the new PNG file in an image viewer. The second half of the flag will be revealed, completing the entire flag.

7. **Submit the full flag:**  
   Combine the first half of the flag (from the PDF) and the second half (from the PNG) to reveal the full flag.

---

### **Writeup Example:**

**Step 1:** I opened the polyglot file in a PDF reader and found part of the flag:  
`CHC{Wh4t_Even_1s_Th1s_`  

**Step 2:** I opened the file in a hex editor. I noticed that the file contained both the PDF header (`%PDF`) and the PNG signature (`\x89\x50\x4E\x47...`).  

**Step 3:** I found the PNG data embedded after the PDF header. Using the hex editor, I removed everything before the PNG header and after the PNG footer.

**Step 4:** I saved the edited data to a new file with a `.png` extension and opened it in an image viewer.

**Step 5:** The second half of the flag was revealed:  
`F1le?!}`  

**Final Flag:**  
`CHC{Wh4t_Even_1s_Th1s_F1le?!}`

---

### **Hints:**

1. **Hex Editing:** You will need to be familiar with hex editing and understanding file signatures.
2. **Polyglot Files:** The file behaves as both a PDF and a PNG, so extracting the PNG from the file will require some careful manipulation.
3. **File Signatures:** Remember that PDF and PNG files have distinct signatures. Finding and extracting the PNG part is the key.