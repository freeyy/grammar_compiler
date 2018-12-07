#include <stdlib.h>
#include <stdio.h>
#include "ofa_consts.h"
#include "LinuxAsrFix.h"

//INPUT: input.jsgf  &&  recognize.vocab	

char* getFileContent(const char *filename)
{
    char* text;
    FILE *pf = fopen(filename,"r");
    fseek(pf,0,SEEK_END);
    long lSize = ftell(pf);
    text=(char*)malloc(lSize+1);
    rewind(pf);
    fread(text,sizeof(char),lSize,pf);
    text[lSize] = '\0';
    return text;
}


int main()
{
	char* clgdir= "clg/jsgf_clg.dat";
	char* userdir = "input/input.vocab";		
	char* modeldir = "models/";
	char* jsgfdir = "input/input.jsgf";
	char* outdir = "output/output.dat";
	char* jsgf = getFileContent(jsgfdir);
	char* userdata = getFileContent(userdir);
	
	long handle = UalOFAInitializeUserDataCompiler(modeldir);
	UalOFASetOptionInt(ASR_LOG_ID, 1);

	if (handle == 0) {
		printf("handle create failed\n");
	}

	int load_ret = UalOFALoadCompiledJsgf(handle, clgdir);
	printf("load_ret = %d\n", load_ret);	
	

	int cpl_ret = UalOFACompileUserData(handle, jsgf, userdata, outdir);
	printf("result = %d\n", cpl_ret);

	if (cpl_ret != 0 && load_ret != 0) {
		printf("build failed\n");
	} else {
		printf("build succeed\n");
	}

	UalOFAReleaseUserDataCompiler(handle);
	free(jsgf);
	free(userdata);
	return 0;
}


