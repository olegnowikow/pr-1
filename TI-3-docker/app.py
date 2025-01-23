from flask import Flask
app = Flask(name)

@app.route('/')
def tell_hi():
  return 'hi'

if name == 'main':
  app.run(host='0.0.0.0', port=25565)
