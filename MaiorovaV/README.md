## Instructions
1. Build Image  
```docker build . -f Dockerfile.MaiorovaV -t maiorova-v-fastapi-webapp```
2. Launch Container
```docker run -p 8080:8080 maiorova-v-fastapi-webapp```  
3. Open Hello World page
<http://localhost:8080/>