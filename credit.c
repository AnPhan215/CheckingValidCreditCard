//#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

bool sumcheck(long long num, int length);

int main(void)
{
    const int master = 16;  //master card has 16 digit
    const int amex = 15;    //amex card has 15 digit
    const int visa = 13;    //visa card has 13 or 16 digit
    long long num = 0;      //input number
    int temp = 0;           //temperary num to distinguise if the card legit

    ///hello

    //Asking input
    do
    {
        printf("Number: ");
        scanf("%lld", &num);
    }
    while (num < 0);

    //Verify if the is invalid in "digit" term
    if (num < pow(10, visa - 1) || (num >= pow(10, visa) && num < pow(10, (amex - 1))) || num >= pow(10, master))
    {
        printf("INVALID\n");
    }
    //Start verify each credit card
    else
    {
        if (num < pow(10, visa))                                    //Verify VISA credit
        {
            if (sumcheck(num, visa) == true)                        //Verify if checksum is valid
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }

        if (num < pow(10, amex) && num >= pow(10, (amex - 1)))    //Verify AMERICAN credit
        {
            if (sumcheck(num, amex) == true)                      //Verify if checksum is valid
            {
                temp = num / pow(10, amex - 2);                   //temp = the first 2 digit
                if ((temp == 34 || temp == 37))                   //Verify if temp is valid
                {
                    printf("AMEX\n");
                }
                else
                {
                    printf("INVALID\n");
                }

            }
        }

        if (num < pow(10, master) && num >= pow(10, (master - 1)))      //Verify MASTERCARD credit
        {
            if (sumcheck(num, master) == true)                          //Verify if checksum is valid
            {
                temp = num / pow(10, master - 2);                       //temp = the first 2 digit
                if ((temp > 50 && temp < 56))                           //Verify if temp is valid for mastercard
                {
                    printf("MASTERCARD\n");
                }
                else if ((temp / 10) == 4)                              //Verify if temp is valid for visa
                {
                    printf("VISA\n");
                }
                else
                {
                    printf("INVALID\n");
                }
            }
            else
            {
                printf("INVALID\n");
            }
        }
    }

}

bool sumcheck(long long num, int length)
{
    bool result = false;
    int sum = 0;
    for (int i = 1; i <= length; i = i + 2)
    {

        if (length % 2 == 0)                                                                //Check if card digit length is 16
        {
            long long k = pow(10, (length - i));
            if ((((num / k) % 10) * 2) >= 10)
            {
                sum = sum + (((num / k) % 10) * 2) / 10 + (((num / k) % 10) * 2) % 10 ;
                //sum += sum*2 of the digit of odd_th digit if the odd_th digit > 10
            }
            else
            {
                sum = sum + ((num / k) % 10) * 2;                                           //sum += odd_th digit*2
            }
            long long h = pow(10, (length - (i + 1)));
            sum = sum + ((num / h) % 10);                                                   //sum +=even_th digit
        }
        else
        {
            long long k = pow(10, (length - i));
            sum = sum + ((num / k) % 10);                                                   //sum +=odd_th digit
            if (i != length)
            {
                long long h = pow(10, (length - (i + 1)));
                if ((((num / h) % 10) * 2) >= 10)
                {
                    sum = sum + (((num / h) % 10) * 2) / 10 + (((num / h) % 10) * 2) % 10;
                    //sum += sum*2 of the digit of even_th digit if the even_th digit > 10
                }
                else
                {
                    sum = sum + ((num / h) % 10) * 2;                                       //sum += even_th digit*2
                }
            }
        }
    }

    if (sum % 10 == 0)                                                                      //Check if last sum's digit = 0
    {
        result = true;
    }
    else
    {
        result = false;
    }

    return result;
}