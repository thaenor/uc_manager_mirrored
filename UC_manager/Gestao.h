#ifndef Gestao_
#define Gestao_

#include <fstream>
#include "UC.h"
//#include <list>
using namespace std;

class Gestao
{
private:

	Pessoa * user;
	UC uc;
	void destroy();

public:
	//Construtor e destrutor
	Gestao();
	Gestao(Pessoa * user, UC uc);
	Gestao(const Gestao &g);
	~Gestao();

	//sets/gets
	void setUser(Pessoa * user);
	Pessoa * getUser();
	//metodo ordenar
	void ListarTeste(vector<Aluno> al);
	void ListarMensagem(vector<Mensagem> ms);

	//ligacao
	BDados* ligar();


	//leitura Teste
	vector<Aluno> LerTeste(string fich);
	double calcAlineas(vector<double> notas, vector<double> cota);

	//leitura de docentes
	vector<Pessoa*> lerDocentes(string fich);

	void printPessoa(vector<Pessoa*> vec);

	//leitura Alunos
	vector<Pessoa*> LerAlunos(string fich);

	//criar aluno
	void criarAluno();

	//Criar docente
	void criarDocente();



};

//construtor e destrutor
Gestao::Gestao()
{
}

Gestao::Gestao(Pessoa * _user, UC _uc)
{	
	user = _user;
	uc = _uc;
}

Gestao::Gestao(const Gestao &g){

}
Gestao::~Gestao(){}

void Gestao::ListarTeste(vector<Aluno> t)
{
	vector<Aluno>::iterator it;

	for (it = t.begin(); it != t.end(); it++) {

		cout << "Numero: " << it->getNumero() <<" Nota: " << (it->getNotas())[0] << "\n";

	}
}

void Gestao::ListarMensagem(vector<Mensagem> ms)
{
	vector<Mensagem>::iterator it;
	int c = 1;
	for (it = ms.begin(); it != ms.end(); it++) {
		cout << "-"<<c<<"-	" ;
		it->listar() ;
		c++;

	}
}

void Gestao :: setUser(Pessoa * _user)
{
	this->user = user;
}

Pessoa * Gestao :: getUser()
{
	return this->user;
}



vector<Aluno> Gestao::LerTeste(string fich)
{
	int inic = 0;
	string linha;
	ifstream fx;

	//dados importados
	vector<double> cotacoes;
	list<double> notas;
	vector<int> numeros;
	vector<Aluno> alunos;
	int n_al;
	int num;


	fx.open(fich);
	if (!fx)
	{
		cout << "Ficheiro de Teste nao existe !" << endl;

	}

	//cotacoes por alinea
	getline(fx, linha, '\n');

	if (linha.size() > 0)
	{
		int	pos = linha.find(';', inic);
		string numero_alineas(linha.substr(inic, pos - inic));
		n_al = stof(numero_alineas);

		for (int i = 0; i < n_al; i++)
		{
			pos++;
			inic = pos;
			pos = linha.find(';', inic);
			string al(linha.substr(inic, pos - inic));
			cotacoes.push_back(stof(al));
		}

	}

	//numero e notas aluno
	while (!fx.eof())
	{
		getline(fx, linha, '\n');
		inic = 0;
		if (linha.size() > 0)
		{
			int	pos = linha.find(';', inic);
			string numero(linha.substr(inic, pos - inic));
			num = stoi(numero);
			numeros.push_back(num);
			for (int i = 0; i < n_al; i++)
			{
				pos++;
				inic = pos;
				pos = linha.find(';', inic);
				string nota(linha.substr(inic, pos - inic));
				double n = std::stod(nota);
				notas.push_back(n);
			}

		}
	}

	for (vector<int> ::iterator it = numeros.begin(); it != numeros.end(); it++)
	{
		vector<double> n;

		for (int i = 0; i < n_al; i++)
		{
			n.push_back(notas.front());
			notas.pop_front();
		}
		vector<double> nota;
		nota.push_back(calcAlineas(n, cotacoes));

		alunos.push_back(Aluno(*it, nota));
	}
	ListarTeste(alunos);
	return alunos;
}

