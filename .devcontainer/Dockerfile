FROM ubuntu:latest

ENV TZ=Asia/Seoul LANG=ko_KR.UTF-8 LANGUAGE=ko_KR.UTF-8

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \
    locales tzdata build-essential gdb vim curl git wget \
    cmake make gcc g++ \
    && locale-gen ko_KR.UTF-8 && update-locale LANG=ko_KR.UTF-8

RUN useradd -m -s /bin/bash jungle && usermod -aG sudo jungle

USER jungle
WORKDIR /home/jungle