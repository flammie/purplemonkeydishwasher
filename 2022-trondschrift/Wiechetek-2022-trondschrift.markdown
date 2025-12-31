

# Mii *eai leat gal vuollánan—Vi *ha neimen ikke gitt opp: 
 En hybrid grammatikkontroll for å rette kongruensfeil

<!-- new command \shorttitle -->

**Authors:** Linda Wiechetek<span class='math'>^1</span>,  Flammie A Pirinen<span class='math'>^1</span>,  Børre Gaup<span class='math'>^1</span>,
Chiara Argese<span class='math'>^2</span>,  Thomas Omma<span class='math'>^1</span>

<span class='math'>^1</span>Divvun - UiT Norges Arktiske Universitet 
 <span class='math'>^2</span>Giellatekno - UiT Norges Arktiske Universitet








\setmainlanguage[variant = bokmal]{norwegian}
<!-- set main language english -->

\pghyphenation[variant = bokmal]{norwegian}{fram-halds-skulen}

<!-- new command \samit --> 
<!-- begin document -->
<!-- set counter page 287 -->
<!-- make title -->


**Abstract:**




<span xml:lang="en">

Machine learning is the dominating paradigm in natural language processing
nowadays.  It requires vast amounts of manually annotated or synthetically
generated text data.  In the *GiellaLT* infrastructure, on the other
hand, we have worked with rule-based methods, where the linguistis have full
control over the development the tools.  In this article we uncover the myth
of machine learning being cheaper than a rule-based approach by showing how
much work there is behind data generation, either via corpus annotation or
creating tools that automatically mark-up the corpus.  Earlier we have shown
that the correction of grammatical errors, in particular compound errors,
benefit from hybrid methods.  Agreement errors, on the other other hand, are
to a higher degree dependent on the larger grammatical context.  Our
experiments show that machine learning methods for this error type, even
when supplemented by rule-based methods generating massive data, can not
compete with the state-of-the-art rule-based approach.

</span>

<!-- end abstract -->

## Innledning

Den digitale verdenen vi lever i krever verktøy som håndterer språk.  Mens dette
blir oppfattet som en selvfølge for de store språkene som engelsk, spansk og en
rekke andre majoritetsspråk, er realiteten for minoritetsspråk en helt annen.
De fleste minoritetsspråk mangler både tastatur for å kunne skrive språket, og
ordanalyse, for ikke å snakke om stavekontroll, tekst-til-tale og
maskinoversetting.  Nordsamisk er et av de språkene som har verktøy for både
morfologisk og syntaktisk analyse, maskinoversetting og stavekontroll, og det
jobbes stadig vekk med å utvikle nye verktøy.  Ett av verktøyene det er behov
for er en grammatikkontroll som kan være med på å øke skriftlig språkkompetanse
og dermed føre til økt bruk av samisk på nettet og i den daglige skriftlige
kommunikasjonen (dvs. på sosiale medier, epost, osv.).

