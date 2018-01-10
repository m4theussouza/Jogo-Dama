#ifndef fundama







//aloca memoria para criar a tabela
char **incializa(){
	char **table;
	
	int i,j;
	char k=' ';

	table = (char **)calloc(10,sizeof(char *));

	for(i=0;i<10;i++)
	
		table[i]= (char *)calloc(10,sizeof(char));


	return table;


}





// organiza a tabela
void organiza(char **table){

	int i,j;
	char X='x', O='o';

		//prenche cada posicao da tabela com um espaco
		for(i=1;i<9;i++)
	
		for(j=1;j<9;j++)
	
			table[i][j] = ' ';

				//faz com que os quadradinhos onde nao se pode jogar fiquem preenchidos

		for(i=1;i<9;i+=2)
		
			for(j=2;j<9;j+=2)
		
				table[i][j] = '/';

		for(i=2;i<9;i+=2)
		
			for(j=1;j<9;j+=2)
		
				table[i][j] = '/';

	//coloca as pecas x nas posicoes iniciais
// coloca as peca X nas posicoes iniciais
		for(i=1;i<4;i++){
		       
		        if(i%2 == 0){
		       
		            j=2;
		       
		         }else{
		       
		            j=1;
		         }
		       
		        while(j<9){
		       
		            table[i][j] = X;
		       
		            j+=2;
		        }
		}        	
		// coloca as pecas o nas posicoes iniciais
		for(i=6;i<9;i++){
		       
		        if(i%2 == 0){
		       
		            j=2;
		       
		         }else{
		       
		            j=1;
		       
		         }
		       
		        while(j<9){
		       
		            table[i][j] = O;
		       
		            j+=2;
		        }
		}


}







void printa_table(char **table){
	
	int i,j;
	
	printf(" 1  2  3  4  5  6  7  8 \n");
	
	for(i=1;i<9;i++){
	
		for(j=1;j<9;j++){
	
			printf("[%c]", table[i][j]);
		}
	
		printf(" %d\n", i);
	}
}





int dama(char **table, int linha_p, int coluna_p, int linha_a, int coluna_a, char jogador){
	
	char x='x', o='o';
	
	int i,j;
	
	if (jogador==x){
				
		for ( i = 1 ; i < 9 ; i++){
	
			if (table[8][i]== x){
	
				printf("A peça table[8][%d] eh DAMA\n", i );
	
				table[linha_p][coluna_p] = 'X';
	
				return 1;
				
			}
			
		}
	
	}	else if (jogador == o){
	
			for(i=1;i<9;i++){
	
				if (table[1][i]== o){
	
					printf("A peca table[1][%d] eh DAMA\n", i );
	
					table[linha_p][coluna_p] = 'O';
	
					return 1;
				}
			}
		}	
 return -9;
}

