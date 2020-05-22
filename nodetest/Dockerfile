FROM centos:7.2.1511 AS compile_stage
     
COPY pingpongR.c /home/
   
WORKDIR /home

RUN yum -y install gcc && gcc pingpongR.c -o pingpongR

FROM centos:7.2.1511

WORKDIR /home 

COPY --from=compile_stage /home/pingpongR .

CMD ["bash"]
