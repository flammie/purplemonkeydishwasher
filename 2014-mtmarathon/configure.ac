## Process this file with autoconf to produce configure scripts

## Copyright (c) 2014 Flammie et al.

## This program is free software: you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation, either version 3 of the License, or
## (at your option) any later version.

## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.

## You should have received a copy of the GNU General Public License
## along with this program.  If not, see <http://www.gnu.org/licenses/>.


AC_INIT([2014-mtm-fin-eng], [20140621], [tommi.pirinen@computing.dcu.ie], [2014-mtm-fin-eng])
AM_INIT_AUTOMAKE([-Wall foreign])

# Programs
AC_PATH_PROG([XELATEX], [xelatex], [false])
AC_PATH_PROG([BIBTEX], [bibtex], [false])

# 
AC_CONFIG_FILES([Makefile])
AC_OUTPUT

cat <<EOF
-- Making article and experiments $PACKAGE_STRING
  * xelatex: $XELATEX
  * bibtex: $BIBTEX

to make experiments or article say make.
