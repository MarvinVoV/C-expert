#include <stdio.h>
#include <stdlib.h>

int main(void){
    float data[2]={10.0,20.3};
    float data_zz[2];
    struct {
	short count;
	long total;
	char *name;
    } it,zz;

    it.count=2;
    it.total=1000;
    it.name="louis";


    /* read and write, create if file isn't exist */ 
    FILE *f=fopen("foo","w+"); 
    if(f==NULL){
	fprintf(stderr,"create file failed\n");
	exit(1);
    }
    /* write two elements of data array to stdout */
    if(fwrite(data,sizeof(float),2,f)!=2){
	fprintf(stderr,"fwrite float error\n");
    }

    if(fwrite(&it,sizeof(it),1,f)!=1){
	fprintf(stderr,"fwrite struct error\n");
    }

    //read 
    rewind(f);
    if(fread(data_zz,sizeof(float),2,f)!=2){
       fprintf(stderr,"fread float error\n");
    }else{
	printf("%f %f\n",data_zz[0],data_zz[1]);
    }

    if(fread(&zz,sizeof(zz),1,f)!=1){
	fprintf(stderr,"fread struct error\n");
    }else{
	printf("%d %ld %s\n",zz.count,zz.total,zz.name);
    }
    
    
    fclose(f);
    exit(0);

}
