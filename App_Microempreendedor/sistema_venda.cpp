#include <iostream>
#include <random>
using namespace std;

struct CLIENTE{
    unsigned id; //código do cliente
    char nome[100];
    unsigned telefone;
};
//CLIENTE vetor_cliente[100];//vamos usar ponteiro para não ter limites de clientes
int quant_cliente = 0;

struct PRODUTO{
	unsigned id;//codigo produto
	string descricao; //nome de venda do produto
	double valor;
	unsigned quantidade;
};
//PRODUTO vetor_produto[100];//vamos usar ponteiro para não ter limites de clientes
int quant_produto = 0; //vale lembrar que isso é o tipo do produto

struct VENDA{
	unsigned id_venda; //código da venda
	unsigned id_cliente; //id do cliente
	string data; //data da emissão
	unsigned parcela[5]; //parecela do produto no maximo 5
	int valor_total; 
};
//VENDA vetor_venda[100];//vamos usar ponteiro para não ter limites de clientes

//tools
bool perm_case(int &op, char ficar, char sair, string frase);

//case_0
void menu_principal();

//case_1
void case_1();
void menu_cadastro();
void cadastro_cliente(CLIENTE cliente, int &op);

//case_2
void case_2(VENDA venda, int &op);

//case_3
void case_3();
void menu_relatorio();

int main() {
	bool perm = 1; // variavel para mandar o programa rodando
	int opcao = 0; // variavel para guardar a escolha do usuario
    
	while(perm) {
		switch(opcao) {
			case 0: {
				menu_principal();
				cin >> opcao;
				break;
			}
			case 1:{
				case_1();
				opcao = 0;
			    break;
			}
			case 2:{
			    case_2(venda, opcao);
			    break;
			}
			case 3:{
			    
			    break;
			}
			case 4:{
			    perm = perm_case(opcao, 'n', 's', "Certeza que quer sair ?(s/n)");
			    break;
			}
			default:{
			    cout << "Entrada inválida. \n por favor coloque uma entrada validade de 1 a 4. \n";
				break;
		    }
		}
	}
}

void case_1(int &opcao){
    PRODUTO produto;
    bool perm = 1; // variavel para mandar o programa rodando
    
    while(perm){
	    // cadastrar produto
	cout << "Qual o ID do produto?";
	cin >> produto.id; //fazer um tratamento de entrada aqui, lembrando que o cadigo tem um tamanho fixo

	    	//verifica se já está cadastrado
	/*for(int ind=0; ind < quant_produto + 1; ind++){ //trocar por uma função que busque no arquivo text
	    if(produto.id == vetor_produto[ind].id){
	        cout << "O produto já está cadastrado" << endl;
	        op = 0;
	        return;
	    }
	}*/
		// cadastrar produto
	cout << "Qual a descrição do produto?";
	getline(cin >> ws, produto.descricao);
	cout << "Qual o seu valor ?"<< endl;
	cin >> produto.valor;
	cout << "Qual a quantidade do produto ?"<< endl;
	cin >> produto.quantidade;
	system("cls");
	
	//aqui é para colocar um função que escreva em um text o struct do produto
	
	perm = perm_case(opcao, 's', 'n', "Voce quer adicionar mais um funcionario?");
	
    }
	
}

void case_2(VENDA venda, int &opcao){
    bool perm = 1; // variavel para mandar o programa rodando
	
	while(perm) {

		/*1 - Escrever o nome da cliente e fazer um tratamento da string para ver se já não está cadastrado
  		 1.1- Se não estiver cadastrado, perguntar o telefone e gerar o id
     		 1.2 - se sim, então segue o baile
  		 2 -  Escrever o produto a ser comprado e a quantidade - fazer isso sem limites
    		 3 -  Depois um função para a data da venda (essa função seria bom se fosse referenciada)
		 4 - e escrever as parcelas
    		 5 - emitir como saida o valor_total e o valor de cada parcela
		 6 - depois de confirmada a operação, realizar a escrita no text
   		 6.1 - se for cancelado, pode cancela a operação
		*/
		
		
		
		perm = perm_case(opcao, 's' ,'n' , "Quer comprar mais algum produto ?");
	}
}

/*void case_3(){
	
    bool perm = 1; // variavel para mandar o programa rodando
	int opcao = 0; // variavel para guardar a escolha do usuario

	while(perm) {
		switch(opcao) {
			case 0: {
				menu_relatorio();
				cin >> opcao;
				break;
			}
			case 1:{
				for(int ind=0; ind < 100; ind++){
					
				}
				
			    break;
			}
			case 2:{
			    break;
			}
			case 3:{
			    perm = perm_case(opcao, 'n', 's', "Certeza que quer sair ?(s/n)");
			    break;
			}
			default:{
			    cout << "Entrada inválida. \n por favor coloque uma entrada validade de 1 a 4. \n";
			    opcao = 0; //para retorna ao menu
			    system("cls");
				break;
		    }
		}
	}
}*/




//menus
void menu_principal() { // menu das opcoes
	string array_menu[] = { // as opcoes do menu
	"Cadastrar produto",
        "Venda", //na propria venda realizar o cadastro do cliente
        "Relatórios",
        "Sair"
	};
	//essa parte é só para eu não me preocupar com o tamnanho do array
	cout <<"      Menu Principal" << endl;
	int ind = 1;
	for(string frase  : array_menu){
	    cout << ind << " - " << frase << endl;
	}
}


void menu_relatorio(){ //ainda tenho que pensar nas opções para relatorio, mas já tem bastante trabalho para fazder
	string array_menu[] = { // as opcoes do menu
	"Total das Venda",
        "Total por Cliente",
        "Total por Produto",
        "Sair"
	};
	//essa parte é só para eu não me preocupar com o tamnanho do array
	cout <<"      Menu Principal" << endl;
	int ind = 1;
	for(string frase  : array_menu){
	    cout << ind << " - " << frase << endl;
	}
}

//tools
bool perm_case(int &op, char ficar, char sair, string frase){ // para perguntar a cada opcao se o usuario quer sair
	char resp = ' ';
	while(resp != ficar && resp != sair) {
		cout << frase;
		cin >> resp;
		if(resp == ficar) {
			system("cls");
			return 1; // permanece na operacao
		} else if(resp == sair) {
			system("cls");
			op = 0; // para ir ao menu
			return 0; // para sair da operacao
		} else {
			cout << "Entrada invalida! \n Escreva (s) ou (n)";
			system("pause");
			system("cls");
		}
	}
	return 0;
}


