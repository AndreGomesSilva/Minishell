# Escolha uma imagem base que tenha o cmake, g++ e make instalados
FROM ubuntu:latest

# Instale as dependências necessárias
RUN apt-get update 

RUN apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
	make \
	g++ \
    git \
	tar \
	gcc-10 \
	curl \
	software-properties-common \
	libreadline-dev \
	zsh \
	curl \
	wget \
	vim \
	openssh-server

RUN apt-get install icu-devtools -y

RUN apt-get install -y openssl

RUN update-ca-certificates

# Clone o GoogleTest do repositório oficial
RUN git clone https://github.com/google/googletest.git

# Zsh
RUN git clone https://github.com/robbyrussell/oh-my-zsh.git ~/.oh-my-zsh
RUN chsh -s $(which zsh)
RUN git clone https://github.com/denysdovhan/spaceship-prompt.git "$HOME/.oh-my-zsh/themes/spaceship-prompt" --depth=1
RUN ln -s "$HOME/.oh-my-zsh/themes/spaceship-prompt/spaceship.zsh-theme" "$HOME/.oh-my-zsh/themes/spaceship.zsh-theme"
COPY .zshrc /root/.zshrc
SHELL ["/bin/zsh", "-c"]

# Plugins Zsh
RUN git clone https://github.com/zsh-users/zsh-autosuggestions ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-autosuggestions
RUN git clone https://github.com/zsh-users/zsh-syntax-highlighting.git ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-syntax-highlighting

#clang e clangd
RUN wget https://apt.llvm.org/llvm.sh
RUN chmod +x llvm.sh
RUN ./llvm.sh 17
RUN update-alternatives --install /usr/bin/clangd clangd /usr/bin/clangd-17 100
RUN update-alternatives --install /usr/bin/clang clang /usr/bin/clang-17 100

# Crie o diretório de build do GoogleTest e compile-o
RUN cd googletest && mkdir build && cd build && cmake .. && make && make install

# Configure o diretório de trabalho para o diretório do seu projeto
RUN mkdir /minishell

WORKDIR /minishell

RUN git config pull.rebase true
