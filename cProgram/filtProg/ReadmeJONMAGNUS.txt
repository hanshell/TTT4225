For å få filtProg til å funke på linux:

1) Last ned libsndfile1 fra hjemmesida dems

2) extract den hvor som helst

3) Via terminal gå til valgt lokasjon

4) kjør ./config -> make -> sudo make install (viktig med sudo for å få rettigheter som trengs)

libsndfile1 er da på plass

5) Gå inn i filtProg mappa

6) velg en editor for å endre example.sh
  vim example.sh

  foran Filter sett ./

  der det står na_play bytt ut med valgt avspillingsprogram
  cvlc er consoleversjon av vlc. legg ved --play-and-exit for at 
  programmet skal stoppe mellom hver gang og få kjøre videre til neste avspilling

  cvlv --play-and- stop filname.wav
