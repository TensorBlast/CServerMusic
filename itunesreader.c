#include <stdio.h>
#include <stdlib.h>
#define BUFSIZE 501
#define KEY "Key"
#define NAME "<key>Name</key>"
#define SIZE "Size"
#define PLAY_COUNT "<key>Play Count</key>"
#define CLOSE_DICT "</dict>"
#define INTEGER "integer"
#define KIND "Kind"
#define MP3 "MPEG audio file"

int parse(char * fileName,char ** s,char ** p, int *n);
int main(int argc, char **argv)
{
	char ** songList=(char **)malloc(10000);
    char ** playcountList = (char **)malloc(10000);
	int numSongs=0;
	printf("%s\n", argv[1]);
	parse(argv[1],songList,playcountList,&numSongs);
	int *plist=(int *)malloc(numSongs*sizeof(int));
	int *map=(int * )malloc(sizeof(int)*numSongs);
	for(int j=0;j<numSongs;j++) {
		//printf("Song : %s || Playcount : %s\n", songList[j], playcountList[j]);
		plist[j]=atoi(playcountList[j]);
    }
    quickSort(plist,numSongs,&map);
    for(int f=0;f<numSongs;f++)
    {
    	printf("Song : %s || Playcount : %s\n", songList[f], plist[map[f]]);

    }
    free(songList);
    free(playcountList);
    free(plist);
    free(map);
	return 0;
}

int parse(char * fileName,char ** songs,char ** playcounts,int *number)
{
	printf("%s\n", "In Parse");
	/* First read file contents into memory */
	FILE * xml=fopen(fileName,"r+");
	int xmlLength=1000;
	int readLength=0;
	char * buffer=(char *)calloc(1, BUFSIZE);
	char * xmlContent=(char *)calloc(1, xmlLength);
	if(buffer==NULL || xmlContent==NULL)
	{
		printf("Insufficient memory to read XML!\n");
		return -1;
	}
	int n=-1;
	while((n=fread(buffer,1, BUFSIZE, xml))>0)
	{
		printf("%d\n", n);
		if(readLength+n > xmlLength)
		{
			xmlLength*=2;
			xmlContent=(char *)realloc(xmlContent,xmlLength);
		}
		memcpy(xmlContent+readLength,buffer,n);
		readLength+=n;
		memset(buffer,0,BUFSIZE);
	}
	xmlContent[readLength]='\0';
	printf("%s\n", xmlContent);
	/* Now parse file contents which are in xmlContents */

	char * xmlPtr = xmlContent;
	while(*xmlPtr != '\0')
	{
		if(strstr(xmlPtr, NAME) == NULL) {
            break;
        } else {
            xmlPtr = strstr(xmlPtr, NAME);
            
        }
		if(strstr(xmlPtr,"string") == NULL) {
            break;
        } else {
            xmlPtr = strstr(xmlPtr,"string");
            
        }
        
        // CHECK FOR MEDIA KIND; BREAK IF NOT MP3
        
        char * closedict = strstr(xmlPtr, CLOSE_DICT);
        int j = closedict - xmlPtr;
        char * tempstr = malloc(j);
        memcpy(tempstr,xmlPtr,j);
        
        // if(strstr(tempstr,MP3) == NULL) {
        //     free(tempstr);
        //     continue;
        // }
        
        // ADD SONG NAME TO SONG LIST
        
		xmlPtr+=7;
		int i=0;
		while(xmlPtr[i]!='<')
			i++;
		i+=1;
		*(songs)=(char *)malloc(i);
		memcpy(*songs,xmlPtr,i-1);
		(*songs)[i-1]='\0';
		*number+=1;
		//printf("%s", *songs);
		songs++;
        
        // CHECK FOR PLAY COUNT AND ADD TO PLAY COUNT LIST
        
        char * zeroPlays = "0\0";
        
        if(strstr(tempstr,PLAY_COUNT) == NULL) {
            *(playcounts) = (char*)malloc(sizeof(char)*2);
            memcpy(*playcounts,zeroPlays,sizeof(char)*2);
            //printf(" || played: %s\n", *playcounts);
            playcounts++;
        } else {
            xmlPtr = strstr(xmlPtr,PLAY_COUNT);
            xmlPtr = strstr(xmlPtr,INTEGER);
            xmlPtr+=8;
            int k=0;
            while(xmlPtr[k]!='<')
                k++;
            k+=1;
            *(playcounts)=(char *)malloc(k);
            memcpy(*playcounts,xmlPtr,k-1);
            (*playcounts)[k-1]='\0';
            //printf(" || played: %s\n", *playcounts);
            playcounts++;
            
        }
        
        free(tempstr);

	}
	*songs='\0';
    *playcounts='\0';
    
	return 0;
}