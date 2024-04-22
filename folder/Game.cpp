#include <vector>
#include <vector>
#include <cstdio>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include <fstream>
#include <iostream>
#include <climits>
#include <vector>
#include <cmath>
#include <unistd.h>

#define MAX_SIZE 100  
#define ROW 21//21 //Y
#define COL 80//80 //X 
#define NPCROW (ROW - 2) //Y
#define NPCCOL (COL - 2) //X 
#define worldXSize 401
#define worldYSize 401
#define MAX_HEAP_SIZE 99999
#define INFINTY 99999

#define BOULDER '%'
#define TREE '^'
#define ROAD '#'
#define MART 'M'
#define CENTER 'C'
#define GRASS ':'
#define CLEARING '.'
#define WATER '~'
#define PLAYERCHAR '@'

#define ENEMYDEFEATED 1
#define PLAYERDEFEATED 2
#define WILDDEFEATED 3

#define DFC(x,y) (abs(x - 200) + abs(y - 200))
#define MIN(x,y) (x < y ? x : y)

int randomGenerator(int upper, int lower){
  return (rand() % (upper - lower + 1)) + lower;
}

/*Debug Num`*/  int dbNum = 0;

/*PokemonFile Class*/
class PokemonFile{
    public:
    int id;
    char identifier[50];
    int species_id;
    int height;
    int weight;
    int base_experience;
    int order;
    int is_default;
};

/*moves class*/
class Moves{
    public:
    int id;
    char identifier[50];
    int generation_id;
    int type_id;
    int power;
    int pp;
    int accuracy;
    int priority;
    int target_id;
    int damage_class_id;
    int effect_id;
    int effect_chance;
    int contest_type_id;
    int contest_effect_id;
    int super_contest_effect_id;
};

/*Pokemon Moves Class*/
class PokemonMoves{
    public:
    int pokemon_id;
    int version_group_id;
    int move_id;
    int pokemon_move_method_id;
    int level;
    int order;
};

/*Pokemon Species Class*/
class PokemonSpecies{
    public:
    int id;
    char identifier[50];
    int generation_id;
    int evolves_from_species_id;
    int evolution_chain_id;
    int color_id;
    int shape_id;
    int habitat_id;
    int gender_rate;
    int capture_rate;
    int base_happiness;
    int is_baby;
    int hatch_counter;
    int has_gender_differences;
    int growth_rate_id;
    int forms_switchable;
    int is_legendary;
    int is_mythical;
    int order;
    int conquest_order;
};

/*Experince Class*/
class Experience{
    public:
    int growth_rate_id;
    int level;
    int experience;
};

/*type names class*/
class TypeNames{
    public:
    int type_id;
    int local_language_id;
    char name[50];
};

/*Pokemon Stats class*/
class PokemonStats{
    public:
    int pokemon_id;
    int stat_id;
    int base_stat;
    int effort;
};

/*Stats class*/
class Stats{
    public:
    int id;
    char identifier[50];
    int damage_class_id;
    int is_battle_only;
    int game_index;
};

/*Pokemon Types class*/
class PokemonTypes{
    public:
    int pokemon_id;
    int type_id;
    int slot;
};

std::vector<PokemonFile> pokemonVector;
std::vector<Moves> movesVector;
std::vector<PokemonMoves> pokemonMovesVector;
std::vector<PokemonSpecies> pokemonSpeciesVector;
std::vector<Experience> experienceVector;
std::vector<TypeNames> typeNamesVector;
std::vector<PokemonStats> pokemonStatsVector;
std::vector<Stats> statsVector;
std::vector<PokemonTypes> pokemonTypesVector;

bool searchPokemonVector(int id, PokemonFile *p){
    // for (int i = 1; i < (int)pokemonVector.size(); i++){
    //     if (pokemonVector[i].id == id){
    //         *p = pokemonVector[i];
    //         return true;
    //     }
    // }
    *p = pokemonVector[id];
    return false;
}

bool searchMovesVector(int id, Moves *m){
    for (int i = 1; i < (int)movesVector.size(); i++){
        if (movesVector[i].id == id){
            *m = movesVector[i];
            return true;
        }
    }
    return false;
}

bool searchPokemonMovesVector(int id, int level, PokemonMoves *pm1, PokemonMoves *pm2, std::vector<Moves> pkMoves){
    for (int i = 1; i < (int)pokemonMovesVector.size(); i++){
        if (pokemonMovesVector[i].pokemon_id == id && pokemonMovesVector[i].level <= level && pm2->move_id != pokemonMovesVector[i].move_id){
            bool dup = false;
            for(int j=0; j<(int)pkMoves.size(); j++){
                if(pkMoves[j].id == pokemonMovesVector[i].move_id){
                    dup = true;
                    break;
                }
            }
            if(!dup){
                *pm1 = pokemonMovesVector[i];
                break;
            }
        }
    }
    return false;
}

bool searchPokemonSpeciesVector(int id, PokemonSpecies *ps){
    for (int i = 1; i < (int)pokemonSpeciesVector.size(); i++){
        if (pokemonSpeciesVector[i].id == id){
            *ps = pokemonSpeciesVector[i];
            return true;
        }
    }
    return false;
}

bool searchExperienceVector(int level, Experience *e){
    for (int i = 1; i < (int)experienceVector.size(); i++){
        if (experienceVector[i].level == level){
            *e = experienceVector[i];
            return true;
        }
    }
    return false;
}

bool searchTypeNamesVector(int id, TypeNames *tn){
    for (int i = 1; i < (int)typeNamesVector.size(); i++){
        if (typeNamesVector[i].type_id == id){
            *tn = typeNamesVector[i];
            return true;
        }
    }
    return false;
}

bool searchPokemonStatsVector(int id, int stats_id, PokemonStats *ps){
    for (int i = 1; i < (int)pokemonStatsVector.size(); i++){
        if (pokemonStatsVector[i].pokemon_id == id && pokemonStatsVector[i].stat_id == stats_id){
            *ps = pokemonStatsVector[i];
            return true;
        }
    }
    return false;
}

bool searchStatsVector(int id, Stats *s){
    for (int i = 1; i < (int)statsVector.size(); i++){
        if (statsVector[i].id == id){
            *s = statsVector[i];
            return true;
        }
    }
    return false;
}

bool searchPokemonTypesVector(int id, PokemonTypes *pt){
    for (int i = 1; i < (int)pokemonTypesVector.size(); i++){
        if (pokemonTypesVector[i].pokemon_id == id){
            *pt = pokemonTypesVector[i];
            return true;
        }
    }
    return false;
}


/*Pokemon class*/
class Pokemon{
    public:
    int id;
    int type;
    char identfier[50];
    int health;
    int currHealth;
    int level;
    int attack;
    int defense;
    int gender;
    int baseHealth;
    int baseAttack;
    int baseDefense;
    int speed;
    int baseSpeed;
    int baseSpecialDefense;
    int specialDefense;
    int baseSpecialAttack;
    int specialAttack;
    int shiny;
    //TODO
    std::vector<Moves> pkMoves;
    char move1[50];
    char move2[50];
    std::vector<Moves> allPossibleMoves;

    
    Pokemon(){ //Incomplete
        // PokemonFile pf;
        // searchPokemonVector(randomGenerator(1092, 1), &pf);
        // id = pf.id;
        // iv = randomGenerator(15, 0); // Generate a random Individual Value (IV) for the Pokemon, between 0 and 15 
        // strcpy(identfier, pf.identifier); // Set the identifier for this Pokemon using the identifier from the PokemonFile object
        // PokemonStats ps;
        // searchPokemonStatsVector(id, 1, &ps); // Search the Pokemon stats vector for the stats corresponding to this Pokemon's ID
        // health = baseHealth = ps.base_stat; // Set the base stat for this Pokemon using the base stat from the PokemonStats object
        // level = 1; // Set the initial level for this Pokemon to 1
        // searchPokemonStatsVector(id, 2, &ps);
        // attack = baseAttack = ps.base_stat;
        // searchPokemonStatsVector(id, 3, &ps);
        // defense = baseDefense = ps.base_stat; 
        // gender = randomGenerator(1,0); // Generate a random gender for this Pokemon, 0 or 1
        // if (rand() % 8192 == 0){ // Determine if the Pokemon is shiny (rare variant) with a 1 in 8192 chance
        //     shiny = 1;
        // } else {
        //     shiny = 0;
        // }
    }

    Pokemon(int distance){ //T H I S 
        PokemonFile pf;
        searchPokemonVector(randomGenerator(1092, 1), &pf);
        id = pf.id; // Generate a random ID for the Pokemon, between 1 and 1092
        strcpy(identfier, pf.identifier); // Set the identifier for this Pokemon using the identifier from the PokemonFile object
        PokemonStats ps;
        searchPokemonStatsVector(id, 1, &ps); // Search the Pokemon stats vector for the stats corresponding to this Pokemon's ID
        health = baseHealth = ps.base_stat; // Set the base stat for this Pokemon using the base stat from the PokemonStats object
        if (distance <= 200){
            if (distance < 2){
                level = 1;
            } else {
                level = randomGenerator(distance / 2 , 1); // If the distance is less than or equal to 200, set the level to a random number between 1 and distance/2
            }        
        } else {
            level = randomGenerator(100, int((distance - 200) / 2)); // If the distance is more than 200, set the level to a random number between (distance - 200)/2 and 100
        }
        searchPokemonStatsVector(id, 2, &ps);
        attack = baseAttack = ps.base_stat;
        searchPokemonStatsVector(id, 3, &ps);
        defense = baseDefense = ps.base_stat; // Calculate the defense for this Pokemon using the formula: floor((base + iv) * 2 / 100) + 5
        searchPokemonStatsVector(id, 4, &ps);
        specialAttack = baseSpecialAttack = ps.base_stat;
        searchPokemonStatsVector(id, 5, &ps);
        specialDefense = baseSpecialDefense = ps.base_stat;
        searchPokemonStatsVector(id, 6, &ps);
        speed = baseSpeed = ps.base_stat;


        gender = randomGenerator(1,0); // Generate a random gender for this Pokemon, 0 or 1
        if (rand() % 8192 == 0){ // Determine if the Pokemon is shiny (rare variant) with a 1 in 8192 chance
            shiny = 1;
        } else {
            shiny = 0;
        }

        for (int i = 1; i < (int)pokemonMovesVector.size(); i++){
            if (pokemonMovesVector[i].pokemon_id == id ){
                PokemonMoves pm = pokemonMovesVector[i];
                for(int j = 1; j < (int)movesVector.size(); j++){
                    if (movesVector[j].id == pm.move_id){
                        allPossibleMoves.push_back(movesVector[j]);
                    }
                }
            }
        }

        // for (int i = 0; i < (int)allPossibleMoves.size(); i++){
        //   printf("%s\n", allPossibleMoves[i].identifier);
        // }
        PokemonMoves pm1;
        PokemonMoves pm2;
        Moves moves;
        searchPokemonMovesVector(id, level, &pm1, &pm2, pkMoves);
        searchMovesVector(pm1.move_id, &moves);
        strcpy(move1, moves.identifier);
        pkMoves.push_back(moves);
        searchPokemonMovesVector(id, level, &pm2, &pm1, pkMoves);
        searchMovesVector(pm2.move_id, &moves);
        strcpy(move2, moves.identifier); 
        pkMoves.push_back(moves);

        currHealth = health = floor((baseHealth + randomGenerator(15,0))*2*level/ 100) + level + 10;
        attack = floor((baseAttack + randomGenerator(15,0))*2*level/ 100) + 5;
        defense = floor((baseDefense + randomGenerator(15,0))*2*level/ 100) + 5;
        speed = floor((baseSpeed + randomGenerator(15,0))*2*level/ 100) + 5;
        specialDefense = floor((baseSpecialDefense + randomGenerator(15,0))*2/ 100) + 5;
        specialAttack = floor((baseSpecialAttack + randomGenerator(15,0))*2/ 100) + 5;

        //get type
        PokemonTypes *pt = (PokemonTypes*)malloc(sizeof(PokemonTypes));
        searchPokemonTypesVector(id, pt);
        type = pt->type_id;
 
    }

    Pokemon(int id, int type, int level, int health, int currHealth, int attack, int defense, int speed, int gender, int specialDefense, int specialAttack, int shiny){
        this->id = id;
        this->type = type;
        this->level = level;
        this->health = health;
        this->currHealth = currHealth;
        this->attack = attack;
        this->defense = defense;
        this->speed = speed;

        PokemonFile pf;
        searchPokemonVector(id, &pf);
        strcpy(identfier, pf.identifier);
        PokemonStats ps;
        searchPokemonStatsVector(id, 1, &ps);
        baseHealth = ps.base_stat;
        searchPokemonStatsVector(id, 2, &ps);
        baseAttack = ps.base_stat;
        searchPokemonStatsVector(id, 3, &ps);
        baseDefense = ps.base_stat;
        searchPokemonStatsVector(id, 4, &ps);
        baseSpecialAttack = ps.base_stat;
        searchPokemonStatsVector(id, 5, &ps);
        baseSpecialDefense = ps.base_stat;
        searchPokemonStatsVector(id, 6, &ps);
        baseSpeed = ps.base_stat;

    }

    void addMoveFromID(int id){
        Moves moves;
        searchMovesVector(id, &moves);
        pkMoves.push_back(moves);   
    }


    void levelUp(){
        level++;
        health = floor((baseHealth + randomGenerator(15,0))*2*level/ 100) + level + 10;
        attack = floor((baseAttack + randomGenerator(15,0))*2*level/ 100) + 5;
        defense = floor((baseDefense + randomGenerator(15,0))*2*level/ 100) + 5;
        speed = floor((baseSpeed + randomGenerator(15,0))*2*level/ 100) + 5;
        specialDefense = floor((baseSpeed + randomGenerator(15,0))*2*level/ 100) + 5;
        specialAttack = floor((baseSpeed + randomGenerator(15,0))*2*level/ 100) + 5;
        
        //searchForNewMove();
        PokemonMoves pm1;
        PokemonMoves pm2;
        Moves moves;
        searchPokemonMovesVector(id, level, &pm1, &pm2, pkMoves);
        if(searchMovesVector(pm1.move_id, &moves) && 4 > (int)pkMoves.size()){
            pkMoves.push_back(moves);
        }
    }

    bool isKnockedOut(){
        if(currHealth <= 0){
            return true;
        }
        return false;
    }

    void printPokemon(){
        printf("ID: %d\n", id);
        printf("Identifier: %s\n", identfier);
        printf("Health: %d\n", health);
        printf("Level: %d\n", level);
        printf("Attack: %d\n", attack);
        printf("Defense: %d\n", defense);
        printf("Gender: %d\n", gender);
        printf("baseHealth: %d\n", baseHealth);
        printf("Shiny: %d\n", shiny);
        for(int i=0; i<(int)pkMoves.size(); i++){
            printf("Move %d: %s      move id %d\n", i+1, pkMoves[i].identifier, pkMoves[i].id);
        }
    }

    void printPokemonCurses(){
        clear();
        mvprintw(0,0, "ID: %d", id);
        mvprintw(1,0, "Identifier: %s", identfier);
        mvprintw(2,0, "Health: %d", health);
        mvprintw(3,0, "Level: %d", level);
        mvprintw(4,0, "Attack: %d", attack);
        mvprintw(5,0, "Defense: %d", defense);
        mvprintw(6,0, "Gender: %d",gender);
        mvprintw(7,0, "baseHealth: %d", baseHealth);
        mvprintw(8,0, "Shiny: %d", shiny);
        for(int i=0; i<(int)pkMoves.size(); i++){
            mvprintw(9+i,0, "Move %d: %s     move id %d", i+1, pkMoves[i].identifier, pkMoves[i].id);
        }
        refresh();
    }



};


//NPC class
typedef class NPC{
    public:
    int symb; //NPC type: Rival, Hiker etc
    int row; 
    int col;
    int direc;
    int weightArr[NPCROW][NPCCOL]; //Weight array for dijkstra
    int defeated;
    Pokemon* pokemons[6];
    int numPK;
    int currPoke;

    bool isDefeated(){
        if(currPoke < numPK){
            return false;
        }
        // for(int i=0; i<numPK; i++){
        //     if(pokemons[i]->currHealth > 0){
        //         return false;
        //     }
        // }
        defeated = 1;
        return true;
    }
}NPC;

//NPC Enums
typedef enum NPCSymb{
    HIKER,
    RIVAL,
    PACER,
    WANDERER,
    SENTRIES, 
    EXPLORERS
}NPCSymb;

typedef enum PCMOV{
    NE,
    N,
    NW,
    W,
    SW,
    S,
    SE,
    E,
    SKIP
}PCMOV;

