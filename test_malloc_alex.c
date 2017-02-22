/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_malloc_alex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/01 20:20:48 by aribeiro          #+#    #+#             */
/*   Updated: 2017/01/03 13:30:29 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*  needed for using exit function only*/
#include <stdlib.h>


/*  replace by your own header but always after stdlib.h
    if you want to test the normal malloc just comment following include */
#include "memory.h" 

/*  replace LG_REALLOC by your very specific own define from header */
#define H_DEFINED 	 defined(LG_REALLOC)

/*  needed for measuring time*/
#include <sys/time.h>
/*  needed for printf just to simplify the output */
#include <stdio.h>

/*  Options  */

#define NUM_A 	1024 	/*  nb of misc size malloc/realloc/free to do */
#define SIZE0 	1024   	/*  matrix allocation size :  char* x SIZE0 x SIZE0   */
#define	LOOPS	16     	/*  how many loops */

#define EXTENDED_TEST	0	/*  if !0 force strong fragmentation test */

//#define MAX_SPEED


#if defined(EXTENDED_TEST) && (EXTENDED_TEST > 0)
# undef LOOPS
# define LOOPS	1
# undef SIZE0
# define SIZE0	64
#endif


#ifndef	_WIN32 
# include <sys/resource.h>

size_t used_mem (void)
{
  struct rusage r_usage;
  getrusage(RUSAGE_SELF,&r_usage);
  return((size_t)r_usage.ru_maxrss);
}
#else
# include <windows.h>

size_t used_mem (void)
{
    MEMORYSTATUS status;
    status.dwLength = sizeof(status);
    GlobalMemoryStatus(&status);
    return ((size_t)(status.dwTotalVirtual - status.dwAvailVirtual));
}

#endif


/*  Globals  */
void 	*p[NUM_A];
int		val[NUM_A + LOOPS + 20];
size_t 	temp_mem;


	
double ms_time()
{
    struct timeval time0;

    gettimeofday(&time0 , NULL);
    return (((double)time0.tv_sec * 1000000 + (double)time0.tv_usec)/1000);
}

void mem_info()
{
	size_t mm = used_mem();
	if(mm < temp_mem)
		printf("Estimated allocation memory : must be 0!" ); 	
	else
		printf("Estimated allocation memory : %u bytes   %u pages\n",
				 mm - temp_mem,  (size_t)(mm - temp_mem)/ 4096); 
}



void info_exit(const char *function, unsigned long line, int i)
{
	printf("Aborting!  Allocating size : %d \n\t", i);
	printf("function : %s   line : %d\n\n", function, (int)line);
	mem_info();
	
#if defined(EXIT_FORCE_SEGFAULT) 	
	show_alloc_mem_ex();
#elif defined(H_DEFINED) && H_DEFINED
	show_alloc_mem();
#endif

	exit(1);
}

/* returns an array of arrays of char*, all of which NULL */
char ***alloc_matrix(unsigned rows, unsigned columns)
{
    char 		***matrix;
    unsigned 	row;
    unsigned 	column;
    
    
	matrix = (char ***)malloc(rows * sizeof(char **));
    if (!matrix) 
		info_exit(__func__, __LINE__ -2, (int)(rows * sizeof(char **)));
	row = 0;
    while ( row < rows)
    {
        matrix[row] = (char **)malloc(columns * sizeof(char *));
        if (!matrix[row]) 
			info_exit(__func__, __LINE__ -2, (int)(columns * sizeof(char *)));
		column = 0;
        while ( column < columns)
        {
            if(EXTENDED_TEST)
            {
            	matrix[row][column] = (char *)malloc(2);
            	if (!(matrix[row][column])) 
					info_exit(__func__, __LINE__ -2, 2);
				matrix[row][column][0]= 'M';
				matrix[row][column][1]= '\0';
#if !defined(MAX_SPEED)	
				printf("row = %u column %u\n", row, column);
#endif							
            }
		    else
		    	matrix[row][column] = NULL;
        	column++;
		}
        row++; 
    }
    return matrix;
}

/* deallocates an array of arrays of char*, calling free() on each */
void free_matrix(char ***matrix, unsigned rows, unsigned columns)
{
    unsigned row;
    unsigned column;
    
    row = 0;
    while ( row < rows)
    {
        column = 0;
		while ( column < columns)
        {
			free(matrix[row][column]);
            column++; 
        }
        free(matrix[row]);
        row++; 
    }
    free(matrix);
}

int my_rand(int i)
{
	int j; 
	
	j = rand()%i;
	if(!j)
		j = 1;
	return (j);		
}

