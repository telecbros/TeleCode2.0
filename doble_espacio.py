#!/usr/bin/python3

Linea = input()

Linea = Linea.split(" ")

for palabra in Linea:
    if(palabra != ""):
        print(palabra + " ", end="")