//PC class
typedef class PC{
    public:
    int row;
    int col;
    int globalX;
    int globalY;
    Pokemon* pokemons[6];
    int numPK;
    int currPoke;
    int potions;
    int pokeballs;
    int revives;

    int useItem(int item, int poke){
        switch(item){
            case 1:
                if(potions > 0){
                    //pokemons[poke]->currHealth += 20;
                    if(pokemons[poke]->currHealth < pokemons[poke]->health){
                        pokemons[poke]->currHealth = MIN(pokemons[poke]->health, pokemons[poke]->currHealth + 20);
                        potions--;
                        return 1;
                    }
                    //potions--;
                }
                break;
            case 2:
                if(pokeballs > 0){
                    pokeballs--;
                    return 2;
                }
                break;
            case 3:
                if(revives > 0 and pokemons[poke]->currHealth == 0){
                    pokemons[poke]->currHealth = pokemons[poke]->health/2;
                    revives--;
                    return 3;
                }
                break;
        }
        return 0;
    }

    void visitMart(){
         numPK = 3;
         potions = 3;
         pokeballs = 3;
         revives = 3;
    }

    void visitCenter(){
        for (int i=0; i<numPK; i++){
            pokemons[i]->currHealth = pokemons[i]->health;
        }
    }

    int openBag(int wild){
        clear();
        mvprintw(0,0, "You have %d potions. Press 1 to use potion", potions);
        mvprintw(1,0, "You have %d pokeballs. Press 2 to capture wild Pokemon", pokeballs);
        mvprintw(2,0, "You have %d revives. Press 3 to use revive", revives);
        mvprintw(3,0, "Press esc to close bag");
        refresh();
        char ch; 
        while((ch = getch()) != 27){ 
            if (ch == '1'){
                mvprintw(4,0, "Which Pokemon do you want to use the potion on?");
                for(int i=0; i<numPK; i++){
                    mvprintw(5+i,0, "%d: %s", i+1, pokemons[i]->identfier);
                }
                refresh();
                int poke;
                while((poke = getch()) != 27){
                    if(poke >= 49 && poke <= numPK+48){
                        useItem(1, poke-48-1);
                        //break;
                    }
                }
            } else if(ch == '2'){ //TODO
                if(wild == 1){
                    if (numPK < 6 ){
                        if (useItem(2,-1) == 2) {return 1;}
                        else {return 2;}
                    } else {
                        return 2;
                    }
                } else {
                    mvprintw(4,0, "You can only catch wild Pokemon.");
                }
                refresh();
                //int poke;
                // while((poke = getch()) != 27){
                //     if(poke >= 49 && poke <= numPK+48){
                //         useItem(2, poke-48-1);
                //         break;
                //     }
                // }
            } //useItem(3, poke-48-1
            else if (ch == '3'){
                mvprintw(4,0, "Which Pokemon do you want to use the revive on?");
                for(int i=0; i<numPK; i++){
                    mvprintw(5+i,0, "%d: %s", i+1, pokemons[i]->identfier);
                }
                refresh();
                int poke;
                while((poke = getch()) != 27){
                    if(poke >= 49 && poke <= numPK+48){
                        useItem(3, poke-48-1);
                        break;
                    }
                }
            }
            clear();
            mvprintw(0,0, "You have %d potions. Press 1 to use potion", potions);
            mvprintw(1,0, "You have %d pokeballs. Press 2 to capture wild Pokemon", pokeballs);
            mvprintw(2,0, "You have %d revives. Press 3 to use revive", revives);
            mvprintw(3,0, "Press esc to close bag");
            refresh();
        }
        return 0;
    }

    bool isDefeated(){
        for(int i=0; i<numPK; i++){
            if(pokemons[i]->currHealth > 0){
                return false;
            }
        }
        return true;
    }

    void findFirstPoke(){
        for(int i=0; i<numPK; i++){
            if(pokemons[i]->currHealth > 0){
                currPoke = i;
                break;
            }
        }
    }


}PC;

typedef class heapNode {
    public:
    int weight;
    //for dijkstra
    int row;
    int col;
    int visited;
    //for moving
    NPC* npc;
    PC* pc;
} heapNode;

/*Begin heap implemantation*/
// Declare a heap classure
class Heap {
    public:
    heapNode* arr[MAX_HEAP_SIZE];
    int size;
    //int capacity;
};
 // define the class Heap name
typedef class Heap heap;

//map class for terrain. 21x80 map
typedef class mapclass{
    public:
    int row;
    int col;
	int gateN;//top
	int gateS;//bottom
	int gateW;//left
	int gateE;//right
    int connection1[2];
    int connection2[2];
	char terrain[ROW][COL];
    NPC* npcArray[NPCROW][NPCCOL];
    PC* playerT;
    int NPCSInit; 
    heap* terrainHeap;
}mapclass;


//Global map. Array of map pointers
typedef class worldMap{
    public:
    int seed;
    int numTrainers;
    mapclass* arr[worldYSize][worldXSize];
    PC* player;

    void setWorldToNull(){
        for(int i=0; i<worldYSize; i++){
            for(int j=0; j<worldXSize; j++){
                arr[i][j] = NULL;
            }
        }
    }

}worldMap;

//char startMap[ROW][COL];
int queSize = 0;
int getQueSize(){
    return queSize;
}

//prototype declerations
    void createMap(int x, int y, worldMap *wm, int npcNum);
    void dijkstras(int row, int col, mapclass* terrainMap, int weightArr[NPCROW][NPCCOL], int type);
    void printWeightMap(int weightArr[NPCROW][NPCCOL]);
    void moveCharecters(worldMap *wm, mapclass *terrainMap, int numTrainers);
    int randomGenerator(int upper, int lower);
    int calcCost(int npc, char terrainType);
    int canMove(mapclass *terrainMap, int symb, int row, int col, int prevRow, int prevCol);
    int movePC(worldMap *wm, mapclass *terrainMap, PC *pc, int direc);
    void enterBuilding(char building, PC *pc);
    void trainerList(mapclass *terrainMap, PC *pc);
    void enterBattle(NPC *npc, PC *pc);
    void moveOnGate(worldMap *wm, mapclass *terrainMap, PC *pc, int newRow, int newCol, int curRow, int curCol, int direc, int npcNum);
    void moveEveryone(worldMap *wm, mapclass *terrainMap, int numTrainers, heap *h);
    void encounterPokemon(PC *pc);
    int fight(PC *pc, Pokemon *wildPokemon, NPC *npc, int switchP);
    int fightNPCTurn(NPC *npc, Pokemon* wp, PC *pc, int pMove);
    int attack(Pokemon *attacker, Pokemon *defender, Moves *move, int isPC);
    int saveGameState(worldMap *wm);

//Prints map out to the terminal
void printMap(mapclass *map, PC *pc){
    int i, j;
    clear();
    start_color();

    init_pair(COLOR_RED, COLOR_RED, COLOR_BLACK); //NPCs
    init_pair(COLOR_BLUE, COLOR_BLUE, COLOR_BLACK); //Water
    init_pair(COLOR_YELLOW, COLOR_YELLOW, COLOR_BLACK); //Road
    init_pair(COLOR_MAGENTA, COLOR_MAGENTA, COLOR_BLACK);  //BOULDER
    init_pair(COLOR_CYAN, COLOR_CYAN, COLOR_BLACK); 
    //init_pair(COLOR_ORANGE, COLOR_ORANGE, COLOR_WHITE);
    init_pair(COLOR_WHITE, COLOR_WHITE, COLOR_BLACK);
    init_pair(COLOR_GREEN, COLOR_GREEN, COLOR_BLACK);

    for (j=0; j < COL; j++){
        mvprintw(1, j, "%d", j % 10);
    }
    //mvprintw(1, 80, "\n");
    for (i=0; i < ROW; i++){
        for(j=0; j < COL; j++){
            
            if(pc->row == i && pc->col == j){
                attron(COLOR_PAIR(COLOR_MAGENTA));
                mvprintw(i+2,j,"%c", PLAYERCHAR);
                attroff(COLOR_PAIR(COLOR_MAGENTA));
                continue;
            } else if (i>0 && i<ROW-1 && j>0 && j<COL-1 && map->npcArray[i-1][j-1] != NULL){          
                char symbs[6] = {'h', 'r', 'p', 'w', 's', 'e'};
                attron(COLOR_PAIR(COLOR_RED));
                mvprintw(i+2,j,"%c", symbs[map->npcArray[i-1][j-1]->symb]);
                attroff(COLOR_PAIR(COLOR_RED));
                continue;
            } else {
                char terrain = map->terrain[i][j];
                switch(terrain){
                    case (BOULDER):
                        attron(COLOR_PAIR(COLOR_WHITE));
                        mvprintw(i+2,j,"%c", map->terrain[i][j]);
                        attroff(COLOR_PAIR(COLOR_WHITE));
                        break;
                    case (TREE):
                        attron(COLOR_PAIR(COLOR_GREEN));
                        mvprintw(i+2,j,"%c", map->terrain[i][j]);
                        attroff(COLOR_PAIR(COLOR_GREEN));
                        break;
                    case (ROAD):
                        attron(COLOR_PAIR(COLOR_YELLOW));
                        mvprintw(i+2,j,"%c", map->terrain[i][j]);
                        attroff(COLOR_PAIR(COLOR_YELLOW));
                        break;
                    case (MART):
                        attron(COLOR_PAIR(COLOR_RED));
                        mvprintw(i+2,j,"%c", map->terrain[i][j]);
                        attroff(COLOR_PAIR(COLOR_RED));
                        break;
                    case (CENTER):
                        attron(COLOR_PAIR(COLOR_RED));
                        mvprintw(i+2,j,"%c", map->terrain[i][j]);
                        attroff(COLOR_PAIR(COLOR_RED));
                        break;
                    case (GRASS):
                        attron(COLOR_PAIR(COLOR_GREEN));
                        mvprintw(i+2,j,"%c", map->terrain[i][j]);
                        attroff(COLOR_PAIR(COLOR_GREEN));
                        break;
                    case (WATER):
                        attron(COLOR_PAIR(COLOR_CYAN));
                        mvprintw(i+2,j,"%c", map->terrain[i][j]);
                        attroff(COLOR_PAIR(COLOR_CYAN));
                        break;
                    case (CLEARING):
                        attron(COLOR_PAIR(COLOR_WHITE));
                        mvprintw(i+2,j,"%c", map->terrain[i][j]);
                        attroff(COLOR_PAIR(COLOR_WHITE));
                        break;
                }
                
            }

        }
        mvprintw(i+2,COL,"%d", i);
        //mvprintw(i,COL+1,"\n");
    }
    mvprintw(ROW+1, COL+1, "(%d, %d)", pc->globalX-200, pc->globalY-200);
    refresh();
}



 
// forward declarations
heap* createHeap();
void insertHelper(heap* h, int index);
void heapify(heap* h, int index);
heapNode* extractMin(heap* h);
void insert(heap* h, heapNode* data);
 
// Define a createHeap function
heap* createHeap()
{
    // Allocating memory to heap h
    heap* h = (heap*)malloc(sizeof(heap));
 
    // Checking if memory is allocated to h or not
    if (h == NULL) {
        printf("Memory error");
        return NULL;
    }
    // set the values to size and capacity
    h->size = 0;
    
    return h;
}
 
// Defining insertHelper function
void insertHelper(heap* hp, int index)
{
 
    // Store parent of element at index
    // in parent variable
    int parent = (index - 1) / 2;

    if(hp->arr[index]->row == 4251078){
        printf("bruhhhh\n");
    }
 
    if (hp->arr[parent]->weight > hp->arr[index]->weight) {
        // Swapping when child is smaller
        // than parent element
        heapNode* temp = hp->arr[parent];
        hp->arr[parent] = hp->arr[index];
        hp->arr[index] = temp;
 
        // Recursively calling insertHelper
        insertHelper(hp, parent);
    }
}
 
void heapify(heap* h, int index)
{
    int left = index * 2 + 1;
    int right = index * 2 + 2;
    int min = index;
 
    // Checking whether our left or child element
    // is at right index or not to avoid index error
    if (left >= h->size || left < 0)
        left = -1;
    if (right >= h->size || right < 0)
        right = -1;
 
    // store left or right element in min if
    // any of these is smaller that its parent
    if (left != -1 && h->arr[left]->weight < h->arr[index]->weight)
        min = left;
    if (right != -1 && h->arr[right]->weight < h->arr[min]->weight)
        min = right;
 
    // Swapping the nodes
    if (min != index) {
        heapNode* temp = h->arr[min];
        h->arr[min] = h->arr[index];
        h->arr[index] = temp;
 
        // recursively calling for their child elements
        // to maintain min heap
        heapify(h, min);
    }
}
 
 //potential leakage
heapNode* extractMin(heap* h){
    heapNode* deleteItem;
    
    // Checking if the heap is empty or not
    if (h->size == 0) {
        printf("\nHeap id empty.");
        return NULL;
    }
 
    // Store the node in deleteItem that
    // is to be deleted.
    deleteItem = h->arr[0];
 
    // Replace the deleted node with the last node
    h->arr[0] = h->arr[h->size - 1];
    // Decrement the size of heap
    //free(h->arr[h->size - 1]);
    h->size--;
 
    // Call minheapify_top_down for 0th index
    // to maintain the heap property
    //ret = deleteItem;
    heapify(h, 0);
    return deleteItem;
} 
 
// Define a insert function
void insert(heap* h, heapNode* data){
 
    // Checking if heap is full or not
    if (h->size < MAX_HEAP_SIZE) {
        // Inserting data into an array
        h->arr[h->size] = data;
        // Calling insertHelper function
        insertHelper(h, h->size);
        // Incrementing size of array
        h->size++;
    }
}

 
void printHeap(heap* h)
{
 
    for (int i = 0; i < h->size; i++) {
        printf("%d ", h->arr[i]->weight);
    }
    printf("\n");
}

void killHeap(heap* h){
    free(h);
}
/*End heap implementation*/

/////Que Implemntation////
 class Node {  
    public:
    int coord[2]; 
    char seed; 
    class Node* next;  
};  
class Node* front = NULL;  ////front of que
class Node* rear = NULL;    ////end of que
void enqueue(int element[2], char seed) {  
    class Node* new_node = (class Node*)malloc(sizeof(class Node));  
    new_node->coord[0] = element[0];
    new_node->coord[1] = element[1];
    new_node->seed = seed;  
    new_node->next = NULL;  
    if (front == NULL && rear == NULL) {  
        front = rear = new_node;  
        return;  
    }  
    rear->next = new_node;  
    rear = new_node; 
    queSize++; 
}   
int dequeue(int coord[2], char *s) {  
    if (front == NULL) {  
        //free(front);
        printf("Queue is empty");  
        return -1;  
    }  
    class Node* temp = front;  
    coord[0] = temp->coord[0]; 
    coord[1] = temp->coord[1]; 
    *s = temp->seed;
    if (front == rear) {  
        front = rear = NULL;  
    }  
    else {  
        front = front->next;  
    }  

    free(temp);  
    queSize --;
    return 0;  
}  
/////End Que Implemntation////




/*Code for creating roads and buildings*/
void makeRoads(mapclass *map, int distanceFromCenter, int x, int y, worldMap* wm){
    //rand() % (max_number + 1 - minimum_number) + minimum_number
    int entranceX1[2] = {0, rand() % (COL-4+1-4)+4}; //North gate
    int entranceX2[2] = {ROW - 1, rand() % (COL-4+1-4)+4}; //South gate
    int entranceY1[2] = {rand() % (ROW-10+1-10)+10, 0};//West gate
    int entranceY2[2] = {rand() % (ROW-4+1-4)+4, COL - 1};//East Gate

    if(map->gateN != -1){
        int gateVal = map->gateN;
        entranceX1[1] = gateVal;
        //entranceY1[1] = 0;
    } else {
        map->gateN = entranceX1[1];
    }
    if(map->gateS != -1){
        int gateVal = map->gateS;
        entranceX2[1] = gateVal;
        //entranceY1[0] = 0;
    } else {
        map->gateS = entranceX2[1];
    }
    if(map->gateW != -1){
        int gateVal = map->gateW;
        entranceY1[0] = gateVal;
        //entranceY1[0] = ROW - 1;
    } else {
        map->gateW = entranceY1[0];
    }
    if(map->gateE != -1){
        int gateVal = map->gateE;
        entranceY2[0] = gateVal;
        //entranceY1[1] = COL - 1;
    } else {
        map->gateE = entranceY2[0];
    }

    int randX = rand() % (ROW-5+1-5) + 5;
    int randY = rand() % (COL-20+1-20) + 20;

    int connectionX1[2] = {randX, entranceX1[1]};
    int connectionX2[2] = {randX, entranceX2[1]};
    int connectionY1[2] = {entranceY1[0], randY};
    int connectionY2[2] = {entranceY2[0], randY};

    map->connection1[0] = connectionX1[0];
    map->connection1[1] = connectionX1[1];
    map->connection2[0] = connectionY2[0];
    map->connection2[1] = connectionY2[1];
    
    int a,b;
    //build roads for cols
    //Go down
    for (a=entranceX1[0]; a <= connectionX1[0]; a++){
        map->terrain[a][entranceX1[1]] = '#';
        //printf("1  %d     %d\n", a, entranceX1[1]);
    }
    //go sideways
    if(connectionX1[1] < connectionX2[1]){ //go left
        for(b=connectionX1[1]; b<=connectionX2[1]; b++){
            map->terrain[connectionX2[0]][b] = '#';
        }
    } else { //Go right
        for(b=connectionX1[1]; b>=connectionX2[1]; b--){
            map->terrain[connectionX2[0]][b] = '#';
        }
    }
    //Go down
    for (a=connectionX2[0]; a <= entranceX2[0]; a++){
        map->terrain[a][entranceX2[1]] = '#';
    }


    //Build rooads for rows
    //Go right
    for (a=entranceY1[1]; a <= connectionY1[1]; a++){
        map->terrain[entranceY1[0]][a] = '#';
    }
    //Go up or down
    if(connectionY1[0] < connectionY2[0]){ //go down
        for(b=connectionY1[0]; b<=connectionY2[0]; b++){
            map->terrain[b][connectionY1[1]] = '#';
        }
    } else { //Go up
        for(b=connectionY1[0]; b>=connectionY2[0]; b--){
            map->terrain[b][connectionY1[1]] = '#';
        }
    }    
    //Go right
    for (a=connectionY2[1]; a <= entranceY2[1]; a++){
        map->terrain[entranceY2[0]][a] = '#';
    }
    
    //if(x == 200 && y == 200){
        wm->player->row = connectionX1[0];
        wm->player->col = connectionX1[1];
    //}

    //Close gates if at the edge
    if (y == 0) //close North gate
        map->terrain[entranceX1[0]][entranceX1[1]] = '%';
    if(y == worldYSize-1) //close West gate
        map->terrain[entranceY2[0]][entranceY2[1]] = '%';
    if (x == 0) //close East gate
        map->terrain[entranceY1[0]][entranceY1[1]] = '%';
    if(x == worldXSize-1) //close south gate
        map->terrain[entranceX2[0]][entranceX2[1]] = '%';


    int oddsForBuilding = ((-45*distanceFromCenter)/200 + 50);
    int chancesOutOf100 = rand() % 100 + 1;

    //Make pokemart
    if (distanceFromCenter == 0){
        //make pokemart
        int i, j;
        for(i = entranceX1[0]+1; i<entranceX1[0]+3; i++){
            for(j = entranceX1[1]+1; j<entranceX1[1]+3; j++){
                map->terrain[i][j] = 'M';
                // b++;
                // if (b == 4)
                //     break;
            }
        }
    } else if ( chancesOutOf100 <= oddsForBuilding && distanceFromCenter <= 200) { //away from center but distance is less than 200
        int i, j;
        for(i = entranceX1[0]+1; i<entranceX1[0]+3; i++){
            for(j = entranceX1[1]+1; j<entranceX1[1]+3; j++){
                map->terrain[i][j] = 'M';
                // b++;
                // if (b == 4)
                //     break;
            }
        }
    } else if (chancesOutOf100 <= 5){//flat 5% chance if 200 away from center
        int i, j;
        for(i = entranceX1[0]+1; i<entranceX1[0]+3; i++){
            for(j = entranceX1[1]+1; j<entranceX1[1]+3; j++){
                map->terrain[i][j] = 'M';
                // b++;
                // if (b == 4)
                //     break;
            }
        }
    }


    chancesOutOf100 = rand() % 100 + 1;
    //make Center
    if (distanceFromCenter == 0){//if at center
        int i, j;
        
        for(i = entranceY1[0]+1; i<entranceY1[0]+3; i++){
            for(j = entranceY1[1]+1; j<entranceY1[1]+3; j++){
                map->terrain[i][j] = 'C';
                // b++;
                // if (b == 4)
                //     break;
            }
        }
    } else if ( chancesOutOf100 <= oddsForBuilding && distanceFromCenter <= 200) { //away from center but distance is less than 200
        int i, j;
        
        for(i = entranceY1[0]+1; i<entranceY1[0]+3; i++){
            for(j = entranceY1[1]+1; j<entranceY1[1]+3; j++){
                map->terrain[i][j] = 'C';
                // b++;
                // if (b == 4)
                //     break;
            }
        }
    } else if (chancesOutOf100 <= 5){ //flat 5% chance if 200 away from center
        int i, j;
        
        for(i = entranceY1[0]+1; i<entranceY1[0]+3; i++){
            for(j = entranceY1[1]+1; j<entranceY1[1]+3; j++){
                map->terrain[i][j] = 'C';
                // b++;
                // if (b == 4)
                //     break;
            }
        }
    }
    
    
}

