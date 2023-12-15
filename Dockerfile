# Escolha uma imagem base que tenha o cmake, g++ e make instalados
FROM ubuntu:latest

# Instale as dependências necessárias
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
	software-properties-common \
	libreadline-dev

RUN apt-get install -y openssl

RUN update-ca-certificates

# Clone o GoogleTest do repositório oficial
RUN git clone https://github.com/google/googletest.git

# Crie o diretório de build do GoogleTest e compile-o
RUN cd googletest && mkdir build && cd build && cmake .. && make && make install

# Configure o diretório de trabalho para o diretório do seu projeto
RUN mkdir /minishell

WORKDIR /minishell