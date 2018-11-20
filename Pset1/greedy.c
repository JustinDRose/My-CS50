int main(void)

{
//Get total bill
    do
    {
        printf ("How much was your bill?: \n");
        Total = get_double();
    }
    while ( Total <= 0); 
    
    int Total_c = Total *100;
//Run coin count    
    while (Total_c > 0)
    {
        int check_q = Total_c % 25;
        int check_d = Total_c % 10;
        int check_n = Total_c % 5;
        int check_p = Total_c % 1;
        
        
        
        if (check_q != Total_c)
        {   
            int n_q = Total_c / 25;
            count = count + n_q;
            Total_c = check_q;
            
          
        }
        else if (check_d != Total_c)
        {
            
            int n_d = Total_c / 10;
            count = count + n_d;  
            Total_c = check_d;
            
        }
        else if (check_n != Total_c)
        {
            int n_n = Total_c / 5;
            count = count + n_n;  
            Total_c = check_n;
           
        }
        else if (check_p != Total_c)
        {
            int n_p = Total_c / 1;
            count = count + n_p;  
            Total_c = check_p;
          
        }
    }
//Print coin count 
    printf("%i\n", count);

 
    
 

 
}

