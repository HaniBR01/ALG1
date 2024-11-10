    #ifndef CIDADE_HPP
    #define CIDADE_HPP

    #include <string>

    using namespace std;

    class Cidade {
    public:
        string nome;

        Cidade(const string& nome) : nome(nome) {}
    };

    #endif
