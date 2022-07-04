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
    double fBenefits; // Benefícios
    double fTotalPay; // Pagamento Total
    double fTotalPay_Benefits; // Pagamento Total 
    int iYear; // Ano      
};

void converterCSVParaBinario(string _sNomeArquivoEntrada, string _sNomeArquivoSaida)
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
        while(!aArquivoEntrada.eof())
        {
			if (!bLeuNomeCampo)
			{
				getline(aArquivoEntrada, sNomeCampos);
				bLeuNomeCampo = true;
				cout << sNomeCampos << endl;
			}
            getline(aArquivoEntrada, sValorCampo, ',');
            if (sValorCampo != "")
            {   
				cout << sValorCampo << ","; 
				
				TRegistro.iID = std::stoi(sValorCampo);
				
				getline(aArquivoEntrada, sValorCampo, ','); 
				cout << sValorCampo << ",";
				iTamanho = int(sizeof(sValorCampo));
				for (int i = 0; i < iTamanho; i++)
				{
					(TRegistro.cEmployeeName)[i] = (sValorCampo)[i];
				}
				
				getline(aArquivoEntrada, sValorCampo, ','); 
				cout << sValorCampo << ","; 
				iTamanho = int(sizeof(sValorCampo));
				for (int i = 0; i < iTamanho; i++)
				{
					(TRegistro.cJobTitle)[i] = (sValorCampo)[i];
				} 
				
				getline(aArquivoEntrada, sValorCampo, ',');  
				cout << sValorCampo << ",";
				TRegistro.fBasePay = std::atof(sValorCampo.c_str());
				
				getline(aArquivoEntrada, sValorCampo, ',');  
				cout << sValorCampo << ",";
				TRegistro.fOvertimePay = std::atof(sValorCampo.c_str());
				
				getline(aArquivoEntrada, sValorCampo, ',');
				if (sValorCampo == "Not Provided")
					sValorCampo = '0';
				TRegistro.fOtherPay = std::atof(sValorCampo.c_str());
				
				getline(aArquivoEntrada, sValorCampo, ',');  
				TRegistro.fBenefits = std::atof(sValorCampo.c_str());
				
				getline(aArquivoEntrada, sValorCampo, ',');  
				TRegistro.fTotalPay = std::atof(sValorCampo.c_str());
				
				getline(aArquivoEntrada, sValorCampo);
				cout << sValorCampo;  
				TRegistro.fTotalPay_Benefits = std::atof(sValorCampo.c_str());

				cout << endl;
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


void imprimirArquivoBinario(string _sNomeArquivoBinario)
{
	
    ifstream aArquivoBinario;
    aArquivoBinario.open(_sNomeArquivoBinario, ios::binary);

    if (aArquivoBinario)
    {
        aArquivoBinario.seekg(0, aArquivoBinario.end);
        int tam = aArquivoBinario.tellg();
        aArquivoBinario.seekg(0, aArquivoBinario.beg);

        int numero_registros = tam / sizeof(registro);

        registro* vetor_registros = new registro[numero_registros];

        for (int i = 0; i < numero_registros; i++) 
        {
            entrada.read((char*)(&vetor_registros[i]), sizeof(registro));         
        }

        entrada.close();
    }
    else
    {
        cout << "Erro na leitura do arquivo!";
    }

	//aArquivoBinario.read(reinterpret_cast<char *> (&variavel), sizeof(tipo_dado_variavel));
}


int main()
{

    string sNomeArquivo = "san_francisco_payroll_dataset.csv";
    string sNomeArquivoBinario = "san_francisco_payroll_dataset.bin";
    
    converterCSVParaBinario(sNomeArquivo, sNomeArquivoBinario);
    
    imprimirArquivoBinario(sNomeArquivoBinario);

    return 0;
}