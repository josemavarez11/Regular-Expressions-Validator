#include <iostream>
#include <string>

enum class Estado { INICIO, DIGITO, LETRA, PUNTO, ERROR, ACEPTACION };

class Automata {
public:
    Automata() = default;
    bool validarDigito(const std::string& cadena);
    bool validarLetra(const std::string& cadena);
    bool validarPalabra(const std::string& cadena);
    bool validarNumeroEntero(const std::string& cadena);
    bool validarNumeroReal(const std::string& cadena);
    bool validarIdentificador(const std::string& cadena);
    bool validarOperador(const std::string& cadena);
};

bool Automata::validarDigito(const std::string& cadena) {
    return cadena.length() == 1 && isdigit(cadena[0]);
}

bool Automata::validarLetra(const std::string& cadena) {
    return cadena.length() == 1 && isalpha(cadena[0]);
}

bool Automata::validarPalabra(const std::string& cadena) {
    Estado estado = Estado::INICIO;
    for (char c : cadena) {
        switch (estado) {
            case Estado::INICIO:
                if (isalpha(c)) {
                    estado = Estado::LETRA;
                } else {
                    estado = Estado::ERROR;
                }
                break;
            case Estado::LETRA:
                if (isalpha(c)) {
                    estado = Estado::LETRA;
                } else {
                    estado = Estado::ERROR;
                }
                break;
            default:
                return false;
        }
    }
    return estado == Estado::LETRA;
}

bool Automata::validarNumeroEntero(const std::string& cadena) {
    Estado estado = Estado::INICIO;
    for (char c : cadena) {
        switch (estado) {
            case Estado::INICIO:
                if (isdigit(c)) {
                    estado = Estado::DIGITO;
                } else {
                    estado = Estado::ERROR;
                }
                break;
            case Estado::DIGITO:
                if (isdigit(c)) {
                    estado = Estado::DIGITO;
                } else {
                    estado = Estado::ERROR;
                }
                break;
            default:
                return false;
        }
    }
    return estado == Estado::DIGITO;
}

bool Automata::validarNumeroReal(const std::string& cadena) {
    Estado estado = Estado::INICIO;
    for (char c : cadena) {
        switch (estado) {
            case Estado::INICIO:
                if (isdigit(c)) {
                    estado = Estado::DIGITO;
                } else {
                    estado = Estado::ERROR;
                }
                break;
            case Estado::DIGITO:
                if (isdigit(c)) {
                    estado = Estado::DIGITO;
                } else if (c == '.') {
                    estado = Estado::PUNTO;
                } else {
                    estado = Estado::ERROR;
                }
                break;
            case Estado::PUNTO:
                if (isdigit(c)) {
                    estado = Estado::ACEPTACION;
                } else {
                    estado = Estado::ERROR;
                }
                break;
            case Estado::ACEPTACION:
                if (isdigit(c)) {
                    estado = Estado::ACEPTACION;
                } else {
                    estado = Estado::ERROR;
                }
                break;
            default:
                return false;
        }
    }
    return estado == Estado::ACEPTACION;
}

bool Automata::validarIdentificador(const std::string& cadena) {
    Estado estado = Estado::INICIO;
    for (char c : cadena) {
        switch (estado) {
            case Estado::INICIO:
                if (isalpha(c) || c == '_') {
                    estado = Estado::LETRA;
                } else {
                    estado = Estado::ERROR;
                }
                break;
            case Estado::LETRA:
                if (isalnum(c) || c == '_') {
                    estado = Estado::LETRA;
                } else {
                    estado = Estado::ERROR;
                }
                break;
            default:
                return false;
        }
    }
    return estado == Estado::LETRA;
}

bool Automata::validarOperador(const std::string& cadena) {
    return cadena.length() == 1 && (cadena == "+" || cadena == "-" || cadena == "*" || cadena == "/" || cadena == "%");
}

int main() {
    std::string cadena;
    std::cout << "Introduce una cadena de caracteres: ";
    std::getline(std::cin, cadena);

    Automata automata;

    if (automata.validarDigito(cadena)) {
        std::cout << "Cadena valida como digito: " << cadena << std::endl;
    } else if (automata.validarLetra(cadena)) {
        std::cout << "Cadena valida como letra: " << cadena << std::endl;
    } else if (automata.validarPalabra(cadena)) {
        std::cout << "Cadena valida como palabra: " << cadena << std::endl;
    } else if (automata.validarNumeroEntero(cadena)) {
        std::cout << "Cadena valida como numero entero: " << cadena << std::endl;
    } else if (automata.validarNumeroReal(cadena)) {
        std::cout << "Cadena valida como numero real: " << cadena << std::endl;
    } else if (automata.validarIdentificador(cadena)) {
        std::cout << "Cadena valida como identificador: " << cadena << std::endl;
    } else if (automata.validarOperador(cadena)) {
        std::cout << "Cadena valida como operador: " << cadena << std::endl;
    } else {
        std::cerr << "Error: La cadena no corresponde a ninguna expresion regular valida." << std::endl;
    }

    return 0;
}