#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#define N 14                //Число колонок
#define AllRows 22			//Число строк общее
#define HEAD 12             //Число строк заголовков
using namespace std;

struct ArrValues{
    string DateTime;
    string Value;
};
struct tags{
    string Name;
    string Mesh;
    ArrValues Values[AllRows-HEAD];
} Tag[8];
int line(FILE* _fp,char _x[200],string _y[N]){
    //fgets(_x, 150,_fp);
	//cout << _x << endl;
    string s(_x);
    _y[1]=s.substr(0,s.find(','));
    _y[0]=s.substr(s.find(',')+1,s.npos);
    for(int i=2;i<N;i++){
        _y[i]=_y[0].substr(0,_y[0].find(','));
        _y[0]=_y[0].substr(_y[0].find(',')+1,_y[0].npos);
    }
    return 0;
}
/*int getValues(FILE* fp,tags Tag[8]){
    char x[200];
    string y[AllRows-HEAD][N];
    for(long i =0;i<(AllRows-HEAD);i++){
        line(fp,x,y[i]);
        for(int j=1;j<8;j++){
            Tag[j].Values[i].Value=y[i][j+5];
            Tag[j].Values[i].DateTime =y[i][3];
            Tag[j].Values[i].DateTime +=" ";
            Tag[j].Values[i].DateTime +=y[i][4];
        }
    }
    return 0;
}*/
int main()
{
    system("chcp 1251 > nul");
    //tags Tag1[8];
    char x[200];
	string  h[HEAD][N],
			y[AllRows][N];
    FILE* fp = fopen("TG0102.csv","r");
    if (fp==NULL) perror("Ошибка открытия файла");
    if (fp!=NULL){
		//fgets(x, 150, fp);
		//cout << x << endl;
		//line(fp, x, h[1]);
        for(int i =0;i<HEAD;i++){           //считывание заголовков
            line(fp,x,h[i]);
            if (i==3){
                for(int j=1;j<9;j++){
                    Tag[j].Name=h[i][j+5];
                }
            }
            if (i==8){
                for(int j=1;j<9;j++){
                    Tag[j].Mesh=h[i][j+5];
                }
            }
        }
        for(long i =0;i<(AllRows-HEAD);i++){ //считывание 1ой части
            line(fp,x,y[i]);
            for(int j=1;j<8;j++){
                Tag[j].Values[i].Value=y[i][j+5];
                Tag[j].Values[i].DateTime =y[i][3];
                Tag[j].Values[i].DateTime +=" ";
                Tag[j].Values[i].DateTime +=y[i][4];
            }

        }
        //getValues(fp,Tag);
        //cout<<"Hello"<<endl;
    }
    fclose(fp);
    for(int n=1;n<9;n++){
        cout<<"Tag["<<n<<"]: "<<Tag[n].Name<<endl;
		cout << "TagM[" << n << "]: " << Tag[n].Mesh << endl;
        for(int k=12000;k<12010;k++){
            cout<<"Date: "<<Tag[n].Values[k].DateTime<<" ";
            cout<<"Value: "<<Tag[n].Values[k].Value<<endl;
		}
    }
    return 0;
}
