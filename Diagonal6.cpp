#include <iostream>
#include <string>

using namespace std;

struct Ficha
{
	int jogador;
	char cor;
	int torre;
};

//FILA
class Queue
{
	Ficha ficha[13];
	int n;
	char head, tail, it;
	public:
	Queue();
	void Push (int jogador, char cor, int torre);
	Ficha Front();
	Ficha Frontit();
	void itplus();
	void Itback();
	bool Empty();
	void pop();
	void viewQueue();
	~Queue();
};
Queue::Queue()
{
	n = 13 + 1;
	head = tail = it = 0;
}
void Queue :: Push(int jogador, char cor, int torre)
{
	ficha[tail]= {jogador, cor, torre};
	tail=(tail+1)%n;
}

void Queue :: itplus()
{
	it = (it + 1)%n;
}
Ficha Queue:: Frontit()
{
	return ficha [it];
}
Ficha Queue:: Front()
{
	return ficha [head];
	
}
void Queue::Itback()
{
	it = head;
}
void Queue::pop()
{
    head = (head + 1) % n;
}
bool Queue:: Empty()
{
    return head==tail;
}
void Queue::viewQueue()
{
	int ite = head;
	while(ite != tail)
	{
		Ficha f = ficha[ite];
		cout<<f.jogador<<f.cor<<f.torre;
		ite = (ite + 1) % n;
	}
}

Queue::~Queue() {}

//PILHA
class Stack
{
	private:
	char cores[6][6];
	int top[6];

	public:
	Stack();
	void Push(char cor, int torre);
	void Pop(int coluna);
	void Top();
    bool isfull();
	void PrintStack();
	void Result();
	~Stack();
};
Stack::Stack()// inicializa a matriz com espaços vazios
{
	for(int i = 0; i < 6;i++)
	{
		top[i] = 0;
		for (int j = 0; j < 6; j++)
		{
            cores[j][i] = '.'; 
        }
	}
}
/* O top indica a linha inserida e a torre a coluna*/ 
void Stack::Push(char cor, int torre) {
    int coluna = (torre - 1); //ajusta pra 0
    if (cor == 'P')
	{
        Pop(coluna);
    }
	else 
	{
        //procura a próxima coluna com espaço
        int tentativas = 0;
        while (top[coluna] >= 6 && tentativas < 6)
		{
            coluna = (coluna + 1) % 6;
            tentativas++;
        }

        //se uma coluna disponível for encontrada, insere a ficha
        if (tentativas < 6) 
		{
            cores[top[coluna]][coluna] = cor;
            top[coluna]++;
        }
    }
}
void Stack::Pop(int torre) 
{
    if (top[torre] > 0) // Verifica se a pilha não está vazia
	{  
       top[torre]--;

    }
} 
void Stack::Top()
{
    for(int i =0; i < 6; i++)
        {
            cout << cores[top[i]][i] << " ";
        }
}
bool Stack::isfull()
{
	for(int i = 0; i < 6; i++)
	{
		if(top[i] < 6)
		{
			return false;
		}
	}
	return true;
}
void Stack::PrintStack() 
{
	for (int i = 5; i >= 0; i--) 
	{
		for(int j =0; j < 6; j++)
		{
			 cout << cores[i][j];
		}
		cout<<endl;
	}
}
void Stack::Result()//faz a contagem da diagonal principal
{
	int countA = 0, countV = 0, countR = 0, countB = 0;

    for (int i = 0; i < 6; i++)
	{
        if (cores[i][5-i] == 'A')
		{
            countA++;
		} 
        if (cores[i][5-i] == 'V')
		{
		    countV++;
		} 
        if (cores[i][5-i] == 'R')
		{
            countR++;
		} 
        if (cores[i][5-i] == 'B')
		{
            countB++; 
		} 
	}
    
	int contagem[4] = {countA, countV, countR, countB};
	char coresvencedoras[4] ={'A','V','R','B'};

	//para ordenar as maiores pontuaçoes
	for(int i = 0; i < 3; i++)
	{
		for(int j= i+1; j < 4; j++)
		{
			if(contagem[i] < contagem[j])
			{
				swap(contagem[i],contagem[j]);
			
			    swap(coresvencedoras[i],coresvencedoras[j]);
			}
		}
	}
	 int maxganhos = contagem[0];  // O maior número de fichas na diagonal
    int vencedores = 0;

    cout << "Vencedores: "<<endl;
    for (int i = 0; i < 4 && vencedores < 3; i++)
	{
        if (contagem[i] == maxganhos)
		{
            cout << coresvencedoras[i] << " ";
            vencedores++;
        }
    }
    cout << endl;
}
Stack::~Stack(){}

int main()
{
	Queue jogadores[4], transfere;//pra cada jogador uma fila
	Stack tabuleiro;
	string fichas;
	int ordem[4];
	int jogador, torre;
	char cor;
	getline(cin,fichas);

	for(size_t i= 0; i < fichas.length(); i+= 4)//divide os valores da ficha pulando espaços
	{
		jogador = fichas[i] - '0';//converte para inteiro
		cor = fichas[i+1];
		torre = fichas[i+2] - '0';//converte para inteiro

		jogadores[jogador-1].Push(jogador, cor, torre);
	}
	
	transfere.Itback();
   char prioridadeCores[] = {'A','V','R','B'};//prioridade/ordem das cores
   int p = 0;
while (p < 4)
{
    for (int k = 0; k < 4; k++) 
        {
			if (jogadores[k].Frontit().cor == prioridadeCores[p])// definindo a sequencia do jogadores que joga
            {
				ordem[p] = jogadores[k].Frontit().jogador;//puxa a cor da ficha do jogador onde marca It 
				p++;
			}
			else
			{
				jogadores[k].itplus();//quando a cor for 'P' move +1
			}
		}
	}
	int atual = 0;
    while (!tabuleiro.isfull())
	{
		Ficha transfere = jogadores[ordem[atual]-1].Front();
        tabuleiro.Push(transfere.cor, transfere.torre);
		tabuleiro.PrintStack();
		cout<< "--------------------------"<<endl;
        jogadores[ordem[atual]-1].pop();
        atual = (atual + 1) % 4;
	}

	/*Mostrar os ganhadores*/
    tabuleiro.Result();

	/*jogadores, se restou alguma ficha, senao mostrar "Vazia" */
	for(int i=0; i < 4 ; i++)
	{
		cout<<"Mao do jogador "<< i+1 <<": ";
		if (jogadores[i].Empty())
		{
			cout << "Vazia";
		}
		else
		{
			jogadores[i].viewQueue();
		}
		cout<<endl;
	}
    cout<<"Tabuleiro final:"<<endl;
    tabuleiro.PrintStack();

	return 0;
}

