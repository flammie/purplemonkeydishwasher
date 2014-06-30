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
AM_INIT_AUTOMAKE([-Wall -Werror -Wno-portability foreign])

# arguments
AC_ARG_WITH([moses],
            [AS_HELP_STRING([--with-moses],
                            [custom path to moses srcdir @<:@default=PATH@>:@])],
            [with_moses=$withval])
AC_ARG_WITH([irstlm],
            [AS_HELP_STRING([--with-irstlm],
                            [custom path to irstlm install dir @<:@default=PATH@>:@])],
            [with_irstlm=$withval])
AC_ARG_WITH([giza],
            [AS_HELP_STRING([--with-giza],
                            [custom path to GIZA++ srcdir @<:@default=PATH@>:@])],
            [with_giza=$withval])
AC_ARG_WITH([mgizapp],
            [AS_HELP_STRING([--with-mgizapp],
                            [custom path to mgizapp srcdir @<:@default=PATH@>:@])],
            [with_mgizapp=$withval])
AC_ARG_WITH([giza-tools],
            [AS_HELP_STRING([--with-giza-tools],
                            [custom path to GIZA++, mkcls, sntcooc etc. @<:@default=PATH@>:@])],
            [with_giza_tools=$withval])

AC_ARG_ENABLE([parallel],
              [AS_HELP_STRING([--enable-parallel],
                              [use parallel processing @<:@default=no@>:@])],
              [enable_parallel=$enableval],
              [enable_parallel=no])

AS_IF([test x$enable_parallel != xno], 
      [AC_SUBST([PARALLEL_FLAGS], ["-parallel -cores 4 -sort-parallel 4"])])
AC_ARG_WITH([pbs-mail],
            [AS_HELP_STRING([set email for pbs job @<:@default=disable pbs@>:@])],
            [with_pbs_mail=$withval],
            [with_pbs_mail=no])
AC_SUBST([PBS_EMAIL], [$with_pbs_mail])


# Programs
AM_PATH_PYTHON([3.2])
AC_PATH_PROG([JAVA], [java], [false])
AC_PATH_PROG([WGET], [wget], [false])
AC_PATH_PROGS([TAR], [gnutar gtar tar], [false])
AC_PATH_PROG([APERTIUM], [apertium], [false])
AC_PATH_PROG([APERTIUM_DESTXT], [apertium-destxt], [cat])
AC_PATH_PROG([APERTIUM_RETXT], [apertium-retxt], [cat])

#tex
AC_PATH_PROG([XELATEX], [xelatex], [false])
AC_PATH_PROG([BIBTEX], [bibtex], [false])

# moses
AC_PATH_PROG([MOSES], [moses], [false], [$PATH$PATH_SEPARATOR$with_moses/bin])
AC_PATH_PROG([MOSES_TRAIN_MODEL], [train-model.perl], [false], [$PATH$PATH_SEPARATOR$with_moses/scripts/training/])
AC_PATH_PROG([MOSES_TOKENIZER], [tokenizer.perl], [false], [$PATH$PATH_SEPARATOR$with_moses/scripts/tokenizer/])
AC_PATH_PROG([MOSES_TRAIN_TRUECASER], [train-truecaser.perl], [false], [$PATH$PATH_SEPARATOR$with_moses/scripts/recaser/])
AC_PATH_PROG([MOSES_TRUECASE], [truecase.perl], [false], [$PATH$PATH_SEPARATOR$with_moses/scripts/recaser/])
AC_PATH_PROG([MOSES_DETOKENIZER], [detokenizer.perl], [false], [$PATH$PATH_SEPARATOR$with_moses/scripts/tokenizer/])
AC_PATH_PROG([MOSES_DETRUECASE], [detruecase.perl], [false], [$PATH$PATH_SEPARATOR$with_moses/scripts/recaser/])
AC_PATH_PROG([MOSES_CLEAN_CORPUS_N], [clean-corpus-n.perl], [false], [$PATH$PATH_SEPARATOR$with_moses/scripts/training/])
AC_PATH_PROG([MOSES_BUILD_BINARY], [build_binary], [false], [$PATH$PATH_SEPARATOR$with_moses/bin/])
AC_PATH_PROG([MOSES_MERT], [mert-moses.pl], [false], [$PATH$PATH_SEPARATOR$with_moses/training/])
AC_PATH_PROG([MOSES_PROCESS_PHRASE_TABLE], [processPhraseTable], [false], [$PATH$PATH_SEPARATOR$with_moses/bin/])
AC_PATH_PROG([MOSES_PROCESS_LEXICAL_TABLE], [processLexicalTable], [false], [$PATH$PATH_SEPARATOR$with_moses/bin/])
AC_PATH_PROG([MOSES_FILTER_MODEL_GIVEN_INPUT], [filter-model-given-input.pl], [false], [$PATH$PATH_SEPARATOR$with_moses/training/])
AC_PATH_PROG([MOSES_OOV], [oov.pl], [false], [$PATH$PATH_SEPARATOR$with_moses/scripts/analysis/])

