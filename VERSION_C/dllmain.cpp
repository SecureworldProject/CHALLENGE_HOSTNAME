// dllmain.cpp : Defines the entry point for the DLL application.
/*
This is the expected json associated to the challenge:
{
	"FileName": "simple_challenge.dll",
	"Description": "This is a simple challenge that does nothing.",
	"Props": {
		"validity_time": 3600,
		"refresh_time": 3000,
		"param1": "texto",
		"param2": 3
	},
	"Requirements": "none"
}
*/


/////  FILE INCLUDES  /////
//para que no de error hay que poner 
//project->properties->linker->input->additional dependencies = ws2_32.lib
#include <winsock2.h>  //necesitamos la funcion gethostname

#include "pch.h"
#include "context_challenge.h"




/////  GLOBAL VARIABLES  /////
//parametros de lanzamiento
int hostname_len = 0;





/////  FUNCTION DEFINITIONS  /////

void getChallengeProperties();




/////  FUNCTION IMPLEMENTATIONS  /////

int init(struct ChallengeEquivalenceGroup* group_param, struct Challenge* challenge_param) {

	int result = 0;

	// It is mandatory to fill these global variables
	group = group_param;
	challenge = challenge_param;
	if (group == NULL || challenge == NULL) {
		printf("\033[33mGroup or challenge are NULL \n \033[0m");
		return -1;
	}
	printf("\033[33mInitializing (%ws) \n \033[0m", challenge->file_name);

	// Process challenge parameters
	getChallengeProperties();

	// It is optional to execute the challenge here
	result = executeChallenge();

	// It is optional to launch a thread to refresh the key here, but it is recommended
	if (result == 0) {
		launchPeriodicExecution();
	}

	return result;
}

int executeChallenge() {
	printf("\033[33m %llu: Executing challenge (%ws)\n \033[0m", time(NULL), challenge->file_name);

	// Nullity check
	if (group == NULL || challenge == NULL || hostname_len == NULL)
		return -1;


	// Calculate new key (size, data and expire date)
	int new_size = hostname_len * sizeof(char);

	byte* new_key_data = (byte*)malloc(hostname_len * sizeof(char));
	if (new_key_data == NULL)
		return -1;

	//obtenemos el hostname
	//char hostbuffer[256];
	char *hostbuffer = (char*)malloc(256);
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		/* Tell the user that we could not find a usable */
		/* Winsock DLL.  
		*/
		printf("WSAStartup failed with error: %d\n", err);
		return -1;
	}
	printf("WinSock initialized\n");  
	int ret=gethostname(hostbuffer, 256);
	if (ret == -1) {
		//perror("error in gethostname");
		printf("ERROR at gethostname() %s \n", hostbuffer);
		//exit(EXIT_FAILURE);
		return -1;
	}
	printf("Hostname:    %s\n", hostbuffer);

	//ahora pegamos el trozo que necesitamos
	if (0 != memcpy_s(new_key_data , new_size , hostbuffer, hostname_len) ){
		free(new_key_data);
		return -1;
	}


	time_t new_expires = time(NULL) + validity_time;


	// Update KeyData inside critical section
	EnterCriticalSection(&(group->subkey->critical_section));
	if ((group->subkey)->data != NULL) {
		free((group->subkey)->data);
	}
	group->subkey->data = new_key_data;
	group->subkey->expires = new_expires;
	group->subkey->size = new_size;
	LeaveCriticalSection(&(group->subkey->critical_section));

	return 0;	// Always 0 means OK.
}


void getChallengeProperties() {
	printf("\033[33m Getting challenge parameters\n \033[0m");
	json_value* value = challenge->properties;
	for (int i = 0; i < value->u.object.length; i++) {
		if (strcmp(value->u.object.values[i].name, "validity_time") == 0) {
			validity_time = (int)(value->u.object.values[i].value->u.integer);
		}
		else if (strcmp(value->u.object.values[i].name, "refresh_time") == 0) {
			refresh_time = (int)(value->u.object.values[i].value->u.integer);
		}
		/*
		else if (strcmp(value->u.object.values[i].name, "param1") == 0) {
			param1 = (char*)malloc((1 + value->u.object.values[i].value->u.string.length) * sizeof(char));
			if (param1 != NULL) {
				strcpy_s(param1, (1 + value->u.object.values[i].value->u.string.length) * sizeof(char), value->u.object.values[i].value->u.string.ptr);
			}
		}*/
		else if (strcmp(value->u.object.values[i].name, "hostname_len") == 0) {
			hostname_len = (int)(value->u.object.values[i].value->u.integer);
		}
		else fprintf(stderr, "\033[33m WARNING: the field '%s' included in the json configuration file is not registered and will not be processed.\n \033[0m", value->u.object.values[i].name);
	}
	printf("\033[33m Challenge properties: \n  validity_time = %d \n  refresh_time = %d \n   hostname_len = %d \n \033[0m",
		validity_time, refresh_time, hostname_len);
}


BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}


