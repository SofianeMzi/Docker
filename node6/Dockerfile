FROM centos_gcc AS compile_stage

WORKDIR /home

COPY pingpongR.c .

RUN gcc pingpongR.c -o pingpongR

FROM centos:7.2.1511

WORKDIR /home 

COPY --from=compile_stage /home/pingpongR .

CMD ["bash"]
