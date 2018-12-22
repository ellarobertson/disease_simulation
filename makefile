all: single_person population_prototype population_contagion main

single_person: single_person.cc
        icpc -o single_person single_person.cc

population_prototype: population_prototype.cc
        icpc -o population_prototype population_prototype.cc

population_contagion: population_contagion.cc
        icpc -o population_contagion population_contagion.cc

main: main.cc
        icpc -o main main.cc

clean:
        rm single_person
        rm population_prototype
        rm population_contagion
        rm main

