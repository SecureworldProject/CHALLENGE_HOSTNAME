# CHALLENGE_HOSTNAME
comprueba si el el usuario tiene un PC corporativo

an example of the configuration file for C version (to test in validator)
notice that we have use only 2 chars but depending on hostname polity you could use more chars. For example if all PC hostames begins with "NOKIA-$$$$$" then you can use 5 chars because all employeees share the same value for the first 5 chars of the hostname

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
```python
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
