# CHALLENGE_HOSTNAME
comprueba si el el usuario tiene un PC corporativo

the configuration file for C version (to test in validator)

```json
{
"FileName": "hostname.dll",
"Description": "challenge de hostname de organizacion",
"Props": {
  "validity_time": 3600,
  "refresh_time": 10,
  "hostname_len": 2
},
"Requirements": "none" 
}
```

the configuration file for python version
```
{
"FileName": "challenge_loader_python.dll",
"Description": "challenge de hostname de organizacion",
"Props": {
  "module_python": "hostname",
  "validity_time": 3600,
  "refresh_time": 10,
  "hostname_len": 2
},
"Requirements": "none" 
}
```
