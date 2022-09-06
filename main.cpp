/*
 Trabalho prático
 Arquivo: "san_francisco_payroll_dataset.csv"

 Nomes: 
        - Igor Abreu Fortunato - 14B

        - Marcos Vinicius Paiva Carvalhar - 14B

        - Pedro Henrique Santana Quintiliano - 14A
*/
 
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <cmath>

using namespace std;

// Folha de pagamento Sao Francisco
struct PayrollSaoFrancisco
{
    int iID; // ID
    char cEmployeeName[50]; // Nome do Funciário
    char cJobTitle[50]; // Cargo
    double fBasePay; // Pagamento Base
    double fOvertimePay; // Pagamento extra
    double fOtherPay; // Outros pagamentos
    double fBenefits; // Beneficios
    double fTotalPay; // Pagamento Total
    double fTotalPay_Benefits; // Pagamento Total 
    int iYear; // Ano      
};

// Função para converter para binário
void fncConverterCSVParaBinario(string _sNomeArquivoEntrada, string _sNomeArquivoSaida)
{
	PayrollSaoFrancisco TRegistro;

    ifstream aArquivoEntrada(_sNomeArquivoEntrada);
    ofstream aArquivoSaida(_sNomeArquivoSaida, ios::binary);

    if (aArquivoEntrada)
    {
        string sNomeCampos;
        string sValorCampo;
        int iTamanho = 0;
        bool bLeuNomeCampo = false;
        // Enquanto não estiver no fim do arquivo
        while(!aArquivoEntrada.eof())
        {
			if (!bLeuNomeCampo)
			{
				// Ler o cabeçalho
				getline(aArquivoEntrada, sNomeCampos);
				bLeuNomeCampo = true;
				//cout << sNomeCampos << endl;
			}
            getline(aArquivoEntrada, sValorCampo, ',');
            // Se o ID da primeira posição não estiver vazio, então o arquivo tem informações.
            if (sValorCampo != "")
            {   
				// Ler e converter as informações da linha para o registro
				//cout << sValorCampo << ","; 
				
				TRegistro.iID = std::stoi(sValorCampo);
				
				getline(aArquivoEntrada, sValorCampo, ','); 
				//cout << sValorCampo << ",";
				iTamanho = sValorCampo.size();
				for (int i = 0; i < iTamanho; i++)
				{
					(TRegistro.cEmployeeName)[i] = (sValorCampo)[i];
				}
				(TRegistro.cEmployeeName)[iTamanho] = '\0';				
				
				getline(aArquivoEntrada, sValorCampo, ','); 
				
				/**if (sValorCampo[0] == '"')
				{
					//cout << sValorCampo << ","; 
					iTamanho = sValorCampo.size();
					for (int i = 0; i < iTamanho; i++)
					{
						(TRegistro.cJobTitle)[i] = (sValorCampo)[i];
					} 
					
					getline(aArquivoEntrada, sValorCampo, '"'); 
					
					int iOutroTamanho = sValorCampo.size();
					
					for (int i = 0; i < iOutroTamanho; i++)
					{
						(TRegistro.cJobTitle)[i] = (sValorCampo)[i];
					} 
					
					getline(aArquivoEntrada, sValorCampo, ',');
					
					(TRegistro.cJobTitle)[(iTamanho + iOutroTamanho)] = '\0';
				} else
				{*/
				//cout << sValorCampo << ","; 
				iTamanho = sValorCampo.size();
				for (int i = 0; i < iTamanho; i++)
				{
					(TRegistro.cJobTitle)[i] = (sValorCampo)[i];
				} 
				
				(TRegistro.cJobTitle)[iTamanho] = '\0';
				//}
				
				getline(aArquivoEntrada, sValorCampo, ',');  
				//cout << sValorCampo << ",";
				TRegistro.fBasePay = std::atof(sValorCampo.c_str());
				
				getline(aArquivoEntrada, sValorCampo, ',');  
				//cout << sValorCampo << ",";
				TRegistro.fOvertimePay = std::atof(sValorCampo.c_str());
				
				getline(aArquivoEntrada, sValorCampo, ',');
				if (sValorCampo == "Not Provided")
					sValorCampo = '0';
				//cout << sValorCampo << ",";  
				TRegistro.fOtherPay = std::atof(sValorCampo.c_str());
				
				getline(aArquivoEntrada, sValorCampo, ',');
				//cout << sValorCampo << ",";    
				TRegistro.fBenefits = std::atof(sValorCampo.c_str());
				
				getline(aArquivoEntrada, sValorCampo, ',');
				//cout << sValorCampo << ",";    
				TRegistro.fTotalPay = std::atof(sValorCampo.c_str());
				
				getline(aArquivoEntrada, sValorCampo, ',');
				//cout << sValorCampo << ",";  
				TRegistro.fTotalPay_Benefits = std::atof(sValorCampo.c_str());
				
				getline(aArquivoEntrada, sValorCampo); 
				//cout << sValorCampo; 
				TRegistro.iYear = std::stoi(sValorCampo);

				//cout << endl;
				// Escrever registro no arquivo
				aArquivoSaida.write((const char *)(&TRegistro), sizeof(PayrollSaoFrancisco)); 
			}
        }
    } else
    {
        cout << "Falha ao executar o arquivo" << endl;
    }

    aArquivoEntrada.close();
    aArquivoSaida.close();
}

