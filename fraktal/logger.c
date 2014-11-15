/*
**
** Copyright (C) 2003-2006 The Contributors of the AlleGimmicks Project.
** Please see the file "AUTHORS" for a list of contributors
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#include <stdio.h>
#include <time.h>
#include <allegro.h>
#include "logger.h"

//using namespace std;

FILE *f;
short log_level;

/*
Logging level:
    0 nothing
    1 error
    2 warrning
    3 info
    4 trace
*/
short log_init(char *log_filename, short logging_level) {
   log_level = logging_level;
   return (f = fopen(log_filename,"w"))==NULL;
}

void log_close() {
   fclose(f);
}
 
struct tm *getTime() {
   time_t current_time;
   current_time = time(NULL);
   return localtime(&current_time);
}

void log_info(char *format, ...) {
   if(log_level < LOG_INFO) return;
   char buf[512];
   struct tm *t;
   
   t = getTime();
   fprintf(f, "%02d:%02d:%02d INFO  ", t->tm_hour, t->tm_min, t->tm_sec);
   
   va_list ap;
   va_start(ap, format);
   uvszprintf(buf, sizeof(buf), format, ap);
   va_end(ap);
   
   fprintf(f,buf);
   fflush(f);
}

void log_error(char *format, ...) {
   if(log_level < LOG_ERROR) return;
   char buf[512];
   struct tm *t;
   
   t = getTime();
   fprintf(f, "%02d:%02d:%02d ERROR ", t->tm_hour, t->tm_min, t->tm_sec);
   
   va_list ap;
   va_start(ap, format);
   uvszprintf(buf, sizeof(buf), format, ap);
   va_end(ap);
   
   fprintf(f,buf);
   fflush(f);
}

void log_warning(char *format, ...) {
   if(log_level < LOG_WARN) return;
   char buf[512];
   struct tm *t;
   
   t = getTime();
   fprintf(f, "%02d:%02d:%02d WARN  ", t->tm_hour, t->tm_min, t->tm_sec);
   
   va_list ap;
   va_start(ap, format);
   uvszprintf(buf, sizeof(buf), format, ap);
   va_end(ap);
   
   fprintf(f,buf);
   fflush(f);
}

void log_trace(char *format, ...) {
   if(log_level < LOG_TRACE) return;
   char buf[512];
   struct tm *t;
   
   t = getTime();
   fprintf(f, "%02d:%02d:%02d TRACE ", t->tm_hour, t->tm_min, t->tm_sec);
   
   va_list ap;
   va_start(ap, format);
   uvszprintf(buf, sizeof(buf), format, ap);
   va_end(ap);
   
   fprintf(f,buf);
   fflush(f);
}
