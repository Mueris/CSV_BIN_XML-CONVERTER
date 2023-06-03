#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlschemastypes.h>

struct _customer{//a struct has been created to keep the informations
	char name[20];//name of the customer
	char surname[30];//surname of the customer
	char gender[2];//gender of the customer M|F
	char occupancy[30];//occupancy of the customer
	char levelOfEducation[7];//levelOfEducation of the customer
	char email[30];//email of the customer
	char bankAccountNumber[13];//bankAccountNumber of the customer
	char iban[32];//iban of the customer
	char accountType[15];//accountType of the customer
	char currencyUnit[5];
	char totalBalanceAvailable[20];
	char availableForLoan[5];
};
char *strsep(char **sp, const char *sep);
void csvToBinary(char* inputFile, char* outputfile);
void binaryToXML(char* inputFile, char* outputfile);
void validate(char* inputFile, char* outputfile);
int endianConverter(int num);

int main(int argc, char *argv[])
{
	if(argc < 4){//protection 
        printf("Please check your format ---> myConverter <input_file> <output_file> <type>");
        exit(1);
    }
    char* inputFile = argv[1];//first input
    char* outputFile = argv[2];//second input
    int type = atoi(argv[3]);
    char* inpChecker = strrchr(inputFile, '.');//takes after the point
    char* outChecker = strrchr(outputFile, '.');
    int inpresult, outresult;
    switch (type)//switch case for terminal run
    {
    case 1:
        inpresult = strcmp(".csv", inpChecker);//comperission of strings of first file format
        outresult = strcmp(".dat", outChecker);//comperission of strings of second file format
        if(inpresult == 0 && outresult == 0){
            csvToBinary(inputFile, outputFile);
        }
        else{
            printf("Input file must be in .csv and output file must be in .dat form\n");
            exit(1);
        }
        break;
    case 2:
        inpresult = strcmp(".dat", inpChecker);
        outresult = strcmp(".xml", outChecker);
        if(inpresult == 0 && outresult == 0){
            binaryToXML(inputFile, outputFile);
        }
        else{
            printf("Input file must be in .dat and output file must be in .xml form\n");
            exit(1);
        }
        break;
    case 3:
        inpresult = strcmp(".xml", inpChecker);
        outresult = strcmp(".xsd", outChecker);
        if(inpresult == 0 && outresult == 0){
            validate(inputFile, outputFile);
        }
        else{
            printf("Input file must be in .xml and output file must be in .xsd form\n");
            exit(1);
        }
    default:
        printf("Please check your format ---> myConverter <input_file> <output_file> <type>\n");
        break;
    }

    return(0);
}
char *strsep(char **sp, const char *sep){
    char *p, *s;
    if (sp == NULL || *sp == NULL || **sp == '\0') return NULL;
    s = *sp;
    p = s + strcspn(s, sep);
    if (*p != '\0') *p++ = '\0';
    *sp = p;
    return s;
}

