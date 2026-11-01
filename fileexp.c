#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>
struct macro
{
    char name[100];
    char value[200];
};
int main(int argc,char **argv)
{

	if(argc!=2)
	{
		printf("usage:./a.out filename");
		return 1;

	}
	FILE *fp=fopen(argv[1],"r");
	if(fp==0)
	{
		printf("the file is not present\n");
		return 0;
	}
	FILE *fd=fopen("output.txt","w");
	if(fd==0)
	{
		printf("the file is not opened\n");
		return 1;
	}
	char a[]="include";
	char *filename = malloc(100 * sizeof(char));

	if (filename == NULL)
	{
		printf("Memory allocation failed\n");
		return 1;
	}
	int i=0,ch,capacity=100,found=0,len,l1=0,l2=0,ch1,next=0,prev=0;
	char end,s[10];
struct macro m[100];
int count = 0;
	while((ch=fgetc(fp))!=EOF)
	{
		if(ch=='#')
		{ 
			l1=0,l2=0;
                        fscanf(fp,"%s",s);
                        if(strcmp(s,"define")==0)
			{
			  ch1=fgetc(fp);


                        while(ch1==' ' ||  ch1=='\t')
                        {
                                ch1=fgetc(fp);
                        }
			fseek(fp,-1,SEEK_CUR);


			  while(ch1 != ' ' && ch1 != '\t' && ch1 != '\n' && ch1 != EOF)
			  {
				  l1++;
				  ch1 = fgetc(fp);
			  }
			  char macro_name[l1+1];
                          fseek(fp,-(l1+1),SEEK_CUR);
			  fscanf(fp,"%s",macro_name);
                          ch1=fgetc(fp);
                        while(ch1==' ' ||  ch1=='\t')
                        {
                                ch1=fgetc(fp);
                        }
                           fseek(fp,-1,SEEK_CUR);
			  while((ch1=fgetc(fp))!='\n' && ch1!=EOF )
				  l2++;

                         char macro_val[l2+1];
			 fseek(fp,-(l2+1),SEEK_CUR);
macro_val[0]='\0';

if(l2>0)
    fgets(macro_val,l2+1,fp);
                          
if(count < 100)
{
    strcpy(m[count].name,macro_name);
    strcpy(m[count].value,macro_val);
    count++;
}
       



			}


                        else
			{
		        len=strlen(s);
			fseek(fp,-len,SEEK_CUR); 
			ch=fgetc(fp);
			while(ch==' ' ||  ch=='\t')
			{
				ch=fgetc(fp);
			}
			i=0;
			while((ch==a[i]) && a[i] )
			{
				ch=fgetc(fp);
				i++;
			}

			if(a[i]=='\0' && ( ch==' ' || ch=='\t' ||ch=='<' || ch=='"' ))
			{
				while(ch==' ' ||  ch=='\t')
				{
					ch=fgetc(fp);
				}
				i=0;
				if(ch=='<')
				{
					end='>';
				}
				else if(ch=='"')
				{
					end='"';
				}
				else
					continue;

				while ((ch = fgetc(fp)) != end && ch != EOF)
				{
					if (i >= capacity - 1)
					{
						int new_capacity = capacity * 2;
						char *temp = realloc(filename, new_capacity);

						if (temp == NULL)
						{
							printf("Memory allocation failed\n");
							free(filename);
							fclose(fp);
							fclose(fd);
							return 1;
						}

						filename = temp;
						capacity = new_capacity;
					}

					filename[i++] = ch;
				}

				if(ch==end)
				{
					filename[i]='\0';
                                        found=1;
				}

			}

                     if(found==1)
		     {
		             FILE *fr = fopen(filename, "r");

if(fr == NULL)
{
    char path[200];

    sprintf(path, "/usr/include/%s", filename);

    fr = fopen(path, "r");
}

if(fr == NULL)
{
    printf("Header file not found: %s\n", filename);
}
else
{
    while((ch = fgetc(fr)) != EOF)
        fputc(ch, fd);

    fclose(fr);
}
		     }

		}
		}

               
else if (ch == '/')
        {
            next = fgetc(fp);

            if (next == '/')
            {
                while ((ch = fgetc(fp)) != EOF && ch != '\n');
                    

                if (ch == '\n')
                    fputc('\n', fd);
            }
            else if (next == '*')
            {
                int prev = 0;

                while ((ch = fgetc(fp)) != EOF)
                {
                    if (prev == '*' && ch == '/')
                        break;

                    prev = ch;
                }
            }
            else
            {
                fputc('/', fd);

                if (next != EOF)
                    fputc(next, fd);
            }
        }
else
{
    if(isalpha(ch) || ch=='_')
    {     char token[100];
        int j=0,flag=0;

        token[j++]=ch;

        while((ch=fgetc(fp))!=EOF &&
              (isalnum(ch) || ch=='_'))
        {
            if(j<99)
                token[j++]=ch;
        }

        token[j]='\0';

        if(ch!=EOF)
            ungetc(ch,fp);

        for(i=0;i<count;i++)
        {
            if(strcmp(token,m[i].name)==0)
            {
                flag=1;
                break;
            }
        }

        if(flag)
            fputs(m[i].value,fd);
        else
            fputs(token,fd);
    }
    else
    {
        fputc(ch,fd);
    }
}
	}



}
