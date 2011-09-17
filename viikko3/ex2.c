/* This program reads characters typed at the keyboard and writes them 
   one at a time to a disk file, then reads from the same file and
   displays the characters.
*/

#include <stdio.h>
#include <stdlib.h>
int main(void)
{
  FILE *fptr;
  int ch;
  puts("Enter what you want to save in the file.");
  puts("End your input with a Return key.");

  if ((fptr = fopen("file-a.txt", "a+")) == NULL)
  {
    printf("Failed to open file: file-a\n");
    exit(1);
  }

  while ((ch = getchar()) != '\n')
      putc(ch, fptr);

  rewind( fptr);

  puts("The contents of the file file-a.txt is : ");
  while ((ch = getc(fptr)) != EOF)
      putchar(ch);

  fclose(fptr);

  puts("\nEnd of my act! :-) ");

  return 0;
}
 
