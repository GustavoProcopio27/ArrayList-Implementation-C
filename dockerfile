FROM gcc:latest AS base

WORKDIR /app 

COPY . .

RUN gcc arraylist_demo.c arraylist.c -o demo

FROM debian:stable

WORKDIR /app 

COPY --from=base /app/demo .

CMD ["./demo"]