// Função para imprimir registros.
void fncImprimirArquivoBinario(string _sNomeArquivoBinario, int _iPosicaoInicial, int _iPosicaoFinal)
{	
	std::cout.precision(2);
	std::cout<<std::fixed;
	ifstream aArquivoBinario;
	aArquivoBinario.open(_sNomeArquivoBinario, ios::binary);
	if (aArquivoBinario)
	{
		// Caso as posições forem = -1, então quer dizer que é para imprimir todos os registros
		if ((_iPosicaoInicial == -1) and (_iPosicaoFinal == -1))
		{
			aArquivoBinario.seekg(0, aArquivoBinario.end);
			int iTamanho = aArquivoBinario.tellg();
			aArquivoBinario.seekg(0, aArquivoBinario.beg);

			int iQtdRegistros = iTamanho / sizeof(PayrollSaoFrancisco);
			
			PayrollSaoFrancisco tmpRegistro;

			for (int i = 0; i < iQtdRegistros; i++) 
			{      
				aArquivoBinario.read(reinterpret_cast<char*>(&tmpRegistro), sizeof(PayrollSaoFrancisco));
				/*cout << "ID: " << tmpRegistro.iID << ", ";
				cout << "Nome do Funcionario: " << tmpRegistro.cEmployeeName << ", ";
				cout << "Cargo: " << tmpRegistro.cJobTitle << ", ";
				cout << "Pagamento Base: " << tmpRegistro.fBasePay << ", "; 
				cout << "Pagamento extra: " << tmpRegistro.fOvertimePay << ", ";
				cout << "Outros pagamentos: " << tmpRegistro.fOtherPay << ", ";
				cout << "Beneficios: " << tmpRegistro.fBenefits << ", ";
				cout << "Pagamento Total: " << tmpRegistro.fTotalPay << ", ";
				cout << "Pagamento Total com Beneficios: " << tmpRegistro.fTotalPay_Benefits << ", ";  
				cout << "Ano: " << tmpRegistro.iYear << endl;*/
				// Deixada a impressão de forma que facilite a comparação de valores
				cout << tmpRegistro.iID << ", ";
				cout << tmpRegistro.cEmployeeName << ", ";
				cout << tmpRegistro.cJobTitle << ", ";
				cout << tmpRegistro.fBasePay << ", "; 
				cout << tmpRegistro.fOvertimePay << ", ";
				cout << tmpRegistro.fOtherPay << ", ";
				cout << tmpRegistro.fBenefits << ", ";
				cout << tmpRegistro.fTotalPay << ", ";
				cout << tmpRegistro.fTotalPay_Benefits << ", ";  
				cout << tmpRegistro.iYear << endl;      
			}
		} else
		{
			// Caso contrário é posicionado na posição final para saber se os registros do intervalo são maiores que o total de registros do arquivo
			// Caso sim, são impressos todos os registros daquele intervalo, caso contrário, são impressos até o final do arquivo.
			
			int iQuantidadeRegistros = _iPosicaoFinal - _iPosicaoInicial + 1;
			
			// Pegar quantidade de registros do arquivo
			aArquivoBinario.seekg((_iPosicaoInicial * sizeof(PayrollSaoFrancisco)), aArquivoBinario.end);
			int iQuantidadeRegArquivo = aArquivoBinario.tellg();
			
			aArquivoBinario.seekg((_iPosicaoInicial * sizeof(PayrollSaoFrancisco)), aArquivoBinario.beg);

			int iNumRegistros = 0;
			
			iNumRegistros = iQuantidadeRegArquivo / sizeof(PayrollSaoFrancisco);		
			
			if (iNumRegistros < iQuantidadeRegistros)
				iQuantidadeRegistros = iNumRegistros;
				
			PayrollSaoFrancisco tmpRegistro;

			for (int i = 0; i < iQuantidadeRegistros; i++) 
			{        
				aArquivoBinario.read(reinterpret_cast<char*>(&tmpRegistro), sizeof(PayrollSaoFrancisco));
				/*cout << "ID: " << tmpRegistro.iID << ", ";
				cout << "Nome do Funcionario: " << tmpRegistro.cEmployeeName << ", ";
				cout << "Cargo: " << tmpRegistro.cJobTitle << ", ";
				cout << "Pagamento Base: " << tmpRegistro.fBasePay << ", "; 
				cout << "Pagamento extra: " << tmpRegistro.fOvertimePay << ", ";
				cout << "Outros pagamentos: " << tmpRegistro.fOtherPay << ", ";
				cout << "Beneficios: " << tmpRegistro.fBenefits << ", ";
				cout << "Pagamento Total: " << tmpRegistro.fTotalPay << ", ";
				cout << "Pagamento Total com Beneficios: " << tmpRegistro.fTotalPay_Benefits << ", ";  
				cout << "Ano: " << tmpRegistro.iYear << endl;*/
				// Deixada a impressão de forma que facilite a comparação de valores
				cout << tmpRegistro.iID << ", ";
				cout << tmpRegistro.cEmployeeName << ", ";
				cout << tmpRegistro.cJobTitle << ", ";
				cout << tmpRegistro.fBasePay << ", "; 
				cout << tmpRegistro.fOvertimePay << ", ";
				cout << tmpRegistro.fOtherPay << ", ";
				cout << tmpRegistro.fBenefits << ", ";
				cout << tmpRegistro.fTotalPay << ", ";
				cout << tmpRegistro.fTotalPay_Benefits << ", ";  
				cout << tmpRegistro.iYear << endl;       
			}
		}
	}
	else
	{
		cout << "Erro na leitura do arquivo!";
	}
	
	aArquivoBinario.close();
}

