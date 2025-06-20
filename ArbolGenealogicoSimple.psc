Algoritmo ArbolGenealogicoSimple
	
    Definir nombreRaiz Como Cadena
    Definir hijo1 Como Cadena
    Definir hijo2 Como Cadena
    Definir respuesta Como Cadena
    Definir nombrePadre Como Cadena
    Definir nuevoHijo Como Cadena
    Definir tieneHijo1 Como Logico
    Definir tieneHijo2 Como Logico
	
    tieneHijo1 <- Falso
    tieneHijo2 <- Falso
	
    Escribir "Ingrese el nombre del ancestro raíz:"
    Leer nombreRaiz
	
    Repetir
        Escribir "¿Desea agregar un descendiente? (SI/NO):"
        Leer respuesta
		
        Si Mayusculas(respuesta) = "SI" Entonces
            Escribir "Ingrese el nombre del padre:"
            Leer nombrePadre
			
            Si Mayusculas(nombrePadre) = Mayusculas(nombreRaiz) Entonces
                Escribir "Ingrese el nombre del nuevo hijo:"
                Leer nuevoHijo
				
                Si tieneHijo1 = Falso Entonces
                    hijo1 <- nuevoHijo
                    tieneHijo1 <- Verdadero
                Sino
                    Si tieneHijo2 = Falso Entonces
                        hijo2 <- nuevoHijo
                        tieneHijo2 <- Verdadero
                    Sino
                        Escribir "Este padre ya tiene dos hijos."
                    FinSi
                FinSi
            Sino
                Escribir "El padre ingresado no es válido (solo se permite el ancestro raíz en esta versión)."
            FinSi
        FinSi
    Hasta Que Mayusculas(respuesta) <> "SI"
	
    Escribir ""
    Escribir "Recorrido Preorden del árbol:"
    Escribir nombreRaiz
	
    Si tieneHijo1 Entonces
        Escribir hijo1
    FinSi
	
    Si tieneHijo2 Entonces
        Escribir hijo2
    FinSi
	
    Escribir "Fin del recorrido."
	
FinAlgoritmo