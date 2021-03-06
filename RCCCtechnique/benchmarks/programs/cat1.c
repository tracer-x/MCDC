# 24 "cat.c"



#include "config.h"
#include <string.h>
#include <stdio.h>
#include <getopt.h>
#include <sys/types.h>

#if HAVE_STROPTS_H
# include <stropts.h>
#endif
#if HAVE_SYS_IOCTL_H
# include <sys/ioctl.h>
#endif

#include "system.h"
#include "error.h"
#include "full-write.h"
#include "quote.h"
#include "safe-read.h"

#define PROGRAM_NAME "cat"

#define AUTHORS "Torbjorn Granlund", "Richard M. Stallman"


#undef max
#define max(h,i) ((h) > (i) ? (h) : (i))


char *program_name;


static char const *infile;


static int input_desc;




#define LINE_COUNTER_BUF_LEN 20
static char line_buf[LINE_COUNTER_BUF_LEN] =
  {
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '0',
    '\t', '\0'
  };



static char *line_num_print = line_buf + LINE_COUNTER_BUF_LEN - 8;


static char *line_num_start = line_buf + LINE_COUNTER_BUF_LEN - 3;


static char *line_num_end = line_buf + LINE_COUNTER_BUF_LEN - 3;


static int newlines2 = 0;

void usage (int status)
{
  if (status != EXIT_SUCCESS)
    fprintf (stderr, _("Try `%s --help' for more information.\n"),
      program_name);
  else
    {
      printf (_("\
Usage: %s [OPTION] [FILE]...\n\
"),
       program_name);
      fputs (_("\
Concatenate FILE(s), or standard input, to standard output.\n\
\n\
  -A, --show-all equivalent to -vET\n\
  -b, --number-nonblank number nonempty output lines\n\
  -e equivalent to -vE\n\
  -E, --show-ends display $ at end of each line\n\
  -n, --number number all output lines\n\
  -s, --squeeze-blank suppress repeated empty output lines\n\
"), stdout);
      fputs (_("\
  -t equivalent to -vT\n\
  -T, --show-tabs display TAB characters as ^I\n\
  -u (ignored)\n\
  -v, --show-nonprinting use ^ and M- notation, except for LFD and TAB\n\
"), stdout);
      fputs (HELP_OPTION_DESCRIPTION, stdout);
      fputs (VERSION_OPTION_DESCRIPTION, stdout);
      fputs (_("\
\n\
With no FILE, or when FILE is -, read standard input.\n\
"), stdout);
      printf (_("\
\n\
Examples:\n\
  %s f - g Output f's contents, then standard input, then g's contents.\n\
  %s Copy standard input to standard output.\n\
"),
       program_name, program_name);
      emit_bug_reporting_address ();
    }
  exit (status);
}



static void next_line_num (void)
{
  char *endp = line_num_end;
  do
    {
      if ((*endp)++ < '9')
 return;
      *endp-- = '0';
    }
  while (endp >= line_num_start);
  if (line_num_start > line_buf)
    *--line_num_start = '1';
  else
    *line_buf = '>';
  if (line_num_start < line_num_print)
    line_num_print--;
}




static bool simple_cat (

     char *buf,



     size_t bufsize)
{

  size_t n_read;



  while(1)
    {


      n_read = safe_read (input_desc, buf, bufsize);
      if (n_read == SAFE_READ_ERROR)
 {
   error (0, errno, "%s", infile);
   return false;
 }



      if (n_read == 0)
 return true;



      {

 size_t n = n_read;
 if (full_write (STDOUT_FILENO, buf, n) != n)
   error (EXIT_FAILURE, errno, _("write error"));
      }
    }
}





