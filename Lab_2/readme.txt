/**********************************************************************
 *  Knäcka lösenord readme.txt
 **********************************************************************/

 Ungefärligt antal timmar spenderade på labben (valfritt): --

/**********************************************************************
 *  Ge en högnivåbeskrivning av ditt program decrypt.c.
 **********************************************************************/
Efter att ha läst in alla ord (hashade lösenord och listan) går vi över
alla möjliga binära kombinationer av halva ordlängden (minst signifikanta
halvan). För varje kombination tar vi hashade lösenordet minus kombinationen och
lägger in de i en hashtabell. För vissa kombinationer resulterar det att den
halvan blev nollor och är då en kombination som kommer komma upp i nästa steg
där vi går igenom andra halvan (mest signifikanta halvan). Blir något i
hashtabellen 0 har vi hittat en möjlig lösning till det hashade lösenordet.


/**********************************************************************
 *  Beskriv symboltabellen du använt för decrypt.c.
 **********************************************************************/
Vår symboltabell använder typen Key som nyckel och en vector av Key som värde.
Samt en hashfunktion som räknar fram ett heltal utifrån binära värdet på Key.


/**********************************************************************
 *  Ge de dekrypterade versionerna av alla lösenord med 8 och 10
 *  bokstäver i uppgiften du lyckades knäca med DIN kod.
 **********************************************************************/


8 bokstäver               10 bokstäver
-----------               ------------
congrats, ibqfehan        completely, nbryjimvrd
mqubzd45, youfound        unbreakabl
theright                  cryptogram
aeiqrsd4, solution        ormaybenot,


/****************************************************************************
 *  Hur lång tid använder brute.c för att knäcka lösenord av en viss storlek?
 *  Ge en uppskattning markerad med en asterisk om det tar längre tid än vad
 *  du orkar vänta. Ge en kort motivering för dina uppskattningar.
 ***************************************************************************/


Char     Brute
--------------
 4      < 1 s
 5        7 s
 6        294 s
 8        *12348 s (294/7*294)


/******************************************************************************
 *  Hur lång tid använder decrypt.c för att knäcka lösenord av en viss storlek?
 *  Hur mycket minne använder programmet?
 *  Ge en uppskattning markerad med en asterisk om det tar längre tid än vad
 *  du orkar vänta. Ge en kort motivering för dina uppskattningar.
 ******************************************************************************/

Char    Tid (sekunder)            Minne (bytes) (enligt valgrind)
-----------------------------------------------------------------
6       < 1 s                     32k
8       14 s                      43 672k
10      590 s                     *
12      *24864 s (590/14*590)     *

/*************************************************************************
 * Hur många operationer använder brute.c för ett N-bitars lösenord?
 * Hur många operationer använder din decrypt.c för ett N-bitars lösenord?
 * Använd ordo-notation.
 *************************************************************************/
brute: O(2^n)
decrypt: O(2^(n/2)) (=O(2^n)?)


/*************************************************************************
 * Vilka egenskaper skulle ni leta efter i en hashfunktion för att
 * försäkra er om att den är "säker"?
 *************************************************************************/
- Så få collisioner som möjligt, dvs fördela värden så jämt det går
- Använda hela indata för att ta fram hashvärde (inte bara en del)
- Genererar väldigt olika hashvärden för indata med lite skillnad.