double Gestao::calcAlineas(vector<double> notas, vector<double> cota)
{
	double nota=0; double a, b; double aux;
	vector<double> ::iterator itn = notas.begin();
	vector<double> ::iterator itc = cota.begin();
	for (int i = 0; i < notas.size(); i++)
	{
		a = *(itn + i);
		b = *(itc + i);
		aux = a*b;
		nota += aux;
	}
	return nota;
}

vector<Pessoa*> Gestao::lerDocentes(string fich)
{
	int inic = 0;
	string linha;
	ifstream fx;

	fx.open(fich);
	if (!fx)
	{
		cout << "Ficheiro de Docentes nao existe !" << endl;

	}
	
	vector <Pessoa*> users;
	while (!fx.eof())
	{
		inic = 0;
		getline(fx, linha, '\n');
		if (linha.size() > 0)
		{
			int	pos = linha.find(';', inic);
			string sigla(linha.substr(inic, pos - inic));
			pos++;
			inic = pos;
			string nome(linha.substr(inic, linha.size()));
			Utilizador * p = new Utilizador(nome, sigla, 'D');
			users.push_back(p);
			

		}
	}
	printPessoa(users);
	return users;
}

void Gestao::printPessoa(vector<Pessoa*> t)
{
	vector<Pessoa*>::iterator it;
	if (strcmp(&(typeid(**it).name())[0], &("class Utilizador")[0]) == 0){
		for (it = t.begin(); it != t.end(); it++) {

			cout << "Sigla: " << (**it).getCod_utilizador() << " Nome: " << (**it).getNome() << "\n";
		}
	}
	if (strcmp(&(typeid(**it).name())[0], &("class Aluno")[0]) == 0)
	{
		for (it = t.begin(); it != t.end(); it++) {

			cout << "Numero: " << (**it).getNumero() << " Nome: " << (**it).getNome() << "\n";
		}
	}
}

vector<Pessoa*> Gestao::LerAlunos(string fich)
{
	int inic = 0;
	string linha;
	ifstream fx;

	fx.open(fich);
	if (!fx)
	{
		cout << "Ficheiro de Alunos nao existe !" << endl;

	}

	vector <Pessoa*> users;
	while (!fx.eof())
	{
		inic = 0;
		getline(fx, linha, '\n');
		if (linha.size() > 0)
		{
			int	pos = linha.find(';', inic);
			string numero(linha.substr(inic, pos - inic));
			int num = stoi(numero);
			pos++;
			inic = pos;
			string nome(linha.substr(inic, linha.size()));
			Aluno * p = new Aluno(nome, num);
			users.push_back(p);


		}
	}
	printPessoa(users);
	return users;
}

void Gestao :: criarAluno()
{
	
	BDados *ligacao = ligar();

	string  nome;int numero;
	vector<double> notas;
	system("cls");
	cout << "introduza o nome : ";
	cin.ignore();
	getline(std::cin,nome);
	cout << "\n";
	cout << "\nintroduza o numero (0 - para gerar automaticamente): ";
	cin >> numero;

	if (!ligacao->jaExisteAluno(numero))
	{
		Aluno a(nome,numero,notas);
		ligacao->regAluno(&a);
	}
	else
	{
		cout << "O numero de aluno fornecido ja existe!!!";
		criarAluno();
	}
	delete ligacao;

}

void Gestao :: criarDocente()
{
	BDados *ligacao = ligar();

	string  nome;string sigla;
	vector<double> notas;
	system("cls");
	cout << "introduza o nome : ";
	cin.ignore();
	getline(cin,nome);
	cout << "\nintroduza a sigla : ";
	getline(cin,sigla);

	if (!ligacao->jaExisteDocente(sigla))
	{
		Utilizador u(nome,sigla,'D');
		ligacao->regDocente(&u);
	}
	else
	{
		cout << "O numero de aluno fornecido ja existe!!!";
		criarDocente();
	}
	delete ligacao;

}



BDados* Gestao :: ligar()
{
	string utilizador = "B6_5";
	string palavra = "xico";
	string bd = "193.136.62.27:1521/pdborcl";
	BDados *ligacao = new BDados(utilizador, palavra, bd);
	return ligacao;
}
#endif
