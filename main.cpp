#include <iostream>
#include <string.h>
#include <stack>
#include <queue>
#include <fstream>

using namespace std;

struct Cubiculo {
    int l1;
    int l2;
    int l3;
    int l4;
    
    Cubiculo(){
        l1=0;
        l2=0;
        l3=0;
        l4=0;
        
    }
};

void escritura (){
    /*
    ofstream salida("datos.txt",ios::out);
    labrynth = new char *[n];
    
    for (int i=0; i<n; i++) {
        *(labrynth +i) = new char[n];
        for (int j=0; j<n; j++){
            cin>>*(*(labrynth+i)+j);
            salida<<*(*(labrynth+i)+j);
        }
    }
    salida.close();
     */
    /*
    ofstream entrada("datos.txt",ios::out);
    
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++){
            cin>>*(*(labrynth+j)+i);
            entrada<<*(*(labrynth+j)+i);
        }
    }
    
    entrada.close();
     */
}

void lectura(char **labrynth, int n){
    
    ifstream entrada("datos.txt",ios::in);
    entrada.seekg(1);
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++){
            entrada>>*(*(labrynth+j)+i);
        }
    }
    
    entrada.close();
    
}

bool lado(char caracter){
    if(caracter == '.')
        return true;
    else
        return false;
}

void btrk (int **sumatoria, int n, int btx, int bty, int suma);

