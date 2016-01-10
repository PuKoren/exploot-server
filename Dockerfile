FROM debian:jessie

RUN apt-get update && apt-get install -y \
  cmake \
  g++ \
  libbullet-dev \
  libenet-dev \
  libprotobuf-dev \
  libmysqlclient-dev \
  libmysqlcppconn-dev \
  protobuf-compiler

COPY . /tmp

WORKDIR /tmp/submodules/exploot-protobuf
RUN sh build.sh

WORKDIR /tmp
RUN mkdir -p build && cd build && cmake .. && make
CMD build/exploot-server