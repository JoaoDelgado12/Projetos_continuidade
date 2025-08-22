#include <iostream>
#include <random> 
#include <string> // para mudar o tipo do indice para string no nome
#include <cstring> // para facilitar copiar matriz
//para ficar melhor a vizulização do loop
#include <chrono>
#include <thread>

using namespace std;

const int TAM_MAP = 15;
char map[TAM_MAP][TAM_MAP];

//função para gerar numero aleatorio inteiro
int num_int_rand(int min, int max) {

    // Inicializar o gerador de números aleatórios
    random_device rd;  // Dispositivo aleatório (fonte de entropia)
    mt19937 gen(rd()); // Motor de geração (Mersenne Twister)

    //  Criar uma distribuição uniforme no intervalo [min, max]
    uniform_int_distribution<int> distrib(min, max);

    //  Gerar o número aleatório
    return distrib(gen);
}

void create_map() {
    for(int i = 0; i < TAM_MAP; i++) {
        for(int j = 0; j < TAM_MAP; j++) {
            map[i][j] = '.';
        }
    }
}

void show_map() {
    for(int i = 0; i < TAM_MAP; i++) {
        for(int j = 0; j < TAM_MAP; j++) {
            cout << map[i][j];
        }
        cout << "\n";
    }
}

class animal {
	protected:
   		bool life = true;
    	int fome;
    	int hood[8][2]; // vizinhaça da coordenada do animal
    	int position[2]; // coordenada do animal
    public:
    	animal(){
    		//para nascimento
    		bool test = true;
    		while(test) {
        	position[0] = num_int_rand(0, TAM_MAP - 1);
        	position[1] = num_int_rand(0, TAM_MAP - 1);
        
        	if(map[position[0]][position[1]] == '.') {
            	test = false;
        		}
			}					
		}
		void up_hood();
		void defealt_walk(char especie);
};

// função para atualizar a vizinhança
void animal::up_hood(){
	if(position[0] == 0){
		if(position[1] == 0){
			int temp_hood[8][2] = {{0, TAM_MAP-1}, {0, 1}, 
			{1, TAM_MAP-1}, {1, 0}, {1, 1}, 
			{TAM_MAP-1, 0}, {TAM_MAP-1, TAM_MAP-1}, {TAM_MAP-1, 1} };
			memcpy(hood, temp_hood, sizeof(hood));
		}else if(position[1] == TAM_MAP - 1){
			int temp_hood[8][2] = {{0, TAM_MAP-2}, {0, 1}, 
			{TAM_MAP-1, TAM_MAP-1}, {TAM_MAP-1, 0}, {TAM_MAP-1, TAM_MAP-2}, 
			{1, TAM_MAP-2}, {1, TAM_MAP-1}, {1, 0} };	
			memcpy(hood, temp_hood, sizeof(hood));
		}else{
			int temp_hood[8][2] = {{position[0], position[1]-1}, {position[0], position[1]+1}, 
			{TAM_MAP-1, position[1]-1}, {TAM_MAP-1, position[1]}, {TAM_MAP-1, position[1]+1}, 
			{position[0]+1, position[1]-1}, {position[0]+1, position[1]}, {position[0]+1, position[1]+1}};
			memcpy(hood, temp_hood, sizeof(hood));
		}
		
	}else if(position[0] == TAM_MAP - 1){
		if(position[1] == 0){
			int temp_hood[8][2] = {{TAM_MAP-1, TAM_MAP-1}, {TAM_MAP-1, 1}, 
			{0, 0}, {0, TAM_MAP-1}, {0, 1}, 
			{TAM_MAP-2, 0}, {TAM_MAP-2, TAM_MAP-1}, {TAM_MAP-2, 1} };
			memcpy(hood, temp_hood, sizeof(hood));
		}else if(position[1] == TAM_MAP - 1){
			int temp_hood[8][2] = {{TAM_MAP-1, TAM_MAP-2}, {TAM_MAP-1, 0}, 
			{TAM_MAP-2, TAM_MAP-1}, {TAM_MAP-2, TAM_MAP-2}, {TAM_MAP-2, 0}, 
			{0, TAM_MAP-1}, {0, 0}, {0, TAM_MAP-2} };
			memcpy(hood, temp_hood, sizeof(hood));
		}else{
			int temp_hood[8][2] = {{position[0], position[1]-1}, {position[0], position[1]+1}, 
			{position[0]-1, position[1]-1}, {position[0]-1, position[1]}, {position[0]-1, position[1]+1}, 
			{0, position[1]-1}, {0, position[1]}, {0, position[1]+1}};
			memcpy(hood, temp_hood, sizeof(hood));
		}		
	}else{
		int temp_hood[8][2] = {{position[0], position[1]-1}, {position[0], position[1]+1}, 
			{position[0]-1, position[1]-1}, {position[0]-1, position[1]}, {position[0]-1, position[1]+1}, 
			{position[0]+1, position[1]-1}, {position[0]+1, position[1]}, {position[0]+1, position[1]+1}};	
		memcpy(hood, temp_hood, sizeof(hood));	
	}	
	
}

