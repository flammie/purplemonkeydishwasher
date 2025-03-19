
perl_version=5.40
prefix=/usr
libdir=${prefix}/lib64
perldir=${libdir}/perl5/vendor_perl/${perl_version}
homeperl=${HOME}/perl5/lib/perl5

install-home:
	install -d ${homeperl}/LaTeXML/Package/
	install -m 644 flammie.cls.ltxml ${homeperl}/LaTeXML/Package/
	install -m 644 polyglossia.sty.ltxml ${homeperl}/LaTeXML/Package/
	install -m 644 expex.sty.ltxml ${homeperl}/LaTeXML/Package/
	install -m 644 linguex.sty.ltxml ${homeperl}/LaTeXML/Package/

install:
	install -d ${perldir}/LaTeXML/Package/
	install -m 644 flammie.cls.ltxml ${perldir}/LaTeXML/Package/
	install -m 644 polyglossia.sty.ltxml ${perldir}/LaTeXML/Package/
	install -m 644 expex.sty.ltxml ${perldir}/LaTeXML/Package/
	install -m 644 linguex.sty.ltxml ${perldir}/LaTeXML/Package/