int damamove(char **table, int linhaatual, int colunaatual, int linhaprox, int colprox, char jogador, int *PP,int *PB){
	
	system ("color 70");
	int i,j, l = 0, direlinha=0 ,direcoluna= 0 , a ,b ;
	int linha_p, coluna_p;
	
	direlinha = (linhaprox - linhaatual);       // faz o calculo da direcao 
	direlinha = direlinha / abs(direlinha);		//ou seja,
	
	direcoluna = colprox - colunaatual;        // 1,1 eh uma direcao -1,1 eh outra direcao e etc
	direcoluna = direcoluna / abs(direcoluna); // subtraindo a minha proxima coordenada pela atual e dividindo o resultado pelo modulo dele obtenho a direçao
	
	i = linhaatual + direlinha;
	j = colunaatual + direcoluna;
	
	if(jogador == 'o'){ // verifica quem e o jogador para q na hora de comer suma com o char correto
			
				if (table[linhaprox][colprox]==' '){ // verifica se onde vou esta livre
					
					for (i , j; linhaprox > linhaatual ? i<linhaprox : i>linhaprox , colprox > colunaatual ?  j<colprox : j>colprox ; linhaprox > linhaatual ? i++ : i-- , colprox >colunaatual ? j++ : j--){
						// esse for anda as diagonais dependendo da direcao, pois cada direcao as condiçoes de contar sao diferentes e fazer esse FOR foi o jeito que achei para dibrar isso
						if (table[i][j]=='x' || table[i][j]=='X'){ // olha quantos O ou X dependo do jogador tem nas diagonais
							
							l++;

						}
					}	

					i = linhaatual + direlinha; // como modifico o i e o j no for acima tenho q traze-lo para o valor original para o novo FOR
					
					j = colunaatual + direcoluna;
	
					for (i, j;  linhaprox > linhaatual ? i<linhaprox : i>linhaprox , colprox > colunaatual ?  j<colprox : j>colprox ; linhaprox > linhaatual ? i++ : i-- , colprox >colunaatual ? j++ : j--){
							// o msm FOR que esta la em cima
							if (l==0 ){ // se l for igual a zero significa que o espaço esta livre e ele pode se locomover

								table[linhaatual][colunaatual]=' ';
								
								table[linhaprox][colprox]= 'O';

								return 1;
							
							} else if (l==1 && (table[linhaprox-direlinha][colprox-direcoluna] == 'x' || table[linhaprox-direlinha][colprox-direcoluna] == 'X')){
							 //se l for igual a um significa que da linha atual ate a proxima foi encontrado um x e se minha linha e colunaproxima -1
							//	nao for igual a x ele nao esta indo uma casa depois esta indo mais
								table[linhaatual][colunaatual]=' ';
								
								table[linhaprox][colprox]= 'O';

								table[linhaprox-direlinha][colprox-direcoluna]= ' ';

								table[linhaatual][colunaatual]=' ';

								if (table[linhaprox+(direlinha * 2)][colprox+(direcoluna * 2)] == ' ' && (table[linhaprox+direlinha][colprox+direcoluna]== 'x' || table[linhaprox+direlinha][colprox+direcoluna]== 'X')){
									// olha a frente do espaço onde estou indo para saber se tem um X se tiver posso comer novmente
									printa_table(table);

									printf("Achou uma peca a frente, digite linha:  ");

									scanf("%d", &linha_p);

									printf("Achou uma peca a frente, digite coluna:  ");
									
									scanf("%d", &coluna_p);

									*PB = *PB - 1;
									
									damamove(table, linhaprox, colprox, linha_p, coluna_p, jogador, *&PP, *&PB); 
									// se achar um x na frente ele chama a funcao novamente e passa as variaveis linhaprox e colprox
									// como a atual e passa as variaveis linha_p e coluna_p como as proximas e como comeu uma peça subtrai do placar
								}

								return 4;
							
							} else if (l>1){ // se for maior q 1 significa q ele esta deixando uma peça para tras e nao pode jogar
							
								printf("Voce esta pulando uma peca, jogada invalida\n");
								
								return -1;
							} else {
								
								return -1;
							}
					}
				
			} else {
			
				return -1;
			}	

	} else if (jogador == 'x'){

		if (table[linhaprox][colprox]==' '){
					
					for (i , j; linhaprox > linhaatual ? i<linhaprox : i>linhaprox , colprox > colunaatual ?  j<colprox : j>colprox ; linhaprox > linhaatual ? i++ : i-- , colprox >colunaatual ? j++ : j--){
						
						if (table[i][j] == 'O' || table[i][j] == 'o'){
							
							l++;

						}
					}	
					
					i = linhaatual + direlinha;
					j = colunaatual + direcoluna;
	
					for(i, j;  linhaprox > linhaatual ? i<linhaprox : i>linhaprox , colprox > colunaatual ?  j<colprox : j>colprox ; linhaprox > linhaatual ? i++ : i-- , colprox >colunaatual ? j++ : j--){
							
							if ( l == 0 ){

								table[linhaatual][colunaatual] = ' ';
								
								table[linhaprox][colprox] = 'X';

								return 1;
							
							}else if (l==1 && (table[linhaprox-direlinha][colprox-direcoluna] == 'o' || table[linhaprox-direlinha][colprox-direcoluna] == 'O')){ 
							//se l for igual a um significa que da linha atual ate a proxima foi encontrado um o
								
								table[linhaatual][colunaatual]=' ';
								
								table[linhaprox][colprox]= 'X';

								table[linhaprox-direlinha][colprox-direcoluna]= ' ';

								table[linhaatual][colunaatual]=' ';
								
								if(table[linhaprox+(direlinha * 2)][colprox+(direcoluna * 2)] == ' ' && (table[linhaprox+direlinha][colprox+direcoluna]== 'o' || table[linhaprox+direlinha][colprox+direcoluna]== 'O')){
									
									printa_table(table);

									printf("Achou uma peca a frente, digite linha:  ");

									scanf("%d", &linha_p);

									printf("Achou uma peca a frente, digite coluna:  ");
									
									scanf("%d", &coluna_p);

									*PP = *PP - 1;

									damamove(table, linhaprox, colprox, linha_p, coluna_p, jogador, *&PP, *&PB);

									
								}

								return 1;
							
							}else if (l>1){
							
								printf("Voce esta pulando uma peca, jogada invalida\n");
								
								return -1;
							} else {
								return -1;
							}
					}
				
			}else {
			
				return -1;
			}
	} 

}