// Função para alterar registro de uma determinada posição
void fncAlterarRegistro(int _iPosicao, PayrollSaoFrancisco _TMPREGISTRO, string _sNomeArquivo)
{
	fstream aArquivoBinario;
	aArquivoBinario.open(_sNomeArquivo, ios::in | ios ::out);
	
	if (aArquivoBinario)
	{
		// Move para a posição informada pelo usuário e substitui as informações pelas do registro informado anteriormente.
		aArquivoBinario.seekp(((_iPosicao) * sizeof(PayrollSaoFrancisco)), aArquivoBinario.cur);
		aArquivoBinario.write((const char *)(&_TMPREGISTRO), sizeof(PayrollSaoFrancisco)); 
	} else
	{
		cout << "Erro na leitura do arquivo!";
	}
	
	aArquivoBinario.close();
}

// Função para adicionar registro entre posições, baseado na posição que for informada.
void fncAdicionarRegistro(int _iPosicao, PayrollSaoFrancisco _TMPREGISTRO, string _sNomeArquivo)
{
	fstream aArquivoBinario;
	aArquivoBinario.open(_sNomeArquivo, ios::binary | ios::in | ios ::out);
	
	if (aArquivoBinario)
	{
		// Inserir registro vazio no final para já alocar uma posição no arquivo.
		PayrollSaoFrancisco RegistroVazio = {-999, "", "", 0, 0, 0, 0, 0, 0, 0};
		aArquivoBinario.seekp(0, aArquivoBinario.end);
		aArquivoBinario.write((const char *)(&RegistroVazio), sizeof(PayrollSaoFrancisco));
		
		// Peguei o registro anterior da posicao informada
		aArquivoBinario.seekg(((_iPosicao) * sizeof(PayrollSaoFrancisco)));
		PayrollSaoFrancisco NovoRegistro;
		aArquivoBinario.read(reinterpret_cast<char*>(&NovoRegistro), sizeof(PayrollSaoFrancisco));
		// Escrito o novo registro na posicao informada
		aArquivoBinario.seekp(((_iPosicao) * sizeof(PayrollSaoFrancisco)));
		aArquivoBinario.write((const char *)(&_TMPREGISTRO), sizeof(PayrollSaoFrancisco)); 
		
		PayrollSaoFrancisco RegistroAnterior;
		// Incrementar para já começar para a proxima
		int iPosRelativa = _iPosicao+1;
		int iTamanhoMaximo = 0;
		// Posicionar na posicao inicial até o final para pegar a posição máxima do arquivo.
		aArquivoBinario.seekg(0, aArquivoBinario.end);
		iTamanhoMaximo = aArquivoBinario.tellg() / sizeof(PayrollSaoFrancisco);
		// Posicionar na poiscao relativa (na próxima posição) para leitura
		aArquivoBinario.seekg((iPosRelativa) * sizeof(PayrollSaoFrancisco));
		// Armazenando o que estava na posição relativa em memória RAM
		aArquivoBinario.read(reinterpret_cast<char*>(&RegistroAnterior), sizeof(PayrollSaoFrancisco));
		// Movido para posição de escrita na posição relativa.
		aArquivoBinario.seekp((iPosRelativa) * sizeof(PayrollSaoFrancisco));
		while (iPosRelativa < iTamanhoMaximo)
		{
			// Escrever na posição relativa o registro que havia sido lido da posição anterior a posição relativa
			aArquivoBinario.seekp((iPosRelativa) * sizeof(PayrollSaoFrancisco));
			aArquivoBinario.write((const char *)(&NovoRegistro), sizeof(PayrollSaoFrancisco));
			
			// O Novo registro a ser escrito na proxima posição é o que acabou de ser substituido (no arquivo) da posição relativa
			NovoRegistro = RegistroAnterior;
			
			iPosRelativa++;		
			// Ler o próximo registro para que o registro que foi lido anteriormente possa ser colocado nesse lugar agora
			aArquivoBinario.seekg((iPosRelativa) * sizeof(PayrollSaoFrancisco));
			aArquivoBinario.read(reinterpret_cast<char*>(&RegistroAnterior), sizeof(PayrollSaoFrancisco));	
		}
	} else
	{
		cout << "Erro na leitura do arquivo!";
	}
	
	aArquivoBinario.close();
}

