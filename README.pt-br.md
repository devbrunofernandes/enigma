![Enigma logo](images/Enigma-logo.png)

# Simulador da Máquina Enigma em C++

[Leia este documento em Inglês (Read this document in English)](./README.md)

Um simulador de interface de linha de comando (CLI) da máquina de criptografia Enigma M3 da Segunda Guerra Mundial, escrito em C++ moderno.

## ⏩ Funcionalidades

- Simulação completa da Enigma M3 com rotores (I-V), refletores (A, B, C) e um plugboard configurável.

- **Operação em Modo Duplo:** Funciona tanto como um menu interativo quanto como uma ferramenta de pipeline de linha de comando.

- **Suporte Completo de E/S (I/O):** Lê do `stdin` ou de arquivos, escreve no `stdout` ou em arquivos, e funciona perfeitamente com pipes (`|`).

- **Configuração Completa:** Todas as configurações da máquina são controláveis via flags de linha de comando (rotores, posições, refletor e plugboard).

- **Validação Robusta:** Protege contra configurações inválidas da máquina (ex: contagem incorreta de rotores, posições não-alfabéticas).

- **Modo Passo-a-Passo:** Um recurso especial no menu interativo para visualizar o caminho do caractere durante a criptografia.

## 🔨 Compilando o Projeto

### Pré-requisitos

- `git` (para clonar e para o `FetchContent`)
- `cmake` (versão 3.14 ou superior)
- Um compilador C++17 (ex: `g++`, `Clang`, `MSVC`)

### Instruções

```bash
# 1. Clone o repositório
git clone [https://github.com/devbrunofernandes/enigma.git](https://github.com/devbrunofernandes/enigma.git)
cd enigma

# 2. Crie um diretório de build
mkdir build && cd build

# 3. Configure com o CMake
# (Isto irá baixar a dependência cxxopts automaticamente)
cmake ..

# 4. Compile o projeto
cmake --build .
```

## 🔌 Como Usar

Este simulador pode rodar em dois modos distintos, dependendo de como é iniciado.

### Modo Interativo

Inicia um menu interativo que guia o usuário na configuração da máquina Enigma e na criptografia de textos.

**Como rodar:**

```bash
./enigma_machine
```

**Caso de Uso:** Ideal para aprender como a máquina funciona, testar configurações ou usar o visualizador passo-a-passo.

![interactive mode output](images/interactive-mode.png)

### Modo de Argumentos (Pipeline)

Funciona como um filtro de linha de comando, processando toda a entrada do `stdin` ou de um arquivo e imprimindo o resultado no `stdout` ou em um arquivo.

**Como rodar:**

- Passando qualquer argumento de linha de comando (como `-h` ou `-f`).
- Usando um pipe (`|`) para enviar dados.
- Redirecionando (`>`) a saída.

**Caso de Uso:** Feito para scripting e integração com outras ferramentas de linha de comando em um pipeline Unix. Também serve para processar arquivos de texto.

![usage of help flag](images/help.png)

## 🖥️ Exemplos de Uso

![example use for program](images/testing.png)