void csvToBinary(char* inputFile, char* outputfile){//converts csv file to binary file
	struct _customer rItem;
	FILE *fp;//file reader
	FILE *bfp;//file writer
	fp = fopen(inputFile, "r");//initiallize the reader
	bfp = fopen(outputfile, "w");//initiallize the writer
	char line[1024];
	char *token, *p;
	if(fp == NULL || bfp == NULL)//if files are sucessfully opened continue
	{
		printf("Error finding file");
		exit(1);
    }
	fgets(line, 1024, fp);//reads the first row
	while(fgets(line, 1024, fp)){//loop to read all file
		p = line;
		token = strsep(&p, ",\n");//reads till the coma
		strcpy(rItem.name, token);//writes the token to the name of the struct
		token = strsep(&p, ",\n");//reads till the coma
		strcpy(rItem.surname, token);//writes the token to the surname of the struct
		token = strsep(&p, ",\n");//reads till the coma
		strcpy(rItem.gender, token);//writes the token to the gender of the struct
		token = strsep(&p, ",\n");//reads till the coma
		strcpy(rItem.occupancy, token);//writes the token to the occupancy of the struct
		token = strsep(&p, ",\n");//reads till the coma
		strcpy(rItem.levelOfEducation, token);//writes the token to the levelOfEducation of the struct
		token = strsep(&p, ",\n");//reads till the coma
		strcpy(rItem.email, token);//writes the token to the email of the struct
		token = strsep(&p, ",\n");//reads till the coma
		strcpy(rItem.bankAccountNumber, token);//writes the token to the bankAccountNumber of the struct
		token = strsep(&p, ",\n");//reads till the coma
		strcpy(rItem.iban, token);//writes the token to the iban of the struct
		token = strsep(&p, ",\n");//reads till the coma
		strcpy(rItem.accountType, token);//writes the token to the accountType of the struct
		token = strsep(&p, ",\n");//reads till the coma
		strcpy(rItem.currencyUnit,token);//writes the token to the currencyUnit of the struct
		token = strsep(&p, ",\n");//reads till the coma
		strcpy(rItem.totalBalanceAvailable, token);//writes totalBalanceAvailable the token to the totalBalanceAvailable of the struct
		token = strsep(&p, ",\n");//reads till the coma
		strcpy(rItem.availableForLoan, token);//writes the token to the availableForLoan of the struct
		fwrite(&rItem.name, sizeof(char), 20, bfp);//writes data to binary file
		fwrite(&rItem.surname, sizeof(char), 30, bfp);//writes data to binary file
		fwrite(&rItem.gender, sizeof(char), 2, bfp);//writes data to binary file
		fwrite(&rItem.occupancy, sizeof(char), 30, bfp);//writes data to binary file
		fwrite(&rItem.levelOfEducation, sizeof(char), 7, bfp);//writes data to binary file
		fwrite(&rItem.email, sizeof(char), 30, bfp);//writes data to binary file
		fwrite(&rItem.bankAccountNumber, sizeof(char), 13, bfp);//writes data to binary file
		fwrite(&rItem.iban, sizeof(char), 32, bfp);//writes data to binary file
		fwrite(&rItem.accountType, sizeof(char), 15, bfp);//writes data to binary file
		fwrite(&rItem.currencyUnit, sizeof(char), 5, bfp);//writes data to binary file
		fwrite(&rItem.totalBalanceAvailable, sizeof(char), 20, bfp);//writes data to binary file
		fwrite(&rItem.availableForLoan, sizeof(char), 5, bfp);//writes data to binary file
		printf("name: %s surname: %s gender: %s occuppancy: %s education: %s email: %s accountNum: %s iban: %s accType: %s currency: %s balanceAvalbl: %s forLoan: %s\n" , rItem.name, 
		rItem.surname, rItem.gender, rItem.occupancy, rItem.levelOfEducation, rItem.email, rItem.bankAccountNumber, rItem.iban, rItem.accountType, rItem.currencyUnit, rItem.totalBalanceAvailable, rItem.availableForLoan);

	}
	fclose(fp);
	fclose(bfp);//closing the files
}

