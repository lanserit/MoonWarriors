#!/bin/sh
# AUTO-GENERATED FILE, DO NOT EDIT!
if [ -f $1.org ]; then
  sed -e 's!^D:/cygwin_tju/lib!/usr/lib!ig;s! D:/cygwin_tju/lib! /usr/lib!ig;s!^D:/cygwin_tju/bin!/usr/bin!ig;s! D:/cygwin_tju/bin! /usr/bin!ig;s!^D:/cygwin_tju/!/!ig;s! D:/cygwin_tju/! /!ig;s!^D:!/d!ig;s! D:! /d!ig;s!^C:!/c!ig;s! C:! /c!ig;' $1.org > $1 && rm -f $1.org
fi
