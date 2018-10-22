#include <stdio.h>
#include <string.h>

int main()
{

    FILE *myFile;
    char fname[100];
    printf("Please enter the name of the input file: \n");
    scanf("%s", fname);

    myFile = fopen(fname, "r");
    //read file into array
    char Array[81];
    int w=0, x, finArray[81];

    for (int i = 0; i < 81; i++){
        fscanf(myFile, "%1s", &Array[i]);
        finArray[i] = 0;
    }
    fclose(myFile);
    for (int i = 0; i < 81; i++){
        if(Array[i]!='.'){
            x = Array[i] - '0';
            finArray[w++] = (i/9+1)*100 + ((i)%9+1)*10 + x;
        }
    }

    FILE *f = fopen("encoding.txt", "wb");
    fprintf(f, "p cnf 729 5000\n");
    for(int w=0; finArray[w]!=0; w++){
        fprintf(f, "%d 0\n",finArray[w]);
    }

    //for cell occurence
    for(int i=1;i<10;i++)
    {
        for(int j=1;j<10;j++)
        {
            for(int k=1;k<10;k++)
            {
                fprintf(f, "%d ",1*(100*i+10*j+k));
            }
            fprintf(f, "%d\n", 0);
        }
    }
    //for cell, to ensure single occurence
    for(int i=1;i<10;i++)
    {
        for(int j=1;j<10;j++)
        {
            for(int k=1;k<10;k++)
            {
                for(int z=k+1;z<10;z++)
                {
                    fprintf(f,"%d ",-1*(100*i+10*j+z));
                    fprintf(f,"%d ",-1*(100*i+10*j+k));
                    fprintf(f,"%d\n",0);
    
                }
            }
        }
    }
    //for rows
    for(int i=1;i<10;i++)
    {
        for(int k=1;k<10;k++)
        {
            for(int j=1;j<10;j++)
            {
                fprintf(f,"%d ",1*(100*i+10*j+k));
            }
            fprintf(f,"%d\n",0);
        }
    }
    //for columns
    for(int j=1;j<10;j++)
    {
        for(int k=1;k<10;k++)
        {
            for(int i=1;i<10;i++)
            {
                fprintf(f,"%d ",1*(100*i+10*j+k));
            }
            fprintf(f,"%d\n",0);
        }
    }


    //for primary diagonal
    for(int i=1;i<10;i++)
    {
        for(int k=1;k<10;k++)
        {
                fprintf(f,"%d ",1*(100*k+10*k+i));
        }
        fprintf(f,"%d\n",0);
    }
    //for other diagonal
    for(int i=1;i<10;i++)
    {
        for(int k=1;k<10;k++)
        {
                fprintf(f,"%d ",1*(100*k+10*(10-k)+i));
        }
        fprintf(f,"%d\n",0);
    }


    //for box
    for(int j=0;j<9;j++)
    {
        for(int k=1;k<10;k++)
        {
            for(int i=0;i<9;i++)
            {
                fprintf(f,"%d ",1*(100*(1+3*(j/3)+i/3)+10*(1+3*(j%3)+i%3)+k));
            }
            fprintf(f,"%d\n",0);
        }
    }
    char str2[5];
    fclose(f);
    system("./minisat encoding.txt SAToutput.txt");    
    // printf("%s\n", str2);
    FILE *f1;
    FILE *f2;
    f1 = fopen("SAToutput.txt", "r");
    f2 = fopen("Answer1.txt", "wb");
    fscanf(f1, "%5s", str2);
    printf("%s\n", str2);
    int boolean[1000];
   
    char pick[5];
    int a, i=0, j=0;
    int arr[9][9];
    for(int k=1;k<1000;k++)
    {
        fscanf(f1, "%5s", pick);
        if(pick[0]!='-')
            a = 100*(pick[0]-'0')+10*(pick[1]-'0')+(pick[2]-'0');
        if(a>0)
        {
            i=a/100;
            j=(a%100)/10;
            arr[i][j]=a%10;
        }
    }
    for(i=1;i<10;i++)
    {
        for(j=1;j<10;j++)
        {
            fprintf(f2, "%d ",arr[i][j]);
            //printf("%d", arr[i][j]);
        }
        fprintf(f2, "\n");
        //printf("\n");
    }
    fclose(f1);
    fclose(f2);

    return 0;
}