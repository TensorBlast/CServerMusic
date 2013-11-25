#include <libxml/tree.h>
#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/xmlreader.h>

void processXMLNode(xmlTextReaderPtr reader);
void parseKey(xmlDoc* doc, xmlNode* curr);
int main(int argc, char ** argv)
{
	xmlDoc * doc=NULL;
	xmlNode * r=NULL;
	xmlNode * curr=NULL;
	xmlNode * child=NULL;

	if(argc!=3)
		return -1;

	if(strcmp(argv[2],"0")==0){
		if((doc=xmlParseFile(argv[1]))==NULL)
			printf("Couldn't parse %s\n",argv[1]);
		else{
			r=xmlDocGetRootElement(doc);
			printXML(r);
			
		}
	}
	else
	{
		// xmlTextReaderPtr reader=xmlReaderForFile(argv[1],NULL,0);
		// if (reader!=NULL)		
		// {
		// 	/* code */
		// 	int res=xmlTextReaderRead(reader);
		// 	while(res==1)
		// 	{
		// 		processXMLNode(reader);
		// 		res=xmlTextReaderRead(reader);
		// 	}
		// 	xmlFreeTextReader(reader);
		// 	if(res!=0)
		// 		fprintf(stderr, "%s: Failed to parse\n", argv[1]);
		// }
		if((doc=xmlParseFile(argv[1]))==NULL)
			printf("Couldn't parse %s\n",argv[1]);
		else{
			r=xmlDocGetRootElement(doc);
			r=r->children;
			while(r!=NULL)
			{
				parseKey(doc,r);
				r=r->children;
			}
			
		}
	}
	return 0;
}
void parseKey(xmlDoc* doc, xmlNode* curr)
{
	printf("%s\n", "This is fucked up");
	while(curr!=NULL){
		if(!xmlStrcmp(curr->name,(const xmlChar *)"key"))
		{
			xmlChar * cmp;
			cmp=xmlNodeListGetString(doc,curr,1);
			//if((!xmlStrcmp(cmp,(const xmlChar*)"Name")))
			{
				curr=curr->next;
				cmp=xmlNodeListGetString(doc,curr,1);
				printf("NAME: %s\n",cmp);
				xmlFree(cmp);
			}
			//else if((!xmlStrcmp(cmp,(const xmlChar*)"Play Count")))
			{
				curr=curr->next;
				cmp=xmlNodeListGetString(doc,curr,1);
				printf("Play Count: %s\n",cmp);
				xmlFree(cmp);
			}
			//else if((!xmlStrcmp(cmp,(const xmlChar*)"Size")))
			{
				curr=curr->next;
				cmp=xmlNodeListGetString(doc,curr,1);
				printf("Size: %s bytes\n",cmp);
				xmlFree(cmp);			
			}
		}
		curr=curr->next;

	}

}
int printXML(xmlNode * a)
{
	xmlNode * r=a;
	xmlNode * curr;
	curr=r;
	for(curr=r;curr;curr=curr->next)
	{
		if(curr->type == XML_ELEMENT_NODE)
		{
			printf("Node name: %s\n",curr->name);
			printXML(curr->children);
		}
	}
	return 0;
}
void processXMLNode(xmlTextReaderPtr reader)
{
	const xmlChar * name, *value;
	xmlTextReaderPtr tmp=reader;

	int t;
	name=xmlTextReaderConstName(reader);
	if(name == NULL)
		name=BAD_CAST "--";

	value= xmlTextReaderConstValue(reader);

	printf("%s\n", "In processXMLNode\n");
	printf("NAME: %s\n", name);
	printf("VALUE: %s\n", value);
	fflush(stdout);
	// if(strcmp((char *)value, "Name")==0)
	// {
	// 	t=xmlTextReaderRead(tmp);
	// 	if(t)
	// 	printf("Song Name: %s\n",xmlTextReaderConstValue(tmp));
	// }
	// if(strcmp((char *)value, "Size")==0)
	// {
	// 	t=xmlTextReaderRead(tmp);
	// 	if(t)
	// 	printf("Size: %s\n", xmlTextReaderConstValue(tmp));
	// }
	// if(strcmp((char *)value,"Play Count")==0)
	// {
	// 	t=xmlTextReaderRead(tmp);
	// 	if(t)
	// 	printf("Play Count: %s\n", xmlTextReaderConstValue(tmp));
	// }
}