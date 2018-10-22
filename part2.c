#include <stdio.h>

int main(){
	FILE *myFile;
	myFile = fopen("Answer1.txt", "r");
	char c,d;
	int a[81], input[81], inputCopy[81];
	for(int i=0; i<81; i++){
		fscanf(myFile, "%1c", &c);
		a[i] = c-'0';
		//printf("%d", a[i]);
		if(!((i+1)%9)){
			fscanf(myFile, "%1c", &d);
			//printf("\n");
		}
	}
	fclose(myFile);
	for(int i=0; i<81; i++){
		input[i] = 100*(i/9+1)+10*(i%9+1)+a[i];
		inputCopy[i] = input[i];
		printf("%d 0\n", input[i]);
	}
	
	// you are a valid sudoku
	// you are not my sudoku S
	// you look like my sudoku S at certain positions
	// can you be something other than S ?

	FILE *f, *f1;
	for(int pop=0; pop<81; pop++){
		f = fopen("newInput.txt", "wb");
		// check if removing it gives UNSAT
		// if yes, remove it from array and put 0 there
		// repeat for all elements

		//encoding for sudoku
	    fprintf(f, "p cnf 999 3321\n");

			//for cell atleast
    for(int i=1;i<10;i++)
    {
        for(int j=1;j<10;j++)
        {
            for(int k=1;k<10;k++)
            {
                fprintf(f, "%d ",1*(100*i+10*j+k));
            }
            fprintf(f, "%d\n", 0);
            //written++;
        }
    }
    //for cell atmost
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
                    //written++;
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
            //written++;
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
            //written++;
        }
    }


    //for diagonal
    // for(int i=1;i<10;i++)
    // {
    //     for(int k=1;k<10;k++)
    //     {
    //             fprintf(f,"%d ",1*(100*i+10*i+k));
    //     }
    //     fprintf(f,"%d\n",0);
    // }
    // //for diagonal
    // for(int i=1;i<10;i++)
    // {
    //     for(int k=1;k<10;k++)
    //     {
    //             fprintf(f,"%d ",1*(100*i+10*(10-i)+k));
    //     }
    //     fprintf(f,"%d\n",0);
    // }


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
            //written++;
        }
    }

    // you should not be S

    for(int i=0; i<81; i++){
    	fprintf(f, "%d ", -1*input[i]);
    	if(i==80){
    		fprintf(f, "0\n");
    	}
    }

	// // you should look like S at certain positions

	for(int j=0; j<81; j++){
		if(inputCopy[j]!=0 && pop!=j){
    		fprintf(f, "%d 0", inputCopy[j]);
    		if(j!=80){
    			fprintf(f, "\n");
    		}
    	}
	}
	fclose(f);
	system("./minisat newInput.txt newOutput.txt");
	
	f1 = fopen("newOutput.txt", "r");
	char sat[10];
	fscanf(f1, "%10s", sat);
	fclose(f1);
	if(sat[0]=='U'){
		inputCopy[pop] = 0;
		printf("YAY\n");
	}else{
		printf("NO!\n");
	}

	}
	for(int i=0; i<81; i++){
		if(inputCopy[i]!=0)
		printf("%d", inputCopy[i]%10);
	    else
	    printf(".");
		if(!((i+1)%9)){
			printf("\n");
		}
	}

}