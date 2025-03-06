from flask import Flask, request, render_template_string

app = Flask(__name__)

@app.route("/")
def index():
    return "<h1>This app is currently in development and only hello functionality is added to it: Use /custom?name=your_input</h1>"

@app.route("/custom")
def ssti():
    name = request.args.get("name", "Guest")
    template = f"Hello {name}"
    return render_template_string(template)

if __name__ == '__main__':
    app.run(debug=False, host='0.0.0.0', port=1337)


