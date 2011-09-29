#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct transition {
    int symbol;
    int state;
    struct transition * next;
} Transition;

typedef struct state {
    int state;
    int type;
    Transition * transitions;
} State;
/* Type is 0 if the state is ordinary,
           1 if the state is initial, and
          -1 if the state is final */

typedef struct symbol_table_element {
    int int_value;
    char symbol[30];
} Symbol;

typedef struct automaton {
    int state_count;
    State* states;
    int initial;

    int symbol_count;
    Symbol* symbols;
} Automaton;

// Ex. 11
void add_transition_node(Transition * TL, Transition * T) {
    T->next = TL;
}

//Ex. 12
int add_transition(State * s, int symbol, int state) {
    Transition * new_transition = malloc(sizeof(Transition));
    if (!new_transition)
        return 0;

    new_transition->symbol = symbol;
    new_transition->state = state;
    add_transition_node(s->transitions, new_transition);
    s->transitions = new_transition;
    return 1;
}

// Ex. 13
Symbol * read_symbols(int symbol_nr, FILE *fp) {
    Symbol * symbols = calloc(symbol_nr, sizeof(Symbol));
    if (!symbols) {
        fprintf(stderr, "Ran out of memory.\n");
        exit(1);
    }

    for (int i = 0; i < symbol_nr; i++) {
        fscanf(fp, "%d %29s", &symbols[i].int_value, (char*) &symbols[i].symbol);
        if (getc(fp) != '\n') {
            fprintf(stderr, "The name of symbol number %d is too long.\n",
                symbols->int_value);
            exit(1);
        }
    }

    return symbols;
}

// Ex. 14
Automaton read_automaton(FILE * fp) {
    int symbol_count, state_count, initial, final_count;
    fscanf(fp, "%d %d %d\n%d ", &state_count, &symbol_count, &initial, &final_count);

    int* final_states = calloc(final_count, sizeof(int));
    State* states = calloc(state_count, sizeof(State));
    Automaton automaton;
    automaton.state_count = state_count;
    automaton.symbol_count = symbol_count;

    if (!final_states || !states) {
        fprintf(stderr, "Ran out of memory.\n");
        free(final_states);
        free(states);
        exit(1);
    }

    for (int i = 0; i < final_count - 1; i++)
        fscanf(fp, "%d ", final_states + i);
    fscanf(fp, "%d\n", final_states + final_count - 1);

    int j = 0;
    int state;
    for (int i = 0; i < state_count; i++) {
        state = i + 1;
        states[i].state = state;
        if (state == initial) {
            states[i].type = 1;
            automaton.initial = state;
        }
        else if (state == final_states[j]) {
            states[i].type = -1;
            j++;
        }
        else
            states[i].type = 0;
    }

    automaton.states = states;
    automaton.symbols = read_symbols(symbol_count, fp);

    int from_state, to_state, symbol;
    while (fscanf(fp, "%d %d %d\n", &from_state, &symbol, &to_state) != EOF)
        add_transition(&states[from_state - 1], symbol, to_state);

    return automaton;
}

// Ex. 15
bool is_deterministic(Automaton maatti) {
    for (int i = 0; i < maatti.state_count; i++) {
        int* symbols = calloc(maatti.state_count, sizeof(int));
        for (Transition* current = maatti.states[i].transitions;
            current != NULL; current = current->next) {
            symbols[current->symbol - 1]++;
            if (symbols[current->symbol - 1] > 1) {
                free(symbols);
                return false;
            }
        }
        free(symbols);
    }
    return true;
}

// Ex. 16
bool accept(Automaton* maatti, int nr_of_symbols, int* symbols) {
    if (!is_deterministic(*maatti)) {
        fprintf(stderr, "Non-deterministic automata not supported.\n");
        exit(2);
    }
    State* current_state = &maatti->states[maatti->initial - 1];
    bool transitioned;
    for (int i = 0; i < nr_of_symbols; i++) {
        transitioned = false;
        for (Transition* current_trans = current_state->transitions;
            current_trans != NULL; current_trans = current_trans->next)
            if (current_trans->symbol == symbols[i]) {
                transitioned = true;
                current_state = &maatti->states[current_trans->state - 1];
                break;
            }
        if (!transitioned)
            return false;
    }

    if (current_state->type == -1)
        return true;
    return false;
}

void print_automaton(Automaton * maatti) {
    for (int i = 0; i < maatti->state_count; i++) {
        printf("State %d, type %d\n", i+1, maatti->states[i].type);
        for (Transition* current = maatti->states[i].transitions;
            current != NULL; current = current->next)
            printf("sym %d state %d\n", current->symbol, current->state);
    }
    for (int i = 0; i < maatti->symbol_count; i++)
        printf("Symbol %d %s\n", maatti->symbols[i].int_value,
            maatti->symbols[i].symbol);
    if (is_deterministic(*maatti))
        printf("Deterministic\n");
    else
        printf("Non-deterministic\n");
}

int main(void) {
    Automaton maatti = read_automaton(fopen("example_automaton.txt", "r"));
    print_automaton(&maatti);

    int abba[] = {1, 2, 2, 1};
    int bbaa[] = {2, 2, 1, 1};

    printf("Accepts abba = %s\n", accept(&maatti, 4, abba) ? "true" : "false");
    printf("Accepts bbaa = %s\n", accept(&maatti, 5, bbaa) ? "true" : "false");

    exit(0);
}
