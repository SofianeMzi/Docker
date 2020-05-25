FROM centos_gcc AS compile_stage

WORKDIR /home

COPY pingpong.c .

RUN gcc pingpong.c -o pingpong

FROM centos:7.2.1511

WORKDIR /home 

COPY --from=compile_stage /home/pingpong .

CMD ["bash"]
