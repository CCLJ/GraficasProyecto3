# Volumetric Visualization

Para correr el proyecto es necesario tener instalado C++ y las librerias OpenGL y GLUT.
Una vez teniendo esto para generar el ejecutable corremos:
`$ g++ project.cpp -L/System/Library/Frameworks -framework OpenGl -framework GLUT -o project -Wno-deprecated-declarations`
y para ejecutarlo corremos:
`$ ./project`

El proyecto recibe la informacion de un cubo en un archivo txt. 
El formato es el siguiente:
```
# largo ancho alto
5 5 5
# informacion
1
2
3
...
125
```

Si queremos podemos generar un archivo con información aleatoria. Para esto generamos programa en C++. Lo compilamos de la siguiente manera
`$ g++ random.cpp -o random`
Y lo ejecutamos:
`$ ./random`
El programa nos va a pedir el tamaño de un cubo perfecto y generara un archivo `info_random.txt` que le podemos pasar al ejecutable `project`.