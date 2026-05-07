#include <stdio.h>
#include <time.h>

#include "menu.h"
#include "login.h"
#include "animacao.h"

static void animacaoCarregamento(void) {
    const char *frames[] = {
        "[          ] 0%",
        "[=         ] 10%",
        "[==        ] 20%",
        "[===       ] 30%",
        "[====      ] 40%",
        "[=====     ] 50%",
        "[======    ] 60%",
        "[=======   ] 70%",
        "[========  ] 80%",
        "[========= ] 90%",
        "[==========] 100%"
    };

    clock_t inicio = clock();
    for (int i = 0; i < 11; i++) {
        while ((clock() - inicio) < (clock_t)(i + 1) * (CLOCKS_PER_SEC / 60)) {}
        printf("\r%s", frames[i]);
        fflush(stdout);
    }
    printf("\n");
}

int main(void) {
    telaLogin();
    animacaoCarregamento();
    animacaoFolhear();
    menu();
    return 0;
}

