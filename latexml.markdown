# Latexml

[Latexml]() is a system for converting latex to XML to HTML. There have been
and will be many systems to do this but this is the one I have found most usable
with current web stuff and my latex, it creates HTML5 and turns some math into
modern web math stuff. 

But its support of latex packages is quite dodgy, basically you need to rewrite
the packages in perl (eww). There's some support for more popular packages and
some packages just work, but e.g. with linguistics and stuff nothing works.
I've documented here some minimal hacks I've made.

Also one can write custom css and javascript and so on, documented here as well.

## Latex packages I wrote

### Polyglossia

Polyglossia is the language support package for modern tex stuff, instead of
babel that was older thing. Initially I just surpressed errors from the missing
definitions so far. The language specific things you can do in latex don't
really matter in HTML, web browsers have zero support for hyphenation.

### Expex and linguex

Expex and linguex are linguistic example formatting libraries, this requires
a lot of work but I've only linearised stuff so far to get rid of messages.

### Flammie.cls

I have a custom class for doing authors preprints, postprints etc. Use it to
make the note and refer to upstream versions and open access policies mainly.

## Style

I reused stuff from the internet: 
* [latex.css](https://github.com/vincentdoerig/latex-css/blob/master/style.css)
* [LaTeX.now.sh](https://latex.now.sh/)
* [Licensed under
   MIT](https://github.com/vincentdoerig/latex-css/blob/master/LICENSE)

and combined it with default latexml css.
