from math import log10, sqrt
import os
from pathlib import Path
import time
import socket


# Variables globales
# ------------------
props_dict = {} 
DEBUG_MODE = True



def init(props):
    global props_dict
    print("CHALLENGE_HOSTNAME --> Enter in init")
    
    #props es un diccionario
    props_dict = props

    return 0


def executeChallenge():
    print("CHALLENGE_HOSTNAME --> Starting execute")
        
    # Obtenemos hostname
    hostname = socket.gethostname()

    # Ahora extraemos la parte del hostname comun a los PC corporativos
    lenstart = props_dict["hostname_len"]
    print("CHALLENGE_HOSTNAME --> Hostname=", hostname)
    cad = hostname[:lenstart]
    #print("CHALLENGE_HOSTNAME --> Subkey is ", cad)
    
    key = bytes(cad,'utf-8')
    key_size = len(key)

    result = (key, key_size)
    print("CHALLENGE_HOSTNAME --> result:", result)
    return result



if __name__ == "__main__":
    midict = {"hostname_len": 2} 
    init(midict)
    executeChallenge()

