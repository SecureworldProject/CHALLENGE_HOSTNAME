from math import log10, sqrt

import os
from pathlib import Path
import time
#para instalar el modulo easygui simplemente:
#pip3 install easygui
# o bien py -m pip install easygui
import easygui 
#import lock

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
    
    #obtenemos hostname
    hostname = socket.gethostname()

    #mecanismo lock out. no lo usamos porque no es necesario en este challenge (no es intrusivo)
    #lock.lockOUT("hostname")
    
    #ahora extraemos la parte del hostname comun a los PC corporativos
    lenstart=props_dict["hostname_len"]
    print ("your hostname=", hostname)
    cad= hostname[:lenstart]
    #print ("subkey is ", cad)
    
    key = bytes(cad,'utf-8')
    key_size = len(key)

    result =(key, key_size)
    print ("result:",result)
    return result



if __name__ == "__main__":
    
    midict={"hostname_len": 2} 
    init(midict)
    executeChallenge()