/*Randomly generate terrain*/
void createTerrain(mapclass *map){

    //assign biomes or seeds
    int grass1[2] =     {rand() % (ROW - 2) + 1, rand() % (COL - 2) + 1};
    int grass2[2] =     {rand() % (ROW - 2) + 1, rand() % (COL - 2) + 1};
    int water[2] =      {rand() % (ROW - 2) + 1, rand() % (COL - 2) + 1};
    int clearing1[2] =  {rand() % (ROW - 2) + 1, rand() % (COL - 2) + 1};
    int clearing2[2] =  {rand() % (ROW - 2) + 1, rand() % (COL - 2) + 1};
    int forest[2] =     {rand() % (ROW - 2) + 1, rand() % (COL - 2) + 1};
    int mountain[2] =   {rand() % (ROW - 2) + 1, rand() % (COL - 2) + 1};

    //add to que
    enqueue(grass1, GRASS);
    enqueue(water, WATER);
    enqueue(clearing1, CLEARING);
    enqueue(grass2, GRASS);
    enqueue(forest, TREE);
    enqueue(mountain, BOULDER);
    enqueue(clearing2, CLEARING);

    char currSeed;

    while (front != NULL) {
        int currCoord[2];
        int randVal = rand() % 10;
        
        dequeue(currCoord, &currSeed);
        //printf("%c", *currSeed);
        //map[currCoord[0]][currCoord[1]] = currSeed;
        // printMap();
        // printf("\n");
        //for loops variables
        if (randVal < 2){
            if (currCoord[0]+1 < ROW-1){
                if (map->terrain[currCoord[0]+1][currCoord[1]] == '_'){
                    int arr[2] = {currCoord[0]+1, currCoord[1]};
                    map->terrain[arr[0]][arr[1]] = currSeed;
                    enqueue(arr, currSeed);
                }
            }
            if (currCoord[0]-1 > 0){
                if (map->terrain[currCoord[0]-1][currCoord[1]] == '_'){
                    int arr[2] = {currCoord[0]-1, currCoord[1]};
                    map->terrain[arr[0]][arr[1]] = currSeed;
                    enqueue(arr, currSeed);
                }
            }
        }
        if (currCoord[1]+1 < COL-1){
            if (map->terrain[currCoord[0]][currCoord[1]+1] == '_'){
                int arr[2] = {currCoord[0], currCoord[1]+1};
                map->terrain[arr[0]][arr[1]] = currSeed;
                enqueue(arr, currSeed);
            }
        }
        if (currCoord[1]-1 > 0){
            if (map->terrain[currCoord[0]][currCoord[1]-1] == '_'){
                int arr[2] = {currCoord[0], currCoord[1]-1};
                map->terrain[arr[0]][arr[1]] = currSeed;
                enqueue(arr, currSeed);
            }
        }
    }

    

}

/*Initilaize map to empty spaces and add border*/
void setMap(mapclass *map, int x, int y, worldMap *wm){
    int i;
    int j;
    for(i = 0; i < ROW; i++){ //Set terrai  to null
        for(j=0; j < COL; j++){
            if (i == 0 || i == ROW-1 || j == 0 || j == COL-1){
                map->terrain[i][j] = '%';
                continue;
            }
            map->terrain[i][j] = '_';
        }
    }
    //set gates to NULL
    map->gateN = -1;
    map->gateE = -1;
    map->gateW = -1;
    map->gateS = -1;

    //check if there are gates to neighbours
    if(x - 1 >= 0){
        if ((wm->arr[x-1][y]) != NULL){
            map->gateW = wm->arr[x-1][y]->gateE;
            //printf("West Gate%d\n",wm->arr[x-1][y]->gateE);
        }
    }
    if(x + 1 < worldXSize){
        if ((wm->arr[x+1][y]) != NULL){
            map->gateE = wm->arr[x+1][y]->gateW;
            //printf("East Gate%d\n",wm->arr[x+1][y]->gateW);
        }
    }
    if(y - 1 >= 0){
        if (wm->arr[x][y-1] != NULL){
            map->gateN = wm->arr[x][y-1]->gateS;
            //printf("North Gate %d\n",wm->arr[x][y-1]->gateS);
        }
    }
    if(y + 1 < worldYSize){
        if (wm->arr[x][y+1] != NULL){
            map->gateS= wm->arr[x][y+1]->gateN;
            //printf("South Gate %d\n",wm->arr[x][y+1]->gateN);

        }
    }

    //map->playerT = (PC*)malloc(sizeof(PC));
    //set all NPCs to NULL
    for(i=0; i<NPCROW; i++){
        for(j=0; j<NPCCOL; j++){
            map->npcArray[i][j] = NULL;
        }
    }
    map->NPCSInit = 0;

}

void pcChooseStarterPokemon(PC *pc){
    Pokemon* pk1 = new Pokemon(0);
    Pokemon* pk2 = new Pokemon(0);
    Pokemon* pk3 = new Pokemon(0);
    Pokemon* pk4 = new Pokemon(75);
    pk4->levelUp();
    pk4->levelUp();
    pk4->levelUp();
    pk4->levelUp();
    pk4->levelUp();
    pk4->levelUp();

    clear();
    mvprintw(0,0, "Choose your starter Pokemon(enter 1, 2, or 3): ");
    mvprintw(1,0, "Name is %s! They are level %d,  health is %d, attack is %d, defense is %d.", pk1->identfier, pk1->level, pk1->health, pk1->attack, pk1->defense);
    mvprintw(2,0, "Name is %s! They are level %d,  health is %d, attack is %d, defense is %d.", pk2->identfier, pk2->level, pk2->health, pk2->attack, pk2->defense);
    mvprintw(3,0, "Name is %s! They are level %d,  health is %d, attack is %d, defense is %d.", pk3->identfier, pk3->level, pk3->health, pk3->attack, pk3->defense);
    refresh();
    char choice;
    while((choice = getch()) != 27){
        if (choice == '1'){
            pc->pokemons[0] = pk1;
            delete pk2;
            delete pk3;
            break;
        } else if (choice == '2'){
            pc->pokemons[0] = pk2;
            delete pk1;
            delete pk3;
            break;
        } else if (choice == '3'){
            pc->pokemons[0] = pk3;
            delete pk1;
            delete pk2;
            break;
        } else if (choice == '6'){
            pc->pokemons[0] = pk4;
            delete pk1;
            delete pk2;
            delete pk3;
            break;
        } else if (choice == 'q' || choice == 'Q'){
            exit(0);
        } 
        else {
            mvprintw(4,0, "Invalid choice. Please enter 1, 2, or 3.");
        }
    }
}

/*Set all pointers to NULL*/
void createWorldMap(worldMap *wm){
    wm->setWorldToNull();

    //Initialize player
    wm->player = (PC*) malloc(sizeof(PC));
    //wm->player->symb = 0;
    //wm->player->row = 10;
    //wm->player->col = 40;
    wm->player->globalX = 200;
    wm->player->globalY = 200;

    //initialize player pokemons and items
    pcChooseStarterPokemon(wm->player);
    wm->player->numPK = 1;
    wm->player->currPoke = 0;
    wm->player->potions = 3;
    wm->player->pokeballs = 3;
    wm->player->revives = 3;
}

/*spawns a pc in the terrain map*/
void spawnNPC(worldMap *wm, mapclass *terrainMap, int npcType){
    int canPlace = -1;
    NPC* npc = (NPC*)malloc(sizeof(NPC));
    npc->symb = npcType;
    npc->direc = 0;
    npc->defeated=0;
    npcType = npcType == HIKER ? HIKER : 1;
    while (canPlace == -1){
        int row = randomGenerator(NPCROW-1, 0);
        int col = randomGenerator(NPCCOL-1, 0);
        if(calcCost(npcType, terrainMap->terrain[row+1][col+1]) != INFINTY){ //check of terrain is not infinty
            if(terrainMap->npcArray[row][col] == NULL){ //&& (terrainMap->terrain[row+1][col+1] != 'M') && (terrainMap->terrain[row+1][col+1] != 'C')){ 
                terrainMap->npcArray[row][col] = npc;
                npc->row = row;
                npc->col = col;
                canPlace = 0;
            }
        }
    }
    npc->numPK = 1;
    npc->pokemons[0] = new Pokemon(DFC(wm->player->globalX, wm->player->globalY));
    npc->currPoke=0;
    for(int i=1; i<6; i++){
        if(randomGenerator(10, 1) <= 6){
            npc->pokemons[i] = new Pokemon(DFC(wm->player->globalX, wm->player->globalY));
            npc->numPK++;
        } else {
            break;
        }
    }
}

/*adds all npcs to terrain map array*/
void placeNPCS(worldMap *wm, mapclass *terrainMap, int npcNum){
    if(npcNum>=2){
    spawnNPC(wm, terrainMap, HIKER);
    spawnNPC(wm, terrainMap, RIVAL);
    //if statements
    npcNum=npcNum-2;
    while (npcNum>0){
        if(npcNum == npcNum-100 || npcNum == 250-500 || npcNum == npcNum-750 || npcNum == npcNum-1000){
            //printf("hello %d\n", npcNum);
        }
        //printf("npcNum %d\n", npcNum);
        if (npcNum == 1){
            spawnNPC(wm, terrainMap, PACER);
            npcNum--;
            continue;
        }
      int npcType = randomGenerator(5,0);
      switch (npcType){
        case HIKER:
            spawnNPC(wm, terrainMap, HIKER);
            break;
        case RIVAL:
            spawnNPC(wm, terrainMap, RIVAL);
            break;
        case PACER:
            spawnNPC(wm, terrainMap, PACER);
            break;
        case WANDERER:
            spawnNPC(wm, terrainMap, WANDERER);
            break;
        case SENTRIES:
            spawnNPC(wm, terrainMap, SENTRIES);
            break;
        case EXPLORERS:
            spawnNPC(wm, terrainMap, EXPLORERS);
            break;
      }
         npcNum--;  

      }
  }else{
    while (npcNum>0){
      spawnNPC(wm, terrainMap, HIKER);
      npcNum--;  
    }
  }

  
    
}


/*Create a terrain map and add it to world map at position x y*/
void createMap(int x, int y, worldMap *wm, int npcNum){
    
    mapclass *newMap = (mapclass*)malloc(sizeof(mapclass)); //malloc new mapclass
    newMap->row = x; newMap->col = y;//set row and col
    setMap(newMap, x, y, wm); //set mapclass terrain to pseudo NULL values
    createTerrain(newMap); //create a terrain and set it to newMap
    int distanceFromCenter = DFC(x, y); //calculate distance from center
    makeRoads(newMap, distanceFromCenter, x, y, wm);//add roads to map

    wm->arr[x][y] = newMap; //add new terrain map to world map

    //newMap->playerT = wm->player;
    // newMap->playerT->row = wm->player->row;
    // newMap->playerT->col = wm->player->col;

    if(newMap->NPCSInit == 0){
        placeNPCS(wm, newMap, npcNum);
        newMap->NPCSInit = 1;
    }

    heap* h = createHeap();
    newMap->terrainHeap = h;

    //printMap(newMap, wm->player); //print map and player
    
//     newMap->npcArray[0][0] = malloc(sizeof(NPC)); //Hiker
//     newMap->npcArray[0][1] = malloc(sizeof(NPC)); //Rival

//     newMap->npcArray[0][0]->symb = 0;
//     newMap->npcArray[0][1]->symb = 1;

//     dijkstras(wm->player->row, wm->player->col, wm->arr[x][y], newMap->npcArray[0][0]->weightArr, newMap->npcArray[0][0]->symb); //dijkstras for hiker
//     dijkstras(wm->player->row, wm->player->col, wm->arr[x][y], newMap->npcArray[0][1]->weightArr, newMap->npcArray[0][1]->symb); //dijkstras for rival

//     printf("Weights for hiker\n");
//     printWeightMap(wm->arr[x][y]->npcArray[0][0]->weightArr);

//     printf("Weights for rival\n");
//     printWeightMap(wm->arr[x][y]->npcArray[0][1]->weightArr);
}

/*Go to terrain map at x y*/
void fly(int row, int col, worldMap *wm, int npcNum, int gate){
    wm->player->globalX = row;
    wm->player->globalY = col;
    if (wm->arr[row][col] != NULL){
        if (gate == N){
            wm->player->row = ROW - 2;
            wm->player-> col = wm->arr[row][col]->gateS; 
        } else if (gate == E){
            wm->player->row = wm->arr[row][col]->gateW;
            wm->player-> col = 1; 
        } else if (gate == S){
            wm->player->row = 1;
            wm->player-> col = wm->arr[row][col]->gateN; 
        } else if (gate == W){
            wm->player->row = wm->arr[row][col]->gateE;
            wm->player-> col = COL-2; 
        } else {
            if(row > 0 && col > 0){
                wm->player->row = wm->arr[row][col]->connection1[0];
                wm->player-> col = wm->arr[row][col]->connection1[1];
            } else {
                wm->player->row = wm->arr[row][col]->connection2[0];
                wm->player-> col = wm->arr[row][col]->connection2[1];
            }
            
        }
        printMap(wm->arr[row][col], wm->player);
        refresh();
        moveEveryone(wm, wm->arr[row][col], npcNum, wm->arr[row][col]->terrainHeap);
    } else {
        createMap(row, col, wm, npcNum);
        if (gate == N){
            wm->player->row = ROW - 2;
            wm->player-> col = wm->arr[row][col]->gateS; 
            // printMap(wm->arr[row][col], wm->player);
            // refresh();
        } else if (gate == E){
            wm->player->row = wm->arr[row][col]->gateW;
            wm->player-> col = 1; 
            printMap(wm->arr[row][col], wm->player);
        } else if (gate == S){
            wm->player->row = 1;
            wm->player-> col = wm->arr[row][col]->gateN; 
            printMap(wm->arr[row][col], wm->player);
        } else if (gate == W){
            wm->player->row = wm->arr[row][col]->gateE;
            wm->player-> col = COL-2; 
            mvprintw(0, 20, "bb");
            //printMap(wm->arr[row][col], wm->player);
        } else {
            if(row > 0 && col > 0){
                wm->player->row = wm->arr[row][col]->connection1[0];
                wm->player-> col = wm->arr[row][col]->connection1[1];
            } else {
                wm->player->row = wm->arr[row][col]->connection2[0];
                wm->player-> col = wm->arr[row][col]->connection2[1];
            }
            
        }
        printMap(wm->arr[row][col], wm->player);
        refresh();
        moveEveryone(wm, wm->arr[row][col], npcNum, wm->arr[row][col]->terrainHeap);
    }
}

