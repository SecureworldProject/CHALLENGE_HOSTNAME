from math import log10, sqrt

import os
from pathlib import Path
import time
#para instalar el modulo easygui simplemente:
#pip3 install easygui
# o bien py -m pip install easygui
import easygui 
import lock

import socket
import fnmatch
# variables globales
# ------------------
props_dict={} 
DEBUG_MODE=True

def init(props):
    global props_dict
    print("Python: Enter in init")
    
    #props es un diccionario
    props_dict= props

    return 0


def executeChallenge():
    print("Starting execute")
    
    
    #mecanismo de lock BEGIN, para garantizar una sola interaccion con user a la vez
    #-----------------------
    #no lo necesito porque no es intrusivo
    #lock.lockIN("hostname")
    
    #pedimos password
    hostname = socket.gethostname()

    #mecanismo lock out
    #lock.lockOUT("hostname")
    
    #ahora comparamos con la correcta
    #hostname_start=props_dict["hostname_start"]
    lenstart=props_dict["hostname_len"]
    #if fnmatch.fnmatch(hostname,hostname_start+"*"):
    #    print ("el pc es corporativo. Hostname=", hostname)
    print ("your hostname=", hostname)
    cad= hostname[:lenstart]
    print ("subkey is ", cad)
    
    
    
    key = bytes(cad,'utf-8')
    key_size = len(key)

    result =(key, key_size)
    print ("result:",result)
    return result



    


if __name__ == "__main__":
    #mode "parental" o "normal"
    midict={"hostname_len": 2} #"clave": "clavesecreta", "mode":"parental"}
    init(midict)
    executeChallenge()

