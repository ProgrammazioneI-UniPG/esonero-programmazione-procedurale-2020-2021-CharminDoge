#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


int getLine(char *inpt);
int printSpeciali(char *s, int len);
int xorFun(char *msg, char *key, char *xorred, int len);
int printHex(char *mssgio, int len);

int main(){
  // messaggio da cifrare
  char msg[128];
  printf("Inserisci il messaggio da cifrare [1-128]:\n");
  // se l'input non mi soddisfa lo richiedo
  while (getLine(msg) != 1){
    printf("Reinserisci:\n");
  }
  printf("\n");


  // scelta dell'utente; uso fgets per prendere l'intera linea e strtol per prendere l'intero
  char choiceStr[128];
  int choiceInt = 0;
  // prendo un intero e verifico che sia o 1 o 2, altrimenti lo richiedo
  while (1){
    printf("Cosa vuoi fare?\n");
    printf("1. Fornire una key\n2. Utilizzare una key causale\n");
    printf("Inserisci il valore corrispondente:\n");
    getLine(choiceStr);
    char *end;
    choiceInt = strtol(choiceStr, &end, 10);
    if (choiceInt == 1 || choiceInt == 2)
      break;
    else
      printf("\nScrivi 1 o 2!\n\n");
  }
  int len = strlen(msg);


  // chiave
  char key[128];
  // immessa dall'utente
  if (choiceInt == 1 ){
    printf("\nInserisci la tua key [%d-128]:\n", len);
    while (getLine(key) != 1 || (strlen(key) < len)){
      if (strlen(key) < len)
        printf("\nTroppo corta, scrivi almeno %d caratteri\n", len);
      printf("Reinserisci:\n");
    }
  }
  // creata randomicamente
  else if (choiceInt == 2){
    time_t t;
    srand((unsigned) time(&t));
    for (int i = 0; i < len; i++){
      key[i] = rand() % 127;
    }
    printf("\nEcco la tua key:\n");
    printSpeciali(key, len);
    printHex(key, len);
    printf("\n");
  }


  // array per il messaggio cifrato
  char cipher[128];
  xorFun(msg, key, cipher, len);
  // stampo con speciali e in hex
  printf("\nIl tuo messaggio cifrato e'\n");
  printSpeciali(cipher, len);
  printf("\n");
  printHex(cipher, len);

  // array per lo xor del messaggio cifrato
  char originalXOR[128];
  xorFun(cipher, key, originalXOR, len);
  printf("\nIl messaggio originale era\n%s\n", originalXOR);
  printHex(originalXOR, len);


  // controllo se effettivamente lo xor della stringa xor-ata mi ritorna la stringa iniziale
  if (strcmp(msg, originalXOR) != 0)
    printf("Qualcosa è andato storto...\n");

  return 0;
}

// funzione che mi prende una stringa in input con alcuni controlli
int getLine(char *inpt) {
    int chr, check;
    // controllo che l'input non sia vuoto
    if (fgets (inpt, 128, stdin) == NULL){
      printf("\nScrivi qualcosa!\n");
      return 0;
    }
    // controllo che almeno 2 caratteri siano stati inseriti in input
    int len = strlen(inpt);
    if (len < 2){
      printf("\nTroppo corto!\n");
      return 0;
    }
    // controllo a fine linea se trovo \n o EOF
    // se c'è, 1, altrimenti 0
    if (inpt[len - 1] != '\n') {
        check = 0;
        while (((chr = getchar()) != '\n') && (chr != EOF))
            check = 1;
        if (check==1){
          printf("\nTroppo lungo!\n");
          return 0;
        }
        else
          return 1;
    }
    // termino l'array
    inpt[len - 1] = '\0';
    return 1;
}

// funzione che stampa i caratteri speciali da 0 a 31 nel formato |%d|
int printSpeciali(char *s, int len){
    for(int i = 0; i < len; i++){
        if(s[i] > 31 || s[i] == 127){
            printf("%c", s[i]);
        }else{
            printf("|%d|", s[i]);
        }
    }
    return 1;
}

// funzione xor
int xorFun(char *msg, char *key, char *cipher, int len){
  int i = 0;
  while (i < len){
    cipher[i] = msg[i] ^ key[i];
    i++;
  }
  cipher[i] = '\0';
  return 1;
}

// funzione che itera l'array e stampa il corrispettivo hex di ogni carattere
int printHex(char *mssgio, int len){
  printf("In hex\n");
  for (int i = 0; i < len; i++){
    printf("%02x", mssgio[i]);
  }
  printf("\n");
  return 1;
}
