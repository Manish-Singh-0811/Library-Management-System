#include<stdio.h>
#include<stdlib.h>

typedef struct{
    int id;
    char name[30];
    char author[30];
    char genre[30];
    int pages;
}books;

typedef struct{
    int reg;
    char st_name[30];
    int issB_count;
}student;

int display();
int add();
int delt();
int issue_of_book();
int student_detail();
int return_of_book();

int main()
{
    int x, z;
    A:
    printf("Choose any of the following : \n\n");
    printf("1. Display whole set of books \n");
    printf("2. Add books \n");
    printf("3. Remove a book \n");
    printf("4. Issue a book / Registration\n");
    printf("5. Student Details\n");
    printf("6. Returing of a book\n");
    printf("7. EXIT\n");
    // printf("4. Search by category \n");
    printf(" \n");

    scanf("%d", &x);

    switch(x)
    {
        case 1:  
                 if(display()==0)
                 {
                    int x=0;
                    printf("Press 3 to get back to the main menu else any other to exit\n");
                    scanf("%d", &x);
                    system("cls");
                    if(x==3)
                    {
                        goto A;
                    }

                    else 
                    return 0;
                 }
                 break;

        case 2:  system("cls");
                 if(add()==0)
                 {
                    goto A;
                 }
                 break;

        case 3:  system("cls");
                 if(delt()==0)
                 {
                    goto A;
                 }
                 break;


        case 4: system("cls");
                if(issue_of_book()==0)
                {
                    goto A;
                }
        case 5: system("cls");
                if(student_detail()==0)
                {
                    goto A;
                }

        case 6: system("cls");
                if(return_of_book()==0)
                {
                    goto A;
                }
        case 7: system("cls");
                return 0;

                
                
    }

    return 0;
}


int return_of_book()
{
    FILE *point=fopen("student_count.txt", "r");
    if(point==NULL)
    {
        int click;
        printf("No record found\n");
        printf("enter any number to continue...\n");
        scanf("%d", &click);
        return 0;
    }

    int st_count=getw(point);
    fclose(point);

    if(st_count==0)
    {
        int click;
        printf("no student entry\n");
        printf("enter any number to go back\n");
        scanf("%d", &click);
        return 0;
    }

    printf("Enter your registration number\n");
    int r_n;
    scanf("%d", &r_n);

    point=fopen("students.txt", "r");
    student s[100];

    int is_reg=-1, is_book_count=0;
    for(int i=0; i<st_count; i++)
    {
        fread(&s[i], sizeof(s[i]), 1, point);
        if(s[i].reg==r_n)
        {
            is_reg++;
            if(s[i].issB_count>0)
            {
                s[i].issB_count--;
                // break;
            }

            else  if(s[i].issB_count<=0)
            {
                is_book_count--;
                // break;
            }
        }       
    }
    fclose(point);

    if(is_reg==-1)
    {
        int click;
        printf("no student found with the given registration id\n");
        printf("enter any number to go back\n");
        scanf("%d", &click);
        return 0;
    }

    if(is_book_count==-1)
    {
        int click;
        printf("no books to return for this student\n");
        printf("enter any number to go back\n");
        scanf("%d", &click);
        return 0;
    }

    int b_id;
    printf("enter book id to be returned\n");
    scanf("%d", &b_id);

    FILE *ptr=fopen("count.txt", "r");
    int bookCOUNT=getw(ptr);
    fclose(ptr);

    ptr=fopen("books.txt", "r");
    books b;
    for(int i=0; i<bookCOUNT; i++)
    {
        fread(&b, sizeof(b), 1, ptr);
        if(b.id==b_id)
        {
            printf("Book Matched\n");
            break;
        }
    }
    fclose(ptr);

    if(b.id!=b_id)
    {
        int click;
        printf("NO such book found\n");
        printf("enter any number to continue\n");
        scanf("%d", &click);
        return 0;
    }


    point=fopen("students.txt", "w");

    for(int i=0; i<st_count; i++)
    {
        fwrite(&s[i], sizeof(s[i]), 1, point);
    }
    fclose(point);
    printf("overwrite successful\n");
    return 0;
}


int student_detail()
{
    FILE *p=fopen("student_count.txt", "r");
    FILE *point=fopen("students.txt", "r");
    if(p==NULL || point==NULL)
    {
        int click;
        printf("NO records available\n");
        printf("enter any number to continue...\n");
        scanf("%d", &click);
        return 0;
    }
    
    int st_count=getw(p);
    fclose(p);
    if(st_count==0)
    {
        fclose(point);
        int click;
        printf("NO records available\n");
        printf("enter any number to continue...\n");
        scanf("%d", &click);
        return 0;
    }

    printf("Enter registration number : ");
    int r_n;
    scanf("%d", &r_n);


    student s;
    int checker=-1;
  
        for(int i=0; i<st_count; i++)
        {
            fread(&s, sizeof(s), 1, point);
            if(s.reg==r_n)
            {
                int click;
                printf("DETAILS  : \n");
                printf("Name : %s", s.st_name);
                printf("Registration Number : %d\n", s.reg);
                printf("Number of books issues : %d\n\n\n",s.issB_count);
                printf("Enter any number to continue....\n");
                scanf("%d", &click);
                checker++;
            }
        }

    fclose(point);

    if(checker<0)
    {
        int click;
        printf("Student not registered :\n");
        printf("enter any number to continue...\n");
        scanf("%d", &click);
    }

    return 0;
}


