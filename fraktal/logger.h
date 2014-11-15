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

#define LOG_NOTHING   0
#define LOG_ERROR     1
#define LOG_WARN      2
#define LOG_INFO      3
#define LOG_TRACE     4

short log_init(char *log_filename, short log_level);

void log_close();

void log_error(char *format, ...);
void log_warning(char *format, ...);
void log_info(char *format, ...);
void log_trace(char *format, ...);
