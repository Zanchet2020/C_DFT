
int main(){
	int foo = 10;
	(^)(int, long long) a = (double (^)(int, long long))foo;
	return 0;
}