int issue_of_book()
{

    FILE *point=fopen("student_count.txt", "r");        //opening st_count in reading mode
    if(point==NULL)
    {
        point=fopen("student_count.txt", "w");          //opening st_count in writing mode
        putw(0, point);
        fclose(point);      //cllsing student.count
        point=fopen("student_count.txt", "r");      //opening st_count in reading mode
    }
    int st_count=getw(point);
    fclose(point);      //closing st_count.txt

    point=fopen("students.txt", "r");
    if(point==NULL)
    {
        point=fopen("students.txt", "w");
        fclose(point);
        point=fopen("students.txt", "r");
    }

    int r_n;
    printf("enter the registration number of the student : ");
    scanf("%d", &r_n);
    getchar();

    student s;
    for(int i=0; i<st_count; i++)
    {
        fread(&s, sizeof(s), 1, point);
        if(s.reg == r_n)
        {
            printf("registration id matched\n");
            break;
        }
    }

    student new_student;
    if((s.reg != r_n) || st_count==0)
    {
        fclose(point);
        point=fopen("students.txt", "a");

        printf("Registration : \n\n\n");
        printf("enter your name : ");
        fgets(&new_student.st_name, 30, stdin);

        new_student.reg=r_n;
        new_student.issB_count=0;

        // fwrite(&new_student, sizeof(new_student), 1, point);
        fwrite(&new_student, sizeof(student), 1, point);

        fclose(point);
        
        st_count++;
        point=fopen("student_count.txt", "w");
        putw(st_count,point);
        fclose(point);

        system("cls");
        printf("Registration Successful !\n\n");
        printf("1. For issuing book\n");
        printf("2. Go back\n");
        int uio;
        scanf("%d", &uio);
        switch(uio)
        {
            case 2 : return 0; 
        }

        point=fopen("students.txt", "r");
    }
    printf("no of registered students : %d\n", st_count);


    printf("enter the id of book for issuing : ");
    int book_id;
    scanf("%d", &book_id);
    FILE *ptr=fopen("count.txt", "r");
    int book_count=getw(ptr);
    fclose(ptr);

    ptr=fopen("books.txt", "r");
    books boo;
    for(int i=0; i<book_count; i++)
    {
        fread(&boo, sizeof(books), 1, ptr);
        if(boo.id==book_id)
        {
            printf("book id matched \n");
            break;
        }
    }
    fclose(ptr);

    int rough;
    if(boo.id!=book_id)
    {
        printf("Book id not found\n");
        // fclose(ptr);
        printf("enter any number to continue \n");
        scanf("%d", &rough);
        return 0;
    }
    // fclose(ptr);

    student ss;
    for(int i=0; i<st_count; i++)
    {
        fread(&ss, sizeof(ss), 1, point);
        if(ss.reg==r_n)
        {
            printf("Already registered student\n");
            break;
        }
    }
    fclose(point);
    point=fopen("students.txt", "r");

    student arr_student[100];

    int max_limit_checker=0;
    for(int i=0; i<st_count; i++)
    {
        fread(&arr_student[i],sizeof(arr_student[i]), 1, point);
        if(arr_student[i].reg==r_n)
        {
            if(arr_student[i].issB_count<3)
            {
            printf("book issue successful\n");
            arr_student[i].issB_count++;
            }

            else
            {
                max_limit_checker--;
                // printf("maximum issue limit reached, cannot issue further\n");
                // printf("enter any number to continue...\n");
                // scanf("%d", &max_limit_checker);
                break;
            }
        }
        printf("reg number : %d\n", arr_student[i].reg);
        printf("name: %s", arr_student[i].st_name);
        printf("book count =%d\n", arr_student[i].issB_count);
    }
    fclose(point);

    if(max_limit_checker<0)
    {
        int che;
        printf("maximum issue limit reached (3), cannot issue further\n");
        printf("enter any number to continue...\n");
        scanf("%d", &che);
        return 0;
    }

    point=fopen("students.txt", "w");

    for(int i=0; i<st_count; i++)
    {
        fwrite(&arr_student[i], sizeof(arr_student[i]), 1, point);
    }

    fclose(point);
    printf("overwrite successful\n");
    return 0;
}

//students


