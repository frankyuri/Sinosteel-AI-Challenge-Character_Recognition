#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    FILE *fil,*out;
    char FileName[40],labelName[40],
         topRight_X_original[40],
         topRight_Y_original[40],
         bottomRight_X_original[40],
         bottomRight_Y_original[40],
         bottomLeft_X_original[40],
         bottomLeft_Y_original[40],
         topLeft_X_original[40],
         topLeft_Y_original[40],
         topLeft_X_Final[40],
         topLeft_Y_Final[40],
         bottomRight_Y_Final[40],
         bottomRight_X_Final[40];
    fil=fopen("public_training_data.csv","r");
    //int i=600;
    //while(i--)
    for(int i=0;i<12067;i++)
    {
        if(fil==EOF)
        {
            break;
        }
        fscanf(fil,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%s\n",
               FileName, labelName, topRight_X_original, topRight_Y_original, bottomRight_X_original, bottomRight_Y_original, bottomLeft_X_original, bottomLeft_Y_original, topLeft_X_original, topLeft_Y_original);
        fflush(stdin);
        printf("%s \n ",FileName);

        char jsonFileName[100]="./json/";
        strcat(jsonFileName,FileName);
        strcat(jsonFileName,".json");

        out=fopen(jsonFileName,"w");
        if(out==NULL)
        {
            printf("fail");
            return 0;
        }

        //左上Y
        if(strcmp(topLeft_Y_original,topRight_Y_original) > 0)
        {
            strcpy(topLeft_Y_Final,topRight_Y_original);
        }
        else
        {
            strcpy(topLeft_Y_Final,topLeft_Y_original);
        }
        //左上X
        if(strcmp(topLeft_X_original,bottomLeft_X_original) < 0)
        {
            strcpy(topLeft_X_Final,topLeft_X_original);
        }
        else
        {
            strcpy(topLeft_X_Final,bottomLeft_X_original);
        }

        //右下Y
        if(strcmp(bottomLeft_Y_original,bottomRight_Y_original) > 0)
        {
            strcpy(bottomRight_Y_Final,bottomLeft_Y_original);
        }
        else
        {
            strcpy(bottomRight_Y_Final,bottomRight_Y_original);
        }

        //右下X
        if(strcmp(topRight_X_original,bottomRight_X_original) > 0)
        {
            strcpy(bottomRight_X_Final,topRight_X_original);
        }
        else
        {
            strcpy(bottomRight_X_Final,bottomRight_X_original);
        }

        fprintf(out,"{\n");
        fprintf(out,"  \"version\": \"4.5.10\",\n");
        fprintf(out,"  \"flags\": {},\n");
        fprintf(out,"  \"shapes\": [\n");
        fprintf(out,"    {\n");
        fprintf(out,"      \"label\": \"object\",\n");
        fprintf(out,"      \"points\": [\n");
        fprintf(out,"        [\n");
        fprintf(out,"          %s,\n",topLeft_X_Final);
        fprintf(out,"          %s\n",topLeft_Y_Final);
        fprintf(out,"        ],\n");
        fprintf(out,"        [\n");
        fprintf(out,"          %s,\n",bottomRight_X_Final);
        fprintf(out,"          %s\n",bottomRight_Y_Final);
        fprintf(out,"        ]\n");
        fprintf(out,"      ],\n");
        fprintf(out,"      \"group_id\": null,\n");
        fprintf(out,"      \"shape_type\": \"rectangle\",\n");
        fprintf(out,"      \"flags\": {}\n");
        fprintf(out,"    }\n");
        fprintf(out,"  ],\n");
        fprintf(out,"  \"imagePath\": \"..\\\\public_training_data\\\\%s.jpg\",\n",FileName);
        fprintf(out,"  \"imageData\": null,\n");
        fprintf(out,"  \"imageHeight\": 1028,\n");
        fprintf(out,"  \"imageWidth\": 1232\n");
        fprintf(out,"}\n");
        fclose(out);
    }
    fclose(fil);
    return 0;
}