// Função para inserir um registro no final do arquivo
void fncInserirNoFinal(PayrollSaoFrancisco _TMPREGISTRO, string _sNomeArquivo)
{
	fstream aArquivoBinario;
	aArquivoBinario.open(_sNomeArquivo, ios::in | ios ::out);
	
	if (aArquivoBinario)
	{
		aArquivoBinario.seekp(0, aArquivoBinario.end);
		aArquivoBinario.write((const char *)(&_TMPREGISTRO), sizeof(PayrollSaoFrancisco)); 
	} else
	{
		cout << "Erro na leitura do arquivo!";
	}
	
	aArquivoBinario.close();
}

// Função para trocar registros de posição
void fncTrocarPosicao(int _iPrimeiraPosicao, int _iSegundaPosicao, string _sNomeArquivo)
{
	PayrollSaoFrancisco PrimeiroRegistro, SegundoRegistro;
	
	fstream aArquivoBinario;
	aArquivoBinario.open(_sNomeArquivo, ios::binary | ios::in | ios ::out);

	if (aArquivoBinario)
	{		
		// Movendo a posição de leitura para a primeira posicao
		aArquivoBinario.seekg((_iPrimeiraPosicao-1) * sizeof(PayrollSaoFrancisco));
		// Lendo o primeiro registro da primeira posicao
		aArquivoBinario.read((char *)(&PrimeiroRegistro), sizeof(PayrollSaoFrancisco));
		
		// Movendo a leitura para a segunda posicao
		aArquivoBinario.seekg((_iSegundaPosicao-1) * sizeof(PayrollSaoFrancisco));
		// Lendo o segundo registro da segunda posicao
		aArquivoBinario.read((char *)(&SegundoRegistro), sizeof(PayrollSaoFrancisco));
			
		// Movendo a posição de leitura para a primeira posição para colocar o segundo registro
		aArquivoBinario.seekp(((_iPrimeiraPosicao-1) * sizeof(PayrollSaoFrancisco)));
		aArquivoBinario.write((const char *)(&SegundoRegistro), sizeof(PayrollSaoFrancisco)); 
		
		// Movendo a posição de leitura para a segunda posição para colocar o primeiro registro
		aArquivoBinario.seekp(((_iSegundaPosicao-1) * sizeof(PayrollSaoFrancisco)));
		aArquivoBinario.write((const char *)(&PrimeiroRegistro), sizeof(PayrollSaoFrancisco)); 
	}
	else
	{
		cout << "Erro na leitura do arquivo!";
	}
	
	aArquivoBinario.close();
}

// Função para ler registro e evitar repetição de código
PayrollSaoFrancisco fncLerRegistro()
{
	PayrollSaoFrancisco tmpRegistro;
	string _sSTR;
	int iTamanho; 
	cout << "Digite as informacoes do Registro: " << endl;
	cout << "ID: "; 
	cin >> tmpRegistro.iID;				
				
	cin.ignore();
	cout << "Nome do Funcionario: "; 
	getline(cin, _sSTR);
	iTamanho = _sSTR.size();
	for (int i = 0; i < iTamanho; i++)
	{
		(tmpRegistro.cEmployeeName)[i] = (_sSTR)[i];
	}
	(tmpRegistro.cEmployeeName)[iTamanho] = '\0';		
	
	cout << "Cargo: ";
	getline(cin, _sSTR);
	iTamanho = _sSTR.size();
	for (int i = 0; i < iTamanho; i++)
	{
		(tmpRegistro.cJobTitle)[i] = (_sSTR)[i];
	} 
	(tmpRegistro.cJobTitle)[iTamanho] = '\0';
	
	cout << "Pagamento Base: ";
	cin >> tmpRegistro.fBasePay; 
	cout << "Pagamento extra: ";
	cin >> tmpRegistro.fOvertimePay;
	cout << "Outros pagamentos: "; 
	cin >> tmpRegistro.fOtherPay;
	cout << "Beneficios: "; 
	cin >> tmpRegistro.fBenefits;
	cout << "Pagamento Total: "; 
	cin >> tmpRegistro.fTotalPay;
	cout << "Pagamento Total com Beneficios: "; 
	cin >> tmpRegistro.fTotalPay_Benefits;  
	cout << "Ano: ";
	cin >> tmpRegistro.iYear;
	cout << endl;
	
	return tmpRegistro;
}