/*calc cost function. Get cost for NPC type*/
int calcCost(int npc, char terrainType){
    int terrainTypeInt;
    switch (terrainType){
        case ROAD:
            terrainTypeInt = 0;
            break;
        case 'M':
            terrainTypeInt = 1;
            break;
        case 'C':
            terrainTypeInt = 2;
            break;
        case GRASS:
            terrainTypeInt = 3;
            break;
        case CLEARING:
            terrainTypeInt = 4;
            break;
        case BOULDER:
            terrainTypeInt = 5;
            break;
        case TREE:
            terrainTypeInt = 6;
            break; 
        case WATER:
            terrainTypeInt = 7;
            break;
        default:
            printf("cost error. Uknown type of terrrain\n");
            break;
    }
                        // 0   1   2   3   4   5   6   7 
                        // P   M   C   T   S   M   F   W   
    int costArr[3][8] = {{10, 50, 50, 15, 10, 15, 15, INFINTY},               //Hiker
                         {10, 50, 50, 20, 10, INFINTY, INFINTY, INFINTY},     //Rival and other
                         {10, 10, 10, 20, 10, INFINTY, INFINTY, INFINTY}};    //PC

    return costArr[npc][terrainTypeInt];
}

/*Function for printing weightmap*/
void printWeightMap(int weightArr[NPCROW][NPCCOL]){
    int i,j;
    printf("\n");
    for(i=0; i<ROW; i++){
        for(j=0; j<COL; j++){
            if(i != 0 && i <= NPCROW && j != 0 && j <= NPCCOL){
                if(weightArr[i-1][j-1] != INFINTY){
                    printf("%2d ", weightArr[i-1][j-1]%100);
                } else {
                    printf("%2s ", "_");
                }
            } else {
                printf("%2s ", "B");
            }
        }
        printf("\n");
    }
}

/*Helper method for dijkstras. Sets all weigts to inity*/
void setWeights(int weightArr[NPCROW][NPCCOL]){
    int i,j;
    for(i=0; i<NPCROW; i++){
        for(j=0; j<NPCCOL; j++){
            weightArr[i][j] = INFINTY;
        }
    }
}

void makeHeapNodeData(heapNode* HN, int i, int j, int type, mapclass* terrainMap){
    //heapNode HN;
  
    HN->row = i;
    HN->col = j;
    HN->weight = calcCost(type, terrainMap->terrain[i+1][j+1]);
    HN->visited = -1;
    //HN = HN1;
    //return &HN;
}

void initHeapNodeDatat(heapNode* HNArr[NPCROW][NPCCOL]){
    int i,j;
    for(i=0; i<NPCROW; i++){
        for(j=0; j<NPCCOL; j++){
            heapNode* HN = (heapNode*)malloc(sizeof(heapNode));
            HN->row = -1;
            HN->col = -1;
            HN->weight = INFINTY;
            HN->visited = -1;
            HNArr[i][j] = HN;
        }
    }
}

/*Function for implemnting dijkstras algorthm. Finds all shortest paths staring at PC depending on NPC type*/
void dijkstras(int row, int col, mapclass* terrainMap, int weightArr[NPCROW][NPCCOL], int type){
    //Initilaize var
    int i,j;
    heap* h = createHeap();
    heapNode* HNArr[NPCROW][NPCCOL]; //heapNodes array if pointers

    setWeights(weightArr); //Set all weights to infinty
    initHeapNodeDatat(HNArr); //Set all heap nodes to null
    
    

    //add all weights to heapNode
    for(i=0; i<NPCROW; i++){
        for(j=0; j<NPCCOL; j++){
            makeHeapNodeData(HNArr[i][j], i, j, type, terrainMap);
        }
    }

    //printWeightMap(weightArr);
    //Set player pos weight to 0
    weightArr[row-1][col-1] = 0;
    insert(h, HNArr[row-1][col-1]);
    //int heapRunCount=0;

    while(h->size > 0){
        heapNode* HN = extractMin(h);

        if(HN->visited == 0)//if visited skip
            continue;

        HN->visited = 0; //set node to visited

         // Check all neighboring nodes to see if their distances need to be updated.
        if (HN->row-1 >= 0){ //Up
            int tentativeDistance = weightArr[HN->row][HN->col] + HNArr[HN->row-1][HN->col]->weight; // Calculate the tentative distance to the neighbor through the current node.
            if(tentativeDistance < weightArr[HN->row-1][HN->col]){ // If the tentative distance is smaller than the current distance to the neighbor, update the distance.
                weightArr[HN->row-1][HN->col] = tentativeDistance;
                insert(h, HNArr[HN->row-1][HN->col]); //enque neighbour
            }
        }

        if (HN->row-1 >= 0 && HN->col+1 < NPCCOL){ //Diagonal up-right
            int tentativeDistance = weightArr[HN->row][HN->col] + HNArr[HN->row-1][HN->col+1]->weight; // Calculate the tentative distance to the neighbor through the current node.
            if(tentativeDistance < weightArr[HN->row-1][HN->col+1]){ // If the tentative distance is smaller than the current distance to the neighbor, update the distance.
                weightArr[HN->row-1][HN->col+1] = tentativeDistance;
                insert(h, HNArr[HN->row-1][HN->col+1]); //enque neighbour
            }
        }

        if (HN->col + 1 < NPCCOL){ //Right
            int tentativeDistance = weightArr[HN->row][HN->col] + HNArr[HN->row][HN->col+1]->weight; // Calculate the tentative distance to the neighbor through the current node.
            if(tentativeDistance < weightArr[HN->row][HN->col+1]){ // If the tentative distance is smaller than the current distance to the neighbor, update the distance.
                weightArr[HN->row][HN->col+1] = tentativeDistance;
                insert(h, HNArr[HN->row][HN->col+1]); //enque neighbour
            }
        }

        if (HN->row+1 < NPCROW && HN->col+1 < NPCCOL){ //Down right
            int tentativeDistance = weightArr[HN->row][HN->col] + HNArr[HN->row+1][HN->col+1]->weight; // Calculate the tentative distance to the neighbor through the current node.
            if(tentativeDistance < weightArr[HN->row+1][HN->col+1]){ // If the tentative distance is smaller than the current distance to the neighbor, update the distance.
                weightArr[HN->row+1][HN->col+1] = tentativeDistance;
                insert(h, HNArr[HN->row+1][HN->col+1]); //enque neighbour
            }
        }

        if (HN->row+1 < NPCROW){ //Down
            int tentativeDistance = weightArr[HN->row][HN->col] + HNArr[HN->row+1][HN->col]->weight; // Calculate the tentative distance to the neighbor through the current node.
            if(tentativeDistance < weightArr[HN->row+1][HN->col]){ // If the tentative distance is smaller than the current distance to the neighbor, update the distance.
                weightArr[HN->row+1][HN->col] = tentativeDistance;
                insert(h, HNArr[HN->row+1][HN->col]); //enque neighbour
            }
        }

        if (HN->row+1 < NPCROW && HN->col-1 >= 0){  //Down Left
            int tentativeDistance = weightArr[HN->row][HN->col] + HNArr[HN->row+1][HN->col-1]->weight; // Calculate the tentative distance to the neighbor through the current node.
            if(tentativeDistance < weightArr[HN->row+1][HN->col-1]){ // If the tentative distance is smaller than the current distance to the neighbor, update the distance.
                weightArr[HN->row+1][HN->col-1] = tentativeDistance;
                insert(h, HNArr[HN->row+1][HN->col-1]); //enque neighbour
            }
        }

        if (HN->col-1 >= 0){ //Left
            int tentativeDistance = weightArr[HN->row][HN->col] + HNArr[HN->row][HN->col-1]->weight; // Calculate the tentative distance to the neighbor through the current node.
            if(tentativeDistance < weightArr[HN->row][HN->col-1]){ // If the tentative distance is smaller than the current distance to the neighbor, update the distance.
                weightArr[HN->row][HN->col-1] = tentativeDistance;
                insert(h, HNArr[HN->row][HN->col-1]); //enque neighbour
            }
        }

        if (HN->row-1 >= 0 && HN->col-1 >= 0){ //Up left
            int tentativeDistance = weightArr[HN->row][HN->col] + HNArr[HN->row-1][HN->col-1]->weight; // Calculate the tentative distance to the neighbor through the current node.
            if(tentativeDistance < weightArr[HN->row-1][HN->col-1]){ // If the tentative distance is smaller than the current distance to the neighbor, update the distance.
                weightArr[HN->row-1][HN->col-1] = tentativeDistance;
                insert(h, HNArr[HN->row-1][HN->col-1]); //enque neighbour
            }
        }
        //heapRunCount++;
    }
    killHeap(h);
}

int getNextSmallestMove(mapclass *terrainMap, NPC* npc, int *row, int *col){
    int minCost = INFINTY;
    int i,j;

    for(i=-1; i<=1; i++){
        for(j=-1; j<=1; j++){
            if(i != 0 && j != 0){
                if(canMove(terrainMap, npc->symb, npc->row+1+i, npc->col+1+j, npc->row+1, npc->col+1) == 1){ 
                    if (minCost > npc->weightArr[npc->row+i][npc->col+j] ){
                        minCost = npc->weightArr[npc->row+i][npc->col+j];
                        *row = npc->row+i;
                        *col = npc->col+j;
                    }
                }
            }
        }
    }
    //mvprintw(ROW+6, 20, "small new row %d, new col %d min cost=%d", *row, *col, minCost);
    refresh();
    return minCost;
}

int moveHiker(mapclass *terrainMap, NPC* hiker){
    if (hiker->defeated == 1){
        return calcCost(HIKER, terrainMap->terrain[hiker->row+1][hiker->col+1]);
    }
    int nextRow, nextCol;
    int prevRow = hiker->row;
    int prevCol = hiker->col;
    nextRow = prevRow;
    nextCol = prevCol;
    int minCost = getNextSmallestMove(terrainMap, hiker, &nextRow, &nextCol);
    //mvprintw(ROW+4, 20, "Hiker move");
        refresh();
    if (minCost != INFINTY){
        hiker->row = nextRow;
        hiker->col = nextCol;
        terrainMap->npcArray[nextRow][nextCol] = hiker;
        terrainMap->npcArray[prevRow][prevCol] = NULL;
        return calcCost(HIKER, terrainMap->terrain[hiker->row+1][hiker->col+1]);
    } else {
        return calcCost(HIKER, terrainMap->terrain[hiker->row+1][hiker->col+1]);
    //mvprintw(ROW+5, 20, "new row %d, new col %d", nextRow, nextCol);
    refresh();
    }  
}

int moveRival(mapclass *terrainMap, NPC* rival){
    if (rival->defeated == 1){
        return calcCost(RIVAL, terrainMap->terrain[rival->row+1][rival->col+1]);
    }
    int nextRow, nextCol;
    int prevRow = rival->row;
    int prevCol = rival->col;
    nextRow = prevRow;
    nextCol = prevCol;
    int minCost = getNextSmallestMove(terrainMap, rival, &nextRow, &nextCol);
    if (minCost != INFINTY){
        rival->row = nextRow;
        rival->col = nextCol;
        terrainMap->npcArray[nextRow][nextCol] = rival;
        terrainMap->npcArray[prevRow][prevCol] = NULL;
        return calcCost(RIVAL, terrainMap->terrain[rival->row+1][rival->col+1]);
    }
    //printf("get next smallest move row %d col %d\n", rival->row, rival->col);
    else{
        return calcCost(RIVAL, terrainMap->terrain[rival->row+1][rival->col+1]);
    }
}

int movePacer(mapclass *terrainMap, NPC* pacer){
    int nextRow, nextCol;
    int prevRow = pacer->row;
    int prevCol = pacer->col;
    if(pacer->direc == 0){
        if(canMove(terrainMap, pacer->symb, pacer->row+1, pacer->col+2, pacer->row+1, pacer->col+1) == 1){
            nextRow = prevRow;
            nextCol = prevCol + 1;
            pacer->row = nextRow;
            pacer->col = nextCol;
            terrainMap->npcArray[nextRow][nextCol] = pacer;
            terrainMap->npcArray[prevRow][prevCol] = NULL;
        } else {
            pacer->direc = 1;
            nextRow = prevRow;
            nextCol = prevCol;
        }
    } else{
        if(canMove(terrainMap, pacer->symb, pacer->row+1, pacer->col, pacer->row+1, pacer->col+1) == 1){
            nextRow = prevRow;
            nextCol = prevCol - 1;
            pacer->row = nextRow;
            pacer->col = nextCol;
            terrainMap->npcArray[nextRow][nextCol] = pacer;
            terrainMap->npcArray[prevRow][prevCol] = NULL;
        } else {
            pacer->direc = 0;
            nextRow = prevRow;
            nextCol = prevCol;
        }
    }
    
    
    return calcCost(RIVAL, terrainMap->terrain[pacer->row+1][pacer->col+1]); 
}

int moveWanderer(mapclass *terrainMap, NPC* wanderer){
    int nextRow, nextCol;
    int prevRow = wanderer->row;
    int prevCol = wanderer->col; 
    nextRow = prevRow;
    nextCol = prevCol;
    
    
    if(wanderer->direc == 0){ //move north
        nextRow = wanderer->row-1;
        nextCol = wanderer->col;
        if (canMove(terrainMap, wanderer->symb, nextRow+1, nextCol+1, prevRow+1, prevCol+1) == 1){
            wanderer->row = nextRow;
            wanderer->col = nextCol;
        } else{
            wanderer->direc = randomGenerator(7,0);
            return calcCost(RIVAL, terrainMap->terrain[wanderer->row+1][wanderer->col+1]);
        }
    }

    else if(wanderer->direc == 1){ //move north west
        nextRow = wanderer->row-1;
        nextCol = wanderer->col+1;
        if (canMove(terrainMap, wanderer->symb, nextRow+1, nextCol+1, prevRow+1, prevCol+1) == 1){
            wanderer->row = nextRow;
            wanderer->col = nextCol;
        } else{
            wanderer->direc = randomGenerator(7,0);
            return calcCost(RIVAL, terrainMap->terrain[wanderer->row+1][wanderer->col+1]);
        }
    }

    else if(wanderer->direc == 2){ //move west
        nextRow = wanderer->row;
        nextCol = wanderer->col+1;
        if (canMove(terrainMap, wanderer->symb, nextRow+1, nextCol+1, prevRow+1, prevCol+1) == 1){
            wanderer->row = nextRow;
            wanderer->col = nextCol;
        } else{
            wanderer->direc = randomGenerator(7,0);
            return calcCost(RIVAL, terrainMap->terrain[wanderer->row+1][wanderer->col+1]);
        }
    }

    else if(wanderer->direc == 3){ //move south west
        nextRow = wanderer->row+1;
        nextCol = wanderer->col+1;
        if (canMove(terrainMap, wanderer->symb, nextRow+1, nextCol+1, prevRow+1, prevCol+1) == 1){
            wanderer->row = nextRow;
            wanderer->col = nextCol;
        } else{
            wanderer->direc = randomGenerator(7,0);
            return calcCost(RIVAL, terrainMap->terrain[wanderer->row+1][wanderer->col+1]);
        }
    }

    else if(wanderer->direc == 4){ //move south
        nextRow = wanderer->row+1;
        nextCol = wanderer->col;
        if (canMove(terrainMap, wanderer->symb, nextRow+1, nextCol+1, prevRow+1, prevCol+1) == 1){
            wanderer->row = nextRow;
            wanderer->col = nextCol;
        } else{
            wanderer->direc = randomGenerator(7,0);
            return calcCost(RIVAL, terrainMap->terrain[wanderer->row+1][wanderer->col+1]);
        }
    }

    else if(wanderer->direc == 5){ //move south east
        nextRow = wanderer->row+1;
        nextCol = wanderer->col-1;
        if (canMove(terrainMap, wanderer->symb, nextRow+1, nextCol+1, prevRow+1, prevCol+1) == 1){
            wanderer->row = nextRow;
            wanderer->col = nextCol;
        } else{
            wanderer->direc = randomGenerator(7,0);
            return calcCost(RIVAL, terrainMap->terrain[wanderer->row+1][wanderer->col+1]);
        }
    }

    else if(wanderer->direc == 6){ //move east
        nextRow = wanderer->row;
        nextCol = wanderer->col-1;
        if (canMove(terrainMap, wanderer->symb, nextRow+1, nextCol+1, prevRow+1, prevCol+1) == 1){
            
            wanderer->row = nextRow;
            wanderer->col = nextCol;
        } else{
            wanderer->direc = randomGenerator(7,0);
            return calcCost(RIVAL, terrainMap->terrain[wanderer->row+1][wanderer->col+1]);
        }
    }

    else if(wanderer->direc == 7){ //move north east
        nextRow = wanderer->row-1;
        nextCol = wanderer->col-1;
        if (canMove(terrainMap, wanderer->symb, nextRow+1, nextCol+1, prevRow+1, prevCol+1) == 1){
            wanderer->row = nextRow;
            wanderer->col = nextCol;
        } else{
            wanderer->direc = randomGenerator(7,0);
            return calcCost(RIVAL, terrainMap->terrain[wanderer->row+1][wanderer->col+1]);
        }
    }


    terrainMap->npcArray[prevRow][prevCol] = NULL;
    terrainMap->npcArray[nextRow][nextCol] = wanderer;
    return calcCost(RIVAL, terrainMap->terrain[wanderer->row+1][wanderer->col+1]);
}