Nordsamisk er et finsk-ugrisk språk som snakkes i Norge, Sverige og Finland og
har omtrent 25 700 talere [(cites: Ethnologue2018)](#Ethnologue2018).  Språktypologisk er det et
syntetisk språk, der de fleste ordklassene, f.eks. substantiv og adjektiv,
bøyes etter kasus, person, tall og mer.  Samisk er et minoritetsspråk som
konkurrerer med majoritetsspråket i et flerspråklig samfunn og trenger derfor
hjelpemidler som fremmer skriftspråket—både i opplæring og administrativ
sammenheng.

I denne artikkelen drøfter vi en av de mest frekvente feiltypene i nordsamisk:
kongruensfeil mellom subjekt og verbal.  Deretter tar vi opp den metodiske
bakgrunnen for å lage en grammatikkontroll som kan rette slike feil.  I neste
seksjon presenteres en maskinlæringsbasert (*NeuSam*) og en regelbasert
(*GramDivvun*) modell.  Disse blir diskutert og evaluerert i siste delen
av artikkelen.

Den regelbaserte framgangsmåten har fordelen at man kan jobbe med veldig lite
tekst (tilgangen på store mengder tekst er ofte en av utfordringene for
minoritetsspråk) og ha kontroll over hva de håndskrevne reglene gjør.
Dekningsgraden av ulike feiltyper begrenses til de feilene man har jobbet med.
Maskinlæringsmodeller behøver mye data for å bli bra. Dette kan være en
utfordring for språk som samisk som ikke har tilstrekkelig med data og samtidig
en rik morfologi som fører til at de enkelte formene blir sjeldnere.  Data som
grammatikkontroll blir trent på må i tillegg inkludere feiloppmerking, og
feiloppmerking er en tidkrevende jobb. De fleste tilnærminger velger derfor å
lage et syntetisk feilkorpus nettopp pga den betydelige
ressursbruken. [(cites: Milkowski2007automated,dahlmeier-etal-2013-building)](#Milkowski2007automated,dahlmeier-etal-2013-building)
Samtidig kan maskinlæringsbaserte metoder ha større dekningsgrad for feil man
ikke har jobbet med spesifikt. Vi har oppnådd gode resultater med maskinlæring
for særskrivingsfeil, dvs. lokale
grammatikkfeil [(cites: Wiechetek-etal-2021-rules)](#Wiechetek-etal-2021-rules).

Vi ønsker derfor å undersøke nytten og begrensningene metoden har for andre
feiltyper og muligheten for å  kombinere maskinlæringsbaserte og regelbaserte
metoder for å lage en bedre grammatikkontroll.


Tekstdata som er tilgjengelig digitalt er stort sett samlet i det nordsamiske
korpuset SIKOR [(cites: sikor_06.11.2018)](#sikor_06.11.2018), og bare en liten del er merket opp for
grammatikkfeil.  Nordsamisk har en relativt ny skriftnormering og det er
varierende skriftlig kompetanse blant skribentene. I tillegg har retteverktøy
ikke vært tilgjengelig så lenge. Derfor inneholder korpuset mange flere skrive-
og grammatikkfeil enn et typisk majoritetsspråkskorpus.  Samisk har også en rik
morfologi, som betyr at det er mange ordformer og at man trenger enda mer tekst
for å dekke alle ordformene.

Dette står i kontrast til store språk der morfologien er relativt enkel, og
teksttilfanget er stort og representativt for hele språket.  Man fanger lett opp
alle ordformer, og man har rik tilgang til språkets syntaks i et slikt
teksttilfang.  Med et slikt bakgrunnsmateriale man kan lage nevrale nettverk som
blir relativt pålitelige fordi ressursene modellen lages på er basert på et
allsidig og representativt materiale.  For å kompensere for datamangelen har vi
derfor laget et nevralt nettverk (maskinlæring) (*NeuSam*) som benytter
seg av syntetiske data. Dataene har vi konstruert ved hjelp av regelbasert
morfosyntaktisk analyse for å erstatte korrekte former med feilaktige. Etterpå
blir dataene filtrert av regelbaserte verktøy—den nordsamiske
grammatikkontrollen *GramDivvun*, slik at de syntetiske dataene bare
inneholder reelle feil.

## Problemstilling

Vi tar utgangspunkt i automatisk feilretting i nordsamisk.  Den første
nordsamiske grammatikkontrollen *GramDivvun* har blitt utviklet siden
2012 og er basert på håndskrevne regler [(cites: Wiechetek2012constraint)](#Wiechetek2012constraint), og ble
offentlig lansert i 2020.  Arbeidet til *GramDivvun* er riktignok ikke
bare et verktøy for en stor mengde grammatikkfeil på alle områder, dvs. fra
ekteordsfeil, til særskrivings- og samsvarsfeil, men også et forskingsresultat
for variasjonen i og hyppigheten av nordsamiske grammatikkfeil.  Ekteordsfeil er
korrekt skrevne ord som er brukt i feil sammenheng. De er vanligvis basert på
enten ortografisk eller fonetisk likhet (f.eks. *å* vs. *og*).  I
denne artikkelen fokuserer vi på retting av samsvarsfeil mellom subjekt og
verbal av samme type som i eksempel [(see: samsvar1)](#samsvar1).  Samsvarsfeil er en
arketypisk grammatikkfeil som er tilstede i mange språk og som krever en analyse
av hele setningen. I motsetning til retting av engelske samsvarsfeil i
eksempel [(see: samsvar1)](#samsvar1), slik [(cites: ng-etal-2013-conll)](#ng-etal-2013-conll) tar for seg, er samiske
samsvarsfeil langt mer komplekse.  Årsaken til dette er at samisk har mange
flere verbformer enn engelsk og kombinasjoner av tall (entall, totall, flertall)
og person (1.,2.,3.) som må kongruere med verbet. I det samiske
eksemplet [(see: samsvar2)](#samsvar2) (footnote: Alle samiske eksempler er tatt fra
SIKOR.) (footnote: Alle eksemplene følger Leipzig Glossing konvensjonene:
<http://www.eva.mpg.de/lingua/resources/glossing-rules.php>) ser man også at
det er flere faktorer som må tas hensyn til når subjektet er sammensatt.
Subjektet innholder både det personlige pronomenet *mii* i første person
flertall og et substantiv i nominativ flertall.  Verbet kongruerer med
pronomenet og ikke med flertallssubstantivet, det burde derfor være
*áigut* isteden for *áigot*. Dette blir synlig på samisk, men ikke
på engelsk siden verbformene i *we have* og *they have* er
homonyme.

**Linguistic examples:**

People still ***prefers** to bear the risk and allow their pets to have maximum freedom.<a id="samsvar1">(¶ samsvar1)</a>

**Linguistic example group:**

 <span style='text-underline: thin black single'>Mii**</span> sámit maid ***áigot** gullot.<a id="samsvar2">(¶ samsvar2)</a>

<span style='font-variant: small-caps'>1pl</span> same<span style='font-variant: small-caps'>.3pl</span> også vil<span style='font-variant: small-caps'>.3pl</span> høre<span style='font-variant: small-caps'>.pass.inf</span>

‘Vi samer vil også bli hørt’

Kongruens i nordsamisk gjelder kasus, tall og person, avhengig av kontekst.  I
nordsamisk er det kongruens mellom subjekt (som er i nominativ) og verb, verb og
subjektspredikat, demonstrative pronomener/numeraler og substantiv, og
relativpronomen og anafora. [(cites: Nickel1994samisk[s.509ff.])](#Nickel1994samisk) (footnote: subjekt
og verbal (tall og person—Gal *mun boađán*), verbal og
utfyllningspredikativ (Olmmái *lea rikkis*), mellom predikativer (Mus lea
*juolgi bávččas*), objekt og objektpredikativ, relativsetninger (Dat
*olmmoš, gii* áigu boahtit.), sammenligning og apposisjoner,
(*Máret* lea liikka stuoris go *don* og Oidnet go don
*Mihkkala*, min nuoramus *bártni*)?)

En *kongruensfeil* forutsetter en finitt verbform som ikke samsvarer i
tall og person med subjektet som hører til verbalet. Subjektet kan stå enten til
venstre eller til høyre for verbalet, og det kan være andre setningsledd mellom
subjektet og verbalet.  I det følgende eksemplet [(see: samsvar3)](#samsvar3) blir subjektet
*makkár váikkuhusat* ‘hvilken konsekvenser’ og verbalet *ledje*
‘var’ avbrutt av hovedsetningen *jáhkát don* ‘tror du’. I
eksempelsetning [(see: samsvar4)](#samsvar4) derimot er det finitte verbet til venstre for
subjektet bare en hovedsetning som introduserer en bisetning uten en
subjunksjon. Det er *liikojedje* som er verbalet til *mánát*
‘barna’.  I eksempelsetning [(see: samsvar5)](#samsvar5) er det en relativsetning mellom
subjektet *máŋgasat* ‘mange’ og verbalet *gehččet* ‘de ser’.

**Linguistic example group:**

 <span style='text-underline: thin black single'>Makkár**</span> <span style='text-underline: thin black single'>váikkuhusat**</span> jáhkát don **ledje** dáid lágain sidjiide [...]<a id="samsvar3">(¶ samsvar3)</a>

hvilken konsekvens<span style='font-variant: small-caps'>.nom.pl</span> tro<span style='font-variant: small-caps'>.2sg</span> <span style='font-variant: small-caps'>2sg</span> være<span style='font-variant: small-caps'>.pst.3pl</span> disse<span style='font-variant: small-caps'>.gen</span> lov<span style='font-variant: small-caps'>.loc.pl</span> de<span style='font-variant: small-caps'>.ill.pl</span>

‘Hvilke konsekvenser tror du disse lovene hadde for dem [...]’

**Linguistic example group:**

 *Orui* <span style='text-underline: thin black single'>mánát**</span> **liikojedje** oaidnit bihtá.<a id="samsvar4">(¶ samsvar4)</a>

virke<span style='font-variant: small-caps'>.pst.3sg</span> barn<span style='font-variant: small-caps'>.pl.nom</span> like<span style='font-variant: small-caps'>.pst.3pl</span> se forestilling<span style='font-variant: small-caps'>.acc</span>

‘Det virket som om barna likte å se forestillingen.’

**Linguistic example group:**

Sávan <span style='text-underline: thin black single'>máŋgasat**</span>, geat eai leat sápmelaččat, **gehččet** dán dokumentára<a id="samsvar5">(¶ samsvar5)</a>

ønske\textit.{1sg} mange<span style='font-variant: small-caps'>.pl</span>, som<span style='font-variant: small-caps'>.nom.pl</span> ikke<span style='font-variant: small-caps'>.3pl</span> være same<span style='font-variant: small-caps'>.nom.pl</span>, se<span style='font-variant: small-caps'>.pl3</span> denne<span style='font-variant: small-caps'>.acc</span> dokumentar<span style='font-variant: small-caps'>.acc</span>

‘Jeg ønsker at mange som ikke er samer, ser denne dokumentaren’

I tillegg til at det kan finnes flere verb som er potensielle verbalkandidater
til et subjekt, kan det være ordformer som bare ser ut som finitte verb, men
ikke er det. Dette kan skyldes homonymi med finitte verb eller ekteordsfeil.
Formen *erret* ‘skille’ i eksempelsetning [(see: samsvar6)](#samsvar6) er egentlig en
ekteordsfeil for adverbet *earret* ‘bortsett fra’. Men formen har to
verbanalyser, både 1. person flertall og 2. person entall. Det kunne altså
tenkes at det er verbalet til *sii* ‘de’.

**Linguistic example group:**

Guossit geat áigot leat sámediggeviesus, ***erret** sii geat áigot leat publikumareálan<a id="samsvar6">(¶ samsvar6)</a>

gjest<span style='font-variant: small-caps'>.nom.pl</span> som<span style='font-variant: small-caps'>.nom.pl</span> vil<span style='font-variant: small-caps'>.3pl</span> være Sametinghus<span style='font-variant: small-caps'>.loc</span>, skille<span style='font-variant: small-caps'>.1pl;2sg</span> <span style='font-variant: small-caps'>3pl</span> som vil<span style='font-variant: small-caps'>.3pl</span> være publikumsareal<span style='font-variant: small-caps'>.loc</span>

‘Gjestene som vil være i Sametingshuset, bortsett fra de som skal være i publikumsarealet’

Det finnes også systematiske homonymirelasjoner mellom forskjellige former som
er presentert i tabell [(see: systematiskhomonymi)](#systematiskhomonymi).  Det er for eksempel noe
homonymi mellom perfektum partisipp og første person entall, f.eks.
*orron* ‘jeg var; har vært’.  Alle infinitiver er homonyme med første
person presens flertallsverbformer. Infinitiver av ulikestavelses verb og
*leat* ‘å være’ er også homonyme med tredje person flertall.  Tredje
person presens flertall samsvarer også med andre person preteritum entall ved
alle verb bortsett fra *leat* ‘være’.  Videre samsvarer 1. person
presens totall og 3. person preteritum flertall bortsett fra *leat*
‘være’, ulikestavelsesverb og sammendradde verb.  Første person preteritum
entall samsvarer med perfektum partisipp-formen ved verb som ender på -ut,
f.eks.  *gorgŋon* ‘jeg har klatret’.  I tillegg gjelder denne homonymien
for *leat* ‘være’, ulikestavelses- og sammendradde verb.  Noen verb som
har endelsen *-ut* har for eksempel passive eller inkoative 3. person
entallsformer som er homonyme med aktive 3. person flertallspreteritumsformer,
f.eks. *orro* ‘hun/han blir boende, de bodde’.



**Table:**[htb]
<!-- centering -->
<!-- small -->


| **Form**  |  **homonyme former** |
| ---- | ---- |
| <span style='font-variant: small-caps'>infinitiv</span>  |  \{1. p. flt. / 3. p. flt. presens, 2. p. ent. presens \} |
| <span style='font-variant: small-caps'>perfektum partisipp</span>  |  \{1. p. ent. preteritum\} |
| <span style='font-variant: small-caps'>1DU presens</span>  |  \{3. p. flt. preteritum \} |
| <span style='font-variant: small-caps'>3. p. flt. preteritum</span>  |  \{3. p. ent. presens passiv \} |
| <span style='font-variant: small-caps'>bokte</span> ‘via’  |  \{boktit ‘vekke’ 3. p. flt. preteritum \} |
| <span style='font-variant: small-caps'>lávlu</span> ‘sanger’  |  \{lávlut ‘synge’ 3. p. ent. presens\} |
| <span style='font-variant: small-caps'>...</span>  |  |

(Caption: Eksempler på systematiske og idiosynkratiske homonymier<a id="systematiskhomonymi">(¶ systematiskhomonymi)</a>)
<!-- end table -->


I tillegg til dette finnes det ytterlige idiosynkratiske homonymier, f.eks.
*bokte* ‘via’ som er både en postposisjon og første person totall og
tredje person flertall av *boktit* ‘vekke’.  Andre former er
derivasjoner, for eksempel *lávlu* som har en rekke med
substantivanalyser (‘sanger’) og tredje person entall form av *lávlut*
‘synge’.

I noen tilfeller er også subjektshomonymi relevant, slik som i
setning [(see: samsvar16)](#samsvar16), der tidsskriftet *Dieđut* er homonymt med
flertallssubstantivet *dieđut* ‘nyheter’ og basert på det kunne det
tenkes at verbformen må være 3. person flertall.

**Linguistic example group:**

 <span style='text-underline: thin black single'>Dieđut**</span> **lea** máŋggadieđalaš čála-ráidu [...]<a id="samsvar16">(¶ samsvar16)</a>

Dieđut<span style='font-variant: small-caps'>.nom.sg</span>;nyhet<span style='font-variant: small-caps'>.pl</span> være<span style='font-variant: small-caps'>.3sg</span> tverrvitenskapelig skriftserie 

‘Dieđut {er} en tverrvitenskapelig skriftserie’

Det er ikke bare homonymi som kan føre til feiltolkinger av setningen. En del
syntaktiske fenomen bidrar til utfordringene. En av de største årsakene til
unntak er koordinerte subjekt. Mens verbalet *ledje* i
eksempelsetning [(see: samsvar7)](#samsvar7) tar hensyn til både første, andre og tredje
elementet i koordinasjonen, er det i de fleste tilfellene tillatt med både 3.
person entall eller 3. person flertall.  Setning [(see: samsvar7)](#samsvar7) koordinerer
konkrete personer, i [(see: samsvar8)](#samsvar8) er det derimot mer abstrakte eller
uspesifiserte begrep som er koordinert.


**Linguistic example group:**

 <span style='text-underline: thin black single'>Persson, Åberg ja Granberg**</span> **ledje** dat golbma buoremusa juohke vuodjimis.<a id="samsvar7">(¶ samsvar7)</a>

{Persson, Åberg og Granberg} være<span style='font-variant: small-caps'>.pst.3pl</span> de tre beste hver kjøring<span style='font-variant: small-caps'>.loc</span>

‘Persson, Åberg og Granberg {var} de tre beste i hver kjøring.’

I eksempelsetning [(see: samsvar8)](#samsvar8) inneholder det koordinerte subjektet
*man ollu riggodagat ja ruhta* et flertalls- og et entallssubstantiv.
Verbet *manai* er derimot i 3. person entall. Både 3. person entall og
3. person flertall er tillatt.

**Linguistic example group:**

 [...] go sii oidne man ollu riggodagat ja <span style='text-underline: thin black single'>ruhta**</span> dokko **manai**.<a id="samsvar8">(¶ samsvar8)</a>

[...] når <span style='font-variant: small-caps'>3pl</span> se<span style='font-variant: small-caps'>.pst.3pl</span> hvor mye rikdom<span style='font-variant: small-caps'>.nom.pl</span> og penger<span style='font-variant: small-caps'>.nom.sg</span> dit gå<span style='font-variant: small-caps'>.pst.3sg</span>

‘[...] når de så hvor mye rikdom og penger som gikk dit.’

I setning [(see: samsvar22)](#samsvar22) oppfattes de koordinerte nominalfrasene i subjektet
som en logisk enhet, og bare det nærmeste elementet samsvarer med det finitte
verbet. Dessuten er samsvar i koordinasjon avhengig av semantisk kategori til
substantivene. Ifølge [(cites: Nickel1994samisk)](#Nickel1994samisk) &lt;&lt;står verbalet i *entall*
[hvis subjektsordene er *navn på stoffer*]. [...] Hvis subjektsordene
er *abstrakte begrep* som nært hører sammen, står verbalet i
*entall*.&gt;&gt; (s.512)

**Linguistic example group:**

Sihke jierbmi ja <span style='text-underline: thin black single'>ipmárdus**</span> **lea** buorre su iežas adnui.<a id="samsvar22">(¶ samsvar22)</a>

Både klokhet og forståelse være<span style='font-variant: small-caps'>.3sg</span> bra <span style='font-variant: small-caps'>3pl.gen</span> eget  bruk<span style='font-variant: small-caps'>.ill</span>

‘Både klokhet og forståelse er bra til sitt bruk.’

Hvis koordinasjonen derimot inneholder et personlig pronomen, er det flertalls-
eller totallsformer av samme person som kreves, for eksempel **leimmet**
‘vi var’ i eksempelsetning [(see: samsvar9)](#samsvar9). Det samme gjelder relativpronomener
med et personlig pronomen som antesedent, *midjiide* ‘til oss’ i
eksempelsetning [(see: samsvar15)](#samsvar15), der verbalformen blir 1. person flertall
istedenfor 3. person flertall som relativpronomenet.


**Linguistic example group:**

Oahpaheaddjit **leimmet** fas <span style='text-underline: thin black single'>Isak Johansen, Johan Jernsletten ja mun**</span>.<a id="samsvar9">(¶ samsvar9)</a>

lærer<span style='font-variant: small-caps'>.nom.pl</span> være<span style='font-variant: small-caps'>.pst.1pl</span> igjen {Isak Johansen, Johan Jernsletten og <span style='font-variant: small-caps'>1sg</span>}

‘Det {var} Isak Johansen, Johan Jernsletten og jeg som var lærerne.’

**Linguistic example group:**

Seamma guoská <span style='text-underline: thin black single'>midjiide geat**</span> **bargat** láhččit rámmaeavttuid juohkehačča ovdáneapmái.<a id="samsvar15">(¶ samsvar15)</a>

samme gjelde<span style='font-variant: small-caps'>.3sg</span> {<span style='font-variant: small-caps'>1pl.ill</span> som<span style='font-variant: small-caps'>.nom.3pl</span>} jobbe<span style='font-variant: small-caps'>.1pl</span> tilrettelegge<span style='font-variant: small-caps'>.inf</span> rammevilkår<span style='font-variant: small-caps'>.acc.pl</span> enkelte<span style='font-variant: small-caps'>.gen</span> utvikling<span style='font-variant: small-caps'>.ill</span>

‘Det samme gjelder oss som {jobber} med å tilrettelegge rammevilkår for den enkeltes utvikling.’


Når verbalet er kopulaverbet *leat* ‘være’ og det dreier seg om en
habitiv eller adverbialkonstruksjon som i [(see: samsvar12)](#samsvar12), så samsvarer det bare
med det nærmeste leddet. [(cites: Nickel1994samisk[s.512])](#Nickel1994samisk) (footnote: &lt;&lt;Hvis predikativet
består av flere sidestilte ord i nominativ, så er det vanligvis samsvar i tall
mellom verbalet og det ordet i predikativet som står nærmest. Dette gjelder
setninger med habitiv eller adverbial i nominatdelen&gt;&gt; (p.512)) I den følgende
konstruksjonen [(see: samsvar12)](#samsvar12) er det bare entall som er mulig siden det dreier
seg om en konstruksjon med et stedsadverbial i begynnelsen, *dáppe*
‘her’.

**Linguistic example group:**

Mun dieđán dáppe **lea** <span style='text-underline: thin black single'>kultuvra**</span> ja árbevierru girkostallat.<a id="samsvar12">(¶ samsvar12)</a>

<span style='font-variant: small-caps'>1sg</span> vite<span style='font-variant: small-caps'>.1sg</span> her være<span style='font-variant: small-caps'>.3sg</span> kultur<span style='font-variant: small-caps'>.nom.sg</span> og tradisjon<span style='font-variant: small-caps'>.nom.sg</span> gå.i.kirken<span style='font-variant: small-caps'>.inf</span>

‘Jeg vet at her er det kultur og tradisjon å gå i kirken.’

Visse typer veldig vanlige skrivefeil (ekteordsfeil) kan komplisere søket etter
kongruensfeil.  I følgende setning [(see: samsvar17)](#samsvar17) er det finitte verbet
korrekt.  Men i og med at *diehttit* ‘å vite’ inneholder en skrivefeil
(to t-er istedenfor en), blir den mente infinitiven et flertallssubstantiv.
Dermed blir det en mulig flertallssubjektskandidat for det finitte verbet, som
kunne tolkes som en kongruensfeil—dvs. at det burde være 3. person flertall
istedenfor 3. person entall.

**Linguistic example group:**

 {Ovddamearkka dihte} mo *diehttit **mieđiha** go buohcci vai lea go son duođaid nuppi oaivilis.<a id="samsvar17">(¶ samsvar17)</a>

{For eksempel} hvordan viter<span style='font-variant: small-caps'>.nom.pl</span> samtykke<span style='font-variant: small-caps'>.3sg</span> <span style='font-variant: small-caps'>qst</span> syk eller være<span style='font-variant: small-caps'>.3sg</span> <span style='font-variant: small-caps'>qst</span> <span style='font-variant: small-caps'>3sg</span> egentlig annen mening<span style='font-variant: small-caps'>.loc</span>

‘For eksempel, hvordan skal man vite om den syke {samtykker} eller om han egentlig har en annen mening.’

En konstruksjon der det kan være vanskelig å finne kongruensfeil, er
asymmetriske subjektpredikats\-konstruksjoner der subjektet og predikativet ikke
har samme tall, som vist i eksempelsetning [(see: samsvar30)](#samsvar30). På språk der
subjektet kan være pre- eller postverbalt, slik som i nordsamisk, kan det være
vanskelig å identifisere subjektet. [(cites: Lorusso2019asymmetries)](#Lorusso2019asymmetries) nevner
utfordringene i NLP-applikasjoner som for eksempel parsere eller
maskinoversetting. Verbalet i italiensk samsvarer med subjektet uavhengig av
ordstillinga, på engelsk samsvarer verbalet med den preverbale nominalfrasen som
i eksempel [(see: agreement)](#agreement). [(cites: Lorusso2019asymmetries)](#Lorusso2019asymmetries)

**Linguistic example group:**

Davviriikkaid <span style='text-underline: thin black single'>sápmelaččat**</span> ***lea** unna minoritehta [...]<a id="samsvar30">(¶ samsvar30)</a>

nordområde<span style='font-variant: small-caps'>.gen.pl</span> same<span style='font-variant: small-caps'>.nom.pl</span> være<span style='font-variant: small-caps'>3p.sg</span> liten minoritet<span style='font-variant: small-caps'>.nom.sg</span>

‘Nordens samer er en liten minoritet [...]’

**Linguistic examples:**

 <a id="agreement">(¶ agreement)</a>
\a.  the pictures are/*is the cause.
b.   the cause *are/is the pictures

## Bakgrunn

### Relatert forskning

Maskinlæringsmetoder som ikke krever lingvistisk ekspertise dominerer per idag
moderne språkteknologi (f.eks. [(cites: chollampatt2018multilayer,boyd2018using)](#chollampatt2018multilayer,boyd2018using)).
Fokuset i maskinlæring har vært på maskinoversetting og andre typer verktøy.
Maskinlærte stavekontroller skiller vanligvis ikke på vanlige skrivefeil og
grammatiske feil.  I det siste har store datamengder ført til at resultatene har
bedret seg noe og medført at man har kunnet laget mer avanserte grammatiske
verktøy som blir brukt av et bredt publikum.

Det er få eksempler på grammatikkontroller som er basert på nevrale nettverk som
er i daglig bruk og er veldokumentert. Noen av de mest populære systemene i bruk
er fortsatt regelbasert, slik som
*LanguageTool* (footnote: <https://languagetool.org>) (basert på åpen
kildekode). *Grammarly* (footnote: <https://grammarly.com>), som er
lukket programvare, bruker maskinlæringsmetoder til en viss
grad (footnote: <https://www.grammarly.com/blog/engineering/grammarly-nlp-building-future-communication/>).

På begynnelsen av 90-tallet introduserte Fred Karlsson konseptet
føringsgrammatikk (Constraint Grammar).  Denne teknologien har produsert gode
tekstprosesseringsverktøy, bl.a. grammatikkontroller, som har blitt godt mottatt
og brukt i mange språksamfunn [(cites: Arppe2000ei,Birn2000detecting,Hagen2001det)](#Arppe2000ei,Birn2000detecting,Hagen2001det).
I *GiellaLT*-infrastrukturen blir det utviklet føringsgrammatikker der
lingvisten har kontroll over hvordan grammatikkontrollene fungerer og hvilke
problem de skal løse. Det er ikke bare tekniske årsaker for metodevalget.
Kunnskapsøkning om grammatikken til det språket som jobbes med, kvalitetssikring
og kontrollerbarhet (grammatikkontrollen gjør det den skal gjøre også ifølge
menneskelige standard) ligger bak preferansen om å jobbe regelbasert.

### Våre ressurser

I dette eksperimentet bruker vi
*GiellaLT*-infrastrukturen (footnote: <https://giellalt.github.io>) for
å lage digitale grammatikker og leksikon og for å lage verktøy som bruker disse
grammatikkene og leksikonene [(cites: moshagen2014open)](#moshagen2014open).  Infrastrukturen er bygd
opp slik at verktøyene  (tastatur, stavekontroller, etc.) er laget på samme måte
for alle språkene, og skiller på denne måten mellom språkspesifikke data og
språkuavhengige metoder.  *GiellaLT* har for tiden repositorier for 136
forskjellige språk—for det meste (sirkumpolære) minoritetsspråk eller andre
mindre språk.  Denne artikkelen bygger på den nordsamiske delen av
infrastrukturen (footnote: <https://github.com/giellalt/lang-sme>) og er et
eksperiment for å eventuelt introdusere nye nevrale metoder til det
språkuavhengige byggesystemet.

For å evaluere og trene den nevrale modellen bruker vi SIKOR.  SIKOR inneholder
ca. 39M ord og består av to korpora:
*GT-Bound* (footnote: <https://gtsvn.uit.no/boundcorpus/orig/sme/>)
(tekster som er dekket av opphavsrett og som er tilgjengelig på forespørsel) og
*GT-Free* (footnote: <https://gtsvn.uit.no/freecorpus/orig/sme/>)
(tekster som er offentlig tilgjengelig).  For å evaluere resultater for både den
regelbaserte og den nevrale modellen, bruker vi et gullkorpus på ca 406 000 ord
som er en del av *GT-Free* og *GT-Bound* og som er oppmerket med
mange forskjellige feiltyper.


## Metodevalg


### Regelbasert metode (*GramDivvun*)

Kongruensfeilretting ved hjelp av håndskrevne regler er basert på endelige
tilstandsautomater (FST) [(cites: beesley2003finite,Pirinen2014state)](#beesley2003finite,Pirinen2014state) og
føringsgrammatikker (Constraint Grammar) [(cites: karlsson1990constraint)](#karlsson1990constraint).  Den
nordsamiske regelbaserte grammatikkontrollen *GramDivvun* retter både
skrive- og mange grammatikkfeil i tillegg til tegnsettings- og formateringsfeil.
*GramDivvun* er bl.a. tilgjengelig som en plugin for Microsoft Office og
Google Docs (footnote: https://divvun.no/no/korrektur/gramcheck.html) og er åpen
kildekode. (footnote: den presise versjonen som er brukt i eksperimentet finnes
her for reproduksjon:
<https://github.com/giellalt/lang-sme/releases/tag/experiment-2022-03-30> se
også
<https://github.com/giellalt/giella-core/releases/tag/experiment-2022-03-30>
og
<https://github.com/giellalt/giella-shared/releases/tag/experiment-2022-03-30>)
Den inkluderer bl.a. en nyere versjon av stavekontrollen fra
2007 (footnote: <http://divvun.no/korrektur/korrektur.html>), cf.
also [(cites: Gaup2005xerox)](#Gaup2005xerox), og seks føringsgrammatikkmoduler, se\
figur [(see: systemarchitecture)](#systemarchitecture).

    
**Figure:**[ht]
    <div style='text-align: center'>
<!-- scalebox .6 [.6] -->
![GramCheckLightFlow.pdf](GramCheckLightFlow.pdf)
(Caption: Modulær struktur av *GramDivvun*<a id="systemarchitecture">(¶ systemarchitecture)</a>)
    </div>
<!-- end figure* -->

Kongruensfeilretting foregår i ‘grammarchecker-release.cg3’-modulen.  45 regler
legger til en samsvarsfeiltag til verbformen som skal rettes. Hver kombinasjon
av person og tall har et eget regelsett som vanligvis består av forskjellige
regler for pre- og postverbal subjektsposisjon.  I tillegg er det spesifikke
regler for passivkonstruksjoner, negasjonskontekster, relativsetninger, kopula,
adposisjoner og koordinerte subjekter.  Regelsettet for pronominale
førstepersonsflertallskontekster er litt mer komplekst siden formen *mii*
er homonymt og kan være både 1. person flertall (‘vi’) og et spørrepronomen i
3. person entall (‘hva’).

Reglene som legger til feiltaggene til en feilaktig verbform har følgende format
(forenklet) og følger ‘Constraint Grammar’-formalismen. Regelen nedenfor (som er
en av 48) går ut i fra en 3. person entallshøyrekontekst.


```
[frame=single,framerule=0.2mm,framesep=3mm,fontsize=<!-- footnotesize -->,baselinestretch=1]
ADD (&kongruensfeiltag)
TARGET finitte verbformer bortsett fra konnegativ/negasjonsverb
IF i høyre kontekst det er et personlig pronomen i 3. person entall
som ikke inneholder en feil
det ikke finnes et annet verb i 3. person entall til høyre for det og
verbet har ingen 3. person entalls-/perf.part.-/konnegativ-/adverbslesing
verbet har ingen 3. person flertallslesing med et koordinert subjekt til høyre
   [...];

```



### Nevral metode (*NeuSam*)


#### Datagenerering (syntetiske feil)<a id="sec:datagenerering">(¶ sec:datagenerering)</a>

Nevrale nettverk krever en stor mengde av parallelt korpus mellom korrekte og
feilaktige setninger.  Siden det kan ta flere år å bygge et slikt korpus, er det
vanlig å generere et feilkorpus. Ulempen med et generert feilkorpus er at det
innebærer en risiko for at feilfordelingen ikke er representativ eller at
feilene kanskje ikke er feil.  Dataene vi bruker i dette eksperimentet kommer
fra SIKOR, og blir viderebehandlet med skript som genererer grammatikkfeil.  Vi
analyserer korpuset med *GramDivvun* og fjerner setninger med feil, for å
deretter introdusere feil ved å forandre på ordformene i dette materialet.
Utfordringene med strategien har vært:


  * For å ikke generere den samme formen som den feilaktige, har vi filtrert bort de introduserte formene som er homonyme (*leat* ‘vi er’, *leat* ‘du er’).
  * Siden datamengden øker eksponensielt om vi erstatter en form med mange andre, spesielt når det er flere verb i setningen, har vi valgt å bare introdusere en feil av gangen i setningen, istedenfor å kombinere alle variantene.


Den korrekte setningen [(see: doarjjui1)](#doarjjui1) som inneholder et 3. person
entallssubjekt og en 3. person entallsverbform kan brukes for å generere opptil
8 setninger med en syntetisk feil (eksempel [(see: doarjjui2)](#doarjjui2)). Dette gjøres ved å
erstatte den korrekte verbformen med forskjellige feilaktige former som er
forskjellig i person og tall (som ikke er homonyme med den rette formen).

**Linguistic example group:**

Son **doarjjui** áinnas unnit *giliid.<a id="doarjjui1">(¶ doarjjui1)</a>

<span style='font-variant: small-caps'>3sg</span> støtte<span style='font-variant: small-caps'>.pst.3sg</span> selvfølgelig mindre språk<span style='font-variant: small-caps'>.acc.pl</span>

‘Hun støttet selvfølgelig mindre språk.’

**Linguistic examples:**

 <a id="doarjjui2">(¶ doarjjui2)</a>
\a. Son **dorjot** áinnas unnit giliid.
b.  Son **doarjjuiga** áinnas unnit giliid.



Vi brukte et skript (footnote: <https://gtsvn.uit.no/hybrid_gramcheck>) som
leser gjennom hver setning i korpuset, og for hver analyse erstatter skriptet
verbformen som kan ha kongruens med et subjekt med andre verbformer som ikke har
kongruens med subjektet. En oversikt av erstatninger som ble gjort vises i
tabell [(see: table:ersetzt)](#table:ersetzt).  I den første gruppen valgte vi bare et verb og
erstattet det med andre former (f.eks tar vi et verb i første person entall og
erstatter det med 2. person entall og 3. person entall, og alle totalls- og
flertallsformene). I den andre gruppen genererte vi frekvente  grammatikkfeil,
som tilsvarer feil basert på vår erfaring med korpussøk.  Ordene i den andre
gruppen har også en begrensing av fonologisk form, f.eks. <span style='font-variant: small-caps'>Ind Prs
Pl3</span> (footnote: vi bruker *GiellaLT* sine analysetaggar som er dokumentert
her: <https://giellalt.github.io/lang-sme/docu-mini-smi-grammartags.html>)
til <span style='font-variant: small-caps'>Imprt Pl2</span>-feil er en feil som oppstår i likestavelsesverb.  Etterpå
filtrerte vi de genererte setningene med *GramDivvun* igjen, slik at vi
bare satt igjen med setninger *GramDivvun* anså for å være feil.
Resultatet er at flesteparten av de syntetiske feilene som vi introduserte, hhv.
94.5% og 86.4%, ikke ble merket som feil av *GramDivvun*, antakeligvis
fordi de er korrekte med formen som ble erstattet. Dette er ikke uvanlig med
tanke på at setninger uten subjekt kan ha korrekte verbformer i alle slags
person-tall kombinasjoner. Vi valgte å bruke *GramDivvun* for å filtrere
setningene etter at vi ved en manuell gjennomgang oppdaget at feilkorpuset som
ble generert for å trene *NeuSam* inneholdt mange setninger som var
korrekte. Siden *GramDivvun* tidligere viste seg å ha god presisjon
valgte vi å redusere feilkilden ved å bare trene *NeuSam* med setninger
*GramDivvun* anser som feil.


**Table:**[htb]
<!-- minipage 0.63\textwidth -->


| ---- | ---- |
| **Analyse** <span class='math'>\rightarrow</span>  |  **Syntetisk** |
| <span style='font-variant: small-caps'>(V) Sg1</span>  |  \{Sg2, Sg3, Du1, Du2, Du3, Pl1, Pl2, Pl3\}  |
| <span style='font-variant: small-caps'>(V) Sg2</span>  |  \{Sg1, Sg3, Du1, Du2, Du3, Pl2\}  |
| <span style='font-variant: small-caps'>(V) Sg3</span>  |  \{Sg1, Sg2, Du1, Du2, Du3, Pl1, Pl2, Pl3\}  |
| <span style='font-variant: small-caps'>(V) Du1</span>  |  \{Sg1, Sg2, Sg3, Du2, Du3, Pl1, Pl2\}  |
| <span style='font-variant: small-caps'>(V) Du2</span>  |  \{Sg1, Sg2, Sg3, Du1, Du3, Pl1, Pl2, Pl3\}  |
| <span style='font-variant: small-caps'>(V) Du3</span>  |  \{Sg1, Sg2, Du1, Du2, Pl1, Pl2, Pl3\}  |
| <span style='font-variant: small-caps'>(V) Pl1</span>  |  \{Sg1, Sg3, Du1, Du2, Du3, Pl2\}  |
| <span style='font-variant: small-caps'>(V) Pl2</span>  |  \{Sg1, Sg2, Sg3, Du1, Du2, Du3, Pl1, Pl3\}  |
| <span style='font-variant: small-caps'>(V) Pl3</span>  |  \{Sg1, Du2, Du3, Pl1, Pl2\}  |
| <span style='font-variant: small-caps'>(V) Ind Prs Pl3</span>  |  <span style='font-variant: small-caps'>Imprt Pl2</span> |
| <span style='font-variant: small-caps'>(Der/Pass V)</span>  |  <span style='font-variant: small-caps'>Imprt Du2</span> |
| {Ind Prs Sg3}  |   |
| <span style='font-variant: small-caps'>(V) Ind Prs Sg3</span>  |  <span style='font-variant: small-caps'>Ind Prt Pl3</span> |

(Caption: Erstatninger for å generere grammatikkfeil; kontekst er i parentes.
    <a id="table:ersetzt">(¶ table:ersetzt)</a>)
<!-- /minipage -->
<!-- minipage 0.28\textwidth -->


| ---- | ---- |
| <!-- bf -->Parameter  |  <!-- bf -->Verdi |
| `train steg`  |  `100,000` |
| `valid steg`  |  `10,000 `|
| `vocab størrelse`  |  `50,000` |
| `seed`  |  `3,435` |
| `encoder type`  |  `brnn` |

(Caption: Parametre gitt til OpenNMT)<a id="table:params">(¶ table:params)</a>
<!-- /minipage -->
<!-- end table -->


#### Trening og testing


**Figure:**
<!-- centering -->
![stuff](stuff)
(Caption: Et diagram av *NeuSam* og treningsprosessen<a id="fig:my_label">(¶ fig:my_label)</a>)
<!-- end figure -->

Vi har brukt OpenNMT-py [(cites: klein2017opennmt)](#klein2017opennmt) for eksperimenteringen
med nevrale nettverk. Vi fulgte metoden som er beskrevet i OpenNMT-py sin
‘tutorial’ (footnote: <https://opennmt.net/OpenNMT-py/quickstart.html>) med
standardparametrene.

90 % av dataene vi samlet i stegene ovenfor ble brukt for å trene modellene. Vi
reformaterte dataene våre slik at de ble tolket som en bokstavbasert modell.
Dette gjorde vi for å unngå OpenNMTs automatiske tokenisering. Disse parametrene
vises også i tabellen [(see: table:params)](#table:params). (footnote: Vi inkluderer hele
konfigurasjonen av opennmt-py og skript til trening i
<https://gtsvn.uit.no/hybrid_gramcheck> ved publisering). Trening av
modellen ble gjort på en GPU-supercomputer fra &lt;&lt;*UNINETT Sigma2—the
National Infrastructure for High Performance Computing and Data Storage in
Norway*&gt;&gt;. Det tok i gjennomsnitt fem timer å generere hver treningsmodell.

Vi har generert to forskjellige nevrale modeller med forskjellige datasett: en
med et større datasett der vi bruker alle syntetisk genererte setninger som
omtalt i seksjonen [(see: sec:datagenerering)](#sec:datagenerering). I den andre lager vi en modell
basert på setninger som etter syntetisk feilgenerering blir filtrert gjennom
*GramDivvun*.  Input til testene av de nevrale modellene er den tiendelen
av vårt genererte korpus som ikke har blitt brukt i treningen av modellene, og
testen vi gjør er å sjekke hvor stor del av dette testsettet som blir merket som
feil. Formelen for nøyaktighet er ganske enkel:
<span class='math'>\mathrm{nøyaktighet}=\frac{\mathrm{korrekte}}{\mathrm{alle}}</span> der
*korrekte* er antall setninger som modellen anser for å inneholde feil,
*alle* er antall setninger i testsettet.


I tabell [(see: tab:accuracy)](#tab:accuracy) ser vi at modellen basert på filtrerte setninger er
mer nøyaktig.  Den større modellen har 9 % dårligere resultat enn den mindre
modellen.  Det betyr at modellen basert på ufilterte setninger egentlig har lært
å fikse feil deler av eller ikke fikser alle feil i nesten 1 av 10 setninger med
syntetiske feil.


**Table:**[htb]
<!-- minipage 0.45\textwidth -->
<!-- centering -->


| \bf{Modell}  |  \bf{Nøyaktighet} |
| ---- | ---- |
| Stor  |  25 % |
| Filtrert  |  37 % |

(Caption: Nøyaktighet av nevrale modeller
    <a id="tab:accuracy">(¶ tab:accuracy)</a>)
<!-- /minipage -->
<!-- minipage 0.45\textwidth -->
<!-- centering -->


| \bf{Modell}  |  \bf{Presisjon}  |  \bf{Dekning}  |  \bf{F-Score} |
| ---- | ---- | ---- | ---- |
| GramDivvun  |  78.50 %  |  43.75 %  |  56.19 |
| NeuSam  |  27.01 %  |  8.21 %  |  12.61 |

(Caption: Evaluering av den regelbaserte og maskinlæringsmodellen
    <a id="tab:accuracy-ekte">(¶ tab:accuracy-ekte)</a>)
<!-- /minipage -->
<!-- end table -->

## Resultater

Vi har evaluert *NeuSam* og *GramDivvun* på det oppmerkede
korpuset på 406 000 ord som er en del av SIKOR.  Korpuset består av mange
administrative og nyhetstekster, litt skjønnlitteratur og en del L2-tekster som
ble samlet inn for spesielle formål. Oppmerkingen fulgte opprinnelig noen
retningslinjer for skrivefeil og fonologiske prosesser, og den har skjedd over
et lengre tidsrom, ca. 15 år.  Etterhvert ble oppmerkingen utvidet og tilpasset
grammatikkontroll og måten evalueringsskriptet er istand til å kjenne igjen
disse feilene på.  Vi følger prinsippet om at bare det som blir rettet blir
merket opp og ikke konteksten for å se feilen.  Vi oppdaget en del inkonsekvent
oppmerking som vi rettet under dette arbeidet. Dette skyldes også at
grammatikkontrollprogrammet kom mange år etter at korpusoppmerkingen startet.
Grammatisk feilkategorisering var ikke helt utarbeidet på det tidspunktet og man
kunne ikke sjekke mot et dataprogram som krever konsekvent oppmerking.


Vi ønsket å sammenligne presisjon og dekning og sjekke om *NeuSam* retter
feil som *GramDivvun* ikke oppdager.  Tabell [(see: tab:accuracy-ekte)](#tab:accuracy-ekte)
viser at *GramDivvun* er betydelig bedre enn *NeuSam* på å finne
kongruensfeil. Man ser også at mange av korreksjonene til *NeuSam* ikke
har noen lingvistisk forklaring, mens mange av korreksjonene til
*GramDivvun* kan være nyttig for brukeren i og med at de viser til en
annen feil i setningen.

I eksempelsetning [(see: earafeaila)](#earafeaila) blir verbformen *livčče* ‘de skulle’
rettet til entall *livččii* ‘hun/han skulle’ fordi subjektet
*Maáŋga mearraolbmáidgirku* inneholder et tallord med en skrivefeil.
Dermed oppfattes bare entallssubstantivet *mearraolbmáidgirku* som
subjekt, og flertallsbetydninga blir tapt.  Dette regnes som en falsk positiv i
evalueringen, men grammatikkontrollen har ‘tenkt’ rett ut i fra den
informasjonen som er tilgjengelig (altså før skrivefeilen blir rettet).

**Linguistic example group:**

 <span style='text-underline: thin black single'>Maáŋga mearraolbmáidgirku**</span> **livčče** vuollebáhcagiin šaddan rahčat [...]<a id="earafeaila">(¶ earafeaila)</a>

{mange sjømannskirke<span style='font-variant: small-caps'>.nom;gen.sg</span>} ville<span style='font-variant: small-caps'>.pot.3pl</span> underskudd<span style='font-variant: small-caps'>.com.pl</span> bli<span style='font-variant: small-caps'>.pastp</span> kjempe<span style='font-variant: small-caps'>.inf</span>

‘Mange sjømannskirker ville kjempet med underskudd [...]’


Falske negativer er det flest av i koordinasjon med to eller flere substantiv,
der det finitte verbet skal være i entall isteden for flertall. Et eksempel
er [(see: koord1)](#koord1), der tredje person flertallsformen *leat* skal rettes til
tredje person entallsformen *lea*. Kongruens i koordinasjon er avhengig
av flere faktorer, blant annet semantisk tilhørighet, syntaks
(kopulakonstruksjoner og adverbialkonstruksjoner behandles forskjellig fra
andre) og pragmatikk (er den introduserte entiteten kjent?).  Grunnen til at
feilen ikke blir oppdaget er at vi ennå ikke laget en regel som retter fra
flertalls- til entallsverb i koordinasjon.

**Linguistic example group:**

Álggahanvahkku prográmmas **leat** <span style='text-underline: thin black single'>almmolaš rahpanbeaivi**</span>, <span style='text-underline: thin black single'>diehtojuohkin Sámi allaskuvlla birra**</span>, <span style='text-underline: thin black single'>fáddarortnet ođđa studeanttaide**</span>.<a id="koord1">(¶ koord1)</a>

startuken<span style='font-variant: small-caps'>.gen</span> program<span style='font-variant: small-caps'>.loc</span> være<span style='font-variant: small-caps'>.3sg</span> {offisiell åpningsdag}, {informasjon Samisk høgskole om}, {fadderordningen nye student<span style='font-variant: small-caps'>.ill.pl</span>}.

‘I startukens program inngår offisiell åpningsdag, informasjon om Samisk høgskole, fadderordningen for nye studenter.’

At *NeuSam* ikke finner flesteparten av de oppmerkede feilene, skyldes
sannsynligvis at treningsmaterialet ikke er representativt nok. Et annet problem
er at når rettingen går galt, blir rettelsen helt uforståelig. Et eksempel er at
samme ordrekkefølge blir repetert uendelig mange ganger *johtá guovllus
sahtá guovllus sahtá guovllus sahtá guovllus sahtá guovll...*. Dette lar seg
fikse ved å endre på lengderestriksjoner for setninger, men følgen er at man
ikke kan rette lengre setninger.


Den større modellen gir følgende feilaktige resultat for eksempel [(see: feil4)](#feil4):
Istedenfor å bare rette verbformen *logat* ‘du leser’ til *lohká*
‘hun/han leser’ blir setningen rettet til [(see: feil5)](#feil5), dvs. *NeuSam* tar
bort hele setningen *logan dál oppalaččat* uten at dette skulle være
lingvistisk fundert.

**Linguistic examples:**


\a.	In dovdda dán ášši, *logan dál oppalaččat,*  **logat** Sámedikki presideanta Egil Olli.<a id="feil4">(¶ feil4)</a>
b.  In dovdda dán ášši,  **lohká** Sámedikki presideanta Egil Olli.<a id="feil5">(¶ feil5)</a>
\c. In dovdda dán ášši, logan dál oppalaččat,  **lohká** Sámedikki presideanta Egil Olli.<a id="feil6">(¶ feil6)</a>


*NeuSam* produserer også noen falske positiver, f.eks. i [(see: feil7)](#feil7)
blir *šaddet* rettet til *šaddá* (3Pl&gt;3Sg), men det burde ikke
rettes siden *stuorát doalut* er et flertallssubjekt.

**Linguistic example group:**

Duogážin manne heastasearvi lea fárus doaluin, lea danin vai **šaddet** stuorát doalut [...]<a id="feil7">(¶ feil7)</a>

bakgrunn<span style='font-variant: small-caps'>.ess</span> hvorfor hesteforening være<span style='font-variant: small-caps'>.3sg</span> med arrangement<span style='font-variant: small-caps'>.loc.pl</span>, være<span style='font-variant: small-caps'>.3sg</span> derfor at bli<span style='font-variant: small-caps'>.3pl</span> stor<span style='font-variant: small-caps'>.comp</span> arrangement<span style='font-variant: small-caps'>.nom.pl</span>

‘Bakgrunnen for at hesteforeningen er med i arrangementet, er at det blir et større arrangement’


## Konklusjon

I denne artikkelen laget vi to maskinlæringsmodeller for å rette kongruensfeil
mellom subjekt og verbal i nordsamisk. Parallelt med dette utviklet vi et
regelsett for slike feil i *GramDivvun*, den eksisterende regelbaserte
grammatikkontrollen.  Vi ville sammenligne resultatene for maskinlæring og
regelbasert metode, både for å få mer klarhet i hvilken metode som bør
foretrekkes for dette formålet og for å se om systemene har styrker på
forskjellige områder og kan kombineres til en hybrid grammatikkontroll.  Vi
ville også forsøke å avdekke myten om at maskinlæring blir billigere enn
regelbaserte metoder, og det mener vi at vi har gjort ved å tydeliggjøre at det
å generere treningsdata må regnes inn i de faktiske kostnadene til metoden.  For
å lage et feiloppmerket treningskorpus for *NeuSam* brukte vi den
regelbaserte modellen *GramDivvun* for å rydde korpuset for støy. Dette
var nødvendig for å etterpå kunne introdusere syntetiske feil.  Uten denne
filteringen blir nøyaktigheten til *NeuSam* 12 prosentpoeng verre.  Det
at den regelbaserte modellen blir brukt for å automatisk generere data viser at
korpuset ikke blir gratis.

Vår hypotese—at regelbaserte metoder kan kompensere for mangel av data, også
for maskinlæringsmodeller—har vist seg å ikke holde stikk når det gjelder
retting av globale grammatikkfeil.  Evalueringen på et ekte korpus (dvs. med
ekte feil i en naturlig distribusjon) i tabell [(see: tab:accuracy)](#tab:accuracy) viser at for
den regelbaserte modellen er presisjonen nesten tre ganger bedre og dekningen
fem ganger bedre enn for den maskinlæringsbaserte modellen. *GramDivvun*
presterer så bra (79% presisjon) at vi har en modell som er til nytte for
språkbrukere i og med at mengden på de falske alarmene er relativt lavt.
*NeuSam* derimot gjør det såpass dårlig på et ekte korpus, med en
presisjon på bare 27% (på testsettet var resultatene tre ganger bedre), at det
ikke kan brukes for å lage en hybrid grammatikkontroll for kongruensfeil.  Det
taler for at det syntetiske feilkorpuset kanskje ikke er representativt nok til
å være et realistisk feilkorpus. I tillegg er det å introdusere ekte
kongruensfeil en oppgave som krever mer enn enkle erstatninger og en enkel
kontekstanalyse. Mange kontekster tillater flere former uten at disse er feil.
Det å introdusere kongruensfeil kan anses som en oppgave som er minst like
vanskelig som, om ikke vanskeligere enn, selve feilfinningen. Dvs. at vi
trenger et verktøy som er like bra som den regelbaserte grammatikkontrollen for
å lage et korpus for en maskinlæringsbasert grammatikkontroll.  Mens
maskinlæringsmetoder fungerer for mer lokale feil som for eksempel
sammensettingsfeil, er det for krevende å lage feilkorpus for mer avanserte
feil.  Dette gir et bra utgangspunkt for framtidig forskning, men med de
nåværende ressursene synes ikke maskinlæring å være den mest lovende metoden for
å lage grammatikkontroller. Den regelbaserte metoden er fortsatt den som gir
best resultat på dette området.

## Godord

Modelleringen av de nevrale nettverkene har blitt utført på maskinene til
UNINETT Sigma2.



# References

* <a id="Ethnologue2018">**Ethnologue2018**</a>:
    * error: <strong style="color: red">missing from bibs</strong>
* <a id="Milkowski2007automated">**Milkowski2007automated**</a>:
    * error: <strong style="color: red">missing from bibs</strong>
* <a id="dahlmeier-etal-2013-building">**dahlmeier-etal-2013-building**</a>:
    * address: Atlanta, Georgia
    * author: Dahlmeier, Daniel  and Ng, Hwee Tou  and Wu, Siew Mei
    * booktitle: Proceedings of the Eighth Workshop on Innovative Use of {NLP
    * month: jun
    * pages: 22–31
    * publisher: Association for Computational Linguistics
    * title: Building a Large Annotated Corpus of Learner English: The {N...
    * url: https://aclanthology.org/W13-1703
    * year: 2013
* <a id="Wiechetek-etal-2021-rules">**Wiechetek-etal-2021-rules**</a>:
    * error: <strong style="color: red">missing from bibs</strong>
* <a id="sikor_06.11.2018">**sikor_06.11.2018**</a>:
    * author: SIKOR
    * title: SIKOR UiT Norgga árktalaš universitehta ja Norgga Sámedikki ...
    * howpublished: 
url{http://gtweb.uit.no/korp}
    * note: Accessed: 2024-10-01
    * year: 2021
* <a id="Wiechetek2012constraint">**Wiechetek2012constraint**</a>:
    * error: <strong style="color: red">missing from bibs</strong>
* <a id="ng-etal-2013-conll">**ng-etal-2013-conll**</a>:
    * address: Sofia, Bulgaria
    * author: Ng, Hwee Tou  and Wu, Siew Mei  and Wu, Yuanbin  and Hadiwin...
    * booktitle: Proceedings of the Seventeenth Conference on Computational
    * month: aug
    * pages: 1–12
    * publisher: Association for Computational Linguistics
    * title: The CoNLL-2013 Shared Task on Grammatical Error Correction
    * url: https://aclanthology.org/W13-3601
    * year: 2013
* <a id="Nickel1994samisk">**Nickel1994samisk**</a>:
    * error: <strong style="color: red">missing from bibs</strong>
* <a id="Lorusso2019asymmetries">**Lorusso2019asymmetries**</a>:
    * error: <strong style="color: red">missing from bibs</strong>
* <a id="chollampatt2018multilayer">**chollampatt2018multilayer**</a>:
    * author: Chollampatt, Shamil and Ng, Hwee Tou
    * booktitle: Proceedings of the AAAI Conference on Artificial Intelligenc...
    * number: 1
    * title: A multilayer convolutional encoder-decoder neural network fo...
    * volume: 32
    * year: 2018
* <a id="boyd2018using">**boyd2018using**</a>:
    * author: Boyd, Adriane
    * booktitle: Proceedings of the 2018 EMNLP Workshop W-NUT: The 4th Worksh...
    * doi: /10.18653/v1/W18-6111
    * pages: 79–84
    * title: Using Wikipedia edits in low resource grammatical error corr...
    * year: 2018
* <a id="Arppe2000ei">**Arppe2000ei**</a>:
    * error: <strong style="color: red">missing from bibs</strong>
* <a id="Birn2000detecting">**Birn2000detecting**</a>:
    * error: <strong style="color: red">missing from bibs</strong>
* <a id="Hagen2001det">**Hagen2001det**</a>:
    * error: <strong style="color: red">missing from bibs</strong>
* <a id="moshagen2014open">**moshagen2014open**</a>:
    * author: Moshagen, Sjur and Rueter, Jack and Pirinen, Flammie and
    * booktitle: Proceedings of e Ninth International Conference on Language
    * pages: 71–77
    * title: Open-Source Infrastructures for Collaborative Work on
    * year: 2014
* <a id="beesley2003finite">**beesley2003finite**</a>:
    * author: Kenneth R Beesley and Lauri Karttunen
    * flammie: fsa
    * isbn: 978-1575864341
    * pages: 503
    * publisher: CSLI publications
    * title: Finite State Morphology
    * year: 2003
* <a id="Pirinen2014state">**Pirinen2014state**</a>:
    * error: <strong style="color: red">missing from bibs</strong>
* <a id="karlsson1990constraint">**karlsson1990constraint**</a>:
    * address: Helsinki
    * author: Fred Karlsson
    * booktitle: Proceedings of the 13th International Conference of
    * editor: H. Karlgren
    * pages: 168–173
    * title: Constraint Grammar as a Framework for Parsing Unrestricted T...
    * volume: 3
    * year: 1990
* <a id="Gaup2005xerox">**Gaup2005xerox**</a>:
    * error: <strong style="color: red">missing from bibs</strong>
* <a id="klein2017opennmt">**klein2017opennmt**</a>:
    * author: Guillaume Klein and Yoon Kim and Yuntian Deng and Jean Senel...
    * booktitle: Proc. ACL
    * doi: 10.18653/v1/P17-4012
    * title: OpenNMT: Open-Source Toolkit for Neural Machine Translation
    * url: https://doi.org/10.18653/v1/P17-4012
    * year: 2017

<!-- bib style: unsrt -->


<a id="lastpage">(¶ lastpage)</a>
<!-- end document -->

* * *

<span style='font-size: 8pt'>Converted with [Flammie’s latex2markdown](https://github.com/flammie/latex2markdown) v.0.1.0</span>