void binaryToXML(char* inputFile, char* outputfile){//reads binary file and writes the xml file
	struct _customer rItem;
    FILE *bfp;
    bfp = fopen(inputFile, "r");//initilize the file to read
	xmlDocPtr doc = NULL;
	xmlNodePtr root_node = NULL, customerInf_node = NULL, accountInf_node = NULL, node = NULL;
	doc = xmlNewDoc(BAD_CAST "1.0");
	char fOut[25];
	strcpy(fOut,outputfile);
	char* root = "records";//makes the root name of the output file
	root_node = xmlNewNode(NULL, BAD_CAST root);
	xmlDocSetRootElement(doc, root_node);
	char buff[250];//number of the rows
	int rowIndexer=1;
	while(!feof(bfp)) {//reads the binary file line by line
        fread(&rItem, sizeof(struct _customer), 1, bfp);
		node = xmlNewChild(root_node, NULL, BAD_CAST "row", NULL);//creates node as row
		sprintf(buff, "%d", rowIndexer);//counts the id of the row
		xmlNewProp(node, BAD_CAST "id", BAD_CAST buff);
		customerInf_node = xmlNewChild(node, NULL, BAD_CAST "customer_info", NULL);//links customer info to row
		//creates node and puts the values of proper nodes of subnodes of customer
		xmlNewChild(customerInf_node, NULL, "name", BAD_CAST rItem.name );
		xmlNewChild(customerInf_node, NULL, "surname", BAD_CAST rItem.surname );
		xmlNewChild(customerInf_node, NULL, "gender", BAD_CAST rItem.gender );
		xmlNewChild(customerInf_node, NULL, "occupancy", BAD_CAST rItem.occupancy);
		xmlNewChild(customerInf_node, NULL, "level_of_education", BAD_CAST rItem.levelOfEducation );
		xmlNewChild(customerInf_node, NULL, "email", BAD_CAST rItem.email );
		accountInf_node = xmlNewChild(node, NULL, BAD_CAST "bank_account_info", NULL);//connects account info to row
		//creates node and puts the values of proper nodes of subnodes of customer
		xmlNewChild(accountInf_node, NULL, "bank_account_number", BAD_CAST rItem.bankAccountNumber );
		xmlNewChild(accountInf_node, NULL, "IBAN", BAD_CAST rItem.iban );
		xmlNewChild(accountInf_node, NULL, "account_type", BAD_CAST rItem.accountType );
		node = xmlNewChild(accountInf_node, NULL, "total_balance_available", BAD_CAST rItem.totalBalanceAvailable );
		xmlNewProp(node, BAD_CAST "currency_unit", BAD_CAST rItem.currencyUnit);
		int num = atoi(rItem.totalBalanceAvailable);//casts to integer value
		char bigEnd_Version[100];//holds the total balance as string for the big endien
		sprintf(bigEnd_Version, "%d", endianConverter(num));//converts big endian version to string
		xmlNewProp(node, BAD_CAST "bigEnd_Version", BAD_CAST bigEnd_Version);
		xmlNewChild(accountInf_node, NULL, "available_for_loan", BAD_CAST rItem.availableForLoan );
        printf("name: %s surname: %s gender: %s occuppacy: %s education: %s email: %s accountNum: %s iban: %s accType: %s currency: %s balanceAvalbl: %s forLoan: %s\n" , rItem.name, 
		rItem.surname, rItem.gender, rItem.occupancy, rItem.levelOfEducation, rItem.email, rItem.bankAccountNumber, rItem.iban, rItem.accountType, rItem.currencyUnit, rItem.totalBalanceAvailable, rItem.availableForLoan);
		rowIndexer++;
	}
	xmlSaveFormatFileEnc(fOut, doc, "UTF-8", 1);
	xmlSaveFormatFileEnc("-", doc, "UTF-8", 1);
	fclose(bfp);
	xmlFreeDoc(doc);
	xmlCleanupParser();
}

void validate(char* inputFile, char* outputfile){
	xmlDocPtr doc;
    xmlSchemaPtr schema = NULL;
    xmlSchemaParserCtxtPtr ctxt;
	
    char *XMLFileName = inputFile; // write your xml file here
    char *XSDFileName = outputfile; // write your xsd file here
    
    
    xmlLineNumbersDefault(1); //set line numbers, 0> no substitution, 1>substitution
    ctxt = xmlSchemaNewParserCtxt(XSDFileName); //create an xml schemas parse context
    schema = xmlSchemaParse(ctxt); //parse a schema definition resource and build an internal XML schema
    xmlSchemaFreeParserCtxt(ctxt); //free the resources associated to the schema parser context
    
    doc = xmlReadFile(XMLFileName, NULL, 0); //parse an XML file
    if (doc == NULL)
    {
        fprintf(stderr, "Could not parse %s\n", XMLFileName);
    }
    else
    {
        xmlSchemaValidCtxtPtr ctxt;  //structure xmlSchemaValidCtxt, not public by API
        int ret;
        
        ctxt = xmlSchemaNewValidCtxt(schema); //create an xml schemas validation context 
        ret = xmlSchemaValidateDoc(ctxt, doc); //validate a document tree in memory
        if (ret == 0) //validated
        {
            printf("%s validates\n", XMLFileName);
        }
        else if (ret > 0) //positive error code number
        {
            printf("%s fails to validate\n", XMLFileName);
        }
        else //internal or API error
        {
            printf("%s validation generated an internal error\n", XMLFileName);
        }
        xmlSchemaFreeValidCtxt(ctxt); //free the resources associated to the schema validation context
        xmlFreeDoc(doc);
    }
    // free the resource
    if(schema != NULL)
        xmlSchemaFree(schema); //deallocate a schema structure

    xmlSchemaCleanupTypes(); //cleanup the default xml schemas types library
    xmlCleanupParser(); //cleans memory allocated by the library itself 
    xmlMemoryDump(); //memory dump
}

int endianConverter(int num){//converts little endian to big endian
    unsigned int big_endian = 0;
    int i;
    //changes bytes places to make little endian big endian.
    for (i = 0; i < 4; i++) {
        big_endian = (big_endian << 8) | ((num >> (i * 8)) & 0xFF);
    }
	
	return big_endian;
}