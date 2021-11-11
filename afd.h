#include"libs.h"

class AFD{
    private:
    int ns; //numero de estados
    int is; //estado inicial
    int nfs; //numero de estados finales
    
    public:
    vector<pair<int,int>> ft;// vector [0]: {1, 0}  // tabla de trancisiones
    vector<int>fss; //vector de estados finales
    AFD() = default;
    AFD(int n, int a, int b);
    void printft();
    string convert_re();  
    void del_st(int index);
    
};

AFD::AFD(int n, int a, int b){
    ns=n;
    int x = pow(2,n);
    is = a;
    nfs = b;
    fss = vector<int>(nfs);
    ft = vector<pair<int,int>>(ns);
}

void AFD::printft(){
  cout<<"\n\n q  | 0  | 1  ";
  int count =0;
  for(int i=0;i<ns;i++){
    cout<<"\n q"<<i<<" | q"<<ft[i].first<<" | q"<<ft[i].second;
  } 
  cout<<endl<<endl;
}

string AFD::convert_re(){
  
    //implementacion de matriz para ER y normalizacion

    vector<vector<string>> er;
    er = vector<vector<string>>(ns+2, vector<string>(ns+2, "v"));  // 0  1  ε
    for(int i=0;i<ns+2;i++){
      cout<<endl;
      for(int j=0; j<ns+2;j++){
        cout<<er[i][j]<<" ";
      }
      
    }
    er[0][is+1]="e";

    for(int i=1; i<=ns; i++){
        for(int j=1; j<=ns; j++){
            string s="";
            if(ft[i-1].first == j-1) s+="0";
            if(ft[i-1].second==j-1){
                if(s=="")s+="1";
                else s+="+1"; 
            } 
            if (s!="") er[i][j]=s;
        }
    }

    for(int i=0; i<nfs;i++){ //conecto a los anteriores estados finales con el nuevo estado final
      er[fss[i]+1][ns+1]="e";
    }
    
    //=========================================================================
   // cout<< endl<<er[1][2]<<endl;
    cout<<"\n\n    | qs | q0 | q1 | qf |";
    for(int i=0;i<ns+2; i++){
        cout<<endl;
        if (i==0) cout<<" qs |  ";
        else if (i==ns+1) cout<<" qf |  ";
        else cout<<" q"<<i-1<<" |  ";
        for(int j=0;j<ns+2;j++){
            cout << er[i][j] <<" |  ";
        }
    }

    //=========================================================================

    //eliminacion de estados

    for(int i=0; i<ns; i++){
        for(int j=0; j<er.size(); j++){
            string s="";
            if(er[j][1]!="v" && j!=1) {
                if(er[j][1]!="e")s+=er[j][1];    //rev->push_back(i); //almaceno los estados que pueden ir al estado que eliminaré (si i = 0 = qs, si i = ns+1 = qf, si 1<=i<=ns q=i-1);
                //verifico si tiene bucle
                if(er[1][1]!="v")
                   s+="("+er[1][1]+")*";
                //hacia donde voy
                for(int k=2; k<ns+2; k++){
                    string m="";
                    if (er[1][k]!="v") m = s + er[1][k];
                    if(er[j][k]=="v") er[j][k]= m;
                    else er[j][k] = "(" + er[j][k] + "+" + m + ")";
                }
            }
        }
        for(int l=0; l<ns+2; l++){
            er[l].erase(er[l].begin()+1);
        }
        er.erase(er.begin()+1);
    //---------------
         cout<<"\n\n    | qs | q0 | q1 | qf |";
        for(int i=0;i<ns+2; i++){
        cout<<endl;
        if (i==0) cout<<" qs |  ";
        else if (i==ns+1) cout<<" qf |  ";
        else cout<<" q"<<i-1<<" |  ";
        for(int j=0;j<ns+2;j++){
            cout << er[i][j] <<" |  ";
        }
    }
    //-------------------------
    }

    string final ="";
    if(er[0][0]!="v"){
        final += "(" + er[0][0] + ")*";
    }
    final+=er[0][1];
    if (er[1][1] != "v") final += "(" + er[0][0] + ")*";

    return final;
}

