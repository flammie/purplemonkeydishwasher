%% This is an article class I use to create my custom pre-, post-print published
%% articles, proper open and free access articles and such to my web site.
%% Basically it overrides default maketitle to print some extra notes and uses
%% my default settings otherwise

\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{flammie}[2014/01/10 v0.1]

% settings
\newcommand{\flammie@layout}{0}
\newcommand{\flammie@version}{0}

% flammie options
\DeclareOption{screen}{
    \renewcommand{\flammie@layout}{0}
}
\DeclareOption{kindle}{
    \renewcommand{\flammie@layout}{1}
}
\DeclareOption{private}{
    \renewcommand{\flammie@version}{0}
}
\DeclareOption{free}{
    \renewcommand{\flammie@version}{1}
}
\DeclareOption{preprint}{
    \renewcommand{\flammie@version}{2}
}
\DeclareOption{postprint}{
    \renewcommand{\flammie@version}{3}
}

% article options
\DeclareOption{draft}{
    \PassOptionsToClass{\CurrentOption}{article}
}
\DeclareOption{final}{
    \PassOptionsToClass{\CurrentOption}{article}
}
\DeclareOption{10pt}{
    \PassOptionsToClass{\CurrentOption}{article}
}

% fallback
\DeclareOption*{
    \ClassWarning{flammie}{Unknown option \CurrentOption}
}

% defaults
\ExecuteOptions{10pt}

\ProcessOptions\relax

% select base class
\ifx\flammie@layout\@undefined%
\LoadClass[a4paper]{article}
\else\ifcase\flammie@layout% 0 = default
\LoadClass[a4paper]{article}
\or % 1 = kindle
\LoadClass[b5paper]{article}
\fi\fi

% fancy header for pubrights
\RequirePackage{fancyhdr}
\pagestyle{fancy}

\fancyhead[LO,RE]{\thepage}
\fancyfoot[C]{
\ifx\flammie@version\@undefined%{
        Unpublished draft
\else\ifcase\flammie@version% 0 = private
        Unpublished draft
\or% 1 = free
        Free publication
\or% 2 = preprint
        Author's pre-print draft.
\or% 3 = postprint
        Author's post-print draft.
\fi\fi
}

% new commands
\newcommand{\footnotepubrights}[1]{
    \footnote{
\ifx\flammie@version\@undefined%{
        This is Tommi A Pirinen's unpublished draft version of an article for
        private reviews. If you found this from the Internet, report to author.
\else\ifcase\flammie@version% 0 = private
        This is Tommi A Pirinen's unpublished draft version of an article for
        private reviews. If you found this from the Internet, report to author.
\or% 1 = free
        This article has a free/open publication licence; this particular
        version is Tommi A Pirinen's draft version.
\or% 2 = preprint
        This version is Tommi A Pirinen's pre-print draft. The official
        publication may differ.
\or% 3 = postprint
        This version is Tommi A Pirinen's post-print draft. The official
        publication may differ.
\fi\fi
        This version uses my own documentclass instead of official
        publication's, if any.
\ifx\flammie@layout\@undefined\relax\else\ifcase\flammie@layout% 0 = screen
        This version is optimised for screen reading.
\or% = kindle
        This version is optimised for small screen readers.
\fi\fi
    #1}
}

% My packages
\RequirePackage{polyglossia}
\RequirePackage{fontspec}
\RequirePackage{xunicode}
\RequirePackage{xltxtra}
\RequirePackage{url}
\RequirePackage{hyperref}
\setmainfont[Mapping=tex-text]{Liberation Serif}

% end input
\endinput
