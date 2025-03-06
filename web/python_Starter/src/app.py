from flask import Flask, request
import subprocess
import os

app = Flask(__name__)
SECRET = os.urandom(16)
#print(SECRET.hex())

@app.route('/')
def index():
    try:
        result = subprocess.run(
            ["python3", "./hello.py"],
            capture_output=True,
            text=True,
            check=True
        )
        output = result.stdout
    except subprocess.CalledProcessError as e:
        output = f"An error occurred: {e}"
    return output

@app.route('/write', methods=['GET', 'POST'])
def write_file():
    if request.method == 'POST':
        chcd = request.form.get('chcd')
        chcf = request.form.get('chcf')
        key = request.form.get('key')

        if not chcd or not chcf or not key or not isinstance(chcd, str) or not isinstance(chcf, str) or not isinstance(chcd, str):
            return "Invalid input, parameters must be present and must be strings."
        #HAHAHA Random key so my authentication mechanism is secure i guess
        try:
            key_value = bytes.fromhex(key)
        except:
            return "Key format is not valid. Try with hex"

        if isEqual(SECRET,key_value):
            if os.path.exists(chcf):
                return "Nopes"
        
            with open(chcf, 'w') as f:
                f.write(chcd)
            return "File written successfully!"
            
        else:
            return "Wrong. Try harder!."
    
    return "Nothing done :<"

def hash_function(s):
    return s * 256 + (s)**999999

def isEqual(s1,s2):
    if len(s1) != len(s2): 
        return False
    for i in range(len(s1)):
        if hash_function(s1[i] ^ s2[i]) != 0:
            return False
    return True

if __name__ == '__main__':
    app.run(debug=False, host='0.0.0.0', port=1337)