// Retorna 1 caso o primeiro registro informado for menor que o segundo, e o segundo, caso contrário.
int fncComparaRegistro(PayrollSaoFrancisco _TMPREGISTRO1, PayrollSaoFrancisco _TMPREGISTRO2)
{
	// Primeiro compara cJobTitle.
	//cout << _TMPREGISTRO1.cJobTitle << " - " << _TMPREGISTRO2.cJobTitle << endl;
	if (_TMPREGISTRO1.cJobTitle != _TMPREGISTRO2.cJobTitle)
	{
		int iComparacao = strcmp(_TMPREGISTRO1.cJobTitle, _TMPREGISTRO2.cJobTitle);
		if (iComparacao < 0)
		{
			//cout << _TMPREGISTRO1.cJobTitle << endl;
			return 1;
		} else if (iComparacao > 0)
		{
			//cout << _TMPREGISTRO2.cJobTitle << endl;
			return 2;
		} else
		{
			// Caso não for nem maior, nem menor, ou seja, é igual, então compara-se o ID.
			if (_TMPREGISTRO1.iID < _TMPREGISTRO2.iID)
			{
				//cout << _TMPREGISTRO1.cJobTitle << endl;
				return 1;
			} else
			{
				//cout << _TMPREGISTRO2.cJobTitle << endl;
				return 2;
			}
		}
	} else
	{
		if (_TMPREGISTRO1.iID < _TMPREGISTRO2.iID)
		{
			//cout << _TMPREGISTRO1.cJobTitle << endl;
			return 1;
		} else
		{
			//cout << _TMPREGISTRO2.cJobTitle << endl;
			return 2;
		}
	}
}

void merge(PayrollSaoFrancisco *_Vetor, int _iEsquerda, int m, int _iDireita) {
	int i, j, k, nl, nr;
	//size of left and right sub-arrays
	nl = m - _iEsquerda + 1; 
	nr = _iDireita - m;
	PayrollSaoFrancisco larr[nl];
	PayrollSaoFrancisco rarr[nr];
	
	//fill left and right sub-arrays
	for(i = 0; i<nl; i++)
	{
      larr[i] = _Vetor[_iEsquerda + i];
	}
	for (j = 0; j<nr; j++)
	{
		rarr[j] = _Vetor[m + 1 + j];
	}
	
	i = 0; 
	j = 0; 
	k = _iEsquerda;

	//marge temp arrays to real array
	while (i < nl && j<nr) 
	{
		if (fncComparaRegistro(larr[i], rarr[j]) == 1) 
		{
			_Vetor[k] = larr[i];
			i++;
		} else
		{
			_Vetor[k] = rarr[j];
			j++;
		}
		k++;
	}

	while (i < nl) 
	{       //extra element in left array
		_Vetor[k] = larr[i];
		i++; 
		k++;
	}

	while (j < nr) {     //extra element in right array
		_Vetor[k] = rarr[j];
		j++; 
		k++;
	}
}

void mergeSort(PayrollSaoFrancisco *_Vetor, int _iEsquerda, int _iDireita) {
   if(_iEsquerda < _iDireita) {
      int iAux = _iEsquerda + (_iDireita - _iEsquerda) / 2;
      // Sort first and second arrays
      mergeSort(_Vetor, _iEsquerda, iAux);
      mergeSort(_Vetor, iAux + 1, _iDireita);
      merge(_Vetor, _iEsquerda, iAux, _iDireita);
   }
}

PayrollSaoFrancisco *fncAlocarVetor(PayrollSaoFrancisco *_vet, int iTamanhoNovo)
{
	PayrollSaoFrancisco *novoVetor = new PayrollSaoFrancisco[iTamanhoNovo];
	
	//memcpy(novoVetor, _vet, (iTamanhoNovo * sizeof(PayrollSaoFrancisco)));
	for (int i = 0; i < iTamanhoNovo - 1; i++)
	{
		novoVetor[i] = _vet[i];
	}
		
	delete[] _vet;
	return novoVetor;
}

