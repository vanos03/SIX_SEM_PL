#include <iostream>
#include <vector>
#include <string.h>
#include <stdio.h>
#include <math.h>

#define d 127
#define q 131

// #define d 9
// #define q 13

std::vector<int> rabin_karp(char *str1, char *str2){
    int n = strlen(str1);
    int m = strlen(str2);

    std::vector<int> res;

    int d_m = ((int)pow(d, m-1)) % q;

    int h1 = 0, h2 = 0;

    for (int i = 0; i < m; i++){
        h1 = (d*h1 + str2[i]) % q;
        h2 = (d*h2 + str1[i]) % q;
    }

    for (int s = 0; s < n-m+1; s++){
        if (h1 == h2){
            char tmp[m];

            strcpy(tmp, str1+s);
            if (strcmp(str2, tmp)) res.push_back(s);
        }

        if (s < n-m){
            h2 = (d * (h2 - d_m*str1[s]) + str1[s+m]) %q;
            if (h2 < 0) h2 += q;
        }
            
    }

    return res;

}

char *pref_func(char *S, char *pi){
    int k = 0;
    pi[0] = 0;

    for (int i = 1; i < strlen(S)-1; i++){
        while((k > 0) && (S[k] != S[i])) k = pi[k-1];

        if (S[k] == S[i]) k++;

        pi[i] = k;
    }

    return pi;
}


std::vector<int> knut_moris(char *T, char *P){
    char pi[strlen(P)];
    pref_func(P, pi);
    int k = 0;
    std::vector<int> res;

    for (int i = 0; i < strlen(T)-1; i++){
        while ((k > 0) && (P[k] != T[i])) k = pi[k-1];

        if (P[k] == T[i]) k++;

        if (k == strlen(P)){
            res.push_back(i-strlen(P)+1);
            k = pi[k-1];
        }

    }

    return res;

}

int b_func(char *pat, int M, int st, char x){
    if (st < M && x == pat[st]) return st + 1;

    int i = 0;
    for (int ns = st; ns > 0; ns--){
        if (pat[ns-1] == x){
            for (i = 0; i < ns-1; i++)
                if (pat[i] != pat[st - ns + i]) break;
            if (i == ns-1) return ns;
        }
    }

    return 0;
}


void avtomat(char *S, char *pat){
    int M = strlen(pat);
    int N = strlen(S);

    int AVT[M+1][d];

    for (int st = 0; st < M+1; st++){
        for (char x = 0; x < d; x++){
            AVT[st][x] = b_func(pat, M, st, x);
            // printf("%d ", AVT[st][x]);
        }
        // printf("\n");
    }

    int st = 0;

    for (int i = 0; i < N; i++){
        // printf("%d %d %d\n", st, M, S[i]);
        st = AVT[st][S[i]];
        
        if (st == M) printf("%d\n", i-M+1);
    }

}


int main(){
    char *str1 = (char*)"qwabcqwertyuiop";
    char *str2 = (char*)"abc";

    for (auto i: rabin_karp(str1, str2))
        printf("%d\n", i);

    for (auto i: knut_moris(str1, str2))
        printf("%d\n", i);

    avtomat(str1, str2);
}