int moveExplorer(mapclass *terrainMap, NPC* explorer){
    int nextRow, nextCol;
    int prevRow = explorer->row;
    int prevCol = explorer->col; 
    nextRow = prevRow;
    nextCol = prevCol;
    
    
    if(explorer->direc == 0){ //move north
        if (canMove(terrainMap, explorer->symb, explorer->row+1-1, explorer->col+1, prevRow+1, prevCol+1) == 1){
            nextRow = explorer->row-1;
            nextCol = explorer->col;
            explorer->row = nextRow;
            explorer->col = nextCol;
        } else{
            explorer->direc = randomGenerator(7,0);
        }
    }

    else if(explorer->direc == 1){ //move north west
        if (canMove(terrainMap, explorer->symb, explorer->row+1-1, explorer->col+1+1, prevRow+1, prevCol+1) == 1){
            nextRow = explorer->row-1;
            nextCol = explorer->col+1;
            explorer->row = nextRow;
            explorer->col = nextCol;
        } else{
            explorer->direc = randomGenerator(7,0);
        }
    }

    else if(explorer->direc == 2){ //move west
        if (canMove(terrainMap, explorer->symb, explorer->row+1, explorer->col+1+1, prevRow+1, prevCol+1) == 1){
            nextRow = explorer->row;
            nextCol = explorer->col+1;
            explorer->row = nextRow;
            explorer->col = nextCol;
        } else{
            explorer->direc = randomGenerator(7,0);
        }
    }

    else if(explorer->direc == 3){ //move south west
        if (canMove(terrainMap, explorer->symb, explorer->row+1+1, explorer->col+1+1, prevRow+1, prevCol+1) == 1){
            nextRow = explorer->row+1;
            nextCol = explorer->col+1;
            explorer->row = nextRow;
            explorer->col = nextCol;
        } else{
            explorer->direc = randomGenerator(7,0);
        }
    }

    else if(explorer->direc == 4){ //move south
        if (canMove(terrainMap, explorer->symb, explorer->row+1+1, explorer->col+1, prevRow+1, prevCol+1) == 1){
            nextRow = explorer->row+1;
            nextCol = explorer->col;
            explorer->row = nextRow;
            explorer->col = nextCol;
        } else{
            explorer->direc = randomGenerator(7,0);
        }
    }

    else if(explorer->direc == 5){ //move south east
        if (canMove(terrainMap, explorer->symb, explorer->row+1+1, explorer->col+1-1, prevRow+1, prevCol+1) == 1){
            nextRow = explorer->row+1;
            nextCol = explorer->col-1;
            explorer->row = nextRow;
            explorer->col = nextCol;
        } else{
            explorer->direc = randomGenerator(7,0);
        }
    }

    else if(explorer->direc == 6){ //move east
        if (canMove(terrainMap, explorer->symb, explorer->row+1, explorer->col+1-1, prevRow+1, prevCol+1) == 1){
            nextRow = explorer->row;
            nextCol = explorer->col-1;
            explorer->row = nextRow;
            explorer->col = nextCol;
        } else{
            explorer->direc = randomGenerator(7,0);
        }
    }

    else if(explorer->direc == 7){ //move north east
        if (canMove(terrainMap, explorer->symb, explorer->row+1-1, explorer->col+1-1, prevRow+1, prevCol+1) == 1){
            nextRow = explorer->row-1;
            nextCol = explorer->col-1;
            explorer->row = nextRow;
            explorer->col = nextCol;
        } else{
            explorer->direc = randomGenerator(7,0);
        }
    }


    
    terrainMap->npcArray[prevRow][prevCol] = NULL;
    terrainMap->npcArray[nextRow][nextCol] = explorer;
    return calcCost(RIVAL, terrainMap->terrain[explorer->row+1][explorer->col+1]); 
}

/*fucntion for checking if next move is possibel. row and col is of ROW and COL size*/
int canMove(mapclass *terrainMap, int symb, int row, int col, int prevRow, int prevCol){
    switch (symb) {
        case HIKER:
            if ( (row > 0 && row < ROW - 1 && col > 0 && col < COL-1)  && //check if in border 
            terrainMap->npcArray[row-1][col-1] == NULL && terrainMap->npcArray[prevRow-1][prevCol-1]->weightArr[prevRow-1][prevCol-1] != INFINTY//check if terrain not infinty     
            && terrainMap->npcArray[prevRow-1][prevCol-1]->defeated == 0){   //not defeated
                return 1;
            } else {
                return -1;
            }
        case RIVAL:
            if ((row > 0 && row < ROW - 1 && col > 0 && col < COL-1) && //check if in border
            terrainMap->npcArray[row-1][col-1] == NULL){
                if (terrainMap->npcArray[prevRow-1][prevCol-1]->weightArr[prevRow-1][prevCol-1] != INFINTY//check if terrain not infinty and is empty
                && terrainMap->npcArray[prevRow-1][prevCol-1]->defeated == 0){   //not defeated
                    return 1;
                } else{
                    return -1;
                }
            } else {
                return -1;
            }
        case PACER:
            if ((row > 0 && row < ROW - 1 && col > 0 && col < COL-1) && //check if in border
            terrainMap->npcArray[row-1][col-1] == NULL && terrainMap->npcArray[prevRow-1][prevCol-1]->weightArr[prevRow-1][prevCol-1] != INFINTY ){//is empty //calcCost(terrainMap->terrain[prevRow][prevCol], 1) != INFINTY
                return 1;
            } else {
                return -1;
            }
        case WANDERER:
            if ((row > 0 && row < ROW - 1 && col > 0 && col < COL-1) && //check if in border
            terrainMap->npcArray[row-1][col-1] == NULL && terrainMap->npcArray[prevRow-1][prevCol-1]->weightArr[prevRow-1][prevCol-1] != INFINTY && //is empty
            terrainMap->terrain[row][col] == terrainMap->terrain[prevRow][prevCol]){ //same kind of terrain
                return 1;
            } else {
                return -1;
            }
        case SENTRIES:
            return 1;
        case EXPLORERS:
            if ((row > 0 && row < ROW - 1 && col > 0 && col < COL-1) && //check if in border
            terrainMap->npcArray[row-1][col-1] == NULL && terrainMap->npcArray[prevRow-1][prevCol-1]->weightArr[prevRow-1][prevCol-1] != INFINTY){//is empty
                return 1;
            } else {
                return -1;
            }
        default: //PC
            if (calcCost(2, terrainMap->terrain[row][col]) != INFINTY && //terrain not infinty
            //terrainMap->npcArray[row-1][col-1] == NULL && //terrain is empty
            row > 0 && row < ROW-1 && col > 0 && col < COL-1){  //bounds checking
                return 1;
            } else {
                return -1;
            }
    }
}



void moveEveryone(worldMap *wm, mapclass *terrainMap, int numTrainers, heap *h){
    /*
    init heap
    add player to heap
    init players if not
        add players to que

    move everyone based on move weight
        get next position
        get cost
    print when players turn
    move player in square for now
    */

   int npcRow = ROW+2;
    
    heapNode* hnNPC = (heapNode*)malloc(sizeof(heapNode));
    hnNPC->npc=NULL;
    hnNPC->pc=wm->player;
    hnNPC->weight=0;
    insert(h, hnNPC);
    int i,j;
    for(i=0; i<NPCROW; i++){
        for(j=0; j<NPCCOL; j++){
            if(terrainMap->npcArray[i][j] != NULL){
                heapNode* hn = (heapNode*)malloc(sizeof(heapNode));
                hn->npc = terrainMap->npcArray[i][j];
                hn->pc = NULL;
                hn->weight = 0;
                insert(h, hn);
            }
        }
    }

    //int pcMove = 0;

    while(h->size > 0){
        heapNode* hn = extractMin(h);
        int i, j;

        if(hn->pc != NULL){
            heapNode* newHN =(heapNode*) malloc(sizeof(heapNode));
            

            for(i=0; i<NPCROW; i++){
                for(j=0; j<NPCCOL; j++){
                    if(terrainMap->npcArray[i][j] != NULL && (terrainMap->npcArray[i][j]->symb == HIKER || terrainMap->npcArray[i][j]->symb == RIVAL)){
                        dijkstras(hn->pc->row, hn->pc->col, terrainMap, terrainMap->npcArray[i][j]->weightArr, terrainMap->npcArray[i][j]->symb);
                    }
                }
            }

            char in;

    while(in !='Q'){
        //printMap(terrainMap, pc);
        //c = heap_remove_min(&world.cur_map->turn);
            
            in = getchar();
            if(in=='7'||in=='y'){ //NW
                moveOnGate(wm, terrainMap, hn->pc, hn->pc->row-1, hn->pc->col-1, hn->pc->row, hn->pc->col, NW,numTrainers);
                if(canMove(terrainMap, 6 ,hn->pc->row-1, hn->pc->col-1, hn->pc->row, hn->pc->col) == 1){
                    int wt = hn->weight;
                    wt += movePC(wm, terrainMap, hn->pc, NW);
                    newHN->pc = hn->pc;
                    newHN->weight = wt;
                    insert(h, newHN);
                    free(hn);
                    printMap(terrainMap, newHN->pc);
                break;
                }
                
            }else if (in=='8'||in=='k'){ //N
                moveOnGate(wm, terrainMap, hn->pc, hn->pc->row-1, hn->pc->col, hn->pc->row, hn->pc->col, N,numTrainers);
                //mvprintw(0, 0, "row: %d, col %d", hn->pc->row, hn->pc->col);
                if(canMove(terrainMap, 6 ,hn->pc->row-1, hn->pc->col, hn->pc->row, hn->pc->col) == 1){
                    int wt = hn->weight;
                    wt += movePC(wm, terrainMap, hn->pc, N);
                    newHN->pc = hn->pc;
                    newHN->weight = wt;
                    insert(h, newHN);
                    free(hn);
                    printMap(terrainMap, newHN->pc);
                break;
                }
            }else if (in=='9'||in=='u'){ //NE
                moveOnGate(wm, terrainMap, hn->pc, hn->pc->row-1, hn->pc->col+1, hn->pc->row, hn->pc->col, NE,numTrainers);
                if(canMove(terrainMap, 6 , hn->pc->row-1, hn->pc->col+1, hn->pc->row, hn->pc->col) == 1){
                    int wt = hn->weight;
                    wt += movePC(wm, terrainMap, hn->pc, NE);
                    newHN->pc = hn->pc;
                    newHN->weight = wt;
                    insert(h, newHN);
                    free(hn);
                    printMap(terrainMap, newHN->pc);
                break;
                }
            }else if (in=='6'||in=='l'){ //E
                moveOnGate(wm, terrainMap, hn->pc, hn->pc->row, hn->pc->col+1, hn->pc->row, hn->pc->col, E,numTrainers);
                if(canMove(terrainMap, 6 ,hn->pc->row, hn->pc->col+1, hn->pc->row, hn->pc->col) == 1){
                    int wt = hn->weight;
                    wt += movePC(wm, terrainMap, hn->pc, E);
                    newHN->pc = hn->pc;
                    newHN->weight = wt;
                    insert(h, newHN);
                    free(hn);
                    printMap(terrainMap, newHN->pc);
                break;
                }
            }else if (in=='3'||in=='n'){ //SE
                moveOnGate(wm, terrainMap, hn->pc, hn->pc->row+1, hn->pc->col+1, hn->pc->row, hn->pc->col, SE,numTrainers);
                if(canMove(terrainMap, 6 ,hn->pc->row+1, hn->pc->col+1, hn->pc->row, hn->pc->col) == 1){
                    int wt = hn->weight;
                    wt += movePC(wm, terrainMap, hn->pc, SE);
                    newHN->pc = hn->pc;
                    newHN->weight = wt;
                    insert(h, newHN);
                    free(hn);
                    printMap(terrainMap, newHN->pc);
                break;
                }
            }else if (in=='2'||in=='j'){ //S
            moveOnGate(wm, terrainMap, hn->pc, hn->pc->row+1, hn->pc->col, hn->pc->row, hn->pc->col, S,numTrainers);
                if(canMove(terrainMap, 6 ,hn->pc->row+1, hn->pc->col, hn->pc->row, hn->pc->col) == 1){
                    int wt = hn->weight;
                    wt += movePC(wm, terrainMap, hn->pc, S);
                    newHN->pc = hn->pc;
                    newHN->weight = wt;
                    insert(h, newHN);
                    free(hn);
                    printMap(terrainMap, newHN->pc);
                break;
                }
            }else if (in=='1'||in=='b'){ //SW
                moveOnGate(wm, terrainMap, hn->pc, hn->pc->row+1, hn->pc->col-1, hn->pc->row, hn->pc->col, SW,numTrainers);
                if(canMove(terrainMap, 6 ,hn->pc->row+1, hn->pc->col-1, hn->pc->row, hn->pc->col) == 1){
                    int wt = hn->weight;
                    wt += movePC(wm, terrainMap, hn->pc, SW);
                    newHN->pc = hn->pc;
                    newHN->weight = wt;
                    insert(h, newHN);
                    free(hn);
                    printMap(terrainMap, newHN->pc);
                break;
                }
            }else if (in=='4'||in=='h'){ //W
                moveOnGate(wm, terrainMap, hn->pc, hn->pc->row, hn->pc->col-1, hn->pc->row, hn->pc->col, W,numTrainers);
                if(canMove(terrainMap, 6 ,hn->pc->row, hn->pc->col-1, hn->pc->row, hn->pc->col) == 1){
                    int wt = hn->weight;
                    wt += movePC(wm, terrainMap, hn->pc, W);
                    newHN->pc = hn->pc;
                    newHN->weight = wt;
                    insert(h, newHN);
                    free(hn);
                    printMap(terrainMap, newHN->pc);
                break;
                }
            }else if (in=='t'){
                trainerList(terrainMap, hn->pc);
                printMap(terrainMap, hn->pc);
            }else if (in=='>'){
                if (terrainMap->terrain[hn->pc->row][hn->pc->col] == 'C' || terrainMap->terrain[hn->pc->row][hn->pc->col] == 'M') {
                    enterBuilding(terrainMap->terrain[hn->pc->row][hn->pc->col], hn->pc);
                }
                // movePC(wm, terrainMap, hn->pc, "NW");
                printMap(terrainMap, hn->pc);
            }else if (in==' '||in=='.'||in=='5'){
                // movePC(wm, terrainMap, hn->pc, "5"); 
                int wt = hn->weight;
                wt += movePC(wm, terrainMap, hn->pc, SKIP);
                newHN->pc = hn->pc;
                newHN->weight = wt;
                insert(h, newHN);
                free(hn);
                printMap(terrainMap, newHN->pc); //Dont forget to add pc to PQ based and add weight
                break;
            } else if (in == 'f'){
                //print message then enter cords then fly
                int userX;
                int userY;
                mvprintw(0,0,"Enter x y coordinates");
                refresh();
                if (scanf(" %d %d", &userX, &userY) != 1) {
                    /* To handle EOF */
                    putchar('\n');
                    userX+=200;
                    userY+=200;
                    if(userX >= worldXSize || userX < 0 || userY >= worldYSize || userY < 0){
                        //printf("invalid coordinates\n");
                    } else {
                        // currX = userX;
                        // currY = userY;
                        fly(userX, userY, wm, numTrainers, 9);
                    }
                }
            } else if (in == 'Q' || in == 'q'){
                endwin();
                exit(0);
                //return;
            } else if (in == 'B'){ //Open bag
                wm->player->openBag(0);
                printMap(terrainMap, hn->pc);
            } else if (in == 'W'){
                saveGameState(wm);
            }
            
            else{
                //printw("unknown character. Try again!");

            }  
    }
        } else {
            int type = hn->npc->symb;
            int wt = INFINTY;
            heapNode* newHN = (heapNode*)malloc(sizeof(NPC));
            //mvprintw(npcRow, 0, "npc %d", hn->npc->symb);
            refresh();
            switch(type){
                case HIKER:
                    wt = moveHiker(terrainMap, hn->npc);
                    //heapNode* newHN = malloc(sizeof(NPC));
                    newHN->weight = hn->weight + wt;
                    newHN->npc = hn->npc;
                    newHN->pc = NULL;
                    if (newHN->npc->row+1 == wm->player->row && newHN->npc->col+1 == wm->player->col && newHN->npc->defeated == 0){
                        enterBattle(newHN->npc, wm->player);
                        printMap(terrainMap, wm->player);
                    }
                    insert(h, newHN);
                    free(hn);
                    break;
                case RIVAL:
                    wt = moveRival(terrainMap, hn->npc);
                    
                    //heapNode* newHN = malloc(sizeof(NPC));
                    newHN->weight = hn->weight + wt;
                    newHN->npc = hn->npc;
                    newHN->pc = NULL;
                    if (newHN->npc->row+1 == wm->player->row && newHN->npc->col+1 == wm->player->col && newHN->npc->defeated == 0){
                        enterBattle(newHN->npc, wm->player);
                        printMap(terrainMap, wm->player);
                    }
                    insert(h, newHN);
                    free(hn);
                    break;
                case PACER:
                    //printf("moving pacer\n");
                    wt = movePacer(terrainMap, hn->npc);
                    //heapNode* newHN = malloc(sizeof(NPC));
                    newHN->weight = hn->weight + wt;
                    newHN->npc = hn->npc;
                    newHN->pc = NULL;
                    if (newHN->npc->row+1 == wm->player->row && newHN->npc->col+1 == wm->player->col && newHN->npc->defeated == 0){
                        enterBattle(newHN->npc, wm->player);
                        printMap(terrainMap, wm->player);
                    }
                    insert(h, newHN);
                    free(hn);
                    break;
                case WANDERER:
                    wt = moveWanderer(terrainMap, hn->npc);
                    //heapNode* newHN = malloc(sizeof(NPC));
                    newHN->weight = hn->weight + wt;
                    newHN->npc = hn->npc;
                    newHN->pc = NULL;
                    if (newHN->npc->row+1 == wm->player->row && newHN->npc->col+1 == wm->player->col && newHN->npc->defeated == 0){
                        enterBattle(newHN->npc, wm->player);
                        printMap(terrainMap, wm->player);
                    }
                    insert(h, newHN);
                    free(hn);
                    break;
                case SENTRIES:
                    //heapNode* newHN = malloc(sizeof(NPC));
                    newHN->weight = hn->weight + 10;
                    newHN->npc = hn->npc;
                    newHN->pc = NULL;
                    if (newHN->npc->row+1 == wm->player->row && newHN->npc->col+1 == wm->player->col && newHN->npc->defeated == 0){
                        enterBattle(newHN->npc, wm->player);
                        printMap(terrainMap, wm->player);
                    }
                    insert(h, newHN);
                    free(hn);
                    break;
                case EXPLORERS:
                    wt = moveExplorer(terrainMap, hn->npc);
                    //heapNode* newHN = malloc(sizeof(NPC));
                    newHN->weight = hn->weight + wt;
                    newHN->npc = hn->npc;
                    newHN->pc = NULL;
                    if (newHN->npc->row+1 == wm->player->row && newHN->npc->col+1 == wm->player->col && newHN->npc->defeated == 0){
                        enterBattle(newHN->npc, wm->player);
                        printMap(terrainMap, wm->player);
                    }
                    insert(h, newHN);
                    free(hn);
                    break;
            }
            ++npcRow;
        }
    }

    
return;
   
}

