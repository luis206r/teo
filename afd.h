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
    if (fss.size() == 0)
        return "v"; //si no hay estados finales retorno v (vacio)

    else if (fss.size() == 1)
    { //si hay un estadofinal y no esta conectado a los otros estados retorno v (vacio)
        int v = 0;
        for (int i = 0; i < fss.size(); i++)
        {
            for (int j = 0; j < ns; j++)
            {
                if (ft[j].first == fss[i] && j != fss[i])
                    v += 1;
                else if (ft[j].second == fss[i] && j != fss[i])
                    v += 1;
            }
            if (v == 0)
                return "v";
        }
    }

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
                    s = "(" + s + "+1)";
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
                {
                    if (er[1][1].length() == 1)
                        s += er[1][1] + "*";
                    else if (er[1][1].length() > 1) //para no repetir parentesis
                    {
                        /*if ((er[1][1])[0] == '(' && (er[1][1])[er[1][1].length() - 1] == ')')
                            s += er[1][1] + "*";
                        else*/
                        s += "(" + er[1][1] + ")*";
                    }
                }
                //hacia donde voy
                for (int k = 2; k < er.size(); k++)
                {
                    string m = "";
                    if (er[1][k] != "v")
                    {
                        if (er[1][k] == "e")
                            m = s;
                        else
                        {
                            /*if(er[1][k][0]=='('&&er[1][k][er[1][k].length()-1]==')')*/ m = s + er[1][k];
                        }

                        if (er[j][k] == "v" /*|| er[j][k] == "e"*/)
                            if (m == "")
                                er[j][k] = "e";
                            else
                                er[j][k] = m;
                        else //para no repetir parentesis
                        {
                            if (i == ns - 1)
                                er[j][k] = er[j][k] + "+" + m;
                            else /*if (er[j][k] != "")*/
                                er[j][k] = "(" + er[j][k] + "+" + m + ")";
                            /*else
                                er[j][k] = m;*/
                        }
                    }
                }
            }
        }

        //-----------------------
        cout << "\n\n";
        for (int i = 0; i < er.size(); i++)
        {
            cout << endl;
            for (int j = 0; j < er.size(); j++)
            {
                cout << er[i][j] << " ";
            }
        }
        cout << "\n\n";
        //-----------------------

        for (int l = 0; l < er.size(); l++) //elimino fila 1 y columna 1 de mi matriz
        {
            er[l].erase(er[l].begin() + 1);
        }
        er.erase(er.begin() + 1);
    }

    //-----------------------
    cout << "\n\n";
    for (int i = 0; i < er.size(); i++)
    {
        cout << endl;
        for (int j = 0; j < er.size(); j++)
        {
            cout << er[i][j] << " ";
        }
    }
    cout << "\n\n";
    //-----------------------

    string final = "";
    if (er[0][0] != "v")
    {
        final += "(" + er[0][0] + ")*";
    }
    final += er[0][1];
    if (er[1][1] != "v")
        final += "(" + er[0][0] + ")*";

    for (int i = 0; i < final.size(); i++)
    {
        if (final[i] == 'v')
        {
            final = "v";
            break;
        }
    }

    return final;
}