AS_IF([test x$MOSES = xfalse], [AC_MSG_ERROR([moses not found, try --with-moses=PATH_TO_MOSES with downloaded mosesdecoder git src dir])])

# qsub
AC_PATH_PROG([QSUB], [qsub], [false])

# irstlm
AC_PATH_PROG([IRSTLM_ADD_START_END], [add-start-end.sh], [false], [$PATH$PATH_SEPARATOR$with_irstlm/bin/])
AC_PATH_PROG([IRSTLM_RM_START_END], [rm-start-end.sh], [false], [$PATH$PATH_SEPARATOR$with_irstlm/bin/])
AC_PATH_PROG([IRSTLM_BUILD_LM], [build-lm.sh], [false], [$PATH$PATH_SEPARATOR$with_irstlm/bin/])
AC_PATH_PROG([IRSTLM_COMPILE_LM], [compile-lm], [false], [$PATH$PATH_SEPARATOR$with_irstlm/bin/])

AS_IF([test x$IRSTLM_COMPILE_LM = xfalse], [AC_MSG_ERROR([irstlm not found, try --with-irstlm=IRSTLM_PATH with path irstlm tells it installs to at the end of configure])])
AC_SUBST([IRSTLM_DIR], [$with_irstlm])

# Argh giza tools
AC_PATH_PROG([MGIZA], [mgiza], [false], [$PATH$PATH_SEPARATOR$with_giza_tools/])
AC_PATH_PROG([GIZAPP], [GIZA++], [false], [$PATH$PATH_SEPARATOR$with_giza_tools/])
AC_PATH_PROG([GIZA_MKCLS], [mkcls], [false], [$PATH$PATH_SEPARATOR$with_giza_tools/])
AC_PATH_PROG([GIZA_SNT2COOC], [snt2cooc], [false], [$PATH$PATH_SEPARATOR$with_giza_tools/])
AC_PATH_PROG([MGIZA_SNT2COOC], [snt2cooc.pl], [false], [$PATH$PATH_SEPARATOR$with_giza_tools/])
AC_PATH_PROG([MGIZA_SNT2COOCRMP], [snt2coocrmp], [false], [$PATH$PATH_SEPARATOR$with_giza_tools/])
AS_IF([test -z $with_giza_tools], [AC_MSG_ERROR([giza tools must be copied to a directory and specified --with-giza-tools=DIR])])
AC_SUBST([GIZA_TOOLDIR], [$with_giza_tools])
AS_IF([test x$MGIZA != xfalse], [AC_SUBST([MGIZA_FLAGS], ["-mgiza -mgiza-cpus 4"])])
AS_IF([test x$MGIZA_SNT2COOC != xfalse], [AC_SUBST([SNT2COOC_FLAG], ["-snt2cooc snt2cooc.pl"])])

# external language models nicely
AC_PATH_PROG([PKGCONFIG], [pkg-config pkgconf], 
             [AC_MSG_ERROR([pkg-config is crucial for even configure to work])])
PKG_CHECK_MODULES([APERTIUM_FIN_ENG], [apertium-fin-eng])
PKG_CHECK_MODULES([OMORFI], [omorfi])
AC_SUBST([OMORFI_PREFIX], [`pkg-config --variable prefix omorfi`])

# some oses are broken
AC_PATH_PROGS_FEATURE_CHECK([SED], [gnused sed],
              [[m4out=`echo aaa | $ac_path_SED 's/a/\n/g' | wc -l`
                test "x$m4out" = x4\
                && ac_cv_path_SED=$ac_path_SED ac_path_SED_found=:]],
              [AC_MSG_ERROR([could not find sed that supports new line])])
AC_SUBST([SED], [$ac_cv_path_M4])


# 
AC_CONFIG_FILES([Makefile])
AS_IF([test x$with_pbs_mail != xno],
      [AC_CONFIG_FILES([mtm2014.pbs])])

AC_OUTPUT

cat <<EOF
-- Making article and experiments $PACKAGE_STRING
  * moses: $with_moses_path $MOSES ...
    * $MOSES_TRAIN_MODEL
  * irstlm: $IRSTLM_DIR $IRSTLM_BUILD_LM ...
  * giza: $GIZA_TOOLDIR
    * $GIZAPP
    * $MGIZA $MGIZA_FLAGS
      $GIZA_MKCLS ...
  * xelatex: $XELATEX
  * bibtex: $BIBTEX

to make experiments or article say make.
(Some parts of this make process may download large files and take up to 50
 hours using 7 gigs of ram, on average laptop)

EOF