// essa funcao e chamada quando o jogador tenta andar mais do que duas linhas, o programa entende que ele quer fazer uma captura e ver se ela é possivel
// se for possivel ele realiza a jogada
int captura(char **table, int linha_p, int coluna_p, int linha_a, int coluna_a, char jogador){
	
	char X='x', O='o';
	
	if(jogador == O){

		if(linha_a != linha_p+2){

			return -1;

		} 	else if(table[linha_a-1][coluna_a-1]== X ) { // verifica se tem peca X a esquerda da sua posicao atual
		
					if(table[linha_p][coluna_p]== ' '){ // vetifica se a posicao para onde ele quer se deslocar esta vazia
				
						table[linha_p][coluna_p] = jogador; // substitui a posicao vaizia pela peca do jogador O
				
						table[linha_a][coluna_a] = ' '; //dexa a posicao ataual do jogador vazia
				
						table[linha_a-1][coluna_a-1]=' ';// deixa a posicao da peca capturada vazia
						
						return 1;
					
					} else {
					
						return -1;
					}			
		} else if (table[linha_a-1][coluna_a+1]== X ){ // verifica se tem peca X a direita da sua posicao atual
					
							if (table[linha_p][coluna_p]== ' '){ // verifica se a posicao para onde ele quer se deslocar esta vazia
								
								table[linha_p][coluna_p] = O; // substitui a posicao vazia pela peca do jogador O
								
								table[linha_a][coluna_a] = ' '; // deixa a posicao atual do jogador vazia
								
								table[linha_a-1][coluna_a+1]=' '; // deica a posicao da peca capturada vazia
								
								return 1;
							
							} else {
							
								return -1;
							}		
				} else {
					return -1;
				}
		} else {
			//jogador X

			if(linha_a != linha_p-2){

			return -1;

		} 	else if(table[linha_a+1][coluna_a+1]== O ) { // verifica x a esquerda da peça para possibilitar movimento > que uma casa
						
					if(table[linha_p][coluna_p]== ' '){
				
						table[linha_p][coluna_p] = jogador;
				
						table[linha_a][coluna_a] = ' ';
				
						table[linha_a+1][coluna_a+1]=' ';
					
						return 1; 
					
					} else {
					
						return -1;
					}			
			} else if (table[linha_a+1][coluna_a-1]== O){ 
					
					if (table[linha_p][coluna_p]== ' '){

						table[linha_p][coluna_p] = X;
							
						table[linha_a][coluna_a] = ' ';
							
						table[linha_a+1][coluna_a-1]=' ';
						
						return 1;
					
					} else {
					
						return -1;
					}		
			} else {
				return -1;
			}


			return -1;
		}
		return -1;
}