int pcdDividirArquivoCompacto(string _sNomeArquivoPrincipal, string _sNomeSubArquivos)
{
	int iQuantidadeSubArquivos = 0;
	fstream aArquivoBinario;
	aArquivoBinario.open(_sNomeArquivoPrincipal, ios::in | ios ::out | ios::binary);
	if (aArquivoBinario)
	{
		int iTamanhoMaximo = 0;
		int iPosAtual = 0;
		aArquivoBinario.seekg(0, aArquivoBinario.end);
		iTamanhoMaximo = aArquivoBinario.tellg() / sizeof(PayrollSaoFrancisco);
		aArquivoBinario.seekg((iPosAtual) * sizeof(PayrollSaoFrancisco), aArquivoBinario.beg);
		int iQuantidadeRegistros = 3500;
		while (iPosAtual < iTamanhoMaximo)
		{
			
			if ((iTamanhoMaximo - iPosAtual) < 3500)
				iQuantidadeRegistros = (iTamanhoMaximo - iPosAtual);
			
			PayrollSaoFrancisco *vet = new PayrollSaoFrancisco[iQuantidadeRegistros];
			aArquivoBinario.read(reinterpret_cast<char*>(vet), sizeof(PayrollSaoFrancisco) * iQuantidadeRegistros);	
			
			//cout << "ANTES DO MERGE: " << vet[0].cJobTitle << endl;
			
			mergeSort(vet, 0, iQuantidadeRegistros-1);
			
			//cout << "DEPOIS DO MERGE: " << vet[0].cJobTitle << endl;
				
			ofstream aSubArquivoBinario;
			aSubArquivoBinario.open(("subarquivos/" + _sNomeSubArquivos + to_string(iQuantidadeSubArquivos) + ".bin"), ios::binary);
			
			if (aSubArquivoBinario.fail())
			{
				cout << "Falhou ao criar arquivo" << endl;
			}
			
			iQuantidadeSubArquivos++;
				
			aSubArquivoBinario.seekp(0);
			aSubArquivoBinario.write(reinterpret_cast<const char *>(&vet[0]), sizeof(PayrollSaoFrancisco) * (iQuantidadeRegistros-1));
							
			aSubArquivoBinario.close();
			
			/*
			 * Debug
			fstream aSubArquivoBinario2;
			aSubArquivoBinario2.open(("subarquivos/" + _sNomeSubArquivos + to_string(iQuantidadeSubArquivos) + ".bin"), ios::in | ios ::out | ios::binary);
			PayrollSaoFrancisco teste;
			aSubArquivoBinario2.seekg(0, aSubArquivoBinario2.beg);
			aSubArquivoBinario2.read(reinterpret_cast<char*>(&teste), sizeof(PayrollSaoFrancisco));
			cout << "Primeiro Registro do arquivo: " << teste.cJobTitle << endl;
			aSubArquivoBinario2.close();*/
			
			iPosAtual += iQuantidadeRegistros;
			aArquivoBinario.seekg((iPosAtual) * sizeof(PayrollSaoFrancisco), aArquivoBinario.beg);
			delete[] vet;
		}
	} else
	{
		cout << "Erro na leitura do arquivo!";
	}
	
	aArquivoBinario.close();
	return iQuantidadeSubArquivos+1;
}

void pcdRetirarPrimeiraPosicao(string _sNomeArquivo)
{
	//cout << "ESCREVEU NO PRINCIPAL" << endl;
	fstream aSubArquivoBinario;
	aSubArquivoBinario.open(_sNomeArquivo, ios::in | ios ::out | ios::binary);
	aSubArquivoBinario.seekg(0, aSubArquivoBinario.end);
	int iQtdDados = aSubArquivoBinario.tellg() / sizeof(PayrollSaoFrancisco);
	
	aSubArquivoBinario.seekg(0, aSubArquivoBinario.beg);
	PayrollSaoFrancisco *vet = new PayrollSaoFrancisco[iQtdDados];
	aSubArquivoBinario.read(reinterpret_cast<char*>(vet), sizeof(PayrollSaoFrancisco) * iQtdDados);						
				
	aSubArquivoBinario.close();	
	
	remove(_sNomeArquivo.c_str());
	
	ofstream aSubArquivoBinario2;
	aSubArquivoBinario2.open(_sNomeArquivo, ios::binary);
	aSubArquivoBinario2.seekp(0);
	aSubArquivoBinario2.write((const char *)(&vet[1]), sizeof(PayrollSaoFrancisco) * (iQtdDados-1));
	
	delete[] vet;
	aSubArquivoBinario2.close();
}