void enterBuilding(char building, PC *pc){
    clear();
    mvprintw(1,1, "You entered a building");
    if (building == 'C') {
        mvprintw(2,1, "Pokemon healed");
        pc->visitCenter();
    } else if (building == 'M') {
        mvprintw(2,1, "Bag filled");
        pc->visitMart();
    }
    refresh();
    char in;
    while((in = getchar()) != '<'){}
}

void copyToScreen(char buffer[1000][80], char c, char ns, char ew, int row, int col, int i) {
  if (ns == 'n') {
    if (ew == 'e') {
      snprintf(buffer[i], sizeof(buffer[i]), "%c, %i North and %i East", c, row, col);
    } else {
      snprintf(buffer[i], sizeof(buffer[i]), "%c, %i North and %i West", c, row, col);
    }
  } else {
    if (ew == 'e') {
      snprintf(buffer[i], sizeof(buffer[i]), "%c, %i South and %i East", c, row, col);
    } else {
      snprintf(buffer[i], sizeof(buffer[i]), "%c, %i South and %i West", c, row, col);
    }
  }
}

void trainerList(mapclass *terrainMap, PC *pc){
 clear();
  char buffer[1000][80];
  int i = 0;
  char toPrint = 'x';
  char ns = 'x';
  int difY = 0;
  int difX = 0;
  char ew = 'x';

  scrollok(stdscr, TRUE); // Enable scrolling
  snprintf(buffer[i], sizeof(buffer[i]), "Trainer List! (press 'esc' to close)\n");
  mvprintw(i, 0, buffer[i]);
  i++;
  refresh();

  int startRow = 0;
  int endRow = 20;

  int pcRow = pc->row -1;
  int pcCol = pc->col -1;

  for (int row = 0; row < NPCROW; row++) {
    for (int col = 0; col < NPCCOL; col++) {

        NPC *npc = terrainMap->npcArray[row][col];

      if (!npc) {continue;}

      if (npc->symb == HIKER) {
        toPrint = 'h';
      } else if (npc->symb == RIVAL) {
        toPrint ='r';
      } else if (npc->symb == WANDERER) {
        toPrint ='w';
      } else if (npc->symb == EXPLORERS) {
        toPrint ='e';
      } else if (npc->symb == PACER) {
        toPrint ='p';
      } else if (npc->symb == SENTRIES) {
        toPrint = 's';
      }

      if (row > pcRow) {
        difY = abs(pcRow - row);
        ns = 's';
      } else {
        ns = 'n';
        difY = (pcRow - row);
      }

      if (col > pcCol) {
        ew = 'e';
        difX = abs(pcCol - col);
      } else {
        ew = 'w';
        difX = pcCol - col;
      }

      copyToScreen(buffer, toPrint, ns, ew, difY, difX, i);
      refresh();
      i++;
    }
  }

  for (int f = 0; f < endRow; f++) {
    mvprintw(f, 0, buffer[f]);
  }
    keypad(stdscr, TRUE);
  int ch;
    while ((ch = getch()) != 27) {
        //mvprintw(10, 10, (char) ch);
        
        
        switch(ch) {
            case KEY_UP:
                if (startRow > 0) {
                    startRow--;
                    endRow--;
                }
                break;
            case KEY_DOWN:
                if (endRow < 999) {
                    startRow++;
                    endRow++;
                }
                break;
        }

        // Redraw visible content
        clear();
        for (int x = startRow; x < endRow; x++) {
            mvprintw(x - startRow, 0, buffer[x]);
        }
        refresh();
    }

  clear();
}


void enterBattle(NPC *npc, PC *pc) { //TODO
    clear();
    mvprintw(0, 0, "Trainer wants to battle! They have. First Pokemon is %s", npc->pokemons[npc->currPoke]->identfier);
    mvprintw(1,0, "You can 'f' to fight, 'B' for bag, and 's' to switch Pokemon");
    mvprintw(11, 11, "Trainer has %d, %d", npc->numPK, npc->currPoke);
    refresh();
    pc->findFirstPoke(); //Get first pokemon not knocked out
    int fc = 0;
    bool runCondition = true;

    while(runCondition){
        Pokemon *spawnedPokemon = npc->pokemons[npc->currPoke];
        int in = getch();
        if(in == 'f' && fc == 0){
            //fight
            int fightResult = fight(pc, spawnedPokemon, npc, 0);
            if(fightResult == WILDDEFEATED){ //TODO
                mvprintw(9,0, "You defeated the enemy %s!", spawnedPokemon->identfier);
                //npc->currPoke++;
                refresh();
                sleep(3);
            } else if (fightResult == 4){
                runCondition = false;
                break;
            }
        } else if (in == 'B'){
            //bag
           pc->openBag(-1);
        } else if (in == 's'){
            //switch pokemon
            clear();
            mvprintw(0,0, "Choose a Pokemon to switch to or press space to cancel. You can only choose Pokemon that are not knocked out.");
            for(int i = 0; i < pc->numPK; i++){
                mvprintw(i+1,0, "Pokemon %d: %s. Health: %d", i+1, pc->pokemons[i]->identfier, pc->pokemons[i]->currHealth);
            }
            int in;
            while ((in = getch()) != 32){
                if(in == '1' && pc->pokemons[0]->currHealth > 0){
                    pc->currPoke = 0;
                    fight(pc, spawnedPokemon, npc, 1);
                    break;
                } else if (in == '2' && pc->pokemons[1]->currHealth > 0){
                    pc->currPoke = 1;
                    fight(pc, spawnedPokemon, npc, 1);
                    break;
                } else if (in == '3' && pc->pokemons[2]->currHealth > 0){
                    pc->currPoke = 2;
                    fight(pc, spawnedPokemon, npc, 1);
                    break;
                } else if (in == '4' && pc->pokemons[3]->currHealth > 0){
                    pc->currPoke = 3;
                    fight(pc, spawnedPokemon, npc, 1);
                    break;
                } else if (in == '5' && pc->pokemons[4]->currHealth > 0){
                    pc->currPoke = 4;
                    fight(pc, spawnedPokemon, npc, 1);
                    break;
                } else if (in == '6' && pc->pokemons[5]->currHealth > 0){
                    pc->currPoke = 5;
                    fight(pc, spawnedPokemon, npc, 1);
                    break;
                } 
            }
        }
        if (pc->isDefeated()){
            runCondition = false;
            clear();
            mvprintw(0,0, "You have been defeated!");
            refresh();
            sleep(2);
        }
        if (npc->isDefeated()){
            runCondition = false;
            for (int i=0; i< pc->numPK; i++){
                pc->pokemons[i]->levelUp();
            }
            clear();
            mvprintw(0,0, "You have defeated the trainer!");
            refresh();
            sleep(2);
        }
        clear();
        mvprintw(0,0, "Enemy Pokemon %s appeared! They are level %d.", spawnedPokemon->identfier, spawnedPokemon->level);
        mvprintw(1,0, "You can 'f' to fight, 'B' for bag, 'r' to run, and 's' to switch Pokemon");
        mvprintw(11, 11, "Trainer has %d, %d", npc->numPK, npc->currPoke);
        refresh();
    }
   
}

int movePC(worldMap *wm, mapclass *terrainMap, PC *pc, int direc){

    switch(direc){
        case NE:
            pc->row-=1;
            pc->col+=1;
            break;
        case N:
            pc->row-=1;
            break;
        case NW:
            pc->row-=1;
            pc->col-=1;
            break;
        case W:
            pc->col-=1;
            break;
        case SW:
            pc->row+=1;
            pc->col-=1;
            break;
        case S:
            pc->row+=1;
            break;
        case SE:
            pc->row+=1;
            pc->col+=1;
            break;
        case E:
            pc->col+=1; 
            break;
        case SKIP:
            break;
    }
    if (terrainMap->npcArray[pc->row-1][pc->col-1] != NULL && terrainMap->npcArray[pc->row-1][pc->col-1]->defeated == 0) {
        enterBattle(terrainMap->npcArray[pc->row-1][pc->col-1], pc);
        printMap(terrainMap, pc);
    }
    if(terrainMap->terrain[pc->row][pc->col] == GRASS){
       int ranVal = randomGenerator(10, 1);

       if (ranVal == 1){
           encounterPokemon(pc);
       }
    }

    return calcCost(2, terrainMap->terrain[pc->row][pc->col]);
}

/**
 * Determines the order of moves in a Pokemon battle.
 * 
 * @param pc Pointer to the player character.
 * @param wildPokemon Pointer to the wild Pokemon.
 * @param pcmove Pointer to the move chosen by the player.
 * @param npcmove Pointer to the move chosen by the wild Pokemon.
 * @return 1 if the player goes first, 0 if the wild Pokemon goes first.
 */
int whoGoesFirst(PC *pc, Pokemon *wildPokemon, Moves *pcmove, Moves *npcmove){
    if (pcmove->priority > npcmove->priority){
        return 1;
    } else if (pcmove->priority < npcmove->priority){
        return 0;
    } else {
        if (pc->pokemons[pc->currPoke]->speed > wildPokemon->speed){
            return 1;
        } else if (pc->pokemons[pc->currPoke]->speed < wildPokemon->speed){
            return 0;
        } else {
            return randomGenerator(1, 0);
        }
    }
}

/**
 * Calculates the damage dealt by a Pokemon's attack.
 * 
 * @param attacker Pointer to the attacking Pokemon.
 * @param defender Pointer to the defending Pokemon.
 * @param move Pointer to the move used.
 * @param isPC Integer indicating whether the attacker is the player character (1 if yes, 0 if no).
 * @return The amount of damage dealt.
 */
int attack(Pokemon *attacker, Pokemon *defender, Moves *move, int isPC){
    if (rand() % 100 <= move->accuracy){
        float crit = (randomGenerator(255, 0) < floor(attacker->baseSpeed/2)) ? 1.5 : 1;
        float rand = (float)randomGenerator(100, 85) / 100;
        float stab = move->type_id == attacker->type ? 1.5 : 1;
        int type = 1;
        mvprintw(20, 80, "DBG%d", 2800);
        int damage = (((((2*(float)attacker->level/5) + 2) * ((float)move->power) * ((float)attacker->attack/(float)defender->defense))/50) + 2)*crit*rand*stab*type;
        mvprintw(20, 80, "DBG%d", dbNum++);
        defender->currHealth -= damage;
        mvprintw(20, 80, "DBG%d", 2804);
        if (isPC == 1){
            mvprintw(8, 30, "It did %d damage!", damage);
            refresh();
            sleep(5);
        } else {
            mvprintw(8, 30, "It did %d damage!", damage);
            refresh();
            sleep(5);
        }
        if (defender->currHealth <= 0){
            defender->currHealth = 0;
            return ENEMYDEFEATED;
        }
        return 3;
    }
    return 0;
}

int fightNPCTurn(NPC *npc, Pokemon* wp, PC *pc, int pMove){ //TODO randomGenerator(2, 1)
    if (npc != NULL){
        wp = npc->pokemons[npc->currPoke];
    }
    if (pMove == 1){
        move(8,0);
        clrtoeol();
        mvprintw(8, 0, "Enemy chose %s. ", wp->pkMoves[0].identifier);
        int npcAttack = attack(wp, pc->pokemons[pc->currPoke], &wp->pkMoves[0], 0);
        if (npcAttack == ENEMYDEFEATED){return PLAYERDEFEATED;}
        else if(npcAttack == 0){
            mvprintw(8, 30, "Move missed!");
            refresh();
            sleep(2);
        }
    } else {
        move(8,0);
        clrtoeol();
        mvprintw(8, 0, "Enemy chose %s. ", wp->pkMoves[0].identifier);
        int npcAttack = attack(wp, pc->pokemons[pc->currPoke], &wp->pkMoves[1], 0);
        if (npcAttack == ENEMYDEFEATED){return PLAYERDEFEATED;} 
        else if(npcAttack == 0){
            mvprintw(8, 30, "Move missed!");
            refresh();
            sleep(2);
        }
    }
    return 0;
}

int fight(PC *pc, Pokemon *wildPokemon, NPC *npc, int switchP){ //TODO
    move(8,0);
    if (npc != NULL){
        wildPokemon = npc->pokemons[npc->currPoke];
    }
    
    clear(); // Clear the screen

    // Display the enemy Pokemon's name, health, and level
    mvprintw(0, 0, "Enemy Pokemon: %s", wildPokemon->identfier);
    mvprintw(1, 0, "Level: %d", wildPokemon->level);
    mvprintw(2, 0, "Health: %d", wildPokemon->currHealth);
    mvprintw(2, 15, "|");
    for(int j=0; j<29; j++){
        int till = (int)((float)wildPokemon->currHealth/(float)wildPokemon->health*29);
        if(j<till){
            mvprintw(2, j+16, "-");
        } else if (j==till){
            mvprintw(2, j+16, "+");
        } else {
            mvprintw(2, j+16, " ");
        }
    }
    mvprintw(2, 45, "|");

    // Display the player's Pokemon's name, health, and level
    mvprintw(4, 20, "Your Pokemon: %s", pc->pokemons[pc->currPoke]->identfier);
    mvprintw(5, 20, "Level: %d", pc->pokemons[pc->currPoke]->level);
    mvprintw(6, 20, "Health: %d", pc->pokemons[pc->currPoke]->currHealth);
    mvprintw(6, 35, "|");
    for(int j=0; j<29; j++){
        int till = (int)((float)pc->pokemons[pc->currPoke]->currHealth/(float)pc->pokemons[pc->currPoke]->health*29);
        if(j<till){
            mvprintw(6, j+36, "-");
        } else if (j==till){
            mvprintw(6, j+36, "+");
        } else {
            mvprintw(6, j+36, " ");
        }
    }
    mvprintw(6, 65, "|");

    

    // List the player's Pokemon moves
    mvprintw(10, 0, "Your Pokemon's Moves:");
    for(int i = 0; i < (int)pc->pokemons[pc->currPoke]->pkMoves.size(); i++) {
        mvprintw(11+i, 0, "%d. %s", i+1, pc->pokemons[pc->currPoke]->pkMoves[i].identifier);
    }

    refresh(); // Refresh the screen to show the changes

    char in = getch(); // Get the user's input
    clrtoeol();
    int npcMove = randomGenerator(2, 1);

    if (in == '1'){
        if (whoGoesFirst(pc, wildPokemon, &pc->pokemons[pc->currPoke]->pkMoves[0], &wildPokemon->pkMoves[npcMove]) == 1 && switchP == 0 ){
            mvprintw(8, 0, "You chose %s! ", pc->pokemons[pc->currPoke]->pkMoves[0].identifier);
            mvprintw(20, 80, "DBG%d", 2912);
            if (attack(pc->pokemons[pc->currPoke], wildPokemon, &pc->pokemons[pc->currPoke]->pkMoves[0], 1) == ENEMYDEFEATED){
                if (npc != NULL){
                    npc->currPoke++;
                    return WILDDEFEATED;
                } else {
                    return WILDDEFEATED;
                }
            } else {
                mvprintw(8, 30, "Move missed!");
            }
            mvprintw(20, 80, "DBG%d", 2923);
            refresh();
            sleep(2);
            if (fightNPCTurn(npc, wildPokemon, pc, npcMove) == PLAYERDEFEATED){
                pc->findFirstPoke();
                mvprintw(9,0 ,"Your Pokemon was knocked out!");
                refresh();
                sleep(3);
            }
        } else {
            if (fightNPCTurn(npc, wildPokemon, pc, npcMove) == PLAYERDEFEATED){
                pc->findFirstPoke();
                mvprintw(9,0 ,"Your Pokemon was knocked out!");
                refresh();
                sleep(3);
                return PLAYERDEFEATED;
            }
            mvprintw(8, 0, "You chose %s! ", pc->pokemons[pc->currPoke]->pkMoves[0].identifier);
            if (attack(pc->pokemons[pc->currPoke], wildPokemon, &pc->pokemons[pc->currPoke]->pkMoves[0], 1) == ENEMYDEFEATED){
                if (npc != NULL){
                    npc->currPoke++;
                } else {
                    return WILDDEFEATED;
                }
            } else {
                mvprintw(8, 30, "Move missed!");
            }
            refresh();
            sleep(2);
        }
    } else if (in == '2'){
        if (whoGoesFirst(pc, wildPokemon, &pc->pokemons[pc->currPoke]->pkMoves[1], &wildPokemon->pkMoves[npcMove]) == 1 && switchP == 0){
            mvprintw(8, 0, "You chose %s! ", pc->pokemons[pc->currPoke]->pkMoves[1].identifier);
            if (attack(pc->pokemons[pc->currPoke], wildPokemon, &pc->pokemons[pc->currPoke]->pkMoves[1], 1) == ENEMYDEFEATED){
                if (npc != NULL){
                    npc->currPoke++;
                    return WILDDEFEATED; 
                } else {
                    return WILDDEFEATED;
                }
            } else {
                mvprintw(8, 30, "Move missed!");
            }
            refresh();
            mvprintw(20, 80, "DBG%d", 2697);
            sleep(2);
            if (fightNPCTurn(npc, wildPokemon, pc, npcMove) == PLAYERDEFEATED){
                pc->findFirstPoke();
                mvprintw(9,0 ,"Your Pokemon was knocked out!");
                refresh();
                sleep(3);
            }
        } else {
            if (fightNPCTurn(npc, wildPokemon, pc, npcMove) == PLAYERDEFEATED){
                pc->findFirstPoke();
                mvprintw(9,0 ,"Your Pokemon was knocked out!");
                refresh();
                sleep(3);
                return PLAYERDEFEATED;
            }
            mvprintw(8, 0, "You chose %s! ", pc->pokemons[pc->currPoke]->pkMoves[1].identifier);
            if (attack(pc->pokemons[pc->currPoke], wildPokemon, &pc->pokemons[pc->currPoke]->pkMoves[1], 1) == ENEMYDEFEATED){
                if (npc != NULL){
                    npc->currPoke++;
                } else {
                    return WILDDEFEATED;
                }
            } else {
                mvprintw(8, 30, "Move missed!");
            }
            refresh();
            sleep(2);
        }
    } else if(in == '3'){
        if (whoGoesFirst(pc, wildPokemon, &pc->pokemons[pc->currPoke]->pkMoves[2], &wildPokemon->pkMoves[npcMove]) == 1 && switchP == 0){
            mvprintw(8, 0, "You chose %s! ", pc->pokemons[pc->currPoke]->pkMoves[2].identifier);
            if (attack(pc->pokemons[pc->currPoke], wildPokemon, &pc->pokemons[pc->currPoke]->pkMoves[2], 1) == ENEMYDEFEATED){
                if (npc != NULL){
                    npc->currPoke++;
                    return WILDDEFEATED;
                } else {
                    return WILDDEFEATED;
                }
            } else {
                mvprintw(8, 30, "Move missed!");
            }
            refresh();
            sleep(2);
            if (fightNPCTurn(npc, wildPokemon, pc, npcMove) == PLAYERDEFEATED){
                pc->findFirstPoke();
                mvprintw(9,0 ,"Your Pokemon was knocked out!");
                refresh();
                sleep(3);
            }
        } else {
            if (fightNPCTurn(npc, wildPokemon, pc, npcMove) == PLAYERDEFEATED){
                pc->findFirstPoke();
                mvprintw(9,0 ,"Your Pokemon was knocked out!");
                refresh();
                sleep(3);
                return PLAYERDEFEATED;
            }
            mvprintw(8, 0, "You chose %s! ", pc->pokemons[pc->currPoke]->pkMoves[2].identifier);
            if (attack(pc->pokemons[pc->currPoke], wildPokemon, &pc->pokemons[pc->currPoke]->pkMoves[2], 1) == ENEMYDEFEATED){
                if (npc != NULL){
                    npc->currPoke++;
                } else {
                    return WILDDEFEATED;
                }
            } else {
                mvprintw(8, 30, "Move missed!");
            }
            refresh();
            sleep(2);
        }
    } else if(in == '4'){
        if (whoGoesFirst(pc, wildPokemon, &pc->pokemons[pc->currPoke]->pkMoves[3], &wildPokemon->pkMoves[npcMove]) == 1 && switchP == 0){
            mvprintw(8, 0, "You chose %s! ", pc->pokemons[pc->currPoke]->pkMoves[3].identifier);
            if (attack(pc->pokemons[pc->currPoke], wildPokemon, &pc->pokemons[pc->currPoke]->pkMoves[3], 1) == ENEMYDEFEATED){
                if (npc != NULL){
                    npc->currPoke++;
                    return WILDDEFEATED;
                } else {
                    return WILDDEFEATED;
                }
            } else {
                mvprintw(8, 30, "Move missed!");
            }
            refresh();
            sleep(2);
            if (fightNPCTurn(npc, wildPokemon, pc, npcMove) == PLAYERDEFEATED){
                pc->findFirstPoke();
                mvprintw(9,0 ,"Your Pokemon was knocked out!");
                refresh();
                sleep(3);
            }
        } else {
            if (fightNPCTurn(npc, wildPokemon, pc, npcMove) == PLAYERDEFEATED){
                pc->findFirstPoke();
                mvprintw(9,0 ,"Your Pokemon was knocked out!");
                refresh();
                sleep(3);
                return PLAYERDEFEATED;
            }
            mvprintw(8, 0, "You chose %s! ", pc->pokemons[pc->currPoke]->pkMoves[3].identifier);
            if (attack(pc->pokemons[pc->currPoke], wildPokemon, &pc->pokemons[pc->currPoke]->pkMoves[3], 1) == ENEMYDEFEATED){
                if (npc != NULL){
                    npc->currPoke++;
                } else {
                    return WILDDEFEATED;
                }
            } else {
                mvprintw(8, 30, "Move missed!");
            }
            refresh();
            sleep(2);
        } 
    }
    if (npc != NULL){
        if (npc->isDefeated()){
            return 4;
        }
    }
    
    return 0;         
}

