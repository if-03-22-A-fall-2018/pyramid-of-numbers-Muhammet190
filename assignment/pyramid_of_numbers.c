/*----------------------------------------------------------
 *				HTBLA-Leonding / Class: <your class>
 * ---------------------------------------------------------
 * Exercise Number: 6
 * Title:			Pyramid of Numbers
 * Author:			Muhammet Batuhan Oezdogan
 * ----------------------------------------------------------
 * Description:
 * Calculates a pyramid of numbers, i.e., it multiplies a big
 * integer by the number 2, its result by 3, etc. and then
 * returns to the original value by subsequently dividing,
 * again starting by 2, 3, etc.
 * ----------------------------------------------------------
 */
#include <stdio.h>
#include <string.h>

/// The maximum number of digits allowed in a big int.
#define MAX_DIGITS 80

/** BigInt represents an integer number which can have MAX_DIGITS digits
*** @see MAX_DIGITS
*/
struct BigInt {
	/** number of digits of the big int. */
	int digits_count;

	/** array of digits of big int. */
	unsigned int the_int[MAX_DIGITS];
};

/** strtobig_int converts a string into a BigInt. If strtobig_int runs
*** against a character not between '0' and '9' the conversion stops
*** at this point.
*** @param *str The string to be converted.
*** @param len Number of characters in string to be converted.
*** @param *big_int The converted string now as BigInt.
* @return The number of characters converted.
*/
int strtobig_int(const char *str, int len, struct BigInt *big_int);

/** print_big_int() prints a BigInt.
*** @param *big_int The BigInt to be printed.
*/
void print_big_int(const struct BigInt *big_int);

/** multiply() multiplies a BigInt by an int.
*** @param big_int The BigInt to be multiplied.
*** @param factor The int value which is multiplied by BigInt.
*** @param *big_result The result of the multiplication.
*/
void multiply(const struct BigInt *big_int, int factor, struct BigInt *big_result);

/** divide() multiplies a BigInt by an int.
*** @param big_int The BigInt to be divided.
*** @param divisor The int value by which we want to devide big_int.
*** @param *big_result The result of the division.
*/
void divide(const struct BigInt *big_int, int divisor, struct BigInt *big_result);

/** copy_big_int() copies a BigInt to another BigInt.
*** @param from The source where we want to copy from.
*** @param *to The target where we want to copy to.
*/
void copy_big_int(const struct BigInt *from, struct BigInt *to);

/**
*** main() reads the base number from which the pyramid has to be calculated
*** into an array of char. The max. length of this number is MAX_DIGITS.
*** The number is checked to contain only digits. If not the program exits.
*** Then the inputted number is converted into a big int by calling the
*** function strtobig_int().
*** After the conversion the tower is calculated by calling the functions
*** multiply(), print_big_int(), and copy_big_int() consecutively from 2 to
*** 9 and then again with divide() instead of multiply() from 2 to 9.
***
*/
int main(int argc, char *argv[])
{
	char input[MAX_DIGITS+1];
  printf("Pyramid of Numbers\n" );
  printf("Please enter a number: " );
  scanf("%s",input);
  int length = strlen(input);

  struct BigInt big_int;
  struct BigInt big_result;
  big_int.digits_count = strtobig_int(input, length, &big_int);
  big_result.digits_count =big_int.digits_count;
  int count = 2;

  while (count <= 9)
	{
    print_big_int(&big_int);
    printf(" * %d = ", count);
    multiply(&big_int, count, &big_result);
    print_big_int(&big_result);
    printf("\n");
    copy_big_int(&big_result, &big_int);
    count++;
  }
  copy_big_int(&big_result, &big_int);
  count = 2;
  while (count <=9)
	{
    print_big_int(&big_int);
    printf(" / %d = ", count);
    divide(&big_int, count, &big_result);
    print_big_int(&big_result);
    printf("\n");
    copy_big_int(&big_result, &big_int);
    count++;
  }
}

void print_big_int (const struct BigInt *big_int)
{
  for (int i = big_int->digits_count-1; i >=0 ; i--) {
    printf("%d",big_int->the_int[i]); //Warum geht [i-1]nicht, wenn i=big_int->digits_count?
  }
}
int strtobig_int(const char *string, int length, struct BigInt *big_int)
{
  int digits_count = 0;
  length--;
  for (int i = 0;i < length+1; i++)
  {
     if (string[i] >= '0' && string[i] <= '9'){
       big_int->the_int[length-i] = string[i]-'0';
       digits_count ++;
      }
    else{
      return i;
        }
  }
  return digits_count;
}

void multiply( const struct BigInt * big_int, int factor, struct BigInt * big_result)
{
  int product= 1;
  int carry = 0;
 for (int i = 0; i < big_int->digits_count ; i++)
 {
   product = big_int -> the_int[i] * factor +carry;
   carry = product/10;
   big_result->the_int[i] = product % 10;
}
  if (carry >0 ) {
    big_result->digits_count++;
    int index = big_result->digits_count-1;
    big_result->the_int[index] = carry;
  }
}

void divide(const struct BigInt * big_int, int divisor, struct BigInt *  big_result)
{
  int quotient= 0;
  int rest = 0;
  int digits_sum= 0;
  int count_zeros = 0;
 for (int i = big_int->digits_count-1; i >=0; i--)
 {
   quotient=big_int->the_int[i] + (rest*10);
   big_result->the_int[i] = quotient/divisor;
   rest= quotient %divisor;
   digits_sum+= big_result->the_int[i];
   if ( big_result->the_int[i] == 0 && digits_sum == 0) {
     count_zeros++;
   }
  }
  big_result->digits_count -= count_zeros;
}

void copy_big_int(const struct BigInt * from, struct BigInt * to)
{
for (int i = 0; i < from -> digits_count; i++)
  {
  to->the_int[i] = from->the_int[i];
  }
  if (from->digits_count != to->digits_count) {
    to->digits_count = from->digits_count;
  }
}
