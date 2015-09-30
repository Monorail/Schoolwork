int main(void){
        printf("%d\n",mult(4,5));
        return 0;
}

int mult(int a, int b){
	if (a==0 || b==0)
		return 0;
	return a+ mult(a,b-1);

}
