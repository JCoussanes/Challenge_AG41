/*
 * Jérôme COUSSANES
 * jerome.coussanes@utbm.fr
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "data_structure.h"
#include "function.h"


int main(int argc, char** argv){

    Data data;
	Solution s;

    if(argc != 2){
        printf("Wrong command. should be a.out <file path>.");
    }
    else{
        parse_file(argv[1],&data);

       mkfsol(&s,data);

        print_sol(s,data);

        s=rnd_way(s,data);

        print_sol(s,data);

    }



    return 0;
}

