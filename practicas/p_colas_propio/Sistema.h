
void LimpiaBuffer(){
	int ch; 
	while( (ch = fgetc(stdin)) != EOF && ch != '\n' ){} 
} 

void LimpiaPantalla(){
	system("clear");
}

void PausaPrograma(){
	getchar();
}