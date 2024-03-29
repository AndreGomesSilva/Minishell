# Escolha uma imagem base que tenha o cmake, g++ e make instalados
FROM ubuntu:latest

# Evite prompts do apt-get
ARG DEBIAN_FRONTEND=noninteractive

# Instale as dependências necessárias
RUN apt-get update -y

RUN apt-get install -y \
	clang-format \
	software-properties-common \
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
	openssh-server \
	icu-devtools \
	openssl

# Instala tmux e copia o arquivo de configuração do tmux para o container
RUN apt-get install -y \
	tmux
COPY .tmux.conf /root/.tmux.conf

RUN apt-get update && \ 
	apt-get install -y valgrind

# Atualizo certificado para o SSH funcionar
RUN update-ca-certificates

# Instale o Python 3.8 e formatter automatico para 42 (42 C-Format)
RUN add-apt-repository ppa:deadsnakes/ppa
RUN apt-get update -y
RUN apt-get install -y \
	python3.8 \
	python3-pip
RUN pip3 install c_formatter_42
RUN pip3 install norminette==3.3.51

RUN apt-get clean

# Clone o GoogleTest do repositório oficial
RUN git clone https://github.com/google/googletest.git

# Zsh
RUN git clone https://github.com/robbyrussell/oh-my-zsh.git ~/.oh-my-zsh
RUN chsh -s $(which zsh)
RUN git clone https://github.com/denysdovhan/spaceship-prompt.git "$HOME/.oh-my-zsh/themes/spaceship-prompt" --depth=1
RUN ln -s "$HOME/.oh-my-zsh/themes/spaceship-prompt/spaceship.zsh-theme" "$HOME/.oh-my-zsh/themes/spaceship.zsh-theme"
COPY .zshrc /root/.zshrc
# SHELL ["/bin/zsh", "-c"]

# Plugins Zsh
RUN git clone https://github.com/zsh-users/zsh-autosuggestions ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-autosuggestions
RUN git clone https://github.com/zsh-users/zsh-syntax-highlighting.git ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-syntax-highlighting

# Clang e clangd
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