void *show_ptr_page()
{
	void 	*temp;

	temp = malloc(10000);
    printf("Fisrt page ptr = %p \n",(void *)((((size_t)temp)/4096)*4096));
    free(temp);
	temp = NULL;
	return ((void *)((((size_t)temp)/4096)*4096));	
}


int main()
{
    int 	i;
    int 	j;
    int		k;
    double	d1;
    void 	*temp;
    void 	*stored;
	char 	***matrix;


    //srand(time(NULL));  // time dependant
    srand(NUM_A); // fixed 
    i = 0;
    /* to create reproductive random misc size suite  
	trying to reproduce real conditions with 3 sizes:
	little < 128(82%)   -   medium < 8000(16%)   -   large > 8000(2%) */
    while (i < NUM_A + LOOPS + 20)
    {
    	val[i] = my_rand(128);
		j = my_rand(128);
		if (j > 105 && j < 126)
			val[i] += ((j - 105) * 317 + 101);
		else if	(j > 125)
		{
			if (j == 126)
				val[i] += (val[i] * my_rand(73) + 5001); 
			else if	(j == 127)
				val[i] += (val[i] * my_rand(757) + 10001); 
			else 
				val[i] += (val[i] * my_rand(657) + 100001);
		}	
		i++;
    }
    stored = show_ptr_page();
    stored += 0;
    temp = NULL;
    printf("memory info before any allocation\n");
    temp_mem = used_mem();
    mem_info();
    
    	printf("\n\n>>>Allocating %d elements of %d bytes \n" , NUM_A, NUM_A);
	i = -1;
	while ( ++i < NUM_A)
	{
		p[i] = malloc(NUM_A);
		if(p[i]== NULL)
			info_exit(__func__, __LINE__ -2, val[i + j]);
		((char*)p[0])[0] = '?'; 	
	} 
	mem_info();
	printf("\n\n>>>Freeing all... \n");
	i = 0;
	while (i < NUM_A )
    {    
  		free(p[i]);
     	p[i]= NULL;
     	i++;
    }
	mem_info();
#if defined(H_DEFINED) && H_DEFINED
	printf("\n show_alloc_mem \n\n");
    show_alloc_mem();
#endif	  

    printf("\n\n>>> Starting Loop test !\n\n");
    d1 = ms_time();
    j = 0;
    while ( j < LOOPS)
    {
        i = -1;
		while ( ++i < NUM_A)
		{
			p[i] = malloc(val[i + j]);
			if(p[i]== NULL)
				info_exit(__func__, __LINE__ -2, val[i + j]);
			((char*)p[0])[0] = '?'; 	
		}
		((char*)p[0])[0] = 'O'; 			/* writing in first allocation */
		((char*)p[NUM_A - 1])[0] = 'K';		/* writing in last allocation */
		i = -1;
		while ( ++i < NUM_A)
		{
			/* to realloc with variable reproductive misc size allocation  */
			temp = realloc( p[i], val[i + j + 7]);
			if(temp== NULL)
			{
				printf("i %d  i %d  %p\n", i, j, p[i]);
				info_exit(__func__, __LINE__ - 4, val[i + j + 7]);
			}
			p[i] = temp;		
		}
		/* reading in first allocation and last allocation to verify  OK */
#if !defined(MAX_SPEED)
		printf("status after realloc : %c%c \n",((char*)p[0])[0],
							((char*)p[NUM_A - 1])[0]);
#endif							
		i = 0;
		k = 0;                
        while (i < NUM_A)
        {
			k++;
			if(k == LOOPS || k == j)
        	{
	        	free(p[i]);
        		p[i]= NULL;
	        }
        	if(k == LOOPS)
        		k = 0;
			i++;			
        }
        matrix = alloc_matrix(SIZE0, SIZE0);
#if !defined(MAX_SPEED)        
        printf("memory > max allocated\t");
		mem_info(); 
#endif		 
        i = 0;
        while (i < NUM_A )
        {
       		free(p[i]);
       		p[i]= NULL;
        	i++;
        }
        free_matrix(matrix, SIZE0, SIZE0);
#if defined(H_DEFINED) && H_DEFINED && !defined(MAX_SPEED)
        if(show_ptr_page() != stored)
        	printf("Different ptr compared to initial fist page !");
#endif        	
        j++;
	}
    d1 -= ms_time();
    d1 = -d1;
    printf("\n\n>>>End\n\nTime used for test loop : %.2f ms\n" , d1 );
#if defined(H_DEFINED) && H_DEFINED   
	printf("\n show_alloc_mem \n\n");
    show_alloc_mem();
#endif
	printf("\nMemory > after free all... \n\t");
	mem_info(); 
 
    return (0);
}