void encounterPokemon(PC *pc){
    Pokemon* spawnedPokemon = new Pokemon(DFC(pc->globalX, pc->globalY));
    pc->findFirstPoke(); //Get first pokemon not knocked out
    int fc = 0;
    bool runCondition = true;
    clear();
    mvprintw(0,0, "A wild %s appeared! They are level %d.", spawnedPokemon->identfier, spawnedPokemon->level);
    mvprintw(1,0, "You can 'f' to fight, 'B' for bag, 'r' to run, and 's' to switch Pokemon");
    refresh();

    while(runCondition){
        int in = getch();
        if(in == 'f' && fc == 0){
            //fight
            if(fight(pc, spawnedPokemon, NULL, 0) == WILDDEFEATED){
                mvprintw(9,0, "You defeated the wild %s! You Can capture or run", spawnedPokemon->identfier);
                refresh();
                fc = 1;
                sleep(4);
            }
        } else if (in == 'B'){
            //bag
           if(pc->openBag(1)==1){
                mvprintw(9,10, "You caught the wild %s!", spawnedPokemon->identfier);
                pc->pokemons[pc->numPK] = spawnedPokemon;
                pc->numPK++;
                refresh();
                runCondition = false;
                sleep(2);
           } else if(pc->openBag(1)==2){
                mvprintw(5,5, "The Pokemon Fled");
                refresh();
                runCondition = false;
                sleep(2);
           } 
        } else if (in == 'r'){
            int runProb = randomGenerator(6, pc->numPK);
            if (runProb == 6 || fc == 1){
                runCondition = false;
            } else {
                mvprintw(5,5, "You couldn't run away!");
                refresh();
                sleep(1);
            }
        } else if (in == 's'){
            //switch pokemon
            clear();
            mvprintw(0,0, "Choose a Pokemon to switch to or press space to cancel. You can only choose Pokemon that are not knocked out.");
            for(int i = 0; i < pc->numPK; i++){
                mvprintw(i+1,0, "Pokemon %d: %s. Health: %d", i+1, pc->pokemons[i]->identfier, pc->pokemons[i]->currHealth);
            }
            int in;
            while ((in = getch()) != 32){
                if(in == '1' && pc->pokemons[0]->currHealth > 0){
                    pc->currPoke = 0;
                    fight(pc, spawnedPokemon, NULL, 1);
                    break;
                } else if (in == '2' && pc->pokemons[1]->currHealth > 0){
                    pc->currPoke = 1;
                    fight(pc, spawnedPokemon, NULL, 1);
                    break;
                } else if (in == '3' && pc->pokemons[2]->currHealth > 0){
                    pc->currPoke = 2;
                    fight(pc, spawnedPokemon, NULL, 1);
                    break;
                } else if (in == '4' && pc->pokemons[3]->currHealth > 0){
                    pc->currPoke = 3;
                    fight(pc, spawnedPokemon, NULL, 1);
                    break;
                } else if (in == '5' && pc->pokemons[4]->currHealth > 0){
                    pc->currPoke = 4;
                    fight(pc, spawnedPokemon, NULL, 1);
                    break;
                } else if (in == '6' && pc->pokemons[5]->currHealth > 0){
                    pc->currPoke = 5;
                    fight(pc, spawnedPokemon, NULL, 1);
                    break;
                } 
            }
        }
        if (pc->isDefeated()){
            runCondition = false;
            clear();
            mvprintw(0,0, "You have been defeated!");
            refresh();
            sleep(2);
        }
        clear();
        mvprintw(0,0, "A wild %s appeared! They are level %d.", spawnedPokemon->identfier, spawnedPokemon->level);
        mvprintw(1,0, "You can 'f' to fight, 'B' for bag, 'r' to run, and 's' to switch Pokemon");
        refresh();
    }

}

void moveOnGate(worldMap *wm, mapclass *terrainMap, PC *pc, int newRow, int newCol, int curRow, int curCol, int direc, int npcNum){
    mvprintw(ROW+2, 0, "new row %d, new col %d", newRow, newCol);
    switch (direc){
        case N:
            if ((newCol == terrainMap->gateN && newRow == 0) && (pc->globalX != 0)){
                fly(--pc->globalX, pc->globalY, wm, npcNum, N);
            }
            break;
        case E:
            if ((newCol == COL - 1 && newRow == terrainMap->gateE) && (pc->globalY != worldYSize-1) ){
                fly(pc->globalX, ++pc->globalY, wm, npcNum, E);
            }
            break;

        case S:
            if (newCol == terrainMap->gateS && newRow == ROW-1 && pc->globalX != worldXSize-1){
                fly(++pc->globalX, pc->globalY, wm, npcNum, S);
            }
            break;
        case W:
            if (newCol == 0 && newRow == terrainMap->gateW && pc->globalY != 0){
                mvprintw(0, 10, " Move W");
                refresh();
                fly(pc->globalX, --pc->globalY, wm, npcNum, W);
            }
            break;
            
        case NE:
            if ((newCol == terrainMap->gateN && newRow == 0) && (pc->globalX != 0)){ //north gate
                fly(--pc->globalX, pc->globalY, wm, npcNum, N);
            } else if ((newCol == COL - 1 && newRow == terrainMap->gateE) && (pc->globalY != worldYSize-1)){ //East gate
                fly(pc->globalX, ++pc->globalY, wm, npcNum, E);
            }
            break;
        case NW:
            if ((newCol == terrainMap->gateN && newRow == 0) && (pc->globalX != 0)){ // north gate
                fly(--pc->globalX, pc->globalY, wm, npcNum, N);
            } else if (newCol == 0 && newRow == terrainMap->gateW && pc->globalY != 0) { //west gate
                fly(pc->globalX, --pc->globalY, wm, npcNum, W);
            }
            break;
        case SW:
            if (newCol == terrainMap->gateS && newRow == ROW-1 && pc->globalX != worldXSize-1){ //South gate
                fly(++pc->globalX, pc->globalY, wm, npcNum, S);
            } else if (newCol == 0 && newRow == terrainMap->gateW && pc->globalY != 0){ //west gate
                fly(pc->globalX, --pc->globalY, wm, npcNum, W);
            }
            break;
        case SE:
            if (newCol == terrainMap->gateS && newRow == ROW-1 && pc->globalX != worldXSize-1){
                fly(++pc->globalX, pc->globalY, wm, npcNum, S);
            } else if ((newCol == COL - 1 && newRow == terrainMap->gateE) && (pc->globalY != worldYSize-1)){
                fly(pc->globalX, ++pc->globalY, wm, npcNum, E);
            }
            break;
    }
}


void parsePokemonFile(){
    //std::vector<PokemonFile> pokemonVector;
    
    char path[300] = "/share/cs327/pokedex/pokedex/data/csv/pokemon.csv";
    char *home = getenv("HOME");
    
    FILE *file = fopen(path, "r");
    
    if (file == NULL){
        strcat(home, "/.poke327/pokedex/pokedex/data/csv/pokemon.csv");
        //printf("home is %s\n", home);
        file = fopen(home, "r");
    }

    if (file != NULL){
        char line[100];

        while (fgets(line, sizeof(line), file)) { 
          PokemonFile pokemon;
            char *token = strtok(line, ","); 
            pokemon.id = (token != NULL) ? atoi(token) : INT_MAX;
            token = strtok(NULL, ",");
            if (token != NULL) {
                strcpy( pokemon.identifier, token);
            } else {
                 strcpy( pokemon.identifier , "");
            }
            token = strtok(NULL, ",");
            pokemon.species_id = (token != NULL) ? atoi(token) : INT_MAX;
            token = strtok(NULL, ",");
            pokemon.height = (token != NULL) ? atoi(token) : INT_MAX;
            token = strtok(NULL, ",");
            pokemon.weight = (token != NULL) ? atoi(token) : INT_MAX;
            token = strtok(NULL, ",");
            pokemon.base_experience = (token != NULL) ? atoi(token) : INT_MAX;
            token = strtok(NULL, ",");
            pokemon.order = (token != NULL) ? atoi(token) : INT_MAX;
            token = strtok(NULL, ",");
            pokemon.is_default = (token != NULL) ? atoi(token) : INT_MAX;

            pokemonVector.push_back(pokemon);
            
  
        }
        
        //printf("%d\n",(int)pokemonVector.size());
        fclose(file);
        //globalPokemonVector = &pokemonVector;
    } 
    else {
        printf("File not found: pokemon.csv\n");
    }
}

void parseMovesFile(){
    //std::vector<Moves> movesVector;
    int size = 0;
    char path[300] = "/share/cs327/pokedex/pokedex/data/csv/moves.csv";
    char *home = getenv("HOME");
    
    FILE *file = fopen(path, "r");
    
    if (file == NULL){
        strcat(home, "/.poke327/pokedex/pokedex/data/csv/moves.csv");
        //printf("home is %s\n", home);
        file = fopen(home, "r");
    }

    if (file != NULL){
        char line[100];

        while (fgets(line, sizeof(line), file)) { 
          Moves moves;
            char *token = strtok(line, ","); 
            moves.id = (token != NULL) ? atoi(token) : INT_MAX;
            token = strtok(NULL, ",");
            if (token != NULL) {
                strcpy( moves.identifier, token);
            } else {
                 strcpy( moves.identifier , "");
            }
            token = strtok(NULL, ",");
            moves.generation_id = (token != NULL) ? atoi(token) : INT_MAX;
            token = strtok(NULL, ",");
            moves.type_id = (token != NULL) ? atoi(token) : INT_MAX;
            token = strtok(NULL, ",");
            moves.power = (token != NULL) ? atoi(token) : INT_MAX;
            token = strtok(NULL, ",");
            moves.pp = (token != NULL) ? atoi(token) : INT_MAX;
            token = strtok(NULL, ",");
            moves.accuracy = (token != NULL) ? atoi(token) : INT_MAX;
            token = strtok(NULL, ",");
            moves.priority = (token != NULL) ? atoi(token) : INT_MAX;
            token = strtok(NULL, ",");
            moves.target_id = (token != NULL) ? atoi(token) : INT_MAX;
            token = strtok(NULL, ",");
            moves.damage_class_id = (token != NULL) ? atoi(token) : INT_MAX;
            token = strtok(NULL, ",");
            moves.effect_id = (token != NULL) ? atoi(token) : INT_MAX;
            token = strtok(NULL, ",");
            moves.effect_chance = (token != NULL) ? atoi(token) : INT_MAX;
            token = strtok(NULL, ",");
            moves.contest_type_id = (token != NULL) ? atoi(token) : INT_MAX;
            token = strtok(NULL, ",");
            moves.contest_effect_id = (token != NULL) ? atoi(token) : INT_MAX;
            token = strtok(NULL, ",");
            moves.super_contest_effect_id = (token != NULL) ? atoi(token) : INT_MAX;
            movesVector.push_back(moves);
            size++;
        }
        //printf("%d",movesVector.size());
        
        fclose(file);
    } 
    else {
        printf("File not found: moves.csv\n");
    }
}

void parsePokemonMovesFile(){
    //std::vector<PokemonMoves> pokemonMovesVector;
    int size = 0;
    char path[300] = "/share/cs327/pokedex/pokedex/data/csv/pokemon_moves.csv";
    char *home = getenv("HOME");
    
    FILE *file = fopen(path, "r");
    
    if (file == NULL){
        strcat(home, "/.poke327/pokedex/pokedex/data/csv/pokemon_moves.csv");
        //printf("home is %s\n", home);
        file = fopen(home, "r");
    }

    if (file != NULL){
        char line[100];

        while (fgets(line, sizeof(line), file)) { 
          PokemonMoves pokemonMoves;
            char *token = strtok(line, ","); 
            pokemonMoves.pokemon_id = (token != NULL) ? atoi(token) : INT_MAX;
            token = strtok(NULL, ",");
            pokemonMoves.version_group_id = (token != NULL) ? atoi(token) : INT_MAX;
            token = strtok(NULL, ",");
            pokemonMoves.move_id = (token != NULL) ? atoi(token) : INT_MAX;
            token = strtok(NULL, ",");
            pokemonMoves.pokemon_move_method_id = (token != NULL) ? atoi(token) : INT_MAX;
            token = strtok(NULL, ",");
            pokemonMoves.level = (token != NULL) ? atoi(token) : INT_MAX;
            token = strtok(NULL, ",");
            pokemonMoves.order = (token != NULL) ? atoi(token) : INT_MAX;

            pokemonMovesVector.push_back(pokemonMoves);
            size++;
        }
        //printf("%d",pokemonMovesVector.size());
        
        fclose(file);
    } 
    else {
        printf("File not found: pokemon_moves.csv\n");
    }
}

