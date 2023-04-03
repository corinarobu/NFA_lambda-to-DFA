#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
ifstream f("fisier.in");
ofstream g("fisier.out");
int nr_stari, nr_stari_afd, stari_afd[100], nr_stari_finale_nfa, stari_finale_nfa[100], stari_finale_dfa[100] ,in,aux[100][100], vec[100],vector[100], lungime, lung, nr_stari_finale_dfa, nr_litere, lambda_inchideri[100][100], i,o, z, ok, j,w, stare1,p, q,u, stare2, nr_tranzitii, k, v, l , matrice[200][200], matrice_afd[100][100];
char alfabet[100], litera, tranzitii[101][4];
int main() {
  // citire
  f >> nr_stari;
  f >> nr_stari_finale_nfa;
  for( i = 0 ; i < nr_stari_finale_nfa; i++ ) f >> stari_finale_nfa[i];
  f >> nr_litere;
  for( i = 0; i < nr_litere; i++ ) f >> alfabet[i];
  f >> nr_tranzitii;
  int copie_nr_tranzitii = 0;
  while(copie_nr_tranzitii < nr_tranzitii) {
    f >> tranzitii[copie_nr_tranzitii][0] >> tranzitii[copie_nr_tranzitii][1] >> tranzitii[copie_nr_tranzitii][2];
    copie_nr_tranzitii++;
  }

int nou[100], lnou = 0;
// completare matrice si lambda_inchiderile cu valori 100 , unde ar fi spatiu nefolosit , pentru a nu fi confuzie cu nodurile = 0
 for(i = 0; i < nr_stari*nr_litere ; i++ ){
   for(j = 0; j < nr_stari; j ++)
     matrice[i][j] = 100;
 }

 for(i = 0; i < 100 ; i++ ){
   for(j = 0; j < 100; j ++)
    if(lambda_inchideri[i][j] == 0 && j!=0)
     lambda_inchideri[i][j] = 100;
 }


  // completarea matricei lambda_inchideri cu lambda_inchiderile fiecarui nod
  int umax = 0;
  for( i = 0 ; i < nr_stari; i++) lambda_inchideri[i][0] = i ;
  int nr_noduri = 0;
  while(nr_noduri < nr_stari) {
    if( u > umax ) umax = u;
     u = 1;
      for(i = 0; i < nr_tranzitii; i ++) {
         if( (tranzitii[i][0]-'0') == nr_noduri && tranzitii[i][1] == 'l') {
                lambda_inchideri[tranzitii[i][0]-'0'][u++] = (tranzitii[i][2]-'0');
                 ok = 1, k = (tranzitii[i][2]- '0');
                 while(ok) {
                   lnou = 0;
                     ok = 0;
                     for(j = 0; j < nr_tranzitii; j++) {
                       if(tranzitii[j][1] == 'l' && (tranzitii[j][0]-'0') == k) {
                         int d = 1;
                         for(int m = 0; m < u; m++){
                           if( (tranzitii[j][2] - '0') == lambda_inchideri[nr_noduri][m]) d = 0;
                         }
                         if( d == 1) {
                           lambda_inchideri[tranzitii[i][0]-'0'][u++] = (tranzitii[j][2] - '0');
                           ok = 1;
                           // nou[lnou++] =  (tranzitii[j][2]-'0');
                           k = (tranzitii[j][2]-'0');
                         }
                       }
                     }

                   //   if(lnou > 1) {
                   //   int copi = lnou;
                   //   for(int r = 0; r < copi; r++){
                   //     k = nou[r];
                   //     for(j = 0; j < nr_tranzitii; j++) {
                   //       if(tranzitii[j][1] == 'l' && (tranzitii[j][0]-'0') == k) {
                   //         lambda_inchideri[tranzitii[i][0]-'0'][u++] = (tranzitii[j][2] - '0');
                   //       }
                   //     }
                   //   }
                   // }
            }
         }
    }
    nr_noduri++;
  }


 // sterge duplicate din lambda_inchideri
  for(i = 0 ; i < nr_stari; i ++){
  for(j = 0; j < umax; j ++) {
    for(k = j+1; k < umax; k++) {
      if(lambda_inchideri[i][j] == lambda_inchideri[i][k]) {
          for(int p = k; p < umax; p++) lambda_inchideri[i][p] = lambda_inchideri[i][p+1];
        }
    }
  }
}


// // completare matrice si lambda_inchiderile cu valori 100 , unde ar fi spatiu nefolosit , pentru a nu fi confuzie cu nodurile = 0
//  for(i = 0; i < nr_stari*nr_litere ; i++ ){
//    for(j = 0; j < nr_stari; j ++)
//      matrice[i][j] = 100;
//  }
//
//  for(i = 0; i < nr_stari ; i++ ){
//    for(j = 0; j < nr_stari; j ++)
//     if(lambda_inchideri[i][j] == 0 && j!=0)
//      lambda_inchideri[i][j] = 100;
//  }


// completare matrice cu lambda litera lambda pt fiecare nod (nr_litere*nr_stari linii)
   for( i = 0 ; i < nr_stari; i ++){
     for(k = 0 ; k < nr_litere; k++){
       lung = 0;
         for(j = 0; j < nr_tranzitii; j ++) {
           for(int e = 0; e < nr_stari; e++){
             if((tranzitii[j][0] - '0') == lambda_inchideri[i][e] && tranzitii[j][1] == alfabet[k]){
               vec[lung++] = (tranzitii[j][2]-'0');
               break;
           }
         }
       }

         lungime = 0;
         for(l = 0; l < nr_stari; l++){
             for(o = 0; o < lung; o++){
               if(vec[o] == l){
                 for(p = 0; p < nr_stari; p++) {
                   if(lambda_inchideri[l][p] != 100)
                    vector[lungime++] = lambda_inchideri[l][p];
                 }
                 break;
               }
             }
        }


        int a = 0;
        if(lungime != 0)
            matrice[k+nr_litere*i][a++] = vector[0];
        for(z = 1; z < lungime; z++){
          int g =1;
          for(int d = 0 ; d < a ; d++){
            if(matrice[k+nr_litere*i][d] == vector[z]) g =0;
          }
          if(g == 1) matrice[k+nr_litere*i][a++] = vector[z];
        }
    }
   }
//

for( i = 0 ; i < nr_stari; i ++) {
     for( j = 0; j < nr_stari; j++)
        for(k = j+1; k < nr_stari;k ++){
          if(lambda_inchideri[i][j] > lambda_inchideri[i][k]) swap(lambda_inchideri[i][j], lambda_inchideri[i][k]);
        }
   }

  // completare matrice_afd
  for(i = 0; i <= nr_stari; i++){
    for(j = 0; j <= nr_stari; j++)
       matrice_afd[i][j] = 100;
  }

  int indice = 0, b;
  for(i = 0; i < nr_stari; i++){
    matrice_afd[indice][i] = lambda_inchideri[0][i];
  }

  indice ++;
  stari_afd[++nr_stari_afd] = nr_stari_afd;
  for(i = 0; i < nr_stari; i++) {
    ok = 0;
    for(j = 0; j < nr_stari_finale_nfa; j++) {
      if( stari_finale_nfa[j] == matrice_afd[indice-1][i]){
        stari_finale_dfa[++nr_stari_finale_dfa] = nr_stari_finale_dfa;
        ok = 1;
      }
      break;
    }
    if(ok == 1) break;
  }

  int v[100], l=0, y, s ,f,a;
  int v2[100], l2 = 0;

  int n = 0;
  z  = 0;
  i = 0;
  while ( i < indice) {
    for( b= 0; b < nr_litere; b++) {
      l = 0;
        for( j = 0; j < nr_stari; j ++){
          k = matrice_afd[i][j];
          if(k != 100 ){
             for(a = 0; a < nr_stari; a++) v[l++] = matrice[b + nr_litere*k][a];
           }
          }

          for(y = 0; y < 100; y++) v2[y] = 100;

           l2 = 0;
             for(  y = 0; y < l; y ++){
                s = 1;
               for( f = 0; f < l2; f++) {
                  if(v[y] == v2[f]) s = 0;
               }
               if( s == 1) v2[l2++] = v[y];
             }

           // sortez linia i din afd si v2
           for(y = 0 ; y < nr_stari-1; y++){
             for( s = y+1; s < nr_stari; s++) {
               if(v2[y] > v2[s])
                 swap(v2[y], v2[s]);
           }
         }

           for( y = 0; y < nr_stari-1; y++){
             for(s =  y+1; s < nr_stari; s++) if(matrice_afd[i][y] > matrice_afd[i][s]) swap(matrice_afd[i][y], matrice_afd[i][s]);
           }

           // // sterge duplicate din v2 si  matrice_afd
           for(y = 0 ; y < nr_stari-1; y++){
             for( s = y+1; s < nr_stari; s++)
                 if(v2[y] == v2[s]) {
               for(in = s; in < nr_stari; in++) v2[in] = v2[in+1];
             }
           }

           for( y = 0; y < nr_stari-1; y++){
             for(s =  y+1; s < nr_stari; s++)
                 if(matrice_afd[i][y] == matrice_afd[i][s]) {
                     for(in = s ; in < nr_stari; in ++) matrice_afd[i][in] = matrice_afd[i][in+1];
             }
           }



        int r;
           for(y = 0; y < indice; y++){
             n = 0;
             for( r = 0; r < nr_stari; r++) {
               if(matrice_afd[y][r] != v2[r]) {
                 n = 1;
               }
           }
           if(n == 0) break;
       }

           if( n == 1 && v2[0] != 100){
             for( s = 0 ; s < nr_stari; s++){
               aux[z][s] = v2[s];
             }
             z++;


             // adaug in matricea AFD
             for(y = 0 ; y < nr_stari; y++){  matrice_afd[indice][y] = v2[y];
             }
             indice ++;


             stari_afd[++nr_stari_afd] = nr_stari_afd;
                   for(y = 0; y < nr_stari; y++) {
                     q = 0;
                     for(s = 0; s < nr_stari_finale_nfa; s++) {
                       if( stari_finale_nfa[s] == matrice_afd[indice-1][y]){
                         stari_finale_dfa[++nr_stari_finale_dfa] = nr_stari_finale_dfa;
                         q = 1;
                       }
                       break;
                     }
                     if(q == 1) break;
                   }
            }

            else {
              for( s = 0 ; s < nr_stari; s++){
                aux[z][s] = v2[s];
              }
              z++;
            }

        }
    i++;
  }

// ---------- AFISARE --------

   cout << "Numar stari AFD => " << nr_stari_afd << endl;
  cout << "Stari AFD : ";
  for(i= 1; i <= nr_stari_afd; i++) cout << stari_afd[i] << " ";
  cout << endl << "Numar stari finale AFD => " << nr_stari_finale_dfa;
  cout << endl << "Stari finale AFD : " ;
  for(i =1 ; i <= nr_stari_finale_dfa; i++) cout << stari_finale_dfa[i] << " ";
  cout << endl << "Tranzitii : " << endl;


  for(i = 0; i < indice; i++) {
    for(j = nr_litere*i  ; j <= nr_litere*i+ nr_litere-1; j++){
        for(k = 0; k < indice; k++){
          ok = 1;
          for(s = 0; s < nr_stari; s++) {
              if(matrice_afd[k][s] != aux[j][s]) ok = 0;
          }
          if( ok == 1) {
             cout << (i+1) << " " << alfabet[j%nr_litere] << " " << (k+1);
             cout << endl;
             break;
          }
        }
    }
  }


  return 0;
}
