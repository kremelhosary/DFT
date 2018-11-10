#include <iostream>
#include<math.h>
using namespace std;

    struct complex {
        double real;
        double img;
    };

    complex cmpmul(complex a, complex b){
            complex m ;
            m.real=a.real * b.real -1 *(a.img * b.img) ;
            m.img =a.real * b.img + a.img * b.real ;
            return m;
    }

    double mag(complex b){
        double a=b.real *b.real;
        double x=b.img * b.img;
        double m=sqrt(a+x);
        return m;
    }
    double phase(complex b){
           double x=b.real;
           double y=b.img;
           return atan(y/x);
    }

    complex matrix(complex t,int q,int w){
            if(q%2==0 &&q!=0) {
                double tem=t.real;
                t.real=t.real * t.real - t.img * t.img ;
                t.img =2 * tem * t.img;
                return matrix(t,q/2,w);
            }
            else if (q%2==1 && q!=1){
                return cmpmul(t,matrix(t,q-1,w));
            }

            if (q==0){
                t.real=1;
                t.img=0;
                return t;
            }
            else if (q==1){
                return t;
            }
    }


int main()
{
    const double pi = atan(1) * 4;

    int n;
    cout<<"Enter of how many points\n";
    cin>>n;
    cout<<"Enter X(n) values\n";
    int Xn[n];
    for (int i=0;i<n;i++){
        cin>>Xn[i];
    }
    cout<<endl;

    complex w;
        if ((360/n)==90 ||(360/n)==270 ){w.real=0;}
        else{w.real=cos((2*pi)/n);}
        w.img=-1*sin((2*pi)/n);

    complex Wn[n][n];
    for(int j=0;j<n;j++){
        for(int k=0;k<n;k++){
            Wn[j][k]=matrix(w,j*k,k);


        }
    }
    cout<<"=> Wn Matrix : \n";
    for(int j=0;j<n;j++){
        for(int k=0;k<n;k++){
                if(Wn[j][k].img==0){cout<<Wn[j][k].real<<"   ";}
                else if (Wn[j][k].real==0){cout<<Wn[j][k].img<<"j  ";}
                else{
                     cout<<Wn[j][k].real<<"+"<<Wn[j][k].img<<"j ";
                    }
        }
        cout<<"\n";
    }
    cout<<endl;


    complex Xk[n];
    complex sum;

    for (int i=0;i<n;i++){
         sum.real =0;
         sum.img=0;
         for(int j=0;j<n;j++){
            sum.real+=Xn[j]*Wn[i][j].real;
            sum.img+=Xn[j]*Wn[i][j].img;

         }
         Xk[i]=sum;

    }

    cout<<"X(k)= { ";
    for (int i=0;i<n;i++){
        if (i!=n-1) cout<<Xk[i].real<<"+"<<Xk[i].img<<"j"<<" , ";
        else cout<<Xk[i].real<<"+"<<Xk[i].img<<"j"<<"  ";
    }
    cout<<"} \n"<<endl;

    cout<< "the magnitudes of X(k) :\n{";
    for (int i=0;i<n;i++){
        if (i!=n-1)cout<<mag(Xk[i])<<"  ,  ";
        else cout<<mag(Xk[i]);
    }
    cout<<" } \n"<<endl;

    cout<< "the Phase of X(k) :\n{";
    for (int i=0;i<n;i++){
        if (i!=n-1)cout<<phase(Xk[i])*180/pi<<"  ,  ";
        else cout<<phase(Xk[i])*180/pi;
    }
    cout<<" } \n"<<endl;



    return 0;
}