//recebe o endereco da tabela, linha e coluna que deseja jogar <linha_p>, linha e coluna atual <linha_a> e jogador que esta fazendo a jogada
//retorna 1 para jogada bem sussedida
//retorna -1 para jogadas invalidas
// -2 para local ocupado por outra peca
// -3 para a jogada nao foi feita para frente ou ele tentou andar mais de uma linha
//

int verificacasa(char **table, int linha_p, int coluna_p, int linha_a, int coluna_a, char jogador,int *PP, int *PB){
	char X='x', O='o';
	int status, statusdama, i, j;

			
			// condiçoes para casa o jogador escolha a pedra referente a O
			if(jogador == O){
			
				if(table[linha_a][coluna_a] == jogador){ // verifica se o jogador esta tentando mover uma peca que pertence a ele
						
				
					if(table[linha_p][coluna_p] != ' '){ // verifica se o jogador esta tentando se mover para uma posicao vazia
				
						printf("A posicao %d-%d esta ocupada\n", linha_p, coluna_p);
				
						return -2;
						//verifica se a jogada foi feita para frente e apenas uma casa & chama a funcao captura para verificar se o jogador quer capturar alguma peca
					} else if(linha_a != linha_p+1) {
						
						if(linha_a < linha_p){ // verifica de ele esta tentando se mover para frente
						
							return -1;
						
						} else {
					
							status = captura(table, linha_p, coluna_p, linha_a, coluna_a, jogador);
							
							if(status>0){
								
								*PB = *PB - 1;
							}
							
							return status;
						}
						// varifica se o jogador esta realizando uma movimentacao na diagonal
					} else if(coluna_a == coluna_p-1 || coluna_a == coluna_p+1){
				
						table[linha_a][coluna_a] = ' '; // remove a peca do jogador da posicao atual
				
						table[linha_p][coluna_p] = O; // coloca a peca do jogador na posicao solicitada
				
						dama(table,linha_p,coluna_p,linha_a,coluna_a,jogador);
						
						return 1;
					} 
				} else if(table[linha_a][coluna_a]== 'O'){
					
					status = damamove(table, linha_a, coluna_a, linha_p, coluna_p, jogador,  *&PP,  *&PB);
										
					if(status> 0){
						
						*PB = *PB - 1;
					} 

					return status;
				} else {
					return -1;
				} 

			} else if (jogador== X){
				//jogador X
				if(table[linha_a][coluna_a] == jogador){
						
				
					if(table[linha_p][coluna_p] != ' '){
				
						printf("A posicao %d-%d esta ocupada\n", linha_p, coluna_p);
				
						return -2;
						//verifica se a jogada foi feita para frente e apenas uma casa & chama a funcao captura para verificar se o jogador quer capturar alguma peca
					} else if(linha_a != linha_p-1) {

						if(linha_a > linha_p){
						
							return -1;
						
						} else {							
						
							status = captura(table, linha_p, coluna_p, linha_a, coluna_a, jogador);
							
							if(status > 0 ){
								
								*PP = *PP -1;
							}
							
							return status;
						}
						//verifica se o jogador esta realizando uma jogada na diagonal e apenas uma casa
					} else if(coluna_a == coluna_p-1 || coluna_a == coluna_p+1){
				
						table[linha_a][coluna_a] = ' ';

						table[linha_p][coluna_p] = X;
						
						dama(table,linha_p,coluna_p,linha_a,coluna_a,jogador);
						
						return 1;
						//verifica se o jogador este relizando
					} 
				}  else if(table[linha_a][coluna_a]== 'X'){
					
					status = damamove(table, linha_a, coluna_a, linha_p, coluna_p, jogador, *&PP, *&PB);
					
					printf("status = %d\n",status );				
					
					if(status> 0){
						
						*PP = *PP - 1;
					}

					return status;
				
				} else {
					return -1;
				} 
			}
			
			
			return -5;
									
}

