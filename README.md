# Simple C TCP Server
## Build docker image
```
docker build -t alpine_c_lang .
```
## Compile
```
docker run -w /home -v ${PWD}/src:/home --rm -it alpine_c_lang make
```
## Run
```
docker run -w /home -v ${PWD}/src:/home -p 8080:80 --rm -it alpine_c_lang ./server
```
## Test
```
curl localhost:8080
```