void camino(int **sumatoria, int n, int x, int y, int btx, int bty, int suma, bool skip, char dirAnt, bool rever){
    
    if ((x==0 & y==0) && sumatoria[y][x]==1) {
        cout<<"sumatoria en posicion = "<<sumatoria[y][x]<<endl<<"coordenadas x = "<<x<<" y = "<<y<<endl<<"suma muros = "<<suma<<endl;
        
        cin.ignore();
        if (sumatoria[y+1][x]>0) {
            suma=suma+(4-sumatoria[y][x]);
            camino(sumatoria, n, x, y+1, btx, bty, suma, skip, dirAnt, rever);
            
        }
    }
    
    if (x==n-1 & y==n-1) {
        
        cout<<"sumatoria en posicion = "<<sumatoria[y][x]<<endl<<"coordenadas x = "<<x<<" y = "<<y<<endl<<"suma muros = "<<suma<<endl;
        
        cin.ignore();
        
        cout<<"suma final = "<<suma<<endl;
        
        cin.ignore();
        
        suma = suma * 9;
        
        cout<<"Area total muros = "<<suma<<endl;
        
        exit(0);
    }
    
    
    if (rever) {
        
        cout<<"sumatoria en posicion = "<<sumatoria[y][x]<<endl<<"coordenadas x = "<<x<<" y = "<<y<<endl<<"suma muros = "<<suma<<endl;
        
        cin.ignore();
        if (y>0) {
            if (sumatoria[y-1][x]>0) {
                suma=suma+(4-sumatoria[y][x]);
                camino(sumatoria, n, x, y-1, btx, bty, suma, skip, dirAnt, rever);
            }else{
                if (sumatoria[y][x+1]>0) {
                    suma=suma+(4-sumatoria[y][x]);
                    camino(sumatoria, n, x+1, y, btx, bty, suma, skip, dirAnt, false);
                }
            }
        }else{
            if (sumatoria[y][x+1]>0) {
                suma=suma+(4-sumatoria[y][x]);
                camino(sumatoria, n, x+1, y, btx, bty, suma, skip, dirAnt, false);
            }
        }
    }
    
    if (x<n) {
        
        cout<<"sumatoria en posicion = "<<sumatoria[y][x]<<endl<<"coordenadas x = "<<x<<" y = "<<y<<endl<<"suma muros = "<<suma<<endl;
        
        cin.ignore();
        
        if (sumatoria[y][x]>=3) {
            btx=x;
            bty=y;
            if (y<n-1) {
                if (sumatoria[y+1][x]>0) {
                    dirAnt='r';
                }else{
                    if (sumatoria[y][x+1]>0) {
                        dirAnt='d';
                    }else{
                        if (sumatoria[y][x-1]>0) {
                            dirAnt='u';
                        }
                    }
                }
            }
        }
        
        
        if (sumatoria[y][x]==1) {
            x=btx;
            y=bty;
            
            if (rever) {
                if (sumatoria[y][x+1]>0) {
                    suma=suma+(4-sumatoria[bty][x]);
                    if (y<n-1) {
                        camino(sumatoria, n, x+1, y, btx, bty, suma, true, dirAnt, rever);
                    }
                    camino(sumatoria, n, x+1, y, btx, bty, suma, skip, dirAnt, rever);
                }
            }
            
            if (dirAnt=='r') {
                if (sumatoria[y][x+1]>0) {
                    x+=1;
                    suma=suma+(4-sumatoria[bty][x]);
                    cout<<"sumatoria en posicion = "<<sumatoria[y][x]<<endl<<"coordenadas x = "<<x<<" y = "<<y<<endl<<"suma muros = "<<suma<<endl;
                    cin.ignore();
                    cout<<endl<<"-----------BT-----------"<<endl<<endl;
                    if (bty>0 && bty<n-1) {
                        if (sumatoria[bty-1][x]>0 && sumatoria[bty+1][x]==0) {
                            suma=suma+(4-sumatoria[bty][btx]);
                            suma=suma+(4-sumatoria[bty-1][btx]);
                            btrk(sumatoria, n, x, bty-1, suma);
                            cout<<endl<<endl<<"---------salio---------"<<endl;
                        }
                    }
                    y=0;
                    cout<<endl<<"x = "<<x<<endl<<"y = "<<y<<endl<<"suma = "<<suma<<endl;
                    
                    cin.ignore();
                    
                    //btrk(sumatoria, n, x+1, y, x, y,suma);
                    
                }
            }
            
            
            
            
        }
        
        
        if (sumatoria[y][x]>=2) {
            if (y==n-1) {
                if (sumatoria[y][x+1]>0) {
                    suma=suma+(4-sumatoria[y][x]);
                    camino(sumatoria, n, x+1, y, btx, bty, suma, skip, dirAnt, rever);
                }else if(x>0){
                    if (skip) {
                        if (sumatoria[y][x-1]>0) {
                            skip=false;
                            suma=suma+(4-sumatoria[y][x]);
                            camino(sumatoria, n, x-1, y, btx, bty, suma, skip, dirAnt, rever);
                        }else{
                            if (sumatoria[y+1][x]>0) {
                                suma=suma+(4-sumatoria[y][x]);
                                camino(sumatoria, n, x, y+1, btx, bty, suma, skip, dirAnt, rever);
                            }
                        }
                    }else{
                        if (sumatoria[y][x-1]>0) {
                            suma=suma+(4-sumatoria[y][x]);
                            camino(sumatoria, n, x-1, y, btx, bty, suma, skip, dirAnt, rever);
                        }
                    }
                }else{
                    if (sumatoria[y][x+1]>0) {
                        suma=suma+(4-sumatoria[y][x]);
                        if (y<n-1) {
                            skip=true;
                        }
                        camino(sumatoria, n, x+1, y, btx, bty, suma, skip, dirAnt, rever);
                    }
                }
            }else{
                if (sumatoria[y+1][x]>0) {
                    suma=suma+(4-sumatoria[y][x]);
                    camino(sumatoria, n, x, y+1, btx, bty, suma, skip, dirAnt, rever);
                }else if (skip){
                    if (sumatoria[y+1][x]==0) {
                        if (sumatoria[y-1][x]) {
                            suma=suma+(4-sumatoria[y][x]);
                            camino(sumatoria, n, x, y-1, btx, bty, suma, skip, dirAnt, true);
                        }
                    }
                    if (sumatoria[y][x-1]>0) {
                        skip=false;
                        suma=suma+(4-sumatoria[y][x]);
                        camino(sumatoria, n, x-1, y, btx, bty, suma, skip, dirAnt, rever);
                    }
                    
                }else{
                    if (sumatoria[y][x+1]>0) {
                        suma=suma+(4-sumatoria[y][x]);
                        if (y<n-1) {
                            skip=true;
                        }
                        camino(sumatoria, n, x+1, y, btx, bty, suma, skip, dirAnt, rever);
                    }
                }
                
                if (sumatoria[y][x+1]>0) {
                    suma=suma+(4-sumatoria[y][x]);
                    if (y<n-1) {
                        skip=true;
                    }
                    camino(sumatoria, n, x+1, y, btx, bty, suma, skip, dirAnt, rever);
                }
            }
        }
    }
    
    cout<<"Area muros = "<<suma<<endl;
    
    
}

