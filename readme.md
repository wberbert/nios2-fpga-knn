# Projeto de Aprendizado de Máquina KNN em FPGA com NIOS II

Este projeto implementa um modelo de aprendizado de máquina K-Nearest Neighbors (KNN) utilizando FPGA e o processador NIOS II. O objetivo é demonstrar a capacidade de acelerar algoritmos de aprendizado de máquina em hardware e a integração com o processador NIOS II para executar operações de controle e processamento de dados.

## Visão Geral

O algoritmo KNN é uma técnica de aprendizado supervisionado amplamente usada para classificação e regressão. Este projeto adapta o algoritmo KNN para execução em hardware FPGA, utilizando o processador NIOS II para coordenar o processamento e gerenciar os dados.

### Funcionalidades

- **Implementação do Algoritmo KNN**: Aceleração do algoritmo KNN em hardware FPGA para processamento eficiente de dados.
- **Processador NIOS II**: Integra o processador NIOS II para controle e gerenciamento do fluxo de dados.
- **Interface de Comunicação**: Comunicação entre o FPGA e o processador NIOS II para troca de informações e controle.

## Requisitos

- FPGA com suporte para o processador NIOS II (por exemplo, placas DE-Series da Altera)
- Software de desenvolvimento FPGA (Quartus II ou similar)
- IDE para o desenvolvimento do processador NIOS II (Eclipse com o NIOS II EDS)
- Conhecimento básico em VHDL/Verilog para desenvolvimento em FPGA
- Familiaridade com o algoritmo KNN e aprendizado de máquina

## Instalação e Configuração

1. **Configuração do Ambiente de Desenvolvimento:**
   - Instale o software Quartus II e o NIOS II EDS.
   - Configure a placa FPGA e o ambiente de desenvolvimento conforme a documentação do fabricante.

2. **Compilação do Hardware FPGA:**
   - Abra o projeto FPGA no Quartus II.
   - Compile o design para gerar o bitstream do FPGA.

3. **Desenvolvimento e Compilação do Processador NIOS II:**
   - Abra o projeto NIOS II na IDE Eclipse.
   - Implemente o código de controle e comunicação com o FPGA.
   - Compile o projeto para gerar o arquivo de firmware.

4. **Carregamento e Execução:**
   - Carregue o bitstream do FPGA na placa utilizando o Quartus II.
   - Carregue o firmware do NIOS II na placa utilizando a IDE Eclipse.
   - Execute o modelo KNN no FPGA e controle o processamento pelo NIOS II.

## Uso

- **Executar o Algoritmo KNN**: O algoritmo KNN é executado no hardware FPGA. O processador NIOS II coordena a execução e gerencia a troca de dados.
- **Interação**: Utilize interfaces de comunicação configuradas para interagir com o FPGA e o processador NIOS II durante o processamento.

## Exemplos

Forneça exemplos de dados e código para demonstrar a execução do algoritmo KNN, se aplicável.

## Contribuindo

Contribuições são bem-vindas! Para contribuir, por favor, abra um *pull request* ou relate problemas na seção de *issues*.

## Licença

Este projeto está licenciado sob a Licença Pública Geral GNU (GPL) - consulte o arquivo `LICENSE` para mais detalhes.

## Contato

Para mais informações, entre em contato com Wanderson Berbert (wberbert@outlook.com).
