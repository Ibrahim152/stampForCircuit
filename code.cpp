#include <iostream>
using namespace std;

class G_res{
private:
    float value;
public:
    G_res(){};
    G_res(float x) {
        if(x==0){set_value(x);}
        else{value = 1 / x; }
        };
    float get_value() { return value; };
    void set_value(float x) { value=x; };
    G_res operator+(G_res obj) {
        G_res temp;
        temp.set_value(value + obj.value);
        return temp;
        };
};
class VOLT{
private:
    float value;
    float g;
    float i;

public:
    VOLT(){};
    VOLT(float x,float y) {
        value = x;
        g = y;
        i = value * g;
        };
    float get_value() { return value; };
    void set_value(float x) {value=x;};
    float get_i() { return i; };
};
class AMP{
private:
    float value;
public:
    AMP(){};
    AMP(float x) { value = x; };
    float get_value() { return value; };
};

void take_iput_Res(float **matrix,int row,int col){
    float inp;
    G_res sum(0) ;
    int placeholder;
    G_res m;
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            if (i == j){
                cout << "Res between Node " << i + 1 << " and GND  = ";
                placeholder = i;
                cin >> inp;
                m = G_res(inp);
                matrix[i][col] = m.get_value();
            }
            else{
                cout << "Res between Node " << i + 1 << " and Node " << j + 1 << " = ";
                cin >> inp;
                m = G_res(inp);
                matrix[i][j] = -m.get_value();
            }
            sum =sum+ m;
        };
        matrix[placeholder][placeholder] = sum.get_value();
        sum.set_value(0);
        };
};
void take_iput_E(float **matrix,int row,int col,float **matrix2){
        float inp1,inp2;
        for (int i = 0; i < row; i++){
        matrix[i][0] = 0;
        for (int j = 0; j < col; j++){
            if (i == j){
                cout << "E Entering Node " << i + 1 << " from GND  = ";
                cin >> inp1;
                cout << "I Entering Node " << i + 1 << " from GND  = ";
                cin >> inp2;
                matrix[i][0] += VOLT(inp1, matrix2[i][col]).get_i()+AMP(inp2).get_value();
            }
            else{
                cout << "E Entering Node " << i + 1 << " from Node " << j + 1 << " = ";
                cin >> inp1;
                cout << "I Entering Node " << i + 1 << " from Node " << j + 1 << " = ";
                cin >> inp2;
                matrix[i][0] += VOLT(inp1, -matrix2[i][j]).get_i()+AMP(inp2).get_value();
            }
        };
        };
};

float **_matrix(int row,int col){
    float **matrix = new float*[row];
    for (int i = 0; i < row;i++){
        matrix[i] = new float[col];
    };
    return matrix;
};
void show_matrix(float **matrix,int row,int col){
    for (int i = 0; i < row; i++){
        for (int j = 0;j < col; j++){
            cout << matrix[i][j] << "\t";
        };
        cout << "\n";
    };
};

int main(){
    int nodes;
    cout << "Enter the number of Nodes = ";cin >> nodes;
    float** G_matrex=_matrix(nodes, nodes+1);
    float** RHS_matrex=_matrix(nodes, nodes);
    take_iput_Res(G_matrex,nodes,nodes);
    take_iput_E(RHS_matrex,nodes,nodes,G_matrex);
    cout << "RES Matrix: \n ";
    show_matrix(G_matrex, nodes, nodes);
    cout << "RHS Matrix: \n";
    show_matrix(RHS_matrex, nodes, 1);
    return 0;
}