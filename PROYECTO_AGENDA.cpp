#include <iostream>
#include <string>
using namespace std;

class Fecha {
private:
    int dia;
    int mes;
    int anio;

public:
    Fecha()
    {
        dia = 1;
        mes = 1;
        anio = 2000;
    }

    void Registrar()
    {
        cout << "Ingrese el dia: ";
        cin >> dia;

        cout << "Ingrese el mes: ";
        cin >> mes;

        cout << "Ingrese el anio: ";
        cin >> anio;
    }

    void Imprimir()
    {
        cout << dia << "/" << mes << "/" << anio << endl;
    }
    
    bool EsCumpleanios(int diaActual, int mesActual)
    {
        if (dia == diaActual && mes == mesActual)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
    int CalcularEdad(int diaActual, int mesActual, int anioActual)
    {
        int edad = anioActual - anio;

        if (mesActual < mes)
        {
            edad = edad - 1;
        }
        else if (mesActual == mes && diaActual < dia)
        {
            edad = edad - 1;
        }

        return edad;
    }
};

class Contacto {
private:
    string nombre;
    string numero;
    string correo;
    string direccion;
    bool bloqueado;
    bool eliminado;
    Fecha fechaNacimiento;

public:
    Contacto()
    {
        nombre = "No asignado";
        numero = "No asignado";
        correo = "No asignado";
        direccion = "No asignado";
        bloqueado = false;
        eliminado = false;
    }

    void Registrar()
    {
        cout << "Ingrese el nombre completo: ";
        getline(cin >> ws, nombre);

        cout << "Ingrese el numero telefonico: ";
        getline(cin, numero);

        cout << "Ingrese el correo electronico: ";
        getline(cin, correo);

        cout << "Ingrese la direccion: ";
        getline(cin, direccion);

        cout << "\nFECHA DE NACIMIENTO" << endl;
        fechaNacimiento.Registrar();
    }

    void Mostrar()
    {   if (eliminado == true)
        {
            cout << "El contacto esta eliminado." << endl;
            return;
        }
        cout << "\nDATOS DEL CONTACTO" << endl;
        cout << "Nombre: " << nombre << endl;
        cout << "Telefono: " << numero << endl;
        cout << "Correo: " << correo << endl;
        cout << "Direccion: " << direccion << endl;

        cout << "Fecha de nacimiento: ";
        fechaNacimiento.Imprimir();

        if (bloqueado == true)
        {
            cout << "Estado: bloqueado" << endl;
        }
        else
        {
            cout << "Estado: desbloqueado" << endl;
        }
    }
    void Bloquear()
    {   if (eliminado == true)
        {
            cout << "El contacto esta eliminado." << endl;
            return;
        }
        if (bloqueado == true)
        {
            cout << "El contacto ya esta bloqueado." << endl;
        }
        else
        {
            bloqueado = true;
            cout << "Contacto bloqueado correctamente." << endl;
        }
    }

    void Desbloquear()
    {   if (eliminado == true)
        {
            cout << "El contacto esta eliminado." << endl;
            return;
        }
        if (bloqueado == false)
        {
            cout << "El contacto ya esta desbloqueado." << endl;
        }
        else
        {
            bloqueado = false;
            cout << "Contacto desbloqueado correctamente." << endl;
        }
    }
    void Editar()
    {   if (eliminado == true)
        {
            cout << "El contacto esta eliminado." << endl;
            return;
        }
        cout << "\nEDITAR CONTACTO" << endl;
        cout << "Ingrese los nuevos datos." << endl;

        Registrar();

        cout << "\nContacto actualizado correctamente." << endl;
    }
    void Eliminar()
    {
        if (eliminado == true)
        {
            cout << "El contacto ya esta eliminado." << endl;
        }
        else
        {
            eliminado = true;
            cout << "Contacto eliminado correctamente." << endl;
        }
    }
    
    void Buscar()
    {
        if (eliminado == true)
        {
            cout << "No hay un contacto disponible para buscar." << endl;
            return;
        }

        string nombreBuscado;

        cout << "\nBUSCAR CONTACTO" << endl;
        cout << "Ingrese el nombre completo: ";
        getline(cin >> ws, nombreBuscado);

        if (nombre == nombreBuscado)
        {
            cout << "\nContacto encontrado." << endl;
            Mostrar();
        }
        else
        {
            cout << "No se encontro el contacto." << endl;
        }
    }
    
    void ListarCumpleaniosHoy(int diaActual, int mesActual)
    {
        if (eliminado == true)
        {
            cout << "El contacto esta eliminado." << endl;
            return;
        }

        if (fechaNacimiento.EsCumpleanios(diaActual, mesActual))
        {
            cout << "\nHoy es el cumpleanios de "
                << nombre << "." << endl;

            Mostrar();
        }
        else
        {
            cout << "El contacto no cumple anios hoy." << endl;
        }
    }

    void MostrarEdad(int diaActual, int mesActual, int anioActual)
    {
        if (eliminado == true)
        {
            cout << "El contacto esta eliminado." << endl;
            return;
        }

        int edad = fechaNacimiento.CalcularEdad(
            diaActual, mesActual, anioActual
        );

        if (edad < 0)
        {
            cout << "La fecha actual es anterior al nacimiento."
                << endl;
            return;
        }

        cout << "Edad de " << nombre << ": "
            << edad << " anios." << endl;
    }
};
int main()
{
    Contacto contacto01 = Contacto();
    int opcion;
    int diaActual;
    int mesActual;
    int anioActual;

    cout << "REGISTRAR NUEVO CONTACTO" << endl;
    contacto01.Registrar();

    do
    {
        cout << "\nAGENDA DE CONTACTOS" << endl;
        cout << "1. Mostrar contacto" << endl;
        cout << "2. Bloquear contacto" << endl;
        cout << "3. Desbloquear contacto" << endl;
        cout << "4. Editar contacto" << endl;
        cout << "5. Eliminar contacto" << endl;
        cout << "6. Buscar contacto" << endl;
        cout << "7. Cumpleanios de hoy" << endl;
        cout << "8. Mostrar edad" << endl;
        cout << "0. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
            case 1:
                contacto01.Mostrar();
                break;

            case 2:
                contacto01.Bloquear();
                break;

            case 3:
                contacto01.Desbloquear();
                break;
            case 4:
                contacto01.Editar();
                break;
            case 5:
                contacto01.Eliminar();
                break;
            case 6:
                contacto01.Buscar();
                break;
            case 7:
                cout << "Ingrese el dia actual: ";
                cin >> diaActual;

                cout << "Ingrese el mes actual: ";
                cin >> mesActual;

                contacto01.ListarCumpleaniosHoy(diaActual, mesActual);
                break;
            case 8:
                cout << "Ingrese el dia actual: ";
                cin >> diaActual;

                cout << "Ingrese el mes actual: ";
                cin >> mesActual;

                cout << "Ingrese el anio actual: ";
                cin >> anioActual;

                contacto01.MostrarEdad(
                    diaActual, mesActual, anioActual
                );
                break;
            case 0:
                cout << "Programa finalizado." << endl;
                break;

            default:
                cout << "Opcion incorrecta." << endl;
                break;
        }

    } while (opcion != 0);

    return 0;
}