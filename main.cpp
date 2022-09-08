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
			}
            getline(aArquivoEntrada, sValorCampo, ',');
            // Se o ID da primeira posição não estiver vazio, então o arquivo tem informações.
            if (sValorCampo != "")
            {   
				// Ler e converter as informações da linha para o registro			
				
				TRegistro.iID = std::stoi(sValorCampo);
				
				getline(aArquivoEntrada, sValorCampo, ','); 
				
				if (sValorCampo[0] == '"')
				{					
					iTamanho = sValorCampo.size();
					for (int i = 0; i < iTamanho; i++)
					{
						(TRegistro.cEmployeeName)[i] = (sValorCampo)[i];
					} 
					
					getline(aArquivoEntrada, sValorCampo, '"'); 
					
					int iOutroTamanho = sValorCampo.size();
					
					for (int i = 0; i < iOutroTamanho; i++)
					{
						(TRegistro.cEmployeeName)[i] = (sValorCampo)[i];
					} 
					
					getline(aArquivoEntrada, sValorCampo, ',');
					
					(TRegistro.cEmployeeName)[(iTamanho + iOutroTamanho)] = '\0';
				} else
				{					
					iTamanho = sValorCampo.size();
					for (int i = 0; i < iTamanho; i++)
					{
						(TRegistro.cEmployeeName)[i] = (sValorCampo)[i];
					}
					(TRegistro.cEmployeeName)[iTamanho] = '\0';		
				}		
				
				
				getline(aArquivoEntrada, sValorCampo, ','); 
				
				if (sValorCampo[0] == '"')
				{					
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
				{					
					iTamanho = sValorCampo.size();
					for (int i = 0; i < iTamanho; i++)
					{
						(TRegistro.cJobTitle)[i] = (sValorCampo)[i];
					} 
					
					(TRegistro.cJobTitle)[iTamanho] = '\0';
				}
				
				getline(aArquivoEntrada, sValorCampo, ',');  				
				TRegistro.fBasePay = std::atof(sValorCampo.c_str());
				
				getline(aArquivoEntrada, sValorCampo, ',');  				
				TRegistro.fOvertimePay = std::atof(sValorCampo.c_str());
				
				getline(aArquivoEntrada, sValorCampo, ',');
				if (sValorCampo == "Not Provided")
					sValorCampo = '0';
				TRegistro.fOtherPay = std::atof(sValorCampo.c_str());
				
				getline(aArquivoEntrada, sValorCampo, ',');
				TRegistro.fBenefits = std::atof(sValorCampo.c_str());
				
				getline(aArquivoEntrada, sValorCampo, ',');
				TRegistro.fTotalPay = std::atof(sValorCampo.c_str());
				
				getline(aArquivoEntrada, sValorCampo, ',');				
				TRegistro.fTotalPay_Benefits = std::atof(sValorCampo.c_str());
				
				getline(aArquivoEntrada, sValorCampo); 				
				TRegistro.iYear = std::stoi(sValorCampo);
				
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

// Retorna 1 caso o primeiro registro informado for menor que o segundo, e o segundo, caso contrário.
int fncComparaRegistro(PayrollSaoFrancisco _TMPREGISTRO1, PayrollSaoFrancisco _TMPREGISTRO2)
{
	// Primeiro compara cJobTitle.
	if (_TMPREGISTRO1.cJobTitle != _TMPREGISTRO2.cJobTitle)
	{
		int iComparacao = strcmp(_TMPREGISTRO1.cJobTitle, _TMPREGISTRO2.cJobTitle);
		if (iComparacao < 0)
		{
			return 1;
		} else if (iComparacao > 0)
		{
			return 2;
		} else
		{
			// Caso não for nem maior, nem menor, ou seja, é igual, então compara-se o ID.
			if (_TMPREGISTRO1.iID < _TMPREGISTRO2.iID)
			{
				return 1;
			} else
			{			
				return 2;
			}
		}
	} else
	{
		if (_TMPREGISTRO1.iID < _TMPREGISTRO2.iID)
		{			
			return 1;
		} else
		{			
			return 2;
		}
	}
}

// Função para fazer merge em vetor de PayrollSaoFrancisco
void merge(PayrollSaoFrancisco *_Vetor, int _iEsquerda, int m, int _iDireita) {
	int i, j, k, iEsquerda, iDireita;
	
	iEsquerda = m - _iEsquerda + 1; 
	iDireita = _iDireita - m;
	PayrollSaoFrancisco ArrayEsquerda[iEsquerda];
	PayrollSaoFrancisco ArrayDireita[iDireita];
	
	for(i = 0; i<iEsquerda; i++)
	{
      ArrayEsquerda[i] = _Vetor[_iEsquerda + i];
	}
	for (j = 0; j<iDireita; j++)
	{
		ArrayDireita[j] = _Vetor[m + 1 + j];
	}
	
	i = 0; 
	j = 0; 
	k = _iEsquerda;

	while (i < iEsquerda && j<iDireita) 
	{
		if (fncComparaRegistro(ArrayEsquerda[i], ArrayDireita[j]) == 1) 
		{
			_Vetor[k] = ArrayEsquerda[i];
			i++;
		} else
		{
			_Vetor[k] = ArrayDireita[j];
			j++;
		}
		k++;
	}

	while (i < iEsquerda) 
	{  
		_Vetor[k] = ArrayEsquerda[i];
		i++; 
		k++;
	}

	while (j < iDireita) {
		_Vetor[k] = ArrayDireita[j];
		j++; 
		k++;
	}
}

// Função MergeSort
void mergeSort(PayrollSaoFrancisco *_Vetor, int _iEsquerda, int _iDireita) {
   if(_iEsquerda < _iDireita) {
      int iAux = _iEsquerda + (_iDireita - _iEsquerda) / 2;
      mergeSort(_Vetor, _iEsquerda, iAux);
      mergeSort(_Vetor, iAux + 1, _iDireita);
      merge(_Vetor, _iEsquerda, iAux, _iDireita);
   }
}

// Struct auxiliar para organização de subarquivos.
struct SubArquivos
{
	PayrollSaoFrancisco dado;
	string sNomeArquivo;
	int iQuantidadeRegistros;
};

// Merge no Vetor de SubArquivos.
void mergeSubArquivos(SubArquivos *_Vetor, int _iEsquerda, int m, int _iDireita) {
	int i, j, k, iEsquerda, iDireita;

	iEsquerda = m - _iEsquerda + 1; 
	iDireita = _iDireita - m;
	SubArquivos ArrayEsquerda[iEsquerda];
	SubArquivos ArrayDireita[iDireita];
	
	for(i = 0; i<iEsquerda; i++)
	{
      ArrayEsquerda[i] = _Vetor[_iEsquerda + i];
	}
	for (j = 0; j<iDireita; j++)
	{
		ArrayDireita[j] = _Vetor[m + 1 + j];
	}
	
	i = 0; 
	j = 0; 
	k = _iEsquerda;

	while (i < iEsquerda && j<iDireita) 
	{
		if (fncComparaRegistro(ArrayEsquerda[i].dado, ArrayDireita[j].dado) == 1) 
		{
			_Vetor[k] = ArrayEsquerda[i];
			i++;
		} else
		{
			_Vetor[k] = ArrayDireita[j];
			j++;
		}
		k++;
	}

	while (i < iEsquerda) 
	{     
		_Vetor[k] = ArrayEsquerda[i];
		i++; 
		k++;
	}

	while (j < iDireita) { 
		_Vetor[k] = ArrayDireita[j];
		j++; 
		k++;
	}
}

// Função MergeSort de subarquivos
void mergeSortSubArquivos(SubArquivos *_Vetor, int _iEsquerda, int _iDireita) {
   if(_iEsquerda < _iDireita) {
      int iAux = _iEsquerda + (_iDireita - _iEsquerda) / 2;
      // Sort first and second arrays
      mergeSortSubArquivos(_Vetor, _iEsquerda, iAux);
      mergeSortSubArquivos(_Vetor, iAux + 1, _iDireita);
      mergeSubArquivos(_Vetor, _iEsquerda, iAux, _iDireita);
   }
}

// Função para dividir o arquivo principal em subarquivos.
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
		// A quantidade escolhida de registros máximos por subarquivo é 3500
		int iQuantidadeRegistros = 3500;
		while (iPosAtual < iTamanhoMaximo)
		{
			
			// caso a quantidade de registros restantes for menor que 3500, insere um ultimo pacote com essa quantidade.
			if ((iTamanhoMaximo - iPosAtual) < 3500)
				iQuantidadeRegistros = (iTamanhoMaximo - iPosAtual);
			
			PayrollSaoFrancisco *vet = new PayrollSaoFrancisco[iQuantidadeRegistros];
			aArquivoBinario.read(reinterpret_cast<char*>(vet), sizeof(PayrollSaoFrancisco) * iQuantidadeRegistros);	
			
			// Faz um MergeSort para inserir no SubArquivo ordenado.
			mergeSort(vet, 0, iQuantidadeRegistros-1);
				
			ofstream aSubArquivoBinario;
			aSubArquivoBinario.open(("subarquivos/" + _sNomeSubArquivos + to_string(iQuantidadeSubArquivos) + ".bin"), ios::binary);
			
			if (aSubArquivoBinario.fail())
			{
				cout << "Falhou ao criar arquivo" << endl;
			}
			
			iQuantidadeSubArquivos++;
			
			// Escrever vetor no subarquivo.
			aSubArquivoBinario.seekp(0);
			aSubArquivoBinario.write(reinterpret_cast<const char *>(&vet[0]), sizeof(PayrollSaoFrancisco) * (iQuantidadeRegistros-1));
							
			aSubArquivoBinario.close();
			
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

// Função para remover o primeiro registro do arquivo escolhido.
void pcdRetirarPrimeiraPosicao(string _sNomeArquivo)
{
	// Abrindo o arquivo primeiramente para verificar a quantidade de registros.
	fstream aSubArquivoBinario;
	aSubArquivoBinario.open(_sNomeArquivo, ios::in | ios ::out | ios::binary);
	aSubArquivoBinario.seekg(0, aSubArquivoBinario.end);
	int iQtdDados = aSubArquivoBinario.tellg() / sizeof(PayrollSaoFrancisco);
	
	aSubArquivoBinario.seekg(0, aSubArquivoBinario.beg);
	PayrollSaoFrancisco *vet = new PayrollSaoFrancisco[iQtdDados];
	aSubArquivoBinario.read(reinterpret_cast<char*>(vet), sizeof(PayrollSaoFrancisco) * iQtdDados);						
				
	aSubArquivoBinario.close();	
	
	// Remove o arquivo inteiro para criar novamente, inserindo após a segunda posição do vetor lido, para não precisar percorre-lo inteiro.
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
	// Abrir o arquivo para pegar tamanho máximo
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
		
	// Dividir o arquivo principal em sub-arquivos ordenados
	int iQuantidadeSubArquivos = pcdDividirArquivoCompacto(_sNomeArquivoPrincipal, _sNomeSubArquivos);
	
	// Remover o arquivo principal para liberar o espaço inicial
	remove(_sNomeArquivoPrincipal.c_str());
	
	// Criar o arquivo principal para inserção dos registros.
	ofstream aCreateArquivoBinario;
	aCreateArquivoBinario.open((_sNomeArquivoPrincipal), ios::binary);
	aCreateArquivoBinario.close();		
		
	// Criado novo vetor da nova Struct que contem o Primeiro registro de cada arquivo, a quantidade de registros e o nome desse arquivo.
	SubArquivos *VetorPrimeiroRegistro = new SubArquivos[iQuantidadeSubArquivos];
	
	// Preencher as posições do vetor de subarquivo.
	for (int i = 0; i < iQuantidadeSubArquivos; i++)
	{
		PayrollSaoFrancisco RegistroComparacao;
		ifstream aSubArquivoBinario;
		string sNomeArquivo = ("subarquivos/" + _sNomeSubArquivos + to_string(i) + ".bin");
		aSubArquivoBinario.open(sNomeArquivo, ios ::out | ios::binary);
		aSubArquivoBinario.seekg(0, aSubArquivoBinario.end);
		
		int iQuantidadeDados = aSubArquivoBinario.tellg() / sizeof(PayrollSaoFrancisco);
		
		aSubArquivoBinario.seekg(0, aSubArquivoBinario.beg);
		aSubArquivoBinario.read(reinterpret_cast<char*>(&RegistroComparacao), sizeof(PayrollSaoFrancisco));
		VetorPrimeiroRegistro[i].dado = RegistroComparacao;
		VetorPrimeiroRegistro[i].sNomeArquivo = sNomeArquivo;			
		VetorPrimeiroRegistro[i].iQuantidadeRegistros = iQuantidadeDados;			
		aSubArquivoBinario.close();
	}
	
	// Fazer um mergeSort dos SubArquivos
	mergeSortSubArquivos(VetorPrimeiroRegistro, 0, iQuantidadeSubArquivos-1);
	
	int iPosicao = 0;
	bool bFazerMergeSort = false;
	bool bRemoverUltimoArquivo = false;
	while (iQuantidadeRegistrosInseridos <= iTamanhoMaximo and ((iQuantidadeSubArquivos-1) > 0))
	{
		// Caso estiver marcado para Fazer merge, 			
		if (bFazerMergeSort)
		{
			mergeSortSubArquivos(VetorPrimeiroRegistro, 0, iQuantidadeSubArquivos-1);
		}
			
		// Essa flag é indicada para remover o ultimo vetor para 
		if (bRemoverUltimoArquivo)
		{
			iQuantidadeSubArquivos--;
			bRemoverUltimoArquivo = false;
		}
			
		// Como o vetor de SubArquivo está ordenado pelo menor registro, eu pego o registro da posição "iPosicao" que indica o próximo menor registro
		PayrollSaoFrancisco rgMenorRegistro = (VetorPrimeiroRegistro)[iPosicao].dado;
		sNomeArquivoMenorRegistro = VetorPrimeiroRegistro[iPosicao].sNomeArquivo;
		VetorPrimeiroRegistro[iPosicao].iQuantidadeRegistros--;
		// Como eu encontrei o menor registro, fazemos a remoção do primeiro registro desse arquivo(O menor inserido no arquivo principal);
		pcdRetirarPrimeiraPosicao(sNomeArquivoMenorRegistro);
		
		// Nesse momento lemos o segundo menor registro do arquivo que contém o menor registro para "passar" ele para frente.
		PayrollSaoFrancisco RegistroComparacao;
		ifstream aSubArquivoBinario;
		aSubArquivoBinario.open(sNomeArquivoMenorRegistro, ios ::out | ios::binary);
		aSubArquivoBinario.seekg(0, aSubArquivoBinario.beg);
		aSubArquivoBinario.read(reinterpret_cast<char*>(&RegistroComparacao), sizeof(PayrollSaoFrancisco));		
		VetorPrimeiroRegistro[iPosicao].dado = RegistroComparacao;
		
		// Caso na posição atual, a quantidade de registros for menor ou igual a zero, preencher o produto com informações
		// altas, para que no MergeSort, ele seja jogado por último, e posteirormente será excluido da última posição.
		if (VetorPrimeiroRegistro[iPosicao].iQuantidadeRegistros <= 0)
		{
			VetorPrimeiroRegistro[iPosicao].dado.iID = 999999;
			for (int i = 0; i < 20; i++)
			{
				VetorPrimeiroRegistro[iPosicao].dado.cJobTitle[i] = 'Z'; 
			}
		}
		aSubArquivoBinario.close();
				
		// Verificar se a posição que eu estou lendo do Vetor de SubArquivos, 
		if (iPosicao < (iQuantidadeSubArquivos-1))
		{
			// Essa comparação foi feita para evitar ordenação desnecessária,
			// Se o próximo registro ainda for menor que o anterior substituido no arquivo que contém o menor registro,
			// então não vai ser necessário fazer MergeSort.
			// As outras cláusulas são para evitar quebra da quantidade de registros do vetor.
			if (fncComparaRegistro(RegistroComparacao, VetorPrimeiroRegistro[iPosicao+1].dado) == 1)
			{
				bFazerMergeSort = true;
				iPosicao = 0;
			}
			else
			{
				if (iPosicao == (iQuantidadeSubArquivos-1))
				{
					bFazerMergeSort = true;
					iPosicao = 0;
				} else
				{
					bFazerMergeSort = false;
					iPosicao++;
				}				
			}
		} else
		{
			bFazerMergeSort = true;
			iPosicao = 0;
		}
					
		// Caso o registro encontrado não esteja marcado para "excluir", inserimos ele no arquivo principal.
		if ((rgMenorRegistro.iID != 999999))
		{
			fstream aArquivoBinario;
			aArquivoBinario.open((_sNomeArquivoPrincipal), ios::in | ios ::out | ios::binary);
			aArquivoBinario.seekp(0, aArquivoBinario.end);
				
			aArquivoBinario.write((const char *)(&rgMenorRegistro), sizeof(PayrollSaoFrancisco));
			aArquivoBinario.close();
							
			iQuantidadeRegistrosInseridos++;
						
			if ((iQuantidadeRegistrosInseridos % 1000) == 0)
				cout << "Aguarde... ordenando arquivo!" << endl;
		} else
		{
			// Caso o registro encontraso seja um dos que foi marcado como "excluido" após o MergeSort ele irá para a ultima posição
			// Então devemos marcar para removê-lo.
			bFazerMergeSort = true;
			iPosicao = 0;
			bRemoverUltimoArquivo = true;
		}
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
		cout << "3 - Ordenar arquivo binario" << endl; // OK
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
			fncImprimirArquivoBinario(sNomeArquivoBinario, -1, -1);
		} else if (iOpcao == 3)
		{
			cout << "Ordenando registros..." << endl;
			pcdOrdenacaoArquivos(sNomeArquivoBinario, "subArquivo");
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
