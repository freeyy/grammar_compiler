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


int main(int argc, char** argv)
{
	if (argc != 4){
		printf("SAMPLE: ./run <input.jsgf> <input.vocab> <output.dat>\n");
		return -1;
	}
	
	int result = 0;
	char* clgdir= "clg/jsgf_clg.dat";
	char* modeldir = "models/";
	//char* userdir = "input/input.vocab";		
	//char* jsgfdir = "input/input.jsgf";
	//char* outdir = "output/output.dat";
	char* jsgfdir = argv[1];
	char* userdir = argv[2];		
	char* outdir = argv[3];
	char* jsgf = getFileContent(jsgfdir);
	char* userdata = getFileContent(userdir);
	
	long handle = UalOFAInitializeUserDataCompiler(modeldir);
	UalOFASetOptionInt(ASR_LOG_ID, 1);

	if (handle == 0) {
		printf("FAILURE: handle create failed!\n");
		result = 1;
	}

	int load_ret = UalOFALoadCompiledJsgf(handle, clgdir);
	//printf("load_ret = %d\n", load_ret);	
	int cpl_ret = UalOFACompileUserData(handle, jsgf, userdata, outdir);
	//printf("result = %d\n", cpl_ret);

	if (cpl_ret != 0 || load_ret != 0) {
		printf("FAILURE: config error!\n");
		result = 1;
	} 

	UalOFAReleaseUserDataCompiler(handle);
	free(jsgf);
	free(userdata);
	
	if (result == 0){
		printf("result: SUCCESS\n");
		return 0;
	}
	else{
		printf("result: FAILED\n");
		return -1;
	}
}


