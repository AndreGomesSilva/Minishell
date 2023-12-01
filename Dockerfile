# Escolha a imagem base
FROM ubuntu:latest

# Atualize o sistema e instale os pacotes necessários
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
	make \
	g++ \
    git \
	clang-12 \
	tar \
	gcc-10 \
	curl \
	software-properties-common

# Instale o OpenSSL
RUN apt-get install -y openssl

# Update SSH
RUN update-ca-certificates

# Instale o OpenSSH Client
# RUN apt-get install -y openssh-client

# # Crie a chave SSH
# RUN ssh-keygen -t rsa -b 2048 -N "" -f /root/.ssh/id_rsa

# Usando Clean
RUN apt-get autoclean && \
    apt-get autoremove && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Adicionando certificados

# Clone o repositório do Google Test
RUN git clone https://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@github.com/google/googletest.git /googletest

# cria local de build
RUN mkdir -p /googletest/build

# mudo diretorio de trabalho
WORKDIR /googletest/build

# Execute o cmake e instale as bibliotecas
RUN cmake .. && make && make install

# Crio diretorio onde vai o código
RUN mkdir -p /code

WORKDIR /code