int add()
{
    // books b[100];
    int x=0, num;
    FILE* ptr=fopen("books.txt", "a");  // opening book.txt file in append mode

    FILE* point=fopen("count.txt", "r");    //opening count.txt file in reading mode
    if(point==NULL)
    {
        point=fopen("count.txt", "w");
        putw(0, point);
        fclose(point);
        x=0;
    }

    else
    {
    x=getw(point);       //storing the existing value of count.txt file in x variable
    fclose(point);      //closing count.txt 
    }

    printf("enter number of books you want to add : ");
    scanf("%d", &num);
    getchar();
    books b[num];


    for(int i=0; i<num; i++)
    {
        printf("\n\nEnter details for book %d :\n\n", i+1);

        printf("Book Name: ");
        fgets(b[i].name, 30, stdin);

        printf("Author Name: ");
        fgets(b[i].author, 30, stdin);

        printf("Book Id: ");
        scanf("%d", &b[i].id);

        printf("Number of pages : ");
        scanf("%d", &b[i].pages);
        getchar();

        printf("Genre : ");
        fgets(b[i].genre, 30, stdin);
        fwrite(&b[i], sizeof(b[i]), 1, ptr);
        printf("\n\n");
        system("cls");       
    }

    point=fopen("count.txt", "w");      //opening count.txt in writing mode
    putw((x+num), point);       //updating value of count (by adding the number of books you want to add in the exting set of books)
    fclose(point);      //closing count.txt file


    fclose(ptr);
    return 0;
}


int delt()
{
    FILE* point=fopen("count.txt", "r");    //opening the file count.txt in reading mode 
    if(point==NULL)
    {
        printf("nothing to delete as count file doesn't exist\n");
        return 0;
    }
    int x=getw(point);      //storing the value of count.txt in variable x
    fclose(point);          //closing the file count.txt

    if(x==0)
    {
        printf("list is empty\n");
        return 0;
    }
    
    int n;
    printf("enter number of books you wanna delete : ");
    scanf("%d",&n);
    int arr[n];

    for(int i=0; i<n; i++)
    {
        printf("enter id for book %d : ", (i+1));
        scanf("%d", &arr[i]);       //taking input from users: the book IDs
    }


    FILE* ptr=fopen("books.txt", "r");      //opening the file books.txt in reading mode
    // books b[100];
    books b[x];
    for(int i=0; i<x; i++)
    {
        fread(&b[i], sizeof(b[i]), 1, ptr);     //stroing the existing set of books in form of array 
    }
    fclose(ptr);        //closing the file books.txt

    int checker=0;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<x; j++)
        {
            if(b[j].id==arr[i])
            {
                checker++;
                arr[i]=j;       //replacing the stored IDs with serial number (in order to arrange it in ascending order )
            }
        }
    }

    if(n!=checker)
    {
        int click;
        printf("Either of your entries are wrong, thus can't process further...\n");
        printf("enter any number to continue...\n");
        scanf("%d", &click);
        return 0;
    }

    //Arranging according to indices
    int key, j;
    for(int i=1; i<n; i++)
    {
        key=arr[i];
        j=i-1;

        while(arr[j]>key && j>=0)
        {
            arr[j+1]=arr[j];
            j--;
        }

        arr[j+1]=key;
    }

    ptr=fopen("books.txt", "r");
    point=fopen("temporary.txt", "w");
    int p=0;
    for(int i=0; i<x; i++)
    {
        if(i!=arr[p])
        {
            fwrite(&b[i], sizeof(b[i]), 1, point);  //copying all elements of books.txt except the ones stored in array "arr"
        }
        else p++;
    }
    fclose(point);
    fclose(ptr);


    // books b1[100];
    books b1[(x-n)];
    ptr=fopen("books.txt", "w");
    point=fopen("temporary.txt", "r");

    for(int i=0; i<x-n; i++) //overwriting the contents of file books.txt (from temporary.txt)
    {
        fread(&b1[i], sizeof(b[i]), 1, point);
        fwrite(&b1[i], sizeof(b[i]), 1, ptr);
    }
    fclose(point);
    fclose(ptr);

    //updating count
    point=fopen("count.txt", "w");
    putw((x-n), point);
    fclose(point);
    system("cls");
    return 0;
}



int display()
{
    // books b[100];
    int x=0;
    FILE* ptr=fopen("count.txt", "r");

    if(ptr==NULL)
    {
        printf("nothing to show\n");
        return 0;
    }
    x=getw(ptr);
    fclose(ptr);

    if(x==0)
    {
        printf("No records available\n");
        return 0;
    }

    books b[x];

    ptr=fopen("books.txt", "r");

    
        for(int i=0; i<x; i++)
        {
            fread(&b[i], sizeof(b[i]), 1, ptr);
            printf("Book %d ....\n", i+1);
            printf("Book Id      : %d\n", b[i].id);
            printf("Book Name    : %s", b[i].name);
            printf("Author Name  : %s", b[i].author);
            printf("Pages        : %d\n", b[i].pages);
            printf("Genre        : %s\n", b[i].genre);
            printf("\n\n");            
        }
    
    fclose(ptr);
    return 0;
}