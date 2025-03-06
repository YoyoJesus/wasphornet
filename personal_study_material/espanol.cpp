#include <iostream>
#include <deque>
#include <string>
#include <algorithm>

using std::cout; using std::endl; using std::cin;
using std::deque; using std::string;

#define principal main
#define entro int
#define cafuera cout
#define cen cin
#define finl endl
#define para for
#define empujar_hacia_atras push_back
#define constante const
#define cadena string
#define generar generate
#define comenzar begin
#define fin end
#define devolver return
#define vacio void
#define estructura struct
#define booleano bool
#define clasificar sort

estructura Persona{
    cadena nombre;
    entro edad;

    vacio imprimir() const{
        cafuera << nombre << ", edad: "<< edad << finl;
    }

    booleano operator<(constante Persona &p) const{
        devolver edad < p.edad;
    }
};

cadena nombres[] = {"Juan", "Maria", "Pedro", "Luis", "Ana", "Rosa", "Carlos", "Jose", "Luisa", "Marta",
                    "Alberto", "Fernando", "Raul", "Sofia", "Laura", "Carmen", "Ricardo", "Roberto", "Javier", "Miguel"};


entro principal(){
    cout << "Hola Mundo!" << finl;

    entro x;
    cafuera << "Ingrese un numero: ";
    cen >> x;
    cafuera << "El numero que ingreso es: " << x << finl;

    deque<entro> d;
    para(entro i = 0; i < 10; i++){
        d.empujar_hacia_atras(i);
    }

    para(constante entro &i : d){
        cafuera << i << " ";
    }
    cafuera << finl;

    deque<Persona> personas;
    para(constante cadena &nombre : nombres){
        personas.empujar_hacia_atras({nombre, 20 + rand() % 30});
    }

    clasificar(personas.comenzar(), personas.fin());

    para(constante Persona &p : personas){
        p.imprimir();
    }
}