void parsePokemonSpeciesFile(){
    //std::vector<PokemonSpecies> pokemonSpeciesVector;
    int size = 0;
    char path[300] = "/share/cs327/pokedex/pokedex/data/csv/pokemon_species.csv";
    char *home = getenv("HOME");

    FILE *file = fopen(path, "r");

    if (file == NULL){
        strcat(home, "/.poke327/pokedex/pokedex/data/csv/pokemon_species.csv");
        //printf("home is %s\n", home);
        file = fopen(home, "r");
    }

    if (file != NULL){
        char line[100];

        while (fgets(line, sizeof(line), file)) { 
          PokemonSpecies pokemonSpecies;
            char *token = strtok(line, ","); 
            pokemonSpecies.id = (token != NULL) ? atoi(token) : INT_MAX;
            token = strtok(NULL, ",");
            if (token != NULL) {
                strcpy( pokemonSpecies.identifier, token);
            } else {
                 strcpy( pokemonSpecies.identifier , "");
            }
            token = strtok(NULL, ",");
            pokemonSpecies.generation_id = (token != NULL) ? atoi(token) : INT_MAX;
            token = strtok(NULL, ",");
            pokemonSpecies.evolves_from_species_id = (token != NULL) ? atoi(token) : INT_MAX;
            token = strtok(NULL, ",");
            pokemonSpecies.evolution_chain_id = (token != NULL) ? atoi(token) : INT_MAX;
            token = strtok(NULL, ",");
            pokemonSpecies.color_id = (token != NULL) ? atoi(token) : INT_MAX;
            token = strtok(NULL, ",");
            pokemonSpecies.shape_id = (token != NULL) ? atoi(token) : INT_MAX;
            token = strtok(NULL, ",");
            pokemonSpecies.habitat_id = (token != NULL) ? atoi(token) : INT_MAX;
            token = strtok(NULL, ",");
            pokemonSpecies.gender_rate = (token != NULL) ? atoi(token) : INT_MAX;
            token = strtok(NULL, ",");
            pokemonSpecies.capture_rate = (token != NULL) ? atoi(token) : INT_MAX;
            token = strtok(NULL, ",");
            pokemonSpecies.base_happiness = (token != NULL) ? atoi(token) : INT_MAX;
            token = strtok(NULL, ",");
            pokemonSpecies.is_baby = (token != NULL) ? atoi(token) : INT_MAX;
            token = strtok(NULL, ",");
            pokemonSpecies.hatch_counter = (token != NULL) ? atoi(token) : INT_MAX;
            token = strtok(NULL, ",");
            pokemonSpecies.has_gender_differences = (token != NULL) ? atoi(token) : INT_MAX;
            token = strtok(NULL, ",");
            pokemonSpecies.growth_rate_id = (token != NULL) ? atoi(token) : INT_MAX;
            token = strtok(NULL, ",");
            pokemonSpecies.forms_switchable = (token != NULL) ? atoi(token) : INT_MAX;
            token = strtok(NULL, ",");
            pokemonSpecies.order = (token != NULL) ? atoi(token) : INT_MAX;
            token = strtok(NULL, ",");
            pokemonSpecies.conquest_order = (token != NULL) ? atoi(token) : INT_MAX;

            pokemonSpeciesVector.push_back(pokemonSpecies);
            size++;
        }
        //printf("%d",pokemonSpeciesVector.size());
        
        fclose(file);
    }
    else {
        printf("File not found: pokemon_species.csv\n");
    }
}

void parseExperienceFile(){
    //std::vector<Experience> experienceVector;
    int size = 0;
    char path[300] = "/share/cs327/pokedex/pokedex/data/csv/experience.csv";
    char *home = getenv("HOME");

    FILE *file = fopen(path, "r");

    if (file == NULL){
        strcat(home, "/.poke327/pokedex/pokedex/data/csv/experience.csv");
        //printf("home is %s\n", home);
        file = fopen(home, "r");
    }

    if (file != NULL){
        char line[100];

        while (fgets(line, sizeof(line), file)) { 
          Experience experience;
            char *token = strtok(line, ","); 
            experience.growth_rate_id = (token != NULL) ? atoi(token) : INT_MAX;
            token = strtok(NULL, ",");
            experience.level = (token != NULL) ? atoi(token) : INT_MAX;
            token = strtok(NULL, ",");
            experience.experience = (token != NULL) ? atoi(token) : INT_MAX;

            experienceVector.push_back(experience);
            size++;
        }
        //printf("%d",experienceVector.size());
        
        fclose(file);
    }
    else {
        printf("File not found: experience.csv\n");
    }
}

void parseTypeNamesFile(){
    //std::vector<TypeNames> typeNamesVector;
    int size = 0;
    char path[300] = "/share/cs327/pokedex/pokedex/data/csv/type_names.csv";
    char *home = getenv("HOME");

    FILE *file = fopen(path, "r");

    if (file == NULL){
        strcat(home, "/.poke327/pokedex/pokedex/data/csv/type_names.csv");
        //printf("home is %s\n", home);
        file = fopen(home, "r");
    }

    if (file != NULL){
        char line[100];

        while (fgets(line, sizeof(line), file)) { 
          TypeNames typeNames;
            char *token = strtok(line, ","); 
            typeNames.type_id = (token != NULL) ? atoi(token) : INT_MAX;
            token = strtok(NULL, ",");
            typeNames.local_language_id = (token != NULL) ? atoi(token) : INT_MAX;
            token = strtok(NULL, ",");
            if (token != NULL) {
                strcpy( typeNames.name, token);
            } else {
                 strcpy( typeNames.name , "");
            }

            typeNamesVector.push_back(typeNames);
            size++;
        }
        //printf("%d",typeNamesVector.size());
        
        fclose(file);
    }
    else {
        printf("File not found: type_names.csv\n");
    }

}
    
void parsePokemonStatsFile(){
    //std::vector<PokemonStats> pokemonStatsVector;
    int size = 0;
    char path[300] = "/share/cs327/pokedex/pokedex/data/csv/pokemon_stats.csv";
    char *home = getenv("HOME");

    FILE *file = fopen(path, "r");

    if (file == NULL){
        strcat(home, "/.poke327/pokedex/pokedex/data/csv/pokemon_stats.csv");
        //printf("home is %s\n", home);
        file = fopen(home, "r");
    }

    if (file != NULL){
        char line[100];
        /*
        int pokemon_id;
    int stat_id;
    int base_stat;
    int effort;
    */
        while (fgets(line, sizeof(line), file)) { 
          PokemonStats pokemonStats;
            char *token = strtok(line, ","); 
            pokemonStats.pokemon_id = (token != NULL) ? atoi(token) : INT_MAX;
            token = strtok(NULL, ",");
            pokemonStats.stat_id = (token != NULL) ? atoi(token) : INT_MAX;
            token = strtok(NULL, ",");
            pokemonStats.base_stat = (token != NULL) ? atoi(token) : INT_MAX;
            token = strtok(NULL, ",");
            pokemonStats.effort = (token != NULL) ? atoi(token) : INT_MAX;

            pokemonStatsVector.push_back(pokemonStats);
            size++;
        }
        //printf("%d",pokemonStatsVector.size());
        
        fclose(file);
    }
    else {
        printf("File not found: pokemon_stats.csv\n");
    }
}

void parseStatsFile(){
    //std::vector<Stats> statsVector;
    int size = 0;
    char path[300] = "/share/cs327/pokedex/pokedex/data/csv/stats.csv";
    char *home = getenv("HOME");

    FILE *file = fopen(path, "r");

    if (file == NULL){
        strcat(home, "/.poke327/pokedex/pokedex/data/csv/stats.csv");
        //printf("home is %s\n", home);
        file = fopen(home, "r");
    }

    if (file != NULL){
        char line[100];
/*
int id;
    char identifier[50];
    int damage_class_id;
    int is_battle_only;
    int game_index;*/
        while (fgets(line, sizeof(line), file)) { 
          Stats stats;
            char *token = strtok(line, ","); 
            stats.id = (token != NULL) ? atoi(token) : INT_MAX;
            token = strtok(NULL, ",");
            if (token != NULL) {
                strcpy( stats.identifier, token);
            } else {
                 strcpy( stats.identifier , "");
            }
            token = strtok(NULL, ",");
            stats.damage_class_id = (token != NULL) ? atoi(token) : INT_MAX;
            token = strtok(NULL, ",");
            stats.is_battle_only = (token != NULL) ? atoi(token) : INT_MAX;
            token = strtok(NULL, ",");
            stats.game_index = (token != NULL) ? atoi(token) : INT_MAX;

            statsVector.push_back(stats);
            size++;
        }
        //printf("%d",statsVector.size());
        
        fclose(file);
    }
    else {
        printf("File not found: stats.csv\n");
    }
}

void parsePokemonTypesFile(){
    //std::vector<PokemonTypes> pokemonTypesVector;
    int size = 0;
    char path[300] = "/share/cs327/pokedex/pokedex/data/csv/pokemon_types.csv";
    char *home = getenv("HOME");

    FILE *file = fopen(path, "r");

    if (file == NULL){
        strcat(home, "/.poke327/pokedex/pokedex/data/csv/pokemon_types.csv");
        //printf("home is %s\n", home);
        file = fopen(home, "r");
    }

    if (file != NULL){
        char line[100];

        while (fgets(line, sizeof(line), file)) { 
          PokemonTypes pokemonTypes;
            char *token = strtok(line, ","); 
            pokemonTypes.pokemon_id = (token != NULL) ? atoi(token) : INT_MAX;
            token = strtok(NULL, ",");
            pokemonTypes.type_id = (token != NULL) ? atoi(token) : INT_MAX;
            token = strtok(NULL, ",");
            pokemonTypes.slot = (token != NULL) ? atoi(token) : INT_MAX;

            pokemonTypesVector.push_back(pokemonTypes);
            size++;
        }
        //printf("%d",pokemonTypesVector.size());
        
        fclose(file);

    }
    else {
        printf("File not found: pokemon_types.csv\n");
    }
}

int saveGameState(worldMap *wm){
    endwin();
    std::cout << "You are saving the game." << std::endl;
    std::ofstream outfile ("savedGame.txt");


    // std::ofstream myfile;
    // myfile.open("saveTest1.txt");
    // myfile << "Writing this to a file.\n";
    //  if (myfile.is_open())
    // {
    //     myfile << "This is a line.\n";
    //     myfile << "This is another line.\n";
    //     myfile.close();
    // }
    // else std::cout << "Unable to open file";
    // myfile.close();
    outfile << wm->seed << ", " << wm->numTrainers << std::endl; //save world map

    //save pc
    outfile << wm->player->row <<", " << wm->player->col << ", " << wm->player->globalX << ", " << wm->player->globalY << ", " << wm->player->numPK << ", " << wm->player->currPoke << ", " << wm->player->potions << ", " << wm->player->pokeballs << ", " << wm->player->revives << std::endl;
    for (int i=0; i<wm->player->numPK; i++){ //Save pokemon
        outfile << wm->player->pokemons[i]->id << ", " << wm->player->pokemons[i]->type << ", " << wm->player->pokemons[i]->health << ", " << wm->player->pokemons[i]->currHealth << ", " << wm->player->pokemons[i]->level 
        << wm->player->pokemons[i]->attack << ", " << wm->player->pokemons[i]->defense << ", " << wm->player->pokemons[i]->gender  << ", " << wm->player->pokemons[i]->speed << ", " << wm->player->pokemons[i]->specialDefense << ", " 
        << wm->player->pokemons[i]->specialAttack << ", " << wm->player->pokemons[i]->shiny << ", ";
        for (int j=0; j<(int)wm->player->pokemons[i]->pkMoves.size(); j++){
            outfile << wm->player->pokemons[i]->pkMoves[j].id;
            if (j != (int)wm->player->pokemons[i]->pkMoves.size()-1){
                outfile << ", ";
            } else {
                outfile << std::endl;
            }
        }
    }

    //save terrain maps
    for(int wmrow = 0; wmrow < worldXSize; wmrow++){
        for(int wmcol = 0; wmcol < worldYSize; wmcol++){
            if (wm->arr[wmrow][wmcol] != NULL){
                outfile << wm->arr[wmrow][wmcol]->row << ", " << wm->arr[wmrow][wmcol]->col << ", " << wm->arr[wmrow][wmcol]->gateN << ", " << wm->arr[wmrow][wmcol]->gateS << ", " << wm->arr[wmrow][wmcol]->gateW << ", " << wm->arr[wmrow][wmcol]->gateE << ", (" << wm->arr[wmrow][wmcol]->connection1[0] << ", " << wm->arr[wmrow][wmcol]->connection1[1] << "), (" << wm->arr[wmrow][wmcol]->connection2[0] << ", " << wm->arr[wmrow][wmcol]->connection2[1] << "), " << wm->arr[wmrow][wmcol]->NPCSInit << std::endl;
                // make save npcs
                while (wm->arr[wmrow][wmcol]->terrainHeap->size > 0){
                    //NPC *npc = (NPC*)extractMin(wm->arr[wmrow][wmcol]->h);
                    heapNode* hn = extractMin(wm->arr[wmrow][wmcol]->terrainHeap);

                    if (hn->pc != NULL){
                        continue;
                    }


                    NPC *npc = hn->npc;
                    outfile << "[ " << hn->weight << ", " << npc->symb << ", " << npc->row << ", " << npc->col << ", " << npc->direc << ", " << npc->defeated << ", " << npc->numPK << ", " << npc->currPoke << std::endl;
                    for (int i=0; i<npc->numPK; i++){
                        outfile << npc->pokemons[i]->id << ", " << npc->pokemons[i]->type << ", " << npc->pokemons[i]->health << ", " << npc->pokemons[i]->currHealth << ", " << npc->pokemons[i]->level 
                        << npc->pokemons[i]->attack << ", " << npc->pokemons[i]->defense << ", " << npc->pokemons[i]->gender  << ", " << npc->pokemons[i]->speed << ", " << npc->pokemons[i]->specialDefense << ", " 
                        << npc->pokemons[i]->specialAttack << ", " << npc->pokemons[i]->shiny << ", ";
                        for (int j=0; j<(int)npc->pokemons[i]->pkMoves.size(); j++){
                            outfile << npc->pokemons[i]->pkMoves[j].id;
                            if (j != (int)npc->pokemons[i]->pkMoves.size()-1){
                                outfile << ", ";
                            } else {
                                outfile << std::endl;
                            }
                        }
                    }
                    outfile << "]" << std::endl;
                }
                outfile << std::endl;
            }
        }
    }




    outfile.close();

    std::cout << "Game Saved.\nThanks for playing! See you soon." << std::endl;
    exit(0);
}

void loadGameState(int encrypted){
    parsePokemonFile();
    parseMovesFile();    
    parsePokemonMovesFile();
    parsePokemonSpeciesFile();
    parseExperienceFile();
    parseTypeNamesFile();
    parsePokemonStatsFile();
    parseStatsFile();
    parsePokemonTypesFile();
    
    FILE *file = fopen("savedGame.txt", "r");
    worldMap wm;
    wm.setWorldToNull();
    //PC
    //mapClass arr



    PC *pc = (PC*)malloc(sizeof(PC));
    // int row;
    // int col;
    // int globalX;
    // int globalY;
    pc->numPK = 0;
    // pc->currPoke = 0;
    // pc->globalX = 0;
    // int potions;
    // int pokeballs;
    // int revives;
    // Pokemon* pokemons[6];

    for (int i=0; i<pc->numPK; i++){
        pc->pokemons[i] = (Pokemon*)malloc(sizeof(Pokemon));
        /////
    }

    for(int wmrow = 0; wmrow < ROW; wmrow++){
        for(int wmcol = 0; wmcol < COL; wmcol++){
            wm.arr[wmrow][wmcol] = (mapclass*)malloc(sizeof(mapclass));
            // int gateN;//top
            // int gateS;//bottom
            // int gateW;//left
            // int gateE;//right
            // int connection1[2];
            // int connection2[2];

            /*I can just generate the terrain from the seed*/

            // char terrain[ROW][COL];
            // NPC* npcArray[NPCROW][NPCCOL];
            // int NPCSInit; 
            // heap* terrainHeap;
            for (int i=0; i<wm.numTrainers; i++){
                NPC *npc = (NPC*)malloc(sizeof(NPC));
                // int symb; 
                // int row; 
                // int col;
                // int direc;
                // int weightArr[NPCROW][NPCCOL]; 
                // int defeated;
                // Pokemon* pokemons[6];
                // int numPK;
                // int currPoke;
                for (int poke = 0; poke < npc->numPK; poke++){
                    npc->pokemons[poke] = (Pokemon*)malloc(sizeof(Pokemon));
                    /////
                }
                /*add to heap*/
            }
        }
    }

    /*Add pc to heap with lowest weight*/
    
    initscr();
    keypad(stdscr, TRUE);
    printMap(wm.arr[200][200], wm.player);
    moveEveryone(&wm, wm.arr[wm.player->row][wm.player->col], wm.numTrainers, wm.arr[wm.player->row][wm.player->col]->terrainHeap);
}



int main(int argc, char *argv[]){
    int seed;
    //seed = time(NULL);
    seed = 11223344;
    srand(seed); //11223344
   
    worldMap wm;
    wm.seed = seed;
    wm.numTrainers = 10;
    int currR = 200;
    int currC = 200;

    parsePokemonFile();
    parseMovesFile();    
    parsePokemonMovesFile();
    parsePokemonSpeciesFile();
    parseExperienceFile();
    parseTypeNamesFile();
    parsePokemonStatsFile();
    parseStatsFile();
    parsePokemonTypesFile();

    //parseMovesFile();
    if (argc >= 2 ){
        if (argc >= 3 && strcmp(argv[1], "--numtrainers") == 0) {
            wm.numTrainers = atoi(argv[2]);
        } 
        else if (argc >= 3 && strcmp(argv[1], "--load") == 0) {
            loadGameState(0);
            exit(0);
        }
    }
       
    

    printf("%d\n", wm.numTrainers);
    
    //return 0;
    
    initscr();
    keypad(stdscr, TRUE);
    createWorldMap(&wm);
    createMap(currR, currC, &wm, wm.numTrainers);
    //lprintf("(%d, %d)\n", currX-200, currY-200);

    printMap(wm.arr[200][200], wm.player);
    moveEveryone(&wm, wm.arr[200][200], wm.numTrainers, wm.arr[200][200]->terrainHeap);
    
    endwin();
    return 0;
}