int status1(char **table,char jogador, int *PP, int *PB){
	int i, j;
	
	for (i = 1; i < 9; i++)
		for (j = 1; j < 9; j++)
		{
			if((table[i][j]!='O' || table [i][j] != 'o') && *PP == 0){
				printf("X Eh o Vencedor\n");
				return 20;
			}else if((table[i][j]!='X' || table[i][j]!='x') && *PB == 0){
				printf("O Eh o Vencedor\n");
				return 20;
			}
		}
	
}

void game(){

	char **table, jogador;
	table = incializa();
	organiza(table);
	printa_table(table);
	int k,j;
	int PP=12, PB=12, opcao; // quantidade peças pretas PP = 'o' peças brancas PB = 'x'  // opcao do switch
	

	int i=1,
		l_a/*linha da peca a ser movida*/, 
		c_a/*coluna da peca a ser movida*/, 
		l_p/*linha para aonde a peca sera movida*/, 
		c_p/*coluna para onde a peca sera movida*/,
		status/*recebe o status da jogada*/;
	
	//loop do jogo
	do{
		system ("color 300");
		//menu de jogo
		printf("____Comandos MENU:____\n||| 100 para reiniar|||\n||| 200 para encerrar |||\n");
	   
	   printf("PLACAR X = %d || O = %d\n", PB, PP);

	    if(i%2==0){ // verifica de qual jogador tem q jogar
	    
	    	jogador = 'x';
	    
	    	printf("E a vez do jogar: %c\n", jogador );
	    
	    	
	    }	 else {
	    	
	    		jogador = 'o';
	    	
	    		printf("E a vez do jogar: %c\n", jogador );
				
			}
			   
					
					printf("Digite algum comando de MENU ou\nDigite a linha referente a peca:"); 
					scanf("%d", &l_a);
					if(l_a < 100){
							printf("Digite a coluna referente a peca:");
							scanf("%d", &c_a);
							printf("Digite a linha onde deseja jogar:");
							scanf("%d", &l_p);
							printf("Digite a coluna onde deseja jogar:");
							scanf("%d", &c_p);
					}
					

						
				
				
				if(l_a==100){
					
					organiza(table);
					
					printa_table(table);

					continue;
					i=1;
				} else if(l_a==200){
					break;
				} else {
					if(l_p > 8 || c_p > 8 || l_a > 9 || c_a > 8){ // verifica se o jogador esta escolhendo uma posicao valida
						system("clear || cls");
				 	
						printf("As linhas e colunas vao ate 8, Digite um numero menor\n");

						printa_table(table);
			 	
						continue;
					} else {
						status =  verificacasa(table, l_p, c_p, l_a, c_a, jogador, &PP, &PB);
					}
				}
				 	system("clear || cls");
				 	
				 	printa_table(table); // printa a tabela atualizada
				
				 if(status < 0 ){ // verifica o status da jogada
				
				 	printf(" voce nao pode fazer essa jogada %d \n", status);
				
				 } else {
				
				 	i++;
				
				 }

				 

		 status = status1(table, jogador, &PP, &PB);

	}while(PP>0 && PB>0);
	
	do{
		printf("Digite um para jogar novamente.\nDigite dois para encerrar o jogo.\n");
	
		printf("Escolha a opcao desejada: ");
	
		scanf("%d", &opcao);
	
		switch (opcao){
			case 1:
				system("clear || cls");

				game();
			
				break;
		
			case 2:
		
				break;
		
			default:
				
				printf("Opcao Invalida!!!\n");
				
				continue;
		}
	}while(opcao!=2);	

}




						


#endif
