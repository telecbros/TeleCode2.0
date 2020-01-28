#!/usr/bin/python3

numero_casos = int(input())

for i in range(numero_casos):
	clave = []
	mensaje = []
	longitud_bytes = int(input())
	cifrado1 = input().split(" ")
	cifrado2 = input().split(" ")
	cifrado3 = input().split(" ")
	for i in range(longitud_bytes):
		dato = int(cifrado2[i])^int(cifrado3[i])
		clave.append(dato)
	for i in range(longitud_bytes):
		dato = int(cifrado1[i])^int(clave[i])
		print(chr(dato), end="")
	print()
