# Docker project
Docker image test  
## Dependencies
Docker and Internet connection
## Usage
1. Build Image  
```docker build -t flask-hello-world -f Dockerfile.AD-158 .```
### Launch via
```docker run -p 5000:5000 flask-hello-world```  
### View results
<http://localhost:5000/>