static inline void write_pending (char *outbuf, char **bpout)
{
  size_t n_write = *bpout - outbuf;
  if (0 < n_write)
    {
      if (full_write (STDOUT_FILENO, outbuf, n_write) != n_write)
        error (EXIT_FAILURE, errno, _("write error"));
      *bpout = outbuf;
    }
}
# 215 "cat.c"
static bool cat (

     char *inbuf,


     size_t insize,


     char *outbuf,


     size_t outsize,


     bool show_nonprinting,
     bool show_tabs,
     bool number,
     bool number_nonblank,
     bool show_ends,
     bool squeeze_blank)
{

  unsigned char ch;


  char *bpin;



  char *eob;


  char *bpout;


  size_t n_read;






  int newlines = newlines2;

#ifdef FIONREAD


  bool use_fionread = true;
#endif




  eob = inbuf;
  bpin = eob + 1;

  bpout = outbuf;

  while(1)
    {
      do
 {


   if (outbuf + outsize <= bpout)
     {
       char *wp = outbuf;
       size_t remaining_bytes;
       do
  {
     size_t aa = full_write (STDOUT_FILENO, wp, outsize); 
    if ( aa != outsize)
      error (EXIT_FAILURE, errno, _("write error"));
    wp += outsize;
    remaining_bytes = bpout - wp;
  }
       while (outsize <= remaining_bytes);




       memmove (outbuf, wp, remaining_bytes);
       bpout = outbuf + remaining_bytes;
     }



   if (bpin > eob)
     {
       bool input_pending = false;
#ifdef FIONREAD
       int n_to_read = 0;




       bool bb =  (ioctl (input_desc, FIONREAD, &n_to_read) < 0);
       if (use_fionread && bb )
  {






    if ((errno == EOPNOTSUPP) || (errno == ENOTTY) || (errno == EINVAL) || (errno == ENODEV) || (errno == ENOSYS))
      use_fionread = false;
    else
      {
        error (0, errno, _("cannot do ioctl on %s"), quote (infile));
        newlines2 = newlines;
        return false;
      }
  }
       if (n_to_read != 0)
  input_pending = true;
#endif

       if (input_pending)
  write_pending (outbuf, &bpout);



       n_read = safe_read (input_desc, inbuf, insize);
       if (n_read == SAFE_READ_ERROR)
  {
    error (0, errno, "%s", infile);
    write_pending (outbuf, &bpout);
    newlines2 = newlines;
    return false;
  }
       if (n_read == 0)
  {
    write_pending (outbuf, &bpout);
    newlines2 = newlines;
    return true;
  }




       bpin = inbuf;
       eob = bpin + n_read;
       *eob = '\n';
     }
   else
     {





       if (++newlines > 0)
  {
    if (newlines >= 2)
      {



        newlines = 2;




        if (squeeze_blank)
   {
     ch = *bpin++;
     continue;
   }
      }



    if (number & !number_nonblank)
      {
        next_line_num ();
        bpout = stpcpy (bpout, line_num_print);
      }
  }



       if (show_ends)
  *bpout++ = '$';



       *bpout++ = '\n';
     }
   ch = *bpin++;
 }
      while (ch == '\n');



      if (newlines >= 0 && number)
 {
   next_line_num ();
   bpout = stpcpy (bpout, line_num_print);
 }
# 423 "cat.c"
      if (show_nonprinting)
 {
   while(1)
     {
     bool kk = (ch == '\t');
     
       if (ch >= 32)
  {
    if (ch < 127)
      *bpout++ = ch;
    else if (ch == 127)
      {
        *bpout++ = '^';
        *bpout++ = '?';
      }
    else
      {
        *bpout++ = 'M';
        *bpout++ = '-';
        if (ch >= 128 + 32)
   {
     if (ch < 128 + 127)
       *bpout++ = ch - 128;
     else
       {
         *bpout++ = '^';
         *bpout++ = '?';
       }
   }
        else
   {
     *bpout++ = '^';
     *bpout++ = ch - 128 + 64;
   }
      }
  }
       else if ( kk && !show_tabs)
  *bpout++ = '\t';
       else if (ch == '\n')
  {
    newlines = -1;
    break;
  }
       else
  {
    *bpout++ = '^';
    *bpout++ = ch + 64;
  }

       ch = *bpin++;
     }
 }
      else
 {

   while(1)
     {
      bool ll = (ch == '\t'); 
       if (ll && (show_tabs))
  {
    *bpout++ = '^';
    *bpout++ = ch + 64;
  }
       else if (ch != '\n')
  *bpout++ = ch;
       else
  {
    newlines = -1;
    break;
  }

       ch = *bpin++;
     }
 }
    }
}

