FROM centos_gcc AS compile_stage

WORKDIR /home

COPY pingpongR.c thread.c thread_nombre_premier.c ./

RUN gcc pingpongR.c -o pingpongR && gcc -Wall -fopenmp thread_nombre_premier.c -o tnp

FROM centos:7.2.1511

WORKDIR /home 

COPY --from=compile_stage /home/pingpongR .

COPY --from=compile_stage /home/tnp .

CMD ["bash"]
