FROM centos_gcc AS compile_stage

WORKDIR /home

COPY pingpong.c .

COPY p.c .

RUN gcc pingpong.c -o pingpong && gcc p.c -o p

FROM centos:7.2.1511

WORKDIR /home 

COPY --from=compile_stage /home/pingpong .

COPY --from=compile_stage /home/p .

CMD ["bash"]