void calcValor (Cubiculo **cubiculos, char **labrynth, int **sumatoria,int n){
    int i=0, j=0;
    
    do {
        do {
            if(i==0){
                if (lado(*(*(labrynth+j)+i+1))) {
                    cubiculos[j][i].l2=1;
                }
            }
            
            if (i>0) {
                if (lado(*(*(labrynth+j)+i-1))) {
                    cubiculos[j][i].l4=1;
                }
                if (lado(*(*(labrynth+j)+i+1))) {
                    cubiculos[j][i].l2=1;
                }
            }
            
            if (i==n-1) {
                if (lado(*(*(labrynth+j)+i-1))) {
                    cubiculos[j][i].l4=1;
                }
            }
            
            if (j==0) {
                if (lado(*(*(labrynth+j+1)+i))) {
                    cubiculos[j][i].l1=1;
                }
            }
            
            if (j>0) {
                if (lado(*(*(labrynth+j-1)+i))) {
                    cubiculos[j][i].l3=1;
                }
                if (lado(*(*(labrynth+j+1)+i))) {
                    cubiculos[j][i].l1=1;
                }
            }
            
            if (j==n-1) {
                if (lado(*(*(labrynth+j-1)+i))) {
                    cubiculos[j][i].l3=1;
                }
            }
            
            j++;
        } while (j<n);
        j=0;
        
        i++;
    } while (i<n);
    
    cout<<endl<<"-----------------"<<endl<<endl;
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            
            if (labrynth[j][i]=='#') {
                cubiculos[j][i].l1=0;
                cubiculos[j][i].l2=0;
                cubiculos[j][i].l3=0;
                cubiculos[j][i].l4=0;
            }
            
            sumatoria[j][i]=cubiculos[j][i].l1+cubiculos[j][i].l2+cubiculos[j][i].l3+cubiculos[j][i].l4;
        }
    }
    camino(sumatoria, n ,0, 0, n, n, 0, false, ' ', false);
}



int main(int argc, const char * argv[]) {
    
    char **labrynth;
    int **values;
    int n=0;
    Cubiculo **cubiculos;
    int **sumatoria;
    
    fstream entrada("datos.txt",ios::in);
    
    entrada>>n;
    
    entrada.close();
    
    labrynth = new char *[n];
    values = new int *[n];
    cubiculos = new Cubiculo *[n];
    sumatoria = new int *[n];
    
    for (int i=0; i<n; i++) {
        *(labrynth +i) = new char[n];
        *(values +i) = new int[n];
        *(cubiculos+i) = new Cubiculo[n];
        *(sumatoria+i) = new int [n];
    }
    
    lectura(labrynth, n);
    
    
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++)
            cout<<*(*(labrynth+j)+i)<<"\t";
        cout<<endl;
    }
    
    cout<<endl;
    
    calcValor(cubiculos, labrynth, sumatoria, n);
    
    return 0;
}


void btrk (int **sumatoria, int n, int btx, int bty, int suma){
    cout<<"sumatoria en posicion = "<<sumatoria[bty][btx]<<endl<<"coordenadas x = "<<btx<<" y = "<<bty<<endl<<"suma muros = "<<suma<<endl;
    cin.ignore();
    
    if(bty>0){
        if(sumatoria[bty-1][btx]>0){
            suma=suma+(4-sumatoria[bty][btx]);
            btrk(sumatoria, n, btx, bty-1, suma);
        }
    }
    
    if (bty==0) {
        if (sumatoria[bty][btx+1]>0) {
            suma=suma+(4-sumatoria[bty][btx]);
            cout<<"suma = "<<suma<<endl;
            cin.ignore();
            camino(sumatoria, n, btx+1, 0, 0, 0, suma, false, ' ', false);
            
        }
    }
    
    cout<<"ultima suma: "<<suma<<endl;
}