void pcdOrdenacaoArquivos(string _sNomeArquivoPrincipal, string _sNomeSubArquivos)
{
	fstream aArquivoBinario;
	aArquivoBinario.open(_sNomeArquivoPrincipal, ios::in | ios ::out | ios::binary);
	
	int iTamanhoMaximo = 0;
	int iPosAtual = 0;
	string sNomeArquivoMenorRegistro;
	aArquivoBinario.seekg(0, aArquivoBinario.end);
	iTamanhoMaximo = aArquivoBinario.tellg() / sizeof(PayrollSaoFrancisco);
	aArquivoBinario.seekg((iPosAtual) * sizeof(PayrollSaoFrancisco), aArquivoBinario.beg);
	aArquivoBinario.close();
	
	int iQuantidadeRegistrosInseridos = 0;
	int iQuantidadeSubArquivos = pcdDividirArquivoCompacto(_sNomeArquivoPrincipal, _sNomeSubArquivos);
	
	remove(_sNomeArquivoPrincipal.c_str());
	
	ofstream aCreateArquivoBinario;
	aCreateArquivoBinario.open((_sNomeArquivoPrincipal), ios::binary);
	aCreateArquivoBinario.close();
	
	int iQuantidadeArquivosSemRegistros = 0;
	
	cout << "QTD ESPERADA DE DADOS: " << iTamanhoMaximo << endl;
	
	bool bSetouPrimeiro = false;
	
	while ((iQuantidadeRegistrosInseridos < iTamanhoMaximo) and (iQuantidadeArquivosSemRegistros <= iQuantidadeSubArquivos))
	{
		iQuantidadeArquivosSemRegistros = 0;
		PayrollSaoFrancisco rgMenorRegistro;
		for (int i = 0; i < iQuantidadeSubArquivos; i++)
		{
			PayrollSaoFrancisco RegistroComparacao;
			ifstream aSubArquivoBinario;
			string sNomeArquivo = ("subarquivos/" + _sNomeSubArquivos + to_string(i) + ".bin");
			aSubArquivoBinario.open(sNomeArquivo, ios ::out | ios::binary);
			aSubArquivoBinario.seekg(0, aSubArquivoBinario.end);
			if ((aSubArquivoBinario.tellg() / sizeof(PayrollSaoFrancisco)) >= sizeof(PayrollSaoFrancisco) and (("subarquivos/" + _sNomeSubArquivos + to_string(i) + ".bin") != sNomeArquivoMenorRegistro))
			{
				aSubArquivoBinario.seekg(0, aSubArquivoBinario.beg);
				aSubArquivoBinario.read(reinterpret_cast<char*>(&RegistroComparacao), sizeof(PayrollSaoFrancisco));
			
				if (RegistroComparacao.cJobTitle[0] != '\0')
				{
					if (!bSetouPrimeiro)
					{
						rgMenorRegistro = RegistroComparacao;
						sNomeArquivoMenorRegistro = sNomeArquivo;
						bSetouPrimeiro = true;
					} else
					{
						if (fncComparaRegistro((RegistroComparacao), (rgMenorRegistro)) == 1)
						{
							sNomeArquivoMenorRegistro = sNomeArquivo;
							rgMenorRegistro = RegistroComparacao;
						}
					}
				}
			} else
			{
				if (!((aSubArquivoBinario.tellg() / sizeof(PayrollSaoFrancisco)) >= sizeof(PayrollSaoFrancisco)))
				{
					iQuantidadeArquivosSemRegistros++;
				}
			}
			
			aSubArquivoBinario.close();
		}
						
		if (sNomeArquivoMenorRegistro != "")
		{
			fstream aArquivoBinario;
			aArquivoBinario.open((_sNomeArquivoPrincipal), ios::in | ios ::out | ios::binary);
			aArquivoBinario.seekp(0, aArquivoBinario.end);
			
			aArquivoBinario.write((const char *)(&rgMenorRegistro), sizeof(PayrollSaoFrancisco));
			aArquivoBinario.close();
			
			pcdRetirarPrimeiraPosicao(sNomeArquivoMenorRegistro);
			
			sNomeArquivoMenorRegistro = "";
			
			iQuantidadeRegistrosInseridos++;
			
			if ((iQuantidadeRegistrosInseridos % 1000) == 0)
				cout << "QTD INSERIDOS: " << iQuantidadeRegistrosInseridos << endl;
			
			bSetouPrimeiro = false;
		}
	}
	aArquivoBinario.close();
	cout << "QTD INSERIDOS: " << iQuantidadeRegistrosInseridos << endl;
}

void pcdOrdenar(string _sNomeArquivo)
{
	// Primeiro passo é copiar
	
	fstream aArquivoBinario;
	aArquivoBinario.open(_sNomeArquivo, ios::in | ios ::out | ios::binary);
	
	if (aArquivoBinario)
	{		
		int iTamanhoMaximo = 0;
		int iPosAtual = 0;
		aArquivoBinario.seekg(0, aArquivoBinario.end);
		iTamanhoMaximo = aArquivoBinario.tellg() / sizeof(PayrollSaoFrancisco);
		aArquivoBinario.seekg((iPosAtual) * sizeof(PayrollSaoFrancisco), aArquivoBinario.beg);
		PayrollSaoFrancisco *vet = new PayrollSaoFrancisco[1];
		int iContRegistros = 0;
		while (iPosAtual < iTamanhoMaximo)
		{
			PayrollSaoFrancisco RegistroComparacao;
			aArquivoBinario.read(reinterpret_cast<char*>(&RegistroComparacao), sizeof(PayrollSaoFrancisco));
						
			vet[iContRegistros] = RegistroComparacao;       
			iContRegistros++;
			
			if ((iContRegistros > 3000) or ((iPosAtual) >= iTamanhoMaximo))
			{
				mergeSort(vet, 0, iContRegistros-1);
				for (int i = 0; i < (iContRegistros); i++)
				{
					/*cout << ((iPosAtual+1)-(iContRegistros))+i << " - RAIZ: " << vet[i].cJobTitle << " : " << vet[i].fOvertimePay << endl;
					cout << (iContRegistros) << " - " << i << " -- ";
					cout << vet[i].iID << ", ";
					cout << vet[i].cEmployeeName << ", ";
					cout << vet[i].cJobTitle << ", ";
					cout << vet[i].fBasePay << ", "; 
					cout << vet[i].fOvertimePay << ", ";
					cout << vet[i].fOtherPay << ", ";
					cout << vet[i].fBenefits << ", ";
					cout << vet[i].fTotalPay << ", ";
					cout << vet[i].fTotalPay_Benefits << ", ";  
					cout << vet[i].iYear << endl; */      
					aArquivoBinario.seekp(((((iPosAtual+1)-(iContRegistros))+i) * sizeof(PayrollSaoFrancisco)));
					aArquivoBinario.write((const char *)(&vet[i]), sizeof(PayrollSaoFrancisco));
				}
				iContRegistros = 0;
				aArquivoBinario.seekg((iPosAtual+1) * sizeof(PayrollSaoFrancisco));
			}
			
			iPosAtual++;
			if (((iPosAtual) < iTamanhoMaximo))
			{
				vet = fncAlocarVetor(vet, iContRegistros+1);
			}	
		}
	} else
	{
		cout << "Erro na leitura do arquivo!";
	}
	
	aArquivoBinario.close();
}



