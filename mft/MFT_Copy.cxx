/**************************************************************************
 * Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 *                                                                        *
 * Author: The ALICE Off-line Project.                                    *
 * Contributors are mentioned in the code where appropriate.              *
 *                                                                        *
 * Permission to use, copy, modify and distribute this software and its   *
 * documentation strictly for non-commercial purposes is hereby granted   *
 * without fee, provided that the above copyright notice appears in all   *
 * copies and that both the copyright notice and this permission notice   *
 * appear in the supporting documentation. The authors make no claims     *
 * about the suitability of this software for any purpose. It is          *
 * provided "as is" without express or implied warranty.                  *
 **************************************************************************/

/* MFT_testBench
 *
 */

#include <stdio.h>
#include <stdlib.h> // For exit()
#include <iostream>
#include <string>
#include <fstream>
#include "MFT_Copy.h"

#define BUFFER_SIZE 1000

using namespace std;

int main()
{
    FILE *fptr1, *fptr2, *xmlfile0, *xmlfile2;
    char filename[100], c;
    
    printf("Enter the filename to open for reading \n");
    scanf("%s", filename);
    
    // Open one file for reading
    fptr1 = fopen(filename, "r");
    if (fptr1 == NULL)
    {
        printf("Cannot open file %s \n", filename);
        exit(0);
    }
    
    printf("Enter the filename to open for writing \n");
    scanf("%s", filename);
    
    // Open another file for writing
    fptr2 = fopen(filename, "w");
    if (fptr2 == NULL)
    {
        printf("Cannot open file %s \n", filename);
        exit(0);
    }
    
    
    printf("Enter the filename to open for reading \n");
    scanf("%s", filename);
    
    // Open one file for reading xml
    xmlfile0 = fopen(filename, "r");
    if (xmlfile0 == NULL)
    {
        printf("Cannot open file %s \n", filename);
        exit(0);
    }
    
    printf("Enter the filename to open for reading \n");
    scanf("%s", filename);
    
    // Open one file for reading xml
    xmlfile2 = fopen(filename, "r+");
    if (xmlfile2 == NULL)
    {
        printf("Cannot open file %s \n", filename);
        exit(0);
    }
    
    
    char content0[100]="Dead pixels";
    char content1[100]="Stuck pixels";
    char content2[100]="Threshold average";
    char content3[100]="Noise average";
    char content4[100]="Ineff pixels";
    char content5[100]="Noisy pixels";

    // Read contents from file
    c = fgetc(fptr1);
    
    while (c != EOF)
    {
        fputc(c, fptr2); // write to another file
        c = fgetc(fptr1);
    }
    
    char *name;
    char *name2;

    char stringToFind[20];
    fgets(stringToFind, sizeof(stringToFind), stdin );
    char line[300];
    char line2[300];
    
    char * pch;
    char buffer[BUFFER_SIZE];
    char oldWord[100], newWord[100];
    
    
    while ( !feof(xmlfile0) ){
        
        fgets(line,sizeof(line),xmlfile0);
        
//        if(strstr(line, stringToFind) != NULL)
//        {
//            printf("%s",line);
//        }
        name = get_value(line, "<name>", "</name>");
        
        if(name != NULL){
            
            
            
            
            while ( !feof(fptr1) ){
                
                
                
                if( fgets(line2,sizeof(line2),fptr1) != NULL){
                
                    name2 = get_value(line2, "Chip 5", "fin");
                    
                    if(name2 != NULL){
                        printf("\n%s",name2);
                        // Replace all occurrence of word from current line
                        replaceAll(line2, name2, name);
                        
                        // After replacing write it to temp file.
                        fputs(line2, xmlfile2);
                        fputs("\n", xmlfile2);

                        //                    pch = strstr (line2,name2);
                        //
                        //                    strncpy (pch,name,sizeof(name));
                        //                    puts (pch);
                        //
                        //                    fputs(name, xmlfile2);
                        //                    printf("\n%s",name2);
                        
                    }
                }
                
                
                
                
                
            }
            
            
            
            fputs(name, xmlfile2);
            printf("\n%s",name);

        }
        
        
    }
    fclose(xmlfile0);
    fclose(xmlfile2);

    //char *pch;
    //pch = strstr (str,"simple");
    //strncpy (pch,"sample",6);

    
    printf("\nContents copied to %s \n", filename);
    
    fclose(fptr1);
    fclose(fptr2);
    return 0;
}

char * get_value(const char *input,const char *start_name,const char *end_name)
{
    const char *start, *end;
    
    if((start = strstr(input, start_name)) != NULL)
    {
        start += strlen(start_name);
        if((end = strstr(start, end_name)) != NULL)
        {
            char *out = (char *) malloc(end - start + 1);
            if(out != NULL)
            {
                memcpy(out, start, (end - start));
                out[end - start] = '\0';
                return out;
            }
        }
    }
    return NULL;
}


/**
 * Replace all occurrences of a given a word in string.
 */
void replaceAll(char *str, const char *oldWord, const char *newWord)
{
    char *pos, temp[BUFFER_SIZE];
    int index = 0;
    int owlen;
    
    owlen = strlen(oldWord);
    
    
    /*
     * Repeat till all occurrences are replaced.
     */
    while ((pos = strstr(str, oldWord)) != NULL)
    {
        // Bakup current line
        strcpy(temp, str);
        
        // Index of current found word
        index = pos - str;
        
        // Terminate str after word found index
        str[index] = '\0';
        
        // Concatenate str with new word
        strcat(str, newWord);
        
        // Concatenate str with remaining words after
        // oldword found index.
        strcat(str, temp + index + owlen);
    }
}
