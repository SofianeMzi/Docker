FROM centos_gcc AS compile_stage

WORKDIR /home

COPY pingpongR.c .

COPY pr.c .

RUN gcc pingpongR.c -o pingpongR && gcc pr.c -o pr

FROM centos:7.2.1511

WORKDIR /home 

COPY --from=compile_stage /home/pingpongR .

COPY --from=compile_stage /home/pr .

CMD ["bash"]