// andar padrão -- ele chama a função que atualiza a vizinhança e depois anda
void animal::defealt_walk(char especie){
	int new_indice = num_int_rand(0,7);
		map[position[0]][position[1]] = '.';//a posição que ele estava, agora está vazia
		position[0] = hood[new_indice][0];
		position[1] = hood[new_indice][1];
		map[position[0]][position[1]] = especie;
}

class hunter : public animal {
    public:
    hunter(){
    	fome = 3;
    	map[position[0]][position[1]] = 'H';
    	
	}	
	void walk_hunter();
	
};

void hunter::walk_hunter(){
	up_hood();
	int around_hunter = 0; //para contar quantas presas tem
	int coord_presa[8]; // identifica qual coordenada está as presas
	for(int i=0; i<8; i++){
		if(map[hood[i][0]][hood[i][1]] == 'P'){
			coord_presa[around_hunter] = i;
			around_hunter++;
		} 
	}
	
	if(around_hunter == 0){
		defealt_walk('H');
	}else{
		int new_indice = coord_presa[num_int_rand(0,around_hunter-1)];
		map[position[0]][position[1]] = '.';//a posição que ele estava, agora está vazia
		position[0] = hood[new_indice][0];
		position[1] = hood[new_indice][1];
		map[position[0]][position[1]] = 'H';
	}
}


class presa : public animal {
public:
    presa(){
    fome = 3;
    map[position[0]][position[1]] = 'P';
	}
	void walk_presa();
	
};

void presa::walk_presa(){
	up_hood();
	int around_presa = 0; //para contar quantos espaços livres (.) tem ao redor
	int coord_hunter[8];// identifica as coordenados onde estão os hunters
	for(int i=0; i<8; i++){
		if(map[hood[i][0]][hood[i][1]] == '.'){
			coord_hunter[around_presa] = i;
			around_presa++;
		}
	}
	
	if(around_presa == 8){
		defealt_walk('P');
	}else if(around_presa == 0){
		
	}else{
		int new_indice = coord_hunter[num_int_rand(0,around_presa - 1)];
		map[position[0]][position[1]] = '.';//a posição que ele estava, agora está vazia
		position[0] = hood[new_indice][0];
		position[1] = hood[new_indice][1];
		map[position[0]][position[1]] = 'P';
	}
}


int main() {
    create_map();
    int quant_hunter = 0, quant_presa = 0;
    
    // Criação do vetor de hunters
    cout << "Quantos cacadores? \n";
    cin >> quant_hunter;
    hunter* hunters = new hunter[quant_hunter];
    
    // Criação do vetor de presas
    cout << "Quantas presas? \n";
    cin >> quant_presa;
    presa* presas = new presa[quant_presa];
    
    for(int i=0; i<1000; i++){
    	show_map();
    	
		for(int j=0; j<quant_presa; j++){
    		presas[j].walk_presa();
		}
		for(int j=0; j<quant_hunter; j++){
    		hunters[j].walk_hunter();
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100)); // espera 0.1 segundos
    	system("cls");
    }
    
    
    // Liberação de memória ao fim do codigo
    delete[] hunters;
    delete[] presas;
    
    return 0;
}
