-- Drop database homecosmetico;
Create database HomeCosmetico;
use HomeCosmetico; 

CREATE TABLE Fornecedor (
    NomeFantasia VARCHAR(100) NOT NULL,
    RazaoSocial VARCHAR(100) NOT NULL,
    CNPJ VARCHAR(15) NOT NULL PRIMARY KEY,
    Telefone VARCHAR(11) NOT NULL,
    Representante VARCHAR(100) NOT NULL, 
    Email VARCHAR(100), 
    CEP VARCHAR(8),
    Endereco VARCHAR(100),
    UF ENUM("AC", "AL", "AP", "AM", "BA", "CE", "DF", "ES", "GO", "MA", "MT", "MS", "MG", 
             "PA", "PB", "PR", "PE", "PI", "RJ", "RN", "RS", "RO", "RR", "SC", "SP", "SE", "TO"),
    Cidade VARCHAR(100),
    Bairro VARCHAR(100),
    Frete_min INT,
    Ramal VARCHAR(10),
    site VARCHAR(100) UNIQUE,
    DataCadastro DATE
);

-- drop table Funcionario;
CREATE TABLE Funcionario (
    MatFunc VARCHAR(5) PRIMARY KEY,
    Nome VARCHAR(100) NOT NULL,
    Cargo VARCHAR(100) NOT NULL,
    Salario DECIMAL(10,2) NOT NULL,
    CPF VARCHAR(11) UNIQUE NOT NULL,
    Data_admissao DATE NOT NULL,
    Data_demissao DATE,
    Vale_alimentacao ENUM('Ifood', 'Alelo', 'Sodexo', 'Vr beneficios') NOT NULL,
    PlanoSaude ENUM('Hapvida', 'Promedica', 'Sulamerica') NOT NULL
);

CREATE TABLE Produto (
    CodBarra VARCHAR(25) NOT NULL PRIMARY KEY,
    Nome VARCHAR(100) UNIQUE,
    ValorCompra DECIMAL(10,2) NOT NULL DEFAULT 0.0,
    ValorVenda DECIMAL(10,2) NOT NULL DEFAULT 0.0,
    CNPJ VARCHAR(15) NOT NULL,
    Descricao VARCHAR(50),
    Marca VARCHAR(30),
    DtFab DATE NOT NULL,
    DtVal DATE NOT NULL,
    Lote VARCHAR(5) NOT NULL,
    
    FOREIGN KEY (CNPJ) REFERENCES Fornecedor (CNPJ)
        ON UPDATE CASCADE
        ON DELETE RESTRICT
);

CREATE TABLE Venda (
    IdVenda INT AUTO_INCREMENT PRIMARY KEY,
    MatFunc VARCHAR(5) NOT NULL,
    DataVenda DATETIME NOT NULL,
    CPF VARCHAR(11),
    
    FOREIGN KEY (MatFunc) REFERENCES Funcionario (MatFunc)
        ON UPDATE CASCADE
        ON DELETE RESTRICT
);

CREATE TABLE ItemVenda (
    IdItem INT AUTO_INCREMENT PRIMARY KEY,
    IdVenda INT,
    MatFunc VARCHAR(5),
    CodBarra VARCHAR(25),
    Quantidade INT NOT NULL,
    ValorUnitario DECIMAL(10,2) NOT NULL,
    Desconto DECIMAL(10,2) DEFAULT 0,
    Montante DECIMAL(10,2) DEFAULT 0,

    FOREIGN KEY (IdVenda) REFERENCES Venda(IdVenda)
        ON DELETE CASCADE,
    
    FOREIGN KEY (CodBarra) REFERENCES Produto(CodBarra)
        ON UPDATE CASCADE
        ON DELETE RESTRICT,
	
    FOREIGN KEY (MatFunc) REFERENCES Funcionario(MatFunc)
        ON DELETE RESTRICT
);
    
