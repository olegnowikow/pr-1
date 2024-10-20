# Docker project
Docker image test  
## Dependencies
Docker and Internet connection
## Usage
1. Remove ".AD-158" from Dockerfile filename  
2. Build Image  
```docker build -t flask-hello-world .```
### Launch via
```docker run -p 5000:5000 flask-hello-world```  
### View results
<http://localhost:5000/>