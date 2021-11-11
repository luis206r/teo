#include "libs.h"

class AFD
{
private:
    int ns;  //numero de estados
    int is;  //estado inicial
    int nfs; //numero de estados finales

public:
    vector<pair<int, int>> ft; // vector [0]: {1, 0}  // tabla de trancisiones
    vector<int> fss;           //vector de estados finales
    AFD() = default;
    AFD(int n, int a, int b);
    void printft();
    string convert_re();
    void del_st(int index);
};

AFD::AFD(int n, int a, int b)
{
    ns = n;
    int x = pow(2, n);
    is = a;
    nfs = b;
    fss = vector<int>(nfs);
    ft = vector<pair<int, int>>(ns);
}

void AFD::printft()
{
    cout << "\nfuncion de transicion: ";
    cout << "\n\nq  | 0  | 1  ";
    int count = 0;
    for (int i = 0; i < ns; i++)
    {
        cout << "\nq" << i << " | q" << ft[i].first << " | q" << ft[i].second;
    }
    cout << endl
         << endl;
}

string AFD::convert_re()
{

    //=================IMPLEMENTACION DE MATRIZ PARA ER Y NORMALIZACION====================
    vector<vector<string>> er;
    er = vector<vector<string>>(ns + 2, vector<string>(ns + 2, "v")); // 0  1  ε

    er[0][is + 1] = "e";

    for (int i = 1; i <= ns; i++)
    {
        for (int j = 1; j <= ns; j++)
        {
            string s = "";
            if (ft[i - 1].first == j - 1)
                s += "0";
            if (ft[i - 1].second == j - 1)
            {
                if (s == "")
                    s += "1";
                else
                    s += "+1";
            }
            if (s != "")
                er[i][j] = s;
        }
    }

    for (int i = 0; i < nfs; i++)
    { //conecto a los anteriores estados finales con el nuevo estado final
        er[fss[i] + 1][ns + 1] = "e";
    }

    //=============================ELIMINACION DE ESTADOS=============================

    for (int i = 0; i < ns; i++)
    {
        for (int j = 0; j < er.size(); j++)
        {

            string s = "";
            if (er[j][1] != "v" && j != 1)
            {
                if (er[j][1] != "e")
                    s += er[j][1];
                //verifico si tiene bucle
                if (er[1][1] != "v")
                    if (er[1][1].length() == 1)
                        s += er[1][1] + "*";
                    else if (er[1][1].length() > 1) //para no repetir parentesis
                    {
                        if ((er[1][1])[0] == '(' && (er[1][1])[er[1][1].length() - 1] == ')')
                            s += er[1][1] + "*";
                        else
                            s += "(" + er[1][1] + ")*";
                    }
                //hacia donde voy
                for (int k = 2; k < er.size(); k++)
                {
                    string m = "";
                    if (er[1][k] != "v")
                        m = s + er[1][k];
                    if (er[j][k] == "v" || er[j][k] == "e")
                        er[j][k] = m;
                    else //para no repetir parentesis
                    {
                        if (er[j][k] != "" && i == ns - 1)
                            er[j][k] = er[j][k] + "+" + m;
                        else if (er[j][k] != "")
                            er[j][k] = "(" + er[j][k] + "+" + m + ")";
                        else
                            er[j][k] = m;
                    }
                }
            }
        }
        for (int l = 0; l < er.size(); l++) //elimino fila 1 y columna 1 de mi matriz
        {
            er[l].erase(er[l].begin() + 1);
        }
        er.erase(er.begin() + 1);
    }

    string final = "";
    if (er[0][0] != "v")
    {
        final += "(" + er[0][0] + ")*";
    }
    final += er[0][1];
    if (er[1][1] != "v")
        final += "(" + er[0][0] + ")*";

    return final;
}
