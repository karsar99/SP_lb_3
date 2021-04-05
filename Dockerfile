FROM amazonlinux
RUN yum install gcc-c++ -y
COPY . .
RUN g++ main.cpp -masm=intel -o main
CMD ./main

