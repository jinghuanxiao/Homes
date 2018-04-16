#!/usr/bin/env python

from  socket import socket, AF_INET,SOCK_STREAM
import sys
class LazyConnect(object):
	def __init__(self,address,family= AF_INET,type= SOCK_STREAM):
		self.address = address
		self.family  = family
		self.type    = type
		self.sock    = None
	def __enter__(self):
		if self.sock is not None:
			raise RuntimeError("Aready connect")
		self.sock = socket(self.family,self.type)
		self.sock.connect(self.address)
		pass
	def __exit__(self):
		self.sock.close()
		self.sock = None

 
if __name__ == "__main__":
	
	client =LazyConnect(("192.168.246.130",10000))
'''	with client as Client:
		
		pass
'''
