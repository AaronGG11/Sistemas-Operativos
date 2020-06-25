
void limpiaBuffer(){
	int ch; 
	while( (ch = fgetc(stdin)) != EOF && ch != '\n' ){} 
} 

void limpiaPantalla(){
	system("clear");
}

void pausaPrograma(){
	getchar();
}