int main (int argc, char **argv)
{

  size_t outsize;


  size_t insize;

  size_t page_size = getpagesize ();


  char *inbuf;


  char *outbuf;

  bool ok = true;
  int c;


  int argind;


  dev_t out_dev;


  ino_t out_ino;


  bool check_redirection = true;


  bool have_read_stdin = false;

  struct stat stat_buf;


  bool number = false;
  bool number_nonblank = false;
  bool squeeze_blank = false;
  bool show_ends = false;
  bool show_nonprinting = false;
  bool show_tabs = false;
  int file_open_mode = O_RDONLY;

  static struct option const long_options[] =
  {
    {"number-nonblank", no_argument, NULL, 'b'},
    {"number", no_argument, NULL, 'n'},
    {"squeeze-blank", no_argument, NULL, 's'},
    {"show-nonprinting", no_argument, NULL, 'v'},
    {"show-ends", no_argument, NULL, 'E'},
    {"show-tabs", no_argument, NULL, 'T'},
    {"show-all", no_argument, NULL, 'A'},
    {GETOPT_HELP_OPTION_DECL},
    {GETOPT_VERSION_OPTION_DECL},
    {NULL, 0, NULL, 0}
  };

  initialize_main (&argc, &argv);
  program_name = argv[0];
  setlocale (LC_ALL, "");
  bindtextdomain (PACKAGE, LOCALEDIR);
  textdomain (PACKAGE);





  atexit (close_stdout);


c = getopt_long (argc, argv, "benstuvAET", long_options, NULL);

  while (c != -1)
    {
      
 
 
 if (c == 'b')
 {
   number = true;
   number_nonblank = true;
   break;
}
 else if (c == 'e'){
   show_ends = true;
   show_nonprinting = true;
   break;
}
else if (c == 'n'){
 
   number = true;
   break;
}
else if (c == 's'){
 
   squeeze_blank = true;
   break;
}
 else if (c == 't'){

   show_tabs = true;
   show_nonprinting = true;
   break;
}
else if (c == 'u'){
 

   break;
}
else if (c == 'v'){
 
   show_nonprinting = true;
   break;
}
else if (c == 'A'){
 
   show_nonprinting = true;
   show_ends = true;
   show_tabs = true;
   break;
}
else if (c == 'E'){
 
   show_ends = true;
   break;
}
else if (c == 'T'){
 
   show_tabs = true;
   break;
}
else if(GETOPT_HELP_CHAR)
{

}
 

 else {
   usage (EXIT_FAILURE);
 }
 
}
 
 
 
 
 
    



  if (fstat (STDOUT_FILENO, &stat_buf) < 0)
    error (EXIT_FAILURE, errno, _("standard output"));

  outsize = ST_BLKSIZE (stat_buf);






  if (S_ISREG (stat_buf.st_mode))
    {
      out_dev = stat_buf.st_dev;
      out_ino = stat_buf.st_ino;
    }
  else
    {
      check_redirection = false;
#ifdef lint
      out_dev = 0;
      out_ino = 0;
#endif
    }
bool O_BINARY;
  if (! (number | show_ends | squeeze_blank))
    {
      file_open_mode |= O_BINARY;
      bool ee = isatty(STDOUT_FILENO);
      if (O_BINARY && !ee )
 freopen (NULL, "wb", stdout);
    }





  infile = "-";
  argind = optind;

  do
    {
      if (argind < argc)
 infile = argv[argind];

      if (STREQ (infile, "-"))
 {
   have_read_stdin = true;
   input_desc = STDIN_FILENO;
   bool ff = (file_open_mode & O_BINARY); 
   bool gg = isatty(STDIN_FILENO);
   if ( ff && !gg )
     freopen (NULL, "rb", stdin);
 }
      else
 {
   input_desc = open (infile, file_open_mode);
   if (input_desc < 0)
     {
       error (0, errno, "%s", infile);
       ok = false;
       continue;
     }
 }

      if (fstat (input_desc, &stat_buf) < 0)
 {
   error (0, errno, "%s", infile);
   ok = false;
   goto contin;
 }
      insize = ST_BLKSIZE (stat_buf);






      if ((check_redirection) && (stat_buf.st_dev == out_dev) && (stat_buf.st_ino == out_ino) && (input_desc != STDIN_FILENO))
 {
   error (0, 0, _("%s: input file is output file"), infile);
   ok = false;
   goto contin;
 }




      if (! (number | show_ends | show_nonprinting | show_tabs | squeeze_blank))
 {
   insize = max (insize, outsize);
   inbuf = xmalloc (insize + page_size - 1);

   ok &= simple_cat (ptr_align (inbuf, page_size), insize);
 }
      else
 {
   inbuf = xmalloc (insize + 1 + page_size - 1);
# 748 "cat.c"
   outbuf = xmalloc (outsize - 1 + insize * 4 + LINE_COUNTER_BUF_LEN
       + page_size - 1);

   ok &= cat (ptr_align (inbuf, page_size), insize,
       ptr_align (outbuf, page_size), outsize, show_nonprinting,
       show_tabs, number, number_nonblank, show_ends,
       squeeze_blank);

   free (outbuf);
 }

      free (inbuf);

    contin:
     
     if(STREQ (infile, "-"))
 {
 if(close (input_desc) < 0)
 {
 error (0, errno, "%s", infile);
   ok = false; 
 }
 }
    } while (++argind < argc);

    bool jj = have_read_stdin; 
    bool kk = (close(STDIN_FILENO) < 0);
  if ( jj && kk)
    error (EXIT_FAILURE, errno, _("closing standard input"));

   
   if(ok == true )
   {
    exit(EXIT_SUCCESS);
    }
    else
    {
    exit(EXIT_FAILURE);
    }
    
  }