int main()
{

    string sNomeArquivo = "san_francisco_payroll_dataset.csv";
    string sNomeArquivoBinario = "san_francisco_payroll_dataset.bin";
    
    int iOpcao = -1;
    
    while(iOpcao != 0)
    {
		cout << "=============================================================" << endl;
		cout << "0 - Sair" << endl; // OK
		cout << "1 - Converter para binario" << endl; // OK
		cout << "2 - Imprimir todos registros" << endl; // OK
		cout << "3 - Imprimir registros entre intervalos de posicoes" << endl; // OK
		cout << "4 - Adicionar um registro em uma posicao especifica" << endl; // OK
		cout << "5 - Trocar elementos de posicao" << endl; // OK
		cout << "6 - Alterar dados de um registro de uma posicao" << endl; // OK
		cout << "7 - Inserir registro no final" << endl; // OK
		cout << "8 - Ordenar arquivo binario" << endl; 
		cout << "=============================================================" << endl;
		
		cin >> iOpcao;
		
		cout << "=============================================================" << endl;
		if (iOpcao == 1)
		{    
			cout << "Convertendo para binario..." << endl;
			fncConverterCSVParaBinario(sNomeArquivo, sNomeArquivoBinario);
		} else if (iOpcao == 2)
		{
			cout << "Imprimindo registros..." << endl;
			string sNomeArquivo;
			cin >> sNomeArquivo;
			if (sNomeArquivo == "*")
				sNomeArquivo = sNomeArquivoBinario;
			fncImprimirArquivoBinario(sNomeArquivo, -1, -1);
		} else if (iOpcao == 3)
		{
			int iPosicaoInicial, iPosicaoFinal;
			cout << "Digite a primeira posicao: ";
			cin >> iPosicaoInicial;
			cout << "Digite a segunda posicao: ";
			cin >> iPosicaoFinal;
			cout << "Imprimindo registros nas posicoes: " << iPosicaoInicial << " - " << iPosicaoFinal <<  "..." << endl;
			fncImprimirArquivoBinario(sNomeArquivoBinario, iPosicaoInicial, iPosicaoFinal);
		} else if (iOpcao == 4)
		{
			int iPosicao = 0;
			cout << "Digite a posicao que gostaria de inserir o registro: ";
			cin >> iPosicao;
			cout << endl;
			PayrollSaoFrancisco TmpRegistro = fncLerRegistro();
			cout << "Adicionando registro..." << endl;
			fncAdicionarRegistro(iPosicao, TmpRegistro, sNomeArquivoBinario);
		} else if (iOpcao == 5)
		{
			int iPrimeiraPosicao = 0, iSegundaPosicao = 0;
			cout << "Digite a primeira posicao: ";
			cin >> iPrimeiraPosicao;
			cout << "Digite a segunda posicao: ";
			cin >> iSegundaPosicao;
			cout << "Trocando elementos de posicao..." << endl;
			fncTrocarPosicao(iPrimeiraPosicao, iSegundaPosicao, sNomeArquivoBinario);
		} else if (iOpcao == 6)
		{
			int iPosicao = 0;
			cout << "Digite a posicao que gostaria de alterar o registro: ";
			cin >> iPosicao;
			cout << endl;
			PayrollSaoFrancisco TmpRegistro = fncLerRegistro();
			cout << "Alterando registro..." << endl;
			fncAlterarRegistro(iPosicao, TmpRegistro, sNomeArquivoBinario);	
		} else if (iOpcao == 7)
		{
			PayrollSaoFrancisco TmpRegistro = fncLerRegistro();
			cout << "Inserindo registro no final..." << endl;
			fncInserirNoFinal(TmpRegistro, sNomeArquivoBinario);
		} else if (iOpcao == 8)
		{
			cout << "Ordenando registros..." << endl;
			pcdOrdenacaoArquivos(sNomeArquivoBinario, "subArquivo");
		} else if (iOpcao == 9)
		{
			cout << "Dividindo arquivo..." << endl;
			pcdDividirArquivoCompacto(sNomeArquivoBinario, "subArquivo");
		} else if (iOpcao == 0)
		{
			cout << "Saindo..." << endl;
		} else
		{
			cout << "Opcao nao encontrada..." << endl;
		}
	}

    return 0;
}
