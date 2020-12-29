/*int x,y,z; float a;

void foo();

int var(int a, int b){
	return a+b;
}

void foo(){
	x=2;
	y=x-5;
}*/

int main(){
    int a,b,c[3];
    a=1*(2+3)%3;
    b= 1<5;
    c[0]=2;
    if(a && b)
        c[0]++;
    else
        c[1]=c[0];
    println(a);
    